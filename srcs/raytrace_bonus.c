/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:54:39 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:57:54 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/multithread.h"

// clear all data stored to prepare a new frame
inline void	init_raytracing(t_app *app)
{
	size_t	i;
	t_scene	*scene;

	app->error_code = 0;
	app->error_message = NULL;
	scene = app->scene;
	if (app->data)
		free_array((void **)app->data, W_HEIGHT);
	app->data = (t_color **)ft_calloc((W_HEIGHT), sizeof(t_color *));
	i = 0;
	while (i < W_HEIGHT)
		app->data[i++] = ft_calloc(W_WIDTH, sizeof (t_color));
	if (!scene->selected_camera)
		scene->selected_camera = ft_get_elem(scene->cameras, 0);
}

inline t_color	shade_hit(t_scene *world, t_hit *hit)
{
	t_color	color;
	t_light	*light;
	size_t	i;

	color = v4(0.0f, 0.0f, 0.0f, 1.0f);
	i = 0;
	while (i < world->lights->length)
	{
		light = ft_get_elem(world->lights, i);
		color = v4_add(color, lighting(world, hit, light));
		i++;
	}
	return (color);
}

inline t_color	color_at(t_scene *world, t_ray *ray)
{
	t_array	*records;
	t_hit	*first_hit;
	t_color	color;

	color = v4(0.0f, 0.0f, 0.0f, 1.0f);
	records = do_intersect_objs(world, ray, false);
	first_hit = get_first_obj_hit(records, RAY_T_MAX, 0);
	if (first_hit != NULL)
		color = shade_hit(world, first_hit);
	ft_free_d_array(records);
	return (color);
}

inline t_color get_pixel_clr(t_scene *scene, double x, double y)
{
	t_color color;
	t_cam *camera;
	t_ray *ray;

	camera = scene->selected_camera;
	x = x + 0.5;
	y = y + 0.5;
	ray = ray_for_pixel(camera, x, y);
	color = color_at(scene, ray);
	free(ray);
	return (color);
}

void	*run_thread_pixel(void *thread_info)
{
	t_thread	*t;
	int			y;
	int			x;
	t_color		color;

	t = thread_info;
	y = t->start;
	while (y < t->end)
	{
		x = 0;
		while (x < (W_WIDTH))
		{
			color = get_pixel_clr(t->scene, (double)x, (double)y);
			pthread_mutex_lock(t->write_mutex);
			t->data[y][x] = color;
			//printf("something\n");
			pthread_mutex_unlock(t->write_mutex);
			x++;
		}
		y++;
	}
	return (t);
}

bool	render(t_app *app)
{
	init_raytracing(app);
	run_threads(run_thread_pixel, app->scene, app->data);
	return (true);
}

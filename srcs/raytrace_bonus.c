/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:54:39 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 18:26:13 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/multithread.h"

// clear all data stored to prepare a new frame
static inline void	print_clr_to_screen(t_thread *t, t_color clr, int x, int y)
{
	int		pos;
	char 	*pixel;
	t_image	*img;

	img = t->app->img;
	if (t->app->out_fd != 0)
	{
		t->data[y][x] = clr;
	}
	else
	{
		pos = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		pixel = img->data + pos;
		*(unsigned int *)pixel = get_trgb(clr);
		//print_progress(app->scene->pix_traced);
	}
}

inline t_color	shade_hit(t_scene *world, t_hit *hit)
{
	t_color	color;
	t_light	*light;
	size_t	i;

	color = (t_v4){0, 0, 0, 1};
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

	color = (t_v4){0, 0, 0, 1};
	records = do_intersect_objs(world, ray);
	first_hit = get_first_obj_hit(records, RAY_T_MAX, 0);
	if (first_hit != NULL)
	{
		ft_compute_hit(first_hit);
		color = shade_hit(world, first_hit);
	}
	ft_free_d_array(records);
	return (color);
}

t_color	get_pixel_clr(t_scene *scene, double x, double y)
{
	t_color	color;
	t_cam	*camera;
	t_ray	*ray;

	camera = scene->selected_camera;
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
	t_color		pix_clr;

	t = thread_info;
	y = t->start;
	while (y < t->end)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			pix_clr = get_pixel_clr(t->scene, (x + 0.5), (y + 0.5));
			pthread_mutex_lock(t->write_mutex);
			t->scene->pix_traced++;
			print_clr_to_screen(t, pix_clr, x, y);
			pthread_mutex_unlock(t->write_mutex);
			x++;
		}
		y++;
	}
	return (t);
}

bool	render(t_app *app)
{
	app->scene->pix_traced = 0;
	run_threads(run_thread_pixel, app, app->data);
	app->scene->pix_traced = 0;
	app->conf.rerender = true;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:21:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_raytracing(t_app *app)
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

/*
 * Return a color vector (s_vector4) clamped between (0-1)
*/
inline t_color	do_tracing(t_scene *scene, t_ray *ray, double max_time, double deep)
{
	t_color	color;
	t_array	*records;
	t_hit	*first;

	color = v4(0.0f, 0.0f, 0.0f, 1.0f);
	records = do_intersect_objs(scene, ray, false);
	first = get_first_obj_hit(records, max_time);
	(void)deep;
	if (first != NULL)
	{
		if (first->intersection == true)
			color = first->object->color;
	}
	ft_free_d_array(records);
	return (color);
}

static inline t_color	get_pixel_data(t_scene *scene, double x, double y)
{
	t_color	color;
	t_cam	*camera;
	t_ray	*ray;

	camera = scene->selected_camera;
	ray = get_viewport_ray(x, y, camera);
	color = do_tracing(scene, ray, RAY_T_MAX, 0);
	free(ray);
	return (color);
}

bool	render(t_app *app)
{
	int		x;
	int		y;
	double	x_pixel;
	double	y_pixel;

	init_raytracing(app);
	y = 0;
	while (y < (W_HEIGHT))
	{
		x = 0;
		while (x < (W_WIDTH))
		{
			x_pixel = x + 0.5;
			y_pixel = y + 0.5;
			app->data[y][x] = get_pixel_data(app->scene, x_pixel, y_pixel);
			x++;
		}
		y++;
	}
	return (true);
}

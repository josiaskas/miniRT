/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 18:24:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/multithread.h"
#include <stdio.h>


void init_raytracing(t_app *app)
{
	size_t	i;
	t_scene	*scene;

	app->error_code = 0;
	app->error_message = NULL;
	printf("Start ray tracing\n");
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

t_color get_pixel_data(t_scene *scene, int x, int y)
{
	t_color	color;
	t_cam	*camera;
	t_ray	*ray;

	camera	= scene->selected_camera;
	ray		= get_viewport_ray(x, y, camera);
	color	= do_intersect_object(scene, ray, RAY_T_MAX);
	free(ray);
	return (color);
}

void	*run_thread_pixel(void *thread_info)
{
	t_thread	*data;
	int			x;
	int			y;

	data = (t_thread *)thread_info;
	x = data->x;
	y = data->y;
	data->data[y][x] = get_pixel_data(data->scene, (double)x, (double)y);
	return (data);
}

bool	do_raytracing(t_app *app)
{
	init_raytracing(app);
	run_threads(run_thread_pixel, app->scene, app->data);
	printf("finished raytracing\n");
	return (true);
}

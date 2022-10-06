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

t_color	get_pixel_data(t_scene *scene, double x, double y)
{
	t_color	color;
	t_cam	*camera;
	t_ray	*ray;

	camera = scene->selected_camera;
	ray = get_viewport_ray(x, y, camera);
	color = do_tracing(scene, ray, RAY_T_MAX);
	free(ray);
	return (color);
}

bool	render(t_app *app)
{
	int		x;
	int		y;

	y = 0;
	init_raytracing(app);
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			app->data[y][x] = get_pixel_data(app->scene, (double)x, (double)y);
			x++;
		}
		y++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include <stdio.h>

void	init_raytracing(t_app *app)
{
	t_scene	*scene;

	app->error_code = 0;
	app->error_message = NULL;
	scene = app->scene;
	if (app->data)
		free(app->data);
	app->data = ft_calloc((W_WIDTH * W_HEIGHT), sizeof(t_vector));
	if (!scene->selected_camera)
		scene->selected_camera = ft_get_elem(scene->cameras, 0);
}

bool	do_raytracing(t_app *app)
{
	t_ray	*ray;
	t_scene	*scene;

	scene = app->scene;
	ft_putendl_fd("Start ray tracing", STDOUT_FILENO);
	init_raytracing(app);

	//future should move 0->W_WIDTH, 0->W_HEIGHT
	ray = get_viewport_ray(0, 0, scene->selected_camera);
	printf("- Pixel (0,0) -\nRayon origine p_view (a n distance de la camera): (%lf, %lf, %lf)\n", ray->origin.x, ray->origin.y,
		   ray->origin.z);
	printf("Rayon vecteur: (%lf, %lf, %lf)\n", ray->dir.x, ray->dir.y,
		   ray->dir.z);
	free(ray);
	ray = get_viewport_ray((double)W_WIDTH, 0, scene->selected_camera);
	printf("- Pixel (%d, 0) -\nRayon origine p_view (a n distance de la camera): (%lf, %lf, %lf)\n",W_WIDTH, ray->origin.x, ray->origin.y,
		   ray->origin.z);
	printf("Rayon vecteur: (%lf, %lf, %lf)\n", ray->dir.x, ray->dir.y,
		   ray->dir.z);
	free(ray);
	return (true);
}
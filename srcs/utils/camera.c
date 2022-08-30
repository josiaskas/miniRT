/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/28 12:16:05 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

// return a t_cam * , can be freed with free_cam
inline t_cam	*build_camera(t_point origin, t_vector dir, double angle)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		cam->origin = origin;
		cam->orientation = dir;
		cam->h_angle = angle;
	}
	return (cam);
}

inline t_scene	*init_scene()
{
	t_scene	*scene;

	scene = NULL;
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (scene)
	{
		scene->hittable = ft_new_array();
		scene->lights = ft_new_array();
		scene->cameras = ft_new_array();
	}
	return (scene);
}

// destroy hittable, lights and cameras on the scene
void	free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_free_d_array(scene->hittable);
		ft_free_d_array(scene->lights);
		ft_free_d_array(scene->cameras);
		free(scene);
	}
}
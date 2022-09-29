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

#include "minirt.h"
#include "raytrace.h"
#include <stdio.h>

inline t_scene *init_scene()
{
	t_scene	*scene;

	scene = NULL;
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (scene)
	{
		scene->hittable = ft_new_array();
		scene->lights = ft_new_array();
		scene->cameras = ft_new_array();
		scene->ambiant.intensity = 0;
	}
	return (scene);
}

// on essaye le plus possible d'avoir y = 1
void build_camera_viewport_vectors(t_cam *cam)
{
	t_vector	v;
	t_vector	u;

	v = cam->dir;
	if (v.x != 0)
		cam->dir_ort = vect3(((-v.y) / v.x), 1, 0);
	else if (v.z != 0)
		cam->dir_ort = vect3(0, 1, (-v.y) / v.z);
	else
		cam->dir_ort = vect3(1, 0, 0);
	cam->dir_ort = normalize(&cam->dir_ort);
	v = ft_cross(&cam->dir, &cam->dir_ort);
	v = normalize(&v);
	cam->u1 = multiply_vector((cam->v_w / (double)W_WIDTH), &v);
	v = ft_cross(&cam->dir, &cam->u1);
	v = normalize(&v);
	cam->u2 = multiply_vector((cam->v_h / (double)W_HEIGHT), &v);
	v = multiply_vector(((double)W_WIDTH / -2), &cam->u1);
	u = multiply_vector(((double)W_HEIGHT) / -2, &cam->u2);
	cam->r_init = add_vector(&v , &u);
}

/*
 * Build a camera with certains characteristic
 * origin, direction vector, fov angle, n near clipping plane distance
 * build also the two vector discribing the viewport plane
 * far_clp_plane by default 300
*/
t_cam *build_camera(t_point origin, t_vector dir, double fov, double n)
{
	t_cam	*cam;
	double	aspect_ratio;

	aspect_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		cam->aspect_ratio = aspect_ratio;
		cam->origin = origin;
		cam->dir = normalize(&dir);
		if (fov == 180.0f)
			cam->fov = 179.99f;
		else
			cam->fov = fov;
		if (n <= 0)
			n = 1.0f;
		cam->near_clp_plane = n;
		cam->far_clp_plane = 3000;
		cam->v_h = 2 * (cam->near_clp_plane) * tan((cam->fov * M_PI / 180) / 2);
		cam->v_w = aspect_ratio * cam->v_h;
		build_camera_viewport_vectors(cam);
	}
	return (cam);
}


// destroy hittable, lights and cameras on the scene
void free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_free_d_array(scene->hittable);
		ft_free_d_array(scene->lights);
		ft_free_d_array(scene->cameras);
		free(scene);
	}
}
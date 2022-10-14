/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:33:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static inline void	build_camera_viewport_vectors(t_cam *cam)
{
	t_v3	x;
	t_v3	y;

	cam->dir_ort = v3(0, 1, 0);
	x = normalize(ft_cross(cam->dir, cam->dir_ort));
	cam->u1 = v3_multi((cam->v_w / (double)W_WIDTH), x);
	y = normalize(ft_cross(cam->dir, cam->u1));
	cam->u2 = v3_multi((cam->v_h / (double)W_HEIGHT), y);
	x = v3_multi(((double)W_WIDTH / -2), cam->u1);
	y = v3_multi(((double)W_HEIGHT) / -2, cam->u2);
	cam->r_init = v3_add(x , y);
}

/*
 * Build a camera with certains characteristic
 * origin, direction vector, fov angle
 * build also the two vector describing the viewport plane
 * far_clp_plane by default 300
*/
t_cam	*build_camera(t_point origin, t_v3 dir, double fov)
{
	t_cam	*cam;
	double	aspect_ratio;

	aspect_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		cam->aspect_ratio = aspect_ratio;
		cam->origin = origin;
		cam->dir = normalize(dir);
		if (fov == 180.0f)
			cam->fov = 179.99f;
		else
			cam->fov = fov;
		cam->near_clp_plane = 1.0f;
		cam->far_clp_plane = 3000;
		cam->v_h = 2 * (cam->near_clp_plane) * tan((cam->fov * M_PI / 180) / 2);
		cam->v_w = aspect_ratio * cam->v_h;
		build_camera_viewport_vectors(cam);
	}
	return (cam);
}

bool	move_camera(t_cam *cam, t_v3 translate, t_v3 angles, bool only_v)
{
	t_m4	transform;
	t_v4	o;
	t_v4	dir;
	t_v4	oo;

	if (cam)
	{
		transform = get_tr_matrix(translate, angles, v3(1,1,1), false);
		if (!only_v)
		{
			o = multiply_m4_v4(transform, v3_to_v4(cam->origin));
			cam->origin = v3(o.r,o.g,o.b);
		}
		oo	= multiply_m4_v4(transform, v4(0,0,0,0));
		dir = multiply_m4_v4(transform, v3_to_v4(cam->dir));
		dir = v4_sub(dir, oo);
		cam->dir =  normalize(v3(dir.r,dir.g,dir.b));
		build_camera_viewport_vectors(cam);
		return (true);
	}
	return (false);
}



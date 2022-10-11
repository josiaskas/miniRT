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
	t_v3	v;

	v = cam->dir;
	if (cam->dir.x != 0)
		cam->dir_ort = normalize(v3(((-v.y) / v.x), 1, 0));
	else if (cam->dir.z != 0)
		cam->dir_ort = normalize(v3(0, 1, (-v.y) / v.z));
	else
		cam->dir_ort = v3(1, 0, 0);
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
 * origin, direction vector, fov angle, n near clipping plane distance
 * build also the two vector discribing the viewport plane
 * far_clp_plane by default 300
*/
t_cam	*build_camera(t_point origin, t_v3 dir, double fov, double n)
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





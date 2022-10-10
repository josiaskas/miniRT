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

inline bool	rotate_camera(t_cam *cam, t_rotation_type type, double angle)
{
	bool	status;
//	t_v4	dir;

	status = false;
//	if (cam)
//	{
//		if (type == e_rot_on_x)
//			dir = rotation_x(angle, v3_to_v4(cam->dir));
//		else if (type == e_rot_on_y)
//			dir = rotation_y(angle, v3_to_v4(cam->dir));
//		else
//			dir = rotation_z(angle, v3_to_v4(cam->dir));
//		cam->dir  = normalize(v3(dir.r, dir.g, dir.b));
//		build_camera_viewport_vectors(cam);
//		status = true;
//	}
	(void)cam;
	(void)type;
	(void)angle;
	return (status);
}

inline bool	translate_camera(t_cam *cam, t_v3 destination)
{
	bool	status;
	//t_v4	dir;

	status = false;
//	if (cam)
//	{
//		dir = translate_m(v3_to_v4(destination), v3_to_v4(cam->dir));
//		cam->dir  = normalize(v3(dir.r, dir.g, dir.b));
//		build_camera_viewport_vectors(cam);
//		status = true;
//	}
	(void)cam;
	(void)destination;
	return (status);
}




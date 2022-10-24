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
	v = ft_cross(cam->dir, cam->dir_ort);
	cam->dir_ort = ft_cross(v, cam->dir);
	x = normalize(ft_cross(cam->dir, cam->dir_ort));
	cam->u1 = v3_multi((cam->v_w / (double)W_WIDTH), x);
	y = normalize(ft_cross(cam->dir, cam->u1));
	cam->u2 = v3_multi((cam->v_h / (double)W_HEIGHT), y);
	x = v3_multi(((double)W_WIDTH / -2), cam->u1);
	y = v3_multi(((double)W_HEIGHT) / -2, cam->u2);
	cam->r_init = v3_add(x , y);
}
*/

/*
 * Build a camera with certains characteristic
 * origin, direction vector, fov angle
 * build also the two vector describing the viewport plane
 * far_clp_plane by default 300
*/
/*
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
*/

/*
bool	move_camera(t_cam *cam, t_v3 translate, t_v3 angles)
{
	t_m4	transform;
	t_v4	o;
	t_v4	dir;
	t_v4	oo;

	if (cam)
	{
		transform = get_tr_matrix(translate, angles, v3(1,1,1), false);
		o = multiply_m4_v4(transform, v3_to_v4(cam->origin));
		cam->origin = v3(o.r,o.g,o.b);
		oo	= multiply_m4_v4(transform, v4(0,0,0,0));
		dir = multiply_m4_v4(transform, v3_to_v4(cam->dir));
		dir = v4_sub(dir, oo);
		cam->dir =  normalize(v3(dir.r,dir.g,dir.b));
		build_camera_viewport_vectors(cam);
		return (true);
	}
	return (false);
}
*/

/*
void test_inverse(void)
{
	t_m4 tr;
	tr.data[0][0] = -5;
	tr.data[0][1] = 2;
	tr.data[0][2] = 6;
	tr.data[0][3] = -8;
	tr.data[1][0] = 1;
	tr.data[1][1] = -5;
	tr.data[1][2] = 1;
	tr.data[1][3] = 8;
	tr.data[2][0] = 7;
	tr.data[2][1] = 7;
	tr.data[2][2] = -6;
	tr.data[2][3] = -7;
	tr.data[3][0] = 1;
	tr.data[3][1] = -3;
	tr.data[3][2] = 7;
	tr.data[3][3] = 4;
	printf("[%lf, %lf, %lf, %lf]\n", tr.data[0][0],tr.data[0][1],tr.data[0][2],tr.data[0][3]);
	printf("[%lf, %lf, %lf, %lf]\n", tr.data[1][0],tr.data[1][1],tr.data[1][2],tr.data[1][3]);
	printf("[%lf, %lf, %lf, %lf]\n", tr.data[2][0],tr.data[2][1],tr.data[2][2],tr.data[2][3]);
	printf("[%lf, %lf, %lf, %lf]\n", tr.data[3][0],tr.data[3][1],tr.data[3][2],tr.data[3][3]);
	t_m4 *inv = get_inverse(tr);
	if (inv)
	{
		printf("inverse\n[%lf, %lf, %lf, %lf]\n", inv->data[0][0],inv->data[0][1],inv->data[0][2],inv->data[0][3]);
		printf("[%lf, %lf, %lf, %lf]\n", inv->data[1][0],inv->data[1][1],inv->data[1][2],inv->data[1][3]);
		printf("[%lf, %lf, %lf, %lf]\n", inv->data[2][0],inv->data[2][1],inv->data[2][2],inv->data[2][3]);
		printf("[%lf, %lf, %lf, %lf]\n", inv->data[3][0],inv->data[3][1],inv->data[3][2],inv->data[3][3]);
	}
	free(inv);
}
*/


inline t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up)
{
	t_v3	forward;
	t_v3	left;
	t_v3	true_up;
	t_m4	or;

	forward = normalize(v3_sub(to, from));
	up = normalize(up);
	left = ft_cross(forward, up);
	true_up = ft_cross(left, forward);
	or = get_identity_matrix();
	or.data[0][0] = left.x;
	or.data[0][1] = left.y;
	or.data[0][2] = left.z;
	or.data[1][0] = true_up.x;
	or.data[1][1] = true_up.y;
	or.data[1][2] = true_up.z;
	or.data[2][0] = -1 * forward.x;
	or.data[2][1] = -1 * forward.y;
	or.data[2][2] = -1 * forward.z;
	return (m4_multi(or, translate_m(v3_multi(-1, from))));
}

t_cam	*build_cam(double hsize, double vsize, double fov)
{
	double	half_view;
	double	aspect;
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		cam->hsize = hsize;
		cam->vsize = vsize;
		aspect = cam->hsize / cam->vsize;
		if (fov == 180.0f)
			cam->fov = 179.99f;
		else
			cam->fov = fov;
		half_view = tan((cam->fov * M_PI / 180) / 2);
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
		cam->pixel_size = (cam->half_width * 2) / cam->hsize;
		cam->inv_tr = get_identity_matrix();
	}
	return (cam);
}

t_cam	*build_camera(t_point origin, t_v3 dir, double fov)
{
	t_m4	*inv;
	t_m4	tr;
	t_cam	*cam;

	cam = build_cam((double)W_HEIGHT,(double)W_WIDTH, fov);
	if (cam)
	{
		(void)dir;
		tr = view_transform(origin, dir, v3(0,1,0));
		inv = get_inverse(tr);
		cam->inv_tr = copy_matrix(inv);
		free(inv);
	}
	return (cam);
}



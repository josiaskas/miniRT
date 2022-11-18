/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:25:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

/*Get the look_at matrix with a translation away from the world*/
inline t_m4	view_transform(t_v3 from, t_v3 forward, t_v3 up)
{
	t_v3	left;
	t_v3	true_up;
	t_m4	or;

	forward = normalize(forward);
	left = ft_cross(forward, normalize(up));
	true_up = ft_cross(left, forward);
	or = get_identity_matrix();
	or.data[0][0] = left.x;
	or.data[0][1] = left.y;
	or.data[0][2] = left.z;
	or.data[1][0] = true_up.x;
	or.data[1][1] = true_up.y;
	or.data[1][2] = true_up.z;
	or.data[2][0] = -forward.x;
	or.data[2][1] = -forward.y;
	or.data[2][2] = -forward.z;
	return (m4_multi(or, translate_m(v3_multi(-1, from))));
}

inline bool	update_cam(t_cam *cam, double hsize, double vsize, double fov)
{
	double	half_view;

	if (cam)
	{
		cam->aspect = vsize / hsize;
		if (fov >= 180)
			cam->fov = 179.99;
		else if (fov < 1)
			cam->fov = 1;
		else
			cam->fov = fov;
		half_view = tanf((cam->fov * 0.01745329251) / 2);
		cam->hsize = 2 * half_view;
		cam->vsize = cam->aspect * cam->hsize;
		cam->half_height = half_view;
		cam->half_width = half_view * cam->aspect;
		cam->pixel_dx = cam->vsize / vsize;
		cam->pixel_dy = cam->hsize / hsize;
		return (true);
	}
	return (false);
}

t_cam	*build_camera(t_point origin, t_v3 forward, double fov)
{
	t_cam	*cam;
	t_v3	up;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		update_cam(cam, (double)W_HEIGHT, (double)W_WIDTH, fov);
		cam->eye = origin;
		cam->look_at = forward;
		up = (t_v3){0, 1, 0};
		if (forward.x == 0 && (forward.y == 1 || forward.y == -1)
			&& forward.z == 0)
			up = (t_v3){0, 0, 1};
		cam->transform = view_transform(origin, forward, up);
		cam->inv_tr = get_inverse(cam->transform);
		cam->rot_angles = (t_v3){0, 0, 0};
	}
	return (cam);
}

bool	move_camera(t_cam *camera, t_point origin, t_v3 forward)
{
	t_v3	up;
	t_m4	rot;

	camera->eye = origin;
	camera->look_at = forward;
	up = (t_v3){0, 1, 0};
	if (forward.x == 0 && (forward.y == 1 || forward.y == -1)
		&& forward.z == 0)
		up = (t_v3){0, 0, 1};
	camera->transform = view_transform(origin, forward, up);
	rot = get_tr_matrix((t_v3){0, 0, 0}, camera->rot_angles,
			(t_v3){1, 1, 1}, false);
	camera->transform = m4_multi(camera->transform, rot);
	camera->inv_tr = get_inverse(camera->transform);
	return (true);
}

bool	switch_camera(t_scene *scn)
{
	printf("switching camera\n");
	if (scn->cam_cursor < (scn->cameras->length - 1))
	{
		scn->cam_cursor++;
		scn->selected_camera = (t_cam *)ft_get_elem(scn->cameras,
				scn->cam_cursor);
	}
	else if (scn->cameras->length == 1)
		return (true);
	else if (scn->cam_cursor == (scn->cameras->length - 1))
	{
		scn->cam_cursor = 0;
		scn->selected_camera = (t_cam *)ft_get_elem(scn->cameras,
				scn->cam_cursor);
	}
	return (true);
}

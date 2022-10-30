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

/*Get the look_at matrix with a translation away from the world*/
inline t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up)
{
	t_v3	forward;
	t_v3	left;
	t_v3	true_up;
	t_m4	or;

	forward = normalize(v3_sub(to, from));
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

inline bool	update_cam(t_cam *cam, float hsize, float vsize, float fov)
{
	float	half_view;

	if (cam)
	{
		cam->aspect = vsize / hsize;
		if (fov >= 180.0f)
			cam->fov = 179.99f;
		else
			cam->fov = fov;
		half_view = tanf((cam->fov * 0.01745329251) / 2.0);
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

t_cam	*build_camera(t_point origin, t_point look_at, float fov)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		update_cam(cam, (float)W_HEIGHT,(float)W_WIDTH, fov);
		cam->eye = origin;
		cam->look_at = look_at;
		cam->transform = view_transform(origin, look_at, v3(0,1.0f,0));
		cam->inv_tr = get_inverse(cam->transform);
	}
	return (cam);
}

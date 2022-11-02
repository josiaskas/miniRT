/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 19:02:16 by jkasongo         ###   ########.fr       */
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

static void	build_camera_viewport_vectors(t_cam *cam, t_v3 forward)
{
	t_v3	left;
	t_v3	true_up;
	t_v3	v;

	forward = normalize(forward);
	left = normalize(ft_cross(forward, v3(0.0f, 1.0f, 0.0f)));
	true_up = normalize(ft_cross(left, forward));
	cam->u1 = normalize(ft_cross(forward, true_up));
	cam->u1 = v3_multi((cam->vsize / cam->pixel_x), cam->u1);
	cam->u2 = normalize(ft_cross(forward, cam->u1));
	cam->u2 = v3_multi((cam->hsize / cam->pixel_y), cam->u1);
	cam->r_init = v3_multi((-0.5f * cam->pixel_x), cam->u1);
	v = v3_multi((-0.5f * cam->pixel_y), cam->u2);
	cam->r_init = v3_add(cam->r_init, v);
	cam->r_init =  v3_add(cam->r_init, forward);
	cam->r_init =  v3_add(cam->r_init, cam->eye);
}

bool	update_cam(t_cam *cam, float fov, t_point eye, t_v3 dir)
{
	if (cam)
	{
		cam->aspect = (float)W_WIDTH / (float)W_HEIGHT;
		if (fov >= 180.0f)
			fov  = 179.99f;
		cam->fov = fov * (M_PI / 180.0f);
		cam->hsize = 2.0f * tanf(cam->fov / 2.0f);
		cam->vsize = cam->aspect * cam->hsize;
		cam->pixel_x = (float)W_WIDTH;
		cam->pixel_y = (float)W_HEIGHT;
		cam->eye = eye;
		build_camera_viewport_vectors(cam, dir);
		return (true);
	}
	return (false);
}

t_cam	*build_camera(t_point origin, t_v3 dir, float fov)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		update_cam(cam, fov, origin, dir);
		cam->transform = get_identity_matrix();
		cam->inv_tr = get_identity_matrix();
	}
	return (cam);
}

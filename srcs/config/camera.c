/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:49:41 by jkasongo          #+#    #+#             */
/*   Updated: 2022/12/13 12:01:29 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static inline void	rotate_in_x_y(int key, double step, t_cam *cam)
{
	if (key == ARROW_UP)
		cam->transform = m4_multi(cam->transform, rotation_x(step));
	else if (key == ARROW_DOWN)
		cam->transform = m4_multi(cam->transform, rotation_x(-step));
	else if (key == ARROW_LEFT)
		cam->transform = m4_multi(cam->transform, rotation_y(step));
	else if (key == ARROW_RIGHT)
		cam->transform = m4_multi(cam->transform, rotation_y(-step));
}

static inline void	rotate_in_x_z(int key, double step, t_cam *cam)
{
	if (key == ARROW_UP)
		cam->transform = m4_multi(cam->transform, rotation_x(step));
	else if (key == ARROW_DOWN)
		cam->transform = m4_multi(cam->transform, rotation_x(-step));
	else if (key == ARROW_LEFT)
		cam->transform = m4_multi(cam->transform, rotation_z(step));
	else if (key == ARROW_RIGHT)
		cam->transform = m4_multi(cam->transform, rotation_z(-step));
}

static inline void	rotate_in_z_y(int key, double step, t_cam *cam)
{
	if (key == ARROW_UP)
		cam->transform = m4_multi(cam->transform, rotation_z(step));
	else if (key == ARROW_DOWN)
		cam->transform = m4_multi(cam->transform, rotation_z(-step));
	else if (key == ARROW_LEFT)
		cam->transform = m4_multi(cam->transform, rotation_y(step));
	else if (key == ARROW_RIGHT)
		cam->transform = m4_multi(cam->transform, rotation_y(-step));
}

inline void	do_camera_rotation(int key, t_app *app)
{
	t_cam	*cam;

	cam = app->scene->selected_camera;
	if (app->conf.c_mode == e_normal_mode)
		rotate_in_x_y(key, 0.0349066, cam);
	else if (app->conf.c_mode == e_x_z_mode)
		rotate_in_x_z(key, 0.0349066, cam);
	else if (app->conf.c_mode == e_z_y_mode)
		rotate_in_z_y(key, 0.0349066, cam);
	cam->inv_tr = get_inverse(cam->transform);
	app->conf.rerender = true;
}

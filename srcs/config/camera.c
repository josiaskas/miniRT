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
	t_v4	forward;

	forward = (t_v4){cam->look_at.x, cam->look_at.y, cam->look_at.z, 1};
	if (key == ARROW_UP)
		forward = multiply_m4_v4(rotation_x(-step), forward);
	else if (key == ARROW_DOWN)
		forward = multiply_m4_v4(rotation_x(step), forward);
	else if (key == ARROW_LEFT)
		forward = multiply_m4_v4(rotation_y(-step), forward);
	else if (key == ARROW_RIGHT)
		forward = multiply_m4_v4(rotation_y(step), forward);
	move_camera(cam, cam->eye, (t_v3){forward.r, forward.g, forward.b});
}

static inline void	rotate_in_x_z(int key, double step, t_cam *cam)
{
	t_v4	forward;

	forward = (t_v4){cam->look_at.x, cam->look_at.y, cam->look_at.z, 1};
	if (key == ARROW_UP)
		forward = multiply_m4_v4(rotation_x(-step), forward);
	else if (key == ARROW_DOWN)
		forward = multiply_m4_v4(rotation_x(step), forward);
	else if (key == ARROW_LEFT)
		forward = multiply_m4_v4(rotation_z(-step), forward);
	else if (key == ARROW_RIGHT)
		forward = multiply_m4_v4(rotation_z(step), forward);
	move_camera(cam, cam->eye, (t_v3){forward.r, forward.g, forward.b});
}

static inline void	rotate_in_z_y(int key, double step, t_cam *cam)
{
	t_v4	forward;

	forward = (t_v4){cam->look_at.x, cam->look_at.y, cam->look_at.z, 1};
	if (key == ARROW_UP)
		forward = multiply_m4_v4(rotation_z(-step), forward);
	else if (key == ARROW_DOWN)
		forward = multiply_m4_v4(rotation_z(step), forward);
	else if (key == ARROW_LEFT)
		forward = multiply_m4_v4(rotation_y(-step), forward);
	else if (key == ARROW_RIGHT)
		forward = multiply_m4_v4(rotation_y(step), forward);
	move_camera(cam, cam->eye, (t_v3){forward.r, forward.g, forward.b});
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
	app->conf.rerender = true;
	render_image(app);
}

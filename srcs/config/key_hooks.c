/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/22 16:43:31 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static int	prepare_camera_move(int key, t_app *app)
{
	t_cam	*cam;
	t_v3	new_origin;
	double	dx;
	double	dy;

	cam = app->scene->selected_camera;
	if (cam && (app->conf.c_mode == e_normal_mode))
	{
		dx = cam->pixel_dx * 100;
		dy = cam->pixel_dy * 100;
		new_origin = cam->eye;
		if (key == ARROW_UP)
			new_origin.x += dx;
		else if (key == ARROW_DOWN)
			new_origin.x -= dx;
		else if (key == ARROW_LEFT)
			new_origin.y += dy;
		else
			new_origin.y -= dy;
		move_camera(cam, new_origin, cam->look_at);
		render(app);
		app->conf.rerender = true;
	}
	return (0);
}

void	make_camera_rotate(int key, t_app *app)
{
	t_cam	*cam;
	double	step;

	cam = app->scene->selected_camera;
	step = 5 * (M_PI / 180);
	if (key == MAIN_PAD_X)
		cam->transform = m4_multi(cam->transform, rotation_x(step));
	else if (key == MAIN_PAD_Y)
		cam->transform = m4_multi(cam->transform, rotation_z(step));
	else if (key == MAIN_PAD_Z)
		cam->transform = m4_multi(cam->transform, rotation_y(step));
	cam->inv_tr = get_inverse(cam->transform);
	render(app);
	app->conf.rerender = true;
}

int	key_pressed_hook(int key, t_app *app)
{
	if ((key == MAIN_PAD_ESC) || (key == MAIN_PAD_Q))
		close_window(app);
	else if ((key == ARROW_UP) || (key == ARROW_DOWN)
		|| (key == ARROW_LEFT) || (key == ARROW_RIGHT))
		prepare_camera_move(key, app);
	else if ((key == MAIN_PAD_X) || (key == MAIN_PAD_Y)
			 || (key == MAIN_PAD_Z))
		make_camera_rotate(key, app);
	else if (key == MAIN_PAD_I)
	{
		app->conf.c_mode = e_select_mode;
		app->conf.rerender = true;
	}
	return (0);
}

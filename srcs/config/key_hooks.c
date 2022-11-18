/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:22:33 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static int	move_camera_eye(int key, t_app *app)
{
	t_cam	*cam;
	t_v3	new_origin;
	double	dy;

	cam = app->scene->selected_camera;
	if (cam && (app->conf.c_mode == e_normal_mode))
	{
		dy = cam->pixel_dy * 100;
		new_origin = cam->eye;
		if (key == ARROW_UP)
			new_origin.x += dy;
		else if (key == ARROW_DOWN)
			new_origin.x -= dy;
		else if (key == ARROW_LEFT)
			new_origin.y += dy;
		else
			new_origin.y -= dy;
		printf("new cam origin: (%lf, %lf, %lf)\n",
			new_origin.x, new_origin.y, new_origin.z);
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
	step = 0.0872665;
	if (app->conf.c_mode == e_clock_wise_mode)
		step = -0.0872665;
	if (key == MAIN_PAD_X)
	{
		cam->rot_angles.x += step;
		cam->transform = m4_multi(cam->transform, rotation_x(step));
	}
	else if (key == MAIN_PAD_Y)
	{
		cam->rot_angles.z += step;
		cam->transform = m4_multi(cam->transform, rotation_z(step));
	}
	else if (key == MAIN_PAD_Z)
	{
		cam->rot_angles.y += step;
		cam->transform = m4_multi(cam->transform, rotation_y(step));
	}
	cam->inv_tr = get_inverse(cam->transform);
	render(app);
	app->conf.rerender = true;
}

void	select_new_camera(t_app *app)
{
	switch_camera(app->scene);
	render(app);
	app->conf.rerender = true;
}

void	start_light_edition(int key, t_app *app)
{
	t_light	*selected;
	size_t	i;

	i = 42;
	if (key == MAIN_PAD_1)
		i = 1;
	else if (key == MAIN_PAD_2)
		i = 2;
	else if (key == MAIN_PAD_3)
		i = 3;
	else if (key == MAIN_PAD_4)
		i = 4;
	else if (key == MAIN_PAD_5)
		i = 5;
	if (i <= app->scene->lights->length)
	{
		selected = ft_get_elem(app->scene->lights, i - 1);
		if (selected)
		{
			light_edition(selected, i);
			render(app);
			app->conf.rerender = true;
		}
	}
}

int	key_pressed_hook(int key, t_app *app)
{
	if ((key == MAIN_PAD_ESC) || (key == MAIN_PAD_Q))
		close_window(app);
	else if ((key == ARROW_UP) || (key == ARROW_DOWN)
		|| (key == ARROW_LEFT) || (key == ARROW_RIGHT))
		move_camera_eye(key, app);
	else if ((key == MAIN_PAD_X) || (key == MAIN_PAD_Y) || (key == MAIN_PAD_Z))
		make_camera_rotate(key, app);
	else if ((key == MAIN_PAD_1) || (key == MAIN_PAD_2) || (key == MAIN_PAD_3)
		|| (key == MAIN_PAD_4) || (key == MAIN_PAD_5))
		start_light_edition(key, app);
	else if (key == MAIN_PAD_C)
		select_new_camera(app);
	else if (key == MAIN_PAD_I || key == MAIN_PAD_V)
	{
		if (key == MAIN_PAD_I)
			app->conf.c_mode = e_select_mode;
		else if (app->conf.c_mode != e_clock_wise_mode)
			app->conf.c_mode = e_clock_wise_mode;
		else
			app->conf.c_mode = e_normal_mode;
		app->conf.rerender = true;
	}
	return (0);
}

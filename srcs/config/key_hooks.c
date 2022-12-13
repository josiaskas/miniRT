/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 15:23:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

void	select_new_camera(t_app *app)
{
	switch_camera(app->scene);
	render(app);
	app->conf.rerender = true;
}

void	moving_object_position(int key, t_app *app)
{
	(void)key;
	(void)app;
}

void	select_plan_mode(t_app *app)
{
	static int	plan_mode = 0;
	int			left;

	plan_mode++;
	left = plan_mode % 3;
	if (left == 0)
		app->conf.c_mode = e_normal_mode;
	else if (left == 1)
		app->conf.c_mode = e_x_z_mode;
	else
		app->conf.c_mode = e_z_y_mode;
	app->conf.rerender = true;
}

int	key_pressed_hook(int key, t_app *app)
{
	if ((key == MAIN_PAD_ESC) || (key == MAIN_PAD_Q))
		close_window(app);
	else if (key == MAIN_PAD_C)
		select_new_camera(app);
	else if (key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT)
		do_camera_rotation(key, app);
	else if (key == MAIN_PAD_I)
	{
		app->conf.c_mode = e_select_mode;
		app->conf.rerender = true;
	}
	else if (key == MAIN_PAD_V)
		select_plan_mode(app);
	return (0);
}

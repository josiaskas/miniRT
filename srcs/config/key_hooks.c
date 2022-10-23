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

static inline int	prepare_camera_move(int key, t_app *app)
{
	t_cam	*cam;
	double	step;
	t_v3	move;

	cam = app->scene->selected_camera;
	if (cam && (app->conf.c_mode == e_normal_mode))
	{
		step = 5 * (M_PI / 180);
		(void)step;
		(void)move;
		(void)key;
		render(app);
		app->conf.rerender = true;
	}
	return (0);
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		close_window(app);
	else if ((key == ARROW_UP) || (key == ARROW_DOWN)
		|| (key == ARROW_LEFT) || (key == ARROW_RIGHT))
		prepare_camera_move(key, app);
	else if (key == MAIN_PAD_C)
		app->conf.c_mode = e_select_mode;
	return (0);
}

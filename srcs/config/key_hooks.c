/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/24 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static inline int prepare_camera_move(int key, t_app *app)
{
	t_cam	*cam;
	double	step;
	t_v3	move;

	cam = app->scene->selected_camera;
	if (cam)
	{
		step = 10 * M_PI / 180;
		if (key == ARROW_LEFT)
			move = v3(0,step, 0);
		else if (key == ARROW_RIGHT)
			move = v3(0,(-1.0 * step), 0);
		else if (key == ARROW_DOWN)
			move = v3(step,0, 0);
		else
			move = v3( (-1.0 * step),0, 0);

		move_camera(cam, v3(0,0,0), move, true);
		render(app);
		app->re_render = true;
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
	return (0);
}

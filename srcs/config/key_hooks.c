/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 20:59:44 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

static inline void	select_new_camera(t_app *app)
{
	switch_camera(app->scene);
	render(app);
	app->conf.rerender = true;
	render_image(app);
}

int	key_pressed_hook(int key, t_app *app)
{
	if ((key == MAIN_PAD_ESC) || (key == MAIN_PAD_Q))
		close_window(app);
	else if (key == MAIN_PAD_C)
		select_new_camera(app);
	else if (key == MAIN_PAD_A || key == MAIN_PAD_D || key == MAIN_PAD_S || key == MAIN_PAD_W)
		do_camera_rotation(key, app);
	else if (key == MAIN_PAD_I)
	{
		if (app->conf.c_mode == e_select_mode)
		{
			app->conf.c_mode = e_normal_mode;
			app->conf.selected_obj = NULL;
		}
		else
			app->conf.c_mode = e_select_mode;
		app->conf.rerender = true;
		render_image(app);
	}
	return (key_pressed_hook_suite(key, app));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:48:51 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	ft_zoom_hook(int button, t_app *app)
{
//	t_cam	*cam;
//	double	fov;
//
//	cam = app->scene->selected_camera;
//	if (button == MOUSE_SCROLL_UP)
//		fov = cam->fov - 5;
//	else
//		fov = cam->fov + 5;
//	if (fov >= 1 && fov <= 180)
//	{
//		update_cam(cam, (double)W_HEIGHT, (double)W_WIDTH, fov);
//		render(app);
//	}
//	app->conf.rerender = true;
	(void)button;
	(void)app;
}


int	mouse_pressed(int button, int x, int y, t_app *app)
{
	if (!app->mouse->b_pressed)
	{
		app->mouse->b_pressed = true;
		app->mouse->start_x = x;
		app->mouse->start_y = y;
	}
	if ((button == MOUSE_LEFT_BUTTON) && (app->conf.c_mode == e_select_mode))
		start_selecting_mode(app, x, y);
	else if ((button == MOUSE_SCROLL_UP) || (button == MOUSE_SCROLL_DOWN))
		ft_zoom_hook(button, app);
	return (0);
}

int	mouse_release(int button, int x, int y, t_app *app)
{
	app->mouse->x = x;
	app->mouse->y = y;
	if (button == MOUSE_LEFT_BUTTON)
		app->mouse->b_pressed = false;
	return (0);
}

int	mouse_moved(int x, int y, t_app *app)
{
	t_mouse	*mouse;

	mouse = app->mouse;
	if (mouse->b_pressed)
	{
		app->mouse->x = x;
		app->mouse->y = y;
	}
	return (0);
}

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
#include "minirt.h"
#include "raytrace.h"

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
	else if (app->mouse->b_pressed && ((button == MOUSE_SCROLL_DOWN || button == MOUSE_SCROLL_UP)))
		ft_zoom_hook(button, app);
	return (0);
}

int	mouse_release(int button, int x, int y, t_app *app)
{
	app->mouse->x = x;
	app->mouse->y = y;
	if (button == MOUSE_LEFT_BUTTON)
		app->mouse->b_pressed = false;
//	else if (button == MOUSE_SCROLL_DOWN || button == MOUSE_SCROLL_UP)
//		ft_zoom_hook(button, app);
	return (0);
}

int	mouse_moved(int x, int y, t_app *app)
{
	t_mouse	*mouse;

	mouse = app->mouse;
	if (mouse->b_pressed)
	{
		if ((x != app->mouse->x) || (y != app->mouse->y))
		{
			app->mouse->x = x;
			app->mouse->y = y;
		}
	}
	return (0);
}

int	ft_zoom_hook(int button, t_app *app)
{
//	double	fov;
//	double	delta;
//	t_cam	*cam;
//
//	cam = app->scene->selected_camera;
//	fov = cam->fov;
//	delta = app->mouse->start_y - app->mouse->y;
//	if (button == MOUSE_SCROLL_UP){
//		fov +=delta;
//		printf("in up with delta: %lf and fov: %lf\n", delta, fov);
//		app->conf.rerender = true;
//	}
//	else if (button == MOUSE_SCROLL_DOWN){
//		fov -=delta;
//		printf("down with delta: %lf and fov: %lf\n", delta, fov);
//		app->conf.rerender = true;
//	}
	(void)button;
	(void)app;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/24 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "minirt.h"
#include "raytrace.h"

int	mouse_pressed(int button, int x, int y, t_app *app)
{
	if (button == MOUSE_LEFT_BUTTON)
	{
		app->mouse->b_pressed = true;
		app->mouse->start_x = x;
		app->mouse->start_y = y;

	}
	return(0);
}

int	mouse_release(int button, int x, int y, t_app *app)
{
	if (button == MOUSE_LEFT_BUTTON)
	{
		app->mouse->b_pressed = false;
		app->mouse->x = x;
		app->mouse->y = y;

	}
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
			if (app->mouse->b_pressed)
			{

			}
		}
	}
	return (0);
}


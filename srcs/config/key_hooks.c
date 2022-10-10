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
#include <stdio.h>

static int	rotate_camera_hook(t_app *app)
{
	t_scene	*scene;
	t_cam	*cam;

	scene = app->scene;
	cam = scene->selected_camera;
	rotate_camera(cam, e_rot_on_z, (90 * M_PI / 180));
	return (0);
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		close_window(app);
	else if (key == MAIN_PAD_R)
		return (rotate_camera_hook(app));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/29 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

int	write_info_section(t_app *app, void *mlx, void *win)
{
	int		y;
	int		x;

	y = 400;
	x = 1100;
	mlx = app->mlx;
	win = app->window;
	mlx_string_put(mlx, win, x, y += 20, BLUE_LIGHT2, app->file_name);
	if (app->conf.c_mode == e_normal_mode)
		mlx_string_put(mlx, win, (x + 15), y += 30, BLUE_LIGHT, "Normal Mode");
	else if (app->conf.c_mode == e_select_mode)
		mlx_string_put(mlx, win, (x + 15), y += 30, RED_L, "Edition Mode");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:35 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 15:00:37 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define WHITE 0xFFFFFF
# define RED_L 0xE63946
# define BLUE_LIGHT 0xA8DADC
# define BLUE_LIGHT2 0x457B9D
# define BLUE_NAVY 0x1D3557

# define TEXT_COLOR 0xF1FAEE

# include "minirt.h"
# include "hooks_key.h"
# include "raytrace.h"

int		write_info_section(t_app *app, void *mlx, void *win);
int		mouse_pressed(int button, int x, int y, t_app *app);
int		mouse_release(int button, int x, int y, t_app *app);
int		mouse_moved(int x, int y, t_app *app);

void	start_selecting_mode(t_app *app, int x, int y);
int		key_pressed_hook(int key, t_app *app);
void	get_line_vector(char *title, t_v3 *v);
void	get_line_color(t_color *color);
void	get_line_double(char *title, double *val);

#endif

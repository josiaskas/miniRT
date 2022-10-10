/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "minirt.h"
# include "hooks_key.h"
# include "raytrace.h"

int	mouse_pressed(int button, int x, int y, t_app *app);
int	mouse_release(int button, int x, int y, t_app *app);
int	mouse_moved(int x, int y, t_app *app);

int	key_pressed_hook(int key, t_app *app);
#endif //WINDOW_H

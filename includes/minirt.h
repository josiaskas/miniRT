/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "hooks_key.h"
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# define W_HEIGHT 768
# define W_WIDTH 1366

typedef struct s_mouse
{
	int		start_x; //if pressed set by the beginning of pressing
	int		start_y;
	int		x;
	int		y;
	bool	b_pressed;
}	t_mouse;

typedef struct s_image {
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_app
{
	void	*mlx;
	void	*window;
	t_image *img;
	char	*file_name;
	char	*error_message;
	int		error_code;
	int		fd;
	t_mouse	*mouse;
}	t_app;

void	exit_app(t_app *app, bool error);
bool	init_window(t_app *app);
void	app_loop(t_app *app);
void	ft_print_error(char *error_message, int code);
bool	do_raytracing(t_app *app);
#endif

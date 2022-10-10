/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "hooks_key.h"
# include "raytrace.h"
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

# ifndef IS_BONUS
#  define IS_BONUS 0
# endif

typedef struct s_mouse
{
	int			start_x;
	int			start_y;
	int			x;
	int			y;
	bool		b_pressed;
	t_hittable	*selected_object;
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
	void		*mlx;
	void		*window;
	t_image		*img;
	char		*file_name;
	char		*error_message;
	int			error_code;
	int			in_fd;
	int			out_fd;
	t_color		**data;
	t_mouse		*mouse;
	t_scene		*scene;
}	t_app;

int		write_image_to_file(t_app *app);
void	ft_print_error(char *error_message, int code);
int		open_rt_file(char *filename, t_app *app);
int		open_out_file(char *file, t_app *app);
bool	parse_rt_file(t_app *app);
void	exit_app(t_app *app, bool error);

bool	init_window(t_app *app);
int		close_window(t_app *app);
void	app_loop(t_app *app);
bool	render(t_app *app);
int		rerender(t_app *app);
#endif

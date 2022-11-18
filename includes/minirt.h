/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:02 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:47:18 by jkasongo         ###   ########.fr       */
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

typedef enum e_app_mode
{
	e_normal_mode,
	e_select_mode,
	e_rotation_mode,
}	t_mode;

typedef struct config_status
{
	t_mode		c_mode;
	t_hittable	*selected_obj;
	int			status;
	char		*message;
	bool		rerender;
}	t_config;

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
	t_config	conf;
}	t_app;

int		write_image_to_file(t_app *app);
void	ft_print_error(char *error_message, int code);
int		open_rt_file(char *filename, t_app *app);
int		open_out_file(char *file, t_app *app);
bool	parse_rt_file(t_app *app);
void	exit_app(t_app *app, bool error);
void	draw_scene(t_image *img, t_color **colors);
bool	init_window(t_app *app);
int		close_window(t_app *app);
void	app_loop(t_app *app);
bool	render(t_app *app);
int		rerender(t_app *app);
#endif

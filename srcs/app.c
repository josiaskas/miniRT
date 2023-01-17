/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 14:20:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "window.h"

int	watcher(t_app *app)
{
	void	*mlx;
	void	*win;
	t_image	*img;

	mlx = app->mlx;
	win = app->window;
	img = app->img;
	if (app->conf.rerender)
	{
		mlx_put_image_to_window(mlx, win, img->img, 0, 0);
		render(app);
		write_info_section(app, mlx, win);
		app->conf.rerender = false;
	}
	return (0);
}

// loop and call hooks function on event
void	app_loop(t_app *app)
{
	t_image	*img;

	img = app->img;
	mlx_put_image_to_window(app->mlx, app->window, img->img, 0, 0);
	mlx_hook(app->window, 4, 1L << 2, mouse_pressed, app);
	mlx_hook(app->window, 5, 1L << 3, mouse_release, app);
	mlx_loop_hook(app->mlx, watcher, app);
	mlx_hook(app->window, 2, 1L << 0, key_pressed_hook, app);
	mlx_hook(app->window, 17, 0, close_window, app);
	mlx_loop(app->mlx);
}

bool	init_window(t_app *app)
{
	t_image	*img;

	app->error_code = 3;
	app->error_message = "Failed to init mlx";
	app->mlx = mlx_init();
	if (!app->mlx)
		return (false);
	app->window = mlx_new_window(app->mlx, W_WIDTH, W_HEIGHT, app->file_name);
	if (!app->window)
		return (false);
	app->img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!app->img)
		return (false);
	img = app->img;
	img->img = mlx_new_image(app->mlx, W_WIDTH, W_HEIGHT);
	img->data = mlx_get_data_addr(img->img,
			&(img->bits_per_pixel), &(img->line_length), &(img->endian));
	app->mouse = (t_mouse *)ft_calloc(1, sizeof(t_mouse));
	if (!img->img || !img->data)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 19:07:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static	void	run_app(bool render_in_a_window, t_app *app)
{
	if (!render_in_a_window)
	{
		if (!render(app))
			exit_app(app, true);
		write_image_to_file(app);
	}
	else
	{
		app->conf.rerender = true;
		if (!init_window(app))
			exit_app(app, true);
		if (render_image(app))
			exit_app(app, true);
		app_loop(app);
	}
	exit_app(app, false);
}

int	close_window(t_app *app)
{
	if (app->error_code > 3)
		exit_app(app, true);
	else
		exit_app(app, false);
	return (0);
}

/*
 * Try to initialise the app with the filename given
 * Parse the file given
 * Init Mlx config or write inside a file
 */
static void	init_app(char *filename, char *outFile)
{
	t_app	*app;
	bool	in_window;

	app = (t_app *)ft_calloc(1, sizeof(t_app));
	if (open_rt_file(filename, app) != 0)
		exit_app(app, true);
	in_window = true;
	if (outFile)
	{
		if (open_out_file(outFile, app) != 0)
			exit_app(app, true);
		in_window = false;
	}
	if (!parse_rt_file(app))
		exit_app(app, true);
	run_app(in_window, app);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		init_app(argv[1], NULL);
	else if (argc == 3 && IS_BONUS)
		init_app(argv[1], argv[2]);
	else
		ft_putendl_fd("Usage: miniRT *.rt", STDOUT_FILENO);
	return (0);
}

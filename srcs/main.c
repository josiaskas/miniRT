/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void run_app(bool render_in_a_window, t_app *app)
{
	if (!do_raytracing(app))
		exit_app(app, true);
	if (!render_in_a_window)
		write_image_to_file(app);
	else
	{
		if (!init_window(app))
			exit_app(app, true);
		ft_putendl_fd("Init window", STDOUT_FILENO);
		app_loop(app);
	}
	exit_app(app, false);
}

/*
 * Try to initialise the app with the filename given
 * Parse the file given
 * Init Mlx window or write inside a file
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

int main(int argc, char *argv[])
{
	if (argc == 2)
		init_app(argv[1], NULL);
	else if (argc == 3)
		init_app(argv[1], argv[2]);
	else
		ft_putendl_fd("Usage: miniRT *.rt", STDOUT_FILENO);
	return (0);
}
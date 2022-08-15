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

void	exit_app(t_app *app, bool error)
{
	if (!app)
		exit(-1);
	if (error)
		ft_print_error(app->error_message, app->error_code);
	if (app->img)
		free(app->img);
	if (app->mouse)
		free(app->mouse);
	if (app->fd != 0)
		close(app->fd);
	free(app);
	if (error)
		exit(-1);
	else
		exit(0);
}

// open a file with the correct extension
static int open_file(char *filename, t_app *app)
{
	int		fd;
	char	*extension;

	extension = ft_strnstr(filename, ".rt", ft_strlen(filename));
	if (!extension)
	{

		app->error_message = "miniRT need a file format like *.rt";
		app->error_code = 1;
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		app->error_message = strerror(errno);
		app->error_code = 2;
		return (-1);
	}
	app->file_name = filename;
	app->fd = fd;
	return (0);
}

/*
 * Try to initialise the app with the filename given
 * Parse the file given
 * Init Mlx window and start the loop
 */
static void	init_app(char *filename)
{
	t_app	*app;

	app = (t_app *)ft_calloc(1, sizeof(t_app));
	if (open_file(filename, app) != 0)
		exit_app(app, true);
	//parsing file here

	//init window
	if (!init_window(app))
		exit_app(app, true);

	if (!do_raytracing(app))
		exit_app(app, true);
	app_loop(app);
	exit_app(app, false);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
		init_app(argv[1]);
	else
		ft_putendl_fd("Usage: miniRT *.rt", STDOUT_FILENO);
	return (0);
}
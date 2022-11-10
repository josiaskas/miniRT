/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 09:30:49 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_error(char *error_message, int code)
{
	ft_putstr_fd("miniRT: error\nCode:", STDERR_FILENO);
	ft_putnbr_fd(code, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
}

static void	clean_app_stuff(t_app *app)
{
	if (app->img)
		free(app->img);
	if (app->mouse)
		free(app->mouse);
	if (app->in_fd != 0)
		close(app->in_fd);
	if (app->out_fd != 0)
		close(app->out_fd);
	if (app->data)
		free_array((void **)app->data, W_HEIGHT);
}

static void	clean_raytrace_stuff(t_app *app)
{
	if (app->scene)
		free_scene(app->scene);
}

void	exit_app(t_app *app, bool error)
{
	if (!app)
		exit(-1);
	if (error)
		ft_print_error(app->error_message, app->error_code);
	clean_app_stuff(app);
	clean_raytrace_stuff(app);
	free(app);
	if (error)
		exit(-1);
	else
		exit(0);
}

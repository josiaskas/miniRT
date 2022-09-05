/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// open input file with the correct extension
int	open_rt_file(char *filename, t_app *app)
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
	app->in_fd = fd;
	return (0);
}

int	open_out_file(char *file, t_app *app)
{
	int		fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		app->error_message = strerror(errno);
		app->error_code = 2;
		return (-1);
	}
	app->out_fd = fd;
	return (0);
}

static void	write_data_to_fd(t_vector *data, int fd)
{
	int			x;
	int			y;
	int			offset;
	t_vector	color;

	y = W_HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			offset = (y * (W_HEIGHT)) + x;
			color = get_vector_normalized(&data[offset]);
			ft_putnbr_fd((int)(color.x * 255.99), fd);
			write(fd, " ", 1);
			ft_putnbr_fd((int)(color.y * 255.99), fd);
			write(fd, " ", 1);
			ft_putnbr_fd((int)(color.z * 255.99), fd);
			write(fd, "\n", 1);
			x++;
		}
		--y;
	}
}

// write inside a file data build dy raytracing
int	write_image_to_file(t_app *app)
{
	if (app->out_fd && app->data)
	{
		ft_putendl_fd("P3", app->out_fd);
		ft_putnbr_fd(W_WIDTH, app->out_fd);
		ft_putstr_fd(" ", app->out_fd);
		ft_putnbr_fd(W_HEIGHT, app->out_fd);
		ft_putendl_fd("\n255", app->out_fd);
		write_data_to_fd(app->data, app->out_fd);
	}
	return (0);
}
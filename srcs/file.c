/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:51:51 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 19:15:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

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
	int	fd;

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

//static void	write_data_to_fd(t_color **data)
//{
//	int		x;
//	int		y;
//	t_color	color;
//
//	y = 0;
//	while (y < W_HEIGHT)
//	{
//		x = 0;
//		while (x < W_WIDTH)
//		{
//			color = data[y][x];
//			printf("%d %d %d ", (int)(color.r * 255),
//				(int)(color.g * 255), (int)(color.b * 255));
//			x++;
//		}
//		printf("\n");
//		y++;
//	}
//}

// write inside a file data build dy raytracing
int	write_image_to_file(t_app *app)
{
	(void)app;
	return (0);
}

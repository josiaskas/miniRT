/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 20:21:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

void	get_trans_vector(t_v3 *v)
{
	char	*line;
	bool	is_valid;

	is_valid = false;
	line = NULL;
	while (!is_valid)
	{
		ft_putstr_fd("Translation (x,y,z): ", STDOUT_FILENO);
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, v);
		free(line);
		line = NULL;
		if (!is_valid)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	get_line_color(t_color *color)
{
	char	*line;
	bool	is_valid;
	t_v3	v;

	is_valid = false;
	line = NULL;
	while (!is_valid)
	{
		ft_putstr_fd("\033[0;32m-Color (r,g,b)[0-255]:\033[0m ", 1);
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, &v);
		free(line);
		line = NULL;
		if (is_valid)
		{
			is_valid = all_vector_coord_are_in_range(0, 255, &v);
			if (!is_valid)
				ft_putstr_fd(" invalid, range [0-255]\n", STDOUT_FILENO);
		}
	}
	if (!all_vector_coord_are_in_range(0, 0, &v))
		*color = make_color_vector(v, 1);
	ft_putstr_fd("\033[0;32m ok\033[0m\n", STDOUT_FILENO);
}

void	get_line_angles(t_v3 *angles)
{
	char	*line;
	bool	is_valid;

	is_valid = false;
	line = NULL;
	while (!is_valid)
	{
		ft_putstr_fd("\033[0;32m-Angles (x,y,z)[180,-180]:\033[0m ", 1);
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, angles);
		free(line);
		line = NULL;
		if (is_valid)
		{
			is_valid = all_vector_coord_are_in_range(-180, 180, angles);
			if (!is_valid)
				ft_putstr_fd(" invalid, range [-180, 180]\n", STDOUT_FILENO);
		}
	}
	*angles = v3_multi(0.01745329251, *angles);
	ft_putstr_fd("\033[0;32m ok\033[0m\n", STDOUT_FILENO);
}

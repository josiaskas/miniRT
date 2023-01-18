/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 21:21:11 by jkasongo         ###   ########.fr       */
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
		printf("-Translation (x,y,z): ");
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, v);
		free(line);
		line = NULL;
		if (!is_valid)
			printf("\033[0;31mInvalid input\033[0m \n");
	}
}

void	get_line_color(t_color *color)
{
	char	*line;
	bool	is_valid;
	t_v3	v;

	is_valid = false;
	line = NULL;
	v = (t_v3){0, 0, 0};
	while (!is_valid)
	{
		printf("\033[0;32m-Color (r,g,b)[0-255]:\033[0m ");
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, &v);
		free(line);
		line = NULL;
		if (is_valid)
		{
			is_valid = all_vector_coord_are_in_range(0, 255, &v);
			if (!is_valid)
				printf("\033[0;31mInvalid range [0-255]\033[0m \n");
		}
		else
			printf("\033[0;31mInvalid input\033[0m \n");
	}
	*color = make_color_vector(v, 1);
}

void	get_line_angles(t_v3 *angles)
{
	char	*line;
	bool	is_valid;

	is_valid = false;
	line = NULL;
	*angles = (t_v3){0, 0, 0};
	while (!is_valid)
	{
		printf("\033[0;32m-Angles (x,y,z)[180,-180]:\033[0m ");
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_a_vector(line, angles);
		free(line);
		line = NULL;
		if (is_valid)
		{
			is_valid = all_vector_coord_are_in_range(-180, 180, angles);
			if (!is_valid)
				printf("Invalid, range [-180, 180]\n");
		}
		else
			printf("\033[0;31mInvalid input\033[0m \n");
	}
	*angles = v3_multi(0.01745329251, *angles);
}

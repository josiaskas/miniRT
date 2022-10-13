/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/12 13:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"


void	get_line_vector(char *title, t_v3 *v)
{
	char	*line;
	bool	is_valid;
	char	*trim_l;

	is_valid = false;
	while (!is_valid)
	{
		printf("\033[0;32m\n-%s:\033[0m ", title);
		get_next_line(STDIN_FILENO,&line);
		trim_l =  ft_strtrim(line, " \v\r\t");
		is_valid = parse_a_vector(line, v);
		free(trim_l);
	}
	printf("\033[0;32m ok\033[0m\n");
	free(line);
}

void	get_line_color(t_color *color)
{
	char	*line;
	char	*trim_l;
	bool	is_valid;
	t_v3	v;

	is_valid = false;
	while (!is_valid)
	{
		printf("\033[0;32m\n color [0-255]:\033[0m ");
		get_next_line(STDIN_FILENO,&line);
		trim_l =  ft_strtrim(line, " \v\r\t");
		is_valid = parse_a_vector(line, &v);
		free(trim_l);
		if (is_valid)
		{
			is_valid = all_vector_coord_are_in_range(0, 255, &v);
			if (!is_valid)
				printf("invalid range [0-255]");
		}
	}
	*color = make_color_vector(v, 1);
	free(line);
	printf("\033[0;32m ok\033[0m\n");
}

void	get_line_double(char *title, double *val)
{
	char	*line;
	char	*trim_l;
	bool	is_valid;

	is_valid = false;
	while (!is_valid)
	{
		printf("\033[0;32m\n-%s:\033[0m ", title);
		get_next_line(STDIN_FILENO,&line);
		trim_l =  ft_strtrim(line, " \v\r\t");
		is_valid = parse_double_from_str(trim_l, val);
		free(trim_l);
	}
	free(line);
	printf("\033[0;32m ok\033[0m\n");
}
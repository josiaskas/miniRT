/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 20:49:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "parser.h"

void	get_line_double(char *title, double *val)
{
	char	*line;
	bool	is_valid;

	is_valid = false;
	line = NULL;
	while (!is_valid)
	{
		printf("\033[0;32m-%s:\033[0m ", title);
		get_next_line(STDIN_FILENO, &line);
		is_valid = parse_double_from_str(line, val, true);
		free(line);
		line = NULL;
		if (is_valid)
			is_valid = *val >= 0;
		if (!is_valid)
			printf("\033[0;31mInvalid input\033[0m \n");
	}
}

void	get_line_int(char *title, int *val, int min, int max)
{
	char	*line;
	bool	is_valid;

	is_valid = false;
	line = NULL;
	while (!is_valid)
	{
		printf("\033[0;32m-%s:\033[0m ", title);
		get_next_line(STDIN_FILENO, &line);
		is_valid = ft_is_a_number(line, false);
		if (is_valid)
			*val = ft_atoi(line);
		free(line);
		line = NULL;
		if (is_valid)
			is_valid = ((*val >= min) && (*val <= max));
		if (!is_valid)
			printf("\033[0;31mInvalid input\033[0m \n");
	}
}

bool	get_line_bool(char *title)
{
	char	*line;
	bool	is_valid;
	bool	state;

	is_valid = false;
	line = NULL;
	state = false;
	while (!is_valid)
	{
		printf("\033[0;32m-%s:\033[0m ", title);
		get_next_line(STDIN_FILENO, &line);
		is_valid = true;
		if (ft_strncmp(line, "y", 1) == 0)
			state = true;
		else if (ft_strncmp(line, "n", 1) == 0)
			state = false;
		else
			is_valid = false;
		free(line);
		line = NULL;
		if (!is_valid)
			printf("\033[0;31mInvalid input\033[0m \n");
	}
	return (state);
}

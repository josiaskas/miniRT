/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:37:36 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// check if is only digit, if decimal '-' in front is false
static inline bool	ft_is_a_number(char *str, bool is_decimal)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	if (str[0] == '-' && (!is_decimal))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (i > 10)
		return (false);
	return (true);
}

// return a double formed from two strings "12"."34"
static double	ft_parse_double(char *str1, char *str2)
{
	double	r;
	double	f;
	double	after_dot;

	r = (double)ft_atoi(str1);
	after_dot = (double)ft_strlen(str2) * -1.0f;
	f = pow(10, after_dot) * (double)ft_atoi(str2) ;
	return (r + f);
}

bool	parse_double_from_str(char *str, double *result)
{
	char	**values;
	size_t	i;
	bool	status;

	status = true;
	i = 0;
	*result = 0;
	values = ft_split(str, '.');
	while (values[i] != 0)
		i++;
	if (!ft_is_a_number(values[0], false))
		status = false;
	if ((i > 2) || (status == false))
		status = false;
	else if (i == 1)
		*result = ft_parse_double(values[0], NULL);
	else
	{
		if (!ft_is_a_number(values[1], true))
			status = false;
		*result = ft_parse_double(values[0], values[1]);
	}
	ft_free_splitted(values);
	return (status);
}

bool	parse_a_vector(char *token, t_v3 *vector)
{
	char	**values;
	size_t	i;
	bool	status;

	values = ft_split(token, ',');
	status = true;
	i = 0;
	while (values[i] != 0)
		i++;
	if (i != 3)
		status = false;
	else
	{
		if (!parse_double_from_str(values[0], &vector->x))
			status = false;
		if (!parse_double_from_str(values[1], &vector->y))
			status = false;
		if (!parse_double_from_str(values[2], &vector->z))
			status = false;
	}
	ft_free_splitted(values);
	return (status);
}

inline bool	tokens_has_valid_params_nbr(char **tokens, size_t nbr)
{
	size_t		params_nbr;

	params_nbr = 0;
	while (tokens[params_nbr] != 0)
		params_nbr++;
	if (params_nbr != nbr)
		return (false);
	return (true);
}


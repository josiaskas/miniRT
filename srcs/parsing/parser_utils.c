/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:51:21 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 20:34:45 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_is_a_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static inline bool	parse_double_suite(char *str, double *result)
{
	bool	is_digit;
	double	decimal;
	int	    count_digit;

	decimal = 0.0;
	count_digit = 0;
	is_digit = false;
	while (ft_isdigit(*str) || (*str == '.'))
	{
		if ((*str == '.' && is_digit) || (*str == '.' && !ft_isdigit(*(str + 1))))
			return (false);
		else if (*str == '.')
			is_digit = true;
		else if (is_digit)
		{
			decimal = decimal * 10 + (*str - '0');
			count_digit++;
		}
		else
			*result = *result * 10 + (*str - '0');
		str++;
	}
	*result += (decimal / pow(10, count_digit));
	return (*str == '\0');
}

bool	parse_double_from_str(char *str, double *result)
{
	bool 	is_valid;
	bool 	is_negative;

	is_valid = false;
	is_negative = false;
	*result = 0.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		is_negative = true;
		str++;
	}
	if (!ft_isdigit(*str))
		return (false);
	if (parse_double_suite(str, result))
	{
		is_valid = true;
		if (is_negative)
			*result *= -1.0;
	}
	return (is_valid);
}

bool	parse_a_vector(char *token, t_v3 *vector)
{
	char	**values;
	size_t	i;
	bool	status;

	status = true;
	if (ft_strnstr(token, ",,", ft_strlen(token)))
		return (false);
	values = ft_split(token, ',');
	i = 0;
	while (values[i])
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
	size_t	params_nbr;

	params_nbr = 0;
	while (tokens[params_nbr] != 0)
		params_nbr++;
	if (params_nbr != nbr)
		return (false);
	return (true);
}

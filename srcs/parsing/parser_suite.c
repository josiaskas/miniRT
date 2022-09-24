/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 14:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// check if is only digit, if decimal '-' in front is false
bool	ft_is_a_number(char *str, bool is_decimal)
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

bool	parse_plan(char **tokens, t_app *app)
{
	t_hittable	*plan;

	plan = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	ft_push(app->scene->hittable, plan);
	plan->type = e_hit_plane;
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &plan->origin))
		return (false);
	if (!parse_a_vector(tokens[2], &plan->conf_vector))
		return (false);
	if (!parse_a_vector(tokens[3], &plan->color))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &plan->conf_vector))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &plan->color))
		return (false);
	return (true);
}

bool	parse_light(char **tokens, t_app *app)
{
	t_light		*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	ft_push(app->scene->lights, light);
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &light->origin))
		return (false);
	if (!parse_double_from_str(tokens[2], &light->cd))
		return (false);
	if (!parse_a_vector(tokens[3], &light->color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &light->color))
		return (false);
	if (light->cd < 0 || light->cd > 1.0f)
		return (false);
	return (true);
}
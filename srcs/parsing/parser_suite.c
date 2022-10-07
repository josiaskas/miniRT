/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:37:45 by jkasongo         ###   ########.fr       */
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

bool	parse_sphere(char **tokens, t_app *app)
{
	t_hittable	*sphere;
	t_vector	v_color;

	app->error_message = "Error during parsing, On a sphere";
	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	ft_push(app->scene->hittable, sphere);
	sphere->type = e_hit_sphere;
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &sphere->origin))
		return (false);
	if (!parse_double_from_str(tokens[2], &sphere->conf_data_1))
		return (false);
	if (!parse_a_vector(tokens[3], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	sphere->color = make_color_vector(&v_color, 1);
	init_hittable_info(sphere, e_metallic);
	return (true);
}

bool	parse_plan(char **tokens, t_app *app)
{
	t_hittable	*plan;
	t_vector	v_color;

	app->error_message = "Error during parsing, On a plan";
	plan = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	ft_push(app->scene->hittable, plan);
	plan->type = e_hit_plane;
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &plan->origin))
		return (false);
	if (!parse_a_vector(tokens[2], &plan->conf_vector))
		return (false);
	if (!parse_a_vector(tokens[3], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &plan->conf_vector))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	plan->color = make_color_vector(&v_color, 1);
	init_hittable_info(plan, e_metallic);
	return (true);
}

bool	parse_cylinder(char **tokens, t_app *app)
{
	t_hittable	*cylinder;
	t_vector	v_color;

	app->error_message = "Error during parsing, On a cylinder";
	cylinder = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	ft_push(app->scene->hittable, cylinder);
	cylinder->type = e_hit_cylinder;
	if (!tokens_has_valid_params_nbr(tokens, 6))
		return (false);
	if (!parse_a_vector(tokens[1], &cylinder->origin))
		return (false);
	if (!parse_a_vector(tokens[2], &cylinder->conf_vector))
		return (false);
	if (!parse_double_from_str(tokens[3], &cylinder->conf_data_1))
		return (false);
	if (!parse_double_from_str(tokens[4], &cylinder->conf_data_2))
		return (false);
	if (!parse_a_vector(tokens[5], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &cylinder->conf_vector))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	cylinder->conf_vector = normalize(&cylinder->conf_vector);
	cylinder->color = make_color_vector(&v_color, 1);
	init_hittable_info(cylinder, e_metallic);
	return (true);
}


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

bool	parse_plan(char **tokens, t_app *app)
{
	t_hittable	*plan;
	t_vector	v_color;

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
	plan->color =  make_color_vector(&v_color, 1);
	return (true);
}

bool	parse_light(char **tokens, t_app *app)
{
	t_light		*light;
	t_vector	v_color;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	ft_push(app->scene->lights, light);
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &light->origin))
		return (false);
	if (!parse_double_from_str(tokens[2], &light->cd))
		return (false);
	if (!parse_a_vector(tokens[3], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	if (light->cd < 0 || light->cd > 1.0f)
		return (false);
	light->color =  make_color_vector(&v_color, 1);
	light->color = color_multi(light->cd, &light->color);
	return (true);
}

bool	parse_ambiant_light(char **tokens, t_app *app)
{
	t_ambiant 		ambiant;
	t_vector		v_color;

	if (!tokens_has_valid_params_nbr(tokens, 3))
		return (false);
	if (!parse_double_from_str(tokens[1], &ambiant.intensity))
		return (false);
	if (!parse_a_vector(tokens[2], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	if (ambiant.intensity < 0 || ambiant.intensity > 1.0f)
		return (false);
	ambiant.color = make_color_vector(&v_color, 1);
	app->scene->ambiant = ambiant;
	return (true);
}
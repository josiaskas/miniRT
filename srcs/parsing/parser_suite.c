/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:50:59 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:51:00 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_sphere(char **tokens, t_app *app)
{
	t_point		origin;
	t_v3		data[3];
	float		radius;

	app->error_message = "Error during parsing, On a sphere";
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &origin))
		return (false);
	if (!parse_float_from_str(tokens[2], &radius))
		return (false);
	if (!parse_a_vector(tokens[3], &data[2]))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &data[2]))
		return (false);
	data[0] = v3_multi(radius, v3(1.0f, 1.0f, 1.0f));
	data[1] = v3(0.0f, 0.0f, 0.0f);
	return (build_sphere(app->scene, origin, data));
}

bool	parse_plan(char **tokens, t_app *app)
{
	t_v3	normal;
	t_point	p;
	t_v3	v_color;

	app->error_message = "Error during parsing, On a plan";
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &p))
		return (false);
	if (!parse_a_vector(tokens[2], &normal))
		return (false);
	if (!parse_a_vector(tokens[3], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &normal))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	return (build_plane(app->scene, p, normal, v_color));
}

bool	parse_cylinder(char **tokens, t_app *app)
{
	t_point		p;
	t_v3		data[5];
	float		conf[2];

	app->error_message = "Error during parsing, On a cylinder";
	if (!tokens_has_valid_params_nbr(tokens, 6))
		return (false);
	if (!parse_a_vector(tokens[1], &p))
		return (false);
	if (!parse_a_vector(tokens[2], &data[3]))
		return (false);
	if (!parse_float_from_str(tokens[3], &conf[0]))
		return (false);
	if (!parse_float_from_str(tokens[4], &conf[1]))
		return (false);
	if (!parse_a_vector(tokens[5], &data[2]))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &data[3]))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &data[2]))
		return (false);
	conf[0] = conf[0] / 2;
	data[0] = v3_multi((conf[0] / 2.0f), v3(1.0f, 1.0f, 1.0f));
	data[1] = v3(45.0f, 45.0f, 45.0f);
	transform_to_rad_and_check(&data[1]);
	return (build_cy(app->scene, p, data, conf[1]));
}

bool	parse_triangle(char **tokens, t_app *app)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_v3	v_color;

	app->error_message = "Error during parsing, On a triangle";
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &p1))
		return (false);
	if (!parse_a_vector(tokens[2], &p2))
		return (false);
	if (!parse_a_vector(tokens[3], &p3))
		return (false);
	if (!parse_a_vector(tokens[4], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	return (bld_t(app->scene, p1, p2, p3, v_color));
}

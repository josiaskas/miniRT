/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:50:59 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:36:24 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_sphere(char **tokens, t_app *app)
{
	t_point		origin;
	t_v3		data[3];
	double		radius;

	app->error_message = "Error during parsing, On a sphere";
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &origin))
		return (false);
	if (!parse_double_from_str(tokens[2], &radius))
		return (false);
	if (!parse_a_vector(tokens[3], &data[2]))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &data[2]))
		return (false);
	data[0] = v3_multi(radius, (t_v3){1, 1, 1});
	data[1] = (t_v3){0, 0, 0};
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
	normal = normalize(normal);
	return (build_plane(app->scene, p, normal, v_color));
}

bool	parse_cylinder(char **tokens, t_app *app)
{
	t_point		p;
	t_v3		data[5];
	double		conf[2];

	app->error_message = "Error during parsing, On a cylinder";
	if (!tokens_has_valid_params_nbr(tokens, 6))
		return (false);
	if (!parse_a_vector(tokens[1], &p))
		return (false);
	if (!parse_a_vector(tokens[2], &data[3]))
		return (false);
	if (!parse_double_from_str(tokens[3], &conf[0]))
		return (false);
	if (!parse_double_from_str(tokens[4], &conf[1]))
		return (false);
	if (!parse_a_vector(tokens[5], &data[2]))
		return (false);
	if (!all_vector_coord_are_in_range(-1, 1, &data[3]))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &data[2]))
		return (false);
	data[0] = (t_v3){conf[0] * 0.5, 1, 1};
	data[1] = (t_v3){0, 0, 0};
	transform_to_rad_and_check(&data[1]);
	return (build_cy(app->scene, p, data, conf[1]));
}

bool	parse_triangle(char **tokens, t_app *app)
{
	t_point	p[3];
	t_v3	v_color;

	app->error_message = "Error during parsing, On a triangle";
	if (!tokens_has_valid_params_nbr(tokens, 4))
		return (false);
	if (!parse_a_vector(tokens[1], &p[0]))
		return (false);
	if (!parse_a_vector(tokens[2], &p[1]))
		return (false);
	if (!parse_a_vector(tokens[3], &p[2]))
		return (false);
	if (!parse_a_vector(tokens[4], &v_color))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &v_color))
		return (false);
	return (build_triangle(app->scene, p, v_color));
}

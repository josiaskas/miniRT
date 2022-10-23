/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_suite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:50:37 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:50:43 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static inline bool	transform_to_rad_and_check(t_v3 *v)
{
	if (!all_vector_coord_are_in_range(-360, 360, v))
		return (false);
	if (v->x != 0)
		v->x = (v->x * M_PI) / 180;
	if (v->y != 0)
		v->y = (v->y * M_PI) / 180;
	if (v->z != 0)
		v->z = (v->z * M_PI) / 180;
	return (true);
}

bool	parse_sphere_bonus(char **tokens, t_app *app)
{
	t_v3		data[3];
	t_point		origin;

	app->error_message = "Error during parsing, On a bonus sphere";
	if (!tokens_has_valid_params_nbr(tokens, 5))
		return (false);
	if (!parse_a_vector(tokens[1], &origin))
		return (false);
	if (!parse_a_vector(tokens[2], &data[0]))
		return (false);
	if (!parse_a_vector(tokens[3], &data[1]))
		return (false);
	if (!parse_a_vector(tokens[4], &data[2]))
		return (false);
	if (!transform_to_rad_and_check(&data[1]))
		return (false);
	if (!all_vector_coord_are_in_range(0, 255, &data[2]))
		return (false);
	return (build_sphere(app->scene, origin, data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 14:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minirt.h"
# include "vector.h"
# include "color.h"

bool	parse_a_vector(char *token, t_v3 *vector);
bool	parse_double_from_str(char *str, double *result);
bool	tokens_has_valid_params_nbr(char **tokens, size_t nbr);
bool	parse_sphere(char **tokens, t_app *app);
bool	parse_plan(char **tokens, t_app *app);
bool	parse_cylinder(char **tokens, t_app *app);
bool	parse_triangle(char **tokens, t_app *app);

// check if vector parameters are in [min, max]
static inline bool	all_vector_coord_are_in_range(double min, double max, t_v3 *v)
{
	if (v->x < min || v->x > max)
		return (false);
	if (v->y < min || v->y > max)
		return (false);
	if (v->z < min || v->z > max)
		return (false);
	return (true);
}
#endif //PARSER_H

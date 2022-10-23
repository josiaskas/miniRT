/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:45:25 by jkasongo         ###   ########.fr       */
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
bool	parse_sphere_bonus(char **tokens, t_app *app);
bool	parse_plan(char **tokens, t_app *app);
bool	parse_cylinder(char **tokens, t_app *app);
bool	parse_triangle(char **tokens, t_app *app);
char	*add_name(t_scene *scene, char *name, bool parsed);

// check if vector parameters are in [min, max]
static inline bool	all_vector_coord_are_in_range(double m, double max, t_v3 *v)
{
	if (v->x < m || v->x > max)
		return (false);
	if (v->y < m || v->y > max)
		return (false);
	if (v->z < m || v->z > max)
		return (false);
	return (true);
}
#endif

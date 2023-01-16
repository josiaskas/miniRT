/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:39:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minirt.h"
# include "vector.h"
# include "color.h"

bool		parse_a_vector(char *token, t_v3 *vector);
bool		parse_double_from_str(char *str, double *result);
bool		tokens_has_valid_params_nbr(char **tokens, size_t nbr);
bool		parse_sphere(char **tokens, t_app *app);
bool		parse_sphere_bonus(char **tokens, t_app *app);
bool		parse_plan(char **tokens, t_app *app);
bool		parse_cylinder(char **tokens, t_app *app);
bool		parse_triangle(char **tokens, t_app *app);
bool		transform_to_rad_and_check(t_v3 *v);
char		*add_name(t_scene *scene, char *name, bool parsed);
bool		ft_is_a_number(char *str, bool is_decimal);

// check if vector parameters are in [min, max]
bool		all_vector_coord_are_in_range(double mi, double max, const t_v3 *v);
t_material	build_default_material(t_color clr, double s, double d, double ph);
t_material	build_stripped(t_color clr[], double s, double d, double ph);
bool		check_config_file(t_app *app);
#endif

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
# include "vector.h"

bool	parse_a_vector(char *token, t_vector *vector);
bool	parse_double_from_str(char *str, double *result);
bool	tokens_has_valid_params_nbr(char **tokens, size_t nbr);
bool	all_vector_coord_are_in_range(double min, double max, t_vector *v);
bool	ft_is_a_number(char *str);

#endif //PARSER_H

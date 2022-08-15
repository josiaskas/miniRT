/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H
# include "vector.h"

typedef struct s_point
{
	double coord[3];
}	t_point;

t_vector	get_line_f_p(t_point *a, t_point *b);
double		get_distance_b_p(t_point *a, t_point *b);
#endif //POINT_H
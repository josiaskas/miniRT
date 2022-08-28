/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

// return a vector build from two point, une droite
t_vector get_line_f_p(t_point *a, t_point *b)
{
	t_vector v;

	v.coord[0] = 0;
	v.coord[1] = 0;
	v.coord[2] = 0;

	if (a && b)
	{
		v.coord[0] = (b->coord[0] - a->coord[0]);
		v.coord[1] = (b->coord[1] - a->coord[1]);
		v.coord[2] = (b->coord[2] - a->coord[2]);
	}
	return (v);
}

// return the distance between two point
double get_distance_b_p(t_point *a, t_point *b)
{
	double d;

	d = 0;
	if (a && b)
	{
		d = sqrt(pow((b->coord[0] - a->coord[0]), 2) +
				 pow((b->coord[1] - a->coord[1]), 2) +
				 pow((b->coord[2] - a->coord[2]), 2));
	}
	return (d);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

// return a vector build from two point, une droite or (b-a)
inline t_vector	get_vector_between(t_point *a, t_point *b)
{
	t_vector v;

	v.x = 0;
	v.y = 0;
	v.z = 0;

	if (a && b)
	{
		v.x = (b->x - a->x);
		v.y = (b->y - a->y);
		v.z = (b->z - a->z);
	}
	return (v);
}

// return the distance between two point
double	get_distance_b_p(t_point *a, t_point *b)
{
	double d;

	d = 0;
	if (a && b)
	{
		d = sqrt(pow((b->x - a->x), 2)
				+ pow((b->y - a->y), 2)
				+ pow((b->z - a->z), 2));
	}
	return (d);
}

// a - b
inline t_vector substract_vector(t_vector *a, t_vector *b)
{
	t_vector v;

	v.x = 0;
	v.y = 0;
	v.z = 0;

	if (a && b)
	{
		v.x = (a->x - b->x);
		v.y = (a->y - b->y);
		v.z = (a->z - b->z);
	}
	return (v);
}

// transform degree angle to radian
double	degrees_to_radians(double degree)
{
	double	radian;

	radian = (degree * M_PI) / 180.0f;
	return  (radian);
}
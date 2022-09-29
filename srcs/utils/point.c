/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 23:34:14 by jkasongo         ###   ########.fr       */
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

inline t_vector4 vector4_add(t_vector4 *a, t_vector4 *b)
{
	t_vector4	addition;

	addition.a = a->a + b->a;
	addition.r = a->r + b->r;
	addition.g = a->g + b->g;
	addition.b = a->b + b->b;

	return (addition);
}

inline t_vector4	vector4_multi(double k, t_vector4 *v)
{
	t_vector4	multiplication;

	ft_bzero(&multiplication, sizeof(multiplication));
	if (v)
	{
		multiplication.a = k * v->a;
		multiplication.r = k * v->r;
		multiplication.g = k * v->g;
		multiplication.b = k * v->b;
	}
	return (multiplication);
}
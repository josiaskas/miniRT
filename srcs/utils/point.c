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

/*
 * Normalize and make sure color vector is between 0 and 1;
*/
inline t_vector4	clamp_color_vect(t_color *v)
{
	t_vector4	normalized;
	t_vector4	clamped;

	normalized = normalize_vec4(v);
	clamped.r = (normalized.r / 2) + 0.5f;
	clamped.g = (normalized.g / 2) + 0.5f;
	clamped.b = (normalized.b / 2) + 0.5f;
	clamped.a = (normalized.a / 2) + 0.5f;
	return (clamped);
}

// return unsigned int value of the color
inline unsigned int get_vector_trgb(t_color color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	r = (unsigned int)(color.r * 255.0f);
	g = (unsigned int)(color.g * 255.0f);
	b = (unsigned int)(color.b * 255.0f);
	a = (unsigned int)(color.a * 255.0f);

	return ((a<<24) | (r << 16) | (g << 8) | b);
}

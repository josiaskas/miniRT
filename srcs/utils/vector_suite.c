/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:28:51 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// a - b
inline t_vector	substract_vector(t_vector *a, t_vector *b)
{
	t_vector	v;

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

/*
 * Retourne un vecteur créer sur la stack avec (i, j, k)
*/
inline t_vector	vect3(double i, double j, double k)
{
	t_vector	vector;

	vector.x = i;
	vector.y = j;
	vector.z = k;
	return (vector);
}

inline t_vector4	normalize_vec4(t_vector4 *v)
{
	double		c;
	double		norm;
	t_vector4	n;

	ft_bzero(&n, sizeof (t_vector4));
	if (v)
	{
		c = ((v->r * v->r) + (v->g * v->g) + (v->b * v->b) + (v->a * v->a));
		norm = sqrt(c);
		n.r = (1 / norm) * v->r;
		n.g = (1 / norm) * v->g;
		n.b = (1 / norm) * v->b;
		n.a = (1 / norm) * v->a;
	}
	return (n);
}

inline t_vector4	vec4(double r, double g, double b, double a)
{
	t_vector4	vector;

	vector.r = r;
	vector.g = g;
	vector.b = b;
	vector.a = a;
	return (vector);
}

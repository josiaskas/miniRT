/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// retourne la norme au carré du vecteur
inline double vector_norm_2(t_vector *v)
{
	if (v)
		return ((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	return (0);
}

// retourne la norme du vecteur
inline double vector_norm(t_vector *v)
{
	if (v)
		return (sqrt(vector_norm_2(v)));
	return (0);
}

// addition of two vectors
inline t_vector	add_vector(t_vector *a, t_vector *b)
{
	t_vector  r;

	r.x = 0;
	r.y = 0;
	r.z = 0;
	if (a && b)
	{
		r.x = (a->x + b->x);
		r.y = (a->y + b->y);
		r.z = (a->z + b->z);
	}
	return (r);
}

// multiply a vector with a number
inline t_vector	multiply_vector(double i, t_vector *v)
{
	t_vector  r;

	r.x = 0;
	r.y = 0;
	r.z = 0;
	if (v)
	{
		r.x = (i * v->x);
		r.y = (i * v->y);
		r.z = (i * v->z);
	}
	return (r);
}

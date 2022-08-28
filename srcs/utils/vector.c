/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// retourne la norme au carré du vecteur
inline double get_vector_norm_2(t_vector *v)
{
	if (v)
	{
		return ((v->coord[0] * v->coord[0]) + (v->coord[1] * v->coord[1]) +
				(v->coord[2] * v->coord[2]));
	}
	return (0);
}

// retourne la norme du vecteur
inline double get_vector_norm(t_vector *v)
{
	if (v)
		return (sqrt(get_vector_norm_2(v)));
	return (0);
}

// addition of two vectors
inline t_vector	add_vector(t_vector *a, t_vector *b)
{
	t_vector  r;

	r.coord[0] = 0;
	r.coord[1] = 0;
	r.coord[2] = 0;
	if (a && b)
	{
		r.coord[0] = (a->coord[0] + b->coord[0]);
		r.coord[1] = (a->coord[1] + b->coord[1]);
		r.coord[2] = (a->coord[2] + b->coord[2]);
	}
	return (r);
}

// multiply a vector with a number
inline t_vector	multiply_vector(double i, t_vector *v)
{
	t_vector  r;

	r.coord[0] = 0;
	r.coord[1] = 0;
	r.coord[2] = 0;
	if (v)
	{
		r.coord[0] = (i * v->coord[0]);
		r.coord[1] = (i * v->coord[1]);
		r.coord[2] = (i * v->coord[2]);
	}
	return (r);
}

// return normalized version of a vector
inline t_vector	get_normalized(t_vector *v)
{
	t_vector	n;
	double		coef;

	n.coord[0] = 0;
	n.coord[1] = 0;
	n.coord[2] = 0;
	if (v)
	{
		coef = get_vector_norm(v);
		if (coef != 0){
			coef = (1 / coef);
			return (multiply_vector(coef, &n));
		}
	}
	return (n);
}
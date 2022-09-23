/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
 * Retourne le résultat du produit scalaire (dot product)
 * |u| * |v|
 * double
*/
inline double ft_dot(t_vector *u, t_vector *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

inline t_vector ft_cross(t_vector *a, t_vector *b)
{
	t_vector vector;

	vector.x = (a->y * b->z) - (a->z * b->y);
	vector.y = (a->z * b->x) - (a->x * b->z);
	vector.z = (a->x * b->y) - (a->y * b->x);
	return (vector);
}

/*
 * Retourne un vecteur créer sur la heap avec (i, j, k)
 * t_vector * (free)
*/
inline t_vector *make_heap_vector(double i, double j, double k)
{
	t_vector *vector;

	vector = ft_calloc(1, sizeof(t_vector));
	if (vector)
	{
		vector->x = i;
		vector->y = j;
		vector->z = k;
	}
	return (vector);
}

inline t_vector make_vector(double i, double j, double k)
{
	t_vector vector;

	vector.x = i;
	vector.y = j;
	vector.z = k;
	return (vector);
}

/*
 * Retourne un repere qui sort de l'ecran
 * Ayant trois vecteur de direction
 * t_repere * (free_repere)
*/
inline t_repere *init_repere(double x, double y, double z)
{
	t_repere *orthogonal;

	orthogonal = (t_repere *)ft_calloc(1, sizeof(t_repere));
	if (orthogonal)
	{
		orthogonal->rep_x = make_vector(x, 0, 0);
		orthogonal->rep_y = make_vector(0, y, 0);
		orthogonal->rep_z = make_vector(0, 0, z);
	}
	return orthogonal;
}

inline unsigned int get_vector_trgb(t_color color)
{
	int r;
	int g;
	int b;
	int t;

	t = 1 << 24;
	r = (int)(color.x) << 16;
	g = (int)(color.y) << 8;
	b = (int)(color.z);
	return (t | r | g | b);
}
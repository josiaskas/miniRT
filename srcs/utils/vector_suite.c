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
inline double	get_scalar_product(t_vector *u, t_vector *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->y));
}

inline t_vector	get_vector_cross(t_vector *u, t_vector *v)
{
	t_vector	vector;

	vector.x = (u->y * v->z )- (u->z * v->y);
	vector.y = (u->z * v->x) - (u->x * v->z);
	vector.z = (u->x * v->y) - (u->y * v->x);
	return (vector);
}

/*
 * Retourne un vecteur créer sur la heap avec (i, j, k)
 * t_vector * (free)
*/
inline t_vector	*get_heap_vector(double i, double j, double k)
{
	t_vector  *vector;

	vector = ft_calloc(1, sizeof (t_vector));
	if (vector)
	{
		vector->x = i;
		vector->y = j;
		vector->z = k;
	}
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
	if (orthogonal){
		orthogonal->rep_x = get_heap_vector(x, 0, 0);
		orthogonal->rep_y = get_heap_vector(0, y, 0);
		orthogonal->rep_z = get_heap_vector(0, 0, z);
	}
	return orthogonal;
}

void	free_repere(t_repere *rep)
{
	if (rep)
	{
		if (rep->rep_x)
			free(rep->rep_x);
		if (rep->rep_y)
			free(rep->rep_y);
		if (rep->rep_z)
			free(rep->rep_z);
		free(rep);
	}
}
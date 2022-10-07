/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "../libft/libft.h"
# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_vector4
{
	double	r;
	double	g;
	double	b;
	double	a;
}	t_vector4;

typedef t_vector	t_point;
typedef t_vector4	t_color;

double			vector_norm(t_vector *v);
double			vector_norm_2(t_vector *v);
t_vector		add_vector(t_vector *a, t_vector *b);
t_vector		substract_vector(t_vector *a, t_vector *b);
t_vector		vect3(double i, double j, double k);

t_vector		get_vector_between(t_point *a, t_point *b);
double			get_distance_b_p(t_point *a, t_point *b);

t_vector4		normalize_vec4(t_vector4 *v);
t_vector4		vector4_add(t_vector4 *a, t_vector4 *b);
t_vector4		vector4_multi(double k, t_vector4 *v);
t_vector4		vec4(double r, double g, double b, double a);

t_color			make_color_vector(t_vector	*v, double alpha);
t_color			color_add(t_color *a, t_color *b);
t_color			color_multi(double k, t_color *c);

// multiply a vector with a number
static inline t_vector	multiply_vector(double i, t_vector *v)
{
	t_vector	r;

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

/*
 * Retourne le résultat du produit scalaire (dot product)
 * |u| * |v|
 * double
*/
inline double	ft_dot(t_vector *u, t_vector *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

// return normalized  t_vector
static inline t_vector	normalize(t_vector *v)
{
	t_vector	n;
	double		coef;

	n.x = 0;
	n.y = 0;
	n.z = 0;
	if (v)
	{
		coef = sqrt(((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
		if (coef != 0)
			return (multiply_vector((1 / coef), v));
	}
	return (n);
}

static inline t_vector	ft_cross(t_vector *a, t_vector *b)
{
	t_vector	vector;

	vector.x = (a->y * b->z) - (a->z * b->y);
	vector.y = (a->z * b->x) - (a->x * b->z);
	vector.z = (a->x * b->y) - (a->y * b->x);
	return (vector);
}

#endif //VECTOR_H

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
}	t_v3;

typedef struct s_vector4
{
	double	r;
	double	g;
	double	b;
	double	a;
}	t_v4;

typedef struct s_matrix4 {
	double data[4][4];
}	t_m4;

typedef t_v3	t_point;

double	v3_norm_2(t_v3 v);
double	v3_norm(t_v3 v);
t_v3	v3_add(t_v3 a, t_v3 b);
t_v3	v3_sub(t_v3 a, t_v3 b);
t_v3	inverse_comp(t_v3 v);
t_v4	v3_to_v4(t_v3 v);
t_v4	v4_add(t_v4 a, t_v4 b);
t_v4	v4_sub(t_v4 a, t_v4 b);
t_v4	v4_multi(double k, t_v4 v);
t_v4	v4(double r, double g, double b, double a);

/*
 * Retourne un vecteur créer sur la stack avec (i, j, k)
*/
static inline t_v3	v3(double i, double j, double k)
{
	t_v3	vector;

	vector.x = i;
	vector.y = j;
	vector.z = k;
	return (vector);
}

// multiply a vector with a number
static inline t_v3	v3_multi(double i, t_v3 v)
{
	t_v3	r;

	r.x = (i * v.x);
	r.y = (i * v.y);
	r.z = (i * v.z);
	return (r);
}

/*
 * Retourne le résultat du produit scalaire (dot product)
 * |u| * |v|
 * double
*/
inline double	ft_dot(t_v3 u, t_v3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

// return normalized  t_v3
static inline t_v3	normalize(t_v3 v)
{
	double	norm;

	norm = sqrt(((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	if (norm != 0.f)
		return (v3_multi((1 / norm), v));
	return (v3_multi(0, v));
}

static inline t_v3	ft_cross(t_v3 a, t_v3 b)
{
	t_v3	vector;

	vector.x = (a.y * b.z) - (a.z * b.y);
	vector.y = (a.z * b.x) - (a.x * b.z);
	vector.z = (a.x * b.y) - (a.y * b.x);
	return (vector);
}

static inline t_v3	reflect(t_v3 *normal, t_v3 *in)
{
	return (v3_sub(*in, v3_multi(2 * ft_dot(*in, *normal), *normal)));
}

#endif //VECTOR_H

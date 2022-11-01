/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 18:16:24 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "../libft/libft.h"
# include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_v3;

typedef struct s_vector4
{
	float	r;
	float	g;
	float	b;
	float	a;
}	t_v4;

typedef struct s_matrix4 {
	float	data[4][4];
}	t_m4;

typedef t_v3	t_point;

float	v3_norm_2(t_v3 v);
float	v3_norm(t_v3 v);
t_v3	v3_add(t_v3 a, t_v3 b);
t_v3	v3_sub(t_v3 a, t_v3 b);
t_v3	inverse_comp(t_v3 v);
t_v4	v4_add(t_v4 a, t_v4 b);
t_v4	v4_sub(t_v4 a, t_v4 b);
t_v4	v4_multi(float k, t_v4 v);
t_v3	ft_cross(t_v3 a, t_v3 b);

// multiply a vector with a number
t_v3	v3_multi(float i, t_v3 v);
// return normalized t_v3
t_v3	normalize(t_v3 v);

/*
 * Retourne un vecteur créer sur la stack avec (i, j, k)
*/
static inline t_v3	v3(float i, float j, float k)
{
	t_v3	vector;

	vector.x = i;
	vector.y = j;
	vector.z = k;
	return (vector);
}

static inline t_v4	v4(float r, float g, float b, float a)
{
	t_v4	v;

	v.r = r;
	v.g = g;
	v.b = b;
	v.a = a;
	return (v);
}

static inline t_v4	v3_to_v4(t_v3 v)
{
	t_v4	t;

	t.r = v.x;
	t.g = v.y;
	t.b = v.z;
	t.a = 1;
	return (t);
}

/*
 * Retourne le résultat du produit scalaire (dot product)
 * |u| * |v|
 * float
*/
static inline float	ft_dot(t_v3 u, t_v3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

static inline t_v3	reflect(t_v3 *normal, t_v3 *in)
{
	return (v3_sub(*in, v3_multi(2.0f * ft_dot(*in, *normal), *normal)));
}

#endif

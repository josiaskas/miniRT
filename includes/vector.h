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
	double	a;
	double	r;
	double	g;
	double	b;
}	t_vector4;

typedef t_vector	t_point;
typedef t_vector4	t_color;

double			vector_norm(t_vector *v);
double			vector_norm_2(t_vector *v);
t_vector		add_vector(t_vector *a, t_vector *b);
t_vector		substract_vector(t_vector *a, t_vector *b);
t_vector		multiply_vector(double i, t_vector *v);
t_vector		ft_cross(t_vector *u, t_vector *v);
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
		coef = vector_norm(v);
		if (coef != 0)
			return (multiply_vector((1 / coef), v));
	}
	return (n);
}

static inline void	color_check_saturation(t_color *color)
{
	if (color->r > 1.0f)
		color->r = 1.0f;
	if (color->g > 1.0f)
		color->g = 1.0f;
	if (color->b > 1.0f)
		color->b = 1.0f;
}

static inline unsigned int	get_vector_trgb(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	color_check_saturation(&color);
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = (unsigned int)(color.a);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

inline t_color	color_multi2(t_color *a, t_color *b)
{
	t_color	m;

	m.r = a->r * b->r;
	m.g = a->g * b->g;
	m.b = a->b * b->b;
	color_check_saturation(&m);
	return (m);
}

#endif //VECTOR_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:22:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/25 22:24:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
 * Normalize color vector v and return with an alpha and range for all canals (0-1)
 * make sure v as no negative
*/
inline t_color	make_color_vector(t_vector	*v, double alpha)
{
	t_color	color;

	color.a = alpha;
	color.r = v->x / 255;
	color.g = v->y / 255;
	color.b = v->z / 255;

	return (color);
}

inline t_color color_add(t_color *a, t_color *b)
{
	t_color	add;

	add = vector4_add(a, b);
	add.a = 1;
	if (add.r > 1)
		add.r = 1;
	if (add.g > 1)
		add.g = 1;
	if (add.b > 1)
		add.b = 1;
	return (add);
}

inline t_color color_multi(double k, t_color *c)
{
	t_color	m;

	m = vector4_multi(k, c);
	m.a = c->a;
	if (m.r > 1)
		m.r = 1;
	if (m.g > 1)
		m.g = 1;
	if (m.b > 1)
		m.b = 1;
	return (m);
}

inline t_color	color_multi2(t_color *a, t_color *b)
{
	t_color	m;

	m.a = a->a * b->a;
	m.r = a->r * b->r;
	m.g = a->g * b->g;
	m.b = a->b * b->b;

	if (m.a > 1)
		m.a = 1;
	if (m.r > 1)
		m.r = 1;
	if (m.g > 1)
		m.g = 1;
	if (m.b > 1)
		m.b = 1;
	return (m);
}

// return unsigned int value of the color
inline unsigned int get_vector_trgb(t_color color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = (unsigned int)(color.a);
	return ((a<<24) | (r << 16) | (g << 8) | b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/06 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "vector.h"

typedef t_v4	t_color;
/*
 * color vector v[ 0 - 1]
 * return with an alpha and range for all canals (0-1)
 * you need to make sure v as no negative
*/
t_color	make_color_vector(t_v3	v, double alpha);

static inline t_color	color_add(t_color a, t_color b)
{
	t_color	color;

	color = v4_add(a, b);
	return (color);
}

static inline t_color	color_multi(double k, t_color c)
{
	t_color	color;

	color = v4_multi(k, c);
	color.a = c.a;
	return (color);
}

static inline t_color	hadamar_prod(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r * b.r;
	color.g = a.g * b.g;
	color.b = a.b * b.b;
	color.a = 1;
	return (color);
}

static inline unsigned int	get_trgb(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	if (color.r > 1.0f)
		color.r = 1.0f;
	if (color.g > 1.0f)
		color.g = 1.0f;
	if (color.b > 1.0f)
		color.b = 1.0f;
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = (unsigned int)(color.a);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

#endif //COLOR_H
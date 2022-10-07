/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:22:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 21:32:31 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "raytrace.h"

/*
 * Normalize color vector v
 * return with an alpha and range for all canals (0-1)
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

inline t_color	color_add(t_color *a, t_color *b)
{
	t_color	add;

	add = vector4_add(a, b);
	color_check_saturation(&add);
	return (add);
}

inline t_color	color_multi(double k, t_color *c)
{
	t_color	m;

	m = vector4_multi(k, c);
	m.a = c->a;
	color_check_saturation(&m);
	return (m);
}

inline void	gamma_correction(t_color *color)
{
	(void)color;
}

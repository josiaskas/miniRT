/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:22:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 09:26:34 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	make_color_vector(t_v3	v, double alpha)
{
	t_color	color;

	color.a = alpha;
	color.r = v.x / 255;
	color.g = v.y / 255;
	color.b = v.z / 255;
	return (color);
}

t_color	hadamar_prod(t_color a, t_color b)
{
	t_color	color;

	color.r = a.r * b.r;
	color.g = a.g * b.g;
	color.b = a.b * b.b;
	color.a = 1;
	return (color);
}

unsigned int	get_trgb(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	if (color.r > 1)
		color.r = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.b > 1)
		color.b = 1;
	if (color.a > 1)
		color.a = 1;
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = (unsigned int)(color.a);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

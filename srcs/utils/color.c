/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:22:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/22 16:38:56 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

inline t_color	make_color_vector(t_v3	v, double alpha)
{
	t_color	color;

	color.a = alpha;
	color.r = v.x / 255.0f;
	color.g = v.y / 255.0f;
	color.b = v.z / 255.0f;
	return (color);
}

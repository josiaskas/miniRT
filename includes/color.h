/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 17:57:43 by jkasongo         ###   ########.fr       */
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
t_color			make_color_vector(t_v3 v, double alpha);
t_color			hadamar_prod(t_color a, t_color b);

static inline void	color_correction(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
}


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:18:16 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 22:18:17 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"



bool	bld_t(t_scene *scene, t_point p1, t_point p2, t_point p3, t_v3 v_color)
{
	t_hittable	*triangle;

	triangle = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (triangle)
	{
		triangle->type = e_hit_triangle;
		triangle->p1 = p1;
		triangle->p2 = p2;
		triangle->p3 = p3;
		triangle->color = make_color_vector(v_color, 1);
		triangle->material = ft_get_elem(scene->materials, 0);
		ft_push(scene->hittable, triangle);
		return (true);
	}
	return (false);
}
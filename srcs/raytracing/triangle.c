/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:53:55 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 18:16:33 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

bool	build_triangle(t_scene *scene, t_point p[3], t_v3 v_color)
{
	t_hittable	*triangle;
	t_color		color;

	triangle = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (triangle)
	{
		triangle->type = e_hit_triangle;
		triangle->p1 = p[0];
		triangle->p2 = p[1];
		triangle->p3 = p[2];
		color = make_color_vector(v_color, 1);
		triangle->material = build_default_material(color, 0.3, 0.7, 200);
		triangle->tr = get_identity_matrix();
		triangle->inv_tr = get_identity_matrix();
		triangle->name = add_name(scene, "Triangle parsed o_n_", true);
		ft_push(scene->hittable, triangle);
		return (true);
	}
	return (false);
}

bool	transform_triangle(t_hittable *tr, t_v3 trans, t_v3 ang, t_v3 sc)
{
	if (tr)
	{
		tr->trans = trans;
		tr->angles = ang;
		tr->scale = sc;
		tr->tr = get_tr_matrix(trans, ang, sc, false);
		tr->inv_tr = get_tr_matrix(trans, ang, sc, true);
		tr->inv_tr_trans = get_identity_matrix();
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 23:34:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray)
{
	float	nv;

	nv = ft_dot(plan->dir, ray->dir);
	if (nv != 0)
	{
		hit->intersection = true;
		hit->normal = plan->dir;
		hit->t = ft_dot(plan->dir,v3_sub(plan->o, ray->o)) / nv;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->over_p= v3_add(hit->h_point, v3_multi(RAY_T_MIN,hit->normal));
	}
}

bool	build_plane(t_scene *scn, t_point p, t_v3 normal, t_v3 v_color)
{
	t_hittable	*plan;
	t_v3		scale;
	t_v3		angles;

	plan = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (plan)
	{
		plan->type = e_hit_plane;
		plan->o = p;
		plan->dir = normal;
		plan->color = make_color_vector(v_color, 1.0f);
		plan->material = ft_get_elem(scn->materials, 0);
		plan->trans = plan->o;
		scale = v3(1.0f, 1.0f, 1.0f);
		angles = v3(0, 0, 0);
		plan->scale = scale;
		plan->angles = angles;
		plan->tr = get_tr_matrix(plan->o, angles, scale, false);
		plan->inv_tr = get_tr_matrix(plan->o, angles, scale, true);
		plan->name = add_name(scn, "Plan parsed o_n_", true);
		ft_push(scn->hittable, plan);
		return (true);
	}
	return (false);
}

bool	transform_plane(t_hittable *plan, t_v3 tr, t_v3 ang, t_v3 sc)
{
	if (plan)
	{
		plan->trans = tr;
		plan->angles = ang;
		plan->scale = sc;
		plan->tr = get_tr_matrix(tr, ang, sc, false);
		plan->inv_tr = get_tr_matrix(tr, ang, sc, true);
		return (true);
	}
	return (false);
}
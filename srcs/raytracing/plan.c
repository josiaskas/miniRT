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

void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray)
{
	double	nv;
	double	dot2;

	hit->t = RAY_T_MAX;
	hit->type = e_hit_plane;
	hit->intersection = false;
	hit->ray = ray;
	nv = ft_dot(plan->dir, ray->dir);
	if (nv != 0)
	{
		hit->intersection = true;
		hit->normal = plan->dir;
		hit->t = (ft_dot(plan->dir,v3_sub(plan->o, ray->o)) / nv);
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		dot2 = 2 * ft_dot(v3_multi(-1, hit->ray->dir), hit->normal);
		hit->r = v3_add(hit->ray->dir, v3_multi(dot2, hit->normal));
		hit->r = normalize(hit->r);
	}
}

bool	build_plan(t_scene *scene, t_point p, t_v3 normal, t_v3 v_color)
{
	t_hittable	*plan;

	plan = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (plan)
	{
		plan->type = e_hit_plane;
		plan->o = p;
		plan->dir = normal;
		plan->color = make_color_vector(v_color, 1);
		plan->material = ft_get_elem(scene->materials, 0);
		ft_push(scene->hittable, plan);
		return (true);
	}
	return (false);
}
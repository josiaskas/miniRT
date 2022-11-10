/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 14:58:07 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

void	compute_plan_hit(t_hit *hit)
{
	t_v3		n;
	t_hittable	*plan;

	if (hit->type != e_hit_plane)
		return ;
	plan = hit->object;
	n = plan->dir;
	if (!hit->inside)
		n = v3_multi(-1, plan->dir);
	n = get_vector_tr(n, plan->tr, (t_v3){0, 0, 0});
	hit->normal = normalize(n);
	hit->acne_p = v3_add(hit->h_point, v3_multi(RAY_T_MIN, hit->normal));
}

void	ft_compute_hit(t_hit *hit)
{
	if (hit->object->type == e_hit_sphere)
		compute_sphere_hit(hit);
	else if (hit->object->type == e_hit_cylinder)
		compute_cylinder_hit(hit);
	else if (hit->object->type == e_hit_plane)
		compute_plan_hit(hit);
}

void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray)
{
	double	d[2];
	double	t;
	t_ray	*s_ray;

	s_ray = get_transformed_ray(ray, plan->inv_tr, (t_v3){0, 0, 0});
	d[0] = ft_dot(plan->dir, s_ray->dir);
	if (d[0] != 0)
	{
		d[1] = ft_dot(v3_sub((t_v3){0, 0, 0}, s_ray->o), plan->dir);
		t = (d[1] / d[0]);
		hit->t_trace[0] = t;
		hit->t_trace[1] = RAY_T_MAX;
		hit->t = t;
		if (t > 0)
		{
			hit->inside = true;
			hit->intersection = true;
			hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
			hit->h_point_obj_coord = get_point_on_ray_at(hit->t, s_ray);
			if (ft_dot(plan->dir, normalize(s_ray->dir)) > 0)
				hit->inside = false;
		}
	}
	free(s_ray);
}

bool	build_plane(t_scene *scn, t_point p, t_v3 normal, t_v3 v_color)
{
	t_hittable	*plan;
	t_color		color;

	plan = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (plan)
	{
		plan->type = e_hit_plane;
		plan->o = (t_v3){0, 0, 0};
		plan->dir = normal;
		color = make_color_vector(v_color, 1);
		plan->material = build_default_material(color, 0.3, 0.7, 200);
		transform_plane(plan, p, (t_v3){0, 0, 0}, (t_v3){1, 1, 1});
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
		plan->inv_tr_trans = get_identity_matrix();
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:52:30 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 22:34:20 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

void	compute_sphere_hit(t_hit *hit)
{
	t_v4	v;

	if (hit->type != e_hit_sphere)
		return ;
	v = v4_sub(v3_to_v4(hit->h_point_obj_coord), v4(0.0f, 0.0f, 0.0f, 0.0f));
	v = multiply_m4_v4(get_transposed(&hit->object->inv_tr), v);
	hit->normal = normalize(v3(v.r, v.g, v.b));
	if (hit->inside)
		hit->normal = v3_multi(-1.0f, hit->normal);
	hit->over_p = v3_add(hit->h_point, v3_multi(RAY_T_MIN,hit->normal));
}

static inline void	set_point(t_hit *hit, t_ray *obj_r)
{
	if (hit->t < 0)
	{
		hit->t = RAY_T_MAX;
		return ;
	}
	hit->intersection = true;
	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
	hit->h_point_obj_coord = get_point_on_ray_at(hit->t, obj_r);
}

void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray)
{
	float	terms[3];
	float	t[2];
	t_v3	sphere_to_ray;
	t_ray	*s_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	s_ray = get_transformed_ray(ray, sphere->inv_tr, v3(0, 0, 0));
	sphere_to_ray = v3_sub(s_ray->o, v3(0, 0, 0));
	terms[0] = ft_dot(s_ray->dir, s_ray->dir);
	terms[1] = 2.0f * ft_dot(s_ray->dir, sphere_to_ray);
	terms[2] = ft_dot(sphere_to_ray, sphere_to_ray) - 1.0f;
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t_trace[0] = t[0];
		hit->t_trace[1] = t[1];
		hit->t = t[0];
		if ((hit->t_trace[0] < 0) && (hit->t_trace[1] > 0))
		{
			hit->inside = true;
			hit->t = t[1];
		}
		set_point(hit, s_ray);
	}
	free(s_ray);
}

bool	build_sphere(t_scene *scn, t_point o, t_v3 data[3])
{
	t_hittable	*sphere;
	t_color		color;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere;
		sphere->o = o;
		sphere->radius = 1.0f;
		color = make_color_vector(data[2], 1.0f);
		sphere->material = build_default_material(color, 0.3f, 0.7f, 200.0f);
		sphere->scale = data[0];
		sphere->angles = data[1];
		sphere->trans = sphere->o;
		sphere->tr = get_tr_matrix(o, data[1], data[0], false);
		sphere->inv_tr = get_tr_matrix(o, data[1], data[0], true);
		sphere->name = add_name(scn, "Sphere parsed o_n_", true);
		ft_push(scn->hittable, sphere);
		return (true);
	}
	return (false);
}

// apply a new transform matrix to the sphere
bool	transform_sphere(t_hittable *sphere, t_v3 tr, t_v3 ang, t_v3 sc)
{
	if (sphere)
	{
		sphere->trans = tr;
		sphere->angles = ang;
		sphere->scale = sc;
		sphere->tr = get_tr_matrix(tr, ang, sc, false);
		sphere->inv_tr = get_tr_matrix(tr, ang, sc, true);
		return (true);
	}
	return (false);
}

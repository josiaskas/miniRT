/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:52:30 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:28:06 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

void	compute_transformable_sphere_hit(t_hit *hit)
{
	t_v4	n;

	if (hit->type != e_hit_sphere)
		return ;
	n = v3_to_v4(hit->h_point_obj_coord);
	n = multiply_m4_v4(hit->object->inv_tr_trans, n);
	hit->normal = normalize((t_v3){n.r, n.g, n.b});
	if (hit->inside)
		hit->normal = v3_multi(-1, hit->normal);
	hit->acne_p = v3_add(hit->h_point, v3_multi(0, hit->normal));
}

static inline void	set_point(t_hit *hit, t_ray t_ray)
{
	if (hit->t < 0)
	{
		hit->t = RAY_T_MAX;
		return ;
	}
	hit->intersection = true;
	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
	hit->h_point_obj_coord = get_point_on_ray_at(hit->t, t_ray);
}

void	intersect_tr_sphere(t_hit *hit, t_hittable *sphere, t_ray ray)
{
	double	terms[3];
	double	t[2];
	t_v3	sphere_to_ray;
	t_ray	tr_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	tr_ray = get_transformed_ray(ray, sphere->inv_tr, (t_v3){0, 0, 0});
	sphere_to_ray = v3_sub(tr_ray.o, (t_v3){0, 0, 0});
	terms[0] = ft_dot(tr_ray.dir, tr_ray.dir);
	terms[1] = 2 * ft_dot(tr_ray.dir, sphere_to_ray);
	terms[2] = ft_dot(sphere_to_ray, sphere_to_ray) - 1.0;
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
		set_point(hit, tr_ray);
	}
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
		sphere->inv_tr_trans = get_transposed(&sphere->inv_tr);
		return (true);
	}
	return (false);
}

bool	build_special_sphere(t_scene *scn, t_point o, t_v3 data[3])
{
	t_hittable	*sphere;
	t_color		color;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere_spec;
		sphere->o = (t_v3){0, 0, 0};
		sphere->radius = 1.0;
		color = make_color_vector(data[2], 1);
		sphere->material = build_default_material(color, 0.3, 0.7, 200);
		transform_sphere(sphere, o, data[1], data[0]);
		sphere->name = add_name(scn, "Transformable sphere parsed o_n_", true);
		ft_push(scn->hittable, sphere);
		return (true);
	}
	return (false);
}

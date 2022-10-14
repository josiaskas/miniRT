/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 19:28:32 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

static inline void	set_point_and_normal(t_hit *hit, t_ray *obj_r)
{
	t_point	obj_p;
	t_v4	v;
	t_m4	transpose;

	hit->intersection = true;
	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
	obj_p = get_point_on_ray_at(hit->t, obj_r);
	v = v4_sub(v3_to_v4(obj_p), v4(0,0,0,0));
	transpose = get_transposed(&hit->object->inv_tr);
	v = multiply_m4_v4(transpose, v);
	hit->normal = normalize(v3(v.r, v.g, v.b));
	hit->r = reflect(&hit->normal, &hit->ray->dir);
}

inline void ft_swap(double *t0, double *t1)
{
	double	temp;

	temp = *t1;
	*t1 = *t0;
	*t0 = temp;
}

void intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray)
{
	double	terms[3];
	double	t[2];
	t_v3	sphere_to_ray;
	t_ray	*s_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	s_ray = get_transformed_ray(ray, sphere->inv_tr, v3(0, 0, 0));
	sphere_to_ray = v3_sub(s_ray->o, v3(0, 0, 0));
	terms[0] = ft_dot(s_ray->dir, s_ray->dir);
	terms[1] = 2.0 * ft_dot(s_ray->dir, sphere_to_ray);
	terms[2] = ft_dot(sphere_to_ray, sphere_to_ray) - 1.0;
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t_trace[0] = t[0];
		hit->t_trace[1] = t[1];
		hit->t = t[0];
		if (t[0] < 0)
			hit->t = t[1];
		if (hit->t > 0)
			set_point_and_normal(hit, s_ray);
	}
	free(s_ray);
}

bool build_sphere(t_scene *scn, t_point o, double r, t_v3 v_clr)
{
	t_hittable	*sphere;
	t_v3		scale;
	t_v3		angles;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere;
		sphere->o = o;
		sphere->radius = r;
		sphere->color = make_color_vector(v_clr, 1);
		sphere->material = ft_get_elem(scn->materials, 0);
		scale = v3_multi(r, v3(1.0, 1.0, 1.0));
		angles = v3(0, 0, 0);
		sphere->scale = scale;
		sphere->angles = angles;
		sphere->trans = sphere->o;
		sphere->tr = get_tr_matrix(sphere->o, angles, scale, false);
		sphere->inv_tr = get_tr_matrix(sphere->o, angles, scale, true);
		sphere->name = add_name(scn, "Sphere parsed o_n_", true);
		ft_push(scn->hittable, sphere);
		return (true);
	}
	return (false);
}

// apply a new transform matrix to the sphere
bool transform_sphere(t_hittable *sphere, t_v3 tr, t_v3 ang, t_v3 sc)
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
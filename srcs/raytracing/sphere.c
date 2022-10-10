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

t_v3	get_normal_in_world_space(t_v3 normal_o, t_hittable *obj)
{
	t_v4	n_world;
	t_v4	o_world;
	t_v3	n;

	n_world = v3_to_v4(normalize(normal_o));
	o_world = multiply_m4_v4(obj->tr, v4(0,0,0,0));
	n_world =  multiply_m4_v4(obj->tr, n_world);
	n_world = v4_sub(n_world, o_world);
	n = v3(n_world.r,n_world.g,n_world.b);
	return (n);
}

static inline void	set_point_and_normal(t_hit *hit, t_ray *obj_r)
{
	t_hittable	*sphere;
	t_v3		hit_p_obj;

	hit->intersection = true;
	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
	hit_p_obj = get_point_on_ray_at(hit->t, obj_r);
	sphere = (t_hittable *)hit->object;
	hit->normal = get_normal_in_world_space(hit_p_obj, sphere);
}


void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray)
{
	t_ray	*ray_o;
	double	terms[4];
	double	t0;
	double	t1;

	hit->t = RAY_T_MAX;
	hit->type = e_hit_sphere;
	hit->intersection = false;
	hit->ray = ray;
	hit->object = sphere;
	ray_o = get_obj_space_ray(ray, sphere);
	terms[0] = ft_dot(ray_o->dir, ray_o->dir);
	terms[1] = 2 * ft_dot(ray_o->dir, ray_o->o);
	terms[3] = sphere->radius * sphere->radius;
	terms[2] = ft_dot(ray_o->o, ray_o->o) - terms[3];
	if (solve_quad(terms, &t0, &t1))
	{
		hit->t = t0;
		if (t0 < 0)
			hit->t = t1;
		if (hit->t > 0)
			set_point_and_normal(hit, ray_o);
	}
	free(ray_o);
}

bool	build_sphere(t_scene *scene, t_point origin, double r, t_v3 v_color)
{
	t_hittable	*sphere;
	t_v3		size;
	t_v3		angles;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere;
		sphere->o = origin;
		sphere->radius = r;
		sphere->color = make_color_vector(v_color, 1);
		sphere->material = ft_get_elem(scene->materials, 0);
		size = v3(1,1,1);
		angles = v3(0,0,0);
		sphere->tr = get_tr_matrix(sphere->o, angles, size, false);
		sphere->inv_tr = get_tr_matrix(sphere->o, angles, size, true);
		ft_push(scene->hittable, sphere);
		return (true);
	}
	return (false);
}

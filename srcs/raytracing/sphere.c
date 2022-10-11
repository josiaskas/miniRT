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

//t_v3	get_normal_in_world_space(t_v3 normal_o, t_hittable *obj)
//{
//	t_v4	n_world;
//	t_v4	o_world;
//	t_v3	n;
//
//	n_world = v3_to_v4(normalize(normal_o));
//	o_world = multiply_m4_v4(obj->tr, v4(0,0,0,0));
//	n_world =  multiply_m4_v4(obj->tr, n_world);
//	n_world = v4_sub(n_world, o_world);
//	n = v3(n_world.r,n_world.g,n_world.b);
//	return (n);
//}
//
//static inline void	set_point_and_normal(t_hit *hit, t_ray *obj_r)
//{
//	t_hittable	*sphere;
//	t_v3		hit_p_obj;
//
//	hit->intersection = true;
//	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
//	hit_p_obj = get_point_on_ray_at(hit->t, obj_r);
//	sphere = (t_hittable *)hit->object;
//	hit->normal = get_normal_in_world_space(hit_p_obj, sphere);
//}
//

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
			hit->intersection = true;
	}
	free(s_ray);
}

bool build_sphere(t_scene *scene, t_point origin, double r, t_v3 v_color)
{
	t_hittable	*sphere;
	t_v3		scale;
	t_v3		angles;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere;
		sphere->o = origin;
		sphere->radius = r;
		sphere->color = make_color_vector(v_color, 1);
		sphere->material = ft_get_elem(scene->materials, 0);
		scale = v3_multi(r, v3(1.0, 1.0, 1.0));
		angles = v3(0, 0, 0);
		sphere->scale = scale;
		sphere->angles = angles;
		sphere->trans = sphere->o;
		sphere->tr = get_tr_matrix(sphere->o, angles, scale, false);
		sphere->inv_tr = get_tr_matrix(sphere->o, angles, scale, true);
		ft_push(scene->hittable, sphere);
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


/*
 *	Ray sphere simple intersection code test
 * 	with transform implemented
 *  t_ray	*a = NULL;
 *	t_hittable *sphere = ft_get_elem(app->scene->hittable, 0);
		if (sphere != NULL)
		{
			a = build_ray(v3(0,0,-5), v3(0,0,1));
			transform_sphere(sphere, v3(0,0,-1), v3(0,0,0), v3(2,2,2));
			t_hit *hit = do_intersect(a, sphere);
			if (hit)
			{
				printf("ray O:(%lf, %lf, %lf) V:(%lf, %lf, %lf)\n",
					   a->o.x,a->o.y,a->o.z,
					   a->dir.x,a->dir.y,a->dir.z);
				if (hit->intersection)
				{
					printf("intersected smallest t is %lf of [%lf, %lf]\n",
						   hit->t, hit->t_trace[0], hit->t_trace[1]);
				}
			}
			free(hit);
		}
*/

/*
 * Ray sphere simple intersection code test
 *
 * t_ray	*a = NULL;
 * t_hittable *sphere = ft_get_elem(app->scene->hittable, 0);
	if (sphere != NULL)
	{
		a = build_ray(v3(0,0,-5.0), v3(0,0,1));
		t_hit *hit = do_intersect(a, sphere);
		if (hit)
		{
			printf("ray O:(%lf, %lf, %lf) V:(%lf, %lf, %lf)\n",
				   a->o.x,a->o.y,a->o.z,
				   a->dir.x,a->dir.y,a->dir.z);
			if (hit->intersection)
			{
				printf("intersected smallest t is %lf of [%lf, %lf]\n",
					   hit->t, hit->t_trace[0], hit->t_trace[1]);
			}
		}
		free(hit);
	}
	free(a);
 *
 *
*/

/* ray transformation testing
 *	t_ray	*a;
 *	t_ray	*b;
	t_m4	tr1;

	t_v3 translation = v3(0,0,0);
	t_v3 angles = v3(0,0,0);
	t_v3 scales = v3(2,3,4);

	a = build_ray(v3(1,2,3), v3(0,1,0));
	tr1 = get_tr_matrix(translation, angles, scales, false);

	b = get_transformed_ray(a, tr1, angles);
	printf("origin: (%lf, %lf, %lf) direction: (%lf, %lf, %lf)\n",
		   b->o.x,b->o.y,b->o.z,
		   b->dir.x,b->dir.y,b->dir.z);
	free(a);

	tr1 = get_tr_matrix(translation, angles, scales, true);
	a = get_transformed_ray(b, tr1, angles);
	free(b);
	printf("origin: (%lf, %lf, %lf) direction: (%lf, %lf, %lf)\n",
		   a->o.x,a->o.y,a->o.z,
		   a->dir.x,a->dir.y,a->dir.z);
free(a);
*/
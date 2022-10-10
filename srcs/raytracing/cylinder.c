/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:17:56 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 22:17:57 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

inline static bool check_end_of_cylinder(t_hittable *c, t_hit *hit, t_v3 v[])
{
	double 	dot[3];
	t_point	p_ray;
	//t_v3	p;

	p_ray = get_point_on_ray_at(hit->t, hit->ray);
	dot[0] = ft_dot(v3_sub(p_ray, c->o), c->dir);
	dot[1] = ft_dot(v3_sub(p_ray, c->p2), c->dir);
	hit->h_point = p_ray;
	if (dot[0] > 0 && dot[1]< 0)
	{

	}
	if ((dot[0] > 0) && (dot[1] < 0))
	{
		hit->intersection = true;
		//p = v3_multi(ft_dot(v3_sub(p_ray, c->o), c->dir), c->dir);
		hit->normal= normalize(v3_add(v[0],v3_multi(hit->t, v[1])));
		dot[2] = 2 * ft_dot(v3_multi(-1, hit->ray->dir), hit->normal);
		hit->r = v3_add(hit->ray->dir, v3_multi(dot[2], hit->normal));
		hit->r = normalize(hit->r);
		return (true);
	}
	return (false);
}

void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray)
{
	t_v3	v[2];
	double	terms[4];
	double	t[2];

	t[0] = RAY_T_MAX;
	hit->type = e_hit_cylinder;
	hit->intersection = false;
	hit->ray = ray;
	v[0] = ft_cross(ft_cross(cyl->dir, v3_sub(ray->o, cyl->p1)), cyl->dir);
	v[1] = ft_cross(ft_cross(cyl->dir, ray->dir), cyl->dir);
	terms[0] = ft_dot(v[1], v[1]);
	terms[1] = ft_dot(v3_multi(2, v[0]), v[1]);
	terms[2] = ft_dot(v[0], v[0]) - (cyl->radius * cyl->radius);
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t = t[0];
		if (t[0] < 0)
			hit->t = t[1];
		check_end_of_cylinder(cyl, hit, v);
	}
}

bool build_cy(t_scene *scene, t_point p, t_v3 dir, t_v3 v_color, double t[])
{
	t_hittable	*cylinder;
	t_v4		m;
	t_v3		v;

	cylinder = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (cylinder)
	{
		cylinder->type = e_hit_cylinder;
		cylinder->o = p;
		//m = rotation_x((90 * M_PI / 180), v3_to_v4(dir));
		v = normalize(v3(m.r,m.g,m.b));
		cylinder->p1 = v3_add(p, v3_multi(t[0], v));
		cylinder->p2 = v3_add(cylinder->p1, v3_multi(t[1], dir));
		cylinder->p3 = v;
		cylinder->dir = dir;
		cylinder->radius = t[0];
		cylinder->h = t[1];
		cylinder->color = make_color_vector(v_color, 1);
		cylinder->material = ft_get_elem(scene->materials, 0);
		ft_push(scene->hittable, cylinder);
		return (true);
	}
	return (false);
}
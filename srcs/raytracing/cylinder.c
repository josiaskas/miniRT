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
#include "parser.h"

//inline static bool check_end_of_cylinder(t_hittable *c, t_hit *hit, t_v3 v[])
//{
//	double 	dot[3];
//	t_point	p_ray;
//	//t_v3	p;
//
//	p_ray = get_point_on_ray_at(hit->t, hit->ray);
//	dot[0] = ft_dot(v3_sub(p_ray, c->o), c->dir);
//	dot[1] = ft_dot(v3_sub(p_ray, c->p2), c->dir);
//	hit->h_point = p_ray;
//	if (dot[0] > 0 && dot[1]< 0)
//	{
//
//	}
//	if ((dot[0] > 0) && (dot[1] < 0))
//	{
//		hit->intersection = true;
//		//p = v3_multi(ft_dot(v3_sub(p_ray, c->o), c->dir), c->dir);
//		hit->normal= normalize(v3_add(v[0],v3_multi(hit->t, v[1])));
//		dot[2] = 2 * ft_dot(v3_multi(-1, hit->ray->dir), hit->normal);
//		hit->r = v3_add(hit->ray->dir, v3_multi(dot[2], hit->normal));
//		hit->r = normalize(hit->r);
//		return (true);
//	}
//	return (false);
//}

bool	check_cylinder_cap(t_hit *hit, t_ray *ray, t_hittable *cy)
{
	double	y[2];

	y[0] = ray->o.y + hit->t_trace[0] * ray->dir.y;
	y[1] = ray->o.y + hit->t_trace[1] * ray->dir.y;
	if ((0 < y[0]) && (y[0] < cy->h))
	{
		hit->t = hit->t_trace[0];
		return (true);
	}
	if ((0 < y[1]) && (y[1] < cy->h))
	{
		hit->t = hit->t_trace[1];
		return (true);
	}
	return (false);
}

void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray)
{
	double	terms[3];
	double	t[2];
	t_ray	*s_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	s_ray = get_transformed_ray(ray, cyl->inv_tr, v3(0, 0, 0));
	terms[0] = (s_ray->dir.x * s_ray->dir.x) + (s_ray->dir.z * s_ray->dir.z);
	if ((terms[0] <= 0.00005) || (terms[0] >= -0.00005))
	{
		terms[1] = (2 * s_ray->o.x * s_ray->dir.x) + (2 * s_ray->o.z * s_ray->dir.z);
		terms[2] = (s_ray->o.x * s_ray->o.x) + (s_ray->o.z * s_ray->o.z) - 1.0;
		if (solve_quad(terms, &t[0], &t[1]))
		{
			hit->t_trace[0] = t[0];
			hit->t_trace[1] = t[1];
			hit->intersection = check_cylinder_cap(hit, s_ray, cyl);
		}
	}
	free(s_ray);
}

bool build_cy(t_scene *scn, t_point p, t_v3 dir, t_v3 v_color, double t[])
{
	t_hittable	*cy;
	t_v3		scale;
	t_v3		angles;

	cy = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (cy)
	{
		cy->type = e_hit_cylinder;
		cy->o = p;
		cy->p1 = v3_add(p, v3_multi( t[1], dir));
		cy->dir = dir;
		cy->radius = t[0];
		cy->h = t[1];
		cy->color = make_color_vector(v_color, 1);
		cy->material = ft_get_elem(scn->materials, 0);
		scale = v3(1.0, 1.0, 1.0);
		angles = v3(0, 0, 0);
		cy->tr = get_tr_matrix(cy->o, angles, scale, false);
		cy->inv_tr = get_tr_matrix(cy->o, angles, scale, true);
		cy->name = add_name(scn, "Cylinder parsed o_n_", true);
		ft_push(scn->hittable, cy);
		return (true);
	}
	return (false);
}

bool transform_cy(t_hittable *cylinder, t_v3 tr, t_v3 ang, t_v3 sc)
{
	if (cylinder)
	{
		cylinder->trans = tr;
		cylinder->angles = ang;
		cylinder->scale = sc;
		cylinder->tr = get_tr_matrix(tr, ang, sc, false);
		cylinder->inv_tr = get_tr_matrix(tr, ang, sc, true);
		return (true);
	}
	return (false);
}
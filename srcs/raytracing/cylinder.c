/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:17:56 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/01 18:16:27 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

//inline static bool check_end_of_cylinder(t_hittable *c, t_hit *hit, t_v3 v[])
//{
//	float 	dot[3];
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

/*
bool	check_cylinder_cap(t_hit *hit, t_ray *ray, t_hittable *cy)
{
	float	y[2];

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
*/

void	compute_cylinder_hit(t_hit *hit)
{
	t_v4	n_world;

	if (hit->type != e_hit_cylinder)
		return ;
	if ((hit->m == hit->object->h) || (hit->m == 0))
		hit->normal = hit->object->dir;
	else
		hit->normal = v3_sub(hit->h_point_obj_coord,
							 v3_multi(hit->m, hit->object->dir));
	n_world = v4_sub(v3_to_v4(hit->normal), v4(0.0f, 0.0f, 0.0f, 0.0f));
	n_world = multiply_m4_v4(get_transposed(&hit->object->inv_tr), n_world);
	hit->normal = normalize(v3(n_world.r, n_world.g, n_world.b));
	if (hit->inside)
		hit->normal = v3_multi(-1.0f, hit->normal);
	hit->over_p = v3_add(hit->h_point, v3_multi(RAY_T_MIN, hit->normal));
}

static inline void	set_point(t_hit *hit, t_ray *ray, t_v3 cyl_ray)
{
	float	m;

	m = (ft_dot(ray->dir, hit->object->dir) * hit->t_trace[0])
		+ ft_dot(cyl_ray, hit->object->dir);
	if ((m >= -(hit->object->h / 2.0f)) && (m <= (hit->object->h / 2.0f)))
	{
		hit->t = hit->t_trace[0];
		hit->intersection = true;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
		hit->m = m;
		return ;
	}
	m = (ft_dot(ray->dir, hit->object->dir) * hit->t_trace[1])
		+ ft_dot(cyl_ray, hit->object->dir);
	if ((m >= -(hit->object->h / 2.0f)) && (m <= (hit->object->h / 2.0f)))
	{
		hit->t = hit->t_trace[1];
		hit->intersection = true;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
		hit->m = m;
		hit->inside = true;
	}
}

void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray)
{
	float	terms[3];
	float	t[2];
	t_ray	*ray_o;
	t_v3	cyl_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	ray_o = get_transformed_ray(ray, cyl->inv_tr, v3(0, 0, 0));
	cyl_ray = v3_sub(ray_o->o, cyl->o);
	terms[0] = ft_dot(ray_o->dir, ray_o->dir)
		- powf(ft_dot(ray_o->dir, cyl->dir), 2.0f);
	terms[1] = ft_dot(ray_o->dir, cyl_ray)
		- (ft_dot(ray_o->dir, cyl->dir) * ft_dot(cyl_ray, cyl->dir));
	terms[1] = 2.0f * terms[1];
	terms[2] = ft_dot(cyl_ray, cyl_ray)
		- powf(ft_dot(cyl_ray, cyl->dir), 2.0f) - powf(cyl->radius, 2.0f);
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t_trace[0] = t[0];
		hit->t_trace[1] = t[1];
		set_point(hit, ray_o, cyl_ray);
	}
	free(ray_o);
}

bool	build_cy(t_scene *scn, t_point o, t_v3 data[4], float h)
{
	t_hittable	*cy;
	t_color		color;

	cy = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (cy)
	{
		cy->o = v3(0.0f, 0.0f, 0.0f);
		cy->type = e_hit_cylinder;
		cy->radius = data[0].x;
		cy->scale = v3(1.0f, 1.0f, 1.0f);
		cy->angles = data[1];
		cy->trans = o;
		cy->dir = normalize(data[3]);
		cy->h = h;
		color = make_color_vector(data[2], 1);
		cy->material = build_default_material(color, 0.3f, 0.7f,200.0f);
		cy->tr = get_tr_matrix(cy->trans, cy->angles, cy->scale, false);
		cy->inv_tr = get_tr_matrix(cy->trans, cy->angles, cy->scale, true);
		cy->name = add_name(scn, "Cylinder parsed o_n_", true);
		ft_push(scn->hittable, cy);
		return (true);
	}
	return (false);
}

bool	transform_cy(t_hittable *cylinder, t_v3 tr, t_v3 ang, t_v3 sc)
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

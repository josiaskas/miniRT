/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:17:56 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 22:34:10 by jkasongo         ###   ########.fr       */
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
	t_v4	v;

	if (hit->type != e_hit_cylinder)
		return ;
	v = v3_to_v4(hit->h_point_obj_coord);
	v.b = 0.0f;
	v.a = 0.0f;
	v = multiply_m4_v4(get_transposed(&hit->object->inv_tr), v);
	hit->normal = normalize(v3(v.r, v.g, v.b));
	if (hit->inside)
		hit->normal = v3_multi(-1.0f, hit->normal);
	hit->over_p = v3_add(hit->h_point, v3_multi(0.0015f, hit->normal));
}

static inline void	set_point(t_hit *hit, t_ray *ray)
{
	float z[2];

	z[0] = ray->o.z + (hit->t_trace[0] * ray->dir.z);
	if ((0 < z[0]) && (z[0] < 1.0f))
	{
		hit->t = hit->t_trace[0];
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
		hit->intersection = true;
		return ;
	}
	z[1] = ray->o.z + (hit->t_trace[1] * ray->dir.z);
	if ((0 < z[1]) && (z[1] < 1.0f))
	{
		hit->t = hit->t_trace[1];
		hit->intersection = true;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
	}
}

void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray)
{
	float	terms[3];
	float	t[2];
	t_ray	*o_r;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	o_r = get_transformed_ray(ray, cyl->inv_tr, v3(0, 0, 0));
	terms[0] = (o_r->dir.x * o_r->dir.x) + (o_r->dir.y * o_r->dir.y);
	if ((terms[0] <= 0.00005f) || (terms[0] >= -0.00005f))
	{
		terms[1] = 2.0f * (o_r->o.x * o_r->dir.x + o_r->o.y * o_r->dir.y);
		terms[2] = (o_r->o.x * o_r->o.x) + (o_r->o.y * o_r->o.y) - 1.0f;
		if (solve_quad(terms, &t[0], &t[1]))
		{
			hit->t_trace[0] = t[0];
			hit->t_trace[1] = t[1];
			if ((hit->t_trace[0] < 0) && (hit->t_trace[1] > 0))
				hit->inside = true;
			set_point(hit, o_r);
		}
	}
	free(o_r);
}

bool	build_cy(t_scene *scn, t_point o, t_v3 data[4], float h)
{
	t_hittable	*cy;
	t_color		color;

	cy = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (cy)
	{
		cy->o = o;
		cy->type = e_hit_cylinder;
		cy->radius = 1.0f;
		cy->scale = data[0];
		cy->angles = data[1];
		cy->trans = cy->o;
		cy->dir = normalize(data[3]);
		cy->h = h;
		color = make_color_vector(data[2], 1);
		cy->material = build_default_material(color, 0.3f, 0.7f,200.0f);
		cy->tr = get_tr_matrix(o, data[1], data[0], false);
		cy->inv_tr = get_tr_matrix(o, data[1], data[0], true);
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

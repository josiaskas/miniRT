/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:17:56 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 02:37:26 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

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
	n_world = v3_to_v4(hit->normal);
	multiply_m4_v4(hit->object->inv_tr_trans, n_world);
	hit->normal = normalize((t_v3){n_world.r, n_world.g, n_world.b});
	if (hit->inside)
		hit->normal = v3_multi(-1, hit->normal);
	hit->acne_p = v3_add(hit->h_point, v3_multi(0.0015, hit->normal));
}

static inline void	set_point(t_hit *hit, t_ray ray, t_v3 cyl_ray)
{
	double	m;

	m = (ft_dot(ray.dir, hit->object->dir) * hit->t_trace[0])
		+ ft_dot(cyl_ray, hit->object->dir);
	if ((m >= 0) && (m <= hit->object->h))
	{
		hit->t = hit->t_trace[0];
		hit->intersection = true;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
		hit->m = m;
		return ;
	}
	m = (ft_dot(ray.dir, hit->object->dir) * hit->t_trace[1])
		+ ft_dot(cyl_ray, hit->object->dir);
	if ((m >= 0) && (m <= hit->object->h))
	{
		hit->t = hit->t_trace[1];
		hit->intersection = true;
		hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
		hit->h_point_obj_coord = get_point_on_ray_at(hit->t, ray);
		hit->m = m;
		hit->inside = true;
	}
}

void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray ray)
{
	double	terms[3];
	double	t[2];
	t_ray	ray_o;
	t_v3	cyl_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	ray_o = get_transformed_ray(ray, cyl->inv_tr, (t_v3){0, 0, 0});
	cyl_ray = ray_o.o;
	terms[0] = ft_dot(ray_o.dir, ray_o.dir)
		- pow(ft_dot(ray_o.dir, cyl->dir), 2);
	terms[1] = ft_dot(ray_o.dir, cyl_ray)
		- (ft_dot(ray_o.dir, cyl->dir) * ft_dot(cyl_ray, cyl->dir));
	terms[1] = 2 * terms[1];
	terms[2] = ft_dot(cyl_ray, cyl_ray)
		- pow(ft_dot(cyl_ray, cyl->dir), 2) - pow(cyl->radius, 2);
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t_trace[0] = t[0];
		hit->t_trace[1] = t[1];
		set_point(hit, ray_o, cyl_ray);
	}
}

bool	build_cy(t_scene *scn, t_point o, t_v3 data[4], double h)
{
	t_hittable	*cy;
	t_color		color;

	cy = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (cy)
	{
		cy->o = (t_v3){0, 0, 0};
		cy->type = e_hit_cylinder;
		cy->radius = data[0].x;
		cy->dir = normalize(data[3]);
		cy->h = h;
		color = make_color_vector(data[2], 1);
		cy->material = build_default_material(color, 0.3, 0.7, 200);
		transform_cy(cy, o, data[1], (t_v3){1, 1, 1});
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
		cylinder->inv_tr_trans = get_transposed(&cylinder->inv_tr);
		return (true);
	}
	return (false);
}

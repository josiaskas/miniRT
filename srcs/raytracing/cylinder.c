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
#include <math.h>

inline static bool is_on_the_right_side(t_ray *ray, double *t, t_hittable *c)
{
	t_vector from_top;
	t_vector from_bottom;
	t_point contact_p;
	t_point top_p;

	top_p = multiply_vector(c->conf_data_2, &c->conf_vector);
	top_p = add_vector(&top_p, &c->origin);
	contact_p = get_point_on_ray_at(*t, ray);
	from_bottom = substract_vector(&contact_p, &c->origin);
	from_top = substract_vector(&contact_p, &top_p);
	if (ft_dot(&from_bottom, &c->conf_vector) >= 0)
	{
		if (ft_dot(&from_top, &c->conf_vector) <= 0)
			return (true);
	}
	return (false);
}

inline static bool	check_e_lim(t_ray *r, double *t, double *tx, t_hittable *c)
{
	if ((*tx > 0.f) && is_on_the_right_side(r, tx, c))
	{
		*t = *tx;
		return (true);
	}
	return (false);
}
bool intersect_cylinder_ray(t_ray *ray, t_hittable *cylinder, double *t)
{
	double ter[4];
	t_vector v[3];
	double t0;
	double t1;

	v[0] = substract_vector(&ray->origin, &cylinder->origin);
	v[0] = ft_cross(&v[0], &cylinder->conf_vector);
	v[0] = ft_cross(&v[0], &cylinder->conf_vector);
	v[1] = ft_cross(&cylinder->conf_vector, &ray->dir);
	v[1] = ft_cross(&cylinder->conf_vector, &v[1]);
	v[2] = multiply_vector(2, &v[0]);
	ter[0] = ft_dot(&v[1], &v[1]);
	ter[1] = ft_dot(&v[2], &v[1]);
	ter[2] = ft_dot(&v[0], &v[0]) - pow(cylinder->conf_data_1, 2);
	if (!solve_quad(ter, &t0, &t1))
		return (false);
	if (check_e_lim(ray, t, &t0, cylinder))
		return (true);
	return (false);
}

t_vector get_cylinder_contact_surf_norm(t_hit *hit)
{
	t_hittable *c;
	t_vector v;
	t_vector n;

	c = (t_hittable *)hit->object;
	v = get_vector_between(&c->origin, &hit->point);
	n = multiply_vector(ft_dot(&v, &c->conf_vector), &c->conf_vector);
	n = substract_vector(&v, &n);
	n = normalize(&n);
	return (n);
}

//t_hittable	*make_cylinder(t_point origin, t_vector dir, double conf[])
//{
//	t_hittable	*cylinder;
//
//
//	return (cylinder);
//}
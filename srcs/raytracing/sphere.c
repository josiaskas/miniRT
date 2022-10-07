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
#include <math.h>

bool	intersect_sphere_ray(t_ray *ray, t_hittable *sphere, double *t)
{
	t_vector	l;
	double		terms[4];
	double		t0;
	double		t1;

	t0 = RAY_T_MAX;
	l = get_vector_between(&sphere->origin, &ray->origin);
	terms[0] = ft_dot(&ray->dir, &ray->dir);
	terms[1] = 2 * ft_dot(&ray->dir, &l);
	terms[3] = sphere->conf_data_1 * sphere->conf_data_1;
	terms[2] = ft_dot(&l, &l) - terms[3];
	if (!solve_quad(terms, &t0, &t1))
		return (false);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (false);
	}
	*t = t0;
	return (true);
}

inline t_vector	get_sphere_contact_surf_norm(t_hit *hit)
{
	t_vector	n;
	t_hittable	*sphere;

	sphere = (t_hittable *)hit->object;
	n = get_vector_between(&sphere->origin, &hit->point);
	n = normalize(&n);
	return (n);
}

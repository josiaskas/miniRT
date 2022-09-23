/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/12 20:59:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include <math.h>

bool solve_quadratic(double a, double b, double c, double *t0, double *t1)
{
	double	discriminant;
	double	q;
	double	temp;

	discriminant = (b * b) - (4.0f * a * c);
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
		*t0 = -0.5f * (b / a);
	else
	{
		if (b > 0.0f)
			q = -0.5f * (b + sqrt(discriminant));
		else
			q = -0.5f * (b - sqrt(discriminant));
		*t0 = q / a;
		*t1 = c / q;
	}
	if (*t0 > *t1)
	{
		temp = *t1;
		*t1 = *t0;
		*t0 = temp;
	}
	return (true);
}

bool	intersect_sphere_ray(t_ray *ray, t_hittable *sphere, double *t)
{
	t_vector	L;
	double		terms[4];
	double		t0;
	double		t1;

	t0 = RAY_T_MAX;
	L = get_vector_between(&sphere->origin, &ray->origin);
	terms[0] = ft_dot(&ray->dir, &ray->dir);
	terms[1] = 2 * ft_dot(&ray->dir, &L);
	terms[3] = sphere->conf_data_1 * sphere->conf_data_1;
	terms[2] = ft_dot(&L, &L) - terms[3];
	if (!solve_quadratic(terms[0], terms[1], terms[2], &t0, &t1))
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
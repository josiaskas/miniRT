/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/12 20:59:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include <math.h>

bool	intersect_plan_ray(t_ray *ray, t_hittable *plan, double *t)
{
	t_vector	normal;
	t_point		line;
	double		dot;
	double		time;

	normal = plan->conf_vector;
	dot = ft_dot(&ray->dir, &normal);
	if (dot == 0)
		return (false);

	line = get_vector_between(&ray->origin, &plan->origin);
	time = ft_dot(&line, &normal) / dot;
	if (time < 0)
		return (false);
	*t = time;
	return (true);
}
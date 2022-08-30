/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
 * Build the ray with origin and direction vector
 * return a *t_ray to be freed (free_ray)
*/
inline t_ray	*build_ray(t_point *origin, t_vector *direction)
{
	t_ray		*ray;

	ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (ray)
	{
		ray->origin = origin;
		ray->dir = direction;
	}
	return (ray);
}

/*
 * Return a Point according to t with a ray, parametric equation.
 * equation is point = ray_origin + (t * ray_dir)
 * ray dir vector need to be normalized to be correct
*/
inline t_point	get_point_on_ray_at(double t, t_ray *ray)
{
	t_point	a;

	ft_bzero(&a, sizeof(t_point));
	if (ray->dir)
	{
		a.x = ray->origin->x + (t * ray->dir->x);
		a.y = ray->origin->y + (t * ray->dir->y);
		a.z = ray->origin->z + (t * ray->dir->z);
	}
	return (a);
}

// Clean the ray
void	free_ray(t_ray *ray)
{
	if (ray)
	{
		if (ray->origin)
			free(ray->origin);
		if (ray->dir)
			free(ray->dir);
		free(ray);
	}
}
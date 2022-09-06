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

#include "raytrace.h"
#include "vector.h"

/*
 * Build the ray with origin and direction vector
 * return a *t_ray to be freed
*/
inline t_ray	*build_ray(t_point origin, t_vector direction)
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

// return the position vector of the pixel on the viewport
static t_point	get_pixel_position_point(double x, double y, t_cam *cam)
{
	t_vector	v;
	t_vector	u;
	t_point 	p_view;


	v = multiply_vector(x, &cam->u1);
	u = multiply_vector(y, &cam->u2);
	v = add_vector(&v, &u);
	v = add_vector(&v, &cam->r_init);
	u = multiply_vector(cam->near_clp_plane, &cam->dir);
	v = add_vector(&u, &v);
	p_view = add_vector(&cam->origin, &v);
	return	p_view;
}

// return a ray p_view (distance of n from the point) to the scene
inline t_ray	*get_viewport_ray(double x, double y, t_cam *cam)
{
	t_point		p_view;
	t_vector	dir;

	p_view = get_pixel_position_point(x, y, cam);
	dir =  get_line_f_p(&cam->origin, &p_view);
	dir = get_vector_normalized(&dir);
	return (build_ray(p_view, dir));
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
	a.x = ray->origin.x + (t * ray->dir.x);
	a.y = ray->origin.y + (t * ray->dir.y);
	a.z = ray->origin.z + (t * ray->dir.z);
	return (a);
}


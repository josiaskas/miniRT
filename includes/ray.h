/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/29 16:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_ray
{
	t_point		origin;
	t_vector	dir;
}	t_ray;

typedef struct s_camera
{
	t_point		origin;
	t_vector	dir;
	t_vector	dir_ort;
	double		fov;
	double		aspect_ratio;
	double		near_clp_plane;
	double		far_clp_plane;
	double		v_w;
	double		v_h;
	t_vector	u1;
	t_vector	u2;
	t_vector	r_init;
}	t_cam;

/*
 * Build the ray with origin and direction vector
 * return a *t_ray to be freed
*/
static inline t_ray	*build_ray(t_point origin, t_vector direction)
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
static inline t_point	get_pixel_position_p(double x, double y, t_cam *cam)
{
	t_vector	v;
	t_vector	u;
	t_point		p_view;

	v = multiply_vector(x, &cam->u1);
	u = multiply_vector(y, &cam->u2);
	v = add_vector(&v, &u);
	v = add_vector(&v, &cam->r_init);
	u = multiply_vector(cam->near_clp_plane, &cam->dir);
	v = add_vector(&u, &v);
	p_view = add_vector(&cam->origin, &v);
	return (p_view);
}

/*
 * return a ray p_view (distance of n from the point) to the scene
 * we don't normalize the ray direction, optimisation
*/
static inline t_ray	*get_viewport_ray(double x, double y, t_cam *cam)
{
	t_point		p_view;
	t_vector	dir;

	p_view = get_pixel_position_p(x, y, cam);
	dir = get_vector_between(&cam->origin, &p_view);
	dir = normalize(&dir);
	return (build_ray(p_view, dir));
}

/*
 * Return a Point according to t with a ray, parametric equation.
 * equation is point = ray_origin + (t * ray_dir)
 * ray dir vector need to be normalized to be correct
*/
static inline t_point	get_point_on_ray_at(double t, t_ray *ray)
{
	t_point	a;

	ft_bzero(&a, sizeof(t_point));
	a.x = ray->origin.x + (t * ray->dir.x);
	a.y = ray->origin.y + (t * ray->dir.y);
	a.z = ray->origin.z + (t * ray->dir.z);
	return (a);
}

#endif //RAY_H

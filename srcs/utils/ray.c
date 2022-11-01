/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:30:08 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 17:35:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "transformation.h"

/*
 * return a ray from camera eye to the pixel
 * use a matrix to transform from camera to view world
 * ray dir is normalized
 */
t_ray	*ray_for_pixel(t_cam *cam, float px, float py)
{
	float	off[2];
	t_v4	v[2];
	t_v3	p[2];
	t_v3	dir;

	px = px * cam->pixel_dx;
	py = py * cam->pixel_dy;
	off[0] = cam->half_width - px;
	off[1] = cam->half_height - py;
	v[1] = multiply_m4_v4(cam->inv_tr, v4(off[0], off[1], -1.0f, 1.0f));
	v[0] = multiply_m4_v4(cam->inv_tr, v4(0.0f, 0.0f, 0.0f, 1.0f));
	p[1] = v3(v[1].r, v[1].g, v[1].b);
	p[0] = v3(v[0].r, v[0].g, v[0].b);
	dir = normalize(v3_sub(p[1], p[0]));
	return (build_ray(p[0], dir));
}

/*
* Return the ray in the object space
* The ray need after usage to be freed
*/
t_ray	*get_transformed_ray(t_ray *ray, const t_m4 transform, const t_v3 sp_o)
{
	t_ray	*tr_ray;
	t_v4	o;
	t_v4	dir;
	t_v4	oo;

	o = multiply_m4_v4(transform, v3_to_v4(ray->o));
	oo = multiply_m4_v4(transform, v3_to_v4(sp_o));
	dir = multiply_m4_v4(transform, v3_to_v4(ray->dir));
	dir = v4_sub(dir, oo);
	tr_ray = build_ray(v3(o.r, o.g, o.b), v3(dir.r, dir.g, dir.b));
	return (tr_ray);
}

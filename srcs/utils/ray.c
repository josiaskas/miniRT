/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:30:08 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 13:54:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "transformation.h"
#include <stdio.h>

t_ray	make_ray(t_v3 origin, t_v3 direction)
{
	t_ray	ray;

	ray.o = origin;
	ray.dir = direction;
	return (ray);
}

/*
 * return a ray from camera eye to the pixel
 * use a matrix to transform from camera to view world
 * ray dir is normalized
 */
t_ray	ray_for_pixel(t_cam *cam, double px, double py)
{
	double	off[2];
	t_v4	v;
	t_v3	p[2];
	t_v3	dir;

	px = px * cam->pixel_dx;
	py = py * cam->pixel_dy;
	off[0] = cam->half_width - px;
	off[1] = cam->half_height - py;
	v = multiply_m4_v4(cam->inv_tr, (t_v4){off[0], off[1], -1, 1});
	p[0] = (t_v3){
		cam->inv_tr.data[0][3],
		cam->inv_tr.data[1][3],
		cam->inv_tr.data[2][3]};
	p[1] = (t_v3){v.r, v.g, v.b};
	dir = normalize(v3_sub(p[1], p[0]));
	return (make_ray(p[0], dir));
}

/*
* Return the ray in the object space
*/
t_ray	get_transformed_ray(t_ray ray, const t_m4 transform, const t_v3 sp_o)
{
	t_ray	tr_ray;
	t_v4	o;
	t_v4	dir;
	t_v4	oo;

	o = multiply_m4_v4(transform, v3_to_v4(ray.o));
	oo = multiply_m4_v4(transform, v3_to_v4(sp_o));
	dir = multiply_m4_v4(transform, v3_to_v4(ray.dir));
	dir = v4_sub(dir, oo);
	tr_ray = make_ray((t_v3){o.r, o.g, o.b}, (t_v3){dir.r, dir.g, dir.b});
	return (tr_ray);
}

/*
* Return the vector after a transformation is applied
* cant get a vector in the correct space (Object or World)
*/
t_v3	get_vector_tr(t_v3 v, const t_m4 transform, const t_v3 origin)
{
	t_v4	dir;
	t_v4	oo;
	t_v3	result;

	oo = multiply_m4_v4(transform, v3_to_v4(origin));
	dir = multiply_m4_v4(transform, v3_to_v4(v));
	dir = v4_sub(dir, oo);
	result = (t_v3){dir.r, dir.g, dir.b};
	return (result);
}

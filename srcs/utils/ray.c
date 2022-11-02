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
	t_v3	dir;
	t_v3	p_view;

	p_view = v3_add(v3_multi(px, cam->u1), v3_multi(py , cam->u2));
	p_view = v3_add(p_view, cam->r_init);
	dir = normalize(v3_sub(p_view, cam->eye));
	return (build_ray(p_view, dir));
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

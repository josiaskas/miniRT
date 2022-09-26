/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 23:34:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include <stdio.h>

bool	is_object_intersected(t_ray *ray, t_hittable *object, double *t)
{
	*t = 0;
	if (object->type == e_hit_sphere)
		return (intersect_sphere_ray(ray, object, t));
	else if (object->type == e_hit_plane)
		return (intersect_plan_ray(ray, object, t));
	return (false);
}

t_hit	do_intersect_objects(t_scene *scene, t_ray *ray, double max_time)
{
	t_hit		hit;
	size_t		i;
	t_hittable	*object;
	double		time;

	ft_bzero(&hit, sizeof(t_hit));
	i = 0;
	hit.ray = ray;
	hit.intersection = false;
	hit.t = max_time;
	while (i < scene->hittable->length)
	{
		object = (t_hittable *)ft_get_elem(scene->hittable, i);
		if (is_object_intersected(ray, object, &time) && (time < hit.t))
		{
			hit.object = object;
			hit.type = object->type;
			hit.t = time;
			hit.intersection = true;
		}
		i++;
	}
	if (hit.intersection)
		hit.point = get_point_on_ray_at((hit.t - RAY_T_MIN), ray);
	return (hit);
}


t_color	get_object_hit_color(t_scene *scene, t_hit *hit, double max_time)
{
	t_color		color;

	if (hit->type == e_hit_sphere)
		hit->normal = get_sphere_contact_surf_norm(hit);
	else if (hit->type == e_hit_plane)
		hit->normal = get_plan_contact_surf_norm(hit);
	(void)max_time;
	color = shading_light(hit, scene);
	return (color);
}

/*
 * min if ray is normalized can be far_clp_plane
 * Return a color vector (s_vector4) clamped between (0-1)
*/
t_color	do_tracing(t_scene *scene, t_ray *ray, double max_time)
{
	t_hit	first_hit;
	t_color	color;

	ft_bzero(&color, sizeof(t_color));
	color.a = 1;
	first_hit = do_intersect_objects(scene, ray, max_time);
	if (first_hit.intersection)
		color = get_object_hit_color(scene, &first_hit, max_time);
	return (color);
}

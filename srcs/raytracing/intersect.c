/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/21 15:39:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raytrace.h"

bool	is_object_intersected(t_ray *ray, t_hittable *object, double *t)
{
	*t = 0;
	if (object->type == e_hit_sphere)
		return (intersect_sphere_ray(ray, object, t));
	else if (object->type == e_hit_plane)
		return (intersect_plan_ray(ray, object, t));
	return (false);
}

t_color	do_intersect_object(t_scene *scene, t_ray *ray, double min_time)
{
	size_t		i;
	t_hittable	*object;
	double		time;
	t_hittable	*top_object;

	top_object = NULL;
	min_time = RAY_T_MAX;
	i = 0;
	while (i < scene->hittable->length)
	{
		object = (t_hittable *)ft_get_elem(scene->hittable, i);
		if (is_object_intersected(ray, object, &time))
		{
			if (time < min_time)
			{
				top_object = object;
				min_time = time;
			}
		}
		i++;
	}
	if (top_object)
		return top_object->color;
	return (make_vector(0, 0, 0));
}
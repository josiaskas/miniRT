/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:04 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/20 22:48:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void	ft_swap(double *t0, double *t1)
{
	double	temp;

	temp = *t1;
	*t1 = *t0;
	*t0 = temp;
}

bool	solve_quad(const double terms[], double *t0, double *t1)
{
	double	discriminant;
	double	q;

	discriminant = (terms[1] * terms[1]) - (4 * terms[0] * terms[2]);
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
	{
		*t0 = -0.5 * (terms[1] / terms[0]);
		*t1 = *t0;
	}
	else
	{
		if (terms[1] > 0.0)
			q = -0.5 * (terms[1] + sqrt(discriminant));
		else
			q = -0.5 * (terms[1] - sqrt(discriminant));
		*t0 = q / terms[0];
		*t1 = terms[2] / q;
	}
	if (*t0 > *t1)
		ft_swap(t0, t1);
	return (true);
}

static inline t_hit	do_intersect(t_ray ray, t_hittable *obj)
{
	t_hit	hit;

	hit.object = obj;
	hit.intersection = false;
	hit.t = RAY_T_MAX;
	hit.type = obj->type;
	hit.ray = ray;
	hit.normal = (t_v3){0, 0, 0};
	hit.inside = false;
	hit.h_point = (t_v3){0, 0, 0};
	hit.h_point_obj_coord = (t_v3){0, 0, 0};
	hit.acne_p = (t_v3){0, 0, 0};
	if (obj->type == e_hit_sphere)
		intersect_sphere(&hit, obj, ray);
	else if (obj->type == e_hit_sphere_spec)
		intersect_tr_sphere(&hit, obj, ray);
	else if (obj->type == e_hit_plane)
		intersect_plane(&hit, obj, ray);
	else if (obj->type == e_hit_cylinder)
		intersect_cylinder(&hit, obj, ray);
	return (hit);
}

t_hit	get_first_obj_hit(t_scene *scene, t_ray ray, double max, double min)
{
	t_hit		hit;
	t_hit		closest_hit;
	t_hittable	*current_obj;
	size_t		i;

	i = 0;
	closest_hit.intersection = false;
	closest_hit.t = RAY_T_MAX;
	while (i < scene->hittable->length)
	{
		current_obj = (t_hittable *)ft_get_elem(scene->hittable, i);
		hit = do_intersect(ray, current_obj);
		if (((hit.t > min) && (hit.t < max)) && (hit.intersection == true))
		{
			if ((!closest_hit.intersection) || (hit.t < closest_hit.t))
				closest_hit = hit;
		}
		i++;
	}
	return (closest_hit);
}

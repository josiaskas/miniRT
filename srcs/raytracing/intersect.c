/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 18:14:11 by jkasongo         ###   ########.fr       */
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
		*t0 = -0.5f * (terms[1] / terms[0]);
		*t1 = *t0;
	}
	else
	{
		if (terms[1] > 0.0f)
			q = -0.5f * (terms[1] + sqrtf(discriminant));
		else
			q = -0.5f * (terms[1] - sqrtf(discriminant));
		*t0 = q / terms[0];
		*t1 = terms[2] / q;
	}
	if (*t0 > *t1)
		ft_swap(t0, t1);
	return (true);
}

static inline t_hit	*do_intersect(t_ray *ray, t_hittable *obj)
{
	t_hit	*hit;

	hit = (t_hit *)ft_calloc(1, sizeof(t_hit));
	if (hit)
	{
		hit->object = obj;
		hit->intersection = false;
		hit->t = RAY_T_MAX;
		hit->type = obj->type;
		hit->ray = ray;
		hit->normal = (t_v3){0, 0, 0};
		if (obj->type == e_hit_sphere)
			intersect_sphere(hit, obj, ray);
		else if (obj->type == e_hit_plane)
			intersect_plane(hit, obj, ray);
		else if (obj->type == e_hit_cylinder)
			intersect_cylinder(hit, obj, ray);
	}
	return (hit);
}

t_array	*do_intersect_objs(t_scene *scene, t_ray *ray)
{
	t_array		*records;
	t_hittable	*obj;
	t_hit		*hit;
	size_t		i;

	records = ft_new_array();
	if (records)
	{
		i = 0;
		while (i < scene->hittable->length)
		{
			obj = (t_hittable *)ft_get_elem(scene->hittable, i);
			hit = do_intersect(ray, obj);
			if (hit->intersection == true)
				ft_push(records, hit);
			else
				free(hit);
			i++;
		}
	}
	return (records);
}

t_hit	*get_first_obj_hit(t_array *rec, double max, double min)
{
	size_t	i;
	t_hit	*first_hit;
	t_hit	*hit;

	first_hit = NULL;
	i = 0;
	if (!rec)
		return (NULL);
	while (i < rec->length)
	{
		hit = (t_hit *)ft_get_elem(rec, i);
		if (hit->intersection && (hit->t < max) && (hit->t > min))
		{
			first_hit = hit;
			max = hit->t;
		}
		i++;
	}
	return (first_hit);
}

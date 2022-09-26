/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:44:14 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 23:45:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static t_color s_diff_calc(double dot, double distance, t_color c)
{
	t_color diffuse_color;

	diffuse_color = c;
	if (dot < 0)
		dot = 0;
	diffuse_color = color_multi(dot, &diffuse_color);
	if (distance > 1)
		diffuse_color = color_multi((1 / distance), &diffuse_color);
	return (diffuse_color);
}

t_color calc_diffuse_light(t_light *light, t_hit *hit, t_scene *scene)
{
	t_vector to_light_vector;
	t_hit obstacle;
	t_ray *to_light;
	t_color diffuse_color;

	ft_bzero(&obstacle, sizeof(t_hit));
	ft_bzero(&diffuse_color, sizeof(t_color));
	obstacle.intersection = false;
	diffuse_color.a = 1;
	to_light_vector = get_vector_between(&hit->point, &light->origin);
	to_light = build_ray(hit->point, to_light_vector);
	obstacle = do_intersect_objects(scene, to_light, RAY_T_MAX);
	free(to_light);
	if (obstacle.intersection)
		return (diffuse_color);
	to_light_vector = normalize(&to_light_vector);
	diffuse_color = s_diff_calc(ft_dot(&to_light_vector, &hit->normal),
								ft_dot(&to_light_vector, &to_light_vector),
								light->color);
	return (diffuse_color);
}

t_color diffuse_light_sum(t_hit *hit, t_scene *scene)
{
	size_t i;
	t_color sum;
	t_color calc;
	t_light *light;

	i = 0;
	ft_bzero(&sum, sizeof(t_color));
	sum.a = 1;
	while (i < scene->lights->length)
	{
		light = (t_light *)ft_get_elem(scene->lights, i);
		calc = calc_diffuse_light(light, hit, scene);
		sum = color_add(&sum, &calc);
		i++;
	}
	return (sum);
}

t_color shading_light(t_hit *hit, t_scene *scene)
{
	t_color	color;
	//t_color amb_l;
	t_color	diff_l;

	//(void)hit;
	//amb_l = color_multi(scene->ambiant.intensity, &scene->ambiant.color);
	diff_l = diffuse_light_sum(hit, scene);

	color = diff_l;

	return (color);
}
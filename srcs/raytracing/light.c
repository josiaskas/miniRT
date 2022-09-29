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

static inline t_color	ambiant_light(t_hit *hit, t_scene *scene)
{
	t_color		surface_color;
	t_color		light_color;
	t_color		ambiant_light;
	double		reflexion_const;

	light_color = color_multi(scene->ambiant.intensity, &scene->ambiant.color);
	reflexion_const = ((t_hittable *)hit->object)->const_reflex[0];
	surface_color = ((t_hittable *)hit->object)->color;
	if (reflexion_const != 1)
		surface_color = color_multi(reflexion_const, &surface_color);
	ambiant_light = color_multi2(&light_color, &surface_color);
	return (ambiant_light);
}

t_color	shading_light(t_hit *hit, t_scene *scene)
{
	t_color		color;
	t_color		amb_l;
	t_color		sources_l;

	amb_l = ambiant_light(hit, scene);
	sources_l = light_from_sources(hit, scene);
	color = color_add(&amb_l, &sources_l);
	return (color);
}
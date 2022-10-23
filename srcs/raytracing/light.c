/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:44:14 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:58:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static inline t_color	diffuse_light(t_light *l, t_hit *hit, double val[2])
{
	t_color	color;
	double	k;

	k = hit->object->material->diffuse;
	color = v4_multi(val[0] * k, hit->object->color);
	color = hadamar_prod(l->color, color);
	return (color);
}

static inline t_color	spec_light(t_light *light, t_hit *hit, t_v3 light_v)
{
	t_v3	reflect_v;
	t_v3	v;
	double	reflect_dot_eye;
	double	factor;

	v = v3_multi(-1, light_v);
	reflect_v = reflect(&hit->normal, &v);
	reflect_dot_eye = ft_dot(reflect_v, normalize(hit->ray->o));
	if (reflect_dot_eye <= 0)
		return (v4(0, 0, 0, 1));
	factor = pow(reflect_dot_eye, hit->object->material->shininess);
	factor = factor * hit->object->material->specular;
	return (v4_multi(factor, light->color));
}

t_color	lighting(t_scene *scn, t_hit *hit, t_light *light)
{
	t_color	phong[3];
	t_color	color;
	t_v3	to_light;
	double	val[2];

	to_light = v3_sub(light->o, hit->h_point);
	val[1] = v3_norm_2(to_light);
	to_light = normalize(to_light);
	phong[0] = hadamar_prod(hit->object->color, scn->ambiant.color);
	val[0] = ft_dot(to_light, hit->normal);
	phong[1] = v4(0, 0, 0, 1);
	phong[2] = v4(0, 0, 0, 1);
	if (val[0] >= 0)
	{
		phong[1] = diffuse_light(light, hit, val);
		phong[2] = spec_light(light, hit, to_light);
	}
	color = v4_add(v4_add(phong[1], phong[2]), phong[0]);
	return (color);
}


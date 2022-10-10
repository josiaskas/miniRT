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

static inline t_color	diffuse_light(t_light *light, t_hit *hit, double dot)
{
	t_color color;
	double	k;

	if (dot == 0)
		return (v4(0,0,0,1));
	k = hit->object->material->diffuse;
	color = color_multi(dot * k, hit->object->color);
	color = hadamar_prod(light->color, color);
	return (color);
}

static inline t_color spec_light(t_light *light, t_hit *hit, t_v3 to_l)
{
	t_v3	h;
	double	cos_theta;
	double  specular_factor;
	t_color	color;

	h = normalize(v3_add(v3_multi(-1, hit->ray->dir), to_l));
	cos_theta = ft_dot(h, hit->normal);
	specular_factor = pow(cos_theta, hit->object->material->shininess);
	color = color_multi(specular_factor, hit->object->color);
	return (hadamar_prod(light->color, color));
}

inline t_color get_b_phong_l(t_light *light, t_hit *hit, t_v3 to_light)
{
	t_color	diffuse;
	t_color	specular;
	double	dist;
	double	lambertian;

	dist = v3_norm_2(to_light);
	to_light = normalize(to_light);
	lambertian = ft_dot(hit->normal, to_light);
	specular = v4(0,0,0,1);
	if (lambertian < 0)
		lambertian = 0;
	if (lambertian > 0)
		specular = spec_light(light, hit, to_light);
	diffuse = diffuse_light(light, hit, lambertian);
	if (dist > 0)
		color_multi((1.f / dist), diffuse);
	return (color_add(diffuse, specular));
}

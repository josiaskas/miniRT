/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:44:14 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/23 23:45:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static inline t_color	s_diff_c(double dot, t_color *light, t_hittable *o)
{
	t_color diffuse_color;

	if (dot < 0)
		dot = 0;
	diffuse_color = color_multi(dot, &o->color);
	diffuse_color = color_multi(o->const_reflex[1], &diffuse_color);
	diffuse_color = color_multi2(light, &diffuse_color);
	return (diffuse_color);
}

static inline t_color	s_blinn_c(double dot, t_hittable *o, t_color *light)
{
	t_color	ref_spec_color;
	t_color	s_plastic;
	double	specular_factor;

	ft_bzero(&ref_spec_color, sizeof(t_color));
	if (dot <= 0)
		return (ref_spec_color);
	specular_factor = pow(dot, 48);
	s_plastic  = color_multi((1 - o->plasticity), &o->color);
	s_plastic.r += o->plasticity;
	s_plastic.g += o->plasticity;
	s_plastic.b += o->plasticity;
	s_plastic = color_multi(o->const_reflex[2], &s_plastic);
	s_plastic = color_multi(specular_factor, &s_plastic);
	ref_spec_color = color_multi2(light, &s_plastic);
	return (ref_spec_color);
}

static inline t_color	calc_light_cont(t_vector *to_l, t_hit *hit, t_light *l)
{
	t_color	c[3];
	double	dot[2];
	double	distance2;
	t_vector h;

	ft_bzero(&c[1], sizeof (t_color));
	dot[0] = ft_dot(to_l, &hit->normal);
	distance2 = vector_norm_2(to_l);
	c[0] = s_diff_c(dot[0], &l->color, hit->object);
	c[2] = color_add(&c[0], &c[1]);
	if (distance2 > 1)
		c[2] = color_multi((1 / distance2), &c[2]);
	h = multiply_vector(-1, &hit->ray->dir);
	h = add_vector(&h, to_l);
	h = normalize(&h);
	dot[1] = ft_dot(&h, &hit->normal);
	c[1] = s_blinn_c(dot[1], hit->object, &l->color);
	c[2] = color_add(&c[0], &c[1]);
	return (c[2]);
}

static inline t_color	calc_d_r(t_light *l, t_hit *hit, t_scene *scn)
{
	t_vector	to_light_vector;
	t_hit		obstacle;
	t_ray		*to_light;
	t_color		color;

	ft_bzero(&obstacle, sizeof(t_hit));
	ft_bzero(&color, sizeof(t_color));
	color.a = 1;
	obstacle.intersection = false;
	to_light_vector = get_vector_between(&hit->point, &l->origin);
	to_light_vector = normalize(&to_light_vector);
	to_light = build_ray(hit->point, to_light_vector);
	obstacle = do_intersect_objects(scn, to_light, vector_norm(&to_light_vector));
	free(to_light);
	if (obstacle.intersection)
		return (color);
	color = calc_light_cont(&to_light_vector, hit, l);
	return (color);
}

inline t_color light_from_sources(t_hit *hit, t_scene *scene)
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
		calc = calc_d_r(light, hit, scene);
		sum = color_add(&sum, &calc);
		i++;
	}
	return (sum);
}

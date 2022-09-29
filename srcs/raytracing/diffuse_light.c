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
	double	n_phong;

	n_phong = 48.0f;
	ref_spec_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	ref_spec_color.a = 1;
	if (dot <= 0.f)
		return (ref_spec_color);
	specular_factor = pow(dot, n_phong);
	s_plastic  = color_multi(o->plasticity, &o->color);
	s_plastic.r += (1 - o->plasticity);
	s_plastic.g += (1 - o->plasticity);
	s_plastic.b += (1 - o->plasticity);
	s_plastic = color_multi(o->const_reflex[2], &s_plastic);
	s_plastic = color_multi(specular_factor, &s_plastic);
	ref_spec_color = color_multi2(light, &s_plastic);
	return (ref_spec_color);
}

static inline t_color	calc_light_cont(t_vector to_l, t_hit *hit, t_light *l, double d)
{
	t_color	c[3];
	double	alpha;
	double	theta;
	t_vector h;

	alpha = ft_dot(&to_l, &hit->normal);
	c[0] = s_diff_c(alpha, &l->color, hit->object);
	h = multiply_vector(-1, &hit->ray->dir);
	h = add_vector(&h, &to_l);
	h = normalize(&h);
	theta = ft_dot(&h, &hit->normal);
	c[1] = s_blinn_c(theta, hit->object, &l->color);
	if (d > 1)
		c[2] = color_multi((1 / (d * d)), &c[2]);
	c[2] = color_add(&c[0], &c[1]);
	return (c[2]);
}

static inline t_color	calc_d_r(t_light *l, t_hit *hit, t_scene *scn)
{
	t_vector	t_l_dir;
	t_hit		obstacle;
	t_ray		*t_l_ray;
	double		d;

	ft_bzero(&obstacle, sizeof(t_hit));
	obstacle.intersection = false;
	t_l_dir = get_vector_between(&hit->point, &l->origin);
	d = vector_norm(&t_l_dir);
	t_l_dir = normalize(&t_l_dir);
	t_l_ray = build_ray(hit->point, t_l_dir);
	obstacle = do_intersect_objects(scn, t_l_ray, d);
	free(t_l_ray);
	if (obstacle.intersection)
		return (vec4(0.0f, 0.0f, 0.0f, 1.0f));
	return (calc_light_cont(t_l_dir, hit, l, d));
}

inline t_color light_from_sources(t_hit *hit, t_scene *scene)
{
	size_t	i;
	t_color	sum;
	t_color calc;
	t_light *light;

	i = 0;
	sum = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	while (i < scene->lights->length)
	{
		light = (t_light *)ft_get_elem(scene->lights, i);
		calc = calc_d_r(light, hit, scene);
		sum = color_add(&sum, &calc);
		i++;
	}
	return (sum);
}

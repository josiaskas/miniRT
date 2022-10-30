#ifndef LIGHT_H
# define LIGHT_H

# include "raytrace.h"

static inline t_color	diffuse_light(t_light *l, t_hit *hit, float val[2])
{
	t_color	color;
	float	k;

	k = hit->object->material->diffuse;
	color = v4_multi(val[0] * k, hit->object->color);
	color = hadamar_prod(l->color, color);
	return (color);
}

static inline t_color	spec_light(t_light *light, t_hit *hit, t_v3 light_v)
{
	t_v3	reflect_v;
	t_v3	v;
	float	reflect_dot_eye;
	float	factor;

	v = v3_multi(-1.0f, light_v);
	reflect_v = reflect(&hit->normal, &v);
	reflect_dot_eye = ft_dot(reflect_v, normalize(hit->ray->o));
	if (reflect_dot_eye <= 0)
		return (v4(0.0f, 0.0f, 0.0f, 1.0f));
	factor = powf(reflect_dot_eye, hit->object->material->shininess);
	factor = factor * hit->object->material->specular;
	return (v4_multi(factor, light->color));
}

static inline bool	is_shadowed(t_scene *world, t_v3 to_l, t_point p, float d)
{
	t_ray	*shadow_ray;
	t_array	*records;
	t_hit	*found;
	bool	in_shadow;

	in_shadow = false;
	found = NULL;
	shadow_ray = build_ray(p, to_l);
	records = do_intersect_objs(world, shadow_ray, true);
	found = get_first_obj_hit(records, d, 0);
	if (found != NULL)
		in_shadow = true;
	ft_free_d_array(records);
	free(shadow_ray);
	return (in_shadow);
}

t_color	lighting(t_scene *scn, t_hit *hit, t_light *light)
{
	t_color	phong[3];
	t_color	color;
	t_v3	to_light;
	float	val[2];

	to_light = v3_sub(light->o, hit->h_point);
	val[1] = v3_norm_2(to_light);
	to_light = normalize(to_light);
	phong[0] = hadamar_prod(hit->object->color, scn->ambiant.color);
	if (is_shadowed(scn, to_light, hit->over_p, val[1]))
		return (phong[0]);
	val[0] = ft_dot(to_light, hit->normal);
	phong[1] = v4(0.0f, 0.0f, 0.0f, 1.0f);
	phong[2] = v4(0.0f, 0.0f, 0.0f, 1.0f);
	if (val[0] >= 0)
	{
		phong[1] = diffuse_light(light, hit, val);
		phong[2] = spec_light(light, hit, to_light);
	}
	color = v4_add(v4_add(phong[1], phong[2]), phong[0]);
	return (color);
}

#endif

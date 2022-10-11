/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/29 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "ray.h"
# include "color.h"
# include "transformation.h"
# include <stdio.h>
# define RAY_T_MIN 0.000001f
# define RAY_T_MAX 1.0e30f
# define W_HEIGHT 720
# define W_WIDTH 1280

typedef struct s_light
{
	t_point	o;
	double	cd;
	t_color	color;
}	t_light;

typedef struct s_ambiant_light
{
	double		intensity;
	t_color		color;
}	t_ambiant;

typedef struct s_scene
{
	t_array		*hittable;
	t_array		*lights;
	t_array		*cameras;
	t_cam		*selected_camera;
	t_ambiant	ambiant;
	t_array		*materials;
}	t_scene;

t_scene	*init_scene(void);
void	free_scene(t_scene *scene);
t_cam	*build_camera(t_point origin, t_v3 dir, double angle, double n);

bool	build_sphere(t_scene *scene, t_point origin, double r, t_v3 v_color);
bool	build_plan(t_scene *scene, t_point p, t_v3 normal, t_v3 v_color);
bool	build_cy(t_scene *scene, t_point p, t_v3 dir, t_v3 v_color, double t[]);
bool	bld_t(t_scene *scene, t_point p1, t_point p2, t_point p3, t_v3 v_color);

t_hit	do_intersect_objects(t_scene *scene, t_ray *ray, double max_time);
t_color	do_tracing(t_scene *scene, t_ray *ray, double max_time, double deep);
void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray);
void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray);
bool	transform_sphere(t_hittable *sphere, t_v3 tr, t_v3 ang, t_v3 sc);
void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray);
t_color	get_b_phong_l(t_light *light, t_hit *hit, t_v3 to_light);

//t_v3	get_plan_contact_surf_norm(t_hit *hit);
//t_v3	get_sphere_contact_surf_norm(t_hit *hit);
//t_v3	get_cylinder_contact_surf_norm(t_hit *hit);
//t_color	light_from_sources(t_hit *hit, t_scene *scene);
//t_color	shading_light(t_hit *hit, t_scene *scene);

void	ft_swap(double *t0, double *t1);
inline static bool	solve_quad(const double terms[], double *t0, double *t1)
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
			q = -0.5f * (terms[1] + sqrt(discriminant));
		else
			q = -0.5f * (terms[1] - sqrt(discriminant));
		*t0 = q / terms[0];
		*t1 = terms[2] / q;
	}
	if (*t0 > *t1)
		ft_swap(t0, t1);
	return (true);
}

static t_hit	*do_intersect(t_ray *ray, t_hittable *obj)
{
	t_hit	*hit;

	hit = (t_hit *)ft_calloc(1, sizeof (t_hit));
	if (hit)
	{
		hit->object = obj;
		hit->intersection = false;
		hit->t = RAY_T_MAX;
		hit->type = obj->type;
		hit->ray = ray;
		hit->normal = v3(0,0,0);
		if (obj->type == e_hit_sphere)
			intersect_sphere(hit, obj, ray);
//		else if (obj->type == e_hit_plane)
//			intersect_plane(hit, obj, ray);
//		else if (obj->type == e_hit_cylinder)
//			intersect_cylinder(hit, obj, ray);
	}
	return (hit);
}

static inline	t_array	*do_intersect_objs(t_scene *scene, t_ray *ray, bool l)
{
	t_array 	*records;
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
			ft_push(records,hit);
			if ((l == true) && (hit->intersection == true))
				return (records);
			i++;
		}
	}
	return (records);
}

static inline	t_hit	*get_first_obj_hit(t_array *records, double max)
{
	size_t	i;
	double	curr_min;
	t_hit	*first_hit;
	t_hit	*hit;

	curr_min = max;
	first_hit = NULL;
	i = 0;
	if (!records)
		return (NULL);
	while (i < records->length)
	{
		hit = (t_hit *)ft_get_elem(records, i);
		if (hit->intersection == true && (hit->t < curr_min))
		{
			first_hit = hit;
			curr_min = hit->t;
		}
		i++;
	}
	return (first_hit);
}

#endif //RAYTRACE_H

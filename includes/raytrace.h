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
# include "vector.h"
# include "ray.h"
# define RAY_T_MIN 0.00000001f
# define RAY_T_MAX 1.0e30f

typedef enum e_hittable_type
{
	e_hit_sphere,
	e_hit_plane,
	e_hit_triangle,
	e_hit_light,
}	t_hit_type;

typedef enum e_hittable_composition
{
	e_metallic,
	e_plastic,
	e_glass
}	t_composition;

typedef struct s_light
{
	t_point		origin;
	double		cd;
	t_color		color;
}	t_light;

typedef struct s_hittable
{
	t_hit_type	type;
	t_point		origin;
	t_color		color;
	t_vector	conf_vector;
	double		conf_data_1;
	double		conf_data_2;
	double		const_reflex[3];
	double		plasticity;
	double		indice_refraction;
	double		reflectivity;
	double		transparency;
}	t_hittable;

typedef struct s_hit_record
{
	bool		intersection;
	t_hit_type	type;
	t_hittable	*object;
	double		t;
	t_ray		*ray;
	t_point		point;
	t_vector	normal;
}	t_hit;

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
}	t_scene;

t_cam		*build_camera(t_point origin, t_vector dir, double angle, double n);
t_scene		*init_scene(void);
t_hit		do_intersect_objects(t_scene *scene, t_ray *ray, double max_time);
t_color		do_tracing(t_scene *scene, t_ray *ray, double max_time);
bool		intersect_plan_ray(t_ray *ray, t_hittable *plan, double *t);
t_vector	get_plan_contact_surf_norm(t_hit *hit);
bool		intersect_sphere_ray(t_ray *ray, t_hittable *sphere, double *t);
t_vector	get_sphere_contact_surf_norm(t_hit *hit);
t_color		light_from_sources(t_hit *hit, t_scene *scene);
t_color		shading_light(t_hit *hit, t_scene *scene);
void		free_scene(t_scene *scene);

#endif //RAYTRACE_H
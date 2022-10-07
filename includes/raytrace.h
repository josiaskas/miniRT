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
	e_hit_cylinder,
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
	t_point		p1;
	t_point		p2;
	t_point		p3;
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
bool		intersect_sphere_ray(t_ray *ray, t_hittable *sphere, double *t);
bool		intersect_cylinder_ray(t_ray *ray, t_hittable *cylinder, double *t);
t_vector	get_plan_contact_surf_norm(t_hit *hit);
t_vector	get_sphere_contact_surf_norm(t_hit *hit);
t_vector	get_cylinder_contact_surf_norm(t_hit *hit);
t_color		light_from_sources(t_hit *hit, t_scene *scene);
t_color		shading_light(t_hit *hit, t_scene *scene);
void		free_scene(t_scene *scene);

inline static bool	solve_quad(const double terms[], double *t0, double *t1)
{
	double	discriminant;
	double	q;
	double	temp;

	discriminant = (terms[1] * terms[1]) - (4.0f * terms[0] * terms[2]);
	if (discriminant < 0)
		return (false);
	else if (discriminant == 0)
		*t0 = -0.5f * (terms[1] / terms[0]);
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
	{
		temp = *t1;
		*t1 = *t0;
		*t0 = temp;
	}
	return (true);
}

static inline void	color_check_saturation(t_color *color)
{
	if (color->r > 1.0f)
		color->r = 1.0f;
	if (color->g > 1.0f)
		color->g = 1.0f;
	if (color->b > 1.0f)
		color->b = 1.0f;
}

static inline unsigned int	get_vector_trgb(t_color color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	color_check_saturation(&color);
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	a = (unsigned int)(color.a);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

inline t_color	color_multi2(t_color *a, t_color *b)
{
	t_color	m;

	m.r = a->r * b->r;
	m.g = a->g * b->g;
	m.b = a->b * b->b;
	color_check_saturation(&m);
	return (m);
}

#endif //RAYTRACE_H

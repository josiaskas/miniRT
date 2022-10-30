/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:13 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 15:00:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "ray.h"
# include "color.h"
# include "transformation.h"
# include "ray.h"
# include <stdio.h>
# define RAY_T_MIN 0.001f
# define RAY_T_MAX 100000000.0f
# define W_HEIGHT 720
# define W_WIDTH 1280
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

typedef struct s_light
{
	t_point	o;
	float	cd;
	t_color	color;
}	t_light;

typedef struct s_ambiant_light
{
	float		intensity;
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
	t_array		*names;
	int			pix_traced;
}	t_scene;

t_scene	*init_scene(void);
void	free_scene(t_scene *scene);
void	printProgress(int count);

t_cam	*build_camera(t_point origin, t_v3 dir, float fov);
t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up);
bool	update_cam(t_cam *cam, float hsize, float vsize, float fov);

bool	build_sphere(t_scene *scn, t_point o, t_v3 data[3]);
bool	build_plane(t_scene *scene, t_point p, t_v3 normal, t_v3 v_color);
bool	build_cy(t_scene *scene, t_point p, t_v3 dir, t_v3 v_color, float t[]);
bool	bld_t(t_scene *scene, t_point p1, t_point p2, t_point p3, t_v3 v_color);

t_color	color_at(t_scene *world, t_ray *ray);
t_color	get_pixel_clr(t_scene *scene, float x, float y);

//plan
void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray);
bool	transform_plane(t_hittable *plan, t_v3 tr, t_v3 ang, t_v3 sc);

//cylinder
void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray);
//sphere
void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray);
bool	transform_sphere(t_hittable *sphere, t_v3 tr, t_v3 ang, t_v3 sc);

//cylinder
void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray);
bool	transform_cy(t_hittable *cylinder, t_v3 tr, t_v3 ang, t_v3 sc);

void	ft_swap(float *t0, float *t1);
void	swap_array_el(t_array_node *node_a, t_array_node *node_b);

inline static bool	solve_quad(const float terms[], float *t0, float *t1)
{
	float	discriminant;
	float	q;

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

static inline t_hit	*do_intersect(t_ray *ray, t_hittable *obj)
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
		hit->normal = v3(0.0f,0.0f,0.0f);
		if (obj->type == e_hit_sphere)
			intersect_sphere(hit, obj, ray);
		else if (obj->type == e_hit_plane)
			intersect_plane(hit, obj, ray);
		//		else if (obj->type == e_hit_cylinder)
//			intersect_cylinder(hit, obj, ray);
	}
	return (hit);
}

static inline	t_array	*do_intersect_objs(t_scene *scene, t_ray *ray, bool l)
{
	t_array		*records;
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
			if (hit->intersection == true)
			{
				ft_push(records, hit);
				if ((l == true) && (hit->intersection == true))
					return (records);
			}
			else
				free(hit);
			i++;
		}
	}
	return (records);
}

static inline t_hit	*get_first_obj_hit(t_array *rec, float max, float min)
{
	size_t	i;
	float	curr_min;
	t_hit	*first_hit;
	t_hit	*hit;

	curr_min = max;
	first_hit = NULL;
	i = 0;
	if (!rec)
		return (NULL);
	while (i < rec->length)
	{
		hit = (t_hit *)ft_get_elem(rec, i);
		if (hit->intersection && (hit->t < curr_min) && (hit->t > min))
		{
			first_hit = hit;
			curr_min = hit->t;
		}
		i++;
	}
	return (first_hit);
}

#endif

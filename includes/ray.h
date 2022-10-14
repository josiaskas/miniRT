/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/29 16:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vector.h"
# include "color.h"
# include "transformation.h"

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

typedef struct	s_material
{
	double			shininess;
	t_composition	type;
	double			reflexive;
	double			diffuse;
	double			specular;
	char			*name;
}	t_material;

typedef struct s_hittable
{
	t_hit_type	type;
	t_point		o;
	t_point		p1;
	t_point		p2;
	t_point		p3;
	t_m4		tr;
	t_m4		inv_tr;
	t_v3		trans;
	t_v3		scale;
	t_v3		angles;
	double		radius;
	double		h;
	t_v3		dir;
	t_color		color;
	char		*name;
	t_material	*material;
}	t_hittable;


typedef struct s_ray
{
	t_point		o;
	t_v3		dir;
}	t_ray;

typedef struct s_camera
{
	t_point		origin;
	t_v3		dir;
	t_v3		dir_ort;
	double		fov;
	double		aspect_ratio;
	double		near_clp_plane;
	double		far_clp_plane;
	t_v3		trans;
	t_v3		angles;
	double		v_w;
	double		v_h;
	t_v3		u1;
	t_v3		u2;
	t_v3		r_init;
}	t_cam;

typedef struct s_hit_record
{
	bool		intersection;
	t_hit_type	type;
	t_hittable	*object;
	double		t;
	double		t_trace[2];
	t_ray		*ray;
	t_point		h_point;
	t_v3		normal;
	t_v3		r;
}	t_hit;

/*
 * Build the ray with origin and direction vector
 * return a *t_ray to be freed
*/
static inline t_ray	*build_ray(t_point origin, t_v3 direction)
{
	t_ray		*ray;

	ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (ray)
	{
		ray->o = origin;
		ray->dir = direction;
	}
	return (ray);
}

/*
 * return a ray p_view (distance of n from the point) to the scene
 * ray dir is normalized
*/
static inline t_ray	*get_viewport_ray(double x, double y, t_cam *cam)
{
	t_v3	dir;
	t_v3	p_view;
	double	cam_sz;

	cam_sz = cam->near_clp_plane;
	p_view = v3_add(v3_multi(x, cam->u1), v3_multi(y , cam->u2));
	p_view = v3_add(p_view, cam->r_init);
	p_view = v3_add(cam->origin, v3_add(v3_multi(cam_sz, cam->dir), p_view));
	dir = normalize(v3_sub(p_view, cam->origin));
	return (build_ray(p_view, dir));
}

/*
 * Return a Point according to t with a ray, parametric equation.
 * equation is point = ray_origin + (t * ray_dir)
 * ray dir vector need to be normalized to be correct
*/
static inline t_point	get_point_on_ray_at(double t, t_ray *ray)
{
	t_point	a;

	a.x = ray->o.x + (t * ray->dir.x);
	a.y = ray->o.y + (t * ray->dir.y);
	a.z = ray->o.z + (t * ray->dir.z);
	return (a);
}

static inline t_ray	*get_transformed_ray(t_ray *ray, t_m4 transform, t_v3 sp_o)
{
	t_ray	*tr_ray;
	t_v4	o;
	t_v4	dir;
	t_v4	oo;

	o = multiply_m4_v4(transform, v3_to_v4(ray->o));
	oo	= multiply_m4_v4(transform, v3_to_v4(sp_o));
	dir = multiply_m4_v4(transform, v3_to_v4(ray->dir));
	dir = v4_sub(dir, oo);
	tr_ray = build_ray(v3(o.r,o.g,o.b), v3(dir.r,dir.g,dir.b));
	return (tr_ray);
}


#endif //RAY_H

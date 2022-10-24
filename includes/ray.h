/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 14:46:12 by jkasongo         ###   ########.fr       */
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

typedef struct s_material
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
	double	fov;
	double	hsize;
	double	vsize;
	double	half_view;
	double	half_width;
	double	half_height;
	double	pixel_size;
	t_m4	inv_tr;
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
	bool		inside;
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
static inline t_ray	*ray_for_pixel(t_cam *cam, double px, double py)
{
	double	off[4];
	t_v4	v[2];
	t_v3	p[2];
	t_v3	dir;

	off[0] = (px + 0.5) * cam->pixel_size;
	off[1] = (py + 0.5) * cam->pixel_size;
	off[2] = cam->half_width - off[0];
	off[3] = cam->half_height - off[1];
	v[1] = multiply_m4_v4(cam->inv_tr, v4(off[2], off[3], -1, 1));
	v[0] = multiply_m4_v4(cam->inv_tr, v4(0, 0, 0, 1));
	p[1] = v3(v[1].r, v[1].g, v[1].b);
	p[0] = v3(v[0].r, v[0].g, v[0].b);
	dir = normalize(v3_sub(p[1], p[0]));
	return (build_ray(p[0], dir));
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
	oo = multiply_m4_v4(transform, v3_to_v4(sp_o));
	dir = multiply_m4_v4(transform, v3_to_v4(ray->dir));
	dir = v4_sub(dir, oo);
	tr_ray = build_ray(v3(o.r, o.g, o.b), v3(dir.r, dir.g, dir.b));
	return (tr_ray);
}

#endif

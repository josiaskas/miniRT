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
	double		radius;
	double		h;
	t_v3		dir;
	t_color		color;
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

// return the position vector of the pixel on the viewport
static inline t_point	get_pixel_position_p(double x, double y, t_cam *cam)
{
	t_v3	on_screen;
	t_v3	v;
	t_v3	cam_to_screen;
	t_point	p_view;

	v = v3_add(v3_multi(x, cam->u1), v3_multi(y, cam->u2));
	on_screen = v3_add(v, cam->r_init);
	cam_to_screen = v3_multi(cam->near_clp_plane, cam->dir);
	p_view = v3_add(cam->origin, v3_add(cam_to_screen, on_screen));
	return (p_view);
}

/*
 * return a ray p_view (distance of n from the point) to the scene
 * ray dir is normalized
*/
static inline t_ray	*get_viewport_ray(double x, double y, t_cam *cam)
{
	t_point	p_view;
	t_v3	dir;

	p_view = get_pixel_position_p(x, y, cam);
	dir = normalize(v3_sub(p_view, cam->origin));
	return (build_ray(cam->origin, dir));
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

// new ray to be freed in the object space
static inline t_ray	*get_obj_space_ray(t_ray *ray, t_hittable *obj)
{
	t_v4	ro;
	t_v4	o_in_obj;
	t_v4	dir;
	t_ray	*ray_obj;

	ro = multiply_m4_v4(obj->inv_tr, v3_to_v4(ray->o));
	o_in_obj = multiply_m4_v4(obj->inv_tr, v4(0,0,0,0));
	dir = multiply_m4_v4(obj->inv_tr, v3_to_v4(ray->dir));
	dir = v4_sub(dir, o_in_obj);
	ray_obj = build_ray(v3(ro.r,ro.g,ro.b), v3(dir.r,dir.g,dir.b));
	return (ray_obj);
}


#endif //RAY_H

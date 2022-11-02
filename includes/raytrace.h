/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:13 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 19:35:47 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "ray.h"
# include "color.h"
# include "transformation.h"
# include <stdio.h>
# define RAY_T_MIN 0.0015f
# define RAY_T_MAX 100000000.0f
# define W_HEIGHT 720
# define W_WIDTH 1280
# define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
# define PBWIDTH 60

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
	t_array		*names;
	int			pix_traced;
}	t_scene;

t_scene	*init_scene(void);
void	free_scene(t_scene *scene);
void	printProgress(int count);

t_cam	*build_camera(t_point origin, t_v3 dir, float fov);
t_m4	view_transform(t_v3 from, t_v3 to, t_v3 up);
bool	update_cam(t_cam *cam, float hsize, float vsize, float fov);
bool	bld_t(t_scene *scene, t_point p1, t_point p2, t_point p3, t_v3 v_color);

t_color	color_at(t_scene *world, t_ray *ray);
t_color	get_pixel_clr(t_scene *scene, float x, float y);
void	ft_compute_hit(t_hit *hit);
t_color	lighting(t_scene *scn, t_hit *hit, t_light *light);
bool	is_shadowed(t_scene *world, t_v3 to_light, const t_point p, float dist);


//sphere
bool	build_sphere(t_scene *scn, t_point o, t_v3 data[3]);
void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray *ray);
void	compute_sphere_hit(t_hit *hit);
bool	transform_sphere(t_hittable *sphere, t_v3 tr, t_v3 ang, t_v3 sc);

//cylinder
bool	build_cy(t_scene *scn, t_point o, t_v3 data[5], float h);
void	intersect_cylinder(t_hit *hit, t_hittable *cyl, t_ray *ray);
void	compute_cylinder_hit(t_hit *hit);
bool	transform_cy(t_hittable *cylinder, t_v3 tr, t_v3 ang, t_v3 sc);

// plan
bool	build_plane(t_scene *scene, t_point p, t_v3 normal, t_v3 v_color);
void	intersect_plane(t_hit *hit, t_hittable *plan, t_ray *ray);
bool	transform_plane(t_hittable *plan, t_v3 tr, t_v3 ang, t_v3 sc);

bool	solve_quad(const float terms[], float *t0, float *t1);
t_array	*do_intersect_objs(t_scene *scene, t_ray *ray, bool l);
t_hit	*get_first_obj_hit(t_array *rec, const float max, float min);

#endif

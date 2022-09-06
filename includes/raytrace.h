/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "vector.h"

typedef enum e_hittable_type
{
	e_hit_sphere,
	e_hit_plane,
	e_hit_triangle,
	e_hit_light,
}	t_hit_type;

typedef	struct s_camera
{
	t_point		origin;
	t_vector	dir;
	t_vector	dir_ort;
	double		fov;
	double		near_clp_plane;
	double		far_clp_plane;
	double		v_w;
	double		v_h;
	t_vector	u1;
	t_vector	u2;
	t_vector	r_init;
}	t_cam;

typedef struct s_hittable
{
	t_hit_type	type;
	t_point		origin;
	t_color		color;
	t_vector	conf_vector;
	double		conf_data_1;
	double		conf_data_2;
}	t_hittable;

typedef struct s_scene
{
	t_array		*hittable;
	t_array		*lights;
	t_array		*cameras;
	int			viewport_pixel_w;
	int			viewport_pixel_h;
	double		aspect_ratio;
	t_cam		*selected_camera;
}	t_scene;


t_cam	*build_camera(t_point origin, t_vector dir, double angle, double n);
t_scene	*init_scene();

t_ray	*get_viewport_ray(double x, double y, t_cam *cam);

void	free_scene(t_scene *scene);
#endif //RAYTRACE_H


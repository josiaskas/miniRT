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
	e_hit_light,
}	t_hit_type;

typedef	struct s_camera
{
	t_point	origin;
	t_point	orientation;
	double	h_angle;
}	t_cam;

typedef struct s_scene
{
	t_array		*hittable;
	t_array		*lights;
	t_array		*cameras;
}	t_scene;

typedef struct s_hittable
{
	t_hit_type	type;
	t_point		origin;
	t_color		color;
	t_vector	conf_vector;
	double		conf_data_1;
	double		conf_data_2;
}	t_hittable;

t_cam	*build_camera(t_point origin, t_vector dir, double angle);
void	free_cam(t_cam *cam);
t_scene	*init_scene();
void	free_scene(t_scene *scene);
#endif //RAYTRACE_H


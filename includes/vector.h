/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/30 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "../libft/libft.h"
# include <math.h>

typedef struct s_vector
{
	double x;
	double y;
	double z;
}	t_vector;

typedef struct s_vector4
{
	double a;
	double r;
	double g;
	double b;
}	t_vector4;

typedef t_vector t_point;
typedef t_vector4 t_color;

typedef struct s_repere
{
	t_vector	rep_x;
	t_vector	rep_y;
	t_vector	rep_z;
}	t_repere;

typedef struct s_ray
{
	t_point		origin;
	t_vector	dir;
}	t_ray;

double			vector_norm(t_vector *v);
double			vector_norm_2(t_vector *v);
t_vector		add_vector(t_vector *a, t_vector *b);
t_vector		substract_vector(t_vector *a, t_vector *b);
t_vector		multiply_vector(double i, t_vector *v);
t_vector		normalize(t_vector *v);
double			ft_dot(t_vector *u, t_vector *v);
t_vector		ft_cross(t_vector *u, t_vector *v);
t_vector		make_vector(double i, double j, double k);

t_vector		get_vector_between(t_point *a, t_point *b);
double			get_distance_b_p(t_point *a, t_point *b);

t_vector4		normalize_vec4(t_vector4 *v);
t_vector4		clamp_color_vect(t_color *v);
unsigned int	get_vector_trgb(t_color color);

t_ray			*build_ray(t_point origin, t_vector direction);
t_point			get_point_on_ray_at(double t, t_ray *ray);

#endif //VECTOR_H

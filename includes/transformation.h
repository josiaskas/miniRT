/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/06 11:26:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H
# include <math.h>
# include "vector.h"

typedef struct s_vector4_4 {
	double	m0[4];
	double	m1[4];
	double	m2[4];
	double	m3[4];
}	t_vector4_4;

static inline t_vector4	multiply_t4_v4(t_vector4_4 *m, t_vector4 *c)
{
	t_vector4	r;

	r.r = (m->m0[0] * c->r) + (m->m0[1] * c->g) + (m->m0[2] * c->b)
		+ (m->m0[3] * c->a);
	r.g = (m->m1[0] * c->r) + (m->m1[1] * c->g) + (m->m1[2] * c->b)
		  + (m->m1[3] * c->a);
	r.b = (m->m2[0] * c->r) + (m->m2[1] * c->g) + (m->m2[2] * c->b)
		  + (m->m2[3] * c->a);
	r.a = (m->m3[0] * c->r) + (m->m3[1] * c->g) + (m->m3[2] * c->b)
		  + (m->m3[3] * c->a);
	return (r);
}

static inline t_vector4	translate_m(t_vector4 *with, t_vector4 *src)
{
	t_vector4_4	translation_matrix;

	ft_bzero(&translation_matrix, sizeof(t_vector4_4));
	translation_matrix.m0[0] = 1;
	translation_matrix.m0[3] = with->r;
	translation_matrix.m1[1] = 1;
	translation_matrix.m1[3] = with->b;
	translation_matrix.m2[2] = 1;
	translation_matrix.m2[3] = with->g;
	translation_matrix.m3[3] = 1;
	return (multiply_t4_v4(&translation_matrix, src));
}

static inline t_vector4	homothetie_m(t_vector4 *with, t_vector4 *src)
{
	t_vector4_4	homo_matrix;

	ft_bzero(&homo_matrix, sizeof(t_vector4_4));
	homo_matrix.m0[0] = with->r;
	homo_matrix.m1[1] = with->b;
	homo_matrix.m2[2] = with->g;
	homo_matrix.m3[3] = 1;
	return (multiply_t4_v4(&homo_matrix, src));
}

static inline t_vector4 rotation_xy(double ang, t_vector4 *src)
{
	t_vector4_4	rot_matrix;
	double cos_val;
	double sin_val;

	ft_bzero(&rot_matrix, sizeof(t_vector4_4));
	cos_val = cos(ang);
	sin_val = sin(ang);
	rot_matrix.m0[0] = cos_val;
	rot_matrix.m0[1] = -sin_val;
	rot_matrix.m1[0] = sin_val;
	rot_matrix.m1[1] = cos_val;
	rot_matrix.m2[2] = 1;
	rot_matrix.m3[3] = 1;
	return (multiply_t4_v4(&rot_matrix, src));
}

static inline t_vector4 rotation_yz(double ang, t_vector4 *src)
{
	t_vector4_4	rot_matrix;
	double cos_val;
	double sin_val;

	ft_bzero(&rot_matrix, sizeof(t_vector4_4));
	cos_val = cos(ang);
	sin_val = sin(ang);
	rot_matrix.m0[0] = 1;
	rot_matrix.m1[1] = cos_val;
	rot_matrix.m1[2] = -sin_val;
	rot_matrix.m2[1] = sin_val;
	rot_matrix.m2[2] = cos_val;
	rot_matrix.m3[3] = 1;
	return (multiply_t4_v4(&rot_matrix, src));
}

#endif //TRANSFORMATION_H

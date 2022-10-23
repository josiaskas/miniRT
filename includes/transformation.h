/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/23 15:00:25 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H
# include "vector.h"

typedef enum e_rotation_type
{
	e_rot_on_x,
	e_rot_on_y,
	e_rot_on_z,
}	t_rotation_type;

t_m4	scale_m(t_v3 with);
t_m4	rotation_z(double ang);
t_m4	rotation_x(double ang);
t_m4	rotation_y(double ang);
t_m4	get_identity_matrix(void);
t_m4	get_transposed(t_m4	*matrix);
t_m4	*get_inverse(t_m4 matrix);
t_m4	copy_matrix(t_m4 *matrix);

static inline void	init_m4(t_m4 *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			a->data[i][j] = 0;
			j++;
		}
		i++;
	}
}

static inline t_m4	m4_multi(t_m4 a, t_m4 b)
{
	int		i;
	int		j;
	int		k;
	t_m4	r;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			r.data[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				r.data[i][j] += a.data[i][k] * b.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (r);
}

static inline t_m4	translate_m(t_v3 with)
{
	t_m4	tr_matrix;

	tr_matrix = get_identity_matrix();
	tr_matrix.data[0][3] = with.x;
	tr_matrix.data[1][3] = with.y;
	tr_matrix.data[2][3] = with.z;
	return (tr_matrix);
}

/*
 * return the transformation matrix or the inverse transformation matrix
 * trans:translation vector, angles: vector, scaling vector, is inverse check
*/
static inline t_m4	get_tr_matrix(t_v3 trans, t_v3 angles, t_v3 sc, bool inv)
{
	t_m4	tr;

	if (inv == false)
	{
		tr = translate_m(trans);
		if (angles.z != 0)
			tr = m4_multi(tr, rotation_z(angles.z));
		if (angles.y != 0)
			tr = m4_multi(tr, rotation_y(angles.y));
		if (angles.x != 0)
			tr = m4_multi(tr, rotation_x(angles.x));
		tr = m4_multi(tr, scale_m(sc));
		return (tr);
	}
	tr = scale_m(inverse_comp(sc));
	if (angles.x != 0)
		tr = m4_multi(tr, rotation_x(-1 * angles.x));
	if (angles.y != 0)
		tr = m4_multi(tr, rotation_y(-1 * angles.y));
	if (angles.z != 0)
		tr = m4_multi(tr, rotation_z(-1 * angles.z));
	tr = m4_multi(tr, translate_m(v3_multi(-1,trans)));
	return (tr);
}

static inline t_v4	multiply_m4_v4(t_m4 m, t_v4 c)
{
	t_v4	r;

	r.r = (m.data[0][0] * c.r) + (m.data[0][1] * c.g) + (m.data[0][2] * c.b)
		+ (m.data[0][3] * c.a);
	r.g = (m.data[1][0] * c.r) + (m.data[1][1] * c.g) + (m.data[1][2] * c.b)
		+ (m.data[1][3] * c.a);
	r.b = (m.data[2][0] * c.r) + (m.data[2][1] * c.g) + (m.data[2][2] * c.b)
		+ (m.data[2][3] * c.a);
	r.a = (m.data[3][0] * c.r) + (m.data[3][1] * c.g) + (m.data[3][2] * c.b)
		+ (m.data[3][3] * c.a);
	return (r);
}

#endif

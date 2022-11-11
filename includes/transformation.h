/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:00:24 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 18:39:15 by jkasongo         ###   ########.fr       */
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

void	init_m4(t_m4 *a);
t_m4	translate_m(t_v3 with);
t_m4	scale_m(t_v3 with);
t_m4	rotation_z(double ang);
t_m4	rotation_x(double ang);
t_m4	rotation_y(double ang);
t_m4	get_identity_matrix(void);
t_m4	get_transposed(t_m4	*matrix);
t_m4	get_inverse(t_m4 matrix);
t_m4	copy_matrix(t_m4 *matrix);
t_v4	multiply_m4_v4(t_m4 m, t_v4 c);
t_m4	m4_multi(t_m4 a, t_m4 b);
t_m4	quaternion_z(double q0, double q1, double q2, double q3);
/*
 * return the transformation matrix or the inverse transformation matrix
 * trans:translation vector, angles: vector, scaling vector, is inverse check
*/
t_m4	get_tr_matrix(t_v3 trans, t_v3 angles, t_v3 sc, bool inv);


#endif

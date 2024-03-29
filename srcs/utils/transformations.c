/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:30:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 09:29:37 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_m4	translate_m(t_v3 with)
{
	t_m4	tr_matrix;

	tr_matrix = get_identity_matrix();
	tr_matrix.data[0][3] = with.x;
	tr_matrix.data[1][3] = with.y;
	tr_matrix.data[2][3] = with.z;
	return (tr_matrix);
}

t_m4	scale_m(t_v3 with)
{
	t_m4	homothetie;

	homothetie = get_identity_matrix();
	homothetie.data[0][0] = with.x;
	homothetie.data[1][1] = with.y;
	homothetie.data[2][2] = with.z;
	return (homothetie);
}

t_m4	rotation_z(double ang)
{
	t_m4	rot_matrix;
	double	cos_val;
	double	sin_val;

	if (ang == 0)
		return (get_identity_matrix());
	init_m4(&rot_matrix);
	cos_val = cos(ang);
	sin_val = sin(ang);
	rot_matrix.data[0][0] = cos_val;
	rot_matrix.data[0][1] = -sin_val;
	rot_matrix.data[1][0] = sin_val;
	rot_matrix.data[1][1] = cos_val;
	rot_matrix.data[2][2] = 1;
	rot_matrix.data[3][3] = 1;
	return (rot_matrix);
}

t_m4	rotation_x(double ang)
{
	t_m4	rot_matrix;
	double	cos_val;
	double	sin_val;

	if (ang == 0)
		return (get_identity_matrix());
	init_m4(&rot_matrix);
	cos_val = cos(ang);
	sin_val = sin(ang);
	rot_matrix.data[0][0] = 1;
	rot_matrix.data[1][1] = cos_val;
	rot_matrix.data[1][2] = -sin_val;
	rot_matrix.data[2][1] = sin_val;
	rot_matrix.data[2][2] = cos_val;
	rot_matrix.data[3][3] = 1;
	return (rot_matrix);
}

t_m4	rotation_y(double ang)
{
	t_m4	rot_matrix;
	double	cos_val;
	double	sin_val;

	if (ang == 0)
		return (get_identity_matrix());
	init_m4(&rot_matrix);
	cos_val = cos(ang);
	sin_val = sin(ang);
	rot_matrix.data[0][0] = cos_val;
	rot_matrix.data[0][2] = sin_val;
	rot_matrix.data[1][1] = 1;
	rot_matrix.data[2][0] = -sin_val;
	rot_matrix.data[2][2] = cos_val;
	rot_matrix.data[3][3] = 1;
	return (rot_matrix);
}

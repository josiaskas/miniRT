/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:30:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 09:27:57 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

static inline t_m4	*inv_s(double a[4][4], double s[6], double c[6], double d)
{
	t_m4	*i;

	i = ft_calloc(1, sizeof(t_m4));
	if (i)
	{
		i->data[0][0] = (a[1][1] * c[5] - a[1][2] * c[4] + a[1][3] * c[3]) * d;
		i->data[0][1] = (-a[0][1] * c[5] + a[0][2] * c[4] - a[0][3] * c[3]) * d;
		i->data[0][2] = (a[3][1] * s[5] - a[3][2] * s[4] + a[3][3] * s[3]) * d;
		i->data[0][3] = (-a[2][1] * s[5] + a[2][2] * s[4] - a[2][3] * s[3]) * d;
		i->data[1][0] = (-a[1][0] * c[5] + a[1][2] * c[2] - a[1][3] * c[1]) * d;
		i->data[1][1] = (a[0][0] * c[5] - a[0][2] * c[2] + a[0][3] * c[1]) * d;
		i->data[1][2] = (-a[3][0] * s[5] + a[3][2] * s[2] - a[3][3] * s[1]) * d;
		i->data[1][3] = (a[2][0] * s[5] - a[2][2] * s[2] + a[2][3] * s[1]) * d;
		i->data[2][0] = (a[1][0] * c[4] - a[1][1] * c[2] + a[1][3] * c[0]) * d;
		i->data[2][1] = (-a[0][0] * c[4] + a[0][1] * c[2] - a[0][3] * c[0]) * d;
		i->data[2][2] = (a[3][0] * s[4] - a[3][1] * s[2] + a[3][3] * s[0]) * d;
		i->data[2][3] = (-a[2][0] * s[4] + a[2][1] * s[2] - a[2][3] * s[0]) * d;
		i->data[3][0] = (-a[1][0] * c[3] + a[1][1] * c[1] - a[1][2] * c[0]) * d;
		i->data[3][1] = (a[0][0] * c[3] - a[0][1] * c[1] + a[0][2] * c[0]) * d;
		i->data[3][2] = (-a[3][0] * s[3] + a[3][1] * s[1] - a[3][2] * s[0]) * d;
		i->data[3][3] = (a[2][0] * s[3] - a[2][1] * s[1] + a[2][2] * s[0]) * d;
	}
	return (i);
}

inline t_m4	get_transposed(t_m4	*matrix)
{
	int		i;
	int		j;
	t_m4	transpose;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			transpose.data[i][j] = matrix->data[j][i];
			j++;
		}
		i++;
	}
	return (transpose);
}

static inline t_m4	*inverse(t_m4 m)
{
	double	s[6];
	double	c[6];
	double	det;

	s[1] = m.data[0][0] * m.data[1][2] - m.data[1][0] * m.data[0][2];
	s[0] = m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1];
	s[2] = m.data[0][0] * m.data[1][3] - m.data[1][0] * m.data[0][3];
	s[3] = m.data[0][1] * m.data[1][2] - m.data[1][1] * m.data[0][2];
	s[4] = m.data[0][1] * m.data[1][3] - m.data[1][1] * m.data[0][3];
	s[5] = m.data[0][2] * m.data[1][3] - m.data[1][2] * m.data[0][3];
	c[4] = m.data[2][1] * m.data[3][3] - m.data[3][1] * m.data[2][3];
	c[5] = m.data[2][2] * m.data[3][3] - m.data[3][2] * m.data[2][3];
	c[3] = m.data[2][1] * m.data[3][2] - m.data[3][1] * m.data[2][2];
	c[2] = m.data[2][0] * m.data[3][3] - m.data[3][0] * m.data[2][3];
	c[1] = m.data[2][0] * m.data[3][2] - m.data[3][0] * m.data[2][2];
	c[0] = m.data[2][0] * m.data[3][1] - m.data[3][0] * m.data[2][1];
	det = s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2]
		- s[4] * c[1] + s[5] * c[0];
	if (det == 0)
		return (NULL);
	det = (1.0f / det);
	return (inv_s(m.data, s, c, det));
}

t_m4	copy_matrix(t_m4 *matrix)
{
	int		i;
	int		j;
	t_m4	copy;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			copy.data[i][j] = matrix->data[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}

inline t_m4	get_inverse(t_m4 matrix)
{
	t_m4	inv;
	t_m4	*m;

	m = inverse(matrix);
	if (m != NULL)
		inv = copy_matrix(m);
	else
		inv = get_identity_matrix();
	free(m);
	return (inv);
}

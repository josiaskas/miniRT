/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:59:08 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/02 10:00:03 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

t_m4	quaternion_z(float q0, float q1, float q2, float q3)
{
	t_m4	q;
	float	qs[4];

	qs[0] = powf(q0, 2);
	qs[1] = powf(q1, 2);
	qs[2] = powf(q2, 2);
	qs[3] = powf(q3, 2);
	q.data[0][0] = qs[0] + qs[1] - qs[2] - qs[3];
	q.data[0][1] = 2.0f * ((q1 * q2) - (q0 * q3));
	q.data[0][2] = 2.0f * ((q1 * q3) + (q0 * q2));
	q.data[0][3] = 0;
	q.data[1][0] =  2.0f * ((q2 * q1) + (q0 * q3));
	q.data[1][1] = qs[0] - qs[1] + qs[2] - qs[3];
	q.data[1][2] = 2.0f * ((q2 * q3) - (q0 * q1));
	q.data[1][3] = 0;
	q.data[1][0] =  2.0f * ((q3 * q1) - (q0 * q2));
	q.data[1][1] = 2.0f * ((q3 * q2) + (q0 * q1));
	q.data[1][2] = qs[0] - qs[1] - qs[2] + qs[3];
	q.data[1][3] = 1;
	return (q);
}

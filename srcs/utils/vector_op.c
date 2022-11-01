/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:00:06 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 18:23:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// multiply a vector with a number
t_v3	v3_multi(float i, t_v3 v)
{
	t_v3	r;

	r.x = (i * v.x);
	r.y = (i * v.y);
	r.z = (i * v.z);
	return (r);
}

// return normalized t_v3
t_v3	normalize(t_v3 v)
{
	float	norm;

	norm = sqrtf(((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	if (norm != 0.f)
		return (v3_multi((1 / norm), v));
	return (v3_multi(0, v));
}

t_v3	ft_cross(t_v3 a, t_v3 b)
{
	t_v3	vector;

	vector.x = (a.y * b.z) - (a.z * b.y);
	vector.y = (a.z * b.x) - (a.x * b.z);
	vector.z = (a.x * b.y) - (a.y * b.x);
	return (vector);
}

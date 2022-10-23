/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/22 16:41:22 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// retourne la norme au carré du vecteur
inline double	v3_norm_2(t_v3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

// retourne la norme du vecteur
inline double	v3_norm(t_v3 v)
{
	return (sqrt(v3_norm_2(v)));
}

// addition of two vectors
inline t_v3	v3_add(t_v3 a, t_v3 b)
{
	t_v3	r;

	r.x = (a.x + b.x);
	r.y = (a.y + b.y);
	r.z = (a.z + b.z);
	return (r);
}

inline t_v3	v3_sub(t_v3 a, t_v3 b)
{
	t_v3	r;

	r.x = (a.x - b.x);
	r.y = (a.y - b.y);
	r.z = (a.z - b.z);
	return (r);
}

// return a vector with (1/x, 1/y, 1/z) by checking zeros
inline t_v3	inverse_comp(t_v3 v)
{
	t_v3	i;

	i = v3(0,0,0);
	if (v.x != 0)
		i.x = 1 / v.x;
	if (v.y != 0)
		i.y = 1 / v.y;
	if (v.z != 0)
		i.z = 1 / v.z;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/10 09:29:57 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

inline t_v4	v4_add(t_v4 a, t_v4 b)
{
	t_v4	addition;

	addition.r = a.r + b.r;
	addition.g = a.g + b.g;
	addition.b = a.b + b.b;
	addition.a = a.a + b.a;
	return (addition);
}

inline t_v4	v4_sub(t_v4 a, t_v4 b)
{
	t_v4	sub;

	sub.r = a.r - b.r;
	sub.g = a.g - b.g;
	sub.b = a.b - b.b;
	sub.a = a.a - b.a;
	return (sub);
}

inline	t_v4	v4_multi(double k, t_v4 v)
{
	t_v4	multiplication;

	multiplication.r = k * v.r;
	multiplication.g = k * v.g;
	multiplication.b = k * v.b;
	multiplication.a = k * v.a;
	return (multiplication);
}

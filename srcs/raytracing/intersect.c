/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/05 19:32:39 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

inline void	ft_swap(float *t0, float *t1)
{
	float	temp;

	temp = *t1;
	*t1 = *t0;
	*t0 = temp;
}

inline	void	swap_array_el(t_array_node *node_a, t_array_node *node_b)
{
	void	*temp_content;

	temp_content = node_a->content;
	node_a->content = node_b->content;
	node_b->content = temp_content;
}





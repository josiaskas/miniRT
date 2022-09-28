/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/09/27 11:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

inline void	init_hittable_info(t_hittable *object, t_composition matiere)
{
	object->plasticity = 0.23;
	object->const_reflex[0] = 1;
	object->const_reflex[1] = 1;
	object->const_reflex[2] = 1;
	object->indice_refraction = 1;
	object->reflectivity = 1;
	object->transparency = 0;
	if (matiere == e_glass)
		object->transparency = 0.8;
	if (matiere == e_plastic)
		object->const_reflex[0] = 0.4;
}
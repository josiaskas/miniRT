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
#include <stdio.h>

//static bool is_in_shadow(t_scene *scene, t_hit *hit, t_v3 to_light)
//{
//	t_ray 	*to_l;
//	t_array	*records;
//	bool	in_shadow;
//
//	to_l = build_ray(hit->h_point,normalize(to_light));
//	records = do_intersect_objs(scene, to_l, true);
//	in_shadow = false;
//	if (get_first_obj_hit(records, v3_norm(to_light)) != NULL)
//		in_shadow = true;
//	free(to_l);
//	ft_free_d_array(records);
//	return (in_shadow);
//}

//static inline t_color	reflected_color(int deep, t_scene *scn, t_hit *hit)
//{
//	t_color		color;
//	t_ray		*ref_ray;
//
//	if (deep > 10 || (hit->object->material->reflexive <= RAY_T_MIN))
//		return (v4(0,0,0,1));
//	ref_ray = build_ray(hit->h_point, hit->r);
//	(void)scn;
//	color = v4(0,0,0.5,1);
//	free(ref_ray);
//	color = color_multi(hit->object->material->reflexive, color);
//	return (color);
//}

//static inline t_color shade_hit(t_scene *scn, t_hit *hit)
//{
//	t_color	color;
//	size_t	i;
//	t_light	*light;
//	t_v3	to_light;
//
//	i = 0;
//	color = color_multi(scn->ambiant.intensity, scn->ambiant.color);
//	color = hadamar_prod(color, hit->object->color);
//	while (i < scn->lights->length)
//	{
//		light = (t_light *)ft_get_elem(scn->lights, i);
//		to_light = v3_sub(light->o, hit->h_point);
//		if (is_in_shadow(scn, hit, to_light))
//			color = color_add(color, v4(0,0,0,1));
//		else
//		color = color_add(color, get_b_phong_l(light, hit, to_light));
//		i++;
//	}
//	return (color);
//}



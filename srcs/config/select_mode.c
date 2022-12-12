/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/11/18 15:22:24 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static inline t_hittable	*find_selected_object(t_scene	*scn, int x, int y)
{
	t_array	*records;
	t_hit	*first;
	t_ray	*ray;

	ray = ray_for_pixel(scn->selected_camera, x, y);
	records = do_intersect_objs(scn, ray);
	first = get_first_obj_hit(records, RAY_T_MAX, 0);
	if (first)
		return (first->object);
	ft_free_d_array(records);
	free(ray);
	return (NULL);
}

void	start_selecting_mode(t_app *app, int x, int y)
{
	t_hittable	*obj;

	if (app->conf.selected_obj != NULL)
	{
		printf("Object: %s, already selected \n", app->conf.selected_obj->name);
		return;
	}
	else
	{
		obj = find_selected_object(app->scene, x, y);
		if (obj)
			app->conf.selected_obj = obj;
		else
			printf("No object found at that position, try again\n");
	}
}

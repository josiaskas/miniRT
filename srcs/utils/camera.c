/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:16:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/28 12:16:05 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

// return a t_cam * , can be freed with free_cam
inline t_cam	*build_camera(t_point *origin, double angle)
{
	t_cam	*cam;

	cam = (t_cam *)ft_calloc(1, sizeof(t_cam));
	if (cam)
	{
		cam->origin = origin;
		cam->angle = angle;
	}
	return (cam);
}

// free camera
void	free_cam(t_cam *cam)
{
	if (cam)
	{
		if (cam->origin)
			free(cam->origin);
		free(cam);
	}
}
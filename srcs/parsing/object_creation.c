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

char	*add_name(t_scene *scene, char	*name, bool parsed)
{
	static int	n = 0;
	char		*made_name;
	char		*number;

	n++;
	made_name = name;
	if (parsed)
	{
		number = ft_itoa(n);
		made_name = ft_strjoin(made_name, number);
		free(number);
	}
	ft_push(scene->names, made_name);
	return (made_name);
}

char	*change_obj_name(t_hittable *obj, char *new_name)
{
	char	*tmp;

	tmp = obj->name;
	obj->name = new_name;
	free(tmp);
	return (new_name);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:52:10 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/31 20:32:53 by jkasongo         ###   ########.fr       */
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

/*
 * Build a normal object material with
 * colors, specular coefficient , diffuse coefficient and phong shines
 */
t_material	build_default_material(t_color clr, double s, double d, double ph)
{
	t_material	m;

	m.type = e_plastic;
	m.specular = s;
	m.diffuse = d;
	m.shininess = ph;
	m.reflexive = 1.0f;
	m.main = clr;
	m.pattern = e_normal_pattern;
	return (m);
}

/*
 * Build a stripped object material with
 * colors, specular coefficient , diffuse coefficient and phong shines
 */
t_material	build_stripped(t_color clr[], double s, double d, double ph)
{
	t_material	m;

	m.type = e_plastic;
	m.specular = s;
	m.diffuse = d;
	m.shininess = ph;
	m.reflexive = 1.0f;
	m.main = clr[0];
	m.second = clr[1];
	m.pattern = e_stripped_pattern;
	return (m);
}

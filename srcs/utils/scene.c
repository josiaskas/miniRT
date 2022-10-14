/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:30:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/10/08 14:30:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static inline void	add_plastic_materials(t_array *m_list)
{
	t_material	*plastic;
	plastic = (t_material *)ft_calloc(1, sizeof(t_material));
	if (plastic)
	{
		plastic->type = e_plastic;
		plastic->name = "PLASTIC";
		plastic->shininess = 200;
		plastic->reflexive = 0;
		plastic->diffuse = 0.9;
		plastic->specular = 0.9;
		ft_push(m_list, plastic);
	}
}

static inline void add_metallic_materials(t_array *m_list)
{
	t_material	*metallic;

	metallic = (t_material *)ft_calloc(1, sizeof(t_material));
	if (metallic)
	{
		metallic->type = e_metallic;
		metallic->name = "METAL";
		metallic->shininess = 200;
		metallic->reflexive = 0.5;
		metallic->diffuse = 0.9;
		metallic->specular = 0.8;
		ft_push(m_list, metallic);
	}
}

inline t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = NULL;
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (scene)
	{
		scene->hittable = ft_new_array();
		scene->lights = ft_new_array();
		scene->cameras = ft_new_array();
		scene->ambiant.intensity = 0;
		scene->materials = ft_new_array();
		add_plastic_materials(scene->materials);
		add_metallic_materials(scene->materials);
	}
	return (scene);
}

// destroy hittable, lights and cameras on the scene
void free_scene(t_scene *scene)
{
	if (scene)
	{
		ft_free_d_array(scene->hittable);
		ft_free_d_array(scene->lights);
		ft_free_d_array(scene->cameras);
		ft_free_d_array(scene->materials);
		ft_free_d_array(scene->names);
		free(scene);
	}
}
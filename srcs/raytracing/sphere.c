/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:52:30 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/17 13:54:53 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "parser.h"

void	compute_sphere_hit(t_hit *hit)
{
	if (hit->type != e_hit_sphere)
		return ;
	hit->normal = normalize(v3_sub(hit->h_point, hit->object->o));
	if (hit->inside)
		hit->normal = v3_multi(-1, hit->normal);
	hit->acne_p = v3_add(hit->h_point, v3_multi(RAY_T_MIN, hit->normal));
}

static inline void	set_point(t_hit *hit)
{
	if (hit->t < 0)
	{
		hit->t = RAY_T_MAX;
		return ;
	}
	hit->intersection = true;
	hit->h_point = get_point_on_ray_at(hit->t, hit->ray);
	hit->h_point_obj_coord = hit->h_point;
}

void	intersect_sphere(t_hit *hit, t_hittable *sphere, t_ray ray)
{
	double	terms[3];
	double	t[2];
	t_v3	sphere_to_ray;

	t[1] = RAY_T_MAX;
	t[0] = RAY_T_MAX;
	hit->t = RAY_T_MAX;
	sphere_to_ray = v3_sub(ray.o, sphere->o);
	terms[0] = ft_dot(ray.dir, ray.dir);
	terms[1] = 2 * ft_dot(ray.dir, sphere_to_ray);
	terms[2] = ft_dot(sphere_to_ray, sphere_to_ray)
		- (sphere->radius * sphere->radius);
	if (solve_quad(terms, &t[0], &t[1]))
	{
		hit->t_trace[0] = t[0];
		hit->t_trace[1] = t[1];
		hit->t = t[0];
		if ((hit->t_trace[0] < 0) && (hit->t_trace[1] > 0))
		{
			hit->inside = true;
			hit->t = t[1];
		}
		set_point(hit);
	}
}

bool	build_sphere(t_scene *scn, t_point o, double radius, t_v3 color_rgb)
{
	t_hittable	*sphere;
	t_color		color;

	sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (sphere)
	{
		sphere->type = e_hit_sphere;
		sphere->o = o;
		sphere->radius = radius;
		color = make_color_vector(color_rgb, 1);
		sphere->material = build_default_material(color, 0.3, 0.7, 200);
		sphere->trans = (t_v3){0, 0, 0};
		sphere->angles = (t_v3){0, 0, 0};
		sphere->scale = (t_v3){1, 1, 1};
		sphere->name = add_name(scn, "Sphere parsed o_n_", true);
		ft_push(scn->hittable, sphere);
		return (true);
	}
	return (false);
}

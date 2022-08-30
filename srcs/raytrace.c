/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:54:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:54:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"


void	init_raytracing(t_app *app)
{
	app->error_code = 0;
	app->error_message = NULL;
	if (app->data)
		free(app->data);
	app->data = ft_calloc((W_WIDTH * W_HEIGHT), sizeof(t_vector));
}

bool	do_raytracing(t_app *app)
{
	t_repere	*orthogonal;
	ft_putendl_fd("Start ray tracing", STDOUT_FILENO);
	init_raytracing(app);
	orthogonal = init_repere(W_HEIGHT, W_WIDTH, 1);

	free(orthogonal);
	return (true);
}
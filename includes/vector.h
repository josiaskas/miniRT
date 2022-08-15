/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 18:56:04 by jkasongo          #+#    #+#             */
/*   Updated: 2022/08/14 18:56:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "../libft/libft.h"
# include <math.h>

typedef struct s_vector
{
	double coord[3];
}	t_vector;

double		get_vector_norm(t_vector *v);
double		get_vector_norm_2(t_vector *v);
t_vector	add_vector(t_vector *a, t_vector *b);
t_vector	multiply_vector(double i, t_vector *v);
t_vector	get_normalized(t_vector *v);
#endif //VECTOR_H

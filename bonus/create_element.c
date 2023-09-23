/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:43:55 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/22 16:43:59 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

t_pixel	*create_element(t_pixel pt)
{
	t_pixel	*new_pixel;

	new_pixel = (t_pixel *)malloc(sizeof(t_pixel));
	if (new_pixel == NULL) 
	{
		perror("Failed to create new grid element");
		return (NULL);
	}
	new_pixel->x = pt.x;
	new_pixel->y = pt.y;
	new_pixel->z = pt.z;
	new_pixel->iso_x = (pt.x - pt.y) * cos(M_PI / 4);
	new_pixel->iso_y = (pt.x + pt.y - pt.z) * sin(M_PI / 4);
	new_pixel->w_x = 0;
	new_pixel->w_y = 0;
	return (new_pixel);
}

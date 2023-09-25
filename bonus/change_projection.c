/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:55:22 by fszendzi          #+#    #+#             */
/*   Updated: 2023/09/25 14:55:25 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/fdf_bonus.h"

void	project_new(t_prog_data *data)
{
	int	projection_mode;

	projection_mode = data->current_projection;
	if (projection_mode == PROJECTION_ORTHO)
	{
		adapt_ortho_pixel(data);
	}
	if (projection_mode == PROJECTION_ISO)
	{
		adapt_iso_pixel(data);
	}
}

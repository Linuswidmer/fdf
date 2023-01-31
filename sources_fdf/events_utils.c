/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:57:55 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/31 10:28:54 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_cross(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

int	auto_motion(t_vars *vars)
{
	while (vars->rotation_y < 4.5)
		event_rotate(vars, -0.0002, 0.0002, 0);
	return (0);
}

void	two_d(t_vars *vars)
{
	event_rotate(vars, -vars->rotation_x, -vars->rotation_y, -vars->rotation_z);
}

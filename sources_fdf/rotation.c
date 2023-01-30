/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:22:53 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/30 11:28:50 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_x(t_point **map, int num_lines, int line_len, double rad)
{
	int		i;
	int		j;
	double	y_double;
	double	z_double;

	i = 0;
	while (i < num_lines)
	{
		j = 0;
		while (j < line_len)
		{
			y_double = (double)(map[i][j].y);
			z_double = (double)(map[i][j].z);
			map[i][j].y = (float)(y_double * cos(rad) - z_double * sin(rad));
			map[i][j].z = (float)(y_double * sin(rad) + z_double * cos(rad));
			j++;
		}
		i++;
	}
}

void	rotation_y(t_point **map, int num_lines, int line_len, double rad)
{
	int		i;
	int		j;
	double	x_double;
	double	z_double;

	i = 0;
	while (i < num_lines)
	{
		j = 0;
		while (j < line_len)
		{
			x_double = (double)(map[i][j].x);
			z_double = (double)(map[i][j].z);
			map[i][j].x = (float)(x_double * cos(rad) - z_double * sin(rad));
			map[i][j].z = (float)(x_double * sin(rad) + z_double * cos(rad));
			j++;
		}
		i++;
	}
}

void	rotation_z(t_point **map, int num_lines, int line_len, double rad)
{
	int		i;
	int		j;
	double	x_double;
	double	y_double;

	i = 0;
	while (i < num_lines)
	{
		j = 0;
		while (j < line_len)
		{
			x_double = (double)(map[i][j].x);
			y_double = (double)(map[i][j].y);
			(map[i][j]).x = (float)(x_double * cos(rad) - y_double * sin(rad));
			(map[i][j]).y = (float)(x_double * sin(rad) + y_double * cos(rad));
			j++;
		}
		i++;
	}
}

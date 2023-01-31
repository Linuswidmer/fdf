/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:41:45 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/31 10:22:21 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_point **map, int num_lines, int line_len, float scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_lines)
	{
		j = 0;
		while (j < line_len)
		{
			map[i][j].x = map[i][j].x * scale;
			map[i][j].y = map[i][j].y * scale;
			map[i][j].z = map[i][j].z * scale;
			j++;
		}
		i++;
	}
}

void	translate_map(t_vars *vars, float trans_x, float trans_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->num_lines)
	{
		j = 0;
		while (j < vars->line_len)
		{
			(vars->map)[i][j].x = (vars->map)[i][j].x + trans_x;
			(vars->map)[i][j].y = (vars->map)[i][j].y + trans_y;
			j++;
		}
		i++;
	}
}

void	map_size(t_vars *vars, t_point **map, t_data_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->num_lines)
	{
		j = 0;
		while (j < vars->line_len)
		{
			if (map[i][j].x < img->smallest_x)
				img->smallest_x = map[i][j].x;
			if (map[i][j].y < img->smallest_y)
				img->smallest_y = map[i][j].y;
			if (map[i][j].x > img->biggest_x)
				img->biggest_x = map[i][j].x;
			if (map[i][j].y > img->biggest_y)
				img->biggest_y = map[i][j].y;
			j++;
		}
		i++;
	}
}

void	calc_map_params(t_vars *vars, t_data_img *img)
{
	float	scale_x;
	float	scale_y;

	img->smallest_x = 0;
	img->smallest_y = 0;
	img->biggest_x = 0;
	img->biggest_y = 0;
	map_size(vars, vars->map, img);
	img->x_len = abs_f(img->biggest_x) + abs_f(img->smallest_x);
	img->y_len = abs_f(img->biggest_y) + abs_f(img->smallest_y);
	scale_x = WINDOW_WIDTH / (img->x_len + 1);
	scale_y = WINDOW_HEIGHT / (img->y_len + 1);
	if (scale_x < scale_y)
		img->scale = scale_x;
	else
		img->scale = scale_y;
}

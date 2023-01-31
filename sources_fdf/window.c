/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:29:55 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/31 09:12:01 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data_img	img_creator(t_vars *vars)
{
	t_data_img	img;

	calc_map_params(vars, &img);
	translate_map(vars, -img.smallest_x, -img.smallest_y);
	scale_map(vars->map, vars->num_lines, vars->line_len, img.scale);
	translate_map(vars, (WINDOW_WIDTH - (img.x_len * img.scale)) / 2, \
		(WINDOW_HEIGHT - (img.y_len * img.scale)) / 2);
	img.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img.img)
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
			&img.line_length, &img.endian);
	return (img);
}

t_vars	mlx_creator(t_point **map, int num_lines, int line_len)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.map = map;
	vars.rotation_x = 0.955;
	vars.rotation_z = 0.785;
	vars.rotation_y = 0;
	vars.num_lines = num_lines;
	vars.line_len = line_len;
	if (vars.mlx)
		vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, \
			WINDOW_HEIGHT, "./fdf");
	return (vars);
}

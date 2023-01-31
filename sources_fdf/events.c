/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:57:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/01/31 10:28:07 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom(t_vars *vars, int keycode)
{
	t_data_img	img_new;
	float		zoom;

	if (keycode == 120)
		zoom = 2;
	else
		zoom = 0.5;
	img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img_new.img)
	{
		img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, \
&img_new.line_length, &img_new.endian);
		scale_map(vars->map, vars->num_lines, vars->line_len, zoom);
		print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, 0, 0);
		vars->img = img_new;
	}
	return (0);
}

void	event_rotate(t_vars *vars, double r_x, double r_y, double r_z)
{
	t_data_img	img_new;

	img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img_new.img)
	{
		img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, \
&img_new.line_length, &img_new.endian);
		if (r_x)
			rotation_x(vars->map, vars->num_lines, vars->line_len, r_x);
		if (r_y)
			rotation_y(vars->map, vars->num_lines, vars->line_len, r_y);
		if (r_z)
			rotation_z(vars->map, vars->num_lines, vars->line_len, r_z);
		print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, 0, 0);
		vars->rotation_x = vars->rotation_x + r_x;
		vars->rotation_y = vars->rotation_y + r_y;
		vars->rotation_z = vars->rotation_x + r_z;
		vars->img = img_new;
	}
}

void	event_translate(t_vars *vars, int keycode)
{
	t_data_img	img_new;

	img_new.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img_new.img)
	{
		img_new.addr = mlx_get_data_addr(img_new.img, &img_new.bits_per_pixel, \
&img_new.line_length, &img_new.endian);
		if (keycode == 119)
			translate_map(vars, 0, 10);
		if (keycode == 115)
			translate_map(vars, 0, -10);
		if (keycode == 97)
			translate_map(vars, 10, 0);
		if (keycode == 100)
			translate_map(vars, -10, 0);
		print_map(&img_new, vars->map, vars->num_lines, vars->line_len);
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_put_image_to_window(vars->mlx, vars->win, img_new.img, 0, 0);
		vars->img = img_new;
	}
}

int	keypress_events(int keycode, t_vars *vars)
{
	if (keycode == 122 || keycode == 120)
		zoom(vars, keycode);
	else if (keycode == 65307)
		mlx_loop_end(vars->mlx);
	else if (keycode == 119 || keycode == 115)
		event_translate(vars, keycode);
	else if (keycode == 97 || keycode == 100)
		event_translate(vars, keycode);
	else if (keycode == 121)
		event_rotate(vars, 0.0628, 0, 0);
	else if (keycode == 117)
		event_rotate(vars, -0.0628, 0, 0);
	else if (keycode == 104)
		event_rotate(vars, 0, 0.0628, 0);
	else if (keycode == 106)
		event_rotate(vars, 0, -0.0628, 0);
	else if (keycode == 110)
		event_rotate(vars, 0, 0, 0.0628);
	else if (keycode == 109)
		event_rotate(vars, 0, 0, -0.0628);
	else if (keycode == 112)
		auto_motion(vars);
	else if (keycode == 50)
		two_d(vars);
	return (0);
}

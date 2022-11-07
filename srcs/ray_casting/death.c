/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:05:15 by albaur            #+#    #+#             */
/*   Updated: 2022/11/07 16:30:17 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	show_death(t_data *data)
{
	mlx_image_to_window(data->mlx, data->enemy.death_bg->img, 0, 0);
	mlx_image_to_window(data->mlx, data->enemy.death_text->img, WIDTH / 2 - 100, HEIGHT / 2 - 50);
}

void	draw_death(t_data *data)
{
	t_shape	background;

	background.height = HEIGHT;
	background.width = WIDTH;
	background.x = 0;
	background.y = 0;
	data->enemy.death_bg = malloc(sizeof(t_image));
	data->enemy.death_text = malloc(sizeof(t_image));
	data->enemy.death_bg->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->enemy.death_text->texture = mlx_load_xpm42("images/dead.xpm42");
	draw_rect(data->enemy.death_bg->img, background, 0xFF000047);
	data->enemy.death_text->img = mlx_texture_to_image(data->mlx, &data->enemy.death_text->texture->texture);
	data->enemy.warning_text->img->enabled = 0;
	data->map->minimap->img->enabled = 0;
	data->enemy.alive = 0;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	data->ray_data.m.focus = 1;
}
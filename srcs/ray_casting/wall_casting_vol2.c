/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_vol2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:29:16 by faventur          #+#    #+#             */
/*   Updated: 2022/10/20 14:41:53 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	texture_y_pos_calculator(t_data *data, t_ray *ray)
{
	ray->step = 1.0 * data->textures[ray->text_select].img->height
		/ ray->line_height;
	ray->tex_pos = (ray->draw_start - ray->resolution.y / 2
			+ ray->line_height / 2) * ray->step;
}

void	texture_x_pos_calculator(t_data *data, t_ray *ray)
{
	size_t	img_width;

	img_width = data->textures[ray->text_select].img->width;
	if (ray->side == 0)
		ray->wall_x = ray->pos.y + ray->wall_distance * ray->ray_dir.y;
	else
		ray->wall_x = ray->pos.x + ray->wall_distance * ray->ray_dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.x = (int)(ray->wall_x * (double)img_width);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex.x = img_width - ray->tex.x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex.x = img_width - ray->tex.x - 1;
}

void	wall_line_calculator(t_ray *ray)
{
	ray->line_height = (int)(ray->resolution.y / ray->wall_distance);
	ray->draw_start = -ray->line_height / 2 + ray->resolution.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + ray->resolution.y / 2;
	if (ray->draw_end >= ray->resolution.y)
		ray->draw_end = ray->resolution.y - 1;
}
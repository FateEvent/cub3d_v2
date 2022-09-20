/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/09/20 13:35:53 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_new_window() function returns a <window> structure containing all the
** coordinates of the new window created.
*/

#include "mlx_utils.h"

int	ft_close(void)
{
	exit(0);
}

t_vector	calculate_window_size(char **map)
{
	t_vector	size;

	size.x = 0;
	size.y = 0;
	while (map[size.y])
	{
		while (map[size.y][size.x])
		{
			size.x++;
		}
		size.y++;
	}
	size.x *= 63;
	size.y *= 63;
	return (size);
}

t_window	ft_new_window(void *mlx, int width, int height, char *name)
{
	t_window	window;

	(void)name;
	window.reference = mlx_new_image(mlx, width, height);
	window.size.x = width;
	window.size.y = height;
	mlx_key_hook(window.reference, 17, 0, ft_close, 0);
	return (window);
}

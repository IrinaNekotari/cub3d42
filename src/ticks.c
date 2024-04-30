/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ticks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascrie <nmascrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:41:33 by nmascrie          #+#    #+#             */
/*   Updated: 2024/04/22 00:41:35 by nmascrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	tick_sprite(t_anim *s)
{
	if (s->index + 1 > 9 || !s->sprites[s->index + 1])
		s->index = 0;
	else
		s->index++;
	s->current = s->sprites[s->index];
}

void	tick_sprites(t_contr *a)
{
	int	i;

	i = 0;
	while (i < MAX_ANIMATIONS)
	{
		if ((a->frame % a->sprite_set[i]->delay) == 0)
			tick_sprite(a->sprite_set[i]);
		i++;
		if (!a->sprite_set[i])
			break ;
	}
	a->frame++;
	if (a->frame >= a->frame_max)
		a->frame = 0;
}

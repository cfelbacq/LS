/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:07:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/15 12:32:03 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	free_data(t_l *data)
{
	while (data)
	{
		free(data->mode);
		free(data->name);
		free(data->user);
		free(data->group_name);
		free(data);
		data = data->next;
	}
}

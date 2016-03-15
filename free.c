/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:07:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/15 16:58:32 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	free_data(t_l **data, int mode) /*mode == 1 free_list mode != 1 free_maillon*/
{
		free((*data)->mode);
		free((*data)->name);
		free((*data)->user);
		free((*data)->group_name);
		free(*data);
		if((*data)->next != NULL && mode == 1)
			free_data(&(*data)->next, mode);
		(*data)->next = NULL;
		*data = NULL;
}


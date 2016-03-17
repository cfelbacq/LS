/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:07:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 18:30:33 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
//mode == 1 free_list mode != 1 free_maillon
void	free_data(t_l **data, int mode, t_option *opt)
{
	free((*data)->name);
	if (opt->l == 1)
	{
		free((*data)->mode);
		free((*data)->user);
		free((*data)->group_name);
		free((*data)->time);
	}
	if ((*data)->next != NULL && mode == 1)
		free_data(&(*data)->next, mode, opt);
	free(*data);
	*data = NULL;
}

void	free_double(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

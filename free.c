/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:07:09 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 16:32:12 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	free_data(t_l **data, int mode, t_option *opt)
{
	free((*data)->path);
	free((*data)->name);
	if ((*data)->type == 'l')
		free((*data)->link);
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

t_l		*remove_link(t_l *ar, char *name, t_option *opt)
{
	t_l *tmp1;
	t_l *tmp2;

	tmp2 = NULL;
	tmp1 = ar;
	while (tmp1 != NULL && ft_strcmp(tmp1->name, name) != 0)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp2 == NULL)
	{
		tmp2 = ar;
		ar = ar->next;
		free_data(&tmp2, 0, opt);
	}
	else
	{
		tmp2->next = tmp1->next;
		free_data(&tmp1, 0, opt);
	}
	return (ar);
}

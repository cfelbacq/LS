/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 16:28:11 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/22 11:01:56 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_l		*check_file(t_l *ar, t_option *opt)
{
	t_l		*tmp;
	t_stat	buf;

	tmp = ar;
	while (tmp != NULL)
	{
		if (lstat(tmp->name, &buf) == -1)
		{
			opt->err += 1;
			print_err_ar(tmp->name);
			ar = remove_link(ar, tmp->name, opt);
		}
		tmp = tmp->next;
	}
	return (ar);
}

int		check_flag(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
		return (1);
	else
		return (0);
}

void	check_len_ar(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			ft_putendl_fd("ls: fts_open: No such file or directory", 2);
			exit(0);
		}
		i++;
	}
}

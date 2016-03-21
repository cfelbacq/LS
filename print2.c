/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 16:40:05 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 17:01:19 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_err_ar(char *str)
{
	ft_putstr("ls: ");
	perror(str);
}

void	print_maj_min(t_l *data)
{
	ft_putnbr(data->major);
	ft_putstr(", ");
	ft_putnbr(data->minor);
}

void	print_total(int total_print, t_l *data)
{
	total_print = total(data);
	ft_putstr("total ");
	ft_putnbr(total_print);
	ft_putchar('\n');
}

void	ls(t_l *data, t_option *opt)
{
	int i;
	int total_print;

	total_print = 0;
	i = 0;
	while (data != NULL)
	{
		if (!(opt->a == 0 && data->name[0] == '.'))
		{
			if (opt->l != 1)
				ft_putendl(data->name);
			else
			{
				if (i == 0)
					print_total(total_print, data);
				i++;
				print_l(data, opt);
			}
		}
		data = data->next;
	}
}

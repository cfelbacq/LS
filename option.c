/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:57:24 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/20 14:02:07 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_ill_opt(char c)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [lRart] [file ...]");
	exit (0);
}

void	check_opt(int argc, t_option *opt, char **str)
{
	int i;
	int j;

	j = 0;
	while (++j < argc)
	{
		i = -1;
			if (str[j][1] == '-' || str[j][0] != '-')
				return ;
		while (str[j][++i] != '\0')
		{
			if(str[j][i] == '-' && str[j][i + 1] == '-')
			{
				init_option(opt);
				return ;
			}
			if (str[j][i] == 'l')
				opt->l = 1;
			else if (str[j][i] == 'R')
				opt->R = 1;
			else if (str[j][i] == 'a')
				opt->a = 1;
			else if (str[j][i] == 'r')
				opt->r = 1;
			else if (str[j][i] == 't')
				opt->t = 1;
			//else if (str[j][i] != '-')
			//	print_ill_opt(str[j][i]);
		}
	}
}

void	init_option(t_option *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->err = 0;
}

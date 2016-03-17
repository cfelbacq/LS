/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:57:24 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 15:41:54 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	check_opt(int argc, t_option *opt, char **str)
{
	int i;
	int j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (str[j][i] != 0 && str[j][0] == '-')
		{
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
			i++;
		}
		if (str[j][0] != '-')
			return ;
		j++;
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

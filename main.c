/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/21 17:56:25 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_l	*reverse(t_l *data)
{
	t_l *tmp1;
	t_l *tmp2;
	t_l *new;

	new = NULL;
	tmp1 = data;
	tmp2 = data;
	while (tmp1)
	{
		tmp1 = tmp1->next;
		tmp2->next = new;
		new = tmp2;
		tmp2 = tmp1;
	}
	return (new);
}

int	main(int argc, char **argv)
{
	t_option opt;

	init_option(&opt);
	check_opt(argc, &opt, argv);
	check_len_ar(argc, argv);
	if (argc == 1)
		print_dir(".", &opt);
	else
		start(argc, argv, &opt);
	return (0);
}

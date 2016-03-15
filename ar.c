/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:57:38 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/15 17:31:28 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_l		*fill_ar(int i, int argc, char **argv)
{
	t_l *ar;
	t_l *tmp;

	ar = fill_data(argv[i], argv[i], NULL);
	tmp = ar;
	while (i < argc - 1)
	{
		i++;
		t_l *new;
		new = fill_data(argv[i], argv[i], NULL);
			if ((ft_strcmp(new->name, tmp->name)) < 0)
				ar = ins_start(ar, new);
			else
			{
				while (tmp->next != NULL && ft_strcmp(new->name, (tmp->next)->name) > 0)
					tmp = tmp->next;
				ins_middle(tmp, new, tmp->next);
			}
			tmp = ar;
	}
	return (ar);
}


static void	init_rep(t_l *ar, t_option *opt, int nb_file, int nb_rep)
{
	t_l *tmp;
	t_l *rep;
	int i;

	i = 0;
	tmp = ar;
	rep = NULL;
	while(tmp)
	{
		if (tmp->type == 'd')
		{
			if (nb_file > 0 || nb_rep > 1)
			{
				if (nb_file > 0 || i > 0)
					ft_putchar('\n');
				ft_putstr(tmp->name);
				ft_putendl(":");
			}
			print_dir(tmp->name, opt);
			i++;
		}
		tmp = tmp->next;
	}
}

static void	init_file(t_l *ar, t_option *opt, int *nb_file, int *nb_rep)
{
	t_l *tmp;

	tmp = ar;
	while(tmp)
	{
		if (tmp->type != 'd')
		{
			*nb_file += 1;
			if (opt->l == 1)
				print_l(tmp, opt);
			else
				ft_putendl(tmp->name);
		}
		else
			*nb_rep += 1;
		tmp = tmp->next;
	}
}

t_l	*remove_link(t_l *ar, t_l *tmp, int i)
{
	t_l *tmp2;
	
	if(tmp != NULL && tmp->next != NULL)
	{
		tmp2 = tmp->next;
		tmp->next = tmp2->next;
		free_data(&tmp2, 0);
	}
	else if (tmp != NULL && tmp->next == NULL)
	{
		free(ar);
		ar = NULL;
	}
	else
	{
		tmp2 = ar;
		ar = ar->next;
		free_data(&tmp2, 0);
	}
	return (ar);
}

static t_l *check_err(t_l *ar)
{
	int i;
	DIR *rep;
	t_l *tmp;
	t_l *tmp2;
	struct stat buf;

	i = 0;
	tmp = ar;
	tmp2 = NULL;
	while (tmp)
	{
		i++;
		stat(tmp->name, &buf);
		if (errno == ENOENT || errno == EACCES || errno == EBADF)
		{
			if ((rep = opendir(tmp->name)) == NULL)
			{
				print_err(tmp->name);
				ar = remove_link(tmp2, ar, i);
			}
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (ar);
}

static void	sort_ar(t_l *ar, t_option *opt)
{
	int nb_file;
	int nb_rep;
	nb_file = 0;
	nb_rep = 0;
	ar = check_err(ar);
	if (ar == NULL)
		exit(0) ;
	init_file(ar, opt, &nb_file, &nb_rep);
	init_rep(ar, opt, nb_file, nb_rep);
}

void	start(int argc, char **argv, t_option *opt)
{
	int i;

	i = 1;
	while (argc > i && argv[i][0] == '-')
		i++;
	if (argc == i)
	{
		print_dir(".", opt);
		return ;
	}
	sort_ar(fill_ar(i, argc, argv), opt);
}

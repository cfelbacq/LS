/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/10 14:24:44 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ls.h"

void	ls(t_l *data, t_option *opt)
{
	while (data->next != NULL)
	{
		if (!(opt->a == 0 && data->name[0] == '.'))
		{
			if(opt->l != 1)
				ft_putendl(data->name);
			else
				print_l(data, opt);
		}
		data = data->next;
	}
}

void	print_dir(char *name, t_option *opt)
{
	struct dirent *ent;
	DIR *rep;
	t_l *data;
	t_l *tmp;

	rep = opendir(name);
	ent = readdir(rep);
	name = ft_strjoin(name, "/");
	data = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL);
	tmp = data;
	while ((ent = readdir(rep)) != NULL)
	{
		
		tmp = tmp->next;
	}
	ft_putchar('\n');
	tmp = data;
	ls(tmp, opt);
	while (tmp && opt->R == 1)
	{
		if (tmp->type == 'd' && ft_strcmp(".", tmp->name) != 0 &&\
				ft_strcmp("..", tmp->name) != 0)
		{
			print_path(ft_strjoin(name, tmp->name));
			print_dir(ft_strjoin(name, tmp->name), opt);
		}
		tmp = tmp->next;
	}
}

void	start(int argc, char **argv, t_option *opt)
{
	int i;
	int j;

	j = argc;
	i = 1;
	while (argc > i && argv[i][0] == '-')
		i++;
	if (argc == i)
	{
		print_dir(".", opt);
		return ;
	}
	while (i < argc)
	{
		print_dir(argv[i], opt);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_option opt;

	init_option(&opt);
	check_opt(argc ,&opt, argv);
	print_opt(&opt);
	if (argc == 1)
		print_dir(".", &opt);
	else
		start(argc, argv, &opt);
		//rep = opendir(argv[1]);
	//	printf("dernier changement d'etat : %s", ctime(&buf.st_ctime));
	//	printf("dernier acces au fichier : %s", ctime(&buf.st_atime));
	//	printf("derniere modification du fichier : %s\n", ctime(&buf.st_mtime));
	return (0);
}

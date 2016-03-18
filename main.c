/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/18 16:56:27 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ls.h"

int	total(t_l *data)
{
	t_l *tmp;
	t_stat buf;
	int total;
	int count;

	count = 0;
	total = 0;
	tmp = data;
	while (tmp)
	{
		lstat(tmp->path, &buf);
	//	ft_putnbr(buf.st_size / 512);
	//	ft_putchar('\n');
		total = total + buf.st_size;
		tmp = tmp->next;
	}
	return ((total / 512));
}

void	ls(t_l *data, t_option *opt)
{
	int i;

	i = 0;
	while (data != NULL)
	{
		if (!(opt->a == 0 && data->name[0] == '.'))
		{
			if(opt->l != 1)
				ft_putendl(data->name);
			else
			{
				if (i == 0)
				{
					data->total = total(data);
					ft_putstr("total ");
					ft_putnbr(data->total);
					ft_putchar('\n');
				}
				i++;
				print_l(data, opt);
			}
		}
		data = data->next;
	}
}

t_l		*create_data(char *name, t_option *opt)
{
	t_dirent *ent;
	DIR *rep;
	t_l *data;
	t_l *tmp;
	t_l *new;

	tmp = NULL;
	if ((rep = opendir(name)) == NULL)
	{
		if (errno)
		{
			print_err(name);
			return (NULL);
		}
	}
	ent = readdir(rep);
	name = ft_strjoin(name, "/");
	data = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
	tmp = data;
	while ((ent = readdir(rep)) != NULL)
	{
		new = fill_data(ft_strjoin(name, ent->d_name), ent->d_name, NULL, opt);
			if ((ft_strcmp(new->name, tmp->name)) < 0)
				data = ins_start(data, new);
			else
			{
				while (tmp->next != NULL && ft_strcmp(new->name, (tmp->next)->name) > 0)
					tmp = tmp->next;
				ins_middle(tmp, new, tmp->next);
			}
			tmp = data;
	}
	closedir(rep);
	return (data);
}

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

void	print_dir(char *name, t_option *opt)
{
	int i;
	t_l *data;
	t_l *tmp;

	i = 0;
	if ((data = create_data(name, opt)) == NULL)
		return ;
	if (name[ft_strlen(name) - 1] != '/')
	name = ft_strjoin(name, "/");
	if (opt->r == 1)
		data = reverse(data);
	tmp = data;
	ls(tmp, opt);
	while (tmp && opt->R == 1)
	{
		if (tmp->type == 'd' && ft_strcmp(".", tmp->name) != 0 &&\
				ft_strcmp("..", tmp->name) != 0)
		{
			if (!(opt->a == 0 && tmp->name[0] == '.'))
			{
				print_path(ft_strjoin(name, tmp->name));
				print_dir(ft_strjoin(name, tmp->name), opt);
			}
		}
		tmp = tmp->next;
	}
	free_data(&data, 1, opt);
}

int	main(int argc, char **argv)
{
	t_option opt;

	init_option(&opt);
	check_opt(argc ,&opt, argv);
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

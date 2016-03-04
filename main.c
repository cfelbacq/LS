/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/04 16:28:34 by cfelbacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ls.h"

void	fill_mod(struct stat *buf, t_l *data)
{
	data->mode = (char *)ft_memalloc(sizeof(char) * 10);
	ft_memset(data->mode, '-', 9);
	data->mode[9] = '\0';
	if (buf->st_mode & S_IRUSR)
		data->mode[0] = 'r';
	if(buf->st_mode & S_IWUSR)
		data->mode[1] = 'w';
	if(buf->st_mode & S_IXUSR)
		data->mode[2] = 'x';
	if (buf->st_mode & S_IRGRP)
		data->mode[3] = 'r';
	if(buf->st_mode & S_IWGRP)
		data->mode[4] = 'w';
	if(buf->st_mode & S_IXGRP)
		data->mode[5] = 'x';
	if (buf->st_mode & S_IROTH)
		data->mode[6] = 'r';
	if(buf->st_mode & S_IWOTH)
		data->mode[7] = 'w';
	if(buf->st_mode & S_IXOTH)
		data->mode[8] = 'x';
}

void	fill_type(struct stat *buf, t_l *data)
{
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		data->type = 'd';
	else if((buf->st_mode & S_IFMT) == S_IFREG)
		data->type = '-';
	else if((buf->st_mode & S_IFMT) == S_IFBLK)
		data->type = 'b';
	else if((buf->st_mode & S_IFMT) == S_IFCHR)
		data->type = 'c';
	else if((buf->st_mode & S_IFMT) == S_IFLNK)
		data->type = 'l';
	else if((buf->st_mode & S_IFMT) == S_IFIFO)
		data->type = 'p';
	else if((buf->st_mode & S_IFMT) == S_IFSOCK)
		data->type = 's';
}

t_l	*fill_data(char *path, char *name)
{
	t_l *data;
	struct stat buf;
	struct passwd *get;
	struct group *getgrp;
	
	stat(path, &buf);
	getgrp = getgrgid(buf.st_gid);
	get = getpwuid(buf.st_uid);
	data = (t_l *)ft_memalloc(sizeof(t_l));
	fill_type(&buf, data);
	fill_mod(&buf, data);
	data->nb_octet = buf.st_size;
	data->name = (char *)ft_memalloc(sizeof(char) * ft_strlen(name) + 1);
	data->name = ft_strcpy(data->name, name);
	data->user = (char *)ft_memalloc(sizeof(char) * ft_strlen(get->pw_name));
	data->group_name = (char *)ft_memalloc(sizeof(char) *\
			ft_strlen(getgrp->gr_name + 1));
	data->nb_link = buf.st_nlink;
	ft_strcpy(data->user, get->pw_name);
	ft_strcpy(data->group_name, getgrp->gr_name);
	data->next = NULL;
	return (data);
}

void	print_l(t_l *data, t_option *opt)
{
	if (!(opt->a == 0 && data->name[0] == '.'))
	{
	ft_putchar(data->type);
	ft_putchar(' ');
	ft_putstr(data->mode);
	ft_putchar(' ');
	ft_putnbr(data->nb_link);
	ft_putchar(' ');
	ft_putstr(data->user);
	ft_putchar(' ');
	ft_putstr(data->group_name);
	ft_putchar(' ');
	ft_putnbr(data->nb_octet);
	ft_putchar(' ');
	ft_putstr(data->name);
	ft_putchar('\n');
	}
}

void	print_dir(char *name, t_option *opt)
{
	struct stat buf;
	struct dirent *ent;
	struct passwd *get;
	DIR *rep;
	t_l *data;
	t_l *tmp;

	rep = opendir(name);
	ent = readdir(rep);
	name = ft_strjoin(name, "/");
	data = fill_data(ft_strjoin(name, ent->d_name), ent->d_name);
	tmp = data;
	while ((ent = readdir(rep)) != NULL)
	{
		print_l(tmp, opt);
		tmp->next = fill_data(ft_strjoin(name, ent->d_name), ent->d_name);
		tmp = tmp->next;
	}
	print_l(tmp, opt);
	ft_putchar('\n');
	tmp = data;
	while (tmp && opt->R == 1)
	{
		if (tmp->type == 'd' && ft_strcmp(".", tmp->name) != 0 &&\
				ft_strcmp("..", tmp->name) != 0)
			print_dir(ft_strjoin(name, tmp->name), opt);
		tmp = tmp->next;
	}
}

t_list	*fill_str(char *str)
{
	t_list *argv;

	argv = (t_list *)ft_memalloc(sizeof(t_list));
	argv->content = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1);
	argv->content = ft_strcpy(argv->content, str);
	argv->next = NULL;
	return (argv);
}

int	check_opt(t_option *opt, char *str)
{
	int i;
	int checkstr;

	checkstr = 0;
	i = 0;
	while (str[i] != 0 && str[0] == '-')
	{
		checkstr = 1;
		if (str[i] == 'l')
			opt->l = 1;
		else if (str[i] == 'R')
			opt->R = 1;
		else if (str[i] == 'a')
			opt->a = 1;
		else if(str[i] == 'r')
			opt->r = 1;
		else if(str[i] == 't')
			opt->r = 1;
		i++;
	}
	return (checkstr);
}

void	create_l(int argc, char **argv, t_option *opt)
{
	int i;
	t_list *str;
	t_list *tmp;

	i = 1;
	str = fill_str(argv[i]);
	tmp = str;
	while (i < argc)
	{
		if (i > 1)
		{
		tmp->next = fill_str(argv[i]);
		tmp = tmp->next;
		}
		i++;
	}
	tmp = str;
	while(tmp)
	{
		if (check_opt(opt, tmp->content) == 0)
			print_dir(tmp->content, opt);
		else
			print_dir(".", opt);
		tmp = tmp->next;
	}
}

void	init_option(t_option *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
}

int	main(int argc, char **argv)
{
	t_option opt;

	init_option(&opt);
	if (argc == 1)
		print_dir(".", &opt);
	else
		create_l(argc, argv, &opt);
		//rep = opendir(argv[1]);
	//	printf("dernier changement d'etat : %s", ctime(&buf.st_ctime));
	//	printf("dernier acces au fichier : %s", ctime(&buf.st_atime));
	//	printf("derniere modification du fichier : %s\n", ctime(&buf.st_mtime));
	return (0);
}

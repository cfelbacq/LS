/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 11:47:39 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/17 18:50:28 by cfelbacq         ###   ########.fr       */
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
	if (buf->st_mode & S_IWUSR)
		data->mode[1] = 'w';
	if (buf->st_mode & S_IXUSR)
		data->mode[2] = 'x';
	if (buf->st_mode & S_IRGRP)
		data->mode[3] = 'r';
	if (buf->st_mode & S_IWGRP)
		data->mode[4] = 'w';
	if (buf->st_mode & S_IXGRP)
		data->mode[5] = 'x';
	if (buf->st_mode & S_IROTH)
		data->mode[6] = 'r';
	if (buf->st_mode & S_IWOTH)
		data->mode[7] = 'w';
	if (buf->st_mode & S_IXOTH)
		data->mode[8] = 'x';
}

void	fill_type(struct stat *buf, t_l *data)
{
	if ((buf->st_mode & S_IFMT) == S_IFDIR)
		data->type = 'd';
	else if ((buf->st_mode & S_IFMT) == S_IFREG)
		data->type = '-';
	else if ((buf->st_mode & S_IFMT) == S_IFBLK)
		data->type = 'b';
	else if ((buf->st_mode & S_IFMT) == S_IFCHR)
		data->type = 'c';
	else if ((buf->st_mode & S_IFMT) == S_IFLNK)
		data->type = 'l';
	else if ((buf->st_mode & S_IFMT) == S_IFIFO)
		data->type = 'p';
	else if ((buf->st_mode & S_IFMT) == S_IFSOCK)
		data->type = 's';
}

char	*ft_readlink(char *path, int size)
{
	int r;
	char *link_name;
	
	r = 0;
	link_name = malloc(size + 1);
	r = readlink(path, link_name, size + 1);
	link_name[size] = '\0';
	return (link_name);
}

char *get_time(char *time)
{
	char *time_print;
	int i;
	int count;
	int j;

	j = 0;
	count = 0;
	i = 0;
	time_print = (char *)malloc(ft_strlen(time) + 1);
	while (time[i] != ' ')
		i++;
	while (time[i] < '0' || time[i] > '9')
	{
		time_print[j] = time[i];
		i++;
		j++;
	}
	while (time[i] != '\n' && count < 2)
	{
		if (time[i] == ':')
			count++;
		time_print[j] = time[i];
		j++;
		i++;
	}
	time_print[j - 1] = '\0';
	return (time_print);
}

t_l		*fill_data(char *path, char *name, t_l *next, t_option *opt)
{
	t_l			*data;
	t_stat		buf;
	t_passwd	*get;
	t_group		*getgrp;

	data = (t_l *)ft_memalloc(sizeof(t_l));
	lstat(path, &buf);
	data->name = (char *)ft_memalloc(sizeof(char) * ft_strlen(name) + 1);
	data->name = ft_strcpy(data->name, name);
	fill_type(&buf, data);
	if (opt->l == 1)
	{
		if (data->type == 'l')
			data->link = ft_readlink(path, buf.st_size);
		data->time = (char *)ft_memalloc((ft_strlen(ctime(&buf.st_mtime))) + 1);
		data->time = get_time(ft_strcpy(data->time, (ctime(&buf.st_mtime))));
		getgrp = getgrgid(buf.st_gid);
		get = getpwuid(buf.st_uid);
		fill_mod(&buf, data);
		data->nb_octet = buf.st_size;
		data->user = (char *)ft_memalloc(sizeof(char) * \
				ft_strlen(get->pw_name));
		data->group_name = (char *)ft_memalloc(sizeof(char) *\
				ft_strlen(getgrp->gr_name + 1));
		data->nb_link = buf.st_nlink;
		ft_strcpy(data->user, get->pw_name);
		ft_strcpy(data->group_name, getgrp->gr_name);
	}
	data->next = next;
	return (data);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfelbacq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:49:19 by cfelbacq          #+#    #+#             */
/*   Updated: 2016/03/03 16:19:54 by cfelbacq         ###   ########.fr       */
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
	//ft_putendl(data->user);
	//ft_putendl(data->group_name);
	//printf("%o \n", data->nb_octet);*/
	data->next = NULL;
	return (data);
}

void	print_l(t_l *data)
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

void	print_dir(char *name)
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
		print_l(tmp);
		tmp->next = fill_data(ft_strjoin(name, ent->d_name), ent->d_name);
		tmp = tmp->next;
	}
	print_l(tmp);
	ft_putchar('\n');
	tmp = data;
	while (tmp)
	{
		if (tmp->type == 'd' && ft_strcmp(".", tmp->name) != 0 &&\
				ft_strcmp("..", tmp->name) != 0)
			print_dir(ft_strjoin(name, tmp->name));
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	DIR * rep;
	struct stat buf;

	int a;
	a = 0;
	t_l *data;
	rep = NULL;
	if (argc == 1)
		print_dir(".");
		//rep = opendir(".");
	else if(argc == 2)
		print_dir(argv[1]);
		//rep = opendir(argv[1]);
	struct passwd *get;
	struct dirent *ent;
	struct group *getgrp;
	/*while ((ent = readdir(rep)) != NULL)
	{
		stat(ent->d_name, &buf);
		getgrp = getgrgid(buf.st_gid);
		get = getpwuid(buf.st_uid);
		fill_data(get, ent->d_name, getgrp, &buf, data);
		if (buf.st_mode == S_IFDIR || buf.st_mode >= 40000)
			ft_putendl("rep");
		fprintf(stdout, "ID PROPIETAIRE(%s) : %d\n",get->pw_name, buf.st_uid);
		fprintf(stdout, "ID DU GROUPE(%s) : %d\n",getgrp->gr_name, buf.st_gid);
		fprintf(stdout, "Protection : %o\n", buf.st_mode);
		fprintf(stdout, "taille : %lld octets\n ", (long long)buf.st_size);
		fprintf(stdout, "NB LIEN : %ld \n", (long)buf.st_nlink);
		printf("dernier changement d'etat : %s", ctime(&buf.st_ctime));
		printf("dernier acces au fichier : %s", ctime(&buf.st_atime));
		printf("derniere modification du fichier : %s\n", ctime(&buf.st_mtime));
	}*/
	return (0);
}

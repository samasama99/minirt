/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:30:02 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/19 15:41:29 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parsing.h"

void	ft_perror(int exit_status)
{
	perror("Error");
	exit(exit_status);
}

bool	is_rt_file(char *file)
{
	char	*dot;

	if (file == NULL)
		return (false);
	dot = strrchr(file, '.');
	if (dot == NULL || file == dot)
		return (false);
	return (is_equal_str(dot, ".rt"));
}

int	open_rt_file(int ac, char **av)
{
	int			fd;

	if (ac != 2)
	{
		ft_putendl_fd("Minirt only accept one argument {*.rt}", 2);
		exit(1);
	}
	if (!is_rt_file(av[1]))
	{
		ft_putendl_fd("Pls provide a .rt file", 2);
		exit(2);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_perror(1);
	return (fd);
}

int	main(int ac, char **av)
{
	const t_res	canvas_size = pair(1200, 675);
	const t_res	res = pair(canvas_size.x, canvas_size.y);
	const int	fd = open_rt_file(ac, av);
	t_data		data;

	data = (t_data){.w = {0, 0, 0, 0}};
	parse(&data, fd, canvas_size);
	close(fd);
	correct_ambient(data.w, data.ambient);
	printf ("The amount of shapes %d\n", data.w.amount_of_shapes);
	init(res, "miniRt");
	render(data.c, data.w);
	start();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:30:02 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/24 16:42:46 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <linear_algebra.h>
#include <parsing.h>

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
	const long		begin = time_now();
	const t_res		res = pair(1000, 600);
	const int		fd = open_rt_file(ac, av);
	t_image			canvas;
	t_data			data;

	init(res, "miniRt");
	data = (t_data){.w = {0, 0, 0, 0}};
	parse(&data, fd, res, split_string(read_file(fd), '\n'));
	close(fd);
	correct_ambient(data.w, data.ambient);
	printf (" \033[0;32m----\033[0m :: The total amount of shapes %d\n",
		data.w.amount_of_shapes);
	printf (" \033[0;32m[MiniRT]\033[0m :: creating a canvas (%d, %d)\n",
		res.width, res.height);
	listen_to(destroy, end_minirt_destroy, NULL);
	listen_to(keydown, end_minirt, NULL);
	canvas = create_image(pair(res.width, res.height));
	render(data.c, data.w, canvas);
	printf ("\n \033[0;32m[MiniRT]\033[0m :: done ! it took %fs\n",
		(time_now() - begin) / 1000.0);
	start();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:30:02 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/18 22:17:47 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parsing.h"

bool isRtFile(char *file) {
  char *dot;

  if (file == NULL)
    return false;
  dot = strrchr(file, '.');
  if (dot == NULL || file == dot)
    return false;
  return is_equal_str(dot, ".rt");
}

void	ft_perror(int exit_status)
{
	perror("Error");
	exit(exit_status);
}

int	main(int ac, char **av)
{
	const t_res	canvas_size = pair(1200, 675);
	const t_res	res = pair(canvas_size.x, canvas_size.y);
	int	fd;
	t_data		data;
  
  if (ac != 2) {
      ft_putendl_fd("minirt only accepet one argument {*.rt}", 2);
      return 1;
  }
  if (!isRtFile(av[1]))
  {
      ft_putendl_fd("pls provide a .rt file", 2);
      return 2;
  }
  fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_perror(1);
	data = (t_data){};
	data.w = (t_world){0, 0, 0, 0};
	parse(&data, fd, canvas_size);
	close(fd);
	correct_ambient(data.w, data.ambient);
	printf ("The amount of shapes %d\n", data.w.amount_of_shapes);
	init(res, "miniRt");
	render(data.c, data.w);
	start();
}

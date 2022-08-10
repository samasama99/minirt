/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:30:02 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/10 11:47:37 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/parsing.h"

void	ft_perror(int exit_status)
{
	perror("Error");
	exit(exit_status);
}

int	main(void)
{
	const t_res	canvas_size = pair(1200, 675);
	const t_res	res = pair(canvas_size.x, canvas_size.y + 25);
	const int	fd = open("src/test3.rt", O_RDONLY);
	t_data		data;

	if (fd < 0)
		ft_perror(1);
	data = (t_data){};
	data.w = (t_world){0, 0, 0, 0};
	data.selected.error = true;
	parse(&data, fd, canvas_size);
	close(fd);
	correct_ambient(data.w, data.ambient);
	printf ("The amount of shapes %d\n", data.w.amount_of_shapes);
	init(res, "miniRt");
	render(data.c, data.w);
	start();
}

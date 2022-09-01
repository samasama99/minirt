#include <parsing.h>

char	*read_file(int fd)
{
	char	*total;
	char	buffer[2];
	int		b;

	total = ft_strdup("\0");
	while (1)
	{
		b = read(fd, buffer, 1);
		if (b == -1)
		{
			ft_perror(1); 
			close(fd);
		}
		if (b == 0)
			break ;
		buffer[1] = '\0';
		total = ft_strjoin(total, buffer);
	}
	if (total && total[0] == '\0')
		return (NULL);
	return (total);
}

int	count_char(const char *str, const char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return (count);
}

size_t	array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		++i;
	return (i);
}

bool	ft_isnumber(const char *num)
{
	size_t	i;

	i = 0;
	if (num == NULL || num[0] == '\0')
		return (false);
	while (num[i])
	{
		if (ft_isdigit(num[i]) != 1)
			return (false);
		++i;
	}
	return (true);
}

size_t	int_len(int num)
{
	int	i;

	i = 0;
	while (num)
	{
		num = num / 10;
		++i;
	}
	return (i);
}

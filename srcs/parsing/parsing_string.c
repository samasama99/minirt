#include <parsing.h>

t_optional_string	parse_string(char *target)
{
	if (target == NULL)
		return ((t_optional_string){.is_null = true});
	return ((t_optional_string){
		.value = target,
		.size = ft_strlen(target),
		.is_null = false,
	});
}

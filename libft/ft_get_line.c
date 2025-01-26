#include "libft.h"

void	ft_str_char_cpy(char	*dst, char	*src, char c)
{
	int	i;

	i = 0;
	if (src)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		free(src);
	}
	dst[i++] = c;
	dst[i] = 0;
}

char	*ft_str_char_join(char c, char *str)
{
	char	*line;

	line = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!line)
	{
		free(str);
		write(2, "ERROR!\n", 7);
		return (0);
	}
	ft_str_char_cpy(line, str, c);
	return (line);
}

char	*ft_get_line(int fd)
{
	char	c;
	char	*line;

	c = 0;
	line = NULL;
	while (c != '\n' && read(fd, &c, 1) > 0)
		line = ft_str_char_join(c, line);
	return (line);
}
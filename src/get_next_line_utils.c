/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 17:45:04 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/02 12:49:48 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strljoin(const char *s1,
					const char *buffer, size_t buffer_len)
{
	size_t		ctr;
	size_t		s1_len;
	char		*catstr;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	catstr = malloc(sizeof(char) * (s1_len + buffer_len + 1));
	if (!catstr)
		return (NULL);
	ctr = 0;
	while (ctr < s1_len)
	{
		catstr[ctr] = s1[ctr];
		ctr++;
	}
	ctr = 0;
	while (ctr < buffer_len)
	{
		catstr[s1_len + ctr] = buffer[ctr];
		ctr++;
	}
	catstr[s1_len + buffer_len] = '\0';
	free((void *)s1);
	return (catstr);
}

int				ft_packup_buffer(t_buffer *root_buffer, t_buffer *buffer)
{
	t_buffer	*prev_buffer;
	ssize_t		bytes_read;

	bytes_read = buffer->bytes_read;
	ft_flush_buffer(buffer);
	if (buffer != root_buffer)
	{
		prev_buffer = root_buffer;
		while (prev_buffer->next && prev_buffer->next != buffer)
			prev_buffer = prev_buffer->next;
		prev_buffer->next = buffer->next;
		free(buffer);
	}
	return (bytes_read == RD_ERR ? RD_ERR : RD_EOF);
}

int				ft_fork_buffer(int fd, char **line,
					t_buffer *root_buffer, t_buffer **buffer)
{
	size_t		ctr;

	*buffer = malloc(sizeof(t_buffer));
	if (!*buffer)
		return (RD_ERR);
	(*buffer)->fd = fd;
	(*buffer)->next = NULL;
	(*buffer)->bytes_read = 0;
	ctr = 0;
	while (ctr < BUFFER_SIZE)
	{
		(*buffer)->store[ctr] = '\0';
		ctr++;
	}
	return (ft_read_to_buffer(fd, line, root_buffer, *buffer));
}

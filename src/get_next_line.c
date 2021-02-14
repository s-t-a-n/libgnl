/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 17:42:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/06/22 13:44:52 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void					ft_flush_buffer(t_buffer *buffer)
{
	size_t				split_pos;
	size_t				ctr;

	split_pos = 0;
	while (buffer->store[split_pos] != '\n' && split_pos < BUFFER_SIZE)
		split_pos++;
	ctr = 0;
	if (buffer->store[split_pos] == '\n')
		split_pos++;
	while (split_pos < BUFFER_SIZE)
	{
		buffer->store[ctr] = buffer->store[split_pos];
		ctr++;
		split_pos++;
	}
	while (ctr < BUFFER_SIZE)
	{
		buffer->store[ctr] = '\0';
		ctr++;
	}
}

int						ft_read_to_buffer(int fd, char **line,
		t_buffer *root_buffer, t_buffer *buffer)
{
	size_t				split_pos;

	split_pos = 0;
	buffer->bytes_read = read(fd, buffer->store, BUFFER_SIZE);
	while (buffer->bytes_read > 0)
	{
		split_pos = 0;
		while (buffer->store[split_pos] != '\n'
				&& (ssize_t)split_pos < buffer->bytes_read)
			split_pos++;
		*line = ft_strljoin(*line, buffer->store, split_pos);
		if (buffer->store[split_pos] == '\n' ||
				buffer->bytes_read < BUFFER_SIZE)
			break ;
		ft_flush_buffer(buffer);
		buffer->bytes_read = read(fd, buffer->store, BUFFER_SIZE);
	}
	if (buffer->bytes_read == 0 || (buffer->bytes_read < BUFFER_SIZE
				&& (ssize_t)split_pos == buffer->bytes_read
				&& buffer->store[buffer->bytes_read - 1] != '\n'))
		return (ft_packup_buffer(root_buffer, buffer));
	ft_flush_buffer(buffer);
	if (buffer->bytes_read > 0 || buffer->store[0] != '\0')
		return (RD_LINE);
	return (ft_packup_buffer(root_buffer, buffer));
}

int						ft_read_from_buffer(int fd, char **line,
		t_buffer *root_buffer, t_buffer *buffer)
{
	size_t				split_pos;

	split_pos = 0;
	while (buffer->store[split_pos] != '\n' && split_pos < BUFFER_SIZE)
		split_pos++;
	*line = ft_strljoin(*line, buffer->store, split_pos);
	if (buffer->store[split_pos] == '\n')
	{
		ft_flush_buffer(buffer);
		return (RD_LINE);
	}
	else
	{
		ft_flush_buffer(buffer);
		return (ft_read_to_buffer(fd, line, root_buffer, buffer));
	}
}

int						get_next_line(int fd, char **line)
{
	static t_buffer		buffer;
	t_buffer			*buffer_actual;

	if (fd < 0 || read(fd, 0, 0) == RD_ERR)
		return (RD_ERR);
	*line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*line)
		return (RD_ERR);
	**line = '\0';
	buffer_actual = &buffer;
	if (fd != buffer.fd && buffer.fd != 0)
		while (buffer_actual)
		{
			if (buffer_actual && buffer_actual->fd == fd)
				break ;
			if (!buffer_actual->next)
				return (ft_fork_buffer(fd, line, &buffer,
						(t_buffer **)&buffer_actual->next));
			buffer_actual = buffer_actual->next;
		}
	buffer_actual->fd = fd;
	if (buffer_actual->store[0] > 0)
		return (ft_read_from_buffer(fd, line, &buffer, buffer_actual));
	else
		return (ft_read_to_buffer(fd, line, &buffer, buffer_actual));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 17:41:26 by sverschu      #+#    #+#                 */
/*   Updated: 2020/02/06 17:14:37 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct	s_buffer
{
	char		store[BUFFER_SIZE];
	ssize_t		bytes_read;
	int			fd;
	void		*next;
}				t_buffer;

/*
** get_next_line.c
*/
int				get_next_line(int fd, char **line);
int				ft_read_from_buffer(int fd, char **line,
					t_buffer *root_buffer, t_buffer *buffer);
int				ft_read_to_buffer(int fd, char **line,
					t_buffer *root_buffer, t_buffer *buffer);
void			ft_flush_buffer(t_buffer *buffer);

/*
** get_next_line_utils.c
*/
char			*ft_strljoin(const char *s1,
					const char *buffer, size_t buffer_len);
int				ft_packup_buffer(t_buffer *root_buffer, t_buffer *buffer);
int				ft_fork_buffer(int fd, char **line,
					t_buffer *root_buffer, t_buffer **buffer);

# define RD_LINE	1
# define RD_EOF		0
# define RD_ERR		-1

#endif

#ifndef GET_NEXT_LINE.H
# define GET_NEXT_LINE.H

# ifndef BUFFERSIZE
#  define BUFFERSIZE 15

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

# endif
#endif
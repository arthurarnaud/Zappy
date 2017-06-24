/*
** network.c for zappy in PSU_2016_zappy/server/src
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sat Jun 24 12:06:12 2017 Antoine Baché
** Last update Sat Jun 24 12:17:33 2017 Antoine Baché
*/

#include <assert.h>
#include <errno.h>
#include "zappy_socket.h"
#include "zappy_network.h"

int32_t		zappy_network_write(t_zappy_socket const * const sock,
				    void const * data, int32_t const len)
{
  int32_t	ret;
  int32_t	total;
  char const	*buff;

  assert(sock && data);
  total = 0;
  buff = data;
  while (total != len)
    {
      errno = EINTR;
      ret = -1;
      while (errno == EINTR && ret == -1)
	ret = write(sock->sock, buff + total, len - total);
      if (ret == -1 || ret == 0)
	{
	  return (ret);
	}
      total += ret;
    }
  return (total);
}

int32_t		zappy_network_read(t_zappy_socket const * const sock,
				   void *data, int32_t const len)
{
  assert(sock && data);
  (void)sock, (void)data, (void)len;
  return (0);
}

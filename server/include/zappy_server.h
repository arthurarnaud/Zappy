/*
** zappy_server.h for zappy in PSU_2016_zappy/server/include
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Fri Jun 23 16:42:53 2017 Antoine Baché
** Last update Sun Jul  2 14:24:26 2017 Antoine Baché
*/

#ifndef ZAPPY_SERVER_H_
#define ZAPPY_SERVER_H_

#include <stdint.h>

/*
** Forward declaration of t_zappy
*/
typedef struct	s_zappy	t_zappy;

/*
** Server's loop
*/
int32_t			zappy_server(t_zappy * const data);

/*
** Accept a client on the server
*/
void			zappy_server_accept(t_zappy * const data);

#endif /* !ZAPPY_SERVER_H_ */

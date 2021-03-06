/*
** left.c for zappy in PSU_2016_zappy/server/src/client_cmd
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sun Jun 25 12:29:34 2017 Antoine Baché
** Last update Sun Jul  2 14:35:39 2017 Antoine Baché
*/

#include <stdlib.h>
#include <string.h>
#include "cqueue.h"
#include "clogger.h"
#include "zappy.h"
#include "zappy_alloc.h"
#include "zappy_client.h"
#include "zappy_client_cmd.h"
#include "zappy_client_game.h"
#include "zappy_message.h"
#include "zappy_graphic.h"

void			zappy_client_cmd_left(t_zappy_client * const cli,
					      t_zappy * const data,
					      char const * const arg)
{
  t_zappy_message	*msg;
  t_zappy_graph_arg	g;

  (void)arg;
  (void)data;
  LOG(LOG_DEBUG, "Treating left command");
  msg = zappy_alloc_message();
  if (msg)
    {
      msg->len = sizeof("ok\n") - 1;
      msg->msg = strdup("ok\n");
      if (msg->msg && cqueue_push(&cli->output_queue, msg))
	{
	  zappy_client_rotate_left(&cli->game);
	  g = (t_zappy_graph_arg){ cli, 0, 0 };
	  zappy_graph_send(&g, data, arg, &zappy_graph_ppo);
	  cli->state = CLI_RESPONSE;
	  cli->can_write = true;
	  return ;
	}
      zappy_free_message(msg);
    }
}

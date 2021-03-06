/*
** plv.c for zappy in PSU_2016_zappy/server/src/graphic_cmd
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Tue Jun 27 20:01:51 2017 Antoine Baché
** Last update Fri Jun 30 21:14:40 2017 Antoine Baché
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clogger.h"
#include "cqueue.h"
#include "zappy.h"
#include "zappy_alloc.h"
#include "zappy_client.h"
#include "zappy_graphic.h"
#include "zappy_message.h"

void			zappy_graph_plv(t_zappy_client * const cli,
					t_zappy_graph_arg *g,
					t_zappy *data,
					char const * const arg)
{
  t_zappy_message	*msg;
  char			buff[4096];
  t_zappy_client	*play;

  (void)data;
  (void)arg;
  LOG(LOG_DEBUG, "Treating graphic plv command");
  play = g->ptr;
  msg = zappy_alloc_message();
  if (msg)
    {
      msg->len = snprintf(buff, sizeof(buff),
			  "plv %d %d\n", play->id,
			  play->game.level);
      if (msg->len != -1)
	msg->msg = strdup(buff);
      if (msg->msg && cqueue_push(&cli->output_queue, msg))
	{
	  cli->state = CLI_RESPONSE;
	  cli->can_write = true;
	  return ;
	}
      zappy_free_message(msg);
    }
}

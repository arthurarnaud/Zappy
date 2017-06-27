/*
** pnw.c for zappy in PSU_2016_zappy/server/src/graphic_cmd
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Tue Jun 27 20:01:51 2017 Antoine Baché
** Last update Wed Jun 28 00:39:47 2017 Antoine Baché
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "clogger.h"
#include "zappy.h"
#include "zappy_alloc.h"
#include "zappy_client.h"
#include "zappy_graphic.h"
#include "zappy_message.h"

// TODO: norme
void			zappy_graph_pnw(t_zappy_client * const cli,
					t_zappy_graph_arg *g,
					t_zappy *data,
					char const * const arg)
{
  t_zappy_message	*msg;
  char			buff[4096];
  t_zappy_client	*p;

  LOG(LOG_DEBUG, "Treating graphic pnw command");
  (void)data;
  (void)arg;
  p = g->ptr;
  if (p->graphical)
    return ;
  msg = zappy_alloc_message();
  if (msg)
    {
      msg->len = snprintf(buff, sizeof(buff),
			  "pnw %d %d %d %d %d %s\n", p->id,
			  p->game.x, p->game.y, p->game.orientation + 1,
			  p->game.level, p->game.team_name);
      if (msg->len != -1)
	msg->msg = strdup(buff);
      if (msg->msg && cqueue_push(&cli->output_queue, msg))
	{
	  cli->state = CLI_RESPONSE;
	  cli->can_write = true;
	  return ;
	}
      free(msg->msg);
      zappy_free_message(msg);
    }
}
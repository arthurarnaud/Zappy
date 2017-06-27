/*
** right.c for zappy in PSU_2016_zappy/server/src/client_cmd
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sun Jun 25 12:29:34 2017 Antoine Baché
** Last update Mon Jun 26 14:00:46 2017 Antoine Baché
*/

#include <stdlib.h>
#include <string.h>
#include "clogger.h"
#include "zappy.h"
#include "zappy_alloc.h"
#include "zappy_client.h"
#include "zappy_client_cmd.h"
#include "zappy_client_game.h"
#include "zappy_message.h"

void			zappy_client_cmd_right(t_zappy_client * const cli,
					       t_zappy * const data,
					       char const * const arg)
{
  t_zappy_message	*msg;

  (void)arg;
  (void)data;
  LOG(LOG_DEBUG, "Treating right command");
  msg = zappy_alloc_message();
  if (msg)
    {
      msg->len = sizeof("ok\n") - 1;
      msg->msg = strdup("ok\n");
      if (msg->msg && cqueue_push(&cli->output_queue, msg))
	{
	  zappy_client_rotate_right(&cli->game);
	  cli->state = CLI_RESPONSE;
	  cli->can_write = true;
	  return ;
	}
      free(msg->msg);
      zappy_free_message(msg);
    }
}

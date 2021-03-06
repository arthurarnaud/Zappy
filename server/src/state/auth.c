/*
** auth.c for zappy in PSU_2016_zappy/server/src/state
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sat Jun 24 00:19:33 2017 Antoine Baché
** Last update Sun Jul  2 17:53:46 2017 Antoine Baché
*/

#include <stdlib.h>
#include <string.h>
#if defined(_WIN32)
#include "zappy_windows.h"
#endif
#include "clogger.h"
#include "cqueue.h"
#include "zappy_alloc.h"
#include "zappy_client.h"
#include "zappy_client_state.h"
#include "zappy_message.h"

void			zappy_cli_state_auth_r(t_zappy_client * const cli,
					       t_zappy * const data,
					       char const * const msg)
{
  (void)data;
  cli->game.team_name = strdup(msg);
  if (!cli->game.team_name)
    {
      cli->authenticated = false;
      cli->connected = false;
      return ;
    }
  LOG(LOG_DEBUG, "Team name %s", cli->game.team_name);
  cli->state = CLI_CONNECTED;
  cli->can_write = true;
  cli->authenticated = false;
}

void			zappy_cli_state_auth_w(t_zappy_client * const cli,
					       t_zappy * const data)
{
  t_zappy_message	*cur;

  (void)data;
  cur = zappy_alloc_message();
  if (cur)
    {
      cur->len = sizeof("WELCOME\n") - 1;
      cur->msg = strdup("WELCOME\n");
      if (cur->msg && cqueue_push(&cli->output_queue, cur))
	{
	  cli->can_write = false;
	  return ;
	}
      zappy_free_message(cur);
    }
  cli->connected = false;
}

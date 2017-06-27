/*
** vision.c for zappy in PSU_2016_zappy/server/src
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Mon Jun 26 17:31:40 2017 Antoine Baché
** Last update Tue Jun 27 13:18:04 2017 Antoine Baché
*/

#include <assert.h>
#include <string.h>
#include "zappy_client.h"
#include "zappy_map.h"
#include "zappy_client_vision.h"

static void			zappy_vision_line(t_zappy_map const *
						  const map,
						  t_zappy_client const *
						  const cli,
						  t_zappy_client_vision *
						  const vis,
						  int32_t infos[])
{
  t_zappy_map_case const	*map_case;
  int32_t			j;
  int32_t			ndx;
  int32_t			off;

  j = 0;
  off = (infos[3] + 1) * (infos[3] + 1);
  while (j < infos[2])
    {
      ndx = off - infos[2] + j;
      map_case = zappy_get_map_case(map, cli->game.x + infos[0] + j,
				    cli->game.y + infos[1]);
      memcpy(vis->map[ndx].res, map_case->content,
	     sizeof(vis->map[infos[3] + j].res));
      vis->map[ndx].players = map_case->nb_players;
      ++j;
    }
}

void				zappy_vision_exec(t_zappy_map const *
						  const map,
						  t_zappy_client const *
						  const cli,
						  t_zappy_client_vision *
						  const vis)
{
  int32_t			off[3];
  int32_t			i;
  int32_t			orient;

  assert(map && cli && vis);
  orient = cli->game.orientation;
  off[0] = 0;
  off[1] = 0;
  off[2] = 1;
  vis->nb_lines = cli->game.vision + 1;
  i = 0;
  while (i < vis->nb_lines)
    {
      zappy_vision_line(map, cli, vis,
			(int32_t[]){ off[!(orient == CLI_NORTH ||
					  orient == CLI_SOUTH)],
			    off[orient == CLI_NORTH || orient == CLI_SOUTH],
			    off[2], i });
      off[0] += (orient == CLI_NORTH || orient == CLI_WEST) ? -1 : 1;
      off[1] += (orient == CLI_NORTH || orient == CLI_EAST) ? 1 : -1;
      off[2] += 2;
      ++i;
    }
}

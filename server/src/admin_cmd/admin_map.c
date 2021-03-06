/*
** admin_map.c for zappy in PSU_2016_zappy/server/src/admin_cmd
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sat Jul  1 23:26:56 2017 Antoine Baché
** Last update Sun Jul  2 23:14:57 2017 Antoine Baché
*/

#include <assert.h>
#include <stdio.h>
#include "clogger.h"
#include "zappy.h"
#include "zappy_admin_cmd.h"
#include "zappy_resource.h"
#include "zappy_map.h"

void			zappy_admin_add_tile(t_zappy * const data,
					     char const * cmd)
{
  int32_t		x;
  int32_t		y;
  char			buff[4096];
  int32_t		res;
  t_zappy_map_tile	*map;

  assert(data && cmd);
  LOG(LOG_DEBUG, "Treating Admin command map add '%s'", cmd);
  if (sscanf(cmd, "%d %d %s", &x, &y, buff) != -1)
    {
      x %= data->map.width;
      y %= data->map.height;
      res = zappy_get_resource_by_name(buff);
      if (res != RES_UNKNOWN)
	{
	  LOG(LOG_INFO, "Administrator adding %s to map tile %dx%d",
	      buff, x, y);
	  map = &data->map.data[y][x];
	  ++map->content[res];
	  zappy_admin_update_tile(x, y, data);
	}
    }
}

void			zappy_admin_rm_tile(t_zappy * const data,
					    char const * cmd)
{
  int32_t		x;
  int32_t		y;
  char			buff[4096];
  int32_t		res;
  t_zappy_map_tile	*map;

  assert(data && cmd);
  LOG(LOG_DEBUG, "Treating Admin command map rm '%s'", cmd);
  if (sscanf(cmd, "%d %d %s", &x, &y, buff) != -1)
    {
      x %= data->map.width;
      y %= data->map.height;
      res = zappy_get_resource_by_name(buff);
      if (res != RES_UNKNOWN)
	{
	  LOG(LOG_INFO, "Administrator removing %s from map tile %dx%d",
	      buff, x, y);
	  map = &data->map.data[y][x];
	  if (map->content[res] > 0)
	    --map->content[res];
	  zappy_admin_update_tile(x, y, data);
	}
    }
}

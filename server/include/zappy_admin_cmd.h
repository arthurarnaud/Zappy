/*
** zappy_admin_cmd.h for zappy in PSU_2016_zappy/server/include
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Mon Jun 26 22:27:51 2017 Antoine Baché
** Last update Mon Jun 26 23:35:35 2017 Antoine Baché
*/

#ifndef ZAPPY_ADMIN_CMD_H_
#define ZAPPY_ADMIN_CMD_H_

#include <stdint.h>

/*
** Forward declaration of t_zappy
*/
typedef struct		s_zappy	t_zappy;

typedef enum		e_zappy_admin_cmd_list
  {
    ADM_HELP		= 0,
    ADM_STOP,
    ADM_INFO,
    ADM_INC,
    ADM_DEC,
    NB_ADM_CMD
  }			t_zappy_admin_cmd_list;

#if defined __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

typedef struct		s_zappy_admin_cmd
{
  void			(*callback)(t_zappy * const data);
  char const		*cmd;
  int32_t		len;
}			t_zappy_admin_cmd;

#if defined __clang__
#pragma clang diagnostic pop
#endif

void			zappy_admin_cmd_help(t_zappy * const data);
void			zappy_admin_cmd_stop(t_zappy * const data);
void			zappy_admin_cmd_info(t_zappy * const data);
void			zappy_admin_cmd_inc_freq(t_zappy * const data);
void			zappy_admin_cmd_dec_freq(t_zappy * const data);

#endif /* !ZAPPY_ADMIN_CMD_H_ */

/*
** zappy_admin_cmd.h for zappy in PSU_2016_zappy/server/include
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Mon Jun 26 22:27:51 2017 Antoine Baché
** Last update Sun Jul  2 23:15:59 2017 Antoine Baché
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
    ADM_RESET,
    ADM_RES_RAND,
    ADM_RES_FOOD,
    ADM_RES_LINEMATE,
    ADM_RES_DERAUMERE,
    ADM_RES_SIBUR,
    ADM_RES_MENDIANE,
    ADM_RES_PHIRAS,
    ADM_RES_THYSTAME,
    ADM_SPAWN_EGG,
    ADM_BROADCAST,
    ADM_ADD_tile,
    ADM_RM_tile,
    NB_ADM_CMD
  }			t_zappy_admin_cmd_list;

#if defined __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

typedef struct		s_zappy_admin_cmd
{
  void			(*callback)(t_zappy * const data,
				    char const * cmd);
  char const		*cmd;
  int32_t		len;
}			t_zappy_admin_cmd;

#if defined __clang__
#pragma clang diagnostic pop
#endif

void			zappy_admin_cmd_help(t_zappy * const data,
					     char const * cmd);
void			zappy_admin_cmd_stop(t_zappy * const data,
					     char const * cmd);
void			zappy_admin_cmd_info(t_zappy * const data,
					     char const * cmd);
void			zappy_admin_cmd_info_team(t_zappy * const data);
void			zappy_admin_cmd_reset(t_zappy * const data,
					      char const * cmd);
void			zappy_admin_cmd_inc_freq(t_zappy * const data,
						 char const * cmd);
void			zappy_admin_cmd_dec_freq(t_zappy * const data,
						 char const * cmd);
void			zappy_admin_cmd_egg(t_zappy * const data,
					    char const *cmd);
void			zappy_admin_cmd_broadcast(t_zappy * const data,
						  char const *cmd);

/*
** Resources commands
*/
void			zappy_admin_cmd_res(t_zappy * const data,
					    int32_t const res);
void			zappy_admin_cmd_res_rand(t_zappy * const data,
						 char const * cmd);
void			zappy_admin_cmd_res_food(t_zappy * const data,
						 char const *cmd);
void			zappy_admin_cmd_res_linemate(t_zappy * const data,
						     char const *cmd);
void			zappy_admin_cmd_res_deraumere(t_zappy * const data,
						      char const * cmd);
void			zappy_admin_cmd_res_sibur(t_zappy * const data,
						  char const * cmd);
void			zappy_admin_cmd_res_mendiane(t_zappy * const data,
						     char const * cmd);
void			zappy_admin_cmd_res_phiras(t_zappy * const data,
						   char const * cmd);
void			zappy_admin_cmd_res_thystame(t_zappy * const data,
						     char const * cmd);

/*
** Map tile commands
*/
void			zappy_admin_add_tile(t_zappy * const data,
					     char const *cmd);
void			zappy_admin_rm_tile(t_zappy * const data,
					    char const *cmd);
void			zappy_admin_update_tile(int32_t const x,
						int32_t const y,
						t_zappy * const data);

/*
** Output
*/
int32_t			zappy_adm_send(t_zappy *data, char const * fmt, ...);

#endif /* !ZAPPY_ADMIN_CMD_H_ */

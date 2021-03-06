/*
** zappy_windows.h for zappy in PSU_2016_zappy/server/include
**
** Made by Antoine Baché
** Login   <antoine.bache@epitech.net>
**
** Started on  Sun Jul  2 17:49:43 2017 Antoine Baché
** Last update Sun Jul  2 21:04:03 2017 Antoine Baché
*/

#ifndef ZAPPY_WINDOWS_H_
#define ZAPPY_WINDOWS_H_

#if !defined(_WIN32)
#error "This header should only be included on Windows"
#endif

#include <stdbool.h>

#define strdup(s)	_strdup(s)
#define write(d, s, l)	_write(d, s, l)
#define read(f, b, n)	_read(f, b, n)
#define fdopen(f, s)	_fdopen(f, s)

bool		zappy_winsock_init();
void		zappy_winsock_deinit();

#endif /* !ZAPPY_WINDOWS_H_ */

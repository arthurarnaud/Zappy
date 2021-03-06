##
## colors.mk for zappy in PSU_2016_zappy/mk
##
## Made by Antoine Baché
## Login   <antoine.bache@epitech.net>
##
## Started on  Fri Jun 23 14:04:49 2017 Antoine Baché
## Last update Fri Jun 23 14:06:26 2017 Antoine Baché
##

COLOR_SUPPORTED=	1

ifeq ($(COLOR_SUPPORTED), 0)
# Colors definitions
CLEAR=

# Bold High Intens
BLACK=
RED=
GREEN=
YELLOW=
BLUE=
PURPLE=
CYAN=
WHITE=

# Regular
BLACK_R=
RED_R=
GREEN_R=
YELLOW_R=
BLUE_R=
PURPLE_R=
CYAN_R=
WHITE_R=

# Bold
BLACK_B=
RED_B=
GREEN_B=
YELLOW_B=
BLUE_B=
PURPLE_B=
CYAN_B=
WHITE_B=

# High Intens
BLACK_H=
RED_H=
GREEN_H=
YELLOW_H=
BLUE_H=
PURPLE_H=
CYAN_H=
WHITE_H=

# Underline
BLACK_U=
RED_U=
GREEN_U=
YELLOW_U=
BLUE_U=
PURPLE_U=
CYAN_U=
WHITE_U=

# Background
BLACK_BG=
RED_BG=
GREEN_BG=
YELLOW_BG=
BLUE_BG=
PURPLE_BG=
CYAN_BG=
WHITE_BG=

# High Intens Background
BLACK_BG_H=		\033[0;100m
RED_BG_H=		\033[0;101m
GREEN_BG_H=		\033[0;102m
YELLOW_BG_H=		\033[0;103m
BLUE_BG_H=		\033[0;104m
PURPLE_BG_H=		\033[0;105m
CYAN_BG_H=		\033[0;106m
WHITE_BG_H=		\033[0;107m
else
# Colors definitions
CLEAR=			\033[0m

# Bold High Intens
BLACK=			\033[1;90m
RED=			\033[1;91m
GREEN=			\033[1;92m
YELLOW=			\033[1;93m
BLUE=			\033[1;94m
PURPLE=			\033[1;95m
CYAN=			\033[1;96m
WHITE=			\033[1;97m

# Regular
BLACK_R=		\033[0;30m
RED_R=			\033[0;31m
GREEN_R=		\033[0;32m
YELLOW_R=		\033[0;33m
BLUE_R=			\033[0;34m
PURPLE_R=		\033[0;35m
CYAN_R=			\033[0;36m
WHITE_R=		\033[0;37m

# Bold
BLACK_B=		\033[1;30m
RED_B=			\033[1;31m
GREEN_B=		\033[1;32m
YELLOW_B=		\033[1;33m
BLUE_B=			\033[1;34m
PURPLE_B=		\033[1;35m
CYAN_B=			\033[1;36m
WHITE_B=		\033[1;37m

# High Intens
BLACK_H=		\033[0;90m
RED_H=			\033[0;91m
GREEN_H=		\033[0;92m
YELLOW_H=		\033[0;93m
BLUE_H=			\033[0;94m
PURPLE_H=		\033[0;95m
CYAN_H=			\033[0;96m
WHITE_H=		\033[0;97m

# Underline
BLACK_U=		\033[4;30m
RED_U=			\033[4;31m
GREEN_U=		\033[4;32m
YELLOW_U=		\033[4;33m
BLUE_U=			\033[4;34m
PURPLE_U=		\033[4;35m
CYAN_U=			\033[4;36m
WHITE_U=		\033[4;37m

# Background
BLACK_BG=		\033[40m
RED_BG=			\033[41m
GREEN_BG=		\033[42m
YELLOW_BG=		\033[43m
BLUE_BG=		\033[44m
PURPLE_BG=		\033[45m
CYAN_BG=		\033[46m
WHITE_BG=		\033[47m

# High Intens Background
BLACK_BG_H=		\033[0;100m
RED_BG_H=		\033[0;101m
GREEN_BG_H=		\033[0;102m
YELLOW_BG_H=		\033[0;103m
BLUE_BG_H=		\033[0;104m
PURPLE_BG_H=		\033[0;105m
CYAN_BG_H=		\033[0;106m
WHITE_BG_H=		\033[0;107m
endif

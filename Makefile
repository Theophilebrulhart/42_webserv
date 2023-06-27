# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:06:30 by tbrulhar          #+#    #+#              #
#    Updated: 2023/03/15 17:31:06 by tbrulhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	Source/main.cpp
SRC +=	${addprefix Network/Socket/, ASocket.cpp BindSocket.cpp ConnectSocket.cpp \
ListenSocket.cpp}
SRC +=	${addprefix Network/Server/, AServer.cpp TestServer.cpp}
SRC +=	${addprefix Network/Parsing/RequestInfo/, RequestParsing.cpp GetInfo.cpp GetFormValue.cpp}
SRC +=	${addprefix Network/Parsing/ResponsInfo/, ResponsInfo.cpp}
SRC +=	${addprefix Network/Parsing/ResponsInfo/CreateRespons/, GetResponsContent.cpp GetStatus.cpp Utils.cpp}
OBJ = $(SRC:.cpp=.o) 
GPP = c++
RM = rm -f 
GFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

NAME = webserv

all: $(NAME) 

$(NAME): $(OBJ) 
		$(GPP) $(GFLAGS) -o $(NAME) $(OBJ) 

clean: 
		$(RM) $(OBJ) 

fclean: clean 
		$(RM) $(NAME) 

re: fclean $(NAME) 

.PHONY:        all clean fclean re
NAME = libft.a

CC = cc
CFLAGS += -Wall -Wextra -Werror
RM = rm -f

SRCS = ft_calloc.c ft_isascii.c ft_itoa.c ft_memcpy.c ft_putchar_fd.c \
      ft_putstr_fd.c ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c \
      ft_tolower.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c \
      ft_memmove.c ft_putendl_fd.c ft_split.c ft_striteri.c ft_strlcpy.c \
      ft_strncmp.c ft_strtrim.c ft_toupper.c ft_bzero.c  ft_isalpha.c  \
      ft_isprint.c ft_memcmp.c ft_memset.c ft_putnbr_fd.c ft_strchr.c \
      ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c \
	  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	  libftprintf/ft_printf.c libftprintf/ft_printf_utils.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c

all: $(NAME)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

bonus:	$(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c	$<	-o	$@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

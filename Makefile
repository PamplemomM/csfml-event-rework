##
## PamplemomM PROJECT, 2025
## Makefile
## File description:
## Makefile for the event rework of the csfml project
##

NAME    =	event_rework

SRCS	=	$(shell find src/ -type f -name '*.c')

CFLAGS	=	-Wall -Wextra -Wshadow -I./../include

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

increment_counter:
	@if [ ! -f .counter ]; then echo -n "Compiling source files: [00]" ; \
	echo 0 > .counter; fi; \
	count=$$(cat .counter); \
	new_count=$$((count + 1)); \
	echo $$new_count > .counter; \
	for i in $$(seq 1 4); do \
		printf "\b \b"; \
	done; \
	if [ $$new_count -lt 10 ]; \
	then printf "[0$$new_count]"; \
	else printf "[$$new_count]"; fi;


%.o	:	%.c
		@$(MAKE) increment_counter --no-print-directory
		@gcc -c $< -o $@

.PHONY	:	all clean fclean re valgrind

$(NAME)	:	$(OBJS)
		@echo ""
		@rm .counter
		@echo "Compiled source files into object files."
		@gcc -o $(NAME) $(OBJS) -l csfml-graphics -l csfml-system \
			-l csfml-audio -lcsfml-window -lm
		@echo "Compiled successfully!"

valgrind	:
		@gcc -o $(NAME) $(OBJS) -l csfml-graphics -l csfml-system \
			-l csfml-audio -lcsfml-window -lm $(CFLAGS) -g3
		@echo "Compiled successfully! (valgrind edition)"

clean	:
		@rm -rf $(OBJS)
		@rm -rf .counter
		@echo "Removed object files."

fclean	:	clean
		@rm -rf $(NAME)
		@echo "Removed binary."

re	:	fclean all

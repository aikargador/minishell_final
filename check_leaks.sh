valgrind --suppressions=readline.supp --suppressions=ls.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./minishell

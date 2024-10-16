/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/15 17:18:53 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <sys/types.h>
//# include <sys/wait.h>
# include "../libft/libft.h"

typedef enum e_lexer
{
	REDIR_INPUT_1,
	REDIR_OUTPUT_1,
	REDIR_INPUT_2,
	REDIR_OUTPUT_2,
	PIPE,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
	OTHER,
}	t_lexer;

typedef struct s_token
{
	char			*token;
	t_lexer			type;
	struct s_token	*next;
}			t_token;

typedef struct s_ast
{
	int				index;
	char			*cmd;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
}			t_ast;

typedef struct s_minish
{
	int				**pipes;
	char			**env_list;
	char			*cwd;
	struct s_token	*tk_list;
	struct s_ast	*cmd_list;
	int				fd_in;
	int				fd_out;
}			t_minish;

//Utils - Initialising
int		testin(void);

#endif

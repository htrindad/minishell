/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:09 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/11 16:16:24 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Imports
# include "../libs/neo_libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

// Debug mode
# ifndef DEBUG
#  define DEBUG 0
# endif

// Enums
typedef enum	e_case
{
	PIPE,
	OUT,
	APPEND,
	IN,
	DEL,
}		t_case;

// Typedefs
typedef struct s_ms	t_ms;

// Structs
typedef struct	s_builtin
{
	const char	*name;
	int			(*f)(t_ms *);
}		t_builtin;

typedef struct	s_token
{
	char			**value;
	struct s_token	*next;
	t_case			cchar;
}		t_token;

typedef struct	s_env
{
	char			*key;
	struct s_env	*next;
	char			*value;
}		t_env;

typedef struct	s_ms
{
	t_env			*env;
	char			*input;
	char			**scases;
	bool			*running;
	int				pid;
	int				last_status;
	t_builtin		*builtin;
	t_token			*tokens;
}		t_ms;

// Functions
t_token				*lexing(t_ms *shell);
int					add_token(t_token **head, char *value);
char				**ft_split_shell(t_ms *shell);
char				*handle_env_var(t_ms *shell);
size_t				iterate_through_q(const char *s, size_t i,
						char *quote_type);
size_t				iteration_cases(const char *s, size_t i);
int					has_env_var(const char *s);
char				*extract_env_var(t_ms *shell, int *i);
char				*var_cases(t_ms *shell, int *i);
char				*conc_char(char c);
void				free_args(char **args);
void				free_env(t_env *env);
void				free_tokens(t_token *tokens);
void				clean_ms(t_ms *shell);
t_env				*get_env(char **env);
void				init_ms(t_ms *shell);
int					quit(t_ms *);
void				em(char *str, t_ms *ms);

#endif

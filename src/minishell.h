/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:09 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 18:33:27 by htrindad         ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>

// Debug mode
# ifndef DEBUG
#  define DEBUG 0
# endif

// Enums
typedef enum	e_case
{
	NONE,
	PIPE,
	OUT,
	APPEND,
	IN,
	HEREDOC,
}		t_case;

typedef enum	e_chcas
{
	NORMAL,
	BACK,
	DOT,
}

// Typedefs
typedef struct s_ms	t_ms;
typedef struct s_token	t_token;

// Structs
typedef struct	s_builtin
{
	const char	*name;
	int			(*f)(t_token *);
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
	struct s_env	*prev;
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
t_token	*lexing(t_ms *shell);
bool	add_token(t_token **head, char **value, t_ms *ms, size_t *l);
char	***ft_split_shell(t_ms *shell);
char	*handle_env_var(t_ms *shell);
size_t	iterate_through_q(const char *s, size_t i,
			t_ms *ms);
size_t	iteration_cases(const char *s, size_t i, char **cases, t_ms *ms);
bool	has_env_var(const char *s);
char	*extract_env_var(t_ms *shell, int *i);
char	*var_cases(t_ms *shell, int *i);
char	*conc_char(char c);
void	free_args(char **args);
void	free_env(t_env *env);
void	free_tokens(t_token *tokens);
void	clean_ms(t_ms *shell);
t_env	*get_env(char **env);
void	init_ms(t_ms *shell);
void	em(char *str, t_ms *ms);
size_t	spec_case(char const *sub, char **cases, size_t *l, size_t y, bool *cas);
char	**duplicator(char **arg);
size_t	count_cases(char const *s, t_ms *ms);
void	sig_handler(int sig, siginfo_t *s, void *content);
void	refresh(t_ms *);
bool	sub(char ***array, char const *s, t_ms *ms, size_t *len);
size_t	ft_count_words(char const *s, t_ms *ms);
void	executor(t_ms *ms);
int		quit(t_ms *);
int		pwd(t_ms *);
int		env(t_ms *);
int		change_dir(t_ms *);
t_env	*get_pwd(t_env *);
char	*get_home(t_env *);
void	set_pwd(char *c, t_env *env, t_ms *ms);
int		error_exp(char *);
bool	check_exp_arg(char *);
bool	bi_export(t_ms *);
bool	add_env(t_env **head, char *env);
bool	check_unst(char *);
bool	rm_env(t_env **head, char *arg);
bool	unset(t_ms *);
int		echo(t_ms *);

#endif

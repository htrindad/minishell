/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:09 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/08 20:57:28 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Imports
# include "../libs/neo_libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

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
}		t_chcas;

// Typedefs
typedef struct s_ms			t_ms;
typedef struct s_token		t_token;
typedef struct sigaction	t_sa;

// Structs
typedef	struct s_redir
{
	char			*filename;
	t_case			type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_fds
{
	t_redir	*in;
	t_redir	*out;
}	t_fds;

typedef struct	s_builtin
{
	const char	*name;
	int			(*f)(t_ms *);
}		t_builtin;

typedef struct	s_token
{
	char			**value;
	struct s_token	*next;
	t_fds			*fds;
	t_case			cchar;
}		t_token;

typedef struct	s_env
{
	char			*key;
	struct s_env	*next;
	struct s_env	*prev;
	char			*value;
}		t_env;

typedef struct	s_ms
{
	t_env			*env;
	char			*input;
	char			**scases;
	bool			running;
	int				pid;
	int				last_status;
	t_sa			si;
	t_sa			sq;
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
int		quit(t_ms *);
void	em(char *str, t_ms *ms);
size_t	spec_case(char const *sub, char **cases, size_t *l, size_t y, bool *cas);
char	**duplicator(char **arg);
size_t	count_cases(char const *s, t_ms *ms);
void	sig_handler(int sig, siginfo_t *s, void *content);
void	refresh(int);
bool	sub(char ***array, char const *s, t_ms *ms, size_t *len);
size_t	ft_count_words(char const *s, t_ms *ms);
bool	is_builtin(char *cmd);
int		exec_builtin(t_token *token, t_ms *ms, bool is_parent);
char	**get_paths(char **env, t_ms *ms);
char	*find_command(char *cmd_args, char **env, t_ms *ms);
void	executor(t_ms *ms);
int		pwd(t_ms *);
int		env(t_ms *);
int		change_dir(t_ms *);
t_env	*get_pwd(t_env *);
char	*get_home(t_env *);
void	set_pwd(char *c, size_t size, t_env *env, t_ms *ms);
int		error_exp(char *);
int		bi_export(t_ms *);
bool	add_env(t_env **head, char *env);
bool	check_unst(char *);
bool	rm_env(t_env **head, char *arg);
int		unset(t_ms *);
int		echo(t_ms *);
void	c_len(size_t *len, char const *s);
void	trimmer(char ***array, char *tmp, size_t itr);
int		parse_redirections(t_token **tokens);
int		handle_redirections(t_token **tokens);
void	cleanup_redir(t_token **tokens);
void	remove_token(t_token **head, t_token *to_remove);
void	cleanup_redir(t_token **tokens);
bool	is_redirection(t_case type);


void	print_tokens(t_token *head);


#endif

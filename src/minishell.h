/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:35:00 by mely-pan          #+#    #+#             */
/*   Updated: 2025/03/26 19:34:44 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/neo_libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	int				type;
}					t_token;

typedef struct s_env
{
	char			*key;
	struct s_env	*next;
	char			*value;
}					t_env;

typedef struct s_ms
{
	t_env			*env;
	char			*input;
	int				pid;
	int				last_status;
	t_token			**tokens;
}					t_ms;

void				lexing(t_ms *shell, char **env);
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

t_env				*get_env(char **env);

void				init_ms(t_ms *shell);

#endif

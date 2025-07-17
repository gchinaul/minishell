/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:39:11 by gchinaul          #+#    #+#             */
/*   Updated: 2025/07/01 22:54:28 by gchinaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "list.h"
# include <stddef.h>
# include <stdlib.h>

typedef struct s_split_ctx
{
	size_t	i;
	size_t	start;
	size_t	len;
}			t_split_ctx;

size_t		ft_strlen(const char *str);
long		ft_atol(const char *str);
int			ft_matrixlen(char **matrix);
void		ft_free_matrix(char ***matrix);
int			is_numeric(const char *s);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strdup(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_3(const char *s1, const char *s2, const char *s3);
void		ft_lstadd_back(t_list **alst, t_list *new);
int			ft_countchar(char *s, char c);
int			ft_putstr_fd(const char *s, int fd);
int			ft_putchar_fd(char c, int fd);
int			ft_strchr_i(const char *s, int c);
int			ft_putendl_fd(const char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_itoa(int n);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_lstsize(t_list *lst);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strrchr(const char *s, int c);
void		free_split_result(char **result, size_t j);
int			split_loop(const char *s, char c, char **result);
int			split_fill(const char *s, char c, char **result, size_t len);
int			find_next_word_s(const char *s, char c, t_split_ctx *ctx);
char		*extract_word_s(const char *s, size_t start, size_t end);
char		*ft_strtok(char *str, const char *delim, char **saveptr);
t_list		*ft_lstget_b(t_list *lst, int index);
t_list		*ft_lstnew(void *content);
char		**ft_split(const char *s, char c);

#endif
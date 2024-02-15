/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:54:46 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/15 14:51:56 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# define BUFFER_SIZE 100

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	*ft_memset(void *ptr, int c, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_memchr(const void *ptr, int c, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t num);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memmove(void *str1, const void *str2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *source);
char	*ft_substr(const char *source, unsigned int start, size_t finish);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strcpy(char *destination, const char *source);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
int		ft_toupper(unsigned char c);
int		ft_tolower(int c);
int		ft_isprint(int c);
int		ft_isdigit(char c);
int		ft_isascii(char c);
int		ft_isalpha(char c);
int		ft_isalnum(char c);
int		ft_islower(char c);
int		ft_isupper(char c);
int		ft_atoi(const char *str);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
char	*ft_itoa(int n);
char	*get_next_line(int fd);

#endif

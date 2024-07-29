/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:34:03 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/07/29 14:07:31 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_wc(char *s1, char *s2)
{
	size_t	length;
	char	*p;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	length = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (length + 1));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[j])
		p[i++] = s2[j++];
	p[length] = '\0';
	return (p);
}

void get_listing(char *pattern, t_token *start, t_token *end)
{
	struct dirent *entry;
	char pwd[1024];
	int count = 0;
	char **arr;
	(void) pattern;
	(void)start;
	(void)end;

	getcwd(pwd, 1024);
	DIR *dir = opendir(pwd);
	if (dir == NULL) {
        perror("opendir");
        return;
    }
	while ((entry = readdir(dir)) != NULL) 
	{
		count++;
        // printf("%s\n", entry->d_name);
    }
	arr=malloc((count + 1) * sizeof(char *));
	if(!arr)
		return ;
	int i = 0;
	while ((entry = readdir(dir)) != NULL) 
	{
		arr[i]= entry->d_name;
        // printf("%s\n", entry->d_name);
		i++;
    }
	arr[i]= NULL;
	i = 0;
	int j;
	int k;
	while(arr[i])
	{
		k = 0;
		j = 0;	
		while(arr[i][j])
		{
			if(pattern[k] == '*')
			{
				k++;
				while(arr[i][j] != pattern[k])
					j++;
			}
			if(arr[i][j] == pattern[k])
			{
				j++;
				k++;
			}
			else
			{
				printf("doesnt match");
				break;
			}
			printf("%s matches\n",arr[i]);
		}
		i++;
	}
	
}

void wildcard_sub(t_token *head, t_token *env)
{
	(void) env;
	char *pattern;
	t_token *start;
	char *freee = NULL;
	t_token *tmp = head->next;
	while(tmp->type != E_CMD)
	{
		pattern = NULL;
		if(tmp->type == WILD)
		{
			start = tmp;
			if(is_string(tmp->prev) == 1)
				(start = tmp->prev,tmp = tmp->prev);
			while(tmp->type != E_CMD && (is_string(tmp) == 1 || tmp->type == WILD))
			{
				freee = pattern;
				pattern = ft_strjoin_wc(freee, tmp->value);
				free(freee);
				tmp = tmp->next;
			}
		}
		if(pattern != NULL)
		{
			get_listing(pattern,start,tmp);
		}
		if(tmp->type != E_CMD)
			tmp = tmp->next;
	}
}
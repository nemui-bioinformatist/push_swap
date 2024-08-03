/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomura <rnomura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:08:55 by rnomura           #+#    #+#             */
/*   Updated: 2024/07/20 16:21:45 by rnomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*使用したlibftの関数*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/*新規の関数*/
int ft_abs(int x)
{
	if (x >= 0)
		return(x);
	else
		return(-1 * x);
}

static void sx(int **stack1)/*stack間の変更はないのでsizeは変わらない*/
{
	int tmp;
	tmp = (*stack1)[0];
	(*stack1)[0] = (*stack1)[1];
	(*stack1)[1] = tmp;
}

static void rx(int **stack1, int stack1_len)/*正の方向への回転、stack間の変更はないのでsizeは変わらない*/
{
	int tmp;
	int i;
	int len;
	
	len = stack1_len;
	tmp = (*stack1)[0];
	i = 0;
	while((1 < len--) && ++i)
		(*stack1)[i - 1] = (*stack1)[i];
	(*stack1)[stack1_len - 1] = tmp;
}

static void rrx(int **stack1, int stack1_len)/*負の方向への回転、stack間の変更はないのでsizeは変わらない*/
{
	int tmp;
	int i;
	int len;

	len = stack1_len;
	tmp = (*stack1)[0];
	while(1 < len--)
		(*stack1)[(len + 1) % stack1_len] = (*stack1)[len];
	(*stack1)[++len] = tmp;
}

static void px(int **stack1, int **stack2, int *stack1_len, int *stack2_len)
{
	int i;
	int len1;
	int len2;

	len1 = *stack1_len;
	len2 = *stack2_len;
	i = 0;
	while (1 < len1--)
		(*stack1)[len1 + 1] = (*stack1)[len1];
	(*stack1)[0] = (*stack2)[0];
	while((1 < len2--) && ++i)
		(*stack2)[i - 1] = (*stack2)[i];
	(*stack1_len)++;
	(*stack2_len)--;
}

void run(char *cmd, int **stack1, int stack1_len, int x)/*rx or rrxのみ複数回*/
{
	size_t len;
	int time;
	void	(*f)(int **, int);

	len = ft_strlen(cmd);
	time = ft_abs(x);
	if(!ft_strncmp(cmd, "ra", len) || !ft_strncmp(cmd, "rb", len) || !ft_strncmp(cmd, "rr", len))
		f = &rx;
	else
		f = &rrx;
	while (time--)
		f(stack1, stack1_len);
}

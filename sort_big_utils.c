/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomura <rnomura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:53:44 by rnomura           #+#    #+#             */
/*   Updated: 2024/08/03 15:35:14 by rnomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int stack_minmax(int *stack, int size, int num)
{
	int x;
	int i;

	i = 0;
	if (num < stack_min(stack))
		x = stack_min(stack);
	else
	{
		x = stack_max(stack);
		i++;//1234567の状況で、8を追加するなら0番目だから回転がいらない。iはsize - iで0になるはず
	}
	while (i++ < size)
	{
		if (stack[i] == x)
			break;
	}
	if (i >= (size + 1) / 2)
		i = -1 * (size - i)
	return (i);
}

int stack_mid(int *stack, int size, int num)
{

}

int get_min_rotate(int *stack_a, int *stack_b, int *a, int *b, int size_a, int size_b)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i++ < size_b)
	{
		num = stack_b[i];
		if (num < stack_min(stack_a) || num > stack_max(stack_a))
			j = stack_minmax(stack_a, size_a, num);//stack_aのindex
		else
			j = stack_mid(stack_a, size_a, num);//stack_aのindex
		k = i;//０から数えたときのstack_bのindex
		if (i >= (size_b + 1) / 2)
			k = -1 * (size_b - i);//後ろから数えたほうが早いときは負に
		//arrayのindexは前からは0,1,2,3,4,,,後ろからは-1,-2,-3,,,,この違い
		if (i == 0 || ft_abs(*a) + ft_abs(*b) > ft_abs(j) + ft_abs(k))//初期はa,b共に0
		{
			//i == 0のときに行ったん更新、それ以降はそれの和より小さかったら更新
			*a = j;
			*b = k;
		}
	}//stack_bの中身を全て探索したら終わり
}

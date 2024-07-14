/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomura <rnomura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:34:24 by rnomura           #+#    #+#             */
/*   Updated: 2024/07/14 19:04:25 by rnomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void ss(int **stack_a, int **stack_b, int flag, int len_a, int len_b)
{
	int tmp;

	if (flag == 0)
	{
		tmp = (*stack_a)[0];
		(*stack_a)[0] = (*stack_a)[1];
		(*stack_a)[1] = tmp;
	}
	else if (flag == 1)
	{
		tmp = (*stack_b)[0];
		(*stack_b)[0] = (*stack_b)[1];
		(*stack_b)[1] = tmp;
	}
	else
	{
		ss(stack_a, stack_b, 0, len_a, len_b);
		ss(stack_a, stack_b, 1, len_b, len_b);
	}
}

static void rr(int **stack_a, int **stack_b, int flag, int len_a, int len_b)
{
	int tmp;
	int i;
	int stock_len;

	if (flag == 0)
	{
		stock_len = len_a;
		tmp = (*stack_a)[0];
		i = 0;
		while((1 < len_a--) && ++i)
			(*stack_a)[i - 1] = (*stack_a)[i];
		(*stack_a)[stock_len - 1] = tmp;
	}
	else if (flag == 1)
	{
		stock_len = len_b;
		tmp = (*stack_b)[0];
		i = 0;
		while((1 < len_b--) && ++i)
			(*stack_b)[i - 1] = (*stack_b)[i];
		(*stack_b)[stock_len - 1] = tmp;
	}
	else
	{
		rr(stack_a, stack_b, 0, len_a, len_b);
		rr(stack_a, stack_b, 1, len_a, len_b);
	}
}
static void rrr(int **stack_a, int **stack_b, int flag, int len_a, int len_b)
{
	int tmp;
	int i;
	int stock_len;

	if (flag == 0)
	{
		stock_len = len_a;
		tmp = (*stack_a)[0];
		while(1 < len_a--)
			(*stack_a)[(len_a + 1) % stock_len] = (*stack_a)[len_a];
		(*stack_a)[++len_a] = tmp;
	}
	else if(flag == 1)
	{
		stock_len = len_b;
		tmp = (*stack_b)[0];
		while(1 < len_b--)
			(*stack_b)[(len_b + 1) % stock_len] = (*stack_b)[len_b];
		(*stack_b)[++len_b] = tmp;
	}
	else
	{
		rrr(stack_a, stack_b, 0, len_a, len_b);
		rrr(stack_a, stack_b, 1, len_a, len_b);
	}
}

static void pa(int **stack_a, int **stack_b, int *len_a, int *len_b)
{
	int i;
	int stock_len_a;
	int stock_len_b;

	stock_len_a = *len_a;
	stock_len_b = *len_b;
	i = 0;
	while(1 < stock_len_a--)
		(*stack_a)[stock_len_a + 1] = (*stack_a)[stock_len_a];
	(*stack_a)[0] = (*stack_b)[0];
	while((1 < stock_len_b--) && ++i)
		(*stack_b)[i - 1] = (*stack_b)[i];
	(*len_a)++;
	(*len_b)--;
}

static void pb(int **stack_a, int **stack_b, int *len_a, int *len_b)
{
	int i;
	int stock_len_a;
	int stock_len_b;

	stock_len_a = *len_a;
	stock_len_b = *len_b;
	i = 0;
	while(1 < stock_len_b--)
		(*stack_b)[stock_len_b + 1] = (*stack_b)[stock_len_b];
	//ここでstock_len_bが0だった場合、-1にアクセスしてしまうのでstcok_len_bをindexで使わないほうがいい
	(*stack_b)[0] = (*stack_a)[0]; 
	while((1 < stock_len_a--) && ++i)
		(*stack_a)[i - 1] = (*stack_a)[i];
	(*len_a)--;
	(*len_b)++;
}

#include <stdlib.h>

int main(void)
{
    // テスト用のスタックを初期化
    int stack_a[] = {1, 2, 3, 4, 5};
	int len_a = sizeof(stack_a) / sizeof(stack_a[0]);

	int *stack_b = malloc(len_a * sizeof(int));//len_a分メモリ取得、超えることはない
	int len_b = 0;

    int *ptr_stack_a = stack_a;
    int *ptr_stack_b = stack_b;
    

    // ss関数のテスト
    printf("Before ss(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    ss(&ptr_stack_a, &ptr_stack_b, 0, len_a, len_b);

    printf("After ss(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    // rr関数のテスト
    printf("Before rr(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    rr(&ptr_stack_a, &ptr_stack_b, 0, len_a, len_b);

    printf("After rr(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    // rrr関数のテスト
    printf("Before rrr(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    rrr(&ptr_stack_a, &ptr_stack_b, 0, len_a, len_b);

    printf("After rrr(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

	// pb関数のテスト
    printf("Before pb(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");

    pb(&ptr_stack_a, &ptr_stack_b, &len_a, &len_b);

    printf("After pb(stack_a): ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", stack_a[i]);
    printf("\n");
    printf("After pb(stack_a): ");
    for (int i = 0; i < len_b; i++)
        printf("%d ", stack_b[i]);
    printf("\n");


    return 0;
}

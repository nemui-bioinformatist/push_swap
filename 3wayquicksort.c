/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3wayquicksort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:11:51 by rnomura           #+#    #+#             */
/*   Updated: 2024/07/07 19:12:20 by rnomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// この関数は配列を3つの部分に分割します
// a) a[l..i] にはピボットより小さいすべての要素が含まれる
// b) a[i+1..j-1] にはピボットと同じ値が含まれる
// c) a[j..r] にはピボットより大きいすべての要素が含まれる
void partition(int a[], int l, int r, int* i, int* j) {
    *i = l - 1;
    *j = r;
    int p = l - 1, q = r;
    int v = a[r];

    while (1) {
        // 左から、ピボット以上の最初の要素を見つける
        // このループは必ず終了する（vは最後の要素）
        while (a[++(*i)] < v);

        // 右から、ピボット以下の最初の要素を見つける
        while (v < a[--(*j)]) {
            if (*j == l) break;
        }

        // iとjが交差したら終了
        if (*i >= *j) break;

        // 小さい要素を左に、大きい要素を右にスワップ
        int temp = a[*i];
        a[*i] = a[*j];
        a[*j] = temp;

        // ピボットと同じ左の要素を配列の先頭に移動し、pをカウントに使用
        if (a[*i] == v) {
            p++;
            temp = a[p];
            a[p] = a[*i];
            a[*i] = temp;
        }

        // ピボットと同じ右の要素を配列の末尾に移動し、qをカウントに使用
        if (a[*j] == v) {
            q--;
            temp = a[q];
            a[q] = a[*j];
            a[*j] = temp;
        }
    }

    // ピボット要素を正しい位置に移動
    int temp = a[*i];
    a[*i] = a[r];
    a[r] = temp;

    // 左の同じ要素を先頭からarr[i]の隣に移動
    *j = *i - 1;
    for (int k = l; k < p; k++, (*j)--) {
        temp = a[k];
        a[k] = a[*j];
        a[*j] = temp;
    }

    // 右の同じ要素を末尾からarr[i]の隣に移動
    *i = *i + 1;
    for (int k = r - 1; k > q; k--, (*i)++) {
        temp = a[*i];
        a[*i] = a[k];
        a[k] = temp;
    }
}

// 3-way partitionに基づくクイックソート
void quicksort(int a[], int l, int r) {
    if (r <= l) return;

    int i, j;

    // iとjは参照として渡されることに注意
    partition(a, l, r, &i, &j);

    // 再帰呼び出し
    quicksort(a, l, j);
    quicksort(a, i, r);
}

// 配列を表示するユーティリティ関数
void printarr(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d  ", a[i]);
    }
    printf("\n");
}

// ドライバコード
int main() {
    int a[] = { 4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4 };
    int size = sizeof(a) / sizeof(int);

    // 関数呼び出し
    printarr(a, size);
    quicksort(a, 0, size - 1);
    printarr(a, size);
    return 0;
}


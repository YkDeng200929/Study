#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int data;
    struct node *next;
};
// 初始化
void init(struct node *phead)
{
    phead->data = 1;
    phead->next = phead;
}

// 插入元素
bool insert_val_tail(struct node *phead, int val)
{
    struct node *pnew = NULL;
    struct node *find;
    pnew = (struct node *)malloc(sizeof(struct node));
    if (!pnew)
        return false;
    pnew->data = val;
    pnew->next = pnew;
    // 当除头元素外没有元素
    if (phead->next == phead)
    {
        pnew->next = phead;
        phead->next = pnew;
        return true;
    }
    // 当存在多个元素
    for (find = phead; find->next != phead; find = find->next)
    {}
    if (find->next == phead)
    {
        pnew->next = phead;
        find->next = pnew;
        return true;
    }
    return false;
}

// 头插
bool insert_val_head(struct node *phead, int val)
{
    struct node *pnew = (struct node *)malloc(sizeof(struct node));
    if (!pnew) return false;
    pnew->data = val;
    pnew->next = phead->next;
    phead->next = pnew;    
}

// 打印
void print(struct node *phead)
{
    struct node *print;
    for (print = phead; print->next != phead; print = print->next)
    {
        printf("%d ", print->data);
    }
    printf("%d ", print->data);
    putchar('\n');
}

// 出队 (ok
struct node * out(struct node *phead, int k, int m, int n)
{
    struct node *find_k, *prev, *del;
    int count = 1, len = 1;
    for (find_k = phead; find_k->data != k; find_k = find_k->next)
    {}
    // 基于 find_k 来出队
    prev = find_k, del = prev->next;
    while (len <= n)
    {
        //prev = find_k, del = prev->next;
        for (count = 1; count < m-1; prev = prev->next, del = prev->next, count++)
        {}
        /*
        if (del == find_k)
        {
            prev = prev->next;
            del = prev->next;
            prev->next = del->next;
            printf("%d", del->data);
            prev = del->next;
            free(del);
            continue;
        }
        */
        prev->next = del->next;
        printf("%d", del->data);
        prev = del->next;
        free(del);
        len++;
    }
    putchar('\n');
    printf("find_k:%d, phead: %d\n", find_k->data, phead->data);
    printf("p_k: %d, p_k_next: %d\n", find_k, find_k->next);
    
    return find_k;
}    


// 插入目标元素 
void josepher(struct node *phead)
{
    int arr[] = {1,2,3,4,5,6,7,8};
    for (int i = sizeof(arr)/sizeof(arr[0])-1; i > 0; i--)
    {
        //printf("test\n");
        insert_val_head(phead, arr[i]);
    }
}

int main()
{
    struct node *head = (struct node *)malloc(sizeof(struct node));
    init(head);
    printf("init ok\n");
    josepher(head);
    printf("insert ok1\n");
    print(head);
    // k = 3, m = 4;
    printf("OK\n");
    head = out(head, 3, 4, 8);
    printf("outok\n");
    //print(head);

    return 0;
}
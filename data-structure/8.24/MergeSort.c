#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef struct LNode {
    int data;
    struct LNode* next;
} LNode, *LinkList;

// ========== 工具函数（一级指针） ==========

LinkList findMiddle(LinkList head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    LinkList slow = head;
    LinkList fast = head->next;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

LinkList mergeTwoLists(LinkList l1, LinkList l2) {
    LNode dummy;
    LinkList tail = &dummy;
    dummy.next = NULL;
    
    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = (l1 != NULL) ? l1 : l2;
    return dummy.next;
}

// ========== 递归排序（一级指针） ==========

LinkList mergeSort(LinkList head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    LinkList mid = findMiddle(head);
    LinkList rightHead = mid->next;
    mid->next = NULL;
    
    LinkList leftSorted = mergeSort(head);
    LinkList rightSorted = mergeSort(rightHead);
    
    return mergeTwoLists(leftSorted, rightSorted);
}

// ========== 对外接口（二级指针） ==========

int MergeSortList_L(LinkList* L) {
    if (*L == NULL || (*L)->next == NULL || (*L)->next->next == NULL) {
        return ERROR;
    }
    
    LinkList head = (*L)->next;
    head = mergeSort(head);
    (*L)->next = head;
    
    return OK;
}

int main()
{
    LinkList L;
}
/*************************************************************************
> File Name: test.cpp
> Author:Sanjingye 
> Mail: 
> Created Time: 2017年12月11日 星期一 22时14分50秒
************************************************************************/

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *p1 = l1, *p2 = l2, *p, *h, *node;
        h = NULL;
        int n = 0;
        while(p1 != NULL && p2 != NULL)
        {
            node = new ListNode(n);
            n = node->val + p1->val + p2->val;
            node->val = n % 10;
            n /= 10;
            if(h == NULL)
                h = p = node;
            else
            {
		        p->next = node;
		       	p = node;
		    }
            p1 = p1->next;
            p2 = p2->next;
        }
        while(p1 != NULL)
        {
            node = new ListNode(n);
            n = node->val + p1->val;
            node->val = n % 10;
            n /= 10;
            p->next = node;
            p = node;
            p1 = p1->next;
        }
        while(p2 != NULL)
        {
            node = new ListNode(n);
            n = node->val + p2->val;
            node->val = n % 10;
            n /= 10;
            p->next = node;
            p = node;
            p2 = p2->next;
        }
        if(n > 0)
        {
        	node = new ListNode(n);
        	p->next = node;
        }
        return h;
	}
};
/*
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p1 = l1, *p2 = l2, *p, *h;
        int n = 0;
        p = h = new ListNode(0);
        while(p1 != NULL && p2 != NULL)
        {
            n = p->val + p1->val + p2->val ;
            p->val = n % 10;
            n /= 10;
            p->next = new ListNode(n);
            p = p->next;
            p1 = p1->next;
            p2 = p2->next;
        }
        while(p1 != NULL)
        {
            n = p->val + p1->val;
            p->val = n % 10;
            n /= 10;
            p->next = new ListNode(n);
            p1 = p1->next;
        }
        while(p2 != NULL)
        {
            n = p->val + p2->val;
            p->val = n % 10;
            n /= 10;
            p->next = new ListNode(n);
            p2 = p2->next;
        }
        return h;
	}
};
*/
int main()
{
    
}

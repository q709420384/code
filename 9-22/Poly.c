#include<stdio.h>
#include<stdlib.h>

typedef struct Poly
{
    float coef;
    int expn;
    struct Poly* next;
}Poly;
Poly* createpoly(void);
void printpoly(Poly* head);
Poly* addpoly(Poly* head1,Poly* head2);
Poly* subpoly(Poly* head1,Poly* head2);
Poly* derpoly(Poly* head);
int main()
{
    int chose;
    Poly* head=NULL;
    printf("Please input polynomial of one indeterminate pa<like 1,1 and 0is over>:\n");
    Poly* head1=createpoly();
    printf("Please input polynomial of one indeterminate pb<like 1,1 and 0is over>:\n");
    Poly* head2=createpoly();
    printf("----------------pa---------------\n");
    printpoly(head1);
    printf("----------------pb---------------\n");
    printpoly(head2);

    while(1)
    {
        printf("\t\t1  pa + pb\n");
        printf("\t\t2  pa - pb\n");
        printf("\t\t3  pa求导\n");
        printf("\t\t4  exit\n");

        scanf("%d",&chose);

        if(chose==1)
        {
           head=addpoly(head1,head2);
           printpoly(head);
        }
        else if(chose == 2)
        {
           head=subpoly(head1,head2);
           printpoly(head);
        }    
        else if(chose == 3)
        {
            head=derpoly(head1);
            printpoly(head);
        }
        else if(chose == 4)
        exit(0);
    }

}
Poly* createpoly(void)
{
    float c;
    int e;
    Poly* head,*rear,*s;
    head=(Poly*)malloc(sizeof(Poly));
    rear=head;
    rear->next=NULL;
    scanf("%f,%d",&c,&e);
    while(c!=0)
    {
        s=(Poly*)malloc(sizeof(Poly));
        s->coef=c;
        s->expn=e;
        s->next=rear->next;
        rear->next=s;
        rear=rear->next;
        scanf("%f,%d",&c,&e);
    }
    return head;
}
void printpoly(Poly* head)
{
    Poly* q=head->next;
    int flag=1;
    if(!q)
    {
        puts("0");
        return;
    }
    while(q)
    {
        if(q->coef>0&&flag!=1)
        putchar('+');
        if(q->coef!=1&&q->coef!=-1)
        {
            printf("%g",q->coef);
            if(q->expn==1)
            putchar('X');
            else if(q->expn)
            printf("X^%d",q->expn);
        }
        else
        {
            if(q->coef==1)
            {
                if(!q->expn)
                putchar('1');
                else if(q->expn==1)
                putchar('X');
                else
                printf("X^%d",q->expn);
            }
            else //系数为1 
            {
                if(!q->expn)
                printf("-1");
                else if(q->expn==1)
                printf("-X");
                else
                printf("-X^%d",q->expn);
            }
        }
        q=q->next;
        flag++;
    }
    printf("\n");
}
Poly* addpoly(Poly* head1,Poly* head2)
{
    Poly* qa=head1->next;
    Poly* qb=head2->next;
    Poly* head3,*pc,*qc;
    pc=(Poly*)malloc(sizeof(Poly));
    pc->next=NULL;
    head3=pc;
    while(qa!=NULL&&qb!=NULL)
    {
        qc=(Poly*)malloc(sizeof(Poly));
        if(qa->expn<qb->expn)
        {
            qc->coef=qa->coef;
            qc->expn=qa->expn;
            qa=qa->next;
        }
        else if(qa->expn==qb->expn)
        {
            qc->coef=qa->coef+qb->coef;
            qc->expn=qa->expn;
            qa=qa->next;
            qb=qb->next;
        }
        else
        {
            qc->coef=qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        if(qc->coef!=0)
        {
            qc->next=pc->next;
            pc->next=qc;
            pc=qc;
        }
        else
        free(qc);
    }
    while(qa!=NULL)
    {
        qc=(Poly*)malloc(sizeof(Poly));
        qc->coef=qa->coef;
        qc->expn=qa->expn;
        qa=qa->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
    while(qb!=NULL)
    {
        qc=(Poly*)malloc(sizeof(Poly));
        qc->coef=qb->coef;
        qc->expn=qb->expn;
        qb=qb->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
	return head3;
}
Poly* subpoly(Poly* head1,Poly* head2)
{
    Poly* h=head2;
    Poly* p=head2->next;
    Poly* pd;
    while(p)
    {
        p->coef*=-1;
        p=p->next;
    }
    pd=addpoly(head1,h);
    for(p=h->next;p;p=p->next)
        p->coef*=-1;
    return pd;
}
Poly* derpoly(Poly* head)
{
    Poly* p=head->next;
    Poly* tmp=head;
    Poly* head3,*rear,*pnew;
    head3=(Poly*)malloc(sizeof(Poly));
    head3->next=NULL;
    rear=head3;
    while(p)
    {
        if(p->expn!=0)
        {
        	pnew=(Poly*)malloc(sizeof(Poly));
            pnew->next=rear->next;
            rear->next=pnew;
            pnew->coef=p->coef * p->expn;
            pnew->expn=p->expn-1;
            rear=rear->next;
        }
        p=p->next;
    }
    return head3;

}

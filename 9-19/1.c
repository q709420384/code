void Recvser1(Elemtype *seq,int len)
{
	int i,t=len/2;
	Elemtype tem;
	for(i=0;i<t;i++)
	{
		tem=seq[i];
		seq[i]=seq[len-i-1];
		seq[len-i-1]=tem;
	}
}
void Reverser2(list H)
{
	node *p,*q;
	p=H->next;
	H->next=NULL;
	while(p)
	{
		q=p;
		p=p->next;
		q->next=H->next;
		H->next=q;
	}
}

void fun(node* la,node* lb,int i,int j,int len)
{
	if(la==NULL||lb==NULL)
	{
		return;
	}
	node* p=la;
	node* q,*tmp,*low;
	int k,t=1;
	while(t<i)
	{
		low=p;
		p=p->next;
		t++;
	}
	tmp=p;
	for(k=0,t=0;t<len;t++)
	{
		p=p->next;
		t++;
	}
	low->next=p->next;
	t=1;
	q=lb;
	while(t<j)
	{
		q=q->next;
		t++;
	}
	p->next=q->next;
	q->next=tmp;
}

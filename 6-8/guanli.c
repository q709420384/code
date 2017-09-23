//作者:闪电黑客
//完成时间:2017.1.4
//耗时3天（累死我了）
//作品:学生成绩管理系统
//用到了链表与文件操作

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

#define pr printf
#define qp system("cls");

#define hh "\n\n\n"


#define m1 "\t┏━━━━━━━━━━━━━━━━━━━━━━━┓\n"
#define m2 "\t┃               学生成绩管理系统               ┃\n"
#define m3 "\t┣━━━━━━━━━━━━━━━━━━━━━━━┫\n"
#define m4 "\t┃                                              ┃\n"
#define m5 "\t┃               1.学生成绩录入                 ┃\n"
#define m6 "\t┃                                              ┃\n"
#define m7 "\t┃               2.学生成绩排序与删除           ┃\n"
#define m8 "\t┃                                              ┃\n"
#define m9 "\t┃               3.成绩统计打印                 ┃\n"
#define ma "\t┃                                              ┃\n"
#define mb "\t┃               0.退出系统                     ┃\n"
#define mc "\t┃                                              ┃\n"
#define md "\t┗━━━━━━━━━━━━━━━━━━━━━━━┛\n"
#define jm pr(hh m1 m2 m3 m4 m5 m6 m7 m8 m9 ma mb mc md);

#define l1 "\t┃             按1可继续录入下一个学生          ┃\n"
#define l2 "\t┃                                              ┃\n"
#define l3 "\t┃             按0可返回界面                    ┃\n"
#define l4 "\t┃                                              ┃\n"
#define l5 "\t┗━━━━━━━━━━━━━━━━━━━━━━━┛\n"
#define l6 "\t  请输入要录入的学生信息:\n\n"
#define lm pr(hh m1 m2 m3 m4 l1 l2 l3 l4 l5 l6);

#define x1 "\t┃     1.顺序学号 2.逆序学号 3.语文最高分       ┃\n"
#define x2 "\t┃                                              ┃\n"
#define x3 "\t┃    4.数学最高分 5.英语最高分 6.总分最高分    ┃\n"
#define x4 "\t┃                                              ┃\n"
#define x5 "\t┃                7.平均最高分                  ┃\n"
#define x6 "\t┃                                              ┃\n"
#define x7 "\t┃              按8可删除学生信息               ┃\n"
#define x8 "\t┃                                              ┃\n"
#define x9 "\t┃              按0可返回界面                   ┃\n"
#define xa "\t┃                                              ┃\n"
#define xb "\t┗━━━━━━━━━━━━━━━━━━━━━━━┛\n"

#define xc "┏━━━┳━━━┳━━━━━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓\n"
#define xd "┃序号\t┃学号\t┃姓  名\t┃语文\t┃ 数学\t┃ 英语\t┃ 总分\t┃平均分┃\n"
#define xm pr(hh m1 m2 m3 m4 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd);

#define pxm pr(hh m1 m2 m3 m4 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb);

#define xt2 "\t┃               学生成绩统计表                 ┃\n"


#define xf "┣━━━╋━━━╋━━━━━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫\n"
#define xsx "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n",n,xs[i].xh,xs[i].name,xs[i].yw,xs[i].sx,xs[i].yy,xs[i].zfs,xs[i].pj

#define xt "┗━━━┻━━━┻━━━━━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛\n"

#define z1 "\t┃      按1将表格按照目前排序打印到.txt文件     ┃\n"
#define z2 "\t┃                                              ┃\n"
#define z3 "\t┃              按0可返回界面                   ┃\n"
#define z4 "\t┣━━━━┳━━━━━━━━━━━━━━━━━━┫\n"
#define z5 "\t┃语文总分┃%d\n"
#define z6 "\t┣━━━━╋━━━━━━━━━━━━━━━━━━┫\n"
#define z7 "\t┃数学总分┃%d\n"
#define z8 "\t┣━━━━╋━━━━━━━━━━━━━━━━━━┫\n"
#define z9 "\t┃英语总分┃%d\n"
#define za "\t┣━━━━╋━━━━━━━━━━━━━━━━━━┫\n"
#define zb "\t┃ 全总分 ┃%d\n"
#define zc "\t┣━━━━┻┳━━━━━━━━━━━━━━━━━┫\n"
#define zd "\t┃语文平均分┃%0.2f\n"
#define ze "\t┣━━━━━╋━━━━━━━━━━━━━━━━━┫\n"
#define zf "\t┃数学平均分┃%0.2f\n"
#define zg "\t┣━━━━━╋━━━━━━━━━━━━━━━━━┫\n"
#define zh "\t┃英语平均分┃%0.2f\n"
#define zi "\t┣━━━━━╋━━━━━━━━━━━━━━━━━┫\n"
#define zj "\t┃ 总平均分 ┃%0.2f\n"
#define zk "\t┗━━━━━┻━━━━━━━━━━━━━━━━━┛\n",zyw,zsx,zyy,zfs,pyw,psx,pyy,pfs
#define zm pr(hh m1 m2 m3 m4 z1 z2 z3 z4 z5 z6 z7 z8 z9 za zb zc zd ze zf zg zh zi zj zk);

#define zm1 pr(hh m1 m2 m3 m4 z1 z2 z3 xb);


#define k1 "\t╔════════════════════════╗\n"
#define k2 "\t╚════════════════════════╝\n"


#define t1 "\t║警告:录入的成绩中不能有大于100的数,信息录入失败!║\n"
#define t2 "\t║警告:已有相同学号的学生,信息录入失败!           ║\n"
#define t3 "\t║提醒:输入1继续录入,输入0结束录入!               ║\n"
#define t4 "\t║提示:按1开始录入学生信息!                       ║\n"
#define t5 "\t║提示:成绩录入结束!按任意键返回目录!             ║\n"
#define t6 "\t║提示:成功打开文件录入该学生信息!                ║\n"
#define t7 "\t║提醒:文件还未建立!                              ║\n"
#define t8 "\t║提示:已成功保存数据退出系统!!!                  ║\n"
#define t9 "\t║警告:学号不能是 0 或负数,也不能大于 5 位数!!!   ║\n"
#define ta "\t║提示:请输入要删除的学生学号!!!                  ║\n"
#define tb "\t║提示:成功删除该学号!!!                          ║\n"
#define tc "\t║提示:未搜索到该学号!!!                          ║\n"
#define td "\t║提醒:存档文件为空!!!                            ║\n"
#define te "\t║提醒:文件已存在,确定要覆盖吗?  1.覆盖 0.返回    ║\n"
#define tf "\t║提醒:文件已经生成!!!                            ║\n"
#define tg "\t║提醒:文件打开失败!!!                            ║\n"
#define th "\t║提醒:数据库中无学生信息!!!                      ║\n"
#define ti "\t║提示:请输入存档文件名称!!!                      ║\n"
#define tj1 "\t║提示:按1输入打印文件名字!!!                     ║\n"
#define tk "\t║警告:输入的名字只能为中文!!!                    ║\n"

#define ts1 pr(k1 t1 k2);
#define ts2 pr(k1 t2 k2);
#define ts3 pr(k1 t3 k2);
#define ts4 pr(k1 t4 k2);
#define ts5 pr(k1 t5 k2);
#define ts6 pr(k1 t6 k2);
#define ts7 pr(k1 t7 k2);
#define ts8 pr(hh k1 t8 k2 hh "\t");
#define ts9 pr(k1 t9 k2);
#define tsa pr(k1 ta k2);
#define tsb pr(k1 tb k2);
#define tsc pr(k1 tc k2);
#define tsd pr(k1 td k2);
#define tse pr(k1 te k2);
#define tsf pr(k1 tf k2);
#define tsg pr(k1 tg k2);
#define tsh pr(k1 th k2);
#define tsi pr(k1 ti k2);
#define tsj pr(k1 tj1 k2);
#define tsk pr(k1 tk k2);

#define jg sizeof(struct xuesheng)

struct xuesheng
{
	int xh;
	char name[6];
	int yw;
	int sx;
	int yy;
	int zfs;
	float pj;
	struct xuesheng *next;

}xs[2];

void luru();
int jcxh();

void ck();
 
struct xuesheng *dc();
struct xuesheng * shanchu(struct xuesheng *tou,int xh);
struct xuesheng *px(struct xuesheng *tou,char cz);
void dy(struct xuesheng *tou);
void cd(struct xuesheng *tou);

void tj();
void cdtxt(struct xuesheng *tou,char name[40]);

 main()
{
	char xx;

	for(;;)
	{
		do
		{
		qp
		jm
		xx=getch();
		}while(!(xx=='0'||xx=='1'||xx=='2'||xx=='3'||xx=='4'));
		
		qp
		
			if(xx=='0')break;
			if(xx=='1')luru();
			if(xx=='2')ck();
			if(xx=='3')tj();
	}
			ts8

		system("PAUSE");
}

void tj()
{
	FILE *p1;
	struct xuesheng *tou,*p0;

	int n=0,i=0;
	
	char ch=0,name[40]={0};
	char *txt=".txt";

	char cz=0;
	
	int zyw=0,zsx=0,zyy=0,zfs=0;
	float pyw=0,psx=0,pyy=0,pfs=0;

	tou=dc();

	if(tou)
	{

				p0=tou;

						do
						{
							n++;
							zyw+=p0->yw;
							zsx+=p0->sx;
							zyy+=p0->yy;
							
							pfs+=p0->pj;

							p0=p0->next;
						}while(p0);
					
					zfs=zyw+zsx+zyy;

					pyw=(float)zyw/n;
					psx=(float)zsx/n;
					pyy=(float)zyy/n;

					pfs/=n;

				zm
					
					while(cz!='1'&&cz!='0')cz=getch();

					if(cz=='1')
					{   
						qp
						zm1

						tsj

						cz=0;	
						
						while(cz!='1'&&cz!='0')cz=getch();

							if(cz=='1')
							{
								tsi

								pr("\t  文件名称:");

								scanf("%s",name);

								strcat(name,txt);
								printf("\n\t\t将生成文件:%s\n\n",name);

								if(!(p1=fopen(name,"r")))ch=1;
							

								if(!ch)
								{
									ch=0;
									tse 
									cz=getch();
									while(cz!='0'&&cz!='1')cz=getch();
									if(cz=='0')return;
									if(cz=='1')
									{
										if(!(p1=fopen(name,"w+"))){tsg return;}
										if(tou!=NULL)
										{
											p0=tou;
											rewind(p1);
											fprintf(p1,hh m1 xt2 z4 z5 z6 z7 z8 z9 za zb zc zd ze zf zg zh zi zj zk);
											fprintf(p1,xc xd);
											n=0;
												do
												{
													fprintf(p1,xf "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n",++n,p0->xh,p0->name,p0->yw,p0->sx,p0->yy,p0->zfs,p0->pj);
													p0=p0->next;

												}while(p0);
												fprintf(p1,xt);
										}
										fclose(p1);
									}
									tsf
									system("PAUSE");
								}
								else
								{	

									if(!(p1=fopen(name,"w+"))){tsg return;}
										if(tou!=NULL)
										{
											p0=tou;
											rewind(p1);
											fprintf(p1,hh m1 xt2 z4 z5 z6 z7 z8 z9 za zb zc zd ze zf zg zh zi zj zk );
											fprintf(p1,xc xd);
											n=0;
												do
												{
													fprintf(p1,xf "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n",++n,p0->xh,p0->name,p0->yw,p0->sx,p0->yy,p0->zfs,p0->pj);
													p0=p0->next;

												}while(p0);
												fprintf(p1,xt);
										}
										tsf
										fclose(p1);
										system("PAUSE");
									
								}
							}
					}
	}
			
}


void luru()
{
	FILE *p1;
	char xx;
	
	qp
	lm

    ts4
	while(xx!='1'&&xx!='0')xx=getch();

	if(xx=='1')
	{
	
		do
		{
				qp
				lm
				
				pr("\t\t学号: ");scanf("%d",&xs[0].xh);
				pr("\t\t姓名: ");scanf("%s",&xs[0].name);
				pr("\t\t语文: ");scanf("%d",&xs[0].yw);
				pr("\t\t数学: ");scanf("%d",&xs[0].sx);
				pr("\t\t英语: ");scanf("%d",&xs[0].yy);

				xs[0].pj =(float)((xs[0].yw +xs[0].sx +xs[0].yy)/3);
				xs[0].zfs =xs[0].yw +xs[0].sx +xs[0].yy;
	
			if(!jcxh())
			{
				if(!(p1=fopen("学生成绩档案","ab+"))){tsg return;}

				fwrite(&xs[0],sizeof(struct xuesheng),1,p1);

				ts6

				fclose(p1);
			}

			ts3
		
			xx=0;
			while(xx!='1'&&xx!='0')xx=getch();
		}while(xx!='0');
		
			ts5
			getch();
	}
}

int jcxh()
{
	FILE *p1;

	int n=0;

	if(!(p1=fopen("学生成绩档案","rb"))) {ts7 return 0;}

			do
			{
				++n;
				fread(&xs[1],sizeof(struct xuesheng),1,p1);
				if(xs[1].xh==xs[00].xh)
				{
					ts2

					pr(xc xd xf "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n" xt,n,xs[1].xh,xs[1].name,xs[1].yw,xs[1].sx,xs[1].yy,xs[1].zfs,xs[1].pj);
					fclose(p1);
					return 1;
				}
				
				if(xs[0].yw>100||xs[0].sx>100||xs[0].yy>100)
				{
					ts1

					fclose(p1);
					return 1;
				}
					if(xs[0].xh<=0||xs[0].xh>99999)
				{
					ts9

					fclose(p1);
					return 1;
				}
						if(xs[0].name[0]>0)
				{
					tsk
					fclose(p1);
					return 1;
				}

			}while(!feof(p1));
		fclose(p1);

		return 0;
}




void ck()
{
	struct xuesheng *tou;

	char cz;
	int xh;
	
	pxm

	tou=dc();
	
	do
	{
		cz=0;
		while(cz!='0'&&cz!='1'&&cz!='2'&&cz!='3'&&cz!='4'&&cz!='5'&&cz!='6'&&cz!='7'&&cz!='8')cz=getch();
		qp

		if(cz=='8')
		{
			pxm
			tsa
			pr("\t");
			scanf("%d",&xh);
			tou=shanchu(tou,xh);
		}
		tou=px(tou,cz);

		if(cz!='0')dy(tou);
	
	}while(cz!='0');

	cd(tou);

}

struct xuesheng * shanchu(struct xuesheng *tou,int xh)
	{
		struct xuesheng *p1,*p2;//声明指针 p1,p2
		
		int n=0;

		if(!tou)//假如链表头为0的话，则无结构可删
		{
			tsh
			goto end;//直接跳到最后，退出函数
		}

		p1=tou;//把头结构给p1
		while(p1->xh !=xh&&p1->next !=NULL)//假如当前结构里的号码不等于所要删除的号码，和当前结构不是链表尾的话，则继续循环
		{
			++n;
			p2=p1;//把当前结构给p2，让p2紧跟p1后面
			p1=p1->next ;//p1则指向下一个结构，循环扫描
		}
		if(xh==p1->xh )//判断号码是否相等
		{
			tsb
			pr(xc xd xf "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n" xt,n,p1->xh,p1->name,p1->yw,p1->sx,p1->yy,p1->zfs,p1->pj);

			if(p1==tou)			//假如相等,判断是否为链表头的结构体
				tou=p1->next;	//假如是链表头，那么把tou指向下一个结构，成为新链表头。把原链表头（p1）抛弃
			else
				p2->next =p1->next ;//假如不是链表头,那么上一个结构体则链接下一个结构体，把当前p1抛弃
		}
		else
			tsc

		end:
		getch();
		qp
		return tou;
	}

void cd(struct xuesheng *tou)
	{
		FILE *p1;
		struct xuesheng *p0;

		int n=0;

		p0=tou;
	
		if(!(p1=fopen("学生成绩档案","wb"))){tsg ;return;}
				
		if(tou)
		{
			rewind(p1);
			do
			{fwrite(p0,sizeof(struct xuesheng),1,p1);p0=p0->next;}
			while(p0);
		}

		fclose(p1);
	}



 void dy(struct xuesheng *tou)
	{
		struct xuesheng *p;

		int n1=0;

		p=tou;//把头结构给p

		if(tou)//检测是否为0，如果是的话则链表为空，不需要打印
		{
			xm
			do
			{
				pr(xf "┃%d\t┃%d\t┃%s  \t┃%d\t┃%d\t┃%d\t┃%d\t┃%0.2f\t┃\n",++n1,p->xh,p->name,p->yw,p->sx,p->yy,p->zfs,p->pj);//打印当前结构里的变量

				p=p->next;//(*p).next，这句的意思是当前结构地址，替换成next里面，下一个结构的地址。
				
			}while(p);//（地址为0时，也就是末尾时，退出循环不再打印）
			pr(xt);
		}
	}


struct xuesheng *px(struct xuesheng *tou,char cz)
	{
		struct xuesheng *p2,*p1,*p0,*p;

		int n=0;
		int x=0;

		if(tou)
		{
			p0=tou;//链表头给p0
			while(p0){p0=p0->next;++n;}
		
			while(n>0&&(cz!='0'&&cz!='8'))
				{
					p0=tou;//链表头给p0
					n--;

					while(p0->next )//当前结构是否为末尾。
						{
						
							p2=p1;//p2紧跟p1
							p1=p0;//p1紧跟p0
							p0=p0->next;//p0指向下一个结构
						
							if(cz=='1'&&p1->xh>p0->xh)x=1;
							if(cz=='2'&&p1->xh<p0->xh)x=1;
							if(cz=='3'&&p1->yw<p0->yw)x=1;
							if(cz=='4'&&p1->sx<p0->sx)x=1;
							if(cz=='5'&&p1->yy<p0->yy)x=1;
							if(cz=='6'&&p1->zfs<p0->zfs)x=1;
							if(cz=='7'&&p1->pj<p0->pj)x=1;
							
							if(x)
							{
								if(p1==tou)
								{
										   p=tou;
							   			 tou=p1->next;
									p1->next=p0->next;
									p0->next=p;
									x=0;
								}
								else
								{
										   p=p2->next;//实现交换两个结构的指针
									p2->next=p1->next;
									p1->next=p0->next;
									p0->next=p;
									x=0;
								}
							}
						}
				}
		}
		return tou;
	}


 struct xuesheng *dc()
 {
	FILE *p1;

	struct xuesheng *s0,*s1,*tou;//声明3个指针
	
	char ch=0;

	int i=0;

	tou=0;
	
	if(!(p1=fopen("学生成绩档案","rb"))) {ts7 return 0;}

	ch=fgetc(p1);
	
	if(ch==EOF)
	{pr(hh);tsd getch();return 0;}
	else
	{
		rewind(p1);

		s0=(struct xuesheng *)malloc(jg);
		fread(s0,sizeof(struct xuesheng),1,p1);
		tou=s0;	s1=s0;
				
		while(!feof(p1))
		{
			s1->next=s0;
			s1=s0;
			s0=(struct xuesheng *)malloc(jg);
			fread(s0,sizeof(struct xuesheng),1,p1);
		}
		s1->next=NULL;
	
		
	}
	fclose(p1);

	return tou;
 
 }

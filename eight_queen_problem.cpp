// twtww.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
int fangge[8][8]={0};
int jilu[8]={0};
int i;
typedef struct
{
	int x;
	int y;
}DataType;

struct SeqStack
{
	int MAXNUM;
	int t;
	DataType * s;
};
typedef struct SeqStack *PSeqStack;


/********************************************/
/*                ����ջ                    */
	PSeqStack createEmptyStack_seq(int m)
	{
		PSeqStack pastack;
		pastack=(PSeqStack)malloc(sizeof(struct SeqStack));
		if(pastack!=NULL)
		{
			pastack->s=(DataType *)malloc(sizeof(struct SeqStack)*m);
				if(pastack->s)
				{
					pastack->MAXNUM=m;
				    pastack->t=0;
					return pastack;
				}
		}
		else free(pastack);
	printf("Out of space!! \n");
	return NULL;		
}

/********************************************/
/*           �ж�ջ�Ƿ�Ϊ��ջ               */
/*int isEmptyStack_seq(PSeqStack pastack)
{
�����Ŀ���˴�����Ҫ�Կ�ջ�ж�
	return (pastack->t==0);
}*/


/********************************************/
/*                 ��ջ                     */
void push_seq(PSeqStack pastack,DataType o) //��ջ��ѹ��һԪ��
{
	if(pastack->t>=pastack->MAXNUM-1)
		printf("Overflow! \n");
	else
	{
		pastack->t=pastack->t+1;
		pastack->s[pastack->t]=o;
	}
}


/********************************************/
/*                 ��ջ                     */
void pop_seq(PSeqStack pastack)  //ɾ��ջ��Ԫ��
{
	if(pastack->t==0)
		printf("Underflow! \n");
	else
		pastack->t=pastack->t-1;
}


/********************************************/
/*              ȡջ��Ԫ��                  */
DataType top_seq(PSeqStack pastack)
{
	//�����Ŀ���˴�����Ҫ�Կ�ջ�ж�
		return (pastack->s[pastack->t]);
}


/********************************************/
/*      ��ʼ��������һ��ȫ����ջ            */
void chushi(PSeqStack st,DataType element)
{
   int j;
   for(j=0;j<8;j++)
	{
		element.x=0;
		element.y=j;
	    push_seq(st,element);
	}
}


/********************************************/
/*   ȡ��ջ��Ԫ��ʱ����Ӱ�쵽�ĵط���ֵ��1  */
void intbiaoji(DataType element)
{
	int z;
	jilu[i]=element.y;
	for(z=1;z<8;z++)
		if((z+i)<8)
		{
		    fangge[z+i][element.y]++;//������ֱ�·�Ԫ�ر��
		    if((element.y+z)<8)
			  fangge[z+i][element.y+z]++;//����б���·��·�Ԫ�ر��
		    if((element.y-z)>=0)
			  fangge[z+i][element.y-z]++;//����б���·��·�Ԫ�ر��
		}
}


/********************************************/
/*    ������ǰ��ջԪ��֮ǰ��ɵ�Ӱ��        */
void outbiaoji(int a)
{
	int z;
	for(z=1;z<8;z++)
		if((z+i)<8)
		{
		   fangge[z+i][a]--;//ȡ������ֱ�·�Ԫ�ر��
			if((a+z)<8)
			fangge[z+i][a+z]--;//ȡ����б���·�Ԫ�ر��
			if((a-z)>=0)
			fangge[z+i][a-z]--;//ȡ����б���·�Ԫ�ر��
		}
}


/********************************************/
/*       ִ�г�ջ��
         ��ǰ���޶�Ӧջ��Ԫ�أ�
         ִ������                          */
void tuihang(PSeqStack st,DataType element)
{
     element=top_seq(st);
	 outbiaoji(element.y);	
	 pop_seq(st);
	 element=top_seq(st);
	while(i!=element.x)
		if((i-element.x)==1)
		{
			i--;
			outbiaoji(element.y);
			pop_seq(st);
			if(st->t!=0)  //ջ��Ϊ��ջ
			element=top_seq(st);
			else
				exit(0);//һ��ջΪ��ջ��ֱ�ӽ�������
		}
	i=element.x;
}


/********************************************/
/*           ��һ���п���ջԪ�أ�
             ��������ִ��                   */
void next(PSeqStack st,DataType element)
{
	int j,biaoji=0;
   for(j=0;j<8;j++)
	  if(fangge[i+1][j]==0)
	  {
		biaoji++;
		element.x=i+1;
		element.y=j;
		push_seq(st,element);
	  }
			if(biaoji==0)
			tuihang(st,element); 
			else
			{
			  biaoji=0;
			  i++;
			}
}


/********************************************/
/*      ������п���ջԪ��
        �����¼�����е�����                */
void over(PSeqStack st,DataType element)
{
    int z;
	for(z=0;z<8;z++)
	printf("  %d  ",jilu[z]);
	printf("\n");
	/*int z,c;
	int shuchu[8][8]={0};
	for(z=0;z<8;z++)
		shuchu[z][jilu[z]]=1;
for(z=0;z<8;z++)
{
    for(c=0;c<8;c++)
	printf(" %d",shuchu[z][c]);
	printf("\n");
}
	printf("\n\n");*/
	element=top_seq(st);
	outbiaoji(element.y);
	pop_seq(st);
	element=top_seq(st);
		while(i!=element.x)
		   if((i-element.x)==1)
			{
				i--;
				outbiaoji(element.y);
				pop_seq(st);
                element=top_seq(st);
			}
	i=element.x;
}


int main(int argc, char* argv[])
{
	PSeqStack st;
    DataType element;
    element.x=0;
    element.y=0;
    st=createEmptyStack_seq(64);
    chushi(st,element);
    i=0;
while(1)
{
	element=top_seq(st);
    intbiaoji(element);
		if(i==7)
		over(st,element);	
		else
		next(st,element);
}
	return 0;
}


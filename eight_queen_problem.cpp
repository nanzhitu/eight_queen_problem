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
/*                创建栈                    */
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
/*           判断栈是否为空栈               */
/*int isEmptyStack_seq(PSeqStack pastack)
{
结合题目，此处不需要对空栈判断
	return (pastack->t==0);
}*/


/********************************************/
/*                 进栈                     */
void push_seq(PSeqStack pastack,DataType o) //在栈中压入一元素
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
/*                 出栈                     */
void pop_seq(PSeqStack pastack)  //删除栈顶元素
{
	if(pastack->t==0)
		printf("Underflow! \n");
	else
		pastack->t=pastack->t-1;
}


/********************************************/
/*              取栈顶元素                  */
DataType top_seq(PSeqStack pastack)
{
	//结合题目，此处不需要对空栈判断
		return (pastack->s[pastack->t]);
}


/********************************************/
/*      初始化：将第一行全部入栈            */
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
/*   取出栈顶元素时对其影响到的地方数值加1  */
void intbiaoji(DataType element)
{
	int z;
	jilu[i]=element.y;
	for(z=1;z<8;z++)
		if((z+i)<8)
		{
		    fangge[z+i][element.y]++;//对其竖直下方元素标记
		    if((element.y+z)<8)
			  fangge[z+i][element.y+z]++;//对其斜右下方下方元素标记
		    if((element.y-z)>=0)
			  fangge[z+i][element.y-z]++;//对其斜左下方下方元素标记
		}
}


/********************************************/
/*    消除当前出栈元素之前造成的影响        */
void outbiaoji(int a)
{
	int z;
	for(z=1;z<8;z++)
		if((z+i)<8)
		{
		   fangge[z+i][a]--;//取消其竖直下方元素标记
			if((a+z)<8)
			fangge[z+i][a+z]--;//取消其斜右下方元素标记
			if((a-z)>=0)
			fangge[z+i][a-z]--;//取消其斜左下方元素标记
		}
}


/********************************************/
/*       执行出栈后，
         当前行无对应栈中元素，
         执行退行                          */
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
			if(st->t!=0)  //栈不为空栈
			element=top_seq(st);
			else
				exit(0);//一旦栈为空栈，直接结束程序
		}
	i=element.x;
}


/********************************************/
/*           后一行有可入栈元素，
             程序往后执行                   */
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
/*      最后行有可入栈元素
        输出记录数组中的数据                */
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


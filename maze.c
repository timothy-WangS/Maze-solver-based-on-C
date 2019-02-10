#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MazeScale 10

typedef struct Position
{
    int x;
    int y;
}Position; 

/*����ջ���е�ͨ����Ԫ�� */
typedef struct SElement 
{
    Position p;/*��¼�ھ����е�λ��*/ 
    int di;/*��һ�β��λ�� */
}SElement; 

typedef struct Stack{
    SElement* bottom;
    SElement* top;
    int stacksize;
}Stack;

int InitStack(Stack* s)
{
    s->bottom=(SElement*)malloc(STACK_INIT_SIZE*sizeof(SElement)); 
    if(!s->bottom) 
	    return 0;
    s->top=s->bottom;
    s->stacksize=STACK_INIT_SIZE;
    return 1; 
}

/*�ж��Ƿ�Ϊ�գ���1��0*/
int IsStackEmpty(Stack* s)
{
    if(s->top==s->bottom) 
	    return 1;
    return 0;
} 

int Get(Stack* s,SElement* e)
{
    if(IsStackEmpty(s)) 
	    return 0;
    e=s->top-1;
    return 1; 
}

int StackLength(Stack* s)
{
    return (s->top)-(s->bottom);
}

int  Push(Stack* s,SElement e)
{
    if((s->top)-(s->bottom)>=STACK_INIT_SIZE)
    {
        s->bottom=(SElement*)realloc(s->bottom,(s->stacksize+STACKINCREMENT)*sizeof(SElement));
        if(!s->bottom) 
		    return 0;
        s->top=s->bottom+s->stacksize;
        s->stacksize+=STACKINCREMENT;
    }
    *(s->top)=e;
    s->top++;
    return 1;
}

int Pop(Stack* s,SElement* e)
{
    if(IsStackEmpty(s)) 
	    return 0;
    *e=*(s->top-1);
    s->top--;
    return 1;
} 

int Maze[MazeScale][MazeScale]={{1,1,1,1,1,1,1,1,1,1},
                                {1,2,1,0,0,0,0,0,0,1},
								{1,0,1,1,1,1,0,1,0,1},
								{1,0,0,0,0,0,0,1,0,1},
								{1,1,1,0,1,1,0,1,0,1},
								{1,0,1,1,0,1,0,1,0,1},
								{1,0,1,1,0,1,1,0,0,1},
								{1,0,0,0,0,1,1,1,1,1},
								{1,1,1,1,0,0,0,0,3,1},
								{1,1,1,1,1,1,1,1,1,1}};
								
int PrintMaze()
{
	int i,j;
    
	/*��ӡ�Թ�*/
    for(i=0;i<MazeScale;i++)
    {
        for(j=0;j<MazeScale;j++)
        {
            printf("%d ",Maze[i][j]);
        }
        printf("\n");
    }
}

int Pass(Position posi)
{
    /*0����*/
    if((Maze[posi.x][posi.y]==0)||(Maze[posi.x][posi.y]==2)||(Maze[posi.x][posi.y]==3))
    {
        return 1;
    } 
    return 0; 
}

Position NextPosition(Position now,int direction)
{
    Position next;
    int x=now.x;
    int y=now.y;
    switch(direction)
    {
        //�� 
        case 1:{
            next.x=x+1;
            next.y=y;
            break;
        }
        //����
		case 2:{
            next.x=x+1;
            next.y=y-1; 
            break;
        }
		//�� 
        case 3:{
            next.x=x;
            next.y=y-1; 
            break;
        }
        //����
        case 4:{
            next.x=x-1;
            next.y=y-1;
            break;
        }
        //��
		case 5:{
            next.x=x-1;
            next.y=y; 
            break;
        }
		//����
		case 6:{
            next.x=x-1;
            next.y=y+1; 
            break;
        } 
        //��
        case 7:
        {
            next.x=x;
            next.y=y+1;
            break;
        }
		//����
		case 8:{
            next.x=x+1;
            next.y=y+1; 
            break;
        } 
        default:break;
    }
    return next;
}

void FootPrint(Position p,int step)
{
    if(Maze[p.x][p.y]==2) 
			    return;
	Maze[p.x][p.y]=step;
}

void MarkPrint(Position p)
{
    Maze[p.x][p.y]=1;
}


int main()
{
	int step=8;
	int i,j;
		
	PrintMaze();
	
	Stack  path;/*��¼·��*/
    InitStack (&path);/*��ʼ��·��*/
    Position now;/*��ǰλ��*/
    
    now.x=1;
    now.y=1;
    
    do
    {
    	if(Pass(now))
        {
            if(Maze[now.x][now.y]==3) 
			    break;
			FootPrint(now,step);
            
            SElement e;
            
            e.di=1;
            e.p.x=now.x;
            e.p.y=now.y;
            
            Push(&path,e);
            
             
            now=NextPosition(now,1);
            
        }
    	else
    	{	
            SElement e;
            Pop(&path,&e);
            /*�������Թ���·����ջ����� */
            while(e.di==8 && !IsStackEmpty(&path))
		    {
                 MarkPrint(e.p); 
                 Pop(&path,&e);
            }
                
            if(e.di<8)
            {
                now=NextPosition(e.p,e.di+1);
                e.di++;
                Push(&path,e);
            }
            
    	}
    }while(!IsStackEmpty(&path));
    printf("\n");
    /*��ӡ���*/
    for(i=0;i<MazeScale;i++)
    {
        for(j=0;j<MazeScale;j++)
        {
            printf("%3d",Maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}

























#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;
#define MAX 1000
#define TQ 4
int flag[MAX],at[MAX],bt[MAX],pt[MAX],rt[MAX],ct[MAX],fe[MAX],fe_flag[MAX],pid[MAX],tms,qt[MAX];
//at arrival time
//bt burst time
//rt Response Time
//pt priority
//pid process id
//ct completion time
queue<int> q;  
void RR()
{
      if(!q.empty())
      {
      	if(rt[q.front()]>0 && qt[q.front()]<4)
      	{
          		qt[q.front()]++;
          		rt[q.front()]--;
          		if(rt[q.front()]==0)
          		{
            	ct[q.front()]=tms+1;
            	q.pop();
          		}
          		if(rt[q.front()]!=0 && qt[q.front()]==4)
          		{
				qt[q.front()]=0;
				q.push(q.front());
				q.pop();
          		}
        	}
      }
}
int main()
{
    int i=0,n=0,smallest=0,last_smallest=-1,min,sum=0,large=0,avgWT=0,avgTAT=0;
    printf("enter no of process\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
    		printf("enter pid of process %d ",i);
    		scanf("%d",&pid[i]);
			A: 
    		printf("enter arrival time :");
    		scanf("%d",&at[i]);
    		if(at[i]<0)
    		{ 
    		  printf("\ninvalid plz reenter\n");
    		  goto A;	
			}
			B:
    		printf("enter burst time :");
    		scanf("%d",&bt[i]);
    		if(bt[i]<1)
    		{
    		  printf("\ninvalid plz reenter\n");
    		  goto B;	
			}
    		C:
    		printf("enter priority no:");
			scanf("%d",&pt[i]);
			if(pt[i]<0)
    		{
    		  printf("\ninvalid plz reenter\n");
    		  goto C;	
			}
    		if(at[i]>large)
    		  	large=at[i];
    		  sum+=bt[i];
    		  rt[i]=bt[i];
    }
    min=MAX;
    for(tms=0;!q.empty() || tms<=sum+large ;tms++)
    {
      min=MAX;
      smallest=-1;
      for(i=0;i<n;i++)
      {
      	if(at[i]<=tms && pt[i]<min && rt[i]>0 && !flag[i])
      	{
      		min=pt[i];
          		smallest=i;
        	}
      }
      if(smallest==-1 && !q.empty())
      {
      	if(last_smallest !=-1 && rt[last_smallest]==0)
      	{
      		ct[last_smallest]=tms;
          		flag[last_smallest]=1;
        	}
        	last_smallest=-1;
        	RR();
        	continue;
      }
      else if(smallest!=-1 && !q.empty() && last_smallest==-1)
      {
      	if(qt[q.front()]<=4 && qt[q.front()]>0)
      	{
      		q.push(q.front());
      		q.pop();
        	}
      }
      if(smallest!=-1 && !fe_flag[smallest])
      {
      	fe[smallest]=tms-at[smallest];
      	fe_flag[smallest]=1;
      }
      if( smallest!=last_smallest && last_smallest!=-1 && !flag[last_smallest])
      {
      	q.push(last_smallest);
      	flag[last_smallest]=1;
      }
      if(smallest !=-1)
      	rt[smallest]--;
      
      if((smallest !=-1) && ((rt[smallest]==0) ||(bt[smallest]-rt[smallest])==TQ))
      {
      	if((bt[smallest]-rt[smallest])==TQ && rt[smallest]!=0)
      	{
      		flag[smallest]=1;
      		q.push(smallest);
        	}
       	else if(smallest!=-1)
       	{
          		ct[smallest]=tms+1;
          		flag[smallest]=1;
        }
      }
      last_smallest=smallest;
    }
    cout<<"\n=====================================================================\n";
    cout<<"PID\tAT\tBT\tCT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
    cout<<pid[i]<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<ct[i]-bt[i]-at[i]<<"\t"<<ct[i]-at[i]<<endl;
    for(int i=0;i<n;i++){
    	avgWT=avgWT+ct[i]-bt[i]-at[i];
    	avgTAT=avgTAT+ct[i]-at[i];
	}
	cout<<"\nAverage Waiting time : "<<avgWT/n;
	cout<<"\nAverage TurnAround time : "<<avgTAT/n;
	return 0;
}

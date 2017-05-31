//////////////////////////////////////////////////////////////////////////////////////
////                           炸飞机小游戏 0.0.3                                   ////
////                           杨海涛 2011.11.10                                   ////
////                                                                              ////
//////////////////////////////////////////////////////////////////////////////////////

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define maxcapacity 900

int wide=10,high=10,capacity=100;
char a[maxcapacity],b[maxcapacity],c[maxcapacity],d[maxcapacity],youfirst='n';
int nhave[maxcapacity],yhave[10],range_head[16];
int ap[11],yp[11];
int at=0,yt=0,j=0,k=0,kill,close=0;
char *w="GO ON!!";
char x,y,other;
///////////////////////////////////////////////////////display//////////////////////////////
void display(char *ai,char *you,int aitime,int youtime,char *word)
	{
	int i,j;
	int maxwide,maxhigh;
	maxwide=4*wide+2+11;
	maxhigh=high;
	////////////////////////////////////////////////////////////////////////////////////
	for(i=0;i<maxwide;i++)printf("*");printf("\n");                                           //1
	printf("*");for(i=0;i<(maxwide-2);i++)printf(" ");printf("*\n");                          //2
	printf("*   AI:");for(i=0;i<(2*wide+1);i++)printf(" ");                                   //3
	printf("YOU:");for(i=0;i<(2*wide);i++)printf(" ");printf("*\n");
	printf("*");for(i=0;i<(maxwide-2);i++)printf(" ");printf("*\n");                          //4
	printf("*   \\ ");for(i=0;i<wide;i++)printf("%c ",'a'+i);
	printf("  \\ ");for(i=0;i<wide;i++)printf("%c ",'a'+i);printf("  *\n");                   //5
	for(i=0;i<maxhigh;i++)                                                                    //6~16
		{
		printf("*   %c ",'a'+i);
		for(j=0;j<wide;j++)printf("%c ",ai[i*wide+j]);
		printf("  %c ",'a'+i);
		for(j=0;j<wide;j++)printf("%c ",you[i*wide+j]);
		printf("  *\n");
		}
	printf("*");for(i=0;i<(maxwide-2);i++)printf(" ");printf("*\n");                          //17
	printf("*   TIME:%3d",aitime);for(i=0;i<(2*wide-4);i++)printf(" ");                       //18
	printf("TIME:%3d",youtime);for(i=0;i<(2*wide-4);i++)printf(" ");printf("*\n");
	printf("*");printf("   %-28s",word);for(i=0;i<(maxwide-33);i++)printf(" ");printf("*\n"); //19
	for(i=0;i<maxwide;i++)printf("*");printf("\n");                                           //20
	}
////////////////////////////////////////////////////seed,myrand////////////////////////////
void seed()
	{
	time_t t;
	srand((unsigned)time(&t));
	}

int my_rand(int range)
	{
	int ans=0;
	ans=rand()%range;
	return ans;
	}
////////////////////////////////////////////////////is_have////////////////////////////////
int is_have(int *a,int i,int j)
	{
	int k,m=0;
	for(k=0;k<=j;k++)
		{
		if(a[k]!=i)m++;
		}
	if((m-1)==j)return 0;
	else return 1;
	}

void range_head_init(int *a)
	{
	a[0]=0;a[1]=1;a[2]=wide-2;a[3]=wide-1;
	a[4]=wide;a[5]=wide+1;a[6]=2*wide-2;a[7]=2*wide-1;
	a[8]=(high-2)*wide;a[9]=(high-2)*wide+1;a[10]=(high-1)*wide-2;a[11]=(high-1)*wide-1;
	a[12]=(high-1)*wide;a[13]=(high-1)*wide+1;a[14]=high*wide-2;a[15]=high*wide-1;
	}
//////////////////////////////////////////////////ai_plane/////////////////////////////////
void ai_plane(char *ai,int *aiplane)
	{
	int ready=0;
	int headx,heady,bottomx,bottomy,body0x,body0y,body3x,body3y,i;
	while(ready!=1)
		{
		aiplane[10]=my_rand(capacity);  //0~(capacity-1)
		if(is_have(range_head,aiplane[10],16)==1)continue;
		else
			{
			heady=(int)(aiplane[10]/wide);
			headx=(int)(aiplane[10]%wide);
			}
		aiplane[9]=my_rand(4);
		switch(aiplane[9])
			{
			case 0:aiplane[9]=aiplane[10]-4*wide;break;
			case 1:aiplane[9]=aiplane[10]+4*wide;break;
			case 2:aiplane[9]=aiplane[10]-4;break;
			case 3:aiplane[9]=aiplane[10]+4;break;
			}
		if((aiplane[9]>=0)&&(aiplane[9]<=(capacity-1)))
			{
			bottomy=(int)(aiplane[9]/wide);
			bottomx=(int)(aiplane[9]%wide);
			}
		else continue;
		if(headx==bottomx)
			{
			if(heady<bottomy)
				{
				aiplane[0]=aiplane[10]+wide-2;
				aiplane[1]=aiplane[10]+wide-1;
				aiplane[2]=aiplane[10]+wide+1;
				aiplane[3]=aiplane[10]+wide+2;
				aiplane[4]=aiplane[10]+wide;
				aiplane[5]=aiplane[10]+2*wide;
				aiplane[6]=aiplane[10]+3*wide;
				aiplane[7]=aiplane[9]-1;
				aiplane[8]=aiplane[9]+1;
				}
			else
				{
				aiplane[0]=aiplane[10]-wide+2;
				aiplane[1]=aiplane[10]-wide+1;
				aiplane[2]=aiplane[10]-wide-1;
				aiplane[3]=aiplane[10]-wide-2;
				aiplane[4]=aiplane[10]-wide;
				aiplane[5]=aiplane[10]-2*wide;
				aiplane[6]=aiplane[10]-3*wide;
				aiplane[7]=aiplane[9]+1;
				aiplane[8]=aiplane[9]-1;
				}
			}
		else if(heady==bottomy)
			{
			if(headx>bottomx)
				{
				aiplane[0]=aiplane[10]-1-2*wide;
				aiplane[1]=aiplane[10]-1-wide;
				aiplane[2]=aiplane[10]-1+wide;
				aiplane[3]=aiplane[10]-1+2*wide;
				aiplane[4]=aiplane[10]-1;
				aiplane[5]=aiplane[10]-2;
				aiplane[6]=aiplane[10]-3;
				aiplane[7]=aiplane[9]-wide;
				aiplane[8]=aiplane[9]+wide;
				}
			else
				{
				aiplane[0]=aiplane[10]+1+2*wide;
				aiplane[1]=aiplane[10]+1+wide;
				aiplane[2]=aiplane[10]+1-wide;
				aiplane[3]=aiplane[10]+1-2*wide;
				aiplane[4]=aiplane[10]+1;
				aiplane[5]=aiplane[10]+2;
				aiplane[6]=aiplane[10]+3;
				aiplane[7]=aiplane[9]+wide;
				aiplane[8]=aiplane[9]-wide;
				}
			}
		else continue;
		body0x=(int)(aiplane[0]%wide);
		body0y=(int)(aiplane[0]/wide);
		body3x=(int)(aiplane[3]%wide);
		body3y=(int)(aiplane[3]/wide);
		if((aiplane[0]<0)||(aiplane[0]>(capacity-1)))continue;
		else if((aiplane[1]<0)||(aiplane[1]>(capacity-1)))continue;
		else if((aiplane[2]<0)||(aiplane[2]>(capacity-1)))continue;
		else if((aiplane[3]<0)||(aiplane[3]>(capacity-1)))continue;
		else if((aiplane[4]<0)||(aiplane[4]>(capacity-1)))continue;
		else if((aiplane[5]<0)||(aiplane[5]>(capacity-1)))continue;
		else if((aiplane[6]<0)||(aiplane[6]>(capacity-1)))continue;
		else if((aiplane[7]<0)||(aiplane[7]>(capacity-1)))continue;
		else if((aiplane[8]<0)||(aiplane[8]>(capacity-1)))continue;
		else if((body0x!=body3x)&&(body0y!=body3y))continue;
		else
			{
			for(i=0;i<11;i++)ai[aiplane[i]]='O';
			ready=1;
			}	
		}
	}
///////////////////////////////////////////////////you_plane///////////////////////////////
	
void you_plane(char *youplane,int *you,char *w)
	{
	int ready=0;
	char direction;
	int youhx,youhy,youbx,youby,body0x,body0y,body3x,body3y,i;
	char x,y;
	extern char c[maxcapacity];
	extern int at,yt;
	w="Place your plane.";
	display(b,c,at,yt,w);
	printf("input your X,Y,direction(w,a,s,d),mode(y,n,o,z):\n");
	printf("	y:YOU first.\n");
	printf("	n:AI first.\n");
	printf("	o:Only you play.\n");
	printf("	z:Only AI play.\n");
	while(ready!=1)
		{
		printf("Input:");
		scanf("%c,%c,%c,%c",&x,&y,&direction,&youfirst);
		other=getchar();
		if((x>('a'+wide))||(x<'a')){printf("X is bigger than wide!\n");continue;}
		if((y>('a'+high))||(y<'a')){printf("Y is bigger than high!\n");continue;}
		ready=1;
		}
	ready=0;
	while(ready!=1)
		{
		you[10]=(x-'a')+(y-'a')*wide;
		if(direction=='w')
			{
			you[9]=you[10]+4*wide;
			you[0]=you[10]+wide-2;
			you[1]=you[10]+wide-1;
			you[2]=you[10]+wide+1;
			you[3]=you[10]+wide+2;
			you[4]=you[10]+wide;
			you[5]=you[10]+2*wide;
			you[6]=you[10]+3*wide;
			you[7]=you[9]-1;
			you[8]=you[9]+1;
			}
		else if(direction=='s')
			{
			you[9]=you[10]-4*wide;
			you[0]=you[10]-wide+2;
			you[1]=you[10]-wide+1;
			you[2]=you[10]-wide-1;
			you[3]=you[10]-wide-2;
			you[4]=you[10]-wide;
			you[5]=you[10]-2*wide;
			you[6]=you[10]-3*wide;
			you[7]=you[9]+1;
			you[8]=you[9]-1;
			}
		else if(direction=='a')
			{
			you[9]=you[10]+4;
			you[0]=you[10]+1+2*wide;
			you[1]=you[10]+1+wide;
			you[2]=you[10]+1-wide;
			you[3]=you[10]+1-2*wide;
			you[4]=you[10]+1;
			you[5]=you[10]+2;
			you[6]=you[10]+3;
			you[7]=you[9]+wide;
			you[8]=you[9]-wide;
			}
		else if(direction=='d')
			{
			you[9]=you[10]-4;
			you[0]=you[10]-1-2*wide;
			you[1]=you[10]-1-wide;
			you[2]=you[10]-1+wide;
			you[3]=you[10]-1+2*wide;
			you[4]=you[10]-1;
			you[5]=you[10]-2;
			you[6]=you[10]-3;
			you[7]=you[9]-wide;
			you[8]=you[9]+wide;
			}
		else continue;
		body0x=(int)(you[0]%wide);
		body0y=(int)(you[0]/wide);
		body3x=(int)(you[3]%wide);
		body3y=(int)(you[3]/wide);
		youhx=(int)(you[10]%wide);
		youhy=(int)(you[10]/wide);
		youbx=(int)(you[9]%wide);
		youby=(int)(you[9]/wide);
		if((you[0]<0)||(you[0]>(capacity-1)))continue;
		else if((you[1]<0)||(you[1]>(capacity-1)))continue;
		else if((you[2]<0)||(you[2]>(capacity-1)))continue;
		else if((you[3]<0)||(you[3]>(capacity-1)))continue;
		else if((you[4]<0)||(you[4]>(capacity-1)))continue;
		else if((you[5]<0)||(you[5]>(capacity-1)))continue;
		else if((you[6]<0)||(you[6]>(capacity-1)))continue;
		else if((you[7]<0)||(you[7]>(capacity-1)))continue;
		else if((you[8]<0)||(you[8]>(capacity-1)))continue;
		else if((body0x!=body3x)&&(body0y!=body3y))continue;
		else if((youbx!=youhx)&&(youby!=youhy))continue;
		else
			{
			for(i=0;i<11;i++)
				youplane[you[i]]='O';
			ready=1;
			}
		w="Your plane is already!";
		display(b,c,at,yt,w);
		}
	}
/////////////////////////////////////////////////are_have//////////////////////////////////
int are_have(int *a,int *b)
	{
	int i,n=0,m=0;
	for(i=0;i<10;i++)
		if((b[i]!=maxcapacity))m++;
	for(i=0;i<10;i++)
		if((is_have(a,b[i],10)==1))n++;
	if(m==n)return 1;
	else return 0;
	}
///////////////////////////////////////////////ai_guess/////////////////////////////////////	
int ai_guess(int *nothave,int *have)
	{
	int ready=0;
	int headx,heady,bottomx,bottomy,body0x,body0y,body3x,body3y;
	int aiplane[11];
	while(ready!=1)
		{
		aiplane[10]=my_rand(capacity);  //0~(capacity-1)
		if((is_have(range_head,aiplane[10],16)==1)||(is_have(nothave,aiplane[10],capacity)==1)||(is_have(have,aiplane[10],10)==1))continue;
		else
			{
			heady=(int)(aiplane[10]/wide);
			headx=(int)(aiplane[10]%wide);
			}
		aiplane[9]=my_rand(4);
		switch(aiplane[9])
			{
			case 0:aiplane[9]=aiplane[10]-4*wide;break;
			case 1:aiplane[9]=aiplane[10]+4*wide;break;
			case 2:aiplane[9]=aiplane[10]-4;break;
			case 3:aiplane[9]=aiplane[10]+4;break;
			}
		if((aiplane[9]>=0)&&(aiplane[9]<=(capacity-1)))
			{
			bottomy=(int)(aiplane[9]/wide);
			bottomx=(int)(aiplane[9]%wide);
			}
		else continue;
		if(headx==bottomx)
			{
			if(heady<bottomy)
				{
				aiplane[0]=aiplane[10]+wide-2;
				aiplane[1]=aiplane[10]+wide-1;
				aiplane[2]=aiplane[10]+wide+1;
				aiplane[3]=aiplane[10]+wide+2;
				aiplane[4]=aiplane[10]+wide;
				aiplane[5]=aiplane[10]+2*wide;
				aiplane[6]=aiplane[10]+3*wide;
				aiplane[7]=aiplane[9]-1;
				aiplane[8]=aiplane[9]+1;
				}
			else
				{
				aiplane[0]=aiplane[10]-wide+2;
				aiplane[1]=aiplane[10]-wide+1;
				aiplane[2]=aiplane[10]-wide-1;
				aiplane[3]=aiplane[10]-wide-2;
				aiplane[4]=aiplane[10]-wide;
				aiplane[5]=aiplane[10]-2*wide;
				aiplane[6]=aiplane[10]-3*wide;
				aiplane[7]=aiplane[9]+1;
				aiplane[8]=aiplane[9]-1;
				}
			}
		else if(heady==bottomy)
			{
			if(headx>bottomx)
				{
				aiplane[0]=aiplane[10]-1-2*wide;
				aiplane[1]=aiplane[10]-1-wide;
				aiplane[2]=aiplane[10]-1+wide;
				aiplane[3]=aiplane[10]-1+2*wide;
				aiplane[4]=aiplane[10]-1;
				aiplane[5]=aiplane[10]-2;
				aiplane[6]=aiplane[10]-3;
				aiplane[7]=aiplane[9]-wide;
				aiplane[8]=aiplane[9]+wide;
				}
			else
				{
				aiplane[0]=aiplane[10]+1+2*wide;
				aiplane[1]=aiplane[10]+1+wide;
				aiplane[2]=aiplane[10]+1-wide;
				aiplane[3]=aiplane[10]+1-2*wide;
				aiplane[4]=aiplane[10]+1;
				aiplane[5]=aiplane[10]+2;
				aiplane[6]=aiplane[10]+3;
				aiplane[7]=aiplane[9]+wide;
				aiplane[8]=aiplane[9]-wide;
				}
			}
		else continue;
		body0x=(int)(aiplane[0]%wide);
		body0y=(int)(aiplane[0]/wide);
		body3x=(int)(aiplane[3]%wide);
		body3y=(int)(aiplane[3]/wide);
		if((aiplane[0]<0)||(aiplane[0]>(capacity-1))||(is_have(nothave,aiplane[0],capacity)==1))continue;
		else if((aiplane[1]<0)||(aiplane[1]>(capacity-1))||(is_have(nothave,aiplane[1],capacity)==1))continue;
		else if((aiplane[2]<0)||(aiplane[2]>(capacity-1))||(is_have(nothave,aiplane[2],capacity)==1))continue;
		else if((aiplane[3]<0)||(aiplane[3]>(capacity-1))||(is_have(nothave,aiplane[3],capacity)==1))continue;
		else if((aiplane[4]<0)||(aiplane[4]>(capacity-1))||(is_have(nothave,aiplane[4],capacity)==1))continue;
		else if((aiplane[5]<0)||(aiplane[5]>(capacity-1))||(is_have(nothave,aiplane[5],capacity)==1))continue;
		else if((aiplane[6]<0)||(aiplane[6]>(capacity-1))||(is_have(nothave,aiplane[6],capacity)==1))continue;
		else if((aiplane[7]<0)||(aiplane[7]>(capacity-1))||(is_have(nothave,aiplane[7],capacity)==1))continue;
		else if((aiplane[8]<0)||(aiplane[8]>(capacity-1))||(is_have(nothave,aiplane[8],capacity)==1))continue;
		else if((aiplane[9]<0)||(aiplane[9]>(capacity-1))||(is_have(nothave,aiplane[9],capacity)==1))continue;
		else if((body0x!=body3x)&&(body0y!=body3y))continue;
		else if(are_have(aiplane,have)!=1)continue;
		else
			{
			ready=1;
			}	
		}
	return aiplane[10];
	}
////////////////////////////////////////////////complex////////////////////////////////////	
void complex(char *a,char *b,int n,char m)
	{
	int i;
	for(i=0;i<n;i++)
		{
		if((a[i]=='O')&&(b[i]=='.'))b[i]=m;
		}
	}
///////////////////////////////////////////////aiturn//////////////////////////////////////
void aiturn()
	{
	kill=ai_guess(nhave,yhave);
		if(kill==yp[10])
			{
			w="AI WIN!";
			at++;
			complex(a,b,capacity,'#');
			complex(c,d,capacity,'O');
			display(b,d,at,yt,w);
			close=1;
			}
		else if(yp[0]==kill){d[yp[0]]='O';yhave[j++]=kill;}
		else if(yp[1]==kill){d[yp[1]]='O';yhave[j++]=kill;}
		else if(yp[2]==kill){d[yp[2]]='O';yhave[j++]=kill;}
		else if(yp[3]==kill){d[yp[3]]='O';yhave[j++]=kill;}
		else if(yp[4]==kill){d[yp[4]]='O';yhave[j++]=kill;}
		else if(yp[5]==kill){d[yp[5]]='O';yhave[j++]=kill;}
		else if(yp[6]==kill){d[yp[6]]='O';yhave[j++]=kill;}
		else if(yp[7]==kill){d[yp[7]]='O';yhave[j++]=kill;}
		else if(yp[8]==kill){d[yp[8]]='O';yhave[j++]=kill;}
		else if(yp[9]==kill){d[yp[9]]='O';yhave[j++]=kill;}
		else {d[kill]='X';nhave[k++]=kill;}
		if(close!=1)
			{
			at++;
			display(b,d,at,yt,w);
			}
	}
//////////////////////////////////////////////////youturn//////////////////////////////////	
void youturn()
	{
	int flag=0;
	while(flag!=1)
		{
		printf("input your X,Y:");
		scanf("%c,%c",&x,&y);
		other=getchar();
		if(x>('a'+wide)||x<'a'){printf("X is bigger than wide!\n");continue;}
		if(y>('a'+high)||y<'a'){printf("Y is bigger than high!\n");continue;}
		flag=1;
		}
		kill=(x-'a')+(y-'a')*wide;
		if(kill==ap[10])
			{
			w="YOU WIN!";
			yt++;
			complex(c,d,capacity,'#');
			complex(a,b,capacity,'O');
			display(b,d,at,yt,w);
			close=1;
			}
		else if(ap[0]==kill)b[ap[0]]='O';
		else if(ap[1]==kill)b[ap[1]]='O';
		else if(ap[2]==kill)b[ap[2]]='O';
		else if(ap[3]==kill)b[ap[3]]='O';
		else if(ap[4]==kill)b[ap[4]]='O';
		else if(ap[5]==kill)b[ap[5]]='O';
		else if(ap[6]==kill)b[ap[6]]='O';
		else if(ap[7]==kill)b[ap[7]]='O';
		else if(ap[8]==kill)b[ap[8]]='O';
		else if(ap[9]==kill)b[ap[9]]='O';
		else b[kill]='X';
		if(close!=1)
			{
			yt++;
			display(b,d,at,yt,w);
			}
	}
void game_init()
	{
	w="Please input wide and high.";
	display(a,c,at,yt,w);
	printf("Input(wide,high)(26>=wide=high>=5):");
	scanf("%d,%d",&wide,&high);
	other=getchar();
	capacity=wide*high;
	w="GO ON! COME ON!!!";
	}	
///////////////////////////////////////////////main////////////////////////////////////////	
int main(void)
	{
	int i;
	for(i=0;i<maxcapacity;i++){a[i]='.';b[i]='.';c[i]='.';d[i]='.';nhave[i]=maxcapacity;}
	for(i=0;i<10;i++){yhave[i]=maxcapacity;}
	game_init();
	range_head_init(range_head);
	seed();
	ai_plane(a,ap);
	you_plane(c,yp,w);
	display(b,d,at,yt,w);
	while(1)
		{
		if(youfirst=='y')
			{
			youturn();
			if(close==1)break;
			aiturn();
			if(close==1)break;
			}
		else if(youfirst=='n')
			{
			aiturn();
			if(close==1)break;
			youturn();
			if(close==1)break;
			}
		else if(youfirst=='o')
			{
			youturn();
			if(close==1)break;
			}
		else
			{
			aiturn();
			if(close==1)break;
			}
		}
	return 0;
	}
////////////////////////////////////////////////////////////////////////////////////////////

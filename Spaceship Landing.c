#include "windows.h" 
#include "toolbox.h"
#include <analysis.h>
#include <ansi_c.h> 
#include <cvirte.h>		
#include <userint.h>
#include "bass.h"
#include "Spaceship Landing.h"
#include "TalGameLibrary.h"

static int panelHandle,panelHandle2,panelHandle3;
//music elements
HSTREAM Music_SND,Thrust_SND,Explosion_SND,Powerup_SND,Fuelling_SND;
int diff=1;
int width,height;
//ship images
int ship,shipmid,shipleft,shipright;
//ship movment
double shipvx,shipvy,dt=0.5,ay,ax,shipx=400,shipy=100, rotator_angle=3600.0,g;
 // ship image movment 
int left,right,mid;
//background	
double bgy=0.0;
//pixels cord
double px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6; 
//explosion
int explosion=0, explosion_img, explosionx=0, explosiony=0;
//maps
int map_counter=1,spacebg,map1mid,map1left,map1right,mapdown1,mapdown2,mapdown3,leftcave,middlecave,rightcave,
	goingup1,goingup2,goingup3;
int fuel=1000;
int lives=3;
int lvl=1;
int time_count=0;
int Score=0;
int bonus=0;
//score related 
int rowscounter=0;
char name[300];
char filename[300];
char line[300];
char line0[300]; 
typedef struct //score Table
{
int scoretot,level;
char name[30] ;
}scoret;
scoret score[11],score0;
FILE *fp;
char user_name[30];

//asteroids 
int asteroid,asteroid1,asteroid2,num_asteroid,asteroidvx,asteroidvy,asteroidx,asteroidy,asteroidx1,asteroidx2,asteroidy1,asteroidy2,
	asteroidvx1,asteroidvy1,asteroidvx2,asteroidvy2;
int leftarrow,rightarrow,downarrow,uparrow,rightarrowx=0,rightarrowy=0,leftarrowy=0,leftarrowx=0,downarrowx=0,downarrowy=0,uparrowx=0,uparrowy=0;
double asteroid_angle=0.0;

 void InitMP3s(void)								  
{
	BASS_Init( -1,44100, 0,0,NULL); 
	Music_SND = BASS_StreamCreateFile(FALSE,"Sounds\\BGsound.mp3",0,0,0);
	Thrust_SND= BASS_StreamCreateFile(FALSE,"Sounds\\thrust1.mp3",0,0,0);
	Explosion_SND= BASS_StreamCreateFile(FALSE,"Sounds\\explosion.mp3",0,0,0); 
	Powerup_SND=BASS_StreamCreateFile(FALSE,"Sounds\\Power_up.mp3",0,0,0);
	Fuelling_SND = BASS_StreamCreateFile(FALSE,"Sounds\\fuelling.mp3",0,0,0);
	BASS_ChannelSetAttribute(Thrust_SND, BASS_ATTRIB_VOL, 0.2);
	BASS_ChannelSetAttribute(Explosion_SND, BASS_ATTRIB_VOL, 0.25);
	BASS_ChannelSetAttribute(Powerup_SND, BASS_ATTRIB_VOL, 0.25);
	BASS_ChannelSetAttribute(Fuelling_SND, BASS_ATTRIB_VOL, 0.25);
}

void ReleaseMP3s(void)
{
	 
	 BASS_StreamFree(Music_SND);
	 BASS_StreamFree(Thrust_SND);
	 BASS_StreamFree(Explosion_SND); 
	 BASS_StreamFree(Powerup_SND);
	 BASS_StreamFree(Fuelling_SND);
}

 //variables for keyboard monitoring
int Callback_Data;	
int Posting_Handle; 
int Keys_Down[256]={0};
 double Pi (void);
 void draw ();
void background (); 
//Receives information from windows regarding key presses
int CVICALLBACK Key_DownFunc(int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData)
{
	unsigned int Key = *wParam;
	Keys_Down[Key] = 1;
	return 0;
}

//Receives information from windows regarding key releases
int CVICALLBACK Key_UpFunc(int panel, int message, unsigned int* wParam, unsigned int* lParam, void* callbackData)
{
	unsigned int Key = *wParam;
	Keys_Down[Key] = 0;
	return 0;
}

//asking windows to send keyboard press and release events to our software 
//Specifing 'Key_DownFunc' and 'Key_UpFunc' as the functions to call
void Connect_To_Windows_Events(void)
{
	InstallWinMsgCallback(panelHandle,WM_KEYDOWN,Key_DownFunc,VAL_MODE_IN_QUEUE,&Callback_Data,&Posting_Handle);
	InstallWinMsgCallback(panelHandle,WM_KEYUP,Key_UpFunc,VAL_MODE_IN_QUEUE,&Callback_Data,&Posting_Handle);
}

void initialize ()
{
	InitMP3s();
	BASS_ChannelPlay(Music_SND,TRUE);
	
//image loading 
		TL_QuickRotateLoad("Images\\SpaceShipV4none.png", &ship);
		TL_QuickRotateLoad("Images\\SpaceShipV4middle.png", &shipmid);
		TL_QuickRotateLoad("Images\\SpaceShipV4left.png", &shipleft);
		TL_QuickRotateLoad("Images\\SpaceShipV4right.png", &shipright);
		
		TL_QuickRotateLoad("Images\\Asteroid.png",&asteroid);    
 		GetBitmapFromFile ("Images\\BackgroundV2.png", &spacebg);
		 //map 1
		GetBitmapFromFile ("Images\\lvl1\\LandMiddle.png", &map1mid);
		GetBitmapFromFile ("Images\\lvl1\\LandLeft.png", &map1left);
		GetBitmapFromFile ("Images\\lvl1\\LandRight.png", &map1right);
		  //map2
		GetBitmapFromFile ("Images\\lvl2\\goingDown1.png", &mapdown1);
		GetBitmapFromFile ("Images\\lvl2\\goingDown2.png", &mapdown2);
		GetBitmapFromFile ("Images\\lvl2\\goingDown3.png", &mapdown3);
		 //map3
		  GetBitmapFromFile ("Images\\lvl3\\leftCave.png", &leftcave);
		  GetBitmapFromFile ("Images\\lvl3\\middleCave.png", &middlecave); 
		  GetBitmapFromFile ("Images\\lvl3\\rightCave.png", &rightcave); 
		   //map4
		   GetBitmapFromFile ("Images\\lvl4\\GoingUp1.png",&goingup1);
		   GetBitmapFromFile ("Images\\lvl4\\GoingUp2.png",&goingup2);
		   GetBitmapFromFile ("Images\\lvl4\\GoingUp3.png",&goingup3);
		   
		GetBitmapFromFile ("Images\\Explosion.png", &explosion_img);
		GetBitmapFromFile ("Images\\LeftArrow.png", &leftarrow);
		GetBitmapFromFile ("Images\\RightArrow.png",&rightarrow);
		GetBitmapFromFile ("Images\\DownArrow.png",&downarrow);
		GetBitmapFromFile ("Images\\UpArrow.png",&uparrow);
  		Connect_To_Windows_Events();
			 fp = fopen ("data_Table.txt", "r");
	 while (fgets(line0, 300, fp)!=0 && rowscounter<=10)
	 {
	   sscanf(line0,"%[^,],%d,%d\n",score[rowscounter].name,&score[rowscounter].scoretot,&score[rowscounter].level);

	 rowscounter++;
	 }

	for(int k=1,i=1; k<=10,i<=10; k++,i++)
	{
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (1, k), score[i-1].name);
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (2, k), score[i-1].scoretot);
	    SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (3, k), score[i-1].level);

	} 
	  
	fclose (fp);


}

void terminate()
{
	ReleaseMP3s(); 
TL_QuickRotateDiscard(ship); 
TL_QuickRotateDiscard(shipmid);
TL_QuickRotateDiscard(shipleft);
TL_QuickRotateDiscard(shipright);
TL_QuickRotateDiscard(asteroid); 
  DiscardBitmap(map1mid);
   DiscardBitmap(spacebg);
	DiscardBitmap(map1left);
	DiscardBitmap(map1right);
	
	 DiscardBitmap(mapdown1);
	 DiscardBitmap(mapdown2);  
	 DiscardBitmap(mapdown3);  
	 
	 DiscardBitmap(leftcave);
	 DiscardBitmap(middlecave);
	 DiscardBitmap(rightcave);
	 
	 DiscardBitmap(goingup1);
	  DiscardBitmap(goingup2);
	   DiscardBitmap(goingup3);
	 
	DiscardBitmap(explosion_img);
	DiscardBitmap(leftarrow);
	DiscardBitmap(rightarrow);
	DiscardPanel (panelHandle2);
	DiscardPanel (panelHandle3);
}

void scorefunc()
{
Score=lives*1000+bonus*500-time_count;
SetCtrlVal (panelHandle, PANEL_NSCORE, Score);
}

void explosionfunc ()
{
	shipvx=0;
	shipvy=0;
 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, explosion_img, MakeRect(64* explosiony,64* explosionx,64,64), MakeRect(shipy-50,shipx-50,100,100));
	 if( explosionx==4)
   {    explosiony++;
	    explosionx=0;
   }
   explosionx++;
   
   if(explosiony==5)
   {	mid=0;
   		right=0;
		left=0;
	   SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	   SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 0);
	 
   }
   BASS_ChannelPlay(Explosion_SND,TRUE); 
}

void rightarrowfunc ()
{
CanvasDrawBitmap (panelHandle, PANEL_CANVAS, rightarrow, MakeRect(20*rightarrowy,25*rightarrowx,20,25),MakeRect(85,1050,40,40) );
   if( rightarrowx==4)
   {    rightarrowy++;
	    rightarrowx=0;
   }
   rightarrowx++;
   if(rightarrowy==3)
   {
	   rightarrowx=0;
	   rightarrowy=0;
   }
}

void leftarrowfunc ()
{
 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, leftarrow, MakeRect(20*leftarrowy,25*leftarrowx,20,25),MakeRect(85,10,40,40) );
 if( leftarrowx==4)
   {    leftarrowy++;
	    leftarrowx=0;
   }
   leftarrowx++;
   if(leftarrowy==3)
   {
	   leftarrowx=0;
	   leftarrowy=0;
   }
}
void downarrowfunc ()
{

 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, downarrow, MakeRect(25*downarrowx,20*downarrowy,25,20),MakeRect(700,50,40,40) );
 if( downarrowx==4)
   {    downarrowy++;
	    downarrowx=0;
   }
   downarrowx++;
   if(downarrowy==3)
   {
	   downarrowx=0;
	   downarrowy=0;
   }	
}

void uparrowfunc ()
{

 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, uparrow, MakeRect(25*uparrowx,20*uparrowy,25,20),MakeRect(40,1050,40,40) );
 if( uparrowx==4)
   {    uparrowy++;
	    uparrowx=0;
   }
   uparrowx++;
   if(uparrowy==3)
   {
	  uparrowx=0;
	   uparrowy=0;
   }	
}


void resetfunc ()
{
explosion=0;
shipvy=0;
shipvx=0;
rotator_angle=3600.0;
Keys_Down[38] = 0;
Keys_Down[37] = 0; 
Keys_Down[39] = 0; 													
fuel=1000;
if(lives>0)
{
	if(map_counter>=0 && map_counter <=2)
	{
		shipy=100;
		shipx=400;
		map_counter=1;
	}
	if(map_counter>=4 && map_counter <=6)
	{
		shipy=170;
		shipx=170;
		map_counter=4;
	}
	if(map_counter>=9 && map_counter <=11)
	{
		shipy=200;
		shipx=50;
		map_counter=9;
	}
	if(map_counter>=13 && map_counter <=15)
	{
		shipy=650;
		shipx=750;
		map_counter=15;
	}
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1); 
	SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 1);
}
else
{  
	scorefunc ();
	MessagePopup ("Notice", "GAME OVER");
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 0);
	bonus=0;
	Score=0;
}
 
}

void initialize_astorids ()
{
			GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, &height);
			GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, &width);
			asteroidvx=3;
			asteroidvy=2;
			asteroidvx1=-3;
			asteroidvy1=2;
			asteroidvx2=2;
			asteroidvy2=-3;
				asteroidx=((double)rand()/RAND_MAX)*width;
				asteroidy=((double)rand()/RAND_MAX)*height;
				asteroidx1=((double)rand()/RAND_MAX)*width;
				asteroidy1=((double)rand()/RAND_MAX)*height;	
				asteroidx2=((double)rand()/RAND_MAX)*width;
				asteroidy2=((double)rand()/RAND_MAX)*height;	
}

void asteroidfunc ()
{   asteroid_angle+=3; 
	switch (num_asteroid)
	{
		case 1:
			asteroidx=asteroidx+asteroidvx*dt;
			asteroidy=asteroidy+asteroidvy*dt;
			
					if((asteroidx>=width) || (asteroidx<=0))
			{
				asteroidvx=asteroidvx*(-1);
			}
			if((asteroidy>=height) || (asteroidy<=0))
			{
				asteroidvy=asteroidvy*(-1);
			}
			   // to make it dissapier here   
			   if(sqrt((asteroidx-shipx)*(asteroidx-shipx)+(asteroidy-shipy)*(asteroidy-shipy))<=25)   
			   {    bonus++;
				asteroidx=10000;
				asteroidy=10000;
				BASS_ChannelPlay(Powerup_SND,TRUE); 
			   }
			break;
		case 2:
			//asteroids movement
			   asteroidx1=asteroidx1+asteroidvx1*dt;
			asteroidy1=asteroidy1+asteroidvy1*dt;
					if((asteroidx1>=width) || (asteroidx1<=0))
			{
				asteroidvx1=asteroidvx1*(-1);
			}
			if((asteroidy1>=height) || (asteroidy1<=0))
			{
				asteroidvy1=asteroidvy1*(-1);
			}
			
			asteroidx2=asteroidx2+asteroidvx2*dt;
			asteroidy2=asteroidy2+asteroidvy2*dt;
					if((asteroidx2>=width) || (asteroidx2<=0))
			{
				asteroidvx2=asteroidvx2*(-1);
			}
			if((asteroidy2>=height) || (asteroidy2<=0))
			{
				asteroidvy2=asteroidvy2*(-1);
			}
			 //asteroid got cought
			  if(sqrt((asteroidx1-shipx)*(asteroidx1-shipx)+(asteroidy1-shipy)*(asteroidy1-shipy))<=25)   
			   {  
				asteroidx1=10000;
				asteroidy1=10000;
				BASS_ChannelPlay(Powerup_SND,TRUE);
				bonus++;
			   }
			   
			   if(sqrt((asteroidx2-shipx)*(asteroidx2-shipx)+(asteroidy2-shipy)*(asteroidy2-shipy))<=25)   
			   {  
				asteroidx2=10000;
				asteroidy2=10000;
				BASS_ChannelPlay(Powerup_SND,TRUE);
				bonus++;
			   }
			
			
			break;
	}
}

void draw ()						 
{
	Rect rectangle; 
	Rect rectangle1;
	int temp_bitmap,temp_bitmap1,temp_bitmap2;
	 int temp_bitmap4,temp_bitmap5;
	 CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,MakeRect(bgy,0,1000,1100));
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,MakeRect(bgy+900,0,1000,1100));
		 background (); 
		 // switch case for map
	 switch (map_counter)
	 {
	 case 1:
		 num_asteroid=1;
			 temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, map1mid, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		  rightarrowfunc ();
		  leftarrowfunc () ;
		 break;
	//lvl1	 
	 case 0:
		 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, map1left, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		 rightarrowfunc ();
			
		 break;
		 
	 case 2:
		 	  num_asteroid=2; 
		 temp_bitmap5 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx2,asteroidy2, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap5, VAL_ENTIRE_OBJECT, rectangle1);
		 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, map1right, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		 temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx1,asteroidy1, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		  leftarrowfunc () ; 
		 break;
		 //lvl2
	 case 4:
		    CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mapdown1, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			downarrowfunc () ;
			num_asteroid=1;
			 temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		 break;
	 case 5:   
		 num_asteroid=1;  
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mapdown2, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		   temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		  downarrowfunc ();
		  uparrowfunc ();
		 break;
	 case 6:
		 num_asteroid=1;  
		  temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, mapdown3, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		  uparrowfunc ();
		 break;
		 //lvl3
	 case 9:
		 num_asteroid=1;  
		    CanvasDrawBitmap (panelHandle, PANEL_CANVAS, leftcave, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			 rightarrowfunc ();
			  temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		 break;
	 case 10:
		 num_asteroid=2;  
		  temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, middlecave, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		    temp_bitmap5 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx2,asteroidy2, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap5, VAL_ENTIRE_OBJECT, rectangle1);
		  leftarrowfunc () ;
		  rightarrowfunc ();
		 break;
	 case 11:
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, rightcave, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		  leftarrowfunc () ;
		 break;
		 //lvl4
	 case 15:
		 num_asteroid=1;  
		 CanvasDrawBitmap (panelHandle, PANEL_CANVAS, goingup3, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
		  temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		 break ;
	 case 14:
		 num_asteroid=1;  
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, goingup2, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT); 
		   temp_bitmap4 = TL_QuickRotate(asteroid,asteroid_angle,asteroidx,asteroidy, &rectangle1);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap4, VAL_ENTIRE_OBJECT, rectangle1);
		 break; 
	 case 13:
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS, goingup1, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT); 
		 break;
	 }
	 if (explosion==0)
	 {
	//Drawing the rotator:
	
	   if (mid==0 && left==0 && right==0)
	   {
	//get the rotated bitmap to draw (no need to free it afterwards) and generare the rectangle information
	//to be used in the next drawing operation
	//the rectnalge info is calculated using the provided x and y of the rotator
	temp_bitmap = TL_QuickRotate(ship,rotator_angle,shipx,shipy, &rectangle);
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	
	   }
	   
	    if (mid==1 && left==1 && right==0) 
		{
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap1 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);
		}
		
		 if (mid==1 && left==0 && right==1) 
		{
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap2 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
		}
		
		 if (mid==1 && left==0 && right==0) 
		{
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
		}
		
		 if (mid==1 && left==1 && right==1) 
		{
			temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
			temp_bitmap1 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);
			temp_bitmap2 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);  
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
		}
		
		if (mid==0 && left==1 && right==0) 
		{
			temp_bitmap1 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);

		}
		
		if (mid==0 && left==0 && right==1) 
		{
			temp_bitmap2 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
		}
		
	 }

		CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);  	
}

void calculation  ()
{ 
	double F=0.1,c,s,angle;
	double r1,s1,c1,angle1,temp1;
	double r2,s2,c2,angle2,temp2;
	double r3,s3,c3,angle3,temp3;
	double r4,s4,c4,angle4,temp4;
	double r5,s5,c5,angle5,temp5;
	double r6,s6,c6,angle6,temp6;
	//calculation of acceleration
	g=0.05  ;
	angle=rotator_angle*Pi()/180;
	c = cos (angle);
	s = sin (angle);
	  ax=F*s;
	  ay=F*c-g;
	//*******************************
	//calculation of pixel location 
	//right bottom
	temp1=atan (11.0/ 12.0);
	angle1=(rotator_angle)*Pi()/180+temp1;
	c1=cos(angle1);
	s1=sin(angle1);
	r1=sqrt(256);
	px1=shipx+r1*c1;
	py1=shipy+r1*s1;
	//left bottom
	temp2=atan (14.0/11.0);
	angle2=(rotator_angle)*Pi()/180+temp2;
	c2=cos(angle2);
	s2=sin(angle2);
	r2=sqrt(317);
	px2=shipx-r2*s2;
	py2=shipy+r2*c2;
	//middle bottom
	temp3=0.0;
	angle3=angle;
	c3=c;
	s3=s;
	r3=11.0;
	px3=shipx-r3*s3;
	py3=shipy+r3*c3;
	//middle right
	temp4=Pi()+atan(10.0/7.0);
	angle4=(rotator_angle)*Pi()/180+temp4; 
	c4=cos(angle4);
	s4=sin(angle4);
	r4=sqrt(149);
	px4=shipx-r4*s4;
	py4=shipy+r4*c4;
	//middle left
	temp5=Pi()+atan(12.0/7.0);
	angle5=(rotator_angle)*Pi()/180+temp5; 
	c5=cos(angle5);
	s5=sin(angle5);
	r5=sqrt(193);
	px5=shipx+r5*c5;
	py5=shipy+r5*s5;
	//top
	temp6=0.0;
	angle6=(rotator_angle)*Pi()/180+temp6; 
	c6=cos(angle6);
	s6=sin(angle6);
	r6=20.0;
	px6=shipx+r6*s6;
	py6=shipy-r6*c6;
}

void background ()
{
//stars background speed movment
bgy=bgy-0.45;
	if (bgy<=-900)
		bgy=0;
// switching between maps	
	 if(shipx <=0)
	 {
	  map_counter--;
	  shipx=1050;
	 }
	 if(shipx >=1100)
	 {
	 map_counter++;
	 shipx=50;
	 }
	 if(shipy <=0)
	 {
	  map_counter--;
	  shipy=780;
	 }
	 if(shipy >=800)
	 {
	 map_counter++;
	 shipy=50;
	 }
	
}

void surrounding ()
{
	int pixelcolor1,pixelcolor2,pixelcolor3,pixelcolor4,pixelcolor5,pixelcolor6; 
	int yellow=16515016,red=16614510,green=7910547,grey=11447981;
	 calculation  (); 
	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px1,py1), &pixelcolor1);//right bottom
	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px2,py2), &pixelcolor2);//left bottom
	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px3,py3), &pixelcolor3);//middle bottom
	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px4,py4), &pixelcolor4);//middle right
	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px5,py5), &pixelcolor5);//middle left
  	CanvasGetPixel (panelHandle, PANEL_CANVAS, MakePoint(px6,py6), &pixelcolor6);//top
 //conditions:				 
	
	//if touche mountains- explode
 if (pixelcolor1==yellow || pixelcolor2==yellow || pixelcolor3==yellow|| pixelcolor4==yellow|| pixelcolor5==yellow||pixelcolor6==yellow)
	   explosion=1; 
 //if touches landing zone  with the sides or top  and also the fuel zone-dead
 if( pixelcolor4== red || pixelcolor5== red || pixelcolor6== red ||pixelcolor4== green|| pixelcolor5== green || pixelcolor6== green  )
 								explosion=1;  
 //mixed -dead boom
	if( pixelcolor1== yellow && pixelcolor2== red && pixelcolor3== red )
	   					  		explosion=1; 
	if( pixelcolor1== red && pixelcolor2== yellow && pixelcolor3== red ) 
		   						explosion=1; 
	if( pixelcolor1== red && pixelcolor2== red && pixelcolor3== yellow )
						  		explosion=1; 
	if( pixelcolor1== red && pixelcolor2== yellow && pixelcolor3== yellow )
								explosion=1; 
	if( pixelcolor1== yellow && pixelcolor2== yellow && pixelcolor3== red ) 
								explosion=1; 
	if( pixelcolor1== yellow && pixelcolor2== red && pixelcolor3== yellow ) 
								explosion=1; 
//landing on with the bottom of ship (as supposed)-win
	if( pixelcolor1== red && pixelcolor2== red && pixelcolor3== red )
	{
		if (shipvy<=0.4 && shipvx<=0.4 &&shipvx>=-0.4)
		{
	 MessagePopup ("red", "landed");
	 lvl++;
	 SetCtrlVal (panelHandle, PANEL_NLVL, lvl);
	 initialize_astorids ();
	
	 	 map_counter=map_counter+4;
		  resetfunc ();
		  if (lvl==5)
		  {
			  strcpy (score[10].name,user_name);
    score[10].scoretot=Score;
	score[10].level=lvl;
	for(int j=0; j<=10; j++)
    for(int i=0;i<10;i++)
     if(score[i].scoretot<score[i+1].scoretot)
	 {
	 score0=score[i];
     score[i]=score[i+1];	 
     score[i+1]=score0;
	 }
    
	fp = fopen ("data_Table.txt", "w");

	for(int i=0; i<10; i++)
	fprintf (fp,"%s ,%d,%d  \n", score[i].name,score[i].scoretot,score[i].level);


	for(int k=1,i=1; k<=10,i<=10; k++,i++)
	{
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (1, k), score[i-1].name);
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (2, k), score[i-1].scoretot);
	    SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (3, k), score[i-1].level);

	} 
	  
	fclose (fp);
		  SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
		  SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 0);
		scorefunc();
		MessagePopup ("Congratulations!", "You have finished the game");
		  }
		}	
		 else
								explosion=1; 	 
	}
	//landing on with the bottom of ship to fuel
	if( pixelcolor1== green && pixelcolor2== green && pixelcolor3== green )
	{
		if (shipvy<=0.4 && shipvx<=0.4 &&shipvx>=-0.4)
		{
			shipvx=0;
	  		shipvy=0 ;
			BASS_ChannelPlay(Fuelling_SND,TRUE);
			if(fuel<=1000)
			fuel=fuel+10;
		}
		 else
								explosion=1; 	 
	}
	if (pixelcolor1==grey || pixelcolor2==grey || pixelcolor3==grey|| pixelcolor4==grey|| pixelcolor5==grey||pixelcolor6==grey)
	asteroidfunc (); 
	 
}

void data ()
{
SetCtrlVal (panelHandle, PANEL_HSPEED,100* shipvy);
if(shipvy<=0.4 && shipvy>=0.0)
{
SetCtrlAttribute (panelHandle, PANEL_HSPEED, ATTR_TEXT_BGCOLOR, VAL_DK_RED);
}
else 
{
	SetCtrlAttribute (panelHandle, PANEL_HSPEED, ATTR_TEXT_BGCOLOR, MakeColor(27,27,28));
}
SetCtrlVal (panelHandle, PANEL_VSPEED,100* shipvx);
 if(shipvx<=0.4 && shipvx>=-0.4)
{
SetCtrlAttribute (panelHandle, PANEL_VSPEED, ATTR_TEXT_BGCOLOR, VAL_DK_RED);
}
else 
{
	SetCtrlAttribute (panelHandle, PANEL_VSPEED, ATTR_TEXT_BGCOLOR,MakeColor(27,27,28));
}

SetCtrlVal (panelHandle, PANEL_FUEL,fuel); 	
}

void timefunc ()
{   int min;
	SetCtrlVal (panelHandle, PANEL_NSEC, (time_count+1)%60);
	time_count++;
	 min=time_count/60;
	 SetCtrlVal (panelHandle, PANEL_NMIN, min%60); 
}

void update ()	    
{
	if(explosion==0)
	{
		switch(diff)
		{
			case 1://easy
//right key
	if ((Keys_Down[39] || Keys_Down['d']))
	{
		rotator_angle+=1;   
			  
		right=1;
	}
	else right=0 ;
	
   //left key
  	if (Keys_Down[37] || Keys_Down['a'] )
	{
		rotator_angle+=-1;
		left=1;
	}	
	else left=0;
  // up key
	if (Keys_Down[38] || Keys_Down['w'] )
	{
	calculation  ();
	shipvy=shipvy-ay*dt;
	shipy=shipy+shipvy*dt-ay*dt*dt/2 ; 
	shipvx=shipvx+ax*dt;
	shipx=shipx+shipvx*dt+ax*dt*dt/2 ; 
	mid=1;
	BASS_ChannelPlay(Thrust_SND,TRUE); 
	}
	else
	{ calculation  (); 
		
	mid=0;
	  shipx=shipx+shipvx*dt;
	  shipvy=shipvy+0.05*dt; 
	shipy=shipy+shipvy*dt+0.05*dt*dt/2;
	}
	break;
	//******************************************
			case 2://hard
				if(fuel>0)
				{
				if ((Keys_Down[39] || Keys_Down['d']))
	{
		rotator_angle+=1;   
			  
		right=1;
	}
	else right=0 ;
	
   //left key
  	if (Keys_Down[37] || Keys_Down['a'] )
	{
		rotator_angle+=-1;
		left=1;
	}	
	else left=0;
  // up key
	if (Keys_Down[38] || Keys_Down['w'] )
	{
	calculation  ();
	shipvy=shipvy-ay*dt;
	shipy=shipy+shipvy*dt-ay*dt*dt/2 ; 
	shipvx=shipvx+ax*dt;
	shipx=shipx+shipvx*dt+ax*dt*dt/2 ; 
	mid=1;
	BASS_ChannelPlay(Thrust_SND,TRUE); 
	fuel--;
	}
	else
	{ calculation  (); 
		
	mid=0;
	  shipx=shipx+shipvx*dt;
	  shipvy=shipvy+0.05*dt; 
	shipy=shipy+shipvy*dt+0.05*dt*dt/2;
	}
				}
				else
				{
					mid=0;
					left=0;
					right=0 ;
				shipx=shipx+shipvx*dt;
	  			shipvy=shipvy+0.05*dt; 
				shipy=shipy+shipvy*dt+0.05*dt*dt/2;
				}
				break;
	}
	
	surrounding ();
	}
	if(explosion ==1)
	{ 
		explosionfunc(); 
	lives--;
	switch (lives)
	{
		case 3:
			SetCtrlAttribute (panelHandle, PANEL_LIVE1, ATTR_VISIBLE, 1);
			SetCtrlAttribute (panelHandle, PANEL_LIVE2, ATTR_VISIBLE, 1);
			 SetCtrlAttribute (panelHandle, PANEL_LIVE3, ATTR_VISIBLE, 1);
			break;
		case 2:
			
			SetCtrlAttribute (panelHandle, PANEL_LIVE1, ATTR_VISIBLE, 1);
			SetCtrlAttribute (panelHandle, PANEL_LIVE2, ATTR_VISIBLE, 1);
			SetCtrlAttribute (panelHandle, PANEL_LIVE3, ATTR_VISIBLE, 0);
			MessagePopup ("DEAD", "Click ok to continue \n 2 lives left"); 
			break;
		case 1:
			SetCtrlAttribute (panelHandle, PANEL_LIVE1, ATTR_VISIBLE, 1);
			SetCtrlAttribute (panelHandle, PANEL_LIVE2, ATTR_VISIBLE, 0);
			SetCtrlAttribute (panelHandle, PANEL_LIVE3, ATTR_VISIBLE, 0);
			MessagePopup ("DEAD", "Click ok to continue \n 1 live left"); 
			break;
		case 0:
			
	 
    strcpy (score[10].name,user_name);
    score[10].scoretot=Score;
	score[10].level=lvl;
	for(int j=0; j<=10; j++)
    for(int i=0;i<10;i++)
     if(score[i].scoretot<score[i+1].scoretot)
	 {
	 score0=score[i];
     score[i]=score[i+1];	 
     score[i+1]=score0;
	 }
    
	fp = fopen ("data_Table.txt", "w");

	for(int i=0; i<10; i++)
	fprintf (fp,"%s ,%d,%d  \n", score[i].name,score[i].scoretot,score[i].level);


	for(int k=1,i=1; k<=10,i<=10; k++,i++)
	{
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (1, k), score[i-1].name);
		SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (2, k), score[i-1].scoretot);
	    SetTableCellVal (panelHandle3, SCOREBOARD_TABLE, MakePoint (3, k), score[i-1].level);

	} 
	  
	fclose (fp);
			break;
	}
	
	
	resetfunc () ;  	   
	}
	 data ();
   asteroidfunc ();
   scorefunc();
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Spaceship Landing.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 =LoadPanel (0, "Spaceship Landing.uir",ABOUTPANEL)) < 0)
		return -1;
	if ((panelHandle3 =LoadPanel (0, "Spaceship Landing.uir",SCOREBOARD)) < 0)
		return -1;
	  srand(time(0)); 
	initialize();
	 initialize_astorids ();
	DisplayPanel (panelHandle);
	
	RunUserInterface ();
	
	terminate();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK panelfunc (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK timerfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
									 
				draw();
			 	update(); 
			break;
	}
	return 0;
}

void CVICALLBACK NewGameFunc (int menuBar, int menuItem, void *callbackData,
							  int panel)
{   time_count=0;   
	lvl=1;
	lives=3;
	SetCtrlAttribute (panelHandle, PANEL_LIVE1, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_LIVE2, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_LIVE3, ATTR_VISIBLE, 1);
	map_counter=1;
	resetfunc () ;
	initialize_astorids ();
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 0);
	SetCtrlAttribute (panelHandle, PANEL_EASY, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_HARD, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_START, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_SCOREBUTT, ATTR_VISIBLE, 1); 
	SetCtrlAttribute (panelHandle, PANEL_HARD, ATTR_DIMMED, 0);
	SetCtrlAttribute (panelHandle, PANEL_EASY, ATTR_DIMMED, 0);
	SetCtrlAttribute (panelHandle, PANEL_user_name, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_PICTURE, ATTR_VISIBLE, 1);
	SetCtrlAttribute (panelHandle, PANEL_TEXTMSG_6, ATTR_VISIBLE, 1); 
	Score=0;
	bonus=0;
}

void CVICALLBACK HighScoreFunc (int menuBar, int menuItem, void *callbackData,
								int panel)
{
	DisplayPanel (panelHandle3); 
}

void CVICALLBACK HelpFunc (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	OpenDocumentInDefaultViewer ("Help.pdf", VAL_NO_ZOOM);
}

void CVICALLBACK AboutFunc (int menuBar, int menuItem, void *callbackData,
							int panel)
{
	DisplayPanel (panelHandle2);
}

int CVICALLBACK ExitAboutPanel (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			 HidePanel (panelHandle2);
			break;
	}
	return 0;
}

void CVICALLBACK DemoFunc (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	OpenDocumentInDefaultViewer ("demo.mp4", VAL_NO_ZOOM); 
}

int CVICALLBACK timer2func (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			timefunc (); 
			break;
	}
	return 0;
}

int CVICALLBACK Easyfunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			diff=1;
			SetCtrlAttribute (panelHandle, PANEL_EASY, ATTR_DIMMED, 1);
			 SetCtrlAttribute (panelHandle, PANEL_HARD, ATTR_DIMMED, 0); 
			break;
	}
	return 0;
}

int CVICALLBACK Hardfunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			diff=2;
			SetCtrlAttribute (panelHandle, PANEL_HARD, ATTR_DIMMED, 1);
			 SetCtrlAttribute (panelHandle, PANEL_EASY, ATTR_DIMMED, 0);
			break;
	}
	return 0;
}

int CVICALLBACK Startfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle, PANEL_user_name,user_name);
			 SetCtrlAttribute (panelHandle, PANEL_EASY, ATTR_VISIBLE, 0);
			  SetCtrlAttribute (panelHandle, PANEL_HARD, ATTR_VISIBLE, 0);
			   SetCtrlAttribute (panelHandle, PANEL_SCOREBUTT, ATTR_VISIBLE, 0);
			   SetCtrlAttribute (panelHandle, PANEL_START, ATTR_VISIBLE, 0);
			   SetCtrlAttribute (panelHandle, PANEL_user_name, ATTR_VISIBLE, 0);
			    SetCtrlAttribute (panelHandle, PANEL_PICTURE, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panelHandle, PANEL_TEXTMSG_6, ATTR_VISIBLE, 0);
		  SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			 SetCtrlAttribute (panelHandle, PANEL_TIMER_2, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK ScorePanel (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			 HidePanel (panelHandle3);
			break;
	}
	return 0;
}

int CVICALLBACK ScoreButtFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 DisplayPanel (panelHandle3);
			break;
	}
	return 0;
}

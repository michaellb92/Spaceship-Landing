#include "windows.h" 
#include "toolbox.h"
#include <analysis.h>
#include <ansi_c.h> 
#include <cvirte.h>		
#include <userint.h>
#include "Spaceship Landing.h"
#include "TalGameLibrary.h"

static int panelHandle;
//bitmap handles
int ship,shipmid,shipleft,shipright,spacebg;
//ship movment
double shipvx,shipvy,dt=0.5,ay,ax,shipx=400,shipy=600, rotator_angle=3600.0,s,c,angle;
 //  ship image movment 
int left,right,mid;

 //variables for keyboard monitoring
int Callback_Data;	
int Posting_Handle; 
int Keys_Down[256]={0};
 double Pi (void);

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
//image loading 
		TL_QuickRotateLoad("Images\\SpaceShipV4none.png", &ship);
		TL_QuickRotateLoad("Images\\SpaceShipV4middle.png", &shipmid);
		TL_QuickRotateLoad("Images\\SpaceShipV4left.png", &shipleft);
		TL_QuickRotateLoad("Images\\SpaceShipV4right.png", &shipright);
 		GetBitmapFromFile ("Images\\BackgroundV2.png", &spacebg);
  		Connect_To_Windows_Events();
}
void terminate()
{
TL_QuickRotateDiscard(ship); 
TL_QuickRotateDiscard(shipmid);
TL_QuickRotateDiscard(shipleft);
TL_QuickRotateDiscard(shipright);
	
  
   DiscardBitmap(spacebg);
}

 

void draw ()						 
{
	Rect rectangle; 
	int temp_bitmap,temp_bitmap1,temp_bitmap2;
	
	
	//Drawing the rotator:
	   if (mid==0 && left==0 && right==0)
	   {
	CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	//get the rotated bitmap to draw (no need to free it afterwards) and generare the rectangle information
	//to be used in the next drawing operation
	//the rectnalge info is calculated using the provided x and y of the rotator
	temp_bitmap = TL_QuickRotate(ship,rotator_angle,shipx,shipy, &rectangle);
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
	   }
	    if (mid==1 && left==1 && right==0) 
		{
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap1 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
		 if (mid==1 && left==0 && right==1) 
		{
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap2 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
		 if (mid==1 && left==0 && right==0) 
		{
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
		 if (mid==1 && left==1 && right==1) 
		{
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap = TL_QuickRotate(shipmid,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap1 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);
	temp_bitmap2 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);  
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
		if (mid==0 && left==1 && right==0) 
		{
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap1 = TL_QuickRotate(shipleft,rotator_angle,shipx,shipy, &rectangle);
	
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap1, VAL_ENTIRE_OBJECT,rectangle);
	
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
		if (mid==0 && left==0 && right==1) 
		{
			
			CanvasStartBatchDraw(panelHandle, PANEL_CANVAS);
	CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);	
		  CanvasDrawBitmap (panelHandle, PANEL_CANVAS,spacebg, VAL_ENTIRE_OBJECT,VAL_ENTIRE_OBJECT);
	temp_bitmap2 = TL_QuickRotate(shipright,rotator_angle,shipx,shipy, &rectangle);
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, temp_bitmap2, VAL_ENTIRE_OBJECT,rectangle);
	CanvasEndBatchDraw(panelHandle, PANEL_CANVAS);
		}
}

void calculation  ()
{ 
	
	double F=0.1,g=0.05;
	angle=rotator_angle*Pi()/180;
	c = cos (angle);
	s = sin (angle);
	  ax=F*s;
	  ay=F*c-g;

}


void update ()	    
{

//right key
	if ((Keys_Down[39] || Keys_Down['d']))
	{
		rotator_angle+=5;   
			  
		right=1;	  
	}
	else right=0 ;
	
   //left key
  	if (Keys_Down[37] || Keys_Down['a'] )
	{
		rotator_angle+=-5;
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
	}
	else
	{ calculation  (); 
		
	mid=0;
	  shipx=shipx+shipvx*dt;
	  shipvy=shipvy+0.05*dt; 
	  shipy=shipy+shipvy*dt+0.05*dt*dt/2;
	} 
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Spaceship Landing.uir", PANEL)) < 0)
		return -1;
	
	initialize();
	
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

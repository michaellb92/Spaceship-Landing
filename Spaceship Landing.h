/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ABOUTPANEL                       1       /* callback function: ExitAboutPanel */
#define  ABOUTPANEL_PICTURE               2       /* control type: picture, callback function: (none) */
#define  ABOUTPANEL_TEXTMSG               3       /* control type: textMsg, callback function: (none) */

#define  PANEL                            2       /* callback function: panelfunc */
#define  PANEL_CANVAS                     2       /* control type: canvas, callback function: (none) */
#define  PANEL_HSPEED                     3       /* control type: numeric, callback function: (none) */
#define  PANEL_VSPEED                     4       /* control type: numeric, callback function: (none) */
#define  PANEL_FUEL                       5       /* control type: scale, callback function: (none) */
#define  PANEL_NSEC                       6       /* control type: numeric, callback function: (none) */
#define  PANEL_NMIN                       7       /* control type: numeric, callback function: (none) */
#define  PANEL_NLVL                       8       /* control type: numeric, callback function: (none) */
#define  PANEL_NSCORE                     9       /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTMSG                    10      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_5                  11      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  12      /* control type: textMsg, callback function: (none) */
#define  PANEL_LIVE1                      13      /* control type: picture, callback function: (none) */
#define  PANEL_LIVE2                      14      /* control type: picture, callback function: (none) */
#define  PANEL_LIVE3                      15      /* control type: picture, callback function: (none) */
#define  PANEL_user_name                  16      /* control type: string, callback function: (none) */
#define  PANEL_TEXTMSG_3                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  18      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      19      /* control type: timer, callback function: timerfunc */
#define  PANEL_SCOREBUTT                  20      /* control type: command, callback function: ScoreButtFunc */
#define  PANEL_START                      21      /* control type: command, callback function: Startfunc */
#define  PANEL_HARD                       22      /* control type: command, callback function: Hardfunc */
#define  PANEL_EASY                       23      /* control type: command, callback function: Easyfunc */
#define  PANEL_TIMER_2                    24      /* control type: timer, callback function: timer2func */
#define  PANEL_PICTURE                    25      /* control type: picture, callback function: (none) */
#define  PANEL_TEXTMSG_6                  26      /* control type: textMsg, callback function: (none) */

#define  SCOREBOARD                       3       /* callback function: ScorePanel */
#define  SCOREBOARD_TABLE                 2       /* control type: table, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_FFILE                    2
#define  MENUBAR_FFILE_NEWGAME            3       /* callback function: NewGameFunc */
#define  MENUBAR_FFILE_HIGHSCORE          4       /* callback function: HighScoreFunc */
#define  MENUBAR_FFILE_HELP               5       /* callback function: HelpFunc */
#define  MENUBAR_ABOUT                    6       /* callback function: AboutFunc */
#define  MENUBAR_DEMO                     7       /* callback function: DemoFunc */


     /* Callback Prototypes: */

void CVICALLBACK AboutFunc(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK DemoFunc(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Easyfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitAboutPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Hardfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK HelpFunc(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK HighScoreFunc(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK NewGameFunc(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK panelfunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ScoreButtFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ScorePanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Startfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer2func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timerfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif

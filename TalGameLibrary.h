/************** Tal Game Library BETA ***************************************/
/* January 2018                                                             */
/* Written by Dr Tal Alon 					                                */
/* Not fully debugged and tested - so the                                   */
/*     functions might not work properly under                              */
/*     certain circumstances					                            */
/*                                                                          */
/* Aimed for my game developing students only                               */ 
/*--------------------------------------------------------------------------*/
#include "toolbox.h" 


// The TL_rotateBitmap function produces a new bitmap which is
// a rotation of the originally provided bitmap
// the function also supplies the new width and height which are
// needed in order to calculate the valrious MakeRect parameters
// when the rotated bitmap is drawn to a canvas control
//
// typical rectangle coordinates:
// MakeRect(center_y-new_height/2.0,
//          center_x-new_width/2.0,
//          new_height,
//          new_width)
//
// 'angle' is in degrees (rotation is clockwise)
//
// Important Note 1: This function allocates memory for a bitmap,
//                   you must use DiscardBitmap to free it on every
//                   call, or your program will consume more and more memory
// Important Note 2: The time it takes to rotate an image is roughly 
//                   proportional to the image size. you should run your 
//                   program in 'release mode' (and not in 'debug mode') for
//                   best performance. In this mode the function should 
//                   be expected to rotate ~2.5 million pixels per second.
//                   This means that a 50x40 pixel image can be rotated
//                   ~1250 times a second but a 500x400 pixel image 
//                   only ~12.5 time a second. Keep your images small
//                   especially if you have many images
// Advice          : If you want to speed things up you can initially create
//                   an array of 359 integers and preload into that array
//                   the rotated results. this is especially good for repeating
//                   objects such as meteors.                   
//
extern int TL_rotateBitmap(int bitmap,
                            double angle,
							int *new_width,
							int *new_height);



// The SpitSprites function takes a bitmap containin several sprites
// and fills the supplied bitmap_arr with new bitmaps, each contains only
// one sprite image
//
// 'horizontal' - specify the number of sprite images in every line
// 'vertical'   - specify the number of sprite images in every column
//
// Important Note  : This function allocates memory for all new bitmaps,
//                   you must use DiscardBitmap to free it when you are done.
extern void TL_SpitSprites(int bitmapID,
						int horizontal,
                        int vertical,
						int *bitmap_arr);

// The TL_GetAngleFromPoints function is fed a vector starting 
// from the center of the image to another point on the canvas
// (maybe where the mouse if pointing) and return the angle (degrees)
// between this vector and the Y axis 
// Can be used to rotate an image to point to that direction
extern double TL_GetAngleFromPoints(Point center, Point tip);


extern int TL_QuickRotateLoad(char filename[], int *TL_bitmap_id);

extern int TL_QuickRotateDiscard(int TL_bitmap_id);

extern int TL_QuickRotate(int TL_bitmap_id, double angle_degrees, double image_center_x, double image_center_y, Rect *rectangle);


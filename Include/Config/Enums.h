/**********************************************************************************************************************
 * @file        : Enums.h
 * 
 * @brief       : This file container all enums used in the librery,
 * 
 * @note        : Some enums are originally from GTK,
 *                but they are redefined to provide the user with some level of abstraction
 *
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 22-03-2025
 * @last_Update : 22-03-2025
 **********************************************************************************************************************/

#ifndef ENUMS_H
#define ENUMS_H


typedef enum
{
   window_none,               // <=> GTK_WIN_POS_NONE
   window_center,             // <=> GTK_WIN_POS_CENTER,
   window_mouse,              // <=> GTK_WIN_POS_MOUSE
   window_center_always,      // <=> GTK_WIN_POS_CENTER_ALWAYS
   window_center_on_parent    // <=> GTK_WIN_POS_CENTER_ON_PARENT
} Window_Position;


typedef enum
{
   style_normal,              // <=> GTK_RELIEF_NORMAL
   style_half,                // <=> GTK_RELIEF_HALF
   style_none                 // <=> GTK_RELIEF_NONE
} Relief_Style;


typedef enum {
   align_fill,                // <=> GTK_ALIGN_FILL
   align_start,               // <=> GTK_ALIGN_START
   align_end,                 // <=> GTK_ALIGN_END
   align_center,              // <=> GTK_ALIGN_CENTER
   align_baseline             // <=> GTK_ALIGN_BASELINE
} Align;




#endif // ENUMS_H
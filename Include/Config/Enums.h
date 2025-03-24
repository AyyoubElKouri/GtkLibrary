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
    none,                // <=> GTK_WIN_POS_NONE
    center,              // <=> GTK_WIN_POS_CENTER,
    mouse,               // <=> GTK_WIN_POS_MOUSE
    center_always,       // <=> GTK_WIN_POS_CENTER_ALWAYS
    center_on_parent     // <=> GTK_WIN_POS_CENTER_ON_PARENT
 } Window_Position;






 #endif // ENUMS_H
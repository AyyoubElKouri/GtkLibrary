/**********************************************************************************************************************
 * @file        : Window.h
 * 
 * @brief       : This file is the header file for the header bar widget,
 *                it contains all the functions and structs related to the header bar widget.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 22-03-2025
 * @last_Update : 22-03-2025
 **********************************************************************************************************************/


#ifndef HEADER_BAR_H
#define HEADER_BAR_H

#include "../../Config/Config.h"

typedef struct Header_Bar Header_Bar;

Header_Bar *New_Header_Bar(
                              char *id,
                              char *title,
                              char *subtitle,
                              bool close_Button,
                              GtkWidget *custom_Title,
                              char *decoration_Layout,
                              double opacity,
                              char *icon,
                              char *background_Color,
                              char *background_Image
                         );


Header_Bar *New_Header_Bar_Default(char *id, char *title);


// Setters ---------------------------------------------------------------------------------------------------------

void Header_Bar_Set_Id                  (Header_Bar *header_bar, char *id);

void Header_Bar_Set_Title               (Header_Bar *header_bar, char *title);

void Header_Bar_Set_Subtitle            (Header_Bar *header_bar, char *subtitle);

void Header_Bar_Set_Close_Button        (Header_Bar *header_bar, bool close_Button);

void Header_Bar_Set_Custom_Title        (Header_Bar *header_bar, GtkWidget *custom_Title);

void Header_Bar_Set_Decoration_Layout   (Header_Bar *header_bar, char *decoration_Layout);

void Header_Bar_Set_Opacity             (Header_Bar *header_bar, double opacity);

void Header_Bar_Set_Icon                (Header_Bar *header_bar, char *icon);

void Header_Bar_Set_Background_Color    (Header_Bar *header_bar, char *background_Color);

void Header_Bar_Set_Background_Image    (Header_Bar *header_bar, char *background_Image);


// Getters ---------------------------------------------------------------------------------------------------------

char  *Header_Bar_Get_Id                (Header_Bar *header_bar);

char  *Header_Bar_Get_Title             (Header_Bar *header_bar);

char  *Header_Bar_Get_Subtitle          (Header_Bar *header_bar);

bool   Header_Bar_Get_Close_Button      (Header_Bar *header_bar);

char  *Header_Bar_Get_Decoration_Layout (Header_Bar *header_bar);

double Header_Bar_Get_Opacity           (Header_Bar *header_bar);

char  *Header_Bar_Get_Icon              (Header_Bar *header_bar);

char  *Header_Bar_Get_Background_Color  (Header_Bar *header_bar);

char  *Header_Bar_Get_Background_Image  (Header_Bar *header_bar);

GtkWidget *Header_Bar_Get_Custom_Title  (Header_Bar *header_bar);

// Functions -------------------------------------------------------------------------------------------------------

void Header_Bar_Show                    (Header_Bar *header_bar);

void Header_Bar_Destroy                 (Header_Bar *header_bar);

GtkWidget *Header_Bar_Get_Widget        (Header_Bar *header_bar);

#endif // HEADER_BAR_H
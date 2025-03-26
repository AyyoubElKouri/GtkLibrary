/**********************************************************************************************************************
 * @file        : Button.h
 * 
 * @brief       : This file is the header file for the button widget.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 25-03-2025
 * @last_Update : 25-03-2025
 **********************************************************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include "../../Config/Config.h"

typedef struct button Button;

Button *New_Button 
                    (
                        char *id,
                        char *label, 
                        char *image, 
                        int image_Width,
                        int image_Height,
                        Relief_Style relief_Style, 
                        bool use_Underline, 
                        double opacity, 
                        int width, 
                        int height, 
                        int margin_Top, 
                        int margin_Bottom, 
                        int margin_Left, 
                        int margin_Right, 
                        Align horizontal_Align, 
                        Align vertical_Align, 
                        bool horizontal_Expand, 
                        bool vertical_Expand, 
                        void (*callback)()
                    );

Button *New_Button_Default(char *id, char *label);


// Setters -----------------------------------------------------------------------------------------------------------

void         Button_Set_Id               (Button *button, char *id);

void         Button_Set_Label            (Button *button, char *label);

void         Button_Set_Image            (Button *button, char *image, int image_Width, int image_Height);

void         Button_Set_Image_Width      (Button *button, int image_Width);

void         Button_Set_Image_Height     (Button *button, int image_Height);

void         Button_Set_Relief_Style     (Button *button, Relief_Style relief_Style);

void         Button_Set_Underline        (Button *button, bool use_Underline);

void         Button_Set_Opacity          (Button *button, double opacity);

void         Button_Set_Dimensions       (Button *button, int width, int height);

void         Button_Set_Margins          (Button *button, int margin_Top, int margin_Bottom, int margin_Left, int margin_Right);

void         Button_Set_Aligns           (Button *button, Align horizontal_Align, Align vertical_Align);

void         Button_Set_Expands          (Button *button, bool horizontal_Expand, bool vertical_Expand);

void         Button_Set_CallBack         (Button *button, void (*callback)());

void         Button_Set_Data                    (Button *button, char *key, void *data);


// Getters -----------------------------------------------------------------------------------------------------------

char *       Button_Get_Id               (Button *button);

char *       Button_Get_Label            (Button *button);

char *       Button_Get_Image            (Button *button);

int          Button_Get_Image_Width      (Button *button);

int          Button_Get_Image_Height     (Button *button);

bool         Button_Get_Use_Underline    (Button *button);

double       Button_Get_Opacity          (Button *button);

int          Button_Get_Width            (Button *button);

int          Button_Get_Height           (Button *button);

int          Button_Get_Margin_Top       (Button *button);

int          Button_Get_Margin_Bottom    (Button *button);

int          Button_Get_Margin_Left      (Button *button);

int          Button_Get_Margin_Right     (Button *button);

Align        Button_Get_Horizontal_Align (Button *button);

Align        Button_Get_Vertical_Align   (Button *button);

bool         Button_Get_Horizontal_Expand(Button *button);

bool         Button_Get_Vertical_Expand  (Button *button);

void (*Button_Get_Callback(Button *button))(Widget *);

void *       Button_Get_Data             (Widget *button, char *key);

Relief_Style Button_Get_Relief_Style     (Button *button);

// Functions -------------------------------------------------------------------------------------------------------

Widget *Button_Get_Widget  (Button *button);



#endif // BUTTON_H
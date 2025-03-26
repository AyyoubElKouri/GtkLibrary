/**********************************************************************************************************************
 * @file        : Window.h
 * 
 * @brief       : This file is the header file for the window widget,
 *                it contains all the functions and structs related to the window widget.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 22-03-2025
 * @last_Update : 22-03-2025
 **********************************************************************************************************************/


 #ifndef WINDOW_H
 #define WINDOW_H

 #include "../../Config/Config.h"
 

 typedef struct window Window;



 /**
  * @brief Creates a new window with specified properties.
  *
  * @param id Unique identifier for the window
  * @param title Window title displayed in the title bar
  * @param width Initial width of the window
  * @param height Initial height of the window
  * @param icon Path to the window's icon image
  * @param opacity Window transparency level (0.0 to 1.0)
  * @param main_Window Indicates if this is the main application window
  * @param resizable Whether the window can be resized by the user
  * @param decorated If window should have standard window decorations
  * @param modal Whether the window blocks input to other windows
  * @param deletable If the window can be closed by the user
  * @param full_Screen Whether the window should start in full screen mode
  * @param background_Color Background color of the window
  * @param background_Image Path to background image for the window
  * @param position Initial screen position of the window
  * @return Pointer to the newly created Window
  */
 Window* New_Window(
                         char *id,
                         char *title,
                         int  width,
                         int  height,
                         char *icon,
                         double  opacity,
                         bool main_Window,
                         bool resizable,
                         bool decorated,
                         bool modal,
                         bool deletable,
                         bool full_Screen,
                         char *background_Color,
                         char *background_Image,
                         Window_Position position
                   );


 /**
  * @brief Creates a new window with default settings.
  *
  * @param id Unique identifier for the window
  * @param main_Window Indicates if this is the main application window
  * @return Pointer to the newly created Window with default properties
  */
 Window *New_Window_Default(char *id, bool main_Window);


 // Setters ----------------------------------------------------------------------------------------------

 void Window_Set_Id                 (Window *window, char *id);

 void Window_Set_Title              (Window *window, char *title);

 void Window_Set_Width              (Window *window, int width);

 void Window_Set_Height             (Window *window, int height);

 void Window_Set_Icon               (Window *window, char *icon);

 void Window_Set_Opacity            (Window *window, double opacity);

 void Window_Set_Resizable          (Window *window, bool resizable);

 void Window_Set_Decorated          (Window *window, bool decorated);

 void Window_Set_Modal              (Window *window, bool modal);

 void Window_Set_Deletable          (Window *window, bool deletable);

 void Window_Set_Full_Screen        (Window *window, bool full_Screen);

 void Window_Set_Background_Color   (Window *window, char *background_Color);

 void Window_Set_Background_Image   (Window *window, char *background_Image);

 void Window_Set_Position           (Window *window, Window_Position position);


 // Getters ----------------------------------------------------------------------------------------------

 char  *Window_Get_Id               (Window *window);

 char  *Window_Get_Title            (Window *window);

 int    Window_Get_Width            (Window *window);

 int    Window_Get_Height           (Window *window);

 char  *Window_Get_Icon             (Window *window);

 double Window_Get_Opacity          (Window *window);

 bool   Window_Get_Resizable        (Window *window);

 bool   Window_Get_Decorated        (Window *window);

 bool   Window_Get_Modal            (Window *window);

 bool   Window_Get_Deletable        (Window *window);

 bool   Window_Get_Full_Screen      (Window *window);

 char  *Window_Get_Background_Color (Window *window);

 char  *Window_Get_Background_Image (Window *window);

 Window_Position Window_Get_Position(Window *window);


 // Window Controls ----------------------------------------------------------------------------------------------

 void    Window_Show                (Window *window);

 Widget *Window_Get_Widget          (Window *window);

 void    Window_Destroy             (Window *window);

 void    Window_Set_Header_Bar      (Window *window, Header_Bar *header_bar);

 void    Window_Set_Container       (Window *window, Container *container);
 

 // Starting Application function ----------------------------------------------------------------------------------------------

 void Application_Start(void (*Start_Function)());

 #endif // WINDOW_H
#include "Include/Widgets/Widgets.h"

extern GtkApplication *application;


void activate(Widget *widget, gpointer data)
{   
    Window *window = New_Window_Default("main_window", true);
    Header_Bar *header_bar = New_Header_Bar_Default("id_hello", "Ayyoub");

   
    
    
    Window_Show(window);
}   



int main(){
    Application_Start(activate);
    return 0;
}
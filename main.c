#include "Include/Widgets/Widgets.h"

extern GtkApplication *application;


void activate(Widget *widget, gpointer data)
{   
    Window *window = New_Window_Default("main_window", true);
    Header_Bar *header_bar = New_Header_Bar_Default("id_hello", "Ayyoub");

   
    Window_Set_Header_Bar(window, header_bar);
    printf("Titre du window : %s\n", Window_Get_Title(window));
    printf("Width : %d\n", Window_Get_Width(window));
    printf("height : %d\n", Window_Get_Height(window));

    
    Window_Show(window);
}   



int main(){
    Application_Start(activate);
    return 0;
}
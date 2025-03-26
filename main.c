#include "Include/Widgets/Widgets.h"

void hello(Widget *widget){
    GtkWidget *w = (GtkWidget *)Button_Get_Data(widget, "box");
    int orienatation = gtk_orientable_get_orientation(GTK_ORIENTABLE(w));
    gtk_orientable_set_orientation(GTK_ORIENTABLE(w), (orienatation == GTK_ORIENTATION_HORIZONTAL) ? GTK_ORIENTATION_VERTICAL : GTK_ORIENTATION_HORIZONTAL);
}

void ayyoub(){

    Window *window = New_Window_Default("id_window", true);

        Header_Bar *header_bar = New_Header_Bar_Default("id_header_bar", "Ayyoub");
        Window_Set_Header_Bar(window, header_bar);

        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

        Button *button = New_Button_Default("id_button", "Click Ayyoub");

        Button_Set_Dimensions(button, 150, 60);

        Button *button2 = New_Button_Default("id_button_2", "Hello bro");
        Button_Set_Dimensions(button2, 150, 60);

        Button_Set_CallBack(button, hello);
        Button_Set_Data(button, "box", box);

        Window_Set_Container(window, box);

    Window_Show(window);


}

int main(){
    Application_Start(ayyoub);
}
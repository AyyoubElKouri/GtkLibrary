#include "Button.h"

typedef struct button
{
    GtkWidget *button;
    char *label;
} Button;

Button *New_Button(char *label){
    Button *buttonInfos = malloc(sizeof(Button));
    if(!buttonInfos) return NULL;

    GtkWidget *button = gtk_button_new();
    if(label){
        gtk_button_set_label(GTK_BUTTON(button), label);
        buttonInfos->label = g_strdup(label);
    } else {
        gtk_button_set_label(GTK_BUTTON(button), "Default label");
        buttonInfos->label = g_strdup("Default label");
    }

    buttonInfos->button = button;
    return buttonInfos;
}

void Set_CallBack(Button *button, void (*callback)()){
    g_signal_connect(button->button, "clicked", G_CALLBACK(callback), button);
}

GtkWidget *Get_Widget(Button *button){
    return button->button;
}

void Set_Data(Button *button, char *key, void *data)
{
    g_object_set_data(G_OBJECT(button->button), key, data);
}

void *Get_Data(Widget *button, char *key)
{
    g_object_get_data(G_OBJECT(button), key);
}
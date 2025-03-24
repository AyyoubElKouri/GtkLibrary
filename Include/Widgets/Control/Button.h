#include <gtk/gtk.h>

typedef struct button Button;
typedef struct GtkWidget Widget;


Button *   New_Button  (char *label);

void       Set_CallBack(Button *button, void (*callback)());

GtkWidget *Get_Widget  (Button *button);

void       Set_Data    (Button *button, char *key, void *data);

void *     Get_Data    (Widget *button, char *key);
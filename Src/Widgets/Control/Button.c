/**********************************************************************************************************************
 * @file        : Button.c
 * 
 * @brief       : This file contains the implementation of the Button widget functions.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 25-03-2025
 * @last_Update : 25-03-2025
 **********************************************************************************************************************/
 

#include "../../../Include/Widgets/Widgets.h"


typedef struct button
{
    GtkWidget *button;
    char *id;
    char *label;
    char *image;
    int image_Width;
    int image_Height;
    Relief_Style relief_Style;
    bool use_Underline;
    double opacity;
    int width;
    int height;
    int margin_Top;
    int margin_Bottom;
    int margin_Left;
    int margin_Right;
    Align horizontal_Align;
    Align vertical_Align;
    bool horizontal_Expand;
    bool vertical_Expand;
    void (*callback)();
    bool data;
} Button;


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
                    )
{
    if(!id){
        printf("Error: id is required\n");
        return NULL;
    }

    GtkWidget *button = gtk_button_new();

    Button *buttonInfos = malloc(sizeof(Button));
    if(!buttonInfos) return NULL;

    buttonInfos->button = button;

    buttonInfos->id = NULL;
    buttonInfos->label = NULL;
    buttonInfos->image = NULL;

    Button_Set_Id           (buttonInfos, id);
    Button_Set_Label        (buttonInfos, label);
    Button_Set_Image        (buttonInfos, image, image_Width, image_Height);
    Button_Set_Relief_Style (buttonInfos, relief_Style);
    Button_Set_Underline    (buttonInfos, use_Underline);
    Button_Set_Opacity      (buttonInfos, opacity);
    Button_Set_Dimensions   (buttonInfos, width, height);
    
    Button_Set_Expands      (buttonInfos, horizontal_Expand, vertical_Expand);
    Button_Set_CallBack     (buttonInfos, callback);
    
    if(horizontal_Align < 0) horizontal_Align = -1;
    if(vertical_Align   < 0) vertical_Align   = -1;
    Button_Set_Aligns       (buttonInfos, horizontal_Align, vertical_Align);

    if(margin_Top    < 0) margin_Top    = 0;
    if(margin_Bottom < 0) margin_Bottom = 0;
    if(margin_Left   < 0) margin_Left   = 0;
    if(margin_Right  < 0) margin_Right  = 0;
    Button_Set_Margins      (buttonInfos, margin_Top, margin_Bottom, margin_Left, margin_Right);

    return buttonInfos;
}

Button *New_Button_Default(char *id, char *label){
    return New_Button  
                        (  
                            id, label, NULL, 0, 0, 
                            style_normal, false, 1.0, 0, 
                            0, 0, 0, 0, 0, -1, -1, 
                            false, false, NULL
                        );
}

void Button_Set_Id(Button *button, char *id){
    
    if(!Valide_Pointer(button)) return;

    // Check the id
    if(!id){
        printf("Error: id is required\n");
        return;
    }

    // Set the id
    if(button->id) g_free(button->id);
    button->id = g_strdup(id);

    return;
}


void Button_Set_Label(Button *button, char *label){
    
    if(!Valide_Pointer(button)) return;

    // Check the label
    if(!label){
        if(button->label) g_free(button->label);
        gtk_button_set_label(GTK_BUTTON(button->button), NULL);
        button->label = NULL;
    } else {
        gtk_button_set_label(GTK_BUTTON(button->button), label);
        if(button->label) g_free(button->label);
        button->label = g_strdup(label);
    }

    return;
}

void Button_Set_Image(Button *button, char *image, int image_Width, int image_Height){
    
    if(!Valide_Pointer(button)) return;

    // Check the image
    if(!image){
        if(button->image) g_free(button->image);
        gtk_button_set_image(GTK_BUTTON(button->button), NULL);
        button->image = NULL;
        button->image_Width = -1;
        button->image_Height = -1;
    } else {
            if(Valide_Image_Path(image)){
                GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image, NULL);
                if(image_Height > 0 && image_Width > 0){
                    pixbuf = gdk_pixbuf_scale_simple(pixbuf, image_Width, image_Height, GDK_INTERP_BILINEAR);
                }
                gtk_button_set_image(GTK_BUTTON(button->button), gtk_image_new_from_pixbuf(pixbuf));
                if(button->image) g_free(button->image);
                button->image = g_strdup(image);
                button->image_Width = (image_Width > 0) ? image_Width : -1;
                button->image_Height = (image_Height > 0) ? image_Height : -1;
                g_object_unref(pixbuf);
            } else {
                printf("Error: Invalid image path\n");
            }
    }

    return;
}

void Button_Set_Image_Width(Button *button, int image_Width){
    
    if(!Valide_Pointer) return;

    // Check the image_Width
    if(image_Width < 0) return;

    // Set the image_Width
    if(button->image_Width != image_Width)
        if(button->image){
            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(button->image, NULL);
            int height = (button->image_Height > 0) ? button->image_Height : 25;
            pixbuf = gdk_pixbuf_scale_simple(pixbuf, image_Width, height , GDK_INTERP_BILINEAR);
            gtk_button_set_image(GTK_BUTTON(button->button), gtk_image_new_from_pixbuf(pixbuf));
            g_object_unref(pixbuf);
            button->image_Width = image_Width;
            button->image_Height = height;
        }
    
    return;
}

void Button_Set_Image_Height(Button *button, int image_Height){
    
    if(!Valide_Pointer) return;

    // Check the image_Height
    if(image_Height < 0) return;

    // Set the image_Height
    if(button->image_Height != image_Height)
        if(button->image){
            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(button->image, NULL);
            int width = (button->image_Width > 0) ? button->image_Width : 25;
            pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, image_Height, GDK_INTERP_BILINEAR);
            gtk_button_set_image(GTK_BUTTON(button->button), gtk_image_new_from_pixbuf(pixbuf));
            g_object_unref(pixbuf);
            button->image_Height = image_Height;
            button->image_Width = width;
        }

    return;
}

void Button_Set_Relief_Style(Button *button, Relief_Style relief_Style){
    
    if(!Valide_Pointer) return;

    // Set the relief_Style
    if(relief_Style < 0 || relief_Style > 2) relief_Style = style_normal;
    gtk_button_set_relief(GTK_BUTTON(button->button), relief_Style);
    button->relief_Style = relief_Style;

    return;
}

void Button_Set_Underline(Button *button, bool use_Underline){
    
    if(!Valide_Pointer) return;

    // Set the use_Underline
    gtk_button_set_use_underline(GTK_BUTTON(button->button), use_Underline);
    button->use_Underline = use_Underline;

    return;
}

void Button_Set_Opacity(Button *button, double opacity){
    
    if(!Valide_Pointer) return;

    // Set the opacity
    if(opacity < 0 || opacity > 1) opacity = 1;
    gtk_widget_set_opacity(GTK_WIDGET(button->button), opacity);
    button->opacity = opacity;

    return;
}

void Button_Set_Dimensions(Button *button, int width, int height){
    
    if(!Valide_Pointer) return;

    // Set the width and height
    if(width <= 0) width = -1;
    if(height <= 0) height = -1;

    gtk_widget_set_size_request(GTK_WIDGET(button->button), width, height);
    button->width = width;
    button->height = height;

    return;
}

void Button_Set_Margins(Button *button, int margin_Top, int margin_Bottom, int margin_Left, int margin_Right){
    
    if(!Valide_Pointer) return;

    // Set the margins
    if(margin_Top >= 0){
        gtk_widget_set_margin_top(GTK_WIDGET(button->button), margin_Top);
        button->margin_Top = margin_Top;
    }
    
    if(margin_Bottom >= 0){
        gtk_widget_set_margin_bottom(GTK_WIDGET(button->button), margin_Bottom);
        button->margin_Bottom = margin_Bottom;
    }

    if(margin_Left >= 0){
        gtk_widget_set_margin_start(GTK_WIDGET(button->button), margin_Left);
        button->margin_Left = margin_Left;
    } 

    if(margin_Right >= 0){
        gtk_widget_set_margin_end(GTK_WIDGET(button->button), margin_Right);
        button->margin_Right = margin_Right;
    }

    return;
}

void Button_Set_Aligns(Button *button, Align horizontal_Align, Align vertical_Align){

    if(!Valide_Pointer(button)) return;

    // Set the horizontal_Align and vertical_Align
    int horizontal = horizontal_Align;
    if(horizontal > 0){
        if(horizontal_Align > 4) horizontal_Align = align_center;
        gtk_widget_set_halign(GTK_WIDGET(button->button), horizontal_Align);
        button->horizontal_Align = horizontal_Align;
    }

    int vertical = vertical_Align;
    if(vertical > 0){
        if(vertical_Align > 4) vertical_Align = align_center;
        gtk_widget_set_valign(GTK_WIDGET(button->button), vertical_Align);
        button->vertical_Align = vertical_Align;
    }

    return;
}

void Button_Set_Expands(Button *button, bool horizontal_Expand, bool vertical_Expand){

    if(!Valide_Pointer(button)) return;

    // Set the horizontal_Expand and vertical_Expand
    gtk_widget_set_hexpand(GTK_WIDGET(button->button), horizontal_Expand);
    gtk_widget_set_vexpand(GTK_WIDGET(button->button), vertical_Expand);

    button->horizontal_Expand = horizontal_Expand;
    button->vertical_Expand   = vertical_Expand;

    return;
}

void Button_Set_CallBack(Button *button, void (*callback)()){

    if(!Valide_Pointer(button)) return;

    // Set the callback
    if(callback){
        g_signal_connect(G_OBJECT(button->button), "clicked", G_CALLBACK(callback), NULL);
        button->callback = callback;
        button->data = true;
    } else 
        button->data = false;

    return;
}

void Button_Set_Data(Button *button, char *key, void *data){

    if(!Valide_Pointer(button)) return;

    // Set the data
    if(key && data){
        g_object_set_data(G_OBJECT(button->button), key, data);
        button->data = true;
    }
    return;
}

char *Button_Get_Id(Button *button){

    if(!Valide_Pointer(button)) return NULL;
    return button->id;
}

char *Button_Get_Label(Button *button){
    if(!Valide_Pointer(button)) return NULL;
    return button->label;
}

char *Button_Get_Image(Button *button){
    if(!Valide_Pointer(button)) return NULL;
    return button->image;
}

int Button_Get_Image_Width(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->image_Width;
}

int Button_Get_Image_Height(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->image_Height;
}

bool Button_Get_Use_Underline(Button *button){
    if(!Valide_Pointer(button)) -1;
    return button->use_Underline;
}

double Button_Get_Opacity(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->opacity;
}

int Button_Get_Width(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->width;
}

int Button_Get_Height(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->height;
}

int Button_Get_Margin_Top(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->margin_Top;
}

int Button_Get_Margin_Bottom(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->margin_Bottom;
}

int Button_Get_Margin_Left(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->margin_Left;
}

int Button_Get_Margin_Right(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->margin_Right;
}

Align Button_Get_Horizontal_Align(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->horizontal_Align;
}

Align Button_Get_Vertical_Align(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->vertical_Align;
}

bool Button_Get_Horizontal_Expand(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->horizontal_Expand;
}

bool Button_Get_Vertical_Expand(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->vertical_Expand;
}

void *Button_Get_Data(Widget *button, char *key){
    if(!Valide_Pointer(button)) return NULL;
    return g_object_get_data(G_OBJECT(button), key);
}

void (*Button_Get_Callback(Button *button))(Widget *) {
    if (!Valide_Pointer(button)) return NULL;
    return button->callback;
}

Relief_Style  Button_Get_Relief_Style(Button *button){
    if(!Valide_Pointer(button)) return -1;
    return button->relief_Style;
}

Widget *Button_Get_Widget  (Button *button){
    return button->button;
}



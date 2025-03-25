/**********************************************************************************************************************
 * @file        : Header_Bar.c
 * 
 * @brief       : This file contains the implementation of the header bar widget functions.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 22-03-2025
 * @last_Update : 22-03-2025
 **********************************************************************************************************************/

 #include "../../../Include/Widgets/Widgets.h"

 typedef struct Header_Bar
 {
    GtkWidget *header_Bar;
    char *id;
    char *title;
    char *subtitle;
    bool close_Button;
    GtkWidget *custom_Title;
    char *decoration_Layout;
    double opacity;
    char *icon;
    char *background_Color;
    char *background_Image;
 } Header_Bar;
 
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
                            )
{
    if(!id){
        printf("Error: id is required\n");
        return NULL;
    }

    Header_Bar *header_Bar = (Header_Bar *)malloc(sizeof(Header_Bar));
    if(!header_Bar){
        printf("Error: Failed to allocate memory for header bar\n");
        return NULL;
    }

    header_Bar->id = g_strdup(id);

    GtkWidget *header_bar = gtk_header_bar_new();

    if(title){
        gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), title);
        header_Bar->title = g_strdup(title);
    } else {
        gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Default title");
        header_Bar->title = g_strdup("Default title");
    }

    if(subtitle){
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar), subtitle);
        header_Bar->subtitle = g_strdup(subtitle);
    } else {
        header_Bar->subtitle = NULL;
    }

    // Set the close button
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), close_Button);
    header_Bar->close_Button = close_Button;

    // Set the custom title
    if(custom_Title){
        gtk_header_bar_set_custom_title(GTK_HEADER_BAR(header_bar), custom_Title);
        header_Bar->custom_Title = custom_Title;
    } else {
        header_Bar->custom_Title = NULL;
    }

    // Set the decoration layout
    if(decoration_Layout){
        gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header_bar), decoration_Layout);
        header_Bar->decoration_Layout = g_strdup(decoration_Layout);
    } else {
        header_Bar->decoration_Layout = NULL;
    }

    // Set the opacity
    if(opacity < 0 || opacity > 1) opacity = 1;
    gtk_widget_set_opacity(header_bar, opacity);
    header_Bar->opacity = opacity;

    // Set the icon
    if(icon){
        GdkPixbuf *icon_Pixbuf = gdk_pixbuf_new_from_file(icon, NULL);
        if(icon_Pixbuf){
            GdkPixbuf *scaled_icon = gdk_pixbuf_scale_simple(icon_Pixbuf, 32, 32, GDK_INTERP_BILINEAR);
            gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), gtk_image_new_from_pixbuf(scaled_icon));
            g_object_unref(icon_Pixbuf);
            g_object_unref(scaled_icon);
            header_Bar->icon = g_strdup(icon);
        } else {
            printf("Error: Icon not found\n");
            header_Bar->icon = NULL;
        }
    } else {
        header_Bar->icon = NULL;
    }

    // Set the background color
    if(background_Color){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *color = g_strdup_printf(".header { background: %s; }", background_Color);
        GError *error = NULL;
        gtk_css_provider_load_from_data(provider, color, -1, &error);
        if(error){
            printf("Error: Color not valide for header bar\n");
            g_error_free(error);
            header_Bar->background_Color = NULL;
        } else {
            gtk_style_context_add_provider_for_screen(
                gdk_screen_get_default(),
                GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
            );
    
            GtkStyleContext *context = gtk_widget_get_style_context(header_bar);
            gtk_style_context_add_class(context, "header");
            header_Bar->background_Color = g_strdup(background_Color);
        }

    } else {
        header_Bar->background_Color = NULL;
    }

    // Set the background image
    if(background_Image){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *image = g_strdup_printf(".header { background-image: url(\"%s\"); background-repeat: no-repeat; background-size: cover; }", background_Image);

        gtk_css_provider_load_from_data(provider, image, -1, NULL);

        gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );

        GtkStyleContext *context = gtk_widget_get_style_context(header_bar);
        gtk_style_context_add_class(context, "header");

        g_free(image);
        header_Bar->background_Image = g_strdup(background_Image);
    } else {
        header_Bar->background_Image = NULL;
    }

    header_Bar->header_Bar = header_bar;
    return header_Bar;
}

Header_Bar *New_Header_Bar_Default(char *id, char *title){
    if(!id){
        printf("Error: id is required\n");
        return NULL;
    }

    return New_Header_Bar(id, title, NULL, true, NULL,
                          ":minimize,maximize,close", 1, NULL, 
                           NULL, NULL
    );
}

void Header_Bar_Set_Id(Header_Bar *header_bar, char *id){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    if(!!id){
        printf("Error: id is required\n");
        return;
    }

    if(header_bar->id) g_free(header_bar->id);
    header_bar->id = g_strdup(id);
    return;
}

 


void Header_Bar_Set_Title(Header_Bar *header_bar, char *title){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    if(!title){
        if(header_bar->title) g_free(header_bar->title);
        header_bar->title = NULL;
        gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar->header_Bar), "");
        return;
    }

    if(header_bar->title) g_free(header_bar->title);
    header_bar->title = g_strdup(title);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar->header_Bar), title);
    
    return;
}

void Header_Bar_Set_Subtitle(Header_Bar *header_bar, char *subtitle){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    if(!subtitle){
        if(header_bar->subtitle) g_free(header_bar->subtitle);
        header_bar->subtitle = NULL;
        gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar->header_Bar), "");
        return;
    }

    if(header_bar->subtitle) g_free(header_bar->subtitle);
    header_bar->subtitle = g_strdup(subtitle);
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header_bar->header_Bar), subtitle);
    return;
}

void Header_Bar_Set_Close_Button(Header_Bar *header_bar, bool close_Button){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar->header_Bar), close_Button);
    header_bar->close_Button = close_Button;

    return;
}

void Header_Bar_Set_Custom_Title(Header_Bar *header_bar, GtkWidget *custom_Title){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    gtk_header_bar_set_custom_title(GTK_HEADER_BAR(header_bar->header_Bar), custom_Title);
    header_bar->custom_Title = custom_Title;
    return;
}


void Header_Bar_Set_Decoration_Layout(Header_Bar *header_bar, char *decoration_Layout){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    if(!decoration_Layout){
        if(header_bar->decoration_Layout) g_free(header_bar->decoration_Layout);
        header_bar->decoration_Layout = NULL;
        gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header_bar->header_Bar), "");
        return;
    }

    if(header_bar->decoration_Layout) g_free(header_bar->decoration_Layout);
    header_bar->decoration_Layout = g_strdup(decoration_Layout);
    gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header_bar->header_Bar), decoration_Layout);

    return;
}

void Header_Bar_Set_Opacity(Header_Bar *header_bar, double opacity){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    // check if opacity is between 0 and 1
    if(opacity < 0 || opacity > 1){
        printf("Error: opacity must be between 0 and 1\n");
        return;
    }

    // set the opacity
    gtk_widget_set_opacity(header_bar->header_Bar, opacity);
    header_bar->opacity = opacity;

    return;
}

void Header_Bar_Set_Icon(Header_Bar *header_bar, char *icon){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }


    // check if icon is a valid path
    GdkPixbuf *icon_Pixbuf;
    if(icon){
        GError *error = NULL;
        icon_Pixbuf = gdk_pixbuf_new_from_file(icon, &error);
        if(error){
            printf("Error: Icon not found\n");
            g_error_free(error);
            return;
        }
    }

    // destroy the old icon
    if(header_bar->icon) g_free(header_bar->icon);
    GList *children = gtk_container_get_children(GTK_CONTAINER(header_bar->header_Bar));
    
    for(GList *child = children; child != NULL; child = child->next){
        if(GTK_IS_IMAGE(child->data)){
            gtk_widget_destroy(GTK_WIDGET(child->data));
            break;
        }
    }

    if(header_bar->icon) g_free(header_bar->icon);
    header_bar->icon = NULL;
    
    // if the icon is null, so is a delete operation
    if(!icon){
        return;
    }

    // set the new icon
    header_bar->icon = g_strdup(icon);
    
    // create a new image
    if(icon_Pixbuf){
        GdkPixbuf *scaled_icon = gdk_pixbuf_scale_simple(icon_Pixbuf, 32, 32, GDK_INTERP_BILINEAR);
        gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar->header_Bar), gtk_image_new_from_pixbuf(scaled_icon));
        g_object_unref(icon_Pixbuf);
        g_object_unref(scaled_icon);
        if(header_bar->icon) g_free(header_bar->icon);
        header_bar->icon = g_strdup(icon);
    } else {
        printf("Error: Icon not found\n");
    }

    return;

}

void Header_Bar_Set_Background_Color(Header_Bar *header_bar, char *background_Color){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }


    if(header_bar->background_Color) g_free(header_bar->background_Color);
    
    GtkCssProvider *provider = gtk_css_provider_new();
        char *color;
        if(!background_Color) {
            header_bar->background_Color = NULL;
            color = g_strdup_printf(".header { background: #dbd7d3; }");
        } else {
            color = g_strdup_printf(".header { background: %s; }", background_Color);
        }

        GError *error = NULL;
        gtk_css_provider_load_from_data(provider, color, -1, &error);
        if(error){
            printf("Error: Color not valide for header bar\n");
            g_error_free(error);
            header_bar->background_Color = NULL;
        } else {
            gtk_style_context_add_provider_for_screen(
                gdk_screen_get_default(),
                GTK_STYLE_PROVIDER(provider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
            );
    
            GtkStyleContext *context = gtk_widget_get_style_context(header_bar->header_Bar);
            gtk_style_context_add_class(context, "header");
            header_bar->background_Color = g_strdup(background_Color);
        }
    
    g_free(color);
    g_object_unref(provider);

    return;
    
}

void Header_Bar_Set_Background_Image(Header_Bar *header_bar, char *background_Image){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }

    if(header_bar->background_Image) g_free(header_bar->background_Image);

    GtkCssProvider *provider = gtk_css_provider_new();
    char *image;
    if(!background_Image) {
        header_bar->background_Image = NULL;
        image = g_strdup_printf(".header { background-image: none; }");
    } else {
        image = g_strdup_printf(".header { background-image: url(\"%s\"); background-repeat: no-repeat; background-size: cover; }", background_Image);
    }

    GError *error = NULL;
    gtk_css_provider_load_from_data(provider, image, -1, &error);
    if(error){
        printf("Error: Image not valide for header bar\n");
        g_error_free(error);
        header_bar->background_Image = NULL;
    } else {
        gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(),
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
        GtkStyleContext *context = gtk_widget_get_style_context(header_bar->header_Bar);
        gtk_style_context_add_class(context, "header");
        header_bar->background_Image = g_strdup(background_Image);
    }

    g_free(image);
    g_object_unref(provider);

    return;
}

char *Header_Bar_Get_Id(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->id;
}


char *Header_Bar_Get_Title(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->title;
}

char *Header_Bar_Get_Subtitle(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->subtitle;
}

bool Header_Bar_Get_Close_Button(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return false;
    }

    return header_bar->close_Button;
}

char *Header_Bar_Get_Decoration_Layout (Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->decoration_Layout;
}

double Header_Bar_Get_Opacity (Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return 0;
    }

    return header_bar->opacity;
}

char *Header_Bar_Get_Icon(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->icon;
}

char *Header_Bar_Get_Background_Color (Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->background_Color;
}

char *Header_Bar_Get_Background_Image (Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->background_Image;
}

GtkWidget *Header_Bar_Get_Custom_Title  (Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return NULL;
    }

    return header_bar->custom_Title;
}






void Header_Bar_Show(Header_Bar *header_bar){
    gtk_widget_show_all(header_bar->header_Bar);
}

void Header_Bar_Destroy(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_bar is NULL\n");
        return;
    }
    if(header_bar->id) g_free(header_bar->id);
    if(header_bar->title) g_free(header_bar->title);
    if(header_bar->subtitle) g_free(header_bar->subtitle);
    if(header_bar->icon) g_free(header_bar->icon);
    if(header_bar->background_Color) g_free(header_bar->background_Color);
    if(header_bar->background_Image) g_free(header_bar->background_Image);
    

    gtk_widget_destroy(header_bar->header_Bar);
    if(header_bar) g_free(header_bar);

}


GtkWidget *Header_Bar_Get_Widget(Header_Bar *header_bar){
    if(!header_bar){
        printf("Error: header_Bar is NULL\n");
        return NULL;
    }

    return header_bar->header_Bar;
}

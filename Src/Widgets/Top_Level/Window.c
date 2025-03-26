/**********************************************************************************************************************
 * @file        : Widgets.c
 * 
 * @brief       : This file contains the implementation of the window widget functions.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 22-03-2025
 * @last_Update : 22-03-2025
 **********************************************************************************************************************/




#include "../../../Include/Widgets/Widgets.h"

GtkApplication *application;


/**
 * @brief Represents a window with comprehensive configuration options
 *
 * This structure encapsulates all properties and settings for a window,
 * including its visual attributes, behavior, and positioning.
 *
 * @note Stores both GTK widget and custom configuration parameters
 */
typedef struct window
{
    GtkWidget *window;
    char *id;
    char *title;
    int  width;
    int  height;
    char *icon;
    double  opacity;
    bool main_Window;
    bool resizable;
    bool decorated;
    bool modal;
    bool deletable;
    bool full_Screen;
    char *background_Color;
    char *background_Image;
    Window_Position position;
} Window;



Window* New_Window(
                        char *id,       char *title,     int  width,      int  height,    char *icon,
                        double  opacity,   bool main_Window, bool resizable,  bool decorated, bool modal,
                        bool deletable, bool full_Screen, char *background_Color,
                        char *background_Image,          Window_Position position
                )
{
    if(!id){
        printf("ID is required\n");
        return NULL;
    }

    // the window
    GtkWidget *window;


    // to store the window informations
    Window *windowInfos = malloc(sizeof(Window));
    if(!windowInfos) return NULL;

    windowInfos->id = g_strdup(id);

    // if the window is the main window (application window)
    if(main_Window){
        window = gtk_application_window_new(application);   
    } else {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    }
    windowInfos->main_Window = main_Window;
    windowInfos->window = window;

    
    // if a title is provide
    if(title){
        gtk_window_set_title(GTK_WINDOW(window), title);
        windowInfos->title = g_strdup(title);
    } else {
        gtk_window_set_title(GTK_WINDOW(window), "Default title");
        windowInfos->title = g_strdup("Default title");
    }

    // set the default size if the provided is not valide
    if(width < 0) width = 700;
    if(height < 0)  height = 500;

    // set the size
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    windowInfos->width = width;
    windowInfos->height = height;


    // if an icon is provided
    if(icon){
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon, NULL);
        if(pixbuf){            
            gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
            g_object_unref(pixbuf);
            windowInfos->icon = g_strdup(icon);
        } else {
            printf("Error: Icon not found\n");
            windowInfos->icon = NULL;
        }
    } else {
        windowInfos->icon = NULL;
    }

    // use the default opacity if the provided is not valide
    if(opacity < 0 || opacity > 1) opacity = 1;

    // set the opacity
    gtk_widget_set_opacity(window, opacity);
    windowInfos->opacity = opacity;

    // if the window is resizable
    if(resizable) gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    else gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    windowInfos->resizable = resizable;

    // if the window is decorated
    if(decorated) gtk_window_set_decorated(GTK_WINDOW(window), TRUE);
    else gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    windowInfos->decorated = decorated;

    // if the window is modal
    if(modal) gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    else gtk_window_set_modal(GTK_WINDOW(window), FALSE);
    windowInfos->modal = modal;

    // if the window is deletable
    if(deletable) gtk_window_set_deletable(GTK_WINDOW(window), TRUE);
    else gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
    windowInfos->deletable = deletable;

    // if the window is full screen
    if(full_Screen) gtk_window_fullscreen(GTK_WINDOW(window));
    else gtk_window_unfullscreen(GTK_WINDOW(window));

    windowInfos->full_Screen = full_Screen;

    // if the window has a background color
    if(background_Color){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *color = g_strdup_printf("window { background-color: %s; }", background_Color);
        gtk_css_provider_load_from_data(provider, color, -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context(window);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider);
        windowInfos->background_Color = background_Color;
    } else {
        windowInfos->background_Color = NULL;
    }

    if(background_Image){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *image = g_strdup_printf("window { background-image: url(\"%s\"); background-repeat: no-repeat; background-size: cover;}", background_Image);
        gtk_css_provider_load_from_data(provider, image, -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context(window);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider);
        windowInfos->background_Color = background_Image;
    } else {
        windowInfos->background_Image = NULL;
    }

    return windowInfos;
}

Window *New_Window_Default(char *id, bool main_Window){
    // check the id if it's null
    if(!id){
        printf("Id is required\n");
        return NULL;
    }

    return New_Window(id, NULL, 700, 500, NULL, 1,
                      main_Window, true, true, false,
                      true, false, NULL, NULL, window_center
    );
}

// Setters --------------------------------------------------------------------------------

void Window_Set_Id(Window *window, char *id){
    if(!id){
        printf("Id is required\n");
        return;
    }

    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Id function\n");
        return;
    }

    g_free(window->id);
    window->id = g_strdup(id);
}


void Window_Set_Title(Window *window, char *title){
    if(!window) return;

    g_free(window->title);
    if(title){
        window->title = g_strdup(title);
        gtk_window_set_title(GTK_WINDOW(window->window), title);
    } else {
        window->title = g_strdup("Default title");
        gtk_window_set_title(GTK_WINDOW(window->window), "Default Title");
    }
}


void Window_Set_Width(Window *window, int width){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Width function\n");
        return;
    }
    // if the window is not resizable, the width can't be changed
    if(!window->resizable){
        printf("The window is not resizable\n");
        return;
    }

    // if the width is not valide
    if(width < 0) width = 700;
    gtk_window_set_default_size(GTK_WINDOW(window->window), width, window->height);
    window->width = width;
}

void Window_Set_Height(Window *window, int height){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Height function\n");
        return;
    }

    // if the window is not resizable, the height can't be changed
    if(!window->resizable){
        printf("The window is not resizable\n");
        return;
    }

    // if the height is not valide
    if(height < 0) height = 500;
    gtk_window_set_default_size(GTK_WINDOW(window->window), window->width, height);
    window->height = height;
}

void Window_Set_Icon(Window *window, char *icon){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Icon function\n");
        return;
    }

    if(icon){
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon, NULL);
        if(pixbuf){
            gtk_window_set_icon(GTK_WINDOW(window->window), pixbuf);
            if(window->icon) g_free(window->icon);
            window->icon = g_strdup(icon);
            g_object_unref(pixbuf);
            return;
        } else {
            printf("Error: Icon not found\n");
            window->icon = NULL;
        }
    } else {
        window->icon = NULL;
    }
}


void Window_Set_Opacity(Window *window, double opacity){
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Opacity function\n");
        return;
    }

    // if the opacity is not valide
    if(opacity < 0 || opacity > 1) opacity = 1;
    gtk_widget_set_opacity(window->window, opacity);
    window->opacity = opacity;
}

void Window_Set_Resizable(Window *window, bool resizable){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Resizable function\n");
        return;
    }

    gtk_window_set_resizable(GTK_WINDOW(window->window), resizable);
    window->resizable = resizable;
}

void Window_Set_Decorated(Window *window, bool decorated){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Decorated function\n");
        return;
    }

    gtk_window_set_decorated(GTK_WINDOW(window->window), decorated);
    window->decorated = decorated;
}

void Window_Set_Modal(Window *window, bool modal){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Modal function\n");
        return;
    }

    gtk_window_set_modal(GTK_WINDOW(window->window), modal);
    window->modal = modal;
}

void Window_Set_Deletable(Window *window, bool deletable){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Deletable function\n");
        return;
    }

    gtk_window_set_deletable(GTK_WINDOW(window->window), deletable);
    window->deletable = deletable;
}

void Window_Set_Full_Screen(Window *window, bool full_Screen){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Full_Screen function\n");
        return;
    }
    if(full_Screen){
        gtk_window_fullscreen(GTK_WINDOW(window->window));
    } else {
        gtk_window_unfullscreen(GTK_WINDOW(window->window));
    }
}

void Window_Set_Background_Color(Window *window, char *background_Color){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Background_Color function\n");
        return;
    }

    if(background_Color){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *color = g_strdup_printf("window { background-color: %s; }", background_Color);
        gtk_css_provider_load_from_data(provider, color, -1, NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        g_free(color);
        g_object_unref(provider);
        if(window->background_Color) g_free(window->background_Color);
        window->background_Color = g_strdup(background_Color);
    } else {
        if(window->background_Color) g_free(window->background_Color);
        window->background_Color = NULL;
    }
}

void Window_Set_Background_Image(Window *window, char *background_Image){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Background_Image function\n");
        return;
    }

    if(background_Image){
        GtkCssProvider *provider = gtk_css_provider_new();
        char *image = g_strdup_printf("window { background-image: url(\"%s\"); background-repeat: no-repeat; background-size: cover;}", background_Image);
        gtk_css_provider_load_from_data(provider, image, -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context(window->window);
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        g_object_unref(provider);
        if(window->background_Image) g_free(window->background_Image);
        window->background_Image = g_strdup(background_Image);
    } else {
        if(window->background_Image) g_free(window->background_Image);
        window->background_Image = NULL;
    }
}

void Window_Set_Position(Window *window, Window_Position position){
    // if the window not exist
    if(!window){
        printf("Error: Passing a null pointer to Window_Set_Position function\n");
        return;
    }

    // check if the position is not valide
    if(position < 0 || position > 4) position = 1;

    gtk_window_set_position(GTK_WINDOW(window->window), position);
    window->position = position;
}



// getters ---------------------------------------------------------------------------------------------

char *Window_Get_Id(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Id function\n");
        return NULL;
    }
    return window->id;
}

char *Window_Get_Title(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Title function\n");
        return NULL;
    }
    return window->title;
}

int Window_Get_Width(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Width function\n");
        return -1;
    }
    return window->width;
}

int Window_Get_Height(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Height function\n");
        return -1;
    }
    return window->height;
}

char *Window_Get_Icon(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Icon function\n");
        return NULL;
    }
    return window->icon;
}

double Window_Get_Opacity(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Opacity function\n");
        return -1;
    }
    return window->opacity;
}

bool Window_Get_Deletable(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Deletable function\n");
        return -1;
    }
    return window->deletable;
}

bool Window_Get_Full_Screen(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Full_Screen function\n");
        return -1;
    }
    return window->full_Screen;
}

bool Window_Get_Resizable(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Resizable function\n");
        return -1;
    }
    return window->resizable;
}

bool Window_Get_Decorated(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Decorated function\n");
        return -1;
    }
    return window->decorated;
}
bool Window_Get_Modal(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Modal function\n");
        return -1;
    }
    return window->modal;
}


Window_Position Window_Get_Position(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Position function\n");
        return -1;
    }
    return window->position;
}

char *Window_Get_Background_Color(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Background_Color function\n");
        return NULL;
    }
    return window->background_Color;
}

char *Window_Get_Background_Image(Window *window){
    if(!window){
        printf("Error: Passing a null pointer to Window_Get_Background_Image function\n");
        return NULL;
    }
    return window->background_Image;
}




Widget *Window_Get_Widget(Window *window){
    return window->window;
}

void Window_Show(Window *window){
    gtk_widget_show_all(window->window);
}

void Window_Set_Header_Bar(Window *window, Header_Bar *header_bar){
if(!window){
        printf("Error: Passing a null pointer to Window_Set_Header_Bar function\n");
        return;
    }
    if(!header_bar){
        printf("Error: Passing a null pointer to Window_Set_Header_Bar function\n");
        return;
    }
    
    gtk_window_set_titlebar(GTK_WINDOW(window->window), Header_Bar_Get_Widget(header_bar));
}

void Window_Destroy(Window *window){
if(!window){
        printf("Error: Passing a null pointer to Window_Destroy function\n");
        return;
    }


    if(window->id) g_free(window->id);
    if(window->title) g_free(window->title);
    if(window->icon) g_free(window->icon);
    if(window->background_Color) g_free(window->background_Color);
    if(window->background_Image) g_free(window->background_Image);
    
    gtk_widget_destroy(window->window);
    g_free(window);

}

void Window_Set_Container(Window *window, Container *container){
    GtkWidget *_container = (GtkWidget *)container;
    gtk_container_add(GTK_CONTAINER(window->window), _container);
}

void Application_Start(void (*Start_Function)()){
    application = gtk_application_new("org.example.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(application, "activate", G_CALLBACK(Start_Function), NULL);
    int status = g_application_run(G_APPLICATION(application), 0, NULL);
    g_object_unref(application);
}


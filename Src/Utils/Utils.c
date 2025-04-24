/**********************************************************************************************************************
 * @file        : Widgets.c
 * 
 * @brief       : This file contains the implementation of the Utils functions in Utils.h.
 * 
 * 
 * @author      : Ayyoub El Kouri
 * @version     : 1
 * @date        : 25-03-2025
 * @last_Update : 25-03-2025
 **********************************************************************************************************************/

#include "../../Include/Utils/Utils.h"



bool Valide_Image_Path(char *image_Path){
    if(!image_Path) return false;

    // check if the image path exists
    if(!g_file_test(image_Path, G_FILE_TEST_EXISTS)) return false;

    // check if the image path is regular file
    if(!g_file_test(image_Path, G_FILE_TEST_IS_REGULAR)) return false;

    return true;
}

bool Valide_Pointer(void *pointer){
    // Check the pointer
    if(!pointer){
        g_warning("Invalid pointer\n");
        return false;
    } 
    return true;
}

#include "limpiarPantalla.h"

#ifdef _WIN32
    #include<windows.h>
#endif  

void limpiarPantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
// librerias
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct proyecto
{ 
    long long int codigo;
    string nombre;
    proyecto *der;  // variable derdor enlace
    proyecto *izq;  // variable derdor enlace
};

// bueno voy a suponer que me lee
// lo que hace esto es lit usar como un archivo en la nube pero yo ahora mismo no puedo ver sus cambios
// si ve esta linea que esta aca
//<----- esa amarilla, significa sus cambios

//para que yo pueda ver sus cambios tiene que hacer esto
// en la parte izquierda hay un icono que representa redes o un 

//ese es el apartado de changes, cambios pues

// en la parte de abajo sale el grafo que representan las ramas de los cambios que se an guardado y
// la que esta en azul seria la rama principal

//para tener mejor control de versiones yo voy a crear una rama

//click derecho a la posicion actual y le da a crear breanch osea la rama, le pone cualquier cosa y le da enter

//si se da cuenta el endpoint sale con el nombre de la rama
//eso significa que esa rama sale de la rama main

// ahora para publicar la rama y yo la pueda ver seria en message poner cualquier cosa
// y le da a commit que vendria siendo pedir peticion hacer peticion
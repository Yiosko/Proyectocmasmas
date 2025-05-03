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


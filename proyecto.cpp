// librerias
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Salon{
    int codigo;
    string materia;
    Salon* izq;
    Salon* der;
    Estudiante* abajo;
};

struct Estudiante{
    int codigo;
    string nombre;
    Estudiante* abajo1;
};

void menu1(void);
void menu2(void);
void menu3(void);
void ingresarSalon(void);
void ingresarEstudiante(void);
void mostrar(void); 
void sacarSalon(void);
void sacarEstudiante(void);
void modificarSalon(void);
void modificarEstudiante(void);


int main() {
    menu1();
}

void menu1(void){
    int opcion;
    do{
        cout<<"1. Menu del Salon"<<endl;
        cout<<"2. Menu de Estudiantes"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                menu2();
                break;
            case 2:
                menu3();
                break;
            
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 5);
}

void menu2(void){
    int opcion;
    do{
        cout<<"Menu del Salon/n"<<endl;
        cout<<"1. Ingresar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Sacar"<<endl;
        cout<<"4. Modificar"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                ingresarSalon();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                sacarSalon();
                break;
            case 4:
                modificarSalon();
                break;
            case 5:
                cout<<"Saliendo del programa..."<<endl;
                break;
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 5);
}

void menu3(void){
    int opcion;
    do{
        cout<<"Menu de Estudiantes/n"<<endl;
        cout<<"1. Ingresar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Sacar"<<endl;
        cout<<"4. Modificar"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                ingresarEstudiante();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                sacarEstudiante();
                break;
            case 4:
                modificarEstudiante();
                break;
            case 5:
                cout<<"Saliendo del programa..."<<endl;
                break;
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 5);
}

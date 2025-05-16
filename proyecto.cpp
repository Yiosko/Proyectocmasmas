// librerias
#include <string>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


struct Estudiante{
    int codigo;
    string nombre;
    float nota;
    struct Estudiante* abajo;  
};

struct Salon{
    int codigo;
    string materia;
    Salon* izq;
    Salon* der;
    struct Estudiante* abajo;
};


Salon* cab = NULL;

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
    cout << "Bienvenido al Sistema de Gestion de Salones y Estudiantes" << endl;
    cout << "-------------------------------------------------------" << endl << endl;
    menu1();
    return 0;
}

void menu1(void){
    int opcion;
    do{
        cout<<"1. Menu del Salon"<<endl;
        cout<<"2. Menu de Estudiantes"<<endl;
        cout<<"3. Para Cerrar el programa"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                menu2();
                break;
            case 2:
                menu3();
                break;
            case 3:
                cout<<"Saliendo del programa..."<<endl;
                break;
            
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 3);
}

void menu2(void){
    int opcion;
    do{
        cout<<"Menu del Salon\n"<<endl;
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
        cout<<"Menu de Estudiantes\n"<<endl;
        cout<<"1. Ingresar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Reporte de mejores y peores notas de los estudiantes"<<endl;
        cout<< "4. Mostrar salon con mejor promedio y sus estudiantes" << endl;
        cout<<"5. Sacar"<<endl;
        cout<<"6. Modificar"<<endl;
        cout<<"7. Salir"<<endl;
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
                reporteMejoresYPeores();
            break;
            case 4:
             mostrarSalonConMejorPromedio();
             break;
            case 5:
                sacarEstudiante();
                break;
            case 6:
                modificarEstudiante();
                break;
            case 7:
                cout<<"Saliendo del programa..."<<endl;
                break;
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 7);
}

void ingresarSalon() {
    Salon* nuevo = new Salon();
    cout << "Ingrese el codigo del salon: ";
    cin >> nuevo->codigo;
    cout << "Ingrese la materia: ";
    cin >> nuevo->materia;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->abajo = NULL;

    if (cab == NULL) {
        cab = nuevo;
    } else {
        Salon* actual = cab;
        Salon* anterior = NULL;
        while (actual != NULL && actual->codigo < nuevo->codigo) {
            anterior = actual;
            actual = actual->der;
        }
        if (anterior == NULL) {
            nuevo->der = cab;
            cab = nuevo;
        } else {
            anterior->der = nuevo;
            nuevo->der = actual;
        }
    }
    cout << "Salon agregado exitosamente!" << endl;
}

void ingresarEstudiante() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    int codigoSalon;
    cout << "Ingrese el codigo del salon: ";
    cin >> codigoSalon;

    Salon* salonActual = cab;
    while (salonActual != NULL && salonActual->codigo != codigoSalon) {
        salonActual = salonActual->der;
    }

    if (salonActual == NULL) {
        cout << "Salon no encontrado!" << endl;
        return;
    }

    Estudiante* nuevo = new Estudiante();
    cout << "Ingrese el codigo del estudiante: ";
    cin >> nuevo->codigo;
    cin.ignore(); // Limpiar buffer
    cout << "Ingrese el nombre del estudiante: ";
    std::getline(cin, nuevo->nombre);
    cout << "Ingrese la nota del estudiante: ";         
    cin >> nuevo->nota;

    nuevo->abajo = NULL;

    if (salonActual->abajo == NULL) {
        salonActual->abajo = nuevo;
    } else {
        Estudiante* actual = salonActual->abajo;
        while (actual->abajo != NULL) {
            actual = actual->abajo;
        }
        actual->abajo = nuevo;
    }
    cout << "Estudiante agregado exitosamente!" << endl;
}


void mostrar() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    Salon* salonActual = cab;
    while (salonActual != NULL) {
        cout << "\nSalon " << salonActual->codigo << " - " << salonActual->materia << endl;
        Estudiante* estudianteActual = salonActual->abajo;
        if (estudianteActual == NULL) {
            cout << "No hay estudiantes en este salon" << endl;
        }
        while (estudianteActual != NULL) {
            cout << "  Estudiante: " << estudianteActual->codigo << " - " << estudianteActual->nombre << endl;
            estudianteActual = estudianteActual->abajo;
        }
        salonActual = salonActual->der;
    }
}

void reporteMejoresYPeores() {
    if (cab == NULL) {
        cout << "No hay salones ni estudiantes registrados!" << endl;
        return;
    }

    // Inicializar
    Estudiante* mejores[2] = {NULL, NULL};
    Estudiante* peores[2] = {NULL, NULL};
    Salon* salonMejor[2] = {NULL, NULL};
    Salon* salonPeor[2] = {NULL, NULL};

    Salon* salonActual = cab;
    while (salonActual != NULL) {
        Estudiante* estudianteActual = salonActual->abajo;
        while (estudianteActual != NULL) {
            float nota = estudianteActual->nota;

            // Verificar mejores
            for (int i = 0; i < 2; ++i) {
                if (mejores[i] == NULL || nota > mejores[i]->nota) {
                    if (i == 1) {
                        mejores[1] = mejores[0];
                        salonMejor[1] = salonMejor[0];
                    }
                    mejores[0] = estudianteActual;
                    salonMejor[0] = salonActual;
                    break;
                }
            }

            // Verificar peores
            for (int i = 0; i < 2; ++i) {
                if (peores[i] == NULL || nota < peores[i]->nota) {
                    if (i == 1) {
                        peores[1] = peores[0];
                        salonPeor[1] = salonPeor[0];
                    }
                    peores[0] = estudianteActual;
                    salonPeor[0] = salonActual;
                    break;
                }
            }

            estudianteActual = estudianteActual->abajo;
        }
        salonActual = salonActual->der;
    }

    cout << "\n--- Reporte de Mejores Estudiantes ---" << endl;
    for (int i = 0; i < 2; ++i) {
        if (mejores[i]) {
            cout << "Estudiante: " << mejores[i]->nombre
                 << " | Nota: " << mejores[i]->nota
                 << " | Salon: " << salonMejor[i]->codigo
                 << " - " << salonMejor[i]->materia << endl;
        }
    }

    cout << "\n--- Reporte de Peores Estudiantes ---" << endl;
    for (int i = 0; i < 2; ++i) {
        if (peores[i]) {
            cout << "Estudiante: " << peores[i]->nombre
                 << " | Nota: " << peores[i]->nota
                 << " | Salon: " << salonPeor[i]->codigo
                 << " - " << salonPeor[i]->materia << endl;
        }
    }
}

void mostrarSalonConMejorPromedio() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    Salon* mejorSalon = NULL;
    float mejorPromedio = -1.0;

    Salon* salonActual = cab;

    while (salonActual != NULL) {
        Estudiante* estudianteActual = salonActual->abajo;
        int cantidad = 0;
        float sumaNotas = 0;

        while (estudianteActual != NULL) {
            sumaNotas += estudianteActual->nota;
            cantidad++;
            estudianteActual = estudianteActual->abajo;
        }

        if (cantidad > 0) {
            float promedio = sumaNotas / cantidad;
            if (promedio > mejorPromedio) {
                mejorPromedio = promedio;
                mejorSalon = salonActual;
            }
        }

        salonActual = salonActual->der;
    }

    if (mejorSalon != NULL) {
        cout << "\n--- Salon con el Mejor Promedio ---" << endl;
        cout << "Salon " << mejorSalon->codigo << " - " << mejorSalon->materia << endl;
        cout << "Promedio: " << mejorPromedio << endl;

        Estudiante* estudianteActual = mejorSalon->abajo;
        while (estudianteActual != NULL) {
            cout << "  Estudiante: " << estudianteActual->codigo
                 << " - " << estudianteActual->nombre
                 << " | Nota: " << estudianteActual->nota << endl;
            estudianteActual = estudianteActual->abajo;
        }
    } else {
        cout << "No hay estudiantes en los salones para calcular el promedio." << endl;
    }
}

void sacarSalon() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del salon a eliminar: ";
    cin >> codigo;

    Salon* actual = cab;
    Salon* anterior = NULL;

    while (actual != NULL && actual->codigo != codigo) {
        anterior = actual;
        actual = actual->der;
    }

    if (actual == NULL) {
        cout << "Salon no encontrado!" << endl;
        return;
    }

    if (anterior == NULL) {
        cab = actual->der;
    } else {
        anterior->der = actual->der;
    }

    delete actual;
    cout << "Salon eliminado exitosamente!" << endl;
}

void sacarEstudiante() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    int codigoSalon, codigoEstudiante;
    cout << "Ingrese el codigo del salon: ";
    cin >> codigoSalon;

    Salon* salonActual = cab;
    while (salonActual != NULL && salonActual->codigo != codigoSalon) {
        salonActual = salonActual->der;
    }

    if (salonActual == NULL) {
        cout << "Salon no encontrado!" << endl;
        return;
    }

    cout << "Ingrese el codigo del estudiante a eliminar: ";
    cin >> codigoEstudiante;

    Estudiante* actual = salonActual->abajo;
    Estudiante* anterior = NULL;

    while (actual != NULL && actual->codigo != codigoEstudiante) {
        anterior = actual;
        actual = actual->abajo;
    }

    if (actual == NULL) {
        cout << "Estudiante no encontrado!" << endl;
        return;
    }

    if (anterior == NULL) {
        salonActual->abajo = actual->abajo;
    } else {
        anterior->abajo = actual->abajo;
    }

    delete actual;
    cout << "Estudiante eliminado exitosamente!" << endl;
}

void modificarSalon() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del salon a modificar: ";
    cin >> codigo;

    Salon* actual = cab;
    while (actual != NULL && actual->codigo != codigo) {
        actual = actual->der;
    }

    if (actual == NULL) {
        cout << "Salon no encontrado!" << endl;
        return;
    }

    cout << "Ingrese la nueva materia: ";
    cin >> actual->materia;
    cout << "Salon modificado exitosamente!" << endl;
}

void modificarEstudiante() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        return;
    }

    int codigoSalon, codigoEstudiante;
    cout << "Ingrese el codigo del salon: ";
    cin >> codigoSalon;

    Salon* salonActual = cab;
    while (salonActual != NULL && salonActual->codigo != codigoSalon) {
        salonActual = salonActual->der;
    }

    if (salonActual == NULL) {
        cout << "Salon no encontrado!" << endl;
        return;
    }

    cout << "Ingrese el codigo del estudiante a modificar: ";
    cin >> codigoEstudiante;

    Estudiante* actual = salonActual->abajo;
    while (actual != NULL && actual->codigo != codigoEstudiante) {
        actual = actual->abajo;
    }

    if (actual == NULL) {
        cout << "Estudiante no encontrado!" << endl;
        return;
    }

    cout << "Ingrese el nuevo nombre del estudiante: ";
    cin >> actual->nombre;
    cout << "Estudiante modificado exitosamente!" << endl;
}

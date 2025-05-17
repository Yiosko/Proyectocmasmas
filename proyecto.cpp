// librerias
#include <string>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std; // para usar cout y cin sin std::


struct Estudiante{ // Definicion de la estructura Estudiante
    int codigo; // codigo del estudiante
    string nombre; // nombre del estudiante
    float nota; // nota del estudiante
    struct Estudiante* abajo;  // puntero al siguiente estudiante
};

struct Salon{
    int codigo; // codigo del salon
    string materia; // materia del salon
    Salon* izq; // puntero al salon anterior
    Salon* der; // puntero al siguiente salon
    struct Estudiante* abajo; // puntero al primer estudiante del salon
};


Salon* cab = NULL; // puntero al primer salon

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
void reporteMejoresYPeores(void);
void mostrarSalonConMejorPromedio(void);
// Prototipos de funciones


int main() {
    cout << "Bienvenido al Sistema de Gestion de Salones y Estudiantes" << endl; // Mensaje de bienvenida simplemente estetico
    cout << "-------------------------------------------------------" << endl << endl; // Divisor
    menu1(); // Llamada al menu principal
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
                break;
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
                cout<<"Saliendo del Menu..."<<endl;
                cout << "-------------------------------------------------------" << endl << endl; 
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
                cout<<"Saliendo del Menu..."<<endl;
                cout << "-------------------------------------------------------" << endl << endl; 
                break;
            default:
                cout<<"Opcion no valida, intente de nuevo."<<endl;
        }
    }while(opcion != 7);
}

bool codigoSalonExiste(int codigo) { // verifica si el codigo del salon ya existe
    Salon* actual = cab;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return true;
        }
        actual = actual->der;
    }
    return false;
}

bool codigoEstudianteExiste(Salon* salon, int codigo) {
    Estudiante* actual = salon->abajo;
    while (actual != NULL) {
        if (actual->codigo == codigo) {
            return true;
        }
        actual = actual->abajo;
    }
    return false;
}

void ingresarSalon() {
    int codigo;
    cout << "Ingrese el codigo del salon: ";
    cin >> codigo;
    
    if (codigoSalonExiste(codigo)) {
        cout << "Error: Ya existe un salon con ese codigo!" << endl;
        cout << "Presione cualquier tecla para continuar...";
        getch();
        return;
    }

    Salon* nuevo = new Salon();
    nuevo->codigo = codigo;
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

void limpiarPantalla() {
    system("cls"); // Limpiar la pantalla
}

void ingresarEstudiante() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl;
        cout << "Presione cualquier tecla para continuar...";
        getch(); // Esperar a que el usuario presione una tecla
        limpiarPantalla();
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
        cout << "Presione cualquier tecla para continuar...";
        getch();
        limpiarPantalla();
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del estudiante: ";
    cin >> codigo;
    
    if (codigoEstudianteExiste(salonActual, codigo)) {
        cout << "Error: Ya existe un estudiante con ese codigo en este salon!" << endl;
        cout << "Presione cualquier tecla para continuar...";
        getch();
        return;
    }

    Estudiante* nuevo = new Estudiante();
    nuevo->codigo = codigo;
    cin.ignore(32767, '\n'); // Limpiar el buffer completamente
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, nuevo->nombre); // Usar getline para permitir espacios en el nombre
    do {
        cout << "Ingrese la nota del estudiante (0-5): ";         
        cin >> nuevo->nota; // Validar que la nota esté entre 0 y 5
    } while(nuevo->nota < 0 || nuevo->nota > 5);

    nuevo->abajo = NULL; // Inicializar el puntero abajo a NULL

    if (salonActual->abajo == NULL) {
        salonActual->abajo = nuevo; // Primer estudiante
    } else {
        Estudiante* actual = salonActual->abajo; // Buscar el último estudiante
        while (actual->abajo != NULL) { // Recorrer la lista hasta el final
            actual = actual->abajo; // Mover al siguiente estudiante
        }
        actual->abajo = nuevo; // Agregar el nuevo estudiante al final
    }
    cout << "Estudiante agregado exitosamente!" << endl;
}


void mostrar() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl; // Mensaje de error si no hay salones
        return;
    }

    Salon* salonActual = cab; // Inicializar el puntero al primer salon
    while (salonActual != NULL) {
        cout << "\nSalon " << salonActual->codigo << " - " << salonActual->materia << endl; // Mostrar el salon actual 
        Estudiante* estudianteActual = salonActual->abajo; // Inicializar el puntero al primer estudiante
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
        cout << "No hay salones ni estudiantes registrados!" << endl; // Mensaje de error si no hay salones ni estudiantes
        return;
    }

    // Inicializar
    Estudiante* mejores[2] = {NULL, NULL}; // Esto es un arreglo de punteros a Estudiante funciona como una lista que guarda los mejores estudiantes 
    Estudiante* peores[2] = {NULL, NULL}; // Peores estudiantes
    Salon* salonMejor[2] = {NULL, NULL}; // Salones de los mejores estudiantes 
    Salon* salonPeor[2] = {NULL, NULL}; // Salones de los peores estudiantes

    Salon* salonActual = cab; // Inicializar el puntero al primer salon
    while (salonActual != NULL) { // Recorrer la lista de salones hasta el final
        Estudiante* estudianteActual = salonActual->abajo; // Inicializar el puntero al primer estudiante y mover al siguiente salon
        while (estudianteActual != NULL) { // Recorrer la lista de estudiantes hasta el final
            float nota = estudianteActual->nota; // Obtener la nota del estudiante 

            // Verificar mejores
            if (mejores[0] == NULL || nota > mejores[0]->nota) { // Si es el mejor estudiante o no hay estudiantes entonces lo guardamos
                mejores[1] = mejores[0]; // apunta al mejor estudiante
                salonMejor[1] = salonMejor[0]; // apunta al salon del mejor estudiante
                mejores[0] = estudianteActual; // Guardamos el mejor estudiante actual
                salonMejor[0] = salonActual;  // Guardamos el salon del mejor estudiante
            } else if (mejores[1] == NULL || nota > mejores[1]->nota) { // Si no es el mejor estudiante pero es el segundo mejor lo guardamos
                mejores[1] = estudianteActual; // Guardamos el segundo mejor estudiante
                salonMejor[1] = salonActual; // Guardamos el salon del segundo mejor estudiante
            }

            // Verificar peores
            if (peores[0] == NULL || nota < peores[0]->nota) { // Si es el peor estudiante o no hay estudiantes entonces lo guardamos
                peores[1] = peores[0]; // apunta al peor estudiante
                salonPeor[1] = salonPeor[0]; // apunta al salon del peor estudiante
                peores[0] = estudianteActual; // Guardamos el peor estudiante actual
                salonPeor[0] = salonActual; // Guardamos el salon del peor estudiante
            } else if (peores[1] == NULL || nota < peores[1]->nota) {
                peores[1] = estudianteActual; // Guardamos el segundo peor estudiante
                salonPeor[1] = salonActual; // Guardamos el salon del segundo peor estudiante
            }

            estudianteActual = estudianteActual->abajo; // Mover al siguiente estudiante
        }
        salonActual = salonActual->der; // Mover al siguiente salon
    }

    cout << "\n--- Reporte de Mejores Estudiantes ---" << endl; // Mostrar los mejores estudiantes
    for (int i = 0; i < 2; ++i) {
        if (mejores[i]) {
            cout << "Estudiante: " << mejores[i]->nombre
                 << " | Nota: " << mejores[i]->nota
                 << " | Salon: " << salonMejor[i]->codigo
                 << " - " << salonMejor[i]->materia << endl; // Mostrar el mejor estudiante
        }
    }

    cout << "\n--- Reporte de Peores Estudiantes ---" << endl;
    for (int i = 0; i < 2; ++i) {
        if (peores[i]) {
            cout << "Estudiante: " << peores[i]->nombre
                 << " | Nota: " << peores[i]->nota
                 << " | Salon: " << salonPeor[i]->codigo
                 << " - " << salonPeor[i]->materia << endl; // Mostrar el peor estudiante
        }
    }
}

void mostrarSalonConMejorPromedio() {
    if (cab == NULL) {
        cout << "No hay salones registrados!" << endl; // si no hay salones registrados
        return;
    }

    Salon* mejorSalon = NULL; // puntero al mejor salon
    float mejorPromedio = -1.0; // Inicializar el mejor promedio a un valor bajo

    Salon* salonActual = cab; // Inicializar el puntero al primer salon

    while (salonActual != NULL) { // Recorrer la lista de salones hasta el final
        Estudiante* estudianteActual = salonActual->abajo; // Inicializar el puntero al primer estudiante
        int cantidad = 0; // Contador de estudiantes
        float sumaNotas = 0; // Sumar las notas de los estudiantes

        while (estudianteActual != NULL) { // Recorrer la lista de estudiantes hasta el final
            sumaNotas += estudianteActual->nota; // Sumar la nota del estudiante
            cantidad++; // Incrementar el contador de estudiantes
            estudianteActual = estudianteActual->abajo; // Mover al siguiente estudiante
        }

        if (cantidad > 0) { // Si hay estudiantes en el salon
            float promedio = sumaNotas / cantidad; // Calcular el promedio
            if (promedio > mejorPromedio) { // Si el promedio es mejor que el mejor promedio existente
                mejorPromedio = promedio; // Actualizar el mejor promedio
                mejorSalon = salonActual; // Actualizar el mejor salon
            }
        }

        salonActual = salonActual->der; // Mover al siguiente salon
    }

    if (mejorSalon != NULL) { // Si se encontró un mejor salon
        cout << "\n--- Salon con el Mejor Promedio ---" << endl;
        cout << "Salon " << mejorSalon->codigo << " - " << mejorSalon->materia << endl;
        cout << "Promedio: " << mejorPromedio << endl;

        Estudiante* estudianteActual = mejorSalon->abajo; // Inicializar el puntero al primer estudiante
        while (estudianteActual != NULL) { // Recorrer la lista de estudiantes hasta el final
            cout << "  Estudiante: " << estudianteActual->codigo
                 << " - " << estudianteActual->nombre
                 << " | Nota: " << estudianteActual->nota << endl; // Mostrar el estudiante
            estudianteActual = estudianteActual->abajo; // Mover al siguiente estudiante
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
        cout << "Presione cualquier tecla para continuar...";
        getch();
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
        cout << "Presione cualquier tecla para continuar...";
        getch();
        return;
    }

    int codigoEstudiante;
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
        cout << "Presione cualquier tecla para continuar...";
        getch();
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
        cout << "Presione cualquier tecla para continuar...";
        getch();
        return;
    }

    int codigoEstudiante;
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

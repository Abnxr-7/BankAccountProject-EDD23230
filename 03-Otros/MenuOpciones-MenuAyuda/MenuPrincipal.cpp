#include <iostream>
#include <cstdlib>

using namespace std;

void mostrarMenuPrincipal() {
    system("cls");
    cout << "=== MENU PRINCIPAL ===\n";
    cout << "1. Instalar con clave de producto\n";
    cout << "2. Realizar Backup\n";
    cout << "3. Restaurar Backup\n";
    cout << "4. Ayuda Tecnica (ver libros)\n";
    cout << "5. Cifrar datos\n";
    cout << "6. Descifrar archivo\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Instalador con clave ejecutado...\n";
                system("pause");
                break;
            case 2:
                cout << "Backup realizado...\n";
                system("pause");
                break;
            case 3:
                cout << "Restaurando datos...\n";
                system("pause");
                break;
            case 4:
                // Aquí se llama al programa de ayuda técnica
                system("AyudaLibros.exe");
                break;
            case 5:
                cout << "Cifrado ejecutado...\n";
                system("pause");
                break;
            case 6:
                cout << "Descifrado ejecutado...\n";
                system("pause");
                break;
            case 7:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }
    } while (opcion != 7);

    return 0;
}

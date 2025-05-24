#include <iostream>
#include <conio.h> // para getch()
#include <windows.h> // para SetConsoleTextAttribute y manejo de color

using namespace std;

void printMenu(int selected) {
    system("cls"); // limpiar pantalla
    const char* options[] = {
        "Opcion 1",
        "Opcion 2",
        "Opcion 3",
        "Salir"
    };
    int nOptions = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < nOptions; i++) {
        if (i == selected) {
            // Cambiar color o indicar selección
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // fondo azul, texto blanco
            cout << "> " << options[i] << "\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // resetear color
        } else {
            cout << "  " << options[i] << "\n";
        }
    }
}

int main() {
    int selected = 0;
    int nOptions = 4;
    while (true) {
        printMenu(selected);

        int key = _getch();

        if (key == 224) {  // Teclas especiales (flechas, etc)
            key = _getch(); // leer código real de la tecla

            if (key == 72) { // flecha arriba
                selected--;
                if (selected < 0) selected = nOptions - 1;
            } else if (key == 80) { // flecha abajo
                selected++;
                if (selected >= nOptions) selected = 0;
            }
        } else if (key == 13) { // Enter
            // acción según opción seleccionada
            if (selected == nOptions - 1) {
                cout << "Saliendo...\n";
                break;
            } else {
                cout << "Seleccionaste: Opcion " << selected + 1 << "\n";
                system("pause");
            }
        }
    }
    return 0;
}

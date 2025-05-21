#include <iostream>
#include <string>
#include "CuentaAhorros.h"
#include "CuentaCorriente.h" 
#include "Persona.h"

#include <conio.h> // getch()
#include <windows.h> // SetConsoleCursorPosition

using namespace std;
// Menu de prueba para comprobar la correcta compilacion
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void mostrarMenu(int seleccion, string opciones[], int numOpciones) {
	system("cls");
	for (int i = 0; i < numOpciones; i++) {
		if (i == seleccion)
			cout << " > " << opciones[i] << endl;
		else
			cout << "   " << opciones[i] << endl;
	}
}

int main() {
	string opciones[] = { "Opcion 1", "Opcion 2", "Opcion 3", "Salir" };
	int numOpciones = sizeof(opciones) / sizeof(opciones[0]);
	int seleccion = 0;

	while (true) {
		mostrarMenu(seleccion, opciones, numOpciones);
		int tecla = _getch(); // Captura sin necesidad de presionar ENTER

		if (tecla == 224) { // Teclas especiales (flechas)
			tecla = _getch();
			if (tecla == 72) // Flecha arriba
				seleccion = (seleccion - 1 + numOpciones) % numOpciones;
			else if (tecla == 80) // Flecha abajo
				seleccion = (seleccion + 1) % numOpciones;
		}
		else if (tecla == 13) { // ENTER
			system("cls");
			cout << "Has seleccionado: " << opciones[seleccion] << endl;
			if (opciones[seleccion] == "Salir") break;
			system("pause");
		}
		else if (tecla == 27) { // ESC
			cout << "Saliendo con ESC..." << endl;
			break;
		}
	}

	return 0;
}

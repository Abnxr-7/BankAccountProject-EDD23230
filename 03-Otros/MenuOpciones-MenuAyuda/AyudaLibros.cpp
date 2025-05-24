#include <iostream>
#include <conio.h>  // Para getch en Windows
#include <vector>
#include <string>

using namespace std;

// Constantes para las teclas
const int TECLA_ARRIBA = 72;
const int TECLA_ABAJO = 80;
const int TECLA_ENTER = 13;

// Libros simulados con título y contenido
struct Libro {
    string titulo;
    vector<string> contenido;
};

void mostrarMenuAyuda(const vector<Libro>& libros, int opcionSeleccionada) {
    system("cls");
    cout << "=== MENU DE AYUDA TECNICA ===\n\n";
    cout << "Usa las flechas ARRIBA y ABAJO para navegar. ENTER para seleccionar.\n\n";
    for (int i = 0; i < (int)libros.size(); i++) {
        if (i == opcionSeleccionada) {
            // Opción seleccionada resaltada
            cout << "> >> " << libros[i].titulo << " <<\n";
        } else {
            cout << "  " << libros[i].titulo << endl;
        }
    }
}

void mostrarContenidoLibro(const Libro& libro) {
    system("cls");
    cout << "=== " << libro.titulo << " ===\n\n";

    for (const auto& linea : libro.contenido) {
        cout << linea << endl;
    }

    cout << "\nPresiona cualquier tecla para volver al menu de ayuda...";
    getch();
}

int main() {
    // Simular algunos libros de ayuda con contenido
    vector<Libro> libros = {
        {
            "README.txt",
            {
                "Este es el archivo README del programa.",
                "Contiene instrucciones sobre la instalacion y uso.",
                "Version: 1.0.0",
                "Autor: Tu Nombre"
            }
        },
        {
            "about.txt",
            {
                "Acerca de este programa:",
                "El programa permite gestionar backups, cifrado y restauracion.",
                "Desarrollado para facilitar la gestion de datos de forma segura."
            }
        },
        {
            "Manual de Backup",
            {
                "Para hacer un backup, selecciona la opcion 'Realizar Backup' en el menu principal.",
                "El sistema guardara tus datos en un archivo seguro.",
                "Puedes restaurar backups desde el menu 'Restaurar Backup'."
            }
        }
    };

    int opcionSeleccionada = 0;
    int numLibros = (int)libros.size();
    int tecla;

    while (true) {
        mostrarMenuAyuda(libros, opcionSeleccionada);

        tecla = getch();

        // Las flechas son códigos extendidos; la primera llamada a getch() devuelve 224
        if (tecla == 224) {
            tecla = getch(); // Segundo código de la flecha
            if (tecla == TECLA_ARRIBA) {
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) {
                    opcionSeleccionada = numLibros - 1;
                }
            } else if (tecla == TECLA_ABAJO) {
                opcionSeleccionada++;
                if (opcionSeleccionada >= numLibros) {
                    opcionSeleccionada = 0;
                }
            }
        } else if (tecla == TECLA_ENTER) {
            mostrarContenidoLibro(libros[opcionSeleccionada]);
        }
    }

    return 0;
}

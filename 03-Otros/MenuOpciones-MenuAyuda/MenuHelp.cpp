#include <iostream>
#include <conio.h>  // Solo en Windows
#include <vector>
#include <string>

using namespace std;

const int TECLA_ARRIBA = 72;
const int TECLA_ABAJO = 80;
const int TECLA_ENTER = 13;

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

        if (tecla == 224) {
            tecla = getch();
            if (tecla == TECLA_ARRIBA) {
                opcionSeleccionada = (opcionSeleccionada - 1 + numLibros) % numLibros;
            } else if (tecla == TECLA_ABAJO) {
                opcionSeleccionada = (opcionSeleccionada + 1) % numLibros;
            }
        } else if (tecla == TECLA_ENTER) {
            mostrarContenidoLibro(libros[opcionSeleccionada]);
        }
    }

    return 0;
}

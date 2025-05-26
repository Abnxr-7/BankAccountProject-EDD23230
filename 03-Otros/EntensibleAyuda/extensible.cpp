#include <iostream>
#include <windows.h>
#include <string>

const int MENU_X1 = 5;
const int MENU_X2 = 20;
const int MENU_Y1 = 5;
const int MENU_Y2 = 8;
const int MESSAGE_Y = 10;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clearRegion(int x1, int y1, int x2, int y2) {
    for (int y = y1; y <= y2; ++y) {
        gotoxy(x1, y);
        for (int x = x1; x <= x2; ++x) {
            std::cout << " ";
        }
    }
}

void displayMenu() {
    gotoxy(MENU_X1, MENU_Y1);
    std::cout << "-----------------";
    gotoxy(MENU_X1, MENU_Y1 + 1);
    std::cout << "|     MENU      |";
    gotoxy(MENU_X1, MENU_Y1 + 2);
    std::cout << "|   (Haz click) |";
    gotoxy(MENU_X1, MENU_Y1 + 3);
    std::cout << "-----------------";
}

void displayMessage(const std::string& message) {
    clearRegion(0, MESSAGE_Y, 79, MESSAGE_Y);
    gotoxy(0, MESSAGE_Y);
    std::cout << message;
}

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    if (hInput == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al obtener el handle de entrada de la consola." << std::endl;
        return 1;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hInput, &dwMode)) {
        std::cerr << "Error al obtener el modo de la consola." << std::endl;
        return 1;
    }
    dwMode |= ENABLE_MOUSE_INPUT;
    dwMode &= ~ENABLE_QUICK_EDIT_MODE;
    if (!SetConsoleMode(hInput, dwMode)) {
        std::cerr << "Error al establecer el modo de la consola." << std::endl;
        return 1;
    }

    hideCursor();
    system("cls");

    displayMenu();
    displayMessage("Haz click en el cuadrado del MENU para ver las opciones.");
    gotoxy(0, 12);
    std::cout << "Presiona 'ESC' para salir.";

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    bool bExit = false;

    while (!bExit) {
        if (!ReadConsoleInput(hInput, irInBuf, 128, &cNumRead)) {
            std::cerr << "Error al leer la entrada de la consola." << std::endl;
            break;
        }

        for (DWORD i = 0; i < cNumRead; ++i) {
            switch (irInBuf[i].EventType) {
                case MOUSE_EVENT: {
                    MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
                    if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                        int mouseX = mer.dwMousePosition.X;
                        int mouseY = mer.dwMousePosition.Y;

                        if (mouseX >= MENU_X1 && mouseX <= MENU_X2 && mouseY >= MENU_Y1 && mouseY <= MENU_Y2) {
                            clearRegion(0, MESSAGE_Y, 79, MESSAGE_Y);
                            gotoxy(25, 6);
                            std::cout << "Opciones del Menu:";
                            gotoxy(25, 7);
                            std::cout << "1. Opcion A";
                            gotoxy(25, 8);
                            std::cout << "2. Opcion B";
                            gotoxy(25, 9);
                            std::cout << "3. Opcion C";
                            gotoxy(25, 11);
                            std::cout << "Selecciona una opcion (1-3) o presiona ESC para volver.";

                            bool menuActive = true;
                            while (menuActive) {
                                if (!ReadConsoleInput(hInput, irInBuf, 128, &cNumRead)) {
                                    std::cerr << "Error al leer la entrada del menu." << std::endl;
                                    break;
                                }
                                for (DWORD j = 0; j < cNumRead; ++j) {
                                    if (irInBuf[j].EventType == KEY_EVENT && irInBuf[j].Event.KeyEvent.bKeyDown) {
                                        WORD vkCode = irInBuf[j].Event.KeyEvent.wVirtualKeyCode;
                                        if (vkCode == '1') {
                                            clearRegion(25, 6, 79, 11);
                                            gotoxy(25, 6);
                                            std::cout << "Seleccionaste: Opcion A";
                                            menuActive = false;
                                        } else if (vkCode == '2') {
                                            clearRegion(25, 6, 79, 11);
                                            gotoxy(25, 6);
                                            std::cout << "Seleccionaste: Opcion B";
                                            menuActive = false;
                                        } else if (vkCode == '3') {
                                            clearRegion(25, 6, 79, 11);
                                            gotoxy(25, 6);
                                            std::cout << "Seleccionaste: Opcion C";
                                            menuActive = false;
                                        } else if (vkCode == VK_ESCAPE) {
                                            clearRegion(25, 6, 79, 11);
                                            menuActive = false;
                                        }
                                    }
                                }
                            }
                            displayMessage("Haz click en el cuadrado del MENU para ver las opciones.");
                        }
                    }
                    break;
                }
                case KEY_EVENT: {
                    KEY_EVENT_RECORD ker = irInBuf[i].Event.KeyEvent;
                    if (ker.bKeyDown && ker.wVirtualKeyCode == VK_ESCAPE) {
                        bExit = true;
                    }
                    break;
                }
            }
        }
    }

    showCursor();
    SetConsoleMode(hInput, dwMode | ENABLE_QUICK_EDIT_MODE);
    system("cls");
    gotoxy(0, 0);
    std::cout << "Saliendo de la aplicacion. ¡Adios!" << std::endl;

    return 0;
}

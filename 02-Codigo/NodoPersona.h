#pragma once
#ifndef NODOPERSONA_H
#define NODOPERSONA_H

// Declaracion forward en lugar de incluir el archivo completo
class Persona;

/**
 * @class NodoPersona
 * @brief Nodo para una lista enlazada de personas.
 *
 * Cada nodo contiene un puntero a un objeto Persona y un puntero al siguiente nodo.
 */
class NodoPersona {
public:
    Persona* persona;           ///< Puntero al objeto Persona.
    NodoPersona* siguiente;     ///< Puntero al siguiente nodo en la lista.

    /**
     * @brief Constructor que toma un puntero a Persona.
     * @param p Puntero a un objeto Persona.
     */
    NodoPersona(Persona* p) : persona(p), siguiente(nullptr) {}

    /**
     * @brief Destructor. No elimina el objeto Persona, solo limpia los punteros.
     */
    ~NodoPersona() {
        // No delete persona - lo maneja quien creo la persona
        persona = nullptr;
        siguiente = nullptr;
    }
};

#endif // NODOPERSONA_H
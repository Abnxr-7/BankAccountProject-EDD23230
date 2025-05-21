#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include "Persona.h"

class Banco {
private:
    std::vector<Persona> listaPersonas;

public:
    Banco();

    std::vector<Persona> getListaPersonas() const;

    void setListaPersonas(const std::vector<Persona>& newListaPersonas);
};

#endif

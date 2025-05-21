#include "Banco.h"

Banco::Banco() {}

std::vector<Persona> Banco::getListaPersonas() const {
    return listaPersonas;
}

void Banco::setListaPersonas(const std::vector<Persona>& newListaPersonas) {
    listaPersonas = newListaPersonas;
}


#pragma once
// NodoCuentaCorriente.h

#ifndef NODO_CUENTA_CORRIENTE_H
#define NODO_CUENTA_CORRIENTE_H

// Declaración de la plantilla NodoCuentaCorriente
template <typename T>
struct NodoCuentaCorriente {
	T numeroCuenta;
	NodoCuentaCorriente* siguiente;
	NodoCuentaCorriente* anterior;
	
	NodoCuentaCorriente(T num) : numeroCuenta(num), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODO_CUENTA_CORRIENTE_H

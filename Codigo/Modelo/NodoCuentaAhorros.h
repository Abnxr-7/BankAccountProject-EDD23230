#pragma once
// NodoCuentaAhorros.h

#ifndef NODO_CUENTA_AHORROS_H
#define NODO_CUENTA_AHORROS_H

// Nodo para lista doblemente enlazada de cuentas
template <typename T>
struct NodoCuentaAhorros {
	T numeroCuenta;
	NodoCuentaAhorros* siguiente;
	NodoCuentaAhorros* anterior;

	NodoCuentaAhorros(T num) : numeroCuenta(num), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODO_CUENTA_AHORROS_H

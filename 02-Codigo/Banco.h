#pragma once
#ifndef BANCO_H
#define BANCO_H

#include "Persona.h"
#include "NodoPersona.h"
#include <Shlobj.h>  // Para SHGetKnownFolderPath
#include <comdef.h>  // Para _bstr_t
#include <KnownFolders.h> // Para FOLDERID_Desktop
#pragma comment(lib, "shell32.lib")  // Enlazar con shell32.lib

/**
 * @class Banco
 * @brief Clase principal para la gestión de personas y cuentas bancarias.
 */
class Banco {
private:
    NodoPersona* listaPersonas; ///< Lista enlazada de personas

public:
    /**
     * @brief Constructor por defecto de la clase Banco.
     */
    Banco();

    /**
     * @brief Destructor de la clase Banco.
     */
    ~Banco();

    /**
     * @brief Obtiene la lista enlazada de personas.
     * @return Puntero al primer nodo de la lista de personas.
     */
    NodoPersona* getListaPersonas() const { return listaPersonas; }

    /**
     * @brief Establece la lista enlazada de personas.
     * @param nuevaLista Puntero al nuevo primer nodo de la lista.
     */
    void setListaPersonas(NodoPersona* nuevaLista){listaPersonas = nuevaLista}

    /**
     * @brief Agrega una persona con cuenta al banco.
     */
    void agregarPersonaConCuenta();

    /**
     * @brief Guarda las cuentas en un archivo especificado.
     * @param nombreArchivo Nombre del archivo donde se guardarán las cuentas.
     */
    void guardarCuentasEnArchivo(const std::string& nombreArchivo) const;

    /**
     * @brief Guarda las cuentas en un archivo con nombre por defecto.
     */
    void guardarCuentasEnArchivo();

    /**
     * @brief Carga las cuentas desde un archivo.
     * @param nombreArchivo Nombre del archivo desde el cual se cargarán las cuentas.
     */
    void cargarCuentasDesdeArchivo(const std::string& nombreArchivo);

    /**
     * @brief Busca cuentas en el banco.
     */
    void buscarCuenta();

    /**
     * @brief Busca cuentas por fecha de apertura.
     * @param fecha Fecha de apertura a buscar.
     */
    void buscarCuentasPorFecha(const std::string& fecha) const;

    /**
     * @brief Busca cuentas por un criterio específico.
     */
    void buscarCuentasPorCriterio();

    /**
     * @brief Realiza una transferencia entre cuentas.
     */
    void realizarTransferencia();

    /**
     * @brief Formatea un valor en centavos con comas.
     * @param valorEnCentavos Valor a formatear.
     * @return Cadena formateada con comas.
     */
    std::string formatearConComas(double valorEnCentavos) const;

    /**
     * @brief Elimina una cuenta por cédula.
     * @param cedula Cédula de la persona cuya cuenta se eliminará.
     */
    void eliminarCuentaPorCedula(const std::string& cedula);

    /**
     * @brief Elimina una cuenta por número de cuenta.
     * @param numeroCuenta Número de cuenta a eliminar.
     */
    void eliminarCuentaPorNumCuenta(const std::string& numeroCuenta);

    /**
     * @brief Obtiene la ruta del escritorio del usuario.
     * @return Ruta del escritorio como cadena.
     */
    std::string obtenerRutaEscritorio() const;
};

#endif // BANCO_H
#pragma once
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <windows.h>
#include <mutex>

/**
 * @struct ElementoMarquesina
 * @brief Representa un elemento de la marquesina con texto y formato.
 */
struct ElementoMarquesina {
    std::string texto;    ///< Texto a mostrar en la marquesina.
    int colorTexto;       ///< Código de color del texto.
    int colorFondo;       ///< Código de color del fondo.
    bool negrita;         ///< Indica si el texto es negrita.
};

/**
 * @class Marquesina
 * @brief Clase para gestionar y mostrar una marquesina animada en consola, con soporte para HTML simple y control de concurrencia.
 */
class Marquesina {
private:
    std::vector<ElementoMarquesina> elementos; ///< Elementos a mostrar en la marquesina.
    std::thread hiloMarquesina;                ///< Hilo de ejecución de la marquesina.
    std::atomic<bool> ejecutando;              ///< Indica si la marquesina está en ejecución.
    std::atomic<bool> pausado;                 ///< Indica si la marquesina está pausada.
    std::atomic<bool> bloqueado;               ///< Indica si la marquesina está temporalmente bloqueada.
    std::atomic<bool> operacionCritica;        ///< Indica si hay una operación crítica de cursor.
    int posX, posY;                            ///< Posición X e Y de la marquesina en consola.
    int ancho;                                 ///< Ancho de la marquesina.
    int velocidad;                             ///< Velocidad de desplazamiento.
    std::string archivoHTML;                   ///< Ruta del archivo HTML de la marquesina.
    std::mutex mtx;                            ///< Mutex para sincronización general.
    std::mutex mtxPantalla;                    ///< Mutex para sincronización de pantalla.

    std::string bufferMarquesina;              ///< Buffer interno para evitar interferencias.
    std::atomic<bool> bufferActualizado;       ///< Indica si el buffer fue actualizado.

    /**
     * @brief Lee y parsea el archivo HTML simple.
     */
    void cargarDesdeHTML();

    /**
     * @brief Ejecuta el hilo de la marquesina.
     */
    void ejecutarMarquesina();

    /**
     * @brief Analiza etiquetas simples de HTML y genera los elementos de la marquesina.
     * @param contenido Contenido HTML a analizar.
     * @return Vector de elementos de la marquesina.
     */
    std::vector<ElementoMarquesina> parsearHTML(const std::string& contenido);

    FILETIME ultimaModificacion; ///< Última fecha de modificación del archivo HTML.

    /**
     * @brief Verifica si el archivo HTML fue modificado.
     * @return true si el archivo fue modificado, false en caso contrario.
     */
    bool archivoModificado();

    /**
     * @brief Verifica si es seguro escribir en una fila específica.
     * @param fila Número de fila a verificar.
     * @return true si es seguro, false en caso contrario.
     */
    bool esSafeZone(int fila) const;

    /**
     * @brief Actualiza el buffer interno de la marquesina.
     */
    void actualizarBuffer();

    /**
     * @brief Renderiza la marquesina en consola.
     */
    void renderizarMarquesina();

public:
    /**
     * @brief Constructor de la clase Marquesina.
     * @param x Posición X en consola.
     * @param y Posición Y en consola.
     * @param ancho Ancho de la marquesina.
     * @param archivoHTML Ruta del archivo HTML.
     * @param velocidad Velocidad de desplazamiento (por defecto 100).
     */
    Marquesina(int x, int y, int ancho, const std::string& archivoHTML, int velocidad = 100);

    /**
     * @brief Destructor de la clase Marquesina.
     */
    ~Marquesina();

    /**
     * @brief Inicia la animación de la marquesina.
     */
    void iniciar();

    /**
     * @brief Detiene la animación de la marquesina.
     */
    void detener();

    /**
     * @brief Pausa la animación de la marquesina.
     */
    void pausar();

    /**
     * @brief Reanuda la animación de la marquesina si está pausada.
     */
    void reanudar();

    /**
     * @brief Actualiza el texto de la marquesina.
     * @param nuevoTexto Nuevo texto a mostrar.
     */
    void actualizarTexto(const std::string& nuevoTexto);

    /**
     * @brief Bloquea temporalmente la marquesina.
     */
    void bloquear();

    /**
     * @brief Desbloquea la marquesina.
     */
    void desbloquear();

    /**
     * @brief Marca el inicio de una operación crítica (por ejemplo, manipulación de cursor).
     */
    void marcarOperacionCritica();

    /**
     * @brief Finaliza una operación crítica.
     */
    void finalizarOperacionCritica();

    /**
     * @brief Fuerza una actualización inmediata de la marquesina.
     */
    void forzarActualizacion();

    /**
     * @brief Muestra la ruta del archivo HTML (para depuración).
     */
    void mostrarRutaArchivo();

    /**
     * @brief Verifica si la marquesina está visible (ejecutando, no pausada ni bloqueada).
     * @return true si está visible, false en caso contrario.
     */
    bool estaVisible() const { return ejecutando && !pausado && !bloqueado; }
};
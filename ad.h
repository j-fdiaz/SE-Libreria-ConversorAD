/*
 * Librería de módulo conversor A/D
 * para el Microcontrolador 68HC12
 *
 * Autores: Raúl Suárez Jiménez
 *          Javier Francisco Díaz
 *
 * Fecha: 06/11/2025
 *
 *
 * */

#include <types.h>
#include <sys/param.h>
#include <sys/interrupts.h>
#include <sys/sio.h>
#include <sys/locks.h>

// elegir puerto de conversion
bool ad_conf_puerto(uint8_t);

// configurar conversión de 8 o 10 bits
bool ad_conf_bits(uint8_t);

// configurar tiempo de muestreo
bool ad_conf_tiempo_muestreo(uint8_t);

// configurar numero de conversiones sucesivas (1, 4 u 8)
bool ad_conf_num_conversiones(uint8_t);

// configurar modo de lectura: único pin, pines sucesivos 
bool ad_activar_lectura_pines_sucesivos(uint8_t);

// configurar pin de inicio
bool ad_conf_pin_inicio(uint8_t);

// configurar el modo de conversión continua (SCAN)
bool ad_activa_lectura_continua(uint8_t);

// iniciar la conversión
bool ad_inicia_conversion();

// esperar a que termine conversión
bool ad_espera_conversion();

// devolver los valores leídos
bool ad_recupera_conversion(uint16_t*);

// instalar función manejadora para cuando termine conversión

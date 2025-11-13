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

#include "ad.h"

#define TRUE 1
#define false 0

uint8_t mi_CTL3 = 0;
uint8_t mi_CTL4 = 0;
uint8_t mi_CTL5 = 0;
uint8_t dir_ad = 0;

// elegir puerto de conversion
uint8_t ad_conf_puerto(uint8_t puerto) {
  dir_ad = (puerto == 0)?0:(M6812_ATD1CTL0 - M6812_ATD0CTL0);
  return TRUE;
}

// configurar conversión de 8 o 10 bits
uint8_t ad_conf_bits(uint8_t bits_conversion) {
  if (bits_conversion == 8) {
    // Desactivamos el bit RES10
    mi_CTL4 &= ~M6812B_RES10;
    return TRUE;
  } else if (bits_conversion == 10) {
    // Activamos el bit RES10
    mi_CTL4 |= M6812B_RES10;
    return TRUE;
  } else 
    return false;
}

// configurar tiempo de muestreo
uint8_t ad_conf_tiempo_muestreo(uint8_t tiempo_muestreo) {
  switch (tiempo_muestreo) {
  case 2:
    mi_CTL4 &= ~M6812B_SMP1 & ~M6812B_SMP0;
    return TRUE;
  case 4:
    mi_CTL4 &= ~M6812B_SMP1;
    mi_CTL4 |= M6812B_SMP0;
    return TRUE;
  case 8:
    mi_CTL4 |= M6812B_SMP1;
    mi_CTL4 &= ~M6812B_SMP0;
    return TRUE;
  case 16:
    mi_CTL4 |= M6812B_SMP1 | M6812B_SMP0;
    return TRUE;
  default:
    return false;
  }
}

// configurar numero de conversiones sucesivas
uint8_t ad_conf_num_conversiones(uint8_t conversiones) {
  switch (conversiones) {
  case 1:
    mi_CTL5 &= ~M6812B_S8C;
    mi_CTL3 |= M6812B_S1C;
    return TRUE;
  case 4:
    mi_CTL5 &= ~M6812B_S8C;
    mi_CTL3 &= ~M6812B_S1C;
    return TRUE;
  case 8:
    mi_CTL5 |= M6812B_S8C;
    return TRUE;
  default:
    return false;
  }
}

// configurar modo de lectura: único pin, pines sucesivos
uint8_t ad_activar_lectura_pines_sucesivos(uint8_t modo) {
  if (modo == 0)
    mi_CTL5 &= ~M6812B_MULT;
  else
    mi_CTL5 |= M6812B_MULT;
  return TRUE;
}

// configurar pin de inicio
uint8_t ad_conf_pin_inicio(uint8_t canal) {
  mi_CTL5 &= ~(0x07);
  mi_CTL5 |= canal & (0x07);
  return TRUE;
}

// configurar el modo de conversión continua (SCAN)
uint8_t ad_activa_lectura_continua(uint8_t modo) {
  if (modo == 0)
    mi_CTL5 &= ~M6812B_SCAN;
  else
    mi_CTL5 |= M6812B_SCAN;
  return TRUE;
}

// Sube los registros a la placa
void ad_push_configuracion() {
  _io_ports[M6812_ATD0CTL3 + dir_ad] = mi_CTL3;
  _io_ports[M6812_ATD0CTL4 + dir_ad] = mi_CTL4;
  _io_ports[M6812_ATD0CTL5 + dir_ad] = mi_CTL5;
}

// iniciar la conversión
uint8_t ad_inicia_conversion();

// esperar a que termine conversión
uint8_t ad_espera_conversion();

// devolver los valores leídos
uint8_t ad_recupera_conversion(uint16_t* );

// instalar función manejadora para cuando termine conversión
//  Función que recibe un puntero a una función, tiene que activar
//  interrupciones. Solo se ejecuta la función recibida cuando 
//  recibe la interrupción (al terminar la conversión)
uint8_t 

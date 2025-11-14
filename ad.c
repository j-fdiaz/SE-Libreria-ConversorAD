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
uint8_t num_conversiones = 0;
void (*)(void) func_glob;

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
  num_conversiones = conversiones;
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
// canal elige el canal de 1 a 7.
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

// iniciar la conversión
void ad_inicia_conversion() {
  _io_ports[M6812_ATD0CTL3 + dir_ad] = mi_CTL3;
  _io_ports[M6812_ATD0CTL4 + dir_ad] = mi_CTL4;
  _io_ports[M6812_ATD0CTL5 + dir_ad] = mi_CTL5;
}

// esperar a que termine conversión
void ad_espera_conversion() {
  while(! (_io_ports[M6812_ATD0STAT0 + DirAD] & M6812B_SCF));
}

// devolver los valores leídos
void ad_recupera_conversion(uint16_t* resul, uint8_t cantidad) {
  cantidad &= (0x07); // cantidad = cantidad % 8
  for (int i = 0; i < cantidad; ++i) {
    resul[i] = _IO_PORTS_W(M6812_ADR00H + dir_ad + i * 2);
  }
}

// funcion ejecutada al saltar una
// interrupcion del Conversor AD
void __attribute__((interrupt)) vi_atd(void) {
  func_global();
}

// instalar función manejadora para cuando termine conversión
//  Función que recibe un puntero a una función, tiene que activar
//  interrupciones. Solo se ejecuta la función recibida cuando
//  recibe la interrupción (al terminar la conversión)
void ad_funcion_manejadora(void (*func)(void)) {
  func_glob = func;
  // Activamos las interrupciones para el conversor AD
  _io_ports[M6812_ATD0CTL2 + dir_ad] |= M6812B_ASCIE;
  ad_inicia_conversion();
  // Desactivamos las interrupciones para el conversor AD
  _io_ports[M6812_ATD0CTL2 + dir_ad] &= ~M6812B_ASCIE;
}

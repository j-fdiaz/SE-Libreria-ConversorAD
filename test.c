/*
 * Programa para testear las funciones
 * de la librería ConversorAD
 *
 * Autores: Raúl Suárez Jiménez
 *          Javier Francisco Díaz
 *
 * Fecha: 13/11/2025
 *
 *
 */

#include "ad.h"

void resetVars() {
  mi_CTL3 = 0;
  mi_CTL4 = 0;
  mi_CTL5 = 0;
  dir_ad = 0;
}

void passed() { serial_print("Test PASSED\n"); }
void failed() { serial_print("Test FAILED\n"); }
void endl() { serial_print("\n"); }

int main() {

  // ==== TEST ad_conf_puerto(uint8_t); ====
  serial_print("Testing ad_conf_puerto(uint8_t)\n");
  // ad_conf_puerto(0)
  serial_print("Test ad_conf_puerto(0): ");
  ad_conf_puerto(0);
  if (dir_ad == 0)
    passed();
  else
    failed();
  endl();
  resetVars();
  // ad_conf_puerto(1)
  serial_print("Test ad_conf_puerto(1): ");
  ad_conf_puerto(0);
  if (dir_ad == (M6812_ATD1CTL0 - M6812_ATD0CTL0))
    passed();
  else
    failed();
  endl();
  resetVars();
  // ad_conf_puerto(37)
  serial_print("Test ad_conf_puerto(37): ");
  ad_conf_puerto(37);
  if (dir_ad == (M6812_ATD1CTL0 - M6812_ATD0CTL0))
    passed();
  else
    failed();
  endl();
  resetVars();

  // ==== TEST ad_conf_bits(uint8_t); ====
  serial_print("Testing ad_conf_bits(uint8_t)");
  serial_print("Test ad_conf_bits(8) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_conf_bits(8)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10)) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 0
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_conf_bits(8) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_conf_bits(8)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10)) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 0
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_conf_bits(10) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_conf_bits(10)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 1
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_conf_bits(10) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_conf_bits(10)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 1
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_conf_bits(45) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_conf_bits(45)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 1
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_conf_bits(45) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_conf_bits(45)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_RES10) {
      // Si ad_conf_bits fue satisfacorio y el bit RES10 está a 1
      passed();
    } else
      failed();
  } else
    failed();


  // ==== TEST uint8_t ad_conf_tiempo_muestreo(uint8_t); ====
  serial_print("Testing ad_conf_tiempo_muestreo(uint8_t)");
  serial_print("Test ad_conf_tiempo_muestreo(2): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_tiempo_muestreo(2)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        !(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 00 
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_tiempo_muestreo(2): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_tiempo_muestreo(2)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        !(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 00 
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_conf_tiempo_muestreo(4): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_tiempo_muestreo(4)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 01 
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_tiempo_muestreo(4): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_tiempo_muestreo(4)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 01 
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_conf_tiempo_muestreo(8): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_tiempo_muestreo(8)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        !(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 10 
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_tiempo_muestreo(8): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_tiempo_muestreo(8)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        !(_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 10 
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_tiempo_muestreo(16): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_tiempo_muestreo(16)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 11 
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_tiempo_muestreo(16): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_tiempo_muestreo(16)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP1) &&
        (_io_ports[M6812_ATD0CTL4 + dir_ad] & M6812B_SMP0)) {
      // Si ad_conf_tiempo_muestreo fue satisfacorio 
      // y los bits SMP1-SMP0 están a 11 
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_conf_tiempo_muestreo(23):");
  if (!ad_conf_tiempo_muestreo(23)) {
      passed();
  } else failed();
  

  // ==== TEST uint8_t ad_conf_num_conversiones(uint8_t); ====
  serial_print("Testing ad_conf_num_conversiones(uint8_t)");
  serial_print("Test ad_conf_num_conversiones(1): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_num_conversiones(1)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C) &&
        (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_S1C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 01
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_num_conversiones(1): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_num_conversiones(1)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C) &&
        (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_S1C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 01
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_conf_num_conversiones(4): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_num_conversiones(4)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C) &&
        !(_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_S1C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 00
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_num_conversiones(4): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_num_conversiones(4)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C) &&
        !(_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_S1C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 00
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_num_conversiones(8): puerto 0");
  ad_conf_puerto(0);
  if (ad_conf_num_conversiones(8)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 1X
      passed();
    } else failed();
  } else failed();
  
  serial_print("Test ad_conf_num_conversiones(8): puerto 1");
  ad_conf_puerto(1);
  if (ad_conf_num_conversiones(8)) {
    ad_inicia_conversion();
    if ((_io_ports[M6812_ATD0CTL3 + dir_ad] & M6812B_S8C)) {
      // Si ad_conf_num_conversiones fue satisfacorio 
      // y los bits S8C-S1C están a 1X
      passed();
    } else failed();
  } else failed();


  // ==== TEST uint8_t ad_activar_lectura_pines_sucesivos(uint8_t); ====
  serial_print("Testing ad_activar_lectura_pines_sucesivos(uint8_t)");
  serial_print("Test ad_activar_lectura_pines_sucesivos(0) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_activar_lectura_pines_sucesivos(0)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT)) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 0
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_activar_lectura_pines_sucesivos(0) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_activar_lectura_pines_sucesivos(0)) {
    ad_inicia_conversion();
    if (!(_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT)) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 0
      passed();
    } else
      failed();
  } else
    failed();

  serial_print("Test ad_activar_lectura_pines_sucesivos(1) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_activar_lectura_pines_sucesivos(1)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 1
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_activar_lectura_pines_sucesivos(1) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_activar_lectura_pines_sucesivos(1)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 1
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_activar_lectura_pines_sucesivos(23) puerto 0: ");
  ad_conf_puerto(0);
  if (ad_activar_lectura_pines_sucesivos(23)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 1
      passed();
    } else failed();
  } else failed();

  serial_print("Test ad_activar_lectura_pines_sucesivos(23) puerto 1: ");
  ad_conf_puerto(1);
  if (ad_activar_lectura_pines_sucesivos(23)) {
    ad_inicia_conversion();
    if (_io_ports[M6812_ATD0CTL5 + dir_ad] & M6812B_MULT) {
      // Si ad_activar_lectura_pines_sucesivos fue satisfacorio y el bit MULT está a 1
      passed();
    } else failed();
  } else failed();

  // ==== TEST uint8_t ad_conf_pin_inicio(uint8_t); ====

  // ==== TEST uint8_t ad_activa_lectura_continua(uint8_t); ====

  // ==== TEST uint8_t ad_inicia_conversion(); ====

  // ==== TEST uint8_t ad_espera_conversion(); ====

  // ==== TEST uint8_t ad_recupera_conversion(uint16_t*); ====
}

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

#include <sys/interrupts.h>
#include <sys/locks.h>
#include <sys/param.h>
#include <sys/sio.h>
#include <types.h>

int main() {
  uint8_t char_recibido;

  uint16_t resultadoAnterior = 0;

  // Encendemos el LED
  _io_ports[M6812_DDRG] |= M6812B_PG7;
  _io_ports[M6812_PORTG] |= M6812B_PG7;

  serial_init();
  serial_print("\r\n" __FILE__ " ==========\r\n");

  while (TRUE) {
    if (serial_receive_pending()) serial_recv();
    // Pedir puerto

    serial_print("\r\nPuerto conversor a utilizar (0 - 1)?:");
    while((char_recibido = serial_recv()) != '0' && char_recibido != '1');
    serial_send(char_recibido); /* a modo de confirmación*/
    ad_conf_puerto(char_recibido);

    serial_print("\r\n Puerto: ");
    serial_print_dec_uint8(char_recibido);

    /* Elección del pin dentro del puerto */
    serial_print("\r\nPin del puerto a utilizar (0 - 7)?:");
    while((char_recibido = serial_recv()) < '0' || char_recibido > '7');
    serial_send(char_recibido); /* a modo de confirmación*/
    ad_conf_pin_inicio(char_recibido);

    serial_print("\r\n Pin: ");
    serial_print_dec_uint8(char_recibido);
    
    // resolución de 10 bits y 16 ciclos de muestreo
    ad_conf_bits((uint8_t)10);
    ad_conf_tiempo_muestreo((uint8_t)16);

    // Modo scan con 8 resultados
    ad_activa_lectura_continua((uint8_t)1);
    ad_conf_num_conversiones((uint8_t)8);
    
    while(!serial_receive_pending()) {
      ad_inicia_conversion();

      ad_espera_conversion();
     
      const uint8_t num_conversiones = 8;
      /*Vemos si los 8 resultados son iguales */
      uint16_t resultado;
      uint16_t resultado_arr[num_conversiones];
      uint16_t resultadoAnterior;
      ad_recupera_conversiones(resultado_arr, num_conversiones);
      resultado = resultado_arr[0];
      uint8_t iguales = 1;
      for(uint8_t i = 0; iguales && i < num_conversiones; i++) {
        iguales = resultado == resultado_arr[i];
      }
      if(!iguales)
        continue;
      if (resultado == resultadoAnterior)
        continue;

      /* Los 8 resultados son iguales y distintos a lo que teníamos antes*/
      serial_print("  Nuevo valor = ");
      serial_print_dec_uint16(resultado);
      serial_print("    \r");
      resultadoAnterior = resultado;
    }
  }
}

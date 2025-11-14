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


/* ! @defgroup ad Conversor Analógico-Digital
  
  Conjunto de funciones que facilitan el uso del conversor
  analógico-digital.

  @{
 */

/*! Elegir puerto.
  
  Configura el puerto a utilizar.

  @param puerto Puerto a utilizar, 0 para el puerto 0,
  cualquier otro valor para puerto 1.

 */
void ad_conf_puerto(uint8_t puerto);

/*! Configurar bits de resolución.

  Configura los bits de resolución de la conversión.
  
  @param bits_conversion Bits de resolución. 8 para
  resolución de 8 bits, 10 para 10. Cualquier otro 
  valor no modifica nada.

  @return true si se configuró correctamente, false
  si hubo algún fallo.

 */
uint8_t ad_conf_bits(uint8_t bits_conversion);

/*! Configurar tiempo de muestreo

  Configura el tiempo de muestreo entre 2, 4,
  8 ó 16 ciclos.
  
  @param tiempo_muestreo Tiempo de muestreo. Puede ser
  2, 4, 8 ó 16. Cualquier otro valor no modifica nada.

  @return true si se configuró correctamente, false
  si hubo algún fallo.

 */
uint8_t ad_conf_tiempo_muestreo(uint8_t tiempo_muestreo);

/*! Configurar número de conversiones sucesivas

  Configura el número de conversiones sucesivas
  que se van a realizar en cada ciclo de conversión.
  
  @param conversiones Número de conversiones. Puede ser
  1, 4 ó 8. Cualquier otro valor no modifica nada.

  @return true si se configuró correctamente, false
  si hubo algún fallo.

 */
uint8_t ad_conf_num_conversiones(uint8_t conversiones);

/*! Activar lectura de pines sucesivos

  Configura si se van a leer pines sucesivos
  o no.
  
  @param modo Modo de lectura. 0 para desactivar
  la lectura de pines sucesivos, cualquier otro
  valor para activarla.

 */
void ad_activar_lectura_pines_sucesivos(uint8_t modo);

/*! Configurar pin de inicio

  Configura el pin de inicio de la conversión.
  
  @param canal Canal a utilizar como pin de inicio.
  Debe estar entre 0 y 7. Cualquier otro valor no
  modifica nada.

  @return true si se configuró correctamente, false
  si hubo algún fallo.

 */
uint8_t ad_conf_pin_inicio(uint8_t canal);

/*! Configurar modo de conversión continua

  Configura el modo de conversión continua (SCAN).
  
  @param modo Modo de conversión. 0 para desactivar
  la conversión continua, cualquier otro valor para
  activarla.

  @return true si se configuró correctamente, false
  si hubo algún fallo.

 */
uint8_t ad_activa_lectura_continua(uint8_t modo);

/*! Iniciar conversión A/D

  Inicia una conversión A/D.

 */
void ad_inicia_conversion();

/*! Esperar a que termine la conversión

  Bloquea la ejecución hasta que termine
  la conversión A/D.

 */
void ad_espera_conversion();

/*! Recuperar resultados de la conversión

  Recupera los resultados de la conversión A/D.

  @param resul Puntero al array donde se van a
  almacenar los resultados.

  @param cantidad Número de conversiones a recuperar.
  Debe estar entre 1 y 8. Si es mayor que 8, se
  recuperan sólo 8 conversiones.

 */
void ad_recupera_conversion(uint16_t* resul, uint8_t cantidad);

/*! Ejecutar función tras conversión A/D

  Configura una función que se ejecutará
  tras cada conversión A/D.

  @param func Función a ejecutar.

 */
void ad_ejecuta_funcion(void (*func)(void));

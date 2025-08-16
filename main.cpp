/**
 * @file main.cpp
 * @brief Exemplo de uso do driver `MPU6050` com o proxy `I2C`.
 *
 * Demonstra a inicialização do I2C, configuração do sensor e leitura periódica
 * de aceleração, giroscópio e temperatura, com impressão via USB-CDC.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "I2C.h"
#include "MPU6050.h"

/**
 * @def I2C_ID
 * @brief Instância de hardware I2C utilizada (i2c0).
 */
#define I2C_ID        i2c0
/**
 * @def I2C_SCL_PIN
 * @brief Pino SCL do barramento I2C.
 */
#define I2C_SCL_PIN   0
/**
 * @def I2C_SDA_PIN
 * @brief Pino SDA do barramento I2C.
 */
#define I2C_SDA_PIN   1

/**
 * @def BAUD_RATE
 * @brief Frequência do barramento I2C em Hz (400kHz).
 */
#define BAUD_RATE     400000   // 400kHz

/**
 * @brief Ponto de entrada do exemplo.
 *
 * - Inicializa stdio e I2C
 * - Instancia e inicia o driver do MPU6050
 * - Lê e imprime dados a cada 2 segundos
 */
int main()
{
    stdio_init_all();

  I2C i2c(I2C_ID, I2C_SDA_PIN, I2C_SCL_PIN);
  i2c.begin();
  i2c.setClock(BAUD_RATE);
  printf ("I2C @ %u Hz\n", BAUD_RATE);

  MPU6050 sensor (&i2c);
  sensor.begin();

  printf ("ID do Sensor: %02X\n", sensor.getId());

  MPU6050::VECT_3D data;
  while(1) {
    sleep_ms(2000);
    sensor.getAccelleration(&data);
    printf ("Aceleração X:%.2f Y:%.2f Z:%.2f\n", data.x, data.y, data.z);
    sensor.getGyroscope(&data);
    printf ("Giroscópio X:%.2f Y:%.2f Z:%.2f\n", data.x, data.y, data.z);
    printf ("Temperatura: %.2f\n", sensor.getTemp());
    printf("\n");
  }
}
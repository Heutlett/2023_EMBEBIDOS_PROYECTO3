#include <unistd.h> /* usleep */
#include <gpio_rpi.h>
#include <stdio.h>

int main()
{
    gpio_rpi_init_ptrs();

    // Configurar todos los pines como output
    gpio_rpi_set_mode(1,1);
    gpio_rpi_set_mode(2,1);
    gpio_rpi_set_mode(3,1);
    gpio_rpi_set_mode(4,1);
    gpio_rpi_set_mode(5,1);
    gpio_rpi_set_mode(6,1);
    // Verificar modo
    gpio_rpi_get_mode_all();

    // Poner todos los pines en 1
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(1, 1);
    gpio_rpi_write(2, 1);
    gpio_rpi_write(3, 1);
    gpio_rpi_write(4, 1);
    gpio_rpi_write(5, 1);
    gpio_rpi_write(6, 1);
    
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(1, 0);
    gpio_rpi_write(2, 0);
    gpio_rpi_write(3, 0);
    gpio_rpi_write(4, 0);
    gpio_rpi_write(5, 0);
    gpio_rpi_write(6, 0);

    // Poner todos los pines en 1
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(1, 1);
    gpio_rpi_write(2, 1);
    gpio_rpi_write(3, 1);
    gpio_rpi_write(4, 1);
    gpio_rpi_write(5, 1);
    gpio_rpi_write(6, 1);
    return 0;
}

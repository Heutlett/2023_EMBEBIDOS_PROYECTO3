#include <unistd.h> /* usleep */
#include <gpio_rpi.h>
#include <stdio.h>

int main()
{
    gpio_rpi_init_ptrs();

    // Configurar todos los pines como output
    gpio_rpi_set_mode(17,0);
    gpio_rpi_set_mode(27,0);
    gpio_rpi_set_mode(22,0);
    gpio_rpi_set_mode(18,0);
    gpio_rpi_set_mode(5,1);
    gpio_rpi_set_mode(6,1);
    // Verificar modo
    gpio_rpi_get_mode_all();

    printf("Pines seteados \n");
    printf("Escritura en pines 5 y 6\n\n");

    // Poner todos los pines en 1
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(5, 1);
    gpio_rpi_write(6, 1);
    
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(5, 0);
    gpio_rpi_write(6, 0);

    // Poner todos los pines en 1
    usleep(1000000);

    // Poner 1 a pin 5
    gpio_rpi_write(5, 1);
    gpio_rpi_write(6, 1);

    usleep(1000000);

    printf("Lectura de pines 17,27,22,18\n\n");

    int a = gpio_rpi_read(17);

    printf("a: %d", a);
    gpio_rpi_read(27);
    gpio_rpi_read(22);
    gpio_rpi_read(18);

    printf("Lectura de todos los pines\n\n");
    gpio_rpi_read_all();

    return 0;
}

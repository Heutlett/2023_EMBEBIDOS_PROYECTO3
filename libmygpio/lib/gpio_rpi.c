#include <sys/mman.h> /* mmap */
#include <err.h>      /* error handling */
#include <fcntl.h>    /* file ops */
#include <unistd.h>   /* usleep */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Static base address */
static unsigned gpio_rpi_BASE = 0x3f200000;

/* Register pointers */
volatile unsigned int *gpfsel0;
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;
volatile unsigned int *gplev0;

/* Initialize pointers: performs memory mapping, exits if mapping fails */
void gpio_rpi_init_ptrs(void)
{
  int fd = -1;

  /* Loading /dev/mem into a file */
  if ((fd = open("/dev/mem", O_RDWR, 0)) == -1)
  {
    err(1, "Error Opening /dev/mem\n");
  }

  /* Mapping GPIO base physical address */
  gpfsel0 = (unsigned int *)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, gpio_rpi_BASE);

  if (gpfsel0 == MAP_FAILED)
  {
    errx(1, "Error during mapping GPIO\n");
  }

  /* Set register pointers */
  /* offset 0x1C / 4 = 0x7 */
  gpset0 = gpfsel0 + 0x7;

  /* offset 0x28 / 4 = 0xA */
  gpclr0 = gpfsel0 + 0xA;

  /* offset 0x34 / 4 = 0xD */
  gplev0 = gpfsel0 + 0xD;
}

/* Configura el modo de todos los pines
  args: mode, dato de 0 a 7 para configurar todos
  los modos de los pines, segun pag 92 de BCM2835
  datasheet
*/
void gpio_rpi_set_mode_all(int mode)
{
  // Limitar el modo de todos los pines para que sean entre 0 y 7
  mode &= 0x7;

  unsigned int value = 0;
  // Calcular el valor a escribir en gpfsel0
  for (int pin = 0; pin < 10; ++pin)
  {
    // shift right para obtener los 3 bits correspondientes al pin
    int mode_bits = (mode >> (pin * 3)) & 0x7;
    // ubicar mode_bits en posicion para colocar los bits en value
    value |= (mode_bits << (pin * 3));
  }

  *gpfsel0 = value;
}

/* Configura el modo de un pin en particular
  args:
        mode:
            dato de 0 a 7 para configurar el
            modo del pin, segun pag 92 de BCM2835
            datasheet.
        int:
        dato de 0 a 9 que indica el pin a configurar
*/
void gpio_rpi_set_mode(int pin, int mode)
{
  // Máscara para los 3 bits asociados al pin
  int mask = 0b111 << (3 * (pin % 10));

  // Se limpian esos bits en gpfsel0
  *gpfsel0 &= ~mask;

  // Se configuran los bits de modo para el pin
  *gpfsel0 |= (mode << (3 * (pin % 10)));
}

/*Configurar todos los pines en 0 o 1 */
void gpio_rpi_write_all(unsigned char bit)
{
  if (bit)
  {
    printf("All bits set to 1\n", 0x2FC);
    *gpset0 = *gpset0 | 0x2FC;
  }
  else
  {
    printf("All bits set to 0\n", 0x2FC);
    *gpclr0 = *gpclr0 | 0x2FC;
  }
}

void gpio_rpi_write(int pin, unsigned char bit)
{
  if (bit)
  {
    printf("Pin %d set to 1\n", pin);
    *gpset0 = (1 << pin);
  }
  else
  {
    printf("Pin %d set to 0\n", pin);
    *gpclr0 = (1 << pin);
  }
}

void gpio_rpi_read_all(void)
{
  unsigned int bits = *gplev0;

  for (int i = 0; i < 10; ++i)
  {
    printf("Pin %d value is %d\n", i, (bits >> i) & 0x1);
  }
}

int gpio_rpi_read(int pin)
{
  unsigned int bits = *gplev0;
  bits >>= pin;
  bits &= 0x1;

  printf("Pin %d value is %d\n", pin, bits);
  return (int)bits;
}

void gpio_rpi_get_mode_all(void)
{
  unsigned int bits = *gpfsel0;

  for (int i = 2; i < 10; ++i)
  {
    printf("Pin %d is in mode %d\n", i, (bits >> (i * 3)) & 0x7);
  }
}

void gpio_rpi_get_mode(int pin)
{
  unsigned int bits = *gpfsel0;

  bits >>= (pin * 3);
  bits &= 0x7;

  printf("Pin %d is in mode %d\n", pin, bits);
}
void gpio_rpi_init_ptrs(void);
void gpio_rpi_set_mode_all(int mode);
void gpio_rpi_set_mode(int pin, int mode);
void gpio_rpi_write_all(unsigned char bit);
void gpio_rpi_write(int pin, unsigned char bit);
void gpio_rpi_read_all(void);
int gpio_rpi_read(int pin);
void gpio_rpi_get_mode_all(void);
void gpio_rpi_get_mode(int pin);

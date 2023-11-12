from ctypes import *

from config import constants

rpigpio_lib = CDLL(constants.GPIO_SRC_LIB)

# void gpio_rpi_init_ptrs(void);
def gpio_rpi_init_ptrs() -> None:
    _gpio_rpi_init_ptrs = rpigpio_lib.gpio_rpi_init_ptrs
    _gpio_rpi_init_ptrs.restype = c_void_p

# void gpio_rpi_set_mode_all(int mode);
def gpio_rpi_set_mode_all(mode: int) -> None:
    _gpio_rpi_set_mode_all = rpigpio_lib.gpio_rpi_set_mode_all
    _gpio_rpi_set_mode_all.restype = c_void_p

# void gpio_rpi_set_mode(int pin, int mode);
def gpio_rpi_set_mode(pin: int, mode: int) -> None:
    _gpio_rpi_set_mode = rpigpio_lib.gpio_rpi_set_mode
    _gpio_rpi_set_mode.restype = c_void_p

# void gpio_rpi_write_all(unsigned char bit);
def gpio_rpi_write_all(bit: int) -> None:
    _gpio_rpi_write_all = rpigpio_lib.gpio_rpi_write_all
    _gpio_rpi_write_all.restype = c_void_p

# void gpio_rpi_write(int pin, unsigned char bit);
def gpio_rpi_write(pin: int, bit: int) -> None:
    _gpio_rpi_write = rpigpio_lib.gpio_rpi_write
    _gpio_rpi_write.restype = c_void_p

# void gpio_rpi_read_all(void);
def gpio_rpi_read_all() -> None:
    _gpio_rpi_read_all = rpigpio_lib.gpio_rpi_read_all
    _gpio_rpi_read_all.restype = c_void_p

# int gpio_rpi_read(int pin);
def gpio_rpi_read(pin: int) -> int:
    _gpio_rpi_read = rpigpio_lib.gpio_rpi_read
    _gpio_rpi_read.restype = c_int

    return _gpio_rpi_read(c_int(pin))

# void gpio_rpi_get_mode_all(void);
def gpio_rpi_get_mode_all() -> None:
    _gpio_rpi_get_mode_all = rpigpio_lib.gpio_rpi_get_mode_all
    _gpio_rpi_get_mode_all.restype = c_void_p

# void gpio_rpi_get_mode(int pin);
def gpio_rpi_get_mode(pin: int) -> None:
    _gpio_rpi_get_mode = rpigpio_lib.gpio_rpi_get_mode
    _gpio_rpi_get_mode.restype = c_void_p


# # int export_command(int PIN);
# def export_command(pin: int) -> int:
#     _export_command = rpigpio_lib.export_command
#     _export_command.restype = c_int

#     return _export_command(c_int(pin))

# # int pinMode(int PIN, int DIRECTION);
# def pin_mode(pin: int, direction: int) -> int:
#     _pin_mode = rpigpio_lib.pinMode
#     _pin_mode.restype = c_int

#     return _pin_mode(c_int(pin), c_int(direction))

# # int digitalWrite(int pin, int value);
# def digital_write(pin: int, direction: int) -> int:
#     _digital_write = rpigpio_lib.digitalWrite
#     _digital_write.restype = c_int

#     return _digital_write(c_int(pin), c_int(direction))

# # int digitalRead(int pin);
# def digital_read(pin: int) -> int:
#     _digital_read = rpigpio_lib.digitalRead
#     _digital_read.restype = c_int

#     return _digital_read(c_int(pin))

# # int blink(int pin, float freq, double duration);
# def blink(pin: int, freq: float, duration: float) -> int:
#     _blink = rpigpio_lib.blink
#     _blink.restype = c_int
    
#     return _blink(c_int(pin), c_float(freq), c_double(duration))

# # int unexport_command(int PIN);
# def unexport_command(pin: int) -> int:
#     _unexport_command = rpigpio_lib.unexport_command
#     _unexport_command.restype = c_int

#     return _unexport_command(c_int(pin))


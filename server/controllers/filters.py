from libs.rpigpio import *
from config import constants

def start() -> None:
    """
    This function starts the pins used by filters.
    """
    gpio_rpi_init_ptrs()
    
    for filter, pin in constants.PINS['filters'].items():
        gpio_rpi_set_mode(pin=pin, mode=constants.INPUT_MODE)
        print(f'Pin {pin} set as input for filter {filter}.')

def get_state(filter: str) -> int:
    """
    This function returns the current state of a specific filter.

    Params
    ------------------------------------------------------------------
        filter: str
            Name of the filter.
    
    Returns
    ------------------------------------------------------------------
        the current state of the filter.
    """
    pin: int = constants.PINS['filters'][filter]

    # Get the state of the door
    result = gpio_rpi_read(pin=pin)

    if (result == constants.FAIL):
        print('Filter Error: {filter} in pin {pin} is not available.')
    
    return result

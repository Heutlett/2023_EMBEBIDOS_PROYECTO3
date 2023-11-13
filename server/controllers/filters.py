from libs.gpioman import *
from libs.rpifilter import *
from config import constants

def finish() -> None:
    """
    This function clears the pins used by doors.
    """
    for pin in constants.PINS['filters'].values():
        unexport_command(pin)

def start() -> None:
    """
    This function starts the pins used by filters.
    """
    
    for filter, pin in constants.PINS['filters'].items():
        if export_command(pin) == constants.FAIL:
            print(f'Filter Error: Pin {pin} for {filter} failed to start.')
        else:
            if pin_mode(pin, constants.INPUT_MODE) == constants.FAIL:
                print(f'Filter Error: Pin {pin} for {filter} failed to start.')

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
    result = digital_read(pin)
    
    print("--------------------    filter ", filter, " value ", result,"    -----------------")

    if (result == constants.FAIL):
        print('Filter Error: {filter} in pin {pin} is not available.')
    
    return result

def filter_image(input_path: str, output_path: str, filter: int, use_omp: int):
    
    return apply_filter(input_path=input_path, output_path=output_path, filter=filter, use_omp=use_omp)
    
    
def take_photo_rpi(output_path: str):
    
    take_photo_gst(output_path)
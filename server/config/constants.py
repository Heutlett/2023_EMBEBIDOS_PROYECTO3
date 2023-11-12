# Dynamic library path
GPIO_SRC_LIB: str = '../usr/lib/libmygpio.so.0'
FILTER_SRC_LIB: str = '../usr/lib/libfilter.so.0'

# When writing out one logic voltage
HIGH: int = 1
# When writing out zero logic voltage
LOW: int = 0


# When setting pin_mode to read values
INPUT_MODE: int = 0
# When setting pin_mode to write values
OUTPUT_MODE: int = 1
# When some function does not reach the goal, returns -1


FAIL: int = -1
# When some function reaches the goal, returns 0
SUCCESS: int = 0


# Pins values
PINS: dict = {
    'filters': {
        'filter1': 23,
        'filter2': 24,
        'filter3': 20
    }
}

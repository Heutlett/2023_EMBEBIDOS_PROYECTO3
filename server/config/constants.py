# Dynamic library path
GPIO_SRC_LIB: str = '../usr/lib/libmygpio.so.0'
FILTER_SRC_LIB: str = '../usr/lib/libfilter.so.0'
GPIOMANSRC_LIB: str = '../usr/lib/libgpioman.so.0'

# Output image files
INPUT_IMG_PATH = '/filter-workspace/input.jpg'
OUTPUT_IMG_PATH = '/filter-workspace/output.jpg'

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
        'filter1': 17,
        'filter2': 27,
        'filter3': 22,
    }
}

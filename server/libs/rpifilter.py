from ctypes import *

from config import constants

rpifilter_lib = CDLL(constants.FILTER_SRC_LIB)

# void take_photo_gst(void);
def take_photo_gst(output_path: str) -> None:
    _take_photo_gst = rpifilter_lib.take_photo_gst
    _take_photo_gst.restype = c_void_p
    
    return _take_photo_gst(c_char_p(output_path.encode('utf-8')))


# int gpio_rpi_read(int pin);
def apply_filter(input_path: str, output_path: str, filter: int, use_omp: int) -> float:
    _apply_filter = rpifilter_lib.apply_filter
    _apply_filter.restype = c_float
    

    return _apply_filter(c_char_p(input_path.encode('utf-8')), c_char_p(output_path.encode('utf-8')), c_int(filter), c_int(use_omp))
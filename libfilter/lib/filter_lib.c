#include "filter_lib.h"
#include <omp.h>

void apply_filter_1(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Implementa el filtro 1 aquí
            // image_data[(y * width + x) * 3 + 0] = ...;  // Red
            // image_data[(y * width + x) * 3 + 1] = ...;  // Green
            // image_data[(y * width + x) * 3 + 2] = ...;  // Blue
        }
    }
}

void apply_filter_2(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Implementa el filtro 2 aquí
        }
    }
}

void apply_filter_3(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Implementa el filtro 3 aquí
        }
    }
}

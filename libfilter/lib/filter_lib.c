#include "filter_lib.h"
#include <omp.h>
#include <math.h>

// Filtro grey scale
void apply_filter_1(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            uint8_t red = image_data[index];
            uint8_t green = image_data[index + 1];
            uint8_t blue = image_data[index + 2];

            // Calcula la escala de grises promediando los componentes RGB
            uint8_t gray = (uint8_t)((red + green + blue) / 3);

            // Establece el mismo valor para los componentes RGB para obtener escala de grises
            image_data[index] = gray;
            image_data[index + 1] = gray;
            image_data[index + 2] = gray;
        }
    }
}

// Filtro sobel
void apply_filter_2(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            // Índices de los píxeles vecinos
            int tl = ((y - 1) * width + (x - 1)) * 3;
            int tc = ((y - 1) * width + x) * 3;
            int tr = ((y - 1) * width + (x + 1)) * 3;
            int cl = (y * width + (x - 1)) * 3;
            int cr = (y * width + (x + 1)) * 3;
            int bl = ((y + 1) * width + (x - 1)) * 3;
            int bc = ((y + 1) * width + x) * 3;
            int br = ((y + 1) * width + (x + 1)) * 3;

            // Máscaras del filtro Sobel
            int mask_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int mask_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // Calcula la convolución con las máscaras Sobel
            int sum_x = 0, sum_y = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sum_x += image_data[(y + i - 1) * width * 3 + (x + j - 1)] * mask_x[i][j];
                    sum_y += image_data[(y + i - 1) * width * 3 + (x + j - 1)] * mask_y[i][j];
                }
            }

            // Calcula la magnitud del gradiente
            int magnitude = (int) sqrt((double)(sum_x * sum_x + sum_y * sum_y));

            // Limita la magnitud a 255 para evitar desbordamientos
            magnitude = (magnitude > 255) ? 255 : magnitude;

            // Establece la magnitud en los componentes RGB del píxel
            image_data[(y * width + x) * 3] = magnitude;
            image_data[(y * width + x) * 3 + 1] = magnitude;
            image_data[(y * width + x) * 3 + 2] = magnitude;
        }
    }
}

// Filtro laplaciano
void apply_filter_3(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int index = (y * width + x) * 3;
            int laplacian = 0;

            // Aplica el filtro Laplaciano
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int neighbor_index = ((y + i) * width + (x + j)) * 3;
                    laplacian += image_data[neighbor_index];
                }
            }

            // Establece el valor resultante en el píxel central
            image_data[index] = laplacian / 9;
            image_data[index + 1] = laplacian / 9;
            image_data[index + 2] = laplacian / 9;
        }
    }
}

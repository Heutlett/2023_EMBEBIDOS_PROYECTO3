#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Filtro sobel
void apply_filter_1(char *image, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            char r = image[index];
            char g = image[index + 1];
            char b = image[index + 2];
            char gray = (char)(0.299 * r + 0.587 * g + 0.114 * b);
            image[index] = image[index + 1] = image[index + 2] = gray;
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

void apply_filter(char *input_path, char *output_path, int filter){

    int width, height, channels;
    uint8_t *image = stbi_load(input_path, &width, &height, &channels, 0);

    if (image == NULL) {
        fprintf(stderr, "Error al cargar la imagen.\n");
    }

    // Aplicar el filtro de escala de grises
    switch (filter)
    {
    case 1:
        apply_filter_1(image,width, height);
        break;

    case 2:
        apply_filter_2(image, width, height);
        break;
    case 3:
        apply_filter_3(image, width, height);
        break;
    
    default:
        break;
    }
    

    // Guardar la imagen resultante
    if (!stbi_write_jpg(output_path, width, height, channels, image, 100)) {
        fprintf(stderr, "Error al guardar la imagen.\n");
    }

    stbi_image_free(image);

    printf("Proceso completado. Imagen guardada en %s\n", output_path);
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <input_path> <output_path> <filter>\n", argv[0]);
        return 1;
    }

    char *input_path = argv[1];
    char *output_path = argv[2];
    int filter = atoi(argv[1]);

    apply_filter(input_path, output_path, filter);

    return 0;
}

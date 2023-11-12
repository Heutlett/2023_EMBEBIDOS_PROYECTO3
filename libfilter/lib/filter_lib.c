#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <sys/time.h>
//#include <gst/gst.h>

// Filtro sobel
void apply_filter_1(uint8_t *image_data, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            uint8_t r = image_data[index];
            uint8_t g = image_data[index + 1];
            uint8_t b = image_data[index + 2];
            uint8_t gray = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
            image_data[index] = image_data[index + 1] = image_data[index + 2] = gray;
        }
    }
}

// Filtro sobel
void apply_filter_2(uint8_t *image_data, int width, int height) {
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

// Filtro sobel
void apply_filter_1_omp(uint8_t *image_data, int width, int height) {
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            uint8_t r = image_data[index];
            uint8_t g = image_data[index + 1];
            uint8_t b = image_data[index + 2];
            uint8_t gray = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
            image_data[index] = image_data[index + 1] = image_data[index + 2] = gray;
        }
    }
}

// Filtro sobel
void apply_filter_2_omp(uint8_t *image_data, int width, int height) {
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
void apply_filter_3_omp(uint8_t *image_data, int width, int height) {
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

void take_photo_gst(char *output_path){
    // gst_init(NULL, NULL);

    // GstElement *pipeline, *source, *parse, *decode, *convert, *encode, *sink;

    // // Crear los elementos
    // pipeline = gst_pipeline_new("take-photo-pipeline");
    // source = gst_element_factory_make("v4l2src", "source");
    // parse = gst_element_factory_make("jpegparse", "parse");
    // decode = gst_element_factory_make("jpegdec", "decode");
    // convert = gst_element_factory_make("videoconvert", "convert");
    // encode = gst_element_factory_make("pngenc", "encode");
    // sink = gst_element_factory_make("filesink", "sink");

    // if (!pipeline || !source || !parse || !decode || !convert || !encode || !sink) {
    //     g_error("Failed to create elements. Exiting.\n");
    // }

    // // Establecer las propiedades de los elementos
    // g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);
    // g_object_set(G_OBJECT(encode), "snapshot", TRUE, NULL);
    // g_object_set(G_OBJECT(sink), "location", output_path, NULL);

    // // Agregar elementos al pipeline
    // gst_bin_add_many(GST_BIN(pipeline), source, parse, decode, convert, encode, sink, NULL);

    // // Enlazar los elementos
    // if (!gst_element_link_many(source, parse, decode, convert, encode, sink, NULL)) {
    //     g_error("Failed to link elements. Exiting.\n");
    // }

    // // Iniciar el pipeline
    // GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    // if (ret == GST_STATE_CHANGE_FAILURE) {
    //     g_error("Failed to start pipeline. Exiting.\n");
    // }

    // // Esperar a que termine la captura
    // GstBus *bus = gst_element_get_bus(pipeline);
    // GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // // Limpiar
    // gst_message_unref(msg);
    // gst_object_unref(bus);
    // gst_element_set_state(pipeline, GST_STATE_NULL);
    // gst_object_unref(pipeline);

}

double apply_filter(char *input_path, char *output_path, int filter, int use_omp){

    printf("Comenzando proceso de filtrado\n\n");
    printf("Filtro seleccionado %d\n\n", filter);

    int width, height, channels;
    uint8_t *image = stbi_load(input_path, &width, &height, &channels, 0);

    if (image == NULL) {
        fprintf(stderr, "Error al cargar la imagen.\n");
    }

    struct timeval start_time, end_time;
    long long elapsed_time;

    // Obtener el tiempo inicial
    gettimeofday(&start_time, NULL);

    // Aplicar el filtro de escala de grises
    switch (filter)
    {
    case 1:
        if(use_omp){
            printf("Aplicando filtro greyscale SIN OpenMP\n\n");
            apply_filter_1(image,width, height);
        }else{
            printf("Aplicando filtro greyscale CON OpenMP\n\n");
            apply_filter_1_omp(image,width, height);
        }
        break;

    case 2:
        if(use_omp){
            printf("Aplicando filtro sobel SIN OpenMP\n\n");
            apply_filter_2(image,width, height);
        }else{
            printf("Aplicando filtro sobel CON OpenMP\n\n");
            apply_filter_2_omp(image,width, height);
        }
        break;
    case 3:
        if(use_omp){
            printf("Aplicando filtro laplaciano SIN OpenMP\n\n");
            apply_filter_3(image,width, height);
        }else{
            printf("Aplicando filtro laplaciano CON OpenMP\n\n");
            apply_filter_3_omp(image,width, height);
        }
        break;
    
    default:
        break;
    }

    // Obtener el tiempo final
    gettimeofday(&end_time, NULL);

    // Calcular el tiempo transcurrido en microsegundos
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000LL + (end_time.tv_usec - start_time.tv_usec);

    // Mostrar el resultado
    printf("Tiempo transcurrido: %lld microsegundos\n", elapsed_time);
    

    // Guardar la imagen resultante
    if (!stbi_write_jpg(output_path, width, height, channels, image, 100)) {
        fprintf(stderr, "Error al guardar la imagen.\n");
    }

    stbi_image_free(image);

    printf("Proceso completado. Imagen guardada en %s\n", output_path);

    return elapsed_time;
}
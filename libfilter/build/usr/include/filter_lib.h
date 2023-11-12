#include <stdint.h>

void apply_filter_1(uint8_t *image_data, int width, int height);
void apply_filter_2(uint8_t *image_data, int width, int height);
void apply_filter_3(uint8_t *image_data, int width, int height);
void apply_filter_1_omp(uint8_t *image_data, int width, int height);
void apply_filter_2_omp(uint8_t *image_data, int width, int height);
void apply_filter_3_omp(uint8_t *image_data, int width, int height);
void take_photo_gst(char *output_path);
double apply_filter(uint8_t *input_path, char *output_path, int filter, int use_omp);
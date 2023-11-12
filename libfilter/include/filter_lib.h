#ifndef FILTER_LIB_H
#define FILTER_LIB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void apply_filter_1(unsigned char *image, int width, int height);
void apply_filter_2(uint8_t *image_data, int width, int height);
void apply_filter_3(uint8_t *image_data, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* FILTER_LIB_H */

#include <filter_lib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <input_path> <output_path> <filter> <use_omp>\n", argv[0]);
        return 1;
    }

    char *input_path = argv[1];
    char *output_path = argv[2];
    int filter = atoi(argv[3]);
    int use_omp = atoi(argv[4]);

    take_photo_gst(input_path);

    double time_elapsed = apply_filter(input_path, output_path, filter, use_omp);

    printf("Time elapsed: %f\n\n", time_elapsed);

    return 0;
}
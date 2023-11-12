#include <filter_lib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <input_path> <output_path> <filter>\n", argv[0]);
        return 1;
    }

    char *input_path = argv[1];
    char *output_path = argv[2];
    int filter = atoi(argv[3]);

    apply_filter(input_path, output_path, filter);

    return 0;
}
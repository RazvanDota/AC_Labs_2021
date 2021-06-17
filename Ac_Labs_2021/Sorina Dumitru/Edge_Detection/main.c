#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080
#define PADDING MAX_WIDTH*2

void read_file(const char *file_path, unsigned char *input_buffer, int width, int height) {
    FILE *input_image = fopen(file_path, "rb");
    unsigned int bytes_loaded = fread(input_buffer, 1, width * height, input_image);

    if (bytes_loaded != width * height) {
        if (feof(input_image)) {
            printf("End of file!\n");
        }

        if (ferror(input_image)) {
            printf("Error reading from file.\n");
        }

        printf("Could not read from stream enough bytes.\n");
        printf("Expected %u, loaded %u bytes\n", width * height, bytes_loaded);
        exit(1);
    }

    fclose(input_image);
}

void sobel(unsigned char *input, unsigned char *output, int width, int height) {
    int vertical[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int horizontal[3][3] = {
            {-1, -2, -1},
            {0,  0,  0},
            {1,  2,  1}
    };

    unsigned char *lines[5];
    for (int j = 0; j < height; j++) {
        lines[0] = input + j * width;
        lines[1] = input + (j + 1) * width;
        lines[2] = input + (j + 2) * width;

        for (int i = 0; i < width; i++) {
            float gx = (float)
                    (vertical[0][0] * lines[0][i - 1] + vertical[0][1] * lines[0][i] +
                     vertical[0][2] * lines[0][i + 1] +
                     vertical[1][0] * lines[1][i - 1] + vertical[1][1] * lines[1][i] +
                     vertical[1][2] * lines[1][i + 1] +
                     vertical[2][0] * lines[2][i - 1] + vertical[2][1] * lines[2][i] +
                     vertical[2][2] * lines[2][i + 1]);

            float gy = (float) (horizontal[0][0] * lines[0][i - 1] + horizontal[0][1] * lines[0][i] +
                                horizontal[0][2] * lines[0][i + 1] +
                                horizontal[1][0] * lines[1][i - 1] + horizontal[1][1] * lines[1][i] +
                                horizontal[1][2] * lines[1][i + 1] +
                                horizontal[2][0] * lines[2][i - 1] + horizontal[2][1] * lines[2][i] +
                                horizontal[2][2] * lines[2][i + 1]);

            float g = sqrtf(gx * gx + gy * gy);
            if (g > 255) {
                *(output + i + j * width) = 255;
            } else {
                *(output + i + j * width) = (unsigned int) g;
            }
        }
    }
}

void add_s(unsigned char *input, int s_size, int width, int height) {
    if (s_size > width || 2 * s_size + 2 > height) {
        perror("S is too big");
    }

    for (int i = 5; i < s_size + 5; i ++) {
        *(input + 2 * width + i) = 127;
    }

    for (int i = 3; i < s_size + 3; i++) {
        *(input + width * i + 5) = 127;
    }

    for (int i = 5; i <= s_size + 5; i ++) {
        *(input + (s_size + 3) * width + i) = 127;
    }

    for (int i = 3 + s_size; i < 2 * s_size + 4; i++) {
        *(input + width * i + 5 + s_size) = 127;
    }

    for (int i = 5; i <= 5 + s_size; i++) {
        *(input + (2  * s_size + 4) * width + i) = 127;
    }
}

void add_d(unsigned char *input, int s_size, int d_size, int width, int height) {
    if (d_size > width || d_size > height - s_size - 3) {
        perror("D is too big");
    }

    for (int i = 3 ; i <= 2 * d_size + 4; i++) {
        *(input + width * i + 5 + s_size + d_size) = 127;
    }

    for (int i = 1; i <= d_size/3; i++) {
        *(input + width * 3 + 5 + i + s_size + d_size) = 127;
    }

    int x = 1;
    for (int i = 3; i < d_size + 3; i++, x++) {
        *(input + width * i + 5 + s_size + d_size + d_size/3 + x) = 127;
    }

    for (int i = d_size + 3; i < 2 * d_size + 5; i++) {
        *(input + width * i + 5 + s_size + 2 * d_size + d_size/3)   = 127;
    }

    for (int i = 0; i < d_size * 4/3; i ++) {
        *(input + width * (4 + 2 * d_size) + 5 + i + s_size + d_size) = 127;
    }
}

void add_name(unsigned char *input, int s_size, int d_size, int width, int height) {
    add_s(input, s_size, width, height);
    add_d(input, s_size, d_size, width, height);
}

int main() {
    const int width = MAX_WIDTH;
    const int height = MAX_HEIGHT;

    unsigned char *input_buffer = (unsigned char *) malloc(sizeof(unsigned char) * width * height + PADDING);
    unsigned char *output_buffer = (unsigned char *) malloc(sizeof(unsigned char) * MAX_WIDTH * MAX_HEIGHT + PADDING);

    // read input file
    read_file("../Studio_1920x1080_8bit.raw", input_buffer, width, height);

    // fill padding
    for (int i = 0; i < width; i++) {
        *(input_buffer + height * width + i) = *(input_buffer + (height + 1) * width + i) = *(input_buffer +
                                                                                              (height - 1) * width + i);
    }

    // apply sobel
    sobel(input_buffer, output_buffer, width, height);

    // add name in the upper left corner :(
    add_name(output_buffer, 20, 20, width, height);

    // write output
    FILE *output_image = fopen("../output.raw", "wb");
    fwrite(output_buffer, 1, sizeof(unsigned char *) * MAX_HEIGHT * MAX_WIDTH, output_image);

    fclose(output_image);

    // free memory 
    free(input_buffer);
    free(output_buffer);

    return 0;
}

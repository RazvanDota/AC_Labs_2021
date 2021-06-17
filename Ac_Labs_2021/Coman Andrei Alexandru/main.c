#include "letters.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080
#define PADDING WIDTH*2

/*
    in     -> pointer to the input image
    out    -> pointer to the output image
    width  -> input image width
    height -> input image height

    This function applies the Sobel algorithm (edge ​​detection)
    to the input image stored in the "in" buffer
    and the result will be stored in the "out" buffer
*/
void Sobel(unsigned char* in, unsigned char* out, int width, int height) {
    unsigned char* lines[4];
    float Gx, Gy, G;
    unsigned char* outLine;

    int vertical[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int horizontal[3][3] = {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
    };

    for (int j = 0; j < height; j++) {
        outLine = out + j * width;

        // entry lines
        lines[0] = in + j * width;
        lines[1] = in + (j + 1) * width;
        lines[2] = in + (j + 2) * width;

        // Finding the gradient for each pixel
        //
        // Checks
        //   (These checks are made so as not to exceed the limits of the input image
        //   If we are on the first or last column, then we double this value)
        //
        // - (i >= 1) ? (i - 1) : 0
        // - (i < width - 1) ? (i + 1) : (width - 1)
        for (int i = 0; i < width; i++) {
            Gx = vertical[0][0] * lines[0][(i >= 1) ? (i - 1) : 0] + vertical[0][1] * lines[0][i] + vertical[0][2] * lines[0][(i < width - 1) ? (i + 1) : (width - 1)] +
                vertical[1][0] * lines[1][(i >= 1) ? (i - 1) : 0] + vertical[1][1] * lines[1][i] + vertical[1][2] * lines[1][(i < width - 1) ? (i + 1) : (width - 1)] +
                vertical[2][0] * lines[2][(i >= 1) ? (i - 1) : 0] + vertical[2][1] * lines[2][i] + vertical[2][2] * lines[2][(i < width - 1) ? (i + 1) : (width - 1)];

            Gy = horizontal[0][0] * lines[0][(i >= 1) ? (i - 1) : 0] + horizontal[0][1] * lines[0][i] + horizontal[0][2] * lines[0][(i < width - 1) ? (i + 1) : (width - 1)] +
                horizontal[1][0] * lines[1][(i >= 1) ? (i - 1) : 0] + horizontal[1][1] * lines[1][i] + horizontal[1][2] * lines[1][(i < width - 1) ? (i + 1) : (width - 1)] +
                horizontal[2][0] * lines[2][(i >= 1) ? (i - 1) : 0] + horizontal[2][1] * lines[2][i] + horizontal[2][2] * lines[2][(i < width - 1) ? (i + 1) : (width - 1)];
            G = sqrtf(Gx * Gx + Gy * Gy);
            if (G > 255)
                *(outLine + i) = 255;
            else
                *(outLine + i) = (unsigned int)G;
        }
    }
    return;
}

/*
    This function put the name on the input image(in)
    The signature will be created starting from startWidth and startHeigth
    The size of the signature is stored in "size"
    The signature is "ALEX C."
*/
void fillName(unsigned char* in, int startWidth, int width, int startHeigth, int size) {

    int* pix = (int*)malloc(10 * sizeof(int));

    letterA(in, startWidth, width, startHeigth, size, pix);
    letterL(in, startWidth + size * 6 + 5, width, startHeigth, size, pix);
    letterE(in, startWidth + 2 * (size * 6 + 5), width, startHeigth, size, pix);
    letterX(in, startWidth + 3 * (size * 6 + 5), width, startHeigth, size, pix);

    letterC(in, startWidth + 5 * (size * 6 + 5), width, startHeigth, size, pix);
    point(in, startWidth + 6 * (size * 6 + 5), width, startHeigth, size, pix);
}

void main() {
    // Input and output files for images
    FILE* inputImage;
    FILE* outputImage;

    // Input file open for reading
    if ((inputImage = fopen("tema_1920_1080.raw", "rb")) == NULL) {
        printf("Something went wrong, input file could not be opened!");
        exit(1);
    }
    // Output file open for writing
    if ((outputImage = fopen("tema_output.raw", "wb")) == NULL) {
        printf("Something went wrong, input file could not be opened!");
        exit(1);
    }

    // Image memory allocation
    unsigned char* inputBuffer = (unsigned char*)malloc(sizeof(unsigned char) * WIDTH * HEIGHT + PADDING);
    unsigned char* outputBuffer = (unsigned char*)malloc(sizeof(unsigned char) * WIDTH * HEIGHT + PADDING);

    // Reading the bytes from the input image
    unsigned int bytes = fread(inputBuffer, 1, WIDTH * HEIGHT, inputImage);

    // Check if the corresponding data in the input file has been read
    if (bytes != WIDTH * HEIGHT) {
        if (feof(inputImage))
            printf("End of file!\n");
        if (ferror(inputImage))
            printf("Error reading from file!\n");
        printf("Could not read enough bytes.\n");
        exit(1);
    }

    fclose(inputImage);

    // Fill padding(the last 2 lines) with the last line
    for (int i = 0; i < WIDTH; i++)
        *(inputBuffer + HEIGHT * WIDTH + i) = *(inputBuffer + (HEIGHT + 1) * WIDTH + i) = *(inputBuffer + (HEIGHT - 1) * WIDTH + i);

    // Application of the Sobel algoritm
    Sobel(inputBuffer, outputBuffer, WIDTH, HEIGHT);

    //Putting the signature on the image
    fillName(outputBuffer, 1700, WIDTH, 20, 4);

    // We save the results from the outputBuffer in the output file, which represents the final image
    fwrite(outputBuffer, 1, sizeof(unsigned char) * WIDTH * HEIGHT, outputImage);
    fclose(outputImage);

    // Free memory
    free(inputBuffer);
    free(outputBuffer);    
}

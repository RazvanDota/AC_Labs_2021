#include "letters.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Functie care coloreaza cu alb un grup de "size" coloane
    Se foloseste de valorile din pixels (sirul care comanda daca se pune alb sau nu)
    Daca in pixels gasim 0 nu schimbam culoarea, dar daca e 1 atunci sschimbam in alb
*/
void fillColumn(unsigned char* buffer, int widthPozition, int width, int startHeigth, int size, int* pixels) {

    for (int i = startHeigth; i < startHeigth + size * 9; i++) {
        if (pixels[(i - startHeigth) / size]) {
            for (int j = 0; j < size; j++)
                *(buffer + widthPozition + j + i * width) = 255;
        }
    }
}

//Functie care da niste valori sirului pix
void fillPix(int* pix, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9) {
    *pix = p1;
    *(pix + 1) = p2;
    *(pix + 2) = p3;
    *(pix + 3) = p4;
    *(pix + 4) = p5;
    *(pix + 5) = p6;
    *(pix + 6) = p7;
    *(pix + 7) = p8;
    *(pix + 8) = p9;
}

void letterA(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 1, 0, 0, 1, 1, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 0, 0, 1, 1, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth,size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

void letterL(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

void letterE(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 1, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 1, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 1, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

void letterX(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 1, 1, 1, 0, 0, 0, 1, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 0, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 1, 1, 1, 1, 1, 0, 0);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 1, 1, 1, 1, 1, 0, 0);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 0, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 0, 0, 0, 1, 1, 1);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

void letterC(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth, size, pix);
    fillPix(pix, 1, 1, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

void point(unsigned char* buffer, int startWidth, int width, int startHeigth, int size, int* pix) {
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    fillColumn(buffer, startWidth + size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 2 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 3 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 4 * size, width, startHeigth, size, pix);
    fillPix(pix, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    fillColumn(buffer, startWidth + 5 * size, width, startHeigth, size, pix);
}

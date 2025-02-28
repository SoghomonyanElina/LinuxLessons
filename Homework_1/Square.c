#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


float SquareofRec(float height, float width) {
    return height * width;
}

float SquareofTriangle(float base, float height) {
    return (base * height) / 2;
}

int main() {
    float heightofTriangle;
    float height0fSquare;
    float base;
    float width;
    printf("Please enter heigt of triangle: ");
    scanf("%f", &heightofTriangle);
    printf("Please enter base of triangle: ");
    scanf("%f", &base);
    printf("Please enter heigt of square: ");
    scanf("%f", &height0fSquare);
    printf("Please enter width of square: ");
    scanf("%f", &height0fSquare);
    pid_t pid = fork();
    if(pid == -1) {
        perror("Fail");
    }
    else if(pid == 0) {
        printf("Child process, calculate square of triangle\n");
        return  SquareofTriangle(base, heightofTriangle);
    }
    else {
        printf("Parent process, calculate square of rectangle\n");
        return SquareofRec(height0fSquare, width);
    }
}
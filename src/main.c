#include <stdio.h>

int main(void)
{
    const int HEIGHT = 256;
    const int WIDTH = 256;

    printf("P3\n%d %d\n255\n", WIDTH, HEIGHT);

    // Increment column
    for (int j = 0; j < HEIGHT; j++)
    {
        fprintf(stderr, "Scanlines remaining: %d\n", HEIGHT - j);

        for (int i = 0; i < WIDTH; i++)
        {
            double r = (double)i / (WIDTH - 1);
            double g = (double)j / (HEIGHT - 1);
            double b = 0.0;

            int ir = 255.999 * r;
            int ig = 255.999 * g;
            int ib = 255.999 * b;

            // Write out row
            printf("%d %d %d\n", ir, ig, ib);
        }
    }

    return 0;
}
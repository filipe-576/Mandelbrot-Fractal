#include <stdint.h>

void calculate_mandelbrot(unsigned char *buffer, int xres, int yres, double xmin, double xmax, double ymin, double ymax, int maxiter) 
{
    /* Precompute pixel width and height. */
    double dx = (xmax - xmin) / xres;
    double dy = (ymax - ymin) / yres;
    
    // double x, y; /* Coordinates of the current point in the complex plane. */
    // double u, v; /* Coordinates of the iterated point. */
    // double u2, v2;
    // int i, j; /* Pixel counters */
    // int k; /* Iteration counter */

    #pragma omp parallel for schedule(dynamic, 1)
    for (int j = 0; j < yres; j++) {
        double y = ymax - j * dy;
        
        for(int i = 0; i < xres; i++) {
            double u = 0.0;
            double v = 0.0;
            double u2 = 0.0;
            double v2 = 0.0;
            double x = xmin + i * dx;
            
            /* Iterate the point */
            int k;
            for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
                v = 2 * u * v + y;
                u = u2 - v2 + x;
                u2 = u * u;
                v2 = v * v;
            }
            
            /* compute pixel color and write it to file */
            unsigned long long pixel_index = ((unsigned long long)j * xres + i) * 3;
            
            if (k >= maxiter) {
                /* interior */
                buffer[pixel_index] = 0;
                buffer[pixel_index + 1] = 0;
                buffer[pixel_index + 2] = 0;
            }
            else {
                /* exterior */
                unsigned char color_factor = k % 256;
                
                buffer[pixel_index] = 64; // R
                buffer[pixel_index + 1] = 0; // G
                buffer[pixel_index + 2] = color_factor; // B
            }
        }
    }
}
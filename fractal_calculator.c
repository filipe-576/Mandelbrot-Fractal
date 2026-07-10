#include <stdint.h>

void calculate_mandelbrot(unsigned char *buffer, int xres, int yres, double xmin, double xmax, double ymin, double ymax, int maxiter) 
{
    // Pré-calcula a distância entre cada pixel no plano.
    double dx = (xmax - xmin) / xres;
    double dy = (ymax - ymin) / yres;

    // double x, y;  Coordinates of the current point in the complex plane. 
    // double u, v;  Coordinates of the iterated point. 
    // double u2, v2;
    // int i, j;  Pixel counters 
    // int k;  Iteration counter 

    // Paraleliza o laço externo (eixo Y), distribuindo as linhas dinamicamente entre as threads.
    #pragma omp parallel for schedule(dynamic, 1)
    for (int j = 0; j < yres; j++) {

        double y = ymax - j * dy; // Calcula a coordenada imaginária Y do plano para a linha atual.
        
        for(int i = 0; i < xres; i++) {
            double u = 0.0;
            double v = 0.0;
            double u2 = 0.0;
            double v2 = 0.0;
            double x = xmin + i * dx;  // Calcula a coordenada real X do plano para a coluna atual.
            
            // Itera a função f(z) = z^2 + c até o limite máximo de iterações 
            // ou até que o módulo do ponto ultrapasse 2
            int k;
            for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
                v = 2 * u * v + y;
                u = u2 - v2 + x;
                u2 = u * u;
                v2 = v * v;
            }
            
            // Calcula o índice linear para o pixel no array (cada pixel exige 3 bytes: R, G e B).
            unsigned long long pixel_index = ((unsigned long long)j * xres + i) * 3;
            
            if (k >= maxiter) {
                // Se atingiu o máximo de iterações sem escapar, colore o pixel de preto.
                buffer[pixel_index] = 0;
                buffer[pixel_index + 1] = 0;
                buffer[pixel_index + 2] = 0;
            }
            else {
                // Se escapou antes, a cor muda com base na velocidade que escapou, dependendo do número de iterações.
                unsigned char color_factor = k % 256;
                
                buffer[pixel_index] = 64;               // Vermelho (R)
                buffer[pixel_index + 1] = 0;            // Verde (G)
                buffer[pixel_index + 2] = color_factor; // Azul (B)
            }
        }
    }
}
# Mandelbrot-Fractal
Aplicação Gráfica do Fractal de Mandelbrot

## Windows
gcc .\fractal_calculator.c -shared -O3 -fopenmp -static -o mandelbrot.dll

## Linux
gcc fractal_calculator.c -shared -O3 -fopenmp -fPIC -o mandelbrot.dll
# Mandelbrot-Fractal
Aplicação Gráfica do Fractal de Mandelbrot utilizando Python & C

C - Responsável pelo processamento e pelo cálculo de cada píxel no plano, utilizando paralelismo via OpenMP para melhorar a performance.(fractal_calculator.c)
Python- Responsável pela interface para o usuário, configurando o fractal, alocando a matriz de imagem e renderizando graficamente o resultado utilizando a biblioteca matplotlib.(interface.py)

# Pré Requisitos:
Compilador GCC
Python 3.11

# Instalações das dependências:
pip install numpy matplotlib 

## Windows
gcc .\fractal_calculator.c -shared -O3 -fopenmp -static -o mandelbrot.dll

## Linux
gcc fractal_calculator.c -shared -O3 -fopenmp -fPIC -o mandelbrot.dll
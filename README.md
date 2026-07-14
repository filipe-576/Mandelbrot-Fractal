# Mandelbrot-Fractal
Aplicação Gráfica do Fractal de Mandelbrot utilizando Python & C

C - Responsável pelo processamento e pelo cálculo de cada píxel no plano, utilizando paralelismo via OpenMP para melhorar a performance.(fractal_calculator.c)
Python- Responsável pela interface para o usuário, configurando o fractal, alocando a matriz de imagem e renderizando graficamente o resultado utilizando a biblioteca matplotlib.(interface.py)

# Pré Requisitos:
Compilador GCC
Python 3.11

# Instalações das dependências:
pip install numpy matplotlib 

## Guia para compilação
Para somente compilar o código em C: `make all`

Para compilar o código em C e executar:
| Preset / Nome | Comando |
| --- | --- |
| Resolução baixa | `make low` 
| Resolução média | `make medium` 
| Resolução alta | `make high`  
| Absolute Cinema | `make cinema`  
| Seahorse Valley | `make SV` 
| Spirals | `make SP`
| Starfish | `make SF`
| Seahorse Valley Ultra | `make SU`

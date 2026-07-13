"""
Mandelbrot Fractal Viewer

Este script serve como interface gráfica principal que carrega 
a biblioteca em C para o cálculo matemático.

"""
import numpy as np
import matplotlib.pyplot as plt
import ctypes
import sys

if len(sys.argv) != 7:
    sys.exit(1)

try:
    args = []
    for i in range(1, 5):
        args.append(float(sys.argv[i]))

    for i in range(5, 7):
        args.append(int(sys.argv[i]))
except ValueError:
    print("Argumentos errados")
    sys.exit(1)

# Carrega a biblioteca dinâmica nativa compilada a partir de fractal_calculator.c
lib = ctypes.CDLL("./mandelbrot.dll")

# Configuração dos tipos de argumentos para garantir conversão correta de dados dinâmicos 
# do Python para os tipos estáticos definidos pelo código fonte C.
lib.calculate_mandelbrot.argtypes = [
    ctypes.POINTER(ctypes.c_ubyte),  # buffer: Ponteiro para o array de bytes
    ctypes.c_int,                    # xres: Resolução de largura em pixels
    ctypes.c_int,                    # yres: Resolução de altura em pixels
    ctypes.c_double,                 # xmin: Limite inferior do eixo real
    ctypes.c_double,                 # xmax: Limite superior do eixo real
    ctypes.c_double,                 # ymin: Limite inferior do eixo imaginário
    ctypes.c_double,                 # ymax: Limite superior do eixo imaginário
    ctypes.c_int                     # maxiter: Limite de iterações do escape
]

# A função C retorna void
lib.calculate_mandelbrot.restype = None

# Parâmetros que delimitam a janela do plano que será renderizada.
xmin, xmax = args[0], args[1]
ymin, ymax = args[2], args[3]

# Resolução base da imagem renderizada. 
max_iter = args[4]  # Quantidade máxima de iterações do cálculo do fractal (define os detalhes nas bordas).
base = args[5]
altura = int((base*(ymax-ymin)) / (xmax-xmin))

# Aloca e zera a memória da matriz da imagem usando Numpy para a resolução fornecida.
fractal_image = np.zeros((altura, base, 3), dtype=np.uint8)

# O Python passa o endereço do buffer por referência, 
# permitindo que o C preencha a matriz fractal_image sem realizar cópia desnecessária de memória.
lib.calculate_mandelbrot(
    fractal_image.ctypes.data_as(ctypes.POINTER(ctypes.c_ubyte)),
    base,
    altura,
    xmin,
    xmax,
    ymin,
    ymax,
    max_iter
)

# Utilização do Matplotlib para plotar a matriz Numpy na tela.
plt.imshow(fractal_image, extent=(xmin, xmax, ymin, ymax))
plt.title("Mandelbrot Fractal")
plt.show()

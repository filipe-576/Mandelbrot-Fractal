import numpy as np
import matplotlib.pyplot as plt
import ctypes 



lib = ctypes.CDLL("./mandelbrot.dll") 

lib.calculate_mandelbrot.argtypes = [
    ctypes.POINTER(ctypes.c_ubyte), 
    ctypes.c_int,                  
    ctypes.c_int,                  
    ctypes.c_double,               
    ctypes.c_double,                 
    ctypes.c_double,                 
    ctypes.c_double,                 
    ctypes.c_int                     
]

# A função C retorna void
lib.calculate_mandelbrot.restype = None

xmin, xmax = -2.0, 1.0
ymin, ymax = -1.5, 1.5

base = 800
altura = 600
max_iter = 100

fractal_image = np.zeros((altura, base, 3), dtype=np.uint8)


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


plt.imshow(fractal_image, extent=(xmin, xmax, ymin, ymax))
plt.title("Mandelbrot Fractal")
plt.show()
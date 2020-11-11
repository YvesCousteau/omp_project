
import ctypes

so_file = ('./omp_proj.so')

try:
	c_functions = ctypes.CDLL(so_file)
except Exception as e:
	print("Err, omp_proj.so doesnt exists, please run make.")
	exit(-1)
c_functions.project.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int] 
c_functions.project.restype =  ctypes.c_double


print("First test : Temps d’exécution en fonction de taille total de données (N*K)")
nthreads = 4
for x in xrange(10,1000):
	n = x
	k = x
	print("N={}, K={}, nthreads={}", n, k, nthreads)
res = c_functions.project(n, k, nthreads)

print("> "+str(res))
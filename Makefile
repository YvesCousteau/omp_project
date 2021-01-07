edit : omp_proj.so omp_proj

omp_proj.so : ProjetOMP.c
	gcc-10 -fPIC -shared -o omp_proj.so ProjetOMP.c -fopenmp

omp_proj : ProjetOMP.c
	gcc-10 -o omp_proj ProjetOMP.c -fopenmp

clean :
	rm omp_proj.so omp_proj

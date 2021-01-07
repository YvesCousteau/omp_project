
import ctypes
import csv
import math

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-t", "--test", type=int, help="select test to run [1, 2, 3, (10 for all)]")
parser.add_argument("-n", "--nthreads", type=int, help="# of Threads")
args = parser.parse_args()

if not args.nthreads:
	print("ERROR specify --nthreads")
	exit(-1)

so_file = ('./omp_proj.so')

try:
	c_functions = ctypes.CDLL(so_file)
except Exception as e:
	print("Err, omp_proj.so doesnt exists, please run make.")
	exit(-1)
c_functions.project.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
c_functions.project.restype =  ctypes.c_double


# Print iterations progress
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
	"""
	Call in a loop to create terminal progress bar
	@author: https://stackoverflow.com/a/34325723/13169250
	@params:
		iteration   - Required  : current iteration (Int)
		total       - Required  : total iterations (Int)
		prefix      - Optional  : prefix string (Str)
		suffix      - Optional  : suffix string (Str)
		decimals    - Optional  : positive number of decimals in percent complete (Int)
		length      - Optional  : character length of bar (Int)
		fill        - Optional  : bar fill character (Str)
		printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
	"""
	percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
	filledLength = int(length * iteration // total)
	bar = fill * filledLength + '-' * (length - filledLength)
	print(f'\r{prefix} |{bar}| {percent}% {suffix}', end = printEnd)
	# Print New Line on Complete
	if iteration == total:
		print()


########

if (args.test == 1 or args.test == 10):
	print("First test : Temps d’exécution en fonction de taille total de données (N*K)")
	printProgressBar(0, 100*100, prefix = 'Progress:', suffix = 'Complete', length = 50)

	iteration = 0

	k = 2**8
	for i in range(2, 16):
		n=2**i

		if (n == 10):
			res = [ ["N","K", "N*K", "nThreads", "Execution Time"] ]
		else:
			res = []

			iteration = iteration+1
			# print(f'N={n}, K={k}, nthreads={nthreads}')
			res.append( [n, k, n*k, args.nthreads, c_functions.project(n, k, args.nthreads)] )

			printProgressBar(iteration, 16-2-i, prefix = 'Progress for k fixed:', suffix = 'Complete', length = 50)

	# save subresults to file
	with open('nk_fixed-n_inc.csv', 'a+', newline='') as file:
		writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
		writer.writerows(res)
		file.close()

	n = 2**8
	for i in range(2, 16):
		k=2**i

		if (n == 10):
			res = [ ["N","K", "N*K", "nThreads", "Execution Time"] ]
		else:
			res = []

			iteration = iteration+1
			# print(f'N={n}, K={k}, args.nthreads={args.nthreads}')
			res.append( [n, k, n*k, args.nthreads, c_functions.project(n, k, args.nthreads)] )

			printProgressBar(iteration, 16-2-i, prefix = 'Progress for n fixed:', suffix = 'Complete', length = 50)

	# save subresults to file
	with open('nk_fixed-k_inc.csv', 'a+', newline='') as file:
		writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
		writer.writerows(res)
		file.close()



########

if (args.test == 2 or args.test == 10):
	print("Second test : Pour N*K fixé, la variation du temps d’exécution en fonction de la variation de K et N")
	printProgressBar(0, 100, prefix = 'Progress:', suffix = 'Complete', length = 50)

	res = [ ["N","K", "N*K", "nThreads", "Execution Time"] ]
	nk_product = 2**2 * 2**16
	for i in range(2, 16):
		n = 2**i
		k = 2**(16+2-i)
		# print(f'N={n}, K={k}, args.nthreads={args.nthreads}')
		res.append( [n, k, nk_product, args.nthreads, c_functions.project(n, k, args.nthreads)] )

		printProgressBar(i, 16-2-i, prefix = 'Progress:', suffix = 'Complete', length = 50)


	# save results to file
	with open('nk_fixed-n_and_k_inc.csv', 'a+', newline='') as file:
		writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
		writer.writerows(res)
		file.close()


if (args.test == 3 or args.test == 10):

	print("Third test : Pour N*K fixé, la variation du temps d’exécution en fonction de nombre de Threads")
	printProgressBar(0, 1000, prefix = 'Progress:', suffix = 'Complete', length = 50)

	res = [ ["N","K", "N*K", "nThreads", "Execution Time"] ]

	n = 2**2
	k = 2**16
	for nthreads in range(0, args.nthreads):
		# print(f'N={n}, K={k}, nthreads={nthreads}')
		res.append( [n, k, n*k, nthreads, c_functions.project(n, k, nthreads)] )

		printProgressBar(nthreads, args.nthreads, prefix = 'Progress for n < k:', suffix = 'Complete', length = 50)

	# save results to file
	with open('nk_fixed-time_by_nthreads-n_lt_k.csv', 'a+', newline='') as file:
		writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
		writer.writerows(res)
		file.close()

	n = 2**16
	k = 2**2
	for nthreads in range(0, args.nthreads):
		# print(f'N={n}, K={k}, nthreads={nthreads}')
		res.append( [n, k, n*k, nthreads, c_functions.project(n, k, nthreads)] )

		printProgressBar(nthreads, args.nthreads, prefix = 'Progress for n > k:', suffix = 'Complete', length = 50)

	# save results to file
	with open('nk_fixed-time_by_nthreads-n_gt_k.csv', 'a+', newline='') as file:
		writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
		writer.writerows(res)
		file.close()

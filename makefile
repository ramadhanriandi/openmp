.SILENT: $

CC = gcc

# make compile
compile: $
	echo "Compiling dijkstra_omp.c..."
	gcc -g -Wall -o ./output/dijkstra_omp ./src/dijkstra_omp.c -fopenmp \

# make run T={thread_count}
run: ./output/dijkstra_omp
	./output/dijkstra_omp ${T}\

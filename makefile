.SILENT: $

CC = gcc
FILE= djikstra-omp

# make compile
compile: $
	echo "Compiling ${FILE}..."
	gcc -g -Wall -o out/${FILE} src/${FILE}.c -fopenmp \
	echo "Successfully compiled ${FILE}! Executable at out/${FILE}."

# make run N={node_size} T={thread_count}
run: ./out/${FILE}
	./out/${FILE} ${N} ${T}\

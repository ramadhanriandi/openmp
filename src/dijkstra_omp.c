#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char** argv[]) {
  if (argc <= 3) {
    printf("Need 2 arguments. For file name, size, number of threads, and include serial or not\n");
    return 0;
  }

  int n_node, thread_count, use_serial;
  n_node = atoi(argv[1]);
  thread_count = atoi(argv[2]);
  use_serial = atoi(argv[3]);

  // seed from 13517029
  int seed = 29;

  clock_t t_serial;
  double t_start_parallel, t_end_parallel;
  int matrix_distance[n_node][n_node];
  int source;

  // final distance matrix which will be outputted
  int final_matrix_distance[n_node][n_node];
  for (int i = 0; i < n_node; i++) {
    fill_array(n_node, final_matrix_distance[i], -1);
  };

  // Matrix initialization for graph
  init_graph(n_node, matrix_distance, seed);

  if (use_serial == 1) {
    // START SERIAL DIJKSTRA ALGORITHM
    t_serial = clock();
    serial_dijkstra(n_node, &matrix_distance, &final_matrix_distance);
    t_serial = clock() - t_serial;

    double time_taken_serial = ((double)t_serial * 1000000) / (CLOCKS_PER_SEC);

    // PRINT RESULT OF SERIAL DIJKSTRA ALGORITHM
    printf("\n%s%2.f%s\n",
           "Time elapsed for serial dijkstra algorithm: ", time_taken_serial,
           " ms");
    // END OF SERIAL DIJKSTRA ALGORITHM
  } else if (use_serial == 0) {
    // START PARALLEL DIJKSTRA ALGORITHM USING OPENMP
    t_start_parallel = omp_get_wtime();
    if (thread_count <= 1) {
      serial_dijkstra(n_node, &matrix_distance, &final_matrix_distance);
    } else {
      #pragma omp parallel num_threads(thread_count)
      {
        openmp_dijkstra(n_node, &matrix_distance, &final_matrix_distance);
      }
    }
    t_end_parallel = omp_get_wtime();

    double time_taken_openmp = (t_end_parallel - t_start_parallel) * 1000000;

    // PRINT RESULT OF PARALLEL DIJKSTRA ALGORITHM
    printf("\n%s%2.f%s\n", "Time elapsed for OpenMP parallel dijkstra algorithm: ", time_taken_openmp, " ms");
    print_matrix_to_file(n_node, final_matrix_distance);
    // END OF PARALLEL DIJKSTRA ALGORITHM
  }

  return 0;
}

void openmp_dijkstra(int n_node, int (*matrix_distance)[n_node], int (*final_matrix_distance)[n_node]) {
  int k;
  int myRank = omp_get_thread_num();
  int thread_count = omp_get_num_threads();
  int result[n_node];

  for (k = myRank; k < n_node; k += thread_count) {
    fill_array(n_node, result, -1);
    dijkstra(n_node, matrix_distance, k, result);
    for (int i = 0; i < n_node; i++) {
      final_matrix_distance[k][i] = result[i];
    }
    printf("Thread %d | Node %d out of %d\n", myRank, k, n_node);
  }
}

void serial_dijkstra(int n_node, int (*matrix_distance)[n_node], int (*final_matrix_distance)[n_node]) {
  int k = 0;
  int result[n_node];

  while (k < n_node) {
    fill_array(n_node, result, -1);
    dijkstra(n_node, matrix_distance, k, result);
    for (int i = 0; i < n_node; i++) {
      final_matrix_distance[k][i] = result[i];
    }
    k++;
    printf("Serial | Node %d out of %d\n", k, n_node);
  }
}

void init_graph(int n_node, int (*matrix)[n_node], int seed) {
  for (int i = 0; i < n_node; i++) {
    for (int j = 0; j < n_node; j++) {
      if (i == j) {
        matrix[i][j] = 0;
      } else if (i < j) {
        int parity = rand() % seed;
        if (parity % 2 == 0) {
          matrix[i][j] = -1;
          matrix[j][i] = -1;
        } else {
          matrix[i][j] = parity;
          matrix[j][i] = parity;
        }
      }
    }
  }
}

void print_matrix(int n_node, int (*matrix)[n_node]) {
  for (int i = 0; i < n_node; i++) {
    for (int j = 0; j < n_node; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void fill_array(int n_node, int array[], int value) {
  for (int i = 0; i < n_node; i++) {
    array[i] = value;
  }
}

int is_visited(int n_node, int visited[], int checked_value) {
  int i = 0;

  while (i < n_node) {
    if (visited[i] == checked_value) {
      return 1;
    }
    i++;
  }

  return 0;
}

int find_alternative(int n_node, int visited[], int result[], int current_idx) {
  int min_alternative = 999;
  int choosen_idx = -1;
  for (int i = 0; i < n_node; i++) {
    if (is_visited(n_node, visited, i) == 0 && result[i] != -1) {
      if (min_alternative > result[i]) {
        min_alternative = result[i];
        choosen_idx = i;
      }
    }
  }
  return choosen_idx != -1 ? choosen_idx : current_idx;
}

void dijkstra(int n_node, int (*matrix)[n_node], int source, int result[]) {
  int visited[n_node];
  int global_min = 999;
  int path_cost = 0;
  int next_idx_pos = 0;
  int current_idx_pos = source;
  int i = 0;

  fill_array(n_node, visited, -1);

  while (i < n_node) {
    for (int j = 0; j < n_node; j++) {
      if (is_visited(n_node, visited, j) == 0) {
        if (j != current_idx_pos) {
          if (matrix[current_idx_pos][j] != -1) {
            if (result[j] == -1 || path_cost + matrix[current_idx_pos][j] < result[j]) {
              result[j] = path_cost + matrix[current_idx_pos][j];
              if (result[j] < global_min) {
                global_min = result[j];
                next_idx_pos = j;
              }
            }
          } else {
            if (result[j] != -1 && result[j] < global_min) {
              global_min = result[j];
              next_idx_pos = j;
            }
          }
        } else {
          if (result[j] == -1) {
            result[j] = 0;
          }
        }

      }
    }

    visited[i] = current_idx_pos;
    if (current_idx_pos != next_idx_pos) {
      current_idx_pos = next_idx_pos;
      path_cost = global_min;
    } else {
      current_idx_pos = find_alternative(n_node, visited, result, current_idx_pos);
      next_idx_pos = current_idx_pos;
      path_cost = result[current_idx_pos];
    }
    global_min = 999;
    i++;
  }
}

void print_solution(int n_node, int result[]) {
  printf("Vertex \t\t Distance from Source\n");
  for (int i = 0; i < n_node; i++)
    printf("%d \t\t %d\n", i, result[i]);
}

void print_matrix_to_file(int n_node, int (*matrix)[n_node]) {
  FILE * fp;
  /* open the file for writing*/
  fp = fopen ("../output/result.txt","w");

  for (int i = 0; i < n_node; i++) {
    for (int j = 0; j < n_node; j++) {
      fprintf(fp, "%d ", matrix[i][j]);
    }
    fprintf(fp, "\n");
  }

  /* close the file*/
  fclose (fp);
}
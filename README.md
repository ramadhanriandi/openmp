# OpenMP Dijkstra

## Petunjuk Penggunaan Program
1.  Jika program belum dikompilasi, lakukan perintah berikut pada terminal atau command prompt di folder root project.
    
    `make`

    yang berisi perintah berikut untuk kompilasi
    
    `gcc -g -Wall -o ./output/dijkstra_omp ./src/dijkstra_omp.c -fopenmp`

2.  Setelah berhasil dikompilasi, jalankan program dengan perintah berikut.

    `./output/dijkstra_omp <jumlah-node> <jumlah-thread> <0 atau 1>`
    
    Jika '0' maka dijkstra akan dijalankan secara parallel sedangkan jika '1' maka dijkstra akan dijalankan secara serial
    
## Pembagian Tugas
Berikut adalah pembagian tugas yang diterapkan.

| NIM | Nama | Pembagian Tugas | Kontribusi |
| ------ | ------ | ------ | ------ | 
| 13517029 | Reyhan Naufal Hakim | openmp integration, main, print_matrix_to_file, openmp_dijkstra | 50% |
| 13517080 | Mgs. Muhammad Riandi Ramadhan | makefile, time-elapsed counter, init_graph, dijkstra, fill_array, is_visited, find_alternative | 50% | 

## Laporan Pengerjaan
Berikut adalah laporan pengerjaan dari tugas ini.

### Deskripsi Solusi Parallel
Pada pengerjaan tugas ini, dilakukan proses pencarian jarak terpendek dari setiap node ke semua node lainnya.
Untuk mencari jarak terpendek dengan suatu source node tertentu, kita menggunakan algoritma dijkstra untuk melakukan penelusuran yang menghasilkan array yang berisi jarak terpendak source node tersebut ke semua node lainnya.
Untuk mendapatkan matriks yang berisi jarak terpendek dari setiap node ke semua node lainnya, algoritma dijkstra yang diterapkan pada setiap node dijalankan secara parallel dan setiap hasil array jarak terpendek dari algoritma tersebut akan disatukan menjadi sebuah matriks.
Kita menggunakan OpenMP untuk melakukan shared memory programming secara parallel. Dengan OpenMP, setiap thread dapat mengakses semua memory yang tersedia. 
Setelah graph berhasil di-generate menggunakan seed yang diberikan, dilakukan perhitungan waktu proses untuk serial dan parallel.
Serial menggunakan fungsi clock() sedangkan parallel menggunakan fungsi omp_get_wtime().
Agar program dapat bekerja secara parallel, diberikan sebuah OpenMP pragma yaitu `#pragma omp parallel num_threads(<thread_count>)`.

### Analisis Solusi yang Diberikan
Berdasarkan solusi yang digunakan, kita menghasilkan kinerja yang lebih ringan dengan melakukan parallelisasi data untuk ditangani oleh beberapa thread.
Hal ini dibuktikan dengan hasil pengujian di mana ketika dijkstra dijalankan secara parallel memiliki elapsed-time yang lebih kecil dibandingkan serial.
Untuk menghasilkan solusi yang lebih baik, dapat dilakukan dengan cara mengoptimasi algoritma Dijkstra yang telah dibuat.
Selain itu kita dapat mengalokasikan memori secara dinamis agar hasil pengerjaan menjadi lebih ringan. Solusi yang saat ini diterapkan belum menerapkan hal tersebut.
Kemampuan parallelisasi dapat meningkat seiring kemampuan mesin yang ditingkatkan sehingga jumlah thread yang optimal dapat lebih banyak.

### Jumlah Thread yang Digunakan
Kita menggunakan 2 thread karena disesuaikan dengan logical processor serta spesifikasi server yang digunakan. Penggunaan 2 thread mendukung kemampuan mesin sehingga kita mendapatkan hasil yang lebih optimal dibandingkan menggunakan jumlah thread lainnya seperti 4 atau 8.

### Pengukuran Kinerja untuk Tiap Kasus Uji Dibandingkan dengan Dijkstra Algorithm Serial
https://gitlab.informatika.org/reyhankim/openmpi/-/raw/master/screenshots/serial_100.png

https://gitlab.informatika.org/reyhankim/openmpi/-/blob/master/screenshots/parallel_100.png

### Analisis Perbandingan Kinerja Serial dan Parallel
Pada umumnya, kinerja program parallel akan menghasilkan kinerja yang lebih baik daripada program serial. Namun pada percobaan tugas ini, hasil yang didapat dari program parallel tidak lebih baik daripada program serial yang telah dibuat.
Kedua program menggunakan algoritma dijkstra yang sama namun perbedaaannya terletak pada bagaimana terdapat beberapa proses di program parallel dalam mengelola data.
Hasil yang lebih buruk ini dapat disebabkan oleh kesalahan algoritma MPI atau kurang cocoknya fitur MPI yang digunakan dalam pembuatan proses parallel.

Hasil contoh pengujian terhadap waktu elapsed:

Parallel 100 : 222.552 ms

Serial 100 : 185.857 ms

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
Serial 100 Node     : 226.588 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/serial_100.png)

Parallel 100 Node   : 119.251 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/parallel_100.png)

Serial 500 Node     : 129.956.783 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/serial_500.png)

Parallel 500 Node   : 64.253.794 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/parallel_500.png)

Serial 1000 Node    : 2.051.541.746 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/serial_1000.png)

Parallel 1000 Node  : 1.017.134.891 mikroseken (https://gitlab.informatika.org/reyhankim/openmp/-/blob/master/output/screenshot/parallel_1000.png)

Serial 3000 Node    : 

Parallel 3000 Node  : 

### Analisis Perbandingan Kinerja Serial dan Parallel
Berdasarkan pengukuran kinerja yang dilakukan untuk setiap kasus uji, dapat dianalisis sebagai berikut.
*  Untuk setiap kasus uji, program yang dijalankan secara parallel menghasilkan elapsed time yang lebih sedikit
*  Jumlah thread yang digunakan mepengaruhi hasil pengujian program yang dijalankan secara parallel
*  Berdasarkan beberapa kali percobaan, jumlah thread yang optimal pada server yang digunakan adalah 2 thread
*  Semakin banyak jumlah data yang digunakan, maka perbedaan kecepatan elapsed time parallel dan serial akan semakin besar 
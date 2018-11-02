# Tugas Jaringan Komputer IF3130
## Kelompok 02 K01
Anggota Kelompok  
-Kevin Andrian Liwinata - 13516118<br>
-Muhammad Azka Widyanto - 13516127<br>
-Teresa                 - 13516133<br>

### BAGIAN I - PETUNJUK PENGGUNAAN
1. Buka terminal, jalankan make
    ```sh
     make
    ```
2. Untuk membuat receiver, ketik
    ```sh
    ./recvfile <filename> <windowsize> <buffersize> <port>
    ```
    - <filename> : nama file output
    - <windowsize> : besar window size yang dipakai (RWS)
    - <buffersize> : besar buffer yang digunakan pada reveiver
    - <port> : port yang digunakan pada receiver
3. Untuk membuat sender, ketik
    ```sh
    ./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>
    ```
    - <filename> merupakan nama file yang akan dikirim
    - <windowsize> : besar window size yang dipakai (SWS)
    - <buffersize> : besar buffer yang digunakan pada sender
    - <port> : port yang digunakan pada receiver

### BAGIAN II - CARA KERJA SLIDING WINDOW
Program dibagi menjadi server.c dan client.c dengan memanfaatkan ADT yang diatur pada data.h. Fungsi yang digunakan adalah checkInt yang bertugas untuk memastikan apakah masukannya text atau bukan, generateCheckSum untuk membuat CheckSum, checkDataIntegrity untuk mengecek apakah CheckSumnya sama atau tidak serta clearCharBuffer untuk menngosongkan buffer.

### BAGIAN II - PEMBAGIAN TUGAS
1. Kevin Andrian Liwinata - server(receiver)
2. Teresa - client(sender)
3. Azka - socket + data.h






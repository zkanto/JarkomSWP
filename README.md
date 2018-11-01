# Tugas Jaringan Komputer IF3130
## Kelompok XX K01
Anggota Kelompok  
Kevin Andrian Liwinata - 13516118
Muhammad Azka Widyanto - 13516127
Teresa                 - 13516133

### BAGIAN I - PETUNJUK PENGGUNAAN
1. Buka terminal, jalankan make
    ```sh
    $ make
    ```
2. Untuk membuat receiver, ketik
    ```sh
    $ ./recvfile <filename> <windowsize> <buffersize> <port>
    ```
    - <filename> : nama file output
    - <windowsize> : besar window size yang dipakai (RWS)
    - <buffersize> : besar buffer yang digunakan pada reveiver
    - <port> : port yang digunakan pada receiver
3. Untuk membuat sender, ketik
    ```sh
    $ ./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>
    ```
    - <filename> merupakan nama file yang akan dikirim
    - <windowsize> : besar window size yang dipakai (SWS)
    - <buffersize> : besar buffer yang digunakan pada sender
    - <port> : port yang digunakan pada receiver

### BAGIAN II - CARA KERJA SLIDING WINDOW





#include <iostream>
#include <thread>
#include <vector>

int shared_variable = 0;

// Fungsi yang dijalankan oleh thread pertama
void thread_function_1() {
    for (int i = 0; i < 1000000; ++i) {
        shared_variable++;
    }
}

// Fungsi yang dijalankan oleh thread kedua
void thread_function_2() {
    for (int i = 0; i < 1000000; ++i) {
        shared_variable--;
    }
}

int main() {
    std::vector<std::thread> threads;

    // Membuat dua thread yang menjalankan fungsi thread_function_1 dan thread_function_2
    threads.emplace_back(thread_function_1);
    threads.emplace_back(thread_function_2);

    // Menunggu sampai kedua thread selesai
    for (auto& thread : threads) {
        thread.join();
    }

    // Program mencoba mencetak nilai akhir dari shared_variable tanpa sinkronisasi
    std::cout << "Nilai akhir dari shared_variable: " << shared_variable << std::endl;

    return 0;
}
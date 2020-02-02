#include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>

const char* passwd = "68486";

int main()
{
    char buffer[6];
    fgets(buffer, 6, stdin);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i { 0 }; i < 6; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (buffer[i] != passwd[i])
        {
            fprintf(stderr, "Mot de passe invalide !\n");
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end-start;
            std::cout << "Temps : " << elapsed.count() << "\n";
            return -1;
        }
    }

    printf("Bravo, c'est le bon mot de passe !\n");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Temps : " << elapsed.count() << "\n";
}

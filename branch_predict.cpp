#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <cstdint>

#include <emmintrin.h>
#include <immintrin.h>

#pragma GCC optimize("no-tree-vectorize") // Pas d'optimisations SIMD qui pourraient rendre les résultats moins explicites

#define TAILLE_PAGE 128

#define CLFLUSH(ptr) _mm_clflush(ptr)

double bench_cpu_speed = 3000; // MHz, initial guess at 3000 Mhz

__attribute__((constructor))
void init_benchmark()
{
    char buffer[4096];

    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    fread(buffer, 1, 4096, cpuinfo);
    fclose(cpuinfo);

    char* ptr = strstr(buffer, "cpu MHz");
    if (!ptr)
        return;

    while (!isdigit(*ptr))
        ++ptr;
    bench_cpu_speed = strtod(ptr, NULL);
    printf("CPU Speed : %.0f MHz\n", bench_cpu_speed);
}

#define BENCH_START() \
    uint64_t bench_start; \
    asm  volatile ("cpuid\n" \
                   "rdtsc\n" \
                   "shlq $32, %%rdx\n" \
                   "orq %%rax, %%rdx\n" \
                   "movq %%rdx, %0" \
                   :"=r"(bench_start):: "%rax", "%rbx", "%rcx", "%rdx"); \

#define BENCH_END() \
    ({     uint64_t bench_end; \
        asm  volatile ("rdtsc\n" \
                   "shlq $32, %%rdx\n" \
                   "orq %%rax, %%rdx\n" \
                   "movq %%rdx, %0\n" \
                   "cpuid" \
                   :"=r"(bench_end):: "%rax", "%rbx", "%rcx", "%rdx"); \
                   bench_end - bench_start;})

int main()
{
    const int taille = 32768;
    int data[taille];

    for (unsigned c = 0; c < taille; ++c)
        data[c] = rand() % 256;



    // std::sort(data, data + taille);



    BENCH_START();

    long long sum = 0;

    for (unsigned i = 0; i < 10000; ++i)
    {
        for (unsigned c = 0; c < taille; ++c)
        {
            if (data[c] >= 128)
                sum += data[c];
        }
    }

    uint64_t result = BENCH_END();
    printf("somme : %d\n", sum);

    double microsecs = result / bench_cpu_speed;
    printf("cycles : %llu (%f us)\n", result, microsecs);
}

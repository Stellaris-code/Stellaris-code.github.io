#ifndef BENCH_H_INCLUDED
#define BENCH_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <emmintrin.h>
#include <immintrin.h>

#pragma GCC optimize("no-tree-vectorize") // Pas d'optimisations SIMD qui pourraient rendre les résultats moins explicites

#define TAILLE_PAGE 128

#define CLFLUSH(ptr) _mm_clflush(ptr)

double bench_cpu_speed = 3000; // MHz

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

#endif // BENCH_H_INCLUDED

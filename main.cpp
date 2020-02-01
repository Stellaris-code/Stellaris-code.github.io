#include "bench.h"

#include <algorithm>
#include <windows.h>


#if 0
int main()
{
    int data[32768];

    for (unsigned c = 0; c < arraySize; ++c)
        data[c] = rand() % 256;

    // !!! With this, the next loop runs faster.
    std::sort(data, data + arraySize);

    BENCH_START();

    // Test
    long long sum = 0;

    for (unsigned i = 0; i < 100000; ++i)
    {
        // Primary loop
        for (unsigned c = 0; c < arraySize; ++c)
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
#else

__attribute__((aligned(TAILLE_PAGE)))
    uint8_t data[2 * TAILLE_PAGE]; // 2 pages mémoires pour tester 1 bit

uint64_t mean_cycles[2];

int test_bit(uint8_t valeur, int idx)
{
    uint64_t cycle_sum[2] = {0};
    const int run_count = 100;

    for (int run = 0; run < run_count; ++run)
    {
        for (int j = 0; j <= 1; ++j)
        {

            uint8_t donne_secrete = 0xAB;
            uint8_t* target_ptr = (uint8_t*)&donne_secrete;

                for(int k = 0; k < TAILLE_PAGE*2; ++k)
                    CLFLUSH(data +  k);

            uintptr_t index = ((valeur >> idx)&1)*TAILLE_PAGE;
            asm volatile ("movb %0, %%al" ::"m"(data[index]):"%rax");

            BENCH_START();
            asm volatile ("movq %0, %%rax\n" ::"m"(data[j*TAILLE_PAGE]):"%rax");
            cycle_sum[j] += BENCH_END();
        }
    }

    mean_cycles[0] = cycle_sum[0]/run_count;
    mean_cycles[1] = cycle_sum[1]/run_count;

    if (mean_cycles[0] > mean_cycles[1])
        return 1;
    else
        return 0;
}

int main()
{
    uint8_t valeur = 0xAB;

    printf("Actual value : 0x%x\n", valeur);

    uint8_t spec_val = 0;

    for (int i = 0; i < 8; ++i)
    {
        int bit = test_bit(valeur, i);
        printf("bit %d : %d (cycles : %d vs %d)\n", i, bit, mean_cycles[0], mean_cycles[1]);
        spec_val |= (bit << i);
    }
    printf("Speculated value : 0x%x\n", spec_val);
}


#endif

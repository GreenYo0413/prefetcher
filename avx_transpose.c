#include "avx_transpose.h"
#include <immintrin.h>
#include <omp.h>
#include <stdio.h>
#define PU_LOW_HALF_128BIT 0x20
#define PU_HIGH_HALF_128BIT 0x31
void transpose(int *src, int *dst, int w, int h)
{
    if(!__builtin_cpu_supports("avx2")) {
        printf("CPU is not support avx2\n");
    }
    for (int x = 0; x < w; x += 8) {
        for (int y = 0; y < h; y += 8) {
            register __m256i I0 = _mm256_loadu_si256((__m256i *)(src + (y + 0) * w + x));
            register __m256i I1 = _mm256_loadu_si256((__m256i *)(src + (y + 1) * w + x));
            register __m256i I2 = _mm256_loadu_si256((__m256i *)(src + (y + 2) * w + x));
            register __m256i I3 = _mm256_loadu_si256((__m256i *)(src + (y + 3) * w + x));
            register __m256i I4 = _mm256_loadu_si256((__m256i *)(src + (y + 4) * w + x));
            register __m256i I5 = _mm256_loadu_si256((__m256i *)(src + (y + 5) * w + x));
            register __m256i I6 = _mm256_loadu_si256((__m256i *)(src + (y + 6) * w + x));
            register __m256i I7 = _mm256_loadu_si256((__m256i *)(src + (y + 7) * w + x));

            register __m256i T0 = _mm256_unpacklo_epi32(I0, I1);
            register __m256i T1 = _mm256_unpacklo_epi32(I2, I3);
            register __m256i T2 = _mm256_unpacklo_epi32(I4, I5);
            register __m256i T3 = _mm256_unpacklo_epi32(I6, I7);
            register __m256i T4 = _mm256_unpackhi_epi32(I0, I1);
            register __m256i T5 = _mm256_unpackhi_epi32(I2, I3);
            register __m256i T6 = _mm256_unpackhi_epi32(I4, I5);
            register __m256i T7 = _mm256_unpackhi_epi32(I6, I7);

            I0 = _mm256_unpacklo_epi64(T0, T2);
            I1 = _mm256_unpackhi_epi64(T0, T2);
            I2 = _mm256_unpacklo_epi64(T1, T3);
            I3 = _mm256_unpackhi_epi64(T1, T3);
            I4 = _mm256_unpacklo_epi64(T4, T6);
            I5 = _mm256_unpackhi_epi64(T4, T6);
            I6 = _mm256_unpacklo_epi64(T5, T7);
            I7 = _mm256_unpackhi_epi64(T5, T7);

            T0 = _mm256_permute2x128_si256(I0, I4, PU_LOW_HALF_128BIT);
            T1 = _mm256_permute2x128_si256(I1, I5, PU_LOW_HALF_128BIT);
            T2 = _mm256_permute2x128_si256(I2, I6, PU_LOW_HALF_128BIT);
            T3 = _mm256_permute2x128_si256(I3, I7, PU_LOW_HALF_128BIT);
            T4 = _mm256_permute2x128_si256(I0, I4, PU_HIGH_HALF_128BIT);
            T5 = _mm256_permute2x128_si256(I1, I5, PU_HIGH_HALF_128BIT);
            T6 = _mm256_permute2x128_si256(I2, I6, PU_HIGH_HALF_128BIT);
            T7 = _mm256_permute2x128_si256(I3, I7, PU_HIGH_HALF_128BIT);

            _mm256_storeu_si256((__m256i *)(dst + ((x + 0) * h) + y), T0);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 1) * h) + y), T1);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 2) * h) + y), T2);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 3) * h) + y), T3);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 4) * h) + y), T4);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 5) * h) + y), T5);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 6) * h) + y), T6);
            _mm256_storeu_si256((__m256i *)(dst + ((x + 7) * h) + y), T7);
        }
    }
}

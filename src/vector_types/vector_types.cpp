#pragma GCC target("arch=skylake") // avx (+avx2) required

typedef float float8_t __attribute__ ((vector_size (8 * sizeof(float))));
typedef double double4_t __attribute__ ((vector_size (4 * sizeof(double))));
typedef int intv8_t __attribute__ ((vector_size (8 * sizeof(int))));

constexpr float8_t float8_0 = {0,0,0,0,0,0,0,0};

// elementwise minimum
inline float8_t min8(float8_t x, float8_t y) {
    return x < y ? x : y;
}

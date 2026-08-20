#include <stdio.h>
#define BIT_MASK(bit) (1 << (bit))

static inline int set_bit(int *reg, int n)
{
    *reg = *reg | BIT_MASK(n);
    return *reg;
}

static inline int clear_bit(int *reg, int n)
{
    *reg = *reg & ~BIT_MASK(n);
    return *reg;
}


int main()
{
    int reg = 10;
    int *p = &reg;
    printf("%d\n", set_bit(p, 2));

    printf("%d\n", clear_bit(p, 3));

    return 0;
}
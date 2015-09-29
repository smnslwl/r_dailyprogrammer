#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long
product_of_array(const long *array, unsigned n)
{
    long prod = 1;
    for (long i = 0; i < n; ++i)
        prod *= array[i];
    return prod;
}

void
display_result(long number, const long *array, unsigned n)
{
    printf("%ld = ", number);
    for (long i = 0; i < n; ++i) {
        printf("%ld", array[i]);
        if (i < n - 1)
            printf(" * ");
    }
    printf("\n");
}

int
is_vampire_number(long number, long *array, unsigned n)
{
    int counter[10] = {0};
    do counter[number % 10]++; 
        while (number /= 10); 

    int factor;
    for (long i = 0; i < n; ++i) {
        factor = array[i];
        do counter[factor % 10]--; 
            while (factor /= 10);
    }

    for (long i = 0; i < 10; ++i)
        if (counter[i] != 0)
            return 0;
    return 1;
}

int
main(int argc, char *argv[])
{
    unsigned digits = (argc > 2) ? atoi(argv[1]) : 1;
    unsigned num_factors = (argc > 2) ? atoi(argv[2]) : 1;
    unsigned factor_digits = digits / num_factors;
    long start = pow(10, factor_digits - 1);
    long end = pow(10, factor_digits) - 1;

    long factors[num_factors];
    for (long i = 0; i < num_factors; ++i)
        factors[i] = start;

    int product;
    while (factors[0] <= end) {
        product = product_of_array(factors, num_factors);
        if (is_vampire_number(product, factors, num_factors))
            display_result(product, factors, num_factors);
        
        factors[num_factors - 1]++;
        
        for (unsigned i = num_factors - 1; i > 0; --i)
            if (factors[i] > end) {
                factors[i - 1] += 1;
                for (unsigned j = i; j < num_factors; ++j)
                    factors[j] = factors[j - 1];
            }
    }
    
    exit(EXIT_SUCCESS);
}


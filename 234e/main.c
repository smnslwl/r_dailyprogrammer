#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long long ulong;

ulong
product_of_array(const ulong *array, unsigned n)
{
    ulong prod = 1;
    for (unsigned i = 0; i < n; ++i)
        prod *= array[i];
    return prod;
}

void
display_result(ulong number, const ulong *array, unsigned n)
{
    printf("%lld = ", number);
    for (unsigned i = 0; i < n; ++i) {
        printf("%lld", array[i]);
        if (i < n - 1)
            printf(" * ");
    }
    printf("\n");
}

int
is_vampire_number(ulong number, ulong *array, unsigned n)
{
    int counter[10] = {0};
    do counter[number % 10]++;
        while (number /= 10); 

    int factor;
    int trailing_zeroes = 0;
    for (unsigned i = 0; i < n; ++i) {
        factor = array[i];
        if (factor % 10 == 0)
            trailing_zeroes++;
        do counter[factor % 10]--; 
            while (factor /= 10);
    }
    
    if (trailing_zeroes > 1)
        return 0;

    for (long i = 0; i < 10; ++i)
        if (counter[i] != 0)
            return 0;
    return 1;
}

int
main(int argc, char *argv[])
{
    unsigned digits = (argc > 1) ? atoi(argv[1]) : 2;
    unsigned num_factors = (argc > 2) ? atoi(argv[2]) : 2;
    unsigned factor_digits = digits / num_factors;
    ulong nstart = pow(10, digits - 1);
    ulong nend = pow(10, digits) - 1;
    ulong start = pow(10, factor_digits - 1);
    ulong end = pow(10, factor_digits) - 1;

    ulong factors[num_factors];
    for (unsigned i = 0; i < num_factors; ++i)
        factors[i] = start;

    ulong product;
    int total = 0;
    while (factors[0] <= end) {
        product = product_of_array(factors, num_factors);
        
        if (product >= nstart && product <= nend)
            if (is_vampire_number(product, factors, num_factors)) {
                display_result(product, factors, num_factors);
                total++;
            }
        
        factors[num_factors - 1]++;
        
        for (unsigned i = num_factors - 1; i > 0; --i)
            if (factors[i] > end) {
                factors[i - 1] += 1;
                for (unsigned j = i; j < num_factors; ++j)
                    factors[j] = factors[j - 1];
            }
    }
    
    printf("Found %d %d-digit vampires made of %d %d-digit fangs each\n", 
           total, digits, num_factors, factor_digits);

    exit(EXIT_SUCCESS);
}


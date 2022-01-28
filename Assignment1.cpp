#include <vector>
#include <iostream>
#include <cstring>
#include <chrono>
#include <cmath>
#include <thread>

// Function Declarations
void PrimeFinder(long long n);
void PrimeFinderInRange(long long low, long long high, long long sqrt_of_n);

const long long n = 100000000; // Finding primes up to n
std::vector<char> prime (n + 1, 1); // stores whether index is prime or composite

// Helpful Function
long long closestMultiple(long n, long x)
{
    if (x > n)
        return x;
    
    n = n + x / 2;
    n = n - (n%x);
    return n;
}

void PrimeFinder(long long n)
{
    // Made because required values for assignment are count, sum and 10 largest primes.
    std::vector<long long> return_values;

    /* First we find all the primes between 2 and the sqrt of n
       This provides a starting place for finding all the primes between sqrt of n and n*/
    long long sqrt_of_n = floor(sqrt(n));
    // Utitlizing the Sieve of Eratosthenes we identify which numbers between 2 and sqrt(n) are not prime
    for (long long p = 2 ; p*p<=sqrt_of_n; p++)
    {
        if (prime[p])
        {
            for (long long i=p*p; i<=sqrt_of_n; i+=p)
                prime[i] = 0;
        }
    }

    // Going to partition the remaining numbers into 8 equal parts
    long long partition_indices[9];
    long long partition_amount = ceil((n  - sqrt_of_n) / 8);

    for (int i = 0; i < 8; i++)
        partition_indices[i] = sqrt_of_n + (partition_amount * i);
    partition_indices[8] = n;

    // Assigned the threads their workload
    std::vector<std::thread> threads;
    for (int i = 0; i < 8; i++)
    {
        threads.push_back(std::thread(PrimeFinderInRange, partition_indices[i] + 1, partition_indices[i+1], sqrt_of_n));
    }

    for (auto &th : threads) {
        th.join();
    }
}

// With all the primes less than sqrt(n), it is possible to segment the
// the array above sqrt(n) and find the primes there in separate threads.
void PrimeFinderInRange(long long low, long long high, long long sqrt_of_n)
{
    for (long long p = 2; p<=sqrt_of_n; p++)
    {
        if (prime[p])
        {
            // Need to find the first mulitple of the prime in the section as the starting point
            long long i = closestMultiple(low, p);
            if (i < low)
                i += p;

            for (; i <= high; i+=p)
            {
                prime[i] = 0;
            }
        }
    }

}

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();

    PrimeFinder(n);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    std::cout << "execution time: " << (elapsed.count() * 1e-9) << " seconds, ";

    long long sum = 0;
    long long prime_count = 0;
    std::vector<long long> top_ten_primes;

    for (int p=n; p>=2; p--)
    {
        if (prime[p])
        {
            sum+=p;
            prime_count++;
            if (prime_count < 11)
                top_ten_primes.push_back(p);
        }
    }

    std::cout << "primes found: " << prime_count << ", sum of all primes found: " << sum << std::endl;

    std::cout << "Top ten maximum primes: ";

    for (int i = 9; i >= 0; i--)
        std::cout << top_ten_primes[i] << " ";
}
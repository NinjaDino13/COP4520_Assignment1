# COP4520_Assignment1

## Running the Program
To run the program, open up a command prompt window. From there enter:
```
g++ Assignment1.cpp -o Assignment1.exe
```
This will compile the code and create the .exe file for it, named Assignment1.exe. Once this has been created, enter the following in to the command line:
```
./Assignment1.exe
```
This will run the code within the command prompt.

## Documentation
### Proof of Correctness
This algorithm is based off of the Sieve of Eratosthenes. This algorithm works by taking the very first prime, 2, and marking off every multiple of that prime less than some specified number *n* as composite. It would then go to the next number not marked as composite, in this case 3, and mark off it's multiples. It will repeat this process for every number less than *n*.

A key thing about composite numbers is that they are guaranteed to have a factor less than or equal to their square root. This algorithm utilizes this property by first finding all the primes less than or equal to the square root of *n*. Using these primes, we can find their multiples across the range from square root of *n* to *n*. Since all the composite numbers here are guaranteed to have a multiple within these values, all of the composites will be marked off, leaving just the primes.

## Efficiency
The above alogrithm is not a very quick process: for large numbers, the range between them and their square roots can be several thousands time the size of the range between 2 and the square root. In order to make this faster, this program splits up the range between the square root of *n* and *n* into 8 equal sections, and then uses 8 threads, each one being assigned a range to find primes in.

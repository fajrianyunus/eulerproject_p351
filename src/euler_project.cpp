//============================================================================
// Author      : Fajrian Yunus
// Description : solution for http://projecteuler.net/problem=351
//============================================================================

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <math.h>
using namespace std;

//list of all positive prime numbers up (in ascending sequence) up to 100,000,000
long primes[] = {
	#include "primes.txt"
};
int primes_length;

map<long, bool> primes_map;

bool is_prime(long n) {
	if (primes_map.find(n) == primes_map.end()) {
		return false;
	} else {
		return true;
	}
}

void prepare_primes_map() {
	int primes_array_size = sizeof(primes);
	int int_size = sizeof(long);
	primes_length = primes_array_size/int_size;
	for (int i = 0 ; i < primes_length ; i++) {
		primes_map.insert(pair<long, bool>(primes[i], true));
	}
}


//calculating gcd
//copied from http://en.wikipedia.org/wiki/Binary_GCD_algorithm and modified here and there
unsigned long gcd(unsigned long u, unsigned long v)
{
  // simple cases (termination)
  if (u == v)
    return u;
  if (u == 0)
    return v;
  if (v == 0)
    return u;

  // look for factors of 2
  if (~u & 1) // u is even
    if (v & 1) // v is odd
      return gcd(u >> 1, v);
    else // both u and v are even
      return gcd(u >> 1, v >> 1) << 1;
  if (~v & 1) // u is odd, v is even
    return gcd(u, v >> 1);

  // reduce larger argument
  if (u > v)
    return gcd((u - v) >> 1, v);
  return gcd((v - u) >> 1, u);
}

//this is an implementation of euler's totient function
//copied from https://gist.github.com/1635288 and slightly modified here and there
long phi(const long n)
{
  // Base case
  if ( n < 2 )
    return 1;

  // Lehmer's conjecture
  if ( is_prime(n) )
    return n-1;

  // Even number?
  if ( n & 1 == 0 ) {
    long m = n >> 1;
    return !(m & 1) ? phi(m)<<1 : phi(m);
  }

  // For all primes ...
  for ( std::map<long, bool>::iterator p = primes_map.begin();
        p != primes_map.end() && p->first <= n;
        ++p )
  {
    long m = p->first;
    if ( n % m != 0 ) continue;

    // phi is multiplicative
    long o = n/m;
    long d = gcd(m, o);
    return d==1? phi(m)*phi(o) : phi(m)*phi(o)*d/phi(d);
  }

  return 0l;
}

//the main logic
//copied from the work of my friend (sally ang), with some optimization
long hex_orchid(long n) {
	long result = 0;
//	TODO: execute the following instructions in threads, rather than in traditional loop
//	each iteration is quite independent from the other iteration, aside from adding a value to "result" variable
	for (long i = 2 ; i <= n ; i++) {
		result += i - phi(i);
		if (i % 100000 == 0) {
			cout << "just finishing i == " << i << endl;
		}
	}
	result = 6 * result;
	return result;
}

int main() {

	prepare_primes_map();
	time_t before_execution = time(NULL);
	long result = hex_orchid(100000000l);
	time_t after_execution = time(NULL);
	cout << "time difference is " << after_execution - before_execution << " seconds" << endl;
	cout << "result == " << result << endl;
	return 0;
}

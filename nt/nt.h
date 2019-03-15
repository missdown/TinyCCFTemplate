//
// Created by miss on 19-1-13.
//

#ifndef ACM_TEMPLATE_NT_H
#define ACM_TEMPLATE_NT_H

#include <cmath>
#include <vector>

#include <algorithm>


float Sqrt(float x)
{
    float a = x;
    unsigned int i = *(unsigned int *)&x;
    i = (i + 0x3f76cf62) >> 1;
    x = *(float *)&i;
    x = (x + a / x) * 0.5;
    return x;
}


float invSqrt(float x)
{
    float xhalf = 0.5 * x;
    int i = *(int*)&x; // get bits for floating value
    i = 0x5f375a86 - (i >> 1); // gives initial guess  Or use 0x5f3759df
    x = *(float*)&i; // convert bits back to float
    x = x * (1.5 - xhalf * x * x); // Newton step
    return x;
}

// Calculate (a * b) % c  long long a, b;
long long mult_mod(long long a, long long b, long long c) {
    a %= c;
    b %= c;
    long long ret = 0;
    while (b) {
        if (b & 1) {
            ret += a;
            ret %= c;
        }
        a <<= 1;
        if (a >= c) {
            a %= c;
        }
        b >>= 1;
    }
    return ret;
}


int Factrial(int n) {
    if (n == 0 || n == 1) return 1;
    else return Factrial(n - 1) + Factrial(n - 2);
}

unsigned long long FactialLM(int n) {
    unsigned long long FactrialList[100];
    FactrialList[0] = FactrialList[1] = 1;
    for (int i = 2; i <= n; ++i) {
        FactrialList[i] = FactrialList[i - 1] + FactrialList[i - 2];
    }
    return FactrialList[n];
}


/*
 * Print All of the Permutation
 *
 * For Example:
 *      list[] = {1, 2, 3}
 *
 *      Output = 1, 2, 3; 1, 3, 2; 2, 1, 3; 2, 3, 1; 3, 1, 2; 3, 2, 1
 */

void PrintPermutation(int list[], int num)
{
    do {
        for (int i = 0; i < num; ++i) {
            std::cout << list[i];
        }
        std::cout << std::endl;
    }  while(std::next_permutation(list, list + num));
//    std::fill(list, list + num , 0);
}


#ifdef debug

    struct fruit {
    string name;
    int price;
    friend bool operator < (const fruit &f1, const fruit& t) {
        return f1.price < f2.price;
    }
};

struct cmp {
    bool operator () (const fruit &f1, const fruit &f2)
    {
        return f1.price > f2.price;
    }
};
#endif

// O(sqrt(n))
bool isPrime(int n) {
    if (n <= 1) return false;
    int sqr = (int)sqrt((double) n);
    for (int i = 0; i < sqr; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// i Maybe out of range, Be careful.
bool isPrime2(int n) {
    if (n <= 1) return false;
    for (int i = 0; i * i < n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// FindPrime O(nlognlogn)
void Find_Prime(int n, std::vector<int> *prime_list) {
    std::vector<bool> num_list(static_cast<unsigned long>(n + 1), false);
    for (int i = 2; i < n + 1; ++i) {
        if (num_list[i] == false) {
            prime_list->push_back(i);
            for (int j = i * 2; j < n + 1; j += i) {
                num_list[j] = true;
            }
        }
    }
}


namespace FactorFactors {
    struct factor {
        int x, cnt;
    };

    template<typename T>
    void FindFF(T n) {
        std::cout << n << "=";
        std::vector<int> prime;
        std::vector<factor> result;
        Find_Prime((int) sqrt((double) n), &prime);
        for (int i = 0; i < prime.size(); ++i) {
            if (n % prime[i] == 0) {
                factor fac{prime[i], 0};
                while (n % prime[i] == 0) {
                    fac.cnt++;
                    n /= prime[i];
                }
                result.push_back(fac);
            }
        }
        if (static_cast<int>(result.size()))
            for (auto &i: result) {
                std::cout << i.x << "^" << i.cnt << " ";
            }
        else
            std::cout << n;
        std::cout << std::endl;
    };
}


// Calculate a^b%m  divide
long long binaryPow(long long a, long long b, long long m) {
    if (b == 0)
        return 1;
    if (m == 1)
        return 0;
    while (a >= m) {
        a %= m;
    }
    if (b & 1)
        return a * binaryPow(a, b - 1, m) % m;
    else {
        long long mul = binaryPow(a, b / 2, m);
        return mul * mul % m;
    }
}

// Calculate a^b%m  divide
long long binaryPow2(long long a, long long b, long long m) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = ans * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}

int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

int lcm(int a, int b)  // lcm = a*b/gcd(a, b)
{
    return a * b / gcd(a, b);
}


class ExGcd {
public:

    /* Assume a*(x + s1) + b*(y - s2) = gcd
     *
     * ax + by = gcd
     * So a * s1 = b * s2
     * s1 / s2 = b / a = (b / gcd) / (a / gcd)
     * x' = x + (b/gcd)*K  K -> Z
     * y' = y - (a/gcd)*K  K -> Z
     */

    void PrintAllResult(int a, int b, int &x, int &y, int K = 0) {
        int gcd = exGcd(a, b, x, y);
//        std::cout << x << " " << y << std::endl;
//        x = (x%(b/gcd) + (b/gcd)) %(b/gcd);  // x <  0
//        y = (y%(a/gcd) - (a/gcd)) %(a/gcd);  // y < 0
        std::cout << x + (b / gcd) * K << " " << y - (a / gcd) * K << std::endl;
    }


    /*
     * Calculate ax + by = c  c -> Z
     *
     * { x' = x + (b/gcd) * K = (c*x0)/gcd + (b/ gcd) * K
     * { y' = y - (a/gcd) * K = (c*y0)/gcd - (a/ gcd) * K
     *
     */

    void EqualC(int a, int b, int c, int &x, int &y, int K = 0) {
        int x0 = x, y0 = y;
        int gcd = exGcd(a, b, x, y);
        std::cout << c * x0 / gcd + (b / gcd) * K << " " << c * y0 / gcd - (a / gcd) * K << std::endl;
    }

    /*
     * Calculate ax )= c(mod m)  just like (a - b) % m = 0
     *  m >= 1
     */

    void EqualMode(int a, int c, int m, int &x, int K) {
        if (c % gcd(a, m))
            std::cout << "No answer" << std::endl;
        else
            std::cout << x + m / gcd(a, m) * K << std::endl;
    }

    /*
     * Calculate (b / a) % m
     *
     * If (a * b) % m == 1 then we call a, b is m's inverse elements;
     * Usage: (b * a) % m  = ( ( b % m ) * (a % m) ) % m
     * However (b / a) % m  != ( ( b % m ) / (a % m) ) % m
     * We tryed to find x which can let [(b / a) % m == (b * x) % m ] equation established
     *
     * a*x )= 1(mode m)
     */
    int CalculateDivisionMode(int a, int b, int m) {
        if (gcd(a, m) == 1) {
            int ie = CalculateInversElements(a, m);
            return (b * ie) % m;
        } else
            return (b % (a * m)) / a;
    }


private:
    /*
     * Calculate a*x1 + b*y1 = gcd(a, b)
     *
     * b*x2 + (a%b)*y2 = gcd(b, a%b)
     * gcd(a, b) = gcd(b, a%b) ; a*x1 + b*y1 = b*x2 + (a%b)*y2 ; a%b = a - (a // b)*b
     * a*x1 + b*y1 = a*y1 + b*(x2-(a//b)*y2)
     * Result:
     * {x1 = y2
     * {y1 = (x2 - (a//b)*y2)
     */

    int exGcd(int a, int b, int &x, int &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int g = exGcd(b, a % b, x, y);
        int temp = x;
        x = y;
        y = temp - a / b * y;
        return g;
    }


    /*
     * Calculate inverse elements by using exGcd
     */

    int CalculateInversElements(int a, int m) {
        int x, y;
        exGcd(a, m, x, y);  // ax + my = 1
        return (x % m + m) % m;
    }

    /*
     * Calculate inverse elements by using Fermat's little theorem
     *
     * Condition: m is prime
     *            a != K*m   K -> Z
     * a^(m - 1) = 1(mod m)
     * a*a^(m - 2) = 1(mod m)
     * So a^(m - 2) %m is the inverse elements(pow mod) of (a % m)
     */

    long long int CalculateInversElements2(int a, int m) {
        if (!isPrime(m))
            std::cerr << "WARNING: m isn't prime" << std::endl;
        if (!(m % a))
            std::cerr << "WARNING: a = " << a / m << "* m" << std::endl;
        return binaryPow2(a, m - 2, m);
    }

};


class Combination {
    using ll = long long;
public:

    /*
     * Calculate C(m, n)
     *
     * Condition n < 67 AND m < 33
     * C(m, n) = C(m , n - 1) + C(m - 1, n - 1)
     */
    ll CMethod1(ll n, ll m) {
        if (m == 0 || m == n) return 1;
        return CMethod1(n - 1, m) + CMethod1(n - 1, m - 1);
    }

    /*
     * Calculate C(m, n)
     *
     * Condition n < 62 AND m < 31
     * O(m)
     */
    ll CMethod2(ll n, ll m) {
        ll ans = 1;
        for (ll i = 1; i <= m; i++) {
            ans = ans * (n - m + i) / i;  // Care that put mul before division
        }
        return ans;
    }

    /*
     * Calculate C(m, n)
     *
     * Print All result in a Vector
     */
    ll res[67][67] = {0};

    void calC() {
        int n = 60;

        for (int i = 0; i <= n; ++i) {
            res[i][0] = res[i][i] = 1; // Init Edge Condition
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i / 2; ++j) {
                res[i][j] = res[i - 1][j] + res[i - 1][j - 1];
                res[i][i - j] = res[i][j]; // C(i, i - j) = C(i, j)
            }
        }
    }

    ll calC2(ll n, ll m) {
        if(m == 0 || m == n) return 1;
        if(res[n][m] != 0) return res[n][m];
        return res[n][m] = calC2(n - 1, m) + calC2(n - 1, m - 1);
    }



    /*
     * Calculate C(m, n) % p
     *
     * Method 1
     * Print All result in a Vector
     *
     * Condition: m <= n <= 1000
     */
    int resCMode[1010][1010] = {0};
    int CalCMode10(int n, int m , int p) {
        if(m == 0 || m == n) return 1 ; // C(n, 0) = C(n, n) = 1
        if(resCMode[n][m] != 0) return resCMode[n][m];
        return resCMode[n][m] = (CalCMode10(n - 1, m, p) + CalCMode10(n - 1, m - 1, p)) % p;
    }

    void CalCMode11(int n, int m, int p) {

        for (int i = 0; i <= n; ++i) {
            resCMode[i][0] = resCMode[i][i] = 1;
        }

        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i / 2; ++j) {
                resCMode[i][j] = (resCMode[i - 1][j] + resCMode[i - 1][j - 1]) % p;
                resCMode[i][i - j] = resCMode[i][j]; // C(i, i - j) = C(i, j)
            }
        }
    }

    /*
     * Method 2
     * Condition m <= n <= 10^6
     *
     * O(klogn)
     */
    long long int CalCMode2(int n, int m, int p) {
        long long int ans = 1;
        std::vector<int> prime;
        Find_Prime(n + 1, &prime);

        // Ergodic All prime which < n
        for (int i = 0; i < prime.size() && prime[i] <= n; i++) {
            // Calculate C(n, m)
            int c = cal(n, prime[i]) - cal(m, prime[i]) - cal(n - m, prime[i]);
            ans = ans * binaryPow2(prime[i], c, p) % p; // prime[i]^c % p
        }
        return ans;
    }

    /*
     * Method 3 Lucas
     * Condition m <= n <= 10^18
     *           p must be prime
     * O(logn)
     * Best Method to solve p <= 10^5
     *
     * m = m0*p^0 + m1*p^1 + ... + mk*p^k
     * n = n0*p^k + n1*p^1 + ... + nk*p^k
     *
     * Lucas: C(m, n) = C(m0, n0) * C(m1, n1) * ... * C(mk, nk) mod p
     *
     */

    long long int Lucas(int n, int m , int p) {
        if(m == 0) return 1;
        return CMethod2(n % p, m % p) * Lucas(n / p, m / p, p) % p;
    }

private:

    // Calculate How many FactorFactors p in n!
    int cal(int n, int p = 5) {
        int ans = 0;
        while (n) {
            ans += n / p;
            n /= p;
        }
        return ans;
    }

    int cal2(int n, int p = 5) {
        if (n < p) return 0;
        return n / p + cal2(n / p, p);
    }
};

#endif //ACM_TEMPLATE_NT_H

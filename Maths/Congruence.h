#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

namespace math {
	namespace priv {
		struct p { int b, e; };

		int _mcd(int a,int b) {
			int r = a % b;
			if (r == 0) {
				return b;
			}
			else {
				return _mcd(b, r);
			}
		}

		int _bezout(int a, int b,std::vector<int>& v) {
			int p = a / b;
			int r = a % b;
			if (r == 0) {
				return b;
			}
			else {
				v.push_back(p);
				return _bezout(b, r,v);
			}
		}
	}

	typedef std::vector<priv::p> Decomposition;

	// GCD: Greatest Common Divisor
	int mcd(int a, int b) {
		if (a > b) {
			return priv::_mcd(a, b);
		}
		else {
			return priv::_mcd(b, a);
		}
	}

	// LCM: Least Common Multiple
	int mcm(int a, int b) {
		return a * b / mcd(a, b);
	}

	// Solve mcd(a,b)= a*c + b*d for c and d
	void bezout(int a, int b, int& c, int& d) {
		std::vector<int>v;
		if (a > b) {
			priv::_bezout(a, b, v);
			c = 0, d = 1;
			for (int i = v.size() - 1; i >= 0; i--) {
				int cn = c, dn = d;
				c = d;
				d = -dn * v[i] + cn;
			}
		}
		else {
			priv::_bezout(b, a, v);
			d = 0, c = 1;
			for (int i = v.size() - 1; i >= 0; i--) {
				int cn = c, dn = d;
				d = c;
				c = -cn * v[i] + dn;
			}
		}

	}

	// decompose n product of primes
	//	base	|	exponent
	//	p1		e1
	//	...		...
	//	pn		en
	Decomposition decompose(int n) {
		Decomposition dec;
		int p = 2;
		
		while (p<=n) {

			if (n % p == 0) {
				dec.push_back({ p,0 });
				while (n % p == 0) {
					n /= p;
					dec.back().e++;
				}
			}
			p++;
		}
		return dec;
	}

	// number of coprimes under n
	// phi(n)
	int totient(int n) { 
		int div = 1;
		Decomposition dec = decompose(n);
		for (int i = 0; i < dec.size(); i++) {
			div *= (dec[i].b - 1) * pow(dec[i].b, dec[i].e - 1);
		}
		return div;
	}

	// inverse of a number mod(m)
	// a^-1 mod(m)
	int inverse(int a, int m) {
		int u, v;
		if (mcd(a, m) != 1) {
			std::cout << "the number and mod must be coprimes\n";
			return -1;
		}
		bezout(m, a, u, v);
		return v;
	}

	// solve ax=b (mod m)
	std::vector<int> solve(int a, int b, int m) {
		int d = mcd(a, m);
		if (b % d != 0) {
			std::cout << "There is no solution \n";
			return {};
		}

		int an = a / d, bn = b / d, mn = m / d;
		int u, v;
		bezout(mn, an, u, v);
		int alpha = v * bn % m;

		std::vector<int> sol;
		for (int i = 0; i < d; i++) {
			sol.push_back(alpha + i * mn);
		}
		return sol;
	}
	
	// solve equation
	// a1*x = b1 (mod m1)
	// ...
	// an*x = bn (mod mn)
	std::vector<int> solve(std::vector<int>&a, std::vector<int>&b, std::vector<int>& m) {
		return{};
	}
}
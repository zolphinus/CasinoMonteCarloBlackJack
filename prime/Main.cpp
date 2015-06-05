#include <iostream>
#include <cmath>
using namespace std;

void outputPrime(short, short);

int main() {

	// your code here

	short num_test;
	cin >> num_test;

	short m, n;

	for(short i = 0; i < num_test; i++){
		cin >> m;
		cin >> n;
		outputPrime(m, n);
		std::cout << std::endl << std::endl;


	}


	return 0;
}


void outputPrime(short m, short n){
	for(m; m < n+1; m++){
		short max_test = ceil(sqrt(m));
		bool isPrime = true;
		for(short i = 2; i < max_test + 1; i++){
			if(m % i == 0){
				isPrime = false;
				break;
			}
		}

		if(isPrime){
			std::cout << m << std::endl;
		}

	}
}

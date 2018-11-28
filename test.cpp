#include<iostream>
#include<string>

int main(){
	int i1, i2;
	std::string s1, s2;

	std::cin >> i1;
	std::cin >> i2;

	std::cin >> s1;
	std::cin >> s2;

	std::cout << "Total inputs: " << i1 << "\nIterations: " << i2 << std::endl;
	std::cout << s1 << "--->" << s2 << std::endl;

	return 0;
}

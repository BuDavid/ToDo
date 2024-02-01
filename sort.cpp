#include <iostream>
#include <vector>

void sort_by_prior(int prior, std::vector<int>& vec) {
	int i = 0;
	int j = 0;

	while (j < vec.size() && i < vec.size()) {
		while (vec[i] == prior) {
			i++;
			if (i >= vec.size()) {
				return;
			}
		}
		j = i;
		while (vec[j] != prior) {
			j++;
			if (j >= vec.size()) { 
				return; 
			}
		}
		std::swap(vec[j], vec[i]);
		i++;
	}
}

int main() {
	std::vector<int> vec = {1, 3, 2, 3, 1, 2, 1, 1, 3, 2};
	sort_by_prior(3, vec); 
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << ' ';
	}
	std::cout << std::endl;
}




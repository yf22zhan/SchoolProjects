#include <iostream>
using namespace std;

// Descending quicksort
void sort(int array[], int low, int high){
	int i = low, j = high;
	int tmp;
	int pivot = array[low + (high - low) / 2];

	while(i <= j){
		while(array[i] > pivot)
			i++;
		while(array[j] < pivot)
			j--;
		if(i <= j){
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}

	if(low < j)
    	sort(array, low, j);
    if(i < high)
    	sort(array, i, high);
}

int main(int argc, char** argv){
	int num_of_denominations;
	int denominations[10] = {0};
	int coefficients[10] = {0};
	int total;

	cin >> num_of_denominations;

	// If read fails, output "Impossible"
	if(!cin){
		cout << "Impossible" << endl;
		return 0;
	}

	// Read in denominations
	// If read fails, output "Impossible"
	for(int i = 0; i < num_of_denominations; i++){
		cin >> denominations[i];

		if(!cin){
			cout << "Impossible" << endl;
			return 0;
		}
	}

	cin >> total;

	// If read fails, output "Impossible"
	if(!cin){
		cout << "Impossible" << endl;
		return 0;
	}

	// If num_of_denominations == 0, exit
	if(num_of_denominations == 0){
		if(total == 0){
			return 0;
		}else{
			cout << "Impossible" << endl;
			return 0;
		}
	}

	// Sort array into descending order
	sort(denominations, 0, num_of_denominations - 1);

	// Determine coefficients for each denomination
	for(int i = 0; i < num_of_denominations; i++){
		if(total >= denominations[i]){
			coefficients[i] = total / denominations[i];
			total = total % denominations[i];
		}
	}

	// If unable to find a combination, output "Impossible"
	// Else, list the combination and omit "0 x denomination"
	if(total != 0){
		cout << "Impossible" << endl;
		return 0;
	}else{
		for(int i = 0; i < num_of_denominations; i++){
			if(coefficients[i] != 0){
				cout << coefficients[i] << " x " << denominations[i] << endl;
			}
		}
	}

	return 0;
}
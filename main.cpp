#include <iostream>

// Function to print the array
void printArray(int arr[],int size){
	for(int i = 0; i < size; i++){
		std::cout<<arr[i]<<", ";
	}// end for
	std::cout<<" "<<std::endl;
}// end printArray


// Function to swap two elements
void swap(int &firstIndex, int &secondIndex){
	int temp = firstIndex;
	firstIndex = secondIndex;
	secondIndex = temp;
}// end swap


// Implement the insertion sort
void insertionSort(int arr[],int size){
	int i = 1; // i starts at the second element so that it can compare with its predecessor
	int j;
	int iComparisons = 0;
	int iSwaps = 0;
	
	for(i; i < size; i++){
		int currentElement = arr[i];
		j = i - 1; // j is the left element of i
		iComparisons++;

		while(j >= 0 && arr[j] > currentElement){
			arr[j+1] = arr[j];
			iSwaps++;
			j = j - 1;
			iComparisons++;
		}// end while
		arr[j+1] = currentElement;
	}//end for

	std::cout<<"Insertion sort for "<<size<<" elements: "<<std::endl;
	std::cout<<"Comparisons: "<<iComparisons<<std::endl;
	std::cout<<"Swaps: "<<iSwaps<<std::endl;
}// end insertionSort


// Implement the Heap Sort
// Turn the array into a max heap
void heapify(int arr[], int size, int i, int &comparisons, int &swaps){
	int largest = i;
	int leftChild = 2 * i + 1;
	int rightChild = 2* i + 2;

	// if the leftChild is larger, it becomes the current largest element
	if(leftChild < size && arr[leftChild] > arr[largest]){
		comparisons++;
		largest = leftChild;
	}// end if

	// if the rightChild is larger, it becomes the current largest element
	if(rightChild < size && arr[rightChild] > arr[largest]){
		comparisons++;
		largest = rightChild;
	}// end if

	// if the current root is not the largest, swap it with the largest element
	if(largest != i){
		swaps++;
		swap(arr[i],arr[largest]);
		heapify(arr, size, largest, comparisons, swaps);
	}// end if
}// end heapify

void heapSort(int arr[],int size){
	int comparisons = 0;
	int swaps = 0;
	// First create the max heap by using the heapify function which starts at the non-leaf node
	// non-leaf node is obtained by (n/2) - 1 where n is the heap size
	
	for(int i = (size / 2) - 1; i >= 0; i--){
		heapify(arr, size, i, comparisons, swaps);
	}// end for

	for(int i = size - 1; i >= 0; i--){
		swap(arr[0],arr[i]);
		swaps++;
		heapify(arr, i , 0, comparisons, swaps);
	}// end for

	std::cout<<"Heap sort for "<<size<<" elements: "<<std::endl;
	std::cout<<"Comparisons: "<<comparisons<<std::endl;
	std::cout<<"Swaps: "<<swaps<<std::endl;
}// end heapSort


// Implement the quick sort by choosing the rightmost element as the pivot
void quickSort(int arr[], int startIndex, int endIndex,int &comparisons, int &swaps) {

    if (startIndex < endIndex) {        
	// Choosing the rightmost element as the pivot
        int pivot = arr[endIndex];
        int i = (startIndex - 1);  // i is the pivot index while j is the scanning index

	// Paritioning process
        for (int j = startIndex; j <= endIndex - 1; j++) {
            comparisons++;
          if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++;
       		}// end if
    	}// end for

        swap(arr[i + 1], arr[endIndex]);
        swaps++;

        int returnPivot = i+1;  // Index of the pivot returned by the partitioning process

        quickSort(arr, startIndex, returnPivot - 1,comparisons, swaps);
        quickSort(arr, returnPivot + 1, endIndex,comparisons, swaps);
    }// end if
}// end quickSort


int main(){
	int quickSortComparisons = 0;
	int quickSortSwaps = 0;
	int arraySizes[] = {100,1000,5000,10000};

	for(int i = 0; i < sizeof(arraySizes)/sizeof(arraySizes[0]);i++){
		std::cout<<std::endl;

		// Create random arrays
		int* arr = new int[arraySizes[i]];
		
		for(int j = 0; j < arraySizes[i]; j++){
			arr[j] = rand() % arraySizes[i] + 1;
		}// end for

		// Copy the array for the insertion sort to be performed so that the other sorting algorithms can use the original array and not the modified array by the Insertion sort
		int* insertionArray = new int[arraySizes[i]];
		std::copy(arr, arr + arraySizes[i], insertionArray);
		std::cout<<std::endl;

		// Copy the array for the quicksort to be performed so that it can use the original array and not the modified array by the other sorting algorithms
		int* quicksortArray = new int[arraySizes[i]];
                std::copy(arr,arr + arraySizes[i], quicksortArray);

		// Insertion sort
		insertionSort(insertionArray, arraySizes[i]);
		std::cout<<std::endl;

		// Heap sort
		heapSort(arr,arraySizes[i]);
		std::cout<<std::endl;	

		// Quick sort
		std::cout<<"Quicksort for "<<arraySizes[i]<<" elements"<<std::endl;
		quickSort(quicksortArray,0,arraySizes[i] - 1,quickSortComparisons, quickSortSwaps);
		std::cout<<"Comparisons: "<<quickSortComparisons<<std::endl;
		std::cout<<"Swaps: "<<quickSortSwaps<<std::endl;
		std::cout<<std::endl;
		
		// Printing the result for 100 and 1000 elements
		if(arraySizes[i] == 100 || arraySizes[i] == 1000){
           		std::cout<<std::endl;
            		std::cout<<"Sorted result for "<<arraySizes[i]<<" elements using insertionSort"<<std::endl;
            		printArray(insertionArray,arraySizes[i]); // heap sort
            		std::cout<<std::endl;

			std::cout<<"Sorted result for "<<arraySizes[i]<<" elements using heapSort"<<std::endl;
			printArray(arr,arraySizes[i]);
			std::cout<<std::endl;

			std::cout<<"Sorted result for "<<arraySizes[i]<<" elements using quickSort"<<std::endl;
			printArray(quicksortArray,arraySizes[i]);
			std::cout<<std::endl;
       		 }	
	}// end for
	return 0;
}// end main

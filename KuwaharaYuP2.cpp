//============================================================================
// Name        : KuwaharaYuP2.cpp
// Author      : Yu Kuwahara
//============================================================================

#include "stdafx.h"
#include <iostream>
using namespace std;

//=============FUNCTION PROTOTYPES============================================

// Task 1
int * generateAndFillArray(int & size);
void displayArray(const int *arr, int size);

// Task 2
int * copyArray(const int *arr, int size);

// Task 3
void selectionSortAscendingTheEven(int arr[], int size);
void bubbleSortDescendTheOdd(int *arr, int size);

// Task 4
void splitAnArray(const int *originalArray, int originalSize, int ** oddArray, int &numOdd, int ** evenArray, int &numEven);

// Task 5
int * mergeArrays(const int *firstArray, int firstSize, const int* secondArray, int secondSize);

//=======MAIN=================================================================

int main()
{
	int genArraySize = 0; // Declare a variable to indicate a size of the first array
	int evenSize = 0; // a size of even elements in an array
	int oddSize = 0; // a size of odd elements in an array

	int *generatedArray = nullptr; // Define a pointer variable and intialize it with the value "nullptr"
	int *copiedArray = nullptr; // a copy of the first array
	int *evenArray = nullptr; // an even sorted array from the copy
	int *oddArray = nullptr; // an odd sorted array from the copy
	int *newArray = nullptr; // an evenodd sorted array from the copy
	int *mergedArray = nullptr; // a merged array from the generated and the evenodd sorted

	// Task 1
	cout << "Task 1: " << endl;
	generatedArray = generateAndFillArray(genArraySize); // Create an array from the first function
	cout << "You generated an array: ";
	displayArray(generatedArray, genArraySize); // Display the generated array
	cout << endl;

	// Task 2
	cout << "Task 2: " << endl;
	copiedArray = copyArray(generatedArray, genArraySize); // Create a copy of the generated array from the copy function
	cout << "Original array: ";
	displayArray(generatedArray, genArraySize); // Display the generated array
	cout << "Copied array: ";
	displayArray(copiedArray, genArraySize); // Display the copied array
	cout << endl;

	// Task 3
	cout << "Task 3: " << endl;
	selectionSortAscendingTheEven(copiedArray, genArraySize); // Create an array for sorted even numbers and unchanged odds
	bubbleSortDescendTheOdd(copiedArray, genArraySize); // Create an array for sorted odd numbers and unchanged evens
	cout << "Sorted array: ";
	displayArray(copiedArray, genArraySize); // Display the sorted array
	cout << endl;

	// Task 4
	cout << "Task 4: " << endl;
	splitAnArray(copiedArray, genArraySize, &evenArray, evenSize, &oddArray, oddSize);

    // Task 5
	cout << "Task 5: " << endl;
	mergedArray = mergeArrays(generatedArray, genArraySize, copiedArray, genArraySize);
	displayArray(mergedArray, genArraySize + genArraySize);

	delete[] generatedArray; // Free the dynamically allocated array in Task 1
	delete[] copiedArray; // Free the dynamically allocated array in Task 2
	delete[] newArray; // Free the dynamically allocated array in Task 4

	return 0;
}

//===========FUNCTION DEFINITIONS=============================================

// This function generates and fills an array
// Use "&" to declare the variable, "size", as a reference
int * generateAndFillArray(int & size)
{
	int *arr = nullptr; // "arr" is an array to hold the size and numbers entered by the user

	// Ask a user for a size of an array within 1-10
	cout << "Please enter the size of your array (1 through 10): ";
	cin >> size;

	// Error check to see if the user typed a number within the range
	// Do not stop until the user types valid numbers
	while (size < 1 || size > 10)
	{
		cout << "Please enter a valid number: ";
		cin >> size;
		cin.ignore(); // Clear the input buffer in the event of the invalid input
	}

	arr = new int[size]; // Dynamically allocate the size by using "new"

	// Ask the user for numbers within 1-100 to store them in the array
	cout << "Please enter " << size << " numbers within 1 through 100: ";
	for (int i = 0; i < size; i++) // Store all the numbers by for loop
	{
		cin >> arr[i];
		while (arr[i] < 1 || arr[i] > 100) // Error check again
		{
			cout << "Please enter a valid number: ";
			cin >> arr[i];
			cin.ignore(); // Clear the input buffer in the event of the invalid input
		}
	}

	return arr; // Return to where the function was called
}

// This function displays generated arrays in functions 
void displayArray(const int *arr, int size)
{
	cout << "["; // Display the array like [1 2 3 4 5 ]
	for (int i = 0; i < size; i++) // Print all the numbers with for loop
	{
		cout << arr[i] << " "; 
	}
	cout << "]" << endl; // No need to return at the end since this is a void function

	return;
			
}

// This function generates a copy of the generated array by the user
int * copyArray(const int *arr, int size)
{
	int *copy = nullptr; // Define a pointer variable and intialize it 

	copy = new int[size]; // Dynamically allocate the size

	for (int i = 0; i < size; ++i) 
	{
		copy[i] = arr[i]; // Assign the content of arr[i] to that of copy[i]
	}

	return copy; // Return to where the function was started
}

// This function sorts only even elements in the array to ascend the order
void selectionSortAscendingTheEven(int arr[], int size)
{
	for (int i = 0; i < size - 1; i += 2) // Check all the even elements to ascend
	{
		int minIndex = i; 
		for (int j = i + 2; j < size; j += 2) // Find the minimum even element in the array
		{
			if (arr[j] < arr[i])
				minIndex = j; 
		}
		int tempVal = arr[minIndex]; 
		arr[minIndex] = arr[i]; 
		arr[i] = tempVal; // Update the minimum even element
	}

	return;

}

// This function sorts only odd elements in the array to descend the order
void bubbleSortDescendTheOdd(int *arr, int size)
{
	bool swapped = true; // Exit condition   
	while (swapped == true) // Repeat the below statement until it is done swapping
	{
		swapped = false;
		for (int i = 1; i < size - 1; i += 2) // Start with 1 since it is sorting odd elements
		{
			if (arr[i] < arr[i + 2]) // Compare the two elements next to each other to descend
			{
				int tempVal = arr[i];
				arr[i] = arr[i + 2];
				arr[i + 2] = tempVal; // Update the maximum odd element
				swapped = true;
			}
		}
	}
	
	return;

}

// This function split the new array into 2 arrays
void splitAnArray(const int *originalArray, int originalSize, int ** oddArray, int &numOdd, int ** evenArray, int &numEven)
{
	// Set size of even and odd array
	if (originalSize % 2 == 1) // When the size of array is odd
	{
		numEven = originalSize / 2 + 1; // Add 1 since division takes the floor of the quotient. e.g. (5 / 2 == 2) but 0, 2, 4 are indices
		numOdd = originalSize / 2;
	}
	else // When the size of array is even
	{
		numEven = originalSize / 2;
		numOdd = originalSize / 2;
	}

	// Dynamically allocate even and odd arrays based on found sizes
	*oddArray = new int[originalSize];
	*evenArray = new int[originalSize];

	for (int i = 1; i < originalSize; i += 2) // Place odd elements into odd array in odd indices
		(*oddArray)[i] = originalArray[i];

	for (int i = 0; i < originalSize; i += 2) // Place even elements into even array in even indices
		(*evenArray)[i] = originalArray[i];

	// Display the 3 arrays
	cout << "Original array: ";
	displayArray(originalArray, originalSize); // Display the copied array

	cout << "Even Array: [";
	for (int i = 0; i < originalSize; i += 2) // Print the array
	{
		cout << (*evenArray)[i] << " "; // Dereference since it is pointer-to-pointer
	}
	cout << "]\n";

	cout << "Odd Array: [";
	for (int i = 1; i < originalSize; i += 2) // Start with 1 since it is odd sorted array
	{
		cout << (*oddArray)[i] << " "; // Deference since it is pointer-to-pointer
	}
	cout << "]\n" << endl;

	return;

}

// This function merges the original array and evenodd sorted array and shows all the three arrays
int * mergeArrays(const int * firstArray, int firstSize, const int * secondArray, int secondSize)
{
	int mergedSize = firstSize + secondSize;

	// Dynamically allocated the merged array
	int *tempArray = new int[firstSize + secondSize];

	// Input values from firstArray into front of tempArray
	for (int i = 0; i < firstSize; ++i)
		tempArray[i] = firstArray[i];

	// Input values from second Array behind the values from firstArray
	for (int i = 0; i < secondSize; ++i)
		tempArray[i + firstSize] = secondArray[i];

	return tempArray;

}
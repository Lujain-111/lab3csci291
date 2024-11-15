#include <stdio.h>
#include <stdbool.h>

// Function to check if the position is valid within the array
bool isValid(const int arr[], int length, int pos) {
    // Returns true if position is within valid index range (1 to length-1)
    return (pos >= 1 && pos < length);
}

// Function to remove an element at a given position in the array
void remove_element(int arr[], int *length, int pos) {
    // Check if the position is valid
    if (!isValid(arr, *length, pos)) {
        printf("Invalid index. Cannot remove the element at index %d.\n", pos);
        return;
    }

    // Shift all elements after the removed element to the left
    for (int i = pos; i < *length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    // Decrease the array length
    (*length)--;

    // Print the array after removing the element
    printf("Array after removing element at index %d:\n", pos);
    for (int i = 0; i < *length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to insert a new element at a specified position in the array
void insert_element(int arr[], int *length, int pos, int value) {
    // Check if the position is valid
    if (!isValid(arr, *length, pos)) {
        printf("Invalid index. Cannot insert the element at index %d.\n", pos);
        return;
    }

    // Shift elements to the right to make space for the new element
    for (int i = *length; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert the new value at the specified position
    arr[pos] = value;

    // Increase the array length
    (*length)++;

    // Print the array after insertion
    printf("Array after inserting %d at index %d:\n", value, pos);
    for (int i = 0; i < *length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to reshape a 1D array into a 2D array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    // Check if the total elements in 1D array match the required size for the 2D array
    if (length != nRows * nCols) {
        printf("Error: The 1-D array size (%d) does not match the required size (%d) for a %d x %d matrix.\n", length, nRows * nCols, nRows, nCols);
        return;
    }

    // Reshape the array into the 2D matrix (column-major order)
    int index = 0;
    for (int col = 0; col < nCols; col++) {
        for (int row = 0; row < nRows; row++) {
            arr2d[row][col] = arr[index++];
        }
    }

    // Print the reshaped 2D array
    printf("2-D array (column-major order):\n");
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }
}

// Function to transpose a matrix (flip rows and columns)
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    // Transpose the matrix
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }

    // Print the transposed matrix
    printf("Transpose of the matrix:\n");
    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }
}

// Function to check if there are duplicate elements in the array
bool found_duplicate(int arr[], int length) {
    // Nested loop to check all pairs for duplicate values
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true; // Duplicate found
            }
        }
    }
    return false; // No duplicates found
}

int main() {
    // Initialize a 1D array and define its length
    int arr[6] = {10, 20, 30, 40, 50, 0};
    int length = 6;

    // Print the original array
    printf("Original array:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Insert a new element (80) at index 2
    insert_element(arr, &length, 2, 80);

    // Remove the element at index 3
    remove_element(arr, &length, 3);

    // Initialize another 1D array and reshape it into a 2D array
    int arr1d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int length1d = 12;
    int nRows = 3;
    int nCols = 4;
    int arr2d[3][4];
    reshape(arr1d, length1d, nRows, nCols, arr2d);

    // Define a 3x4 matrix and transpose it
    int mat[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
    int mat_transp[4][3];
    trans_matrix(3, 4, mat, mat_transp);

    // Check if there are any duplicates in the array with duplicates
    int arr_with_duplicates[] = {1, 2, 3, 4, 5, 3};
    if (found_duplicate(arr_with_duplicates, 6)) {
        printf("Duplicate found in the array.\n");
    } else {
        printf("No duplicates found in the array.\n");
    }

    return 0;
}

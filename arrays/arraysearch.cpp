//Требующийся функционал программы:
//1). Создание массива случайных элементов заданного в интерфейсе размера.
//2). Функции поиска, вставки и удаления по случайному массиву.
//3). Создание упорядоченного массива заданного в интерфейсе размера.
//4). Функции поиска, двоичного поиска, вставки и удаления из упорядоченного массива.

#include <bits/stdc++.h>
#include <cstdlib>


const int MAX_LENGTH = 1000000;


void printArray(int* array, int length) {  
    std::cout << "[ ";
    for (int i = 0; i < length; i++) std::cout << array[i] << ", ";
    std::cout << "]\n";
}


void printColumnArray(int* array, int length) {  
    for (int i = 0; i < length; i++) std::cout << array[i] << "\n";
}


int getRandomNumber(void) {
   return std::rand(); 
}


void randomiseArray(int* array, int length) {
    if (length < 1 ) throw std::invalid_argument("Array length less then 1\n");
    
    while (length > 0) array[--length] = getRandomNumber(); 
}


int searchInArray (int value, int* array, int length) { // returns index of element
    while (length > 0)
    {
        if (array[--length] == value) return length;
    }
    return length; // else return non index int
}


int deleteELement(int value, int* array, int length) { // return length
    int index = searchInArray(value, array, length);
    if (index == length) throw std::invalid_argument("Array have no value.\n\nNothing to do!\n");
    
    while (++index < length) array[index] = array[index + 1];

    return length - 1;
}


int insertArrayValue(int value, int* array, int length) {
    if (length == MAX_LENGTH) throw std::invalid_argument("Array is full!\n");
    
    array[length] = value;

    return length + 1;
}

int insertArrayByIndex(int value, int index, int* array, int length) {
    if (length == MAX_LENGTH) throw std::invalid_argument("Array is full!\n");

    const int outlength = length + 1;
    
    while(length > index) {
        array[length] = array[length-1];
        length--;
    }

    array[index] = value;

    return outlength;
}


//
// SORTED ARRAY
//


bool isSortedArray(int* array, int length) {
    while (--length) if (array[length] < array[length - 1]) return false;
    
    return true;
}

int insertSortedArrayValue(int value, int* array, int length) {
    int bottom = 0, top = length - 1, index;
    while(true) {
        index = (bottom + top) / 2;
        if (value == array[index]) {
            return insertArrayByIndex(value, index, array, length);

        } else if (top < bottom){
            return insertArrayByIndex(value, bottom, array, length);

        } else {

            if (value > array[index]) {
                bottom = index + 1;
            }
            else {
                top = index - 1;
            }
        }
    }
    return length;
}


int makeSortedArray(int* srcArray, int* destArray, int length) {
    for (int i = 0; i < length; i++) insertSortedArrayValue(srcArray[i], destArray, i);
    
    return length;
}

int searchInSortedArray (int value, int* array, int length) {
    int bottom = 0, top = length - 1, index;
    while(true) {
        index = (bottom + top) / 2;
        if (value == array[index]) return index;
        else if (top < bottom) return length;
        else {
            if (value > array[index]) bottom = index + 1;
            else top = index - 1;
        }
    }
}

int deleteSortedELement(int value, int* array, int length) { // return length
    int index = searchInSortedArray(value, array, length);
    if (index == length) throw std::invalid_argument("Array have no value.\n\nNothing to do!\n");
    
    while (++index < length) array[index] = array[index + 1];

    return length - 1;
}


int main() {
    int array[MAX_LENGTH];
    int length = MAX_LENGTH;

    length = deleteELement(array[0], array, length);
    length = deleteELement(array[length/2], array, length);
    length = insertArrayValue(-100, array, length);
    length = insertArrayValue(255, array, length);

    searchInArray(array[length/2], array, length);


    int sortedArray[length];
    int sortedLength = makeSortedArray(array, sortedArray, length);


    sortedLength = deleteELement(sortedArray[0], sortedArray, sortedLength);
    sortedLength = deleteELement(sortedArray[sortedLength/2], sortedArray, sortedLength);
    sortedLength = insertArrayValue(-1000, sortedArray, sortedLength);
    sortedLength = insertArrayValue(255, sortedArray, sortedLength);

    searchInSortedArray(sortedArray[sortedLength/2], sortedArray, sortedLength);
    searchInArray(sortedArray[sortedLength/2], sortedArray, sortedLength);

    //std::cout << isSortedArray(sortedArray, sortedLength) << "\n";
    //std::cout << isSortedArray(array, length) << "\n";

    return 0;
}

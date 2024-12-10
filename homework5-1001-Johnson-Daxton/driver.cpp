#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <algorithm>

void recordSortData(int* sizes, int** numbers, int type);

void realBubble(int size, int* numbers);

void generateNumbers(int* sizes, int** arrays);

void bubbleSort(int size, int* numbers, long& swaps, long& comparisons);

void insertionSort(int size, int* numbers, long& swaps, long& comparisons);

void merge(int* numbers, int low, int mid, int high, long& comparisons, long& swaps);

void mergeSort(int* numbers, long& swaps, long& comparisons, int low, int high);

int main(){
    long swaps, comparisons;
    std::ofstream fileOut;
    int unsorted1[1000];
    int unsorted2[10000];
    int unsorted3[100000];
    int sorted1[1000];
    int sorted2[10000];
    int sorted3[100000];
    int sizes[6] = {1000, 10000, 100000, 1000, 10000, 100000};
    int* numberArrays[6] = {unsorted1, unsorted2, unsorted3, sorted1, sorted2, sorted3};
    generateNumbers(sizes, numberArrays);
    realBubble(1000, sorted1);
    realBubble(10000, sorted2);
    realBubble(100000, sorted3);
    //std::cout<<"MERGE SWAPS: "<<swaps<<std::endl;
    //std::cout<<"MERGE COMPARISONS: "<<comparisons<<std::endl;
    recordSortData(sizes, numberArrays, 1);
    recordSortData(sizes, numberArrays, 2);
    recordSortData(sizes, numberArrays, 3);
    return 1;
}

void recordSortData(int* sizes, int** numbers, int type){
    long swaps, comparisons;
    std::string typeString;
    std::ofstream fileOut;
    switch(type){
        case 1: 
            typeString = "bubble";
            break;
        case 2: 
            typeString = "insertion";
            break;
        case 3: 
            typeString = "merge";
            break; 
    }
    for(int j = 0; j < 3; j++){
        //std::cout<<"STARTED "<<j<<"TH REPETITION"<<std::endl;
        fileOut.open(typeString+std::to_string(sizes[j])+".csv");
        fileOut<<"Runtime, Comparisons, Swaps"<<std::endl<<"Unsorted,,"<<std::endl;
        for(int i = 0; i < 10; i++){
            swaps = comparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            switch(type){
                case 1: 
                    bubbleSort(sizes[j], numbers[j], swaps, comparisons);
                    break;
                case 2: 
                    insertionSort(sizes[j], numbers[j], swaps, comparisons);
                    break;
                case 3: 
                    int newNums[sizes[j]];
                    for(int i = 0; i < sizes[j]; i++){
                        newNums[i] = numbers[j][i];
                    }
                    mergeSort(newNums, swaps, comparisons, 0, sizes[j]-1);
                    break; 
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            fileOut<<duration.count()<<","<<comparisons<<","<<swaps<<std::endl;
        }
        fileOut<<std::endl<<"Sorted,,"<<std::endl;
        for(int i = 0; i < 10; i++){
            swaps = comparisons = 0;
            auto start = std::chrono::high_resolution_clock::now();
            switch(type){
                case 1: 
                    bubbleSort(sizes[j], numbers[j+3], swaps, comparisons);
                    break;
                case 2: 
                    insertionSort(sizes[j], numbers[j+3], swaps, comparisons);
                    break;
                case 3: 
                    int newNums[sizes[j]];
                    for(int i = 0; i < sizes[j]; i++){
                        newNums[i] = numbers[j+3][i];
                    }
                    mergeSort(newNums, swaps, comparisons, 0, sizes[j]-1);
                    break; 
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            fileOut<<duration.count()<<","<<comparisons<<","<<swaps<<std::endl;
        }
        fileOut.close();
    }
}

void generateNumbers(int* sizes, int** array){
    srand((unsigned) time(0));
    for(int j = 0; j < 6; j++){
        for(int i = 0; i < sizes[j]; i++){
            int result = (rand() % 1000000);
            array[j][i] = result;
        } 
    }
}

void realBubble(int size, int* numbers){
    for(int i = 0; i < size-2; i++){
        for(int j = 0; j < size-i-1; j++){
            if(numbers[j] > numbers[j+1]){
                int temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }
        }
    }
}

void bubbleSort(int size, int* numbers, long& swaps, long& comparisons){
    /*array copies are included at the beginnings of these sort functions so 
    that they can be run in succession and collect the same diagnostic data*/
    int newNums[size];
    for(int i = 0; i < size; i++){
        newNums[i] = numbers[i];
    }
    for(int i = 0; i < size-2; i++){
        for(int j = 0; j < size-i-1; j++){
            comparisons++;
            if(newNums[j] > newNums[j+1]){
                int temp = newNums[j];
                newNums[j] = newNums[j+1];
                newNums[j+1] = temp;
                swaps++;
            }
        }
    }
}

void insertionSort(int size, int* numbers, long& swaps, long& comparisons){
    int newNums[size];
    for(int i = 0; i < size; i++){
        newNums[i] = numbers[i];
    }
    int temp, j;
    for(int i = 1; i < size; i ++){
        temp = newNums[i];
        j = i-1;
        while(j >= 0 && newNums[j] > temp){
            comparisons++;
            newNums[j+1] = newNums[j];
            j = j-1;
        }
        newNums[j+1] = temp;
        swaps++;
    }
    /*for(int i = 0; i < size; i++){
        std::cout<<newNums[i]<<std::endl;
    }*/
}

void merge(int* numbers, int low, int mid, int high, long& comparisons, long& swaps){
    int i = low, j = mid + 1, k = 0;
    int temp[high-low+1];
    while(i <= mid && j <= high){
        comparisons++;
        if(numbers[i] < numbers[j]){
            temp[k] = numbers[i];
            k++;
            i++;
        } else {
            temp[k] = numbers[j];
            k++;
            j++;
        }
    }
    while(i <= mid){
        temp[k] = numbers[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = numbers[j];
        k++;
        j++;
    }
    for(int i = low; i <= high; i++){
        numbers[i] = temp[i-low];
    }
}

void mergeSort(int* numbers, long& swaps, long& comparisons, int low, int high){
    int mid;
    if(low<high){
        mid = (low+high)/2;
        mergeSort(numbers, swaps, comparisons, low, mid);
        mergeSort(numbers, swaps, comparisons, mid+1, high);
        merge(numbers, low, mid, high, comparisons, swaps);
    }
}   
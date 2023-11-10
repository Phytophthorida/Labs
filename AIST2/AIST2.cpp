#include <iostream>

class DynamicArray {
private:
    int* arr;
    int size;

public:
    DynamicArray() : arr(nullptr), size(0) {}

    void append(int value) {
        int* newArr = new int[size + 1];
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        newArr[size] = value;
        delete[] arr;
        arr = newArr;
        ++size;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    int getSize() const {
        return size;
    }

    void display() const {
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    ~DynamicArray() {
        delete[] arr;
    }
};

struct Run {
    int start;
    int length;
};

void insertionSort(DynamicArray& dynArr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = dynArr[i];
        int j = i - 1;
        while (j >= left && dynArr[j] > key) {
            dynArr[j + 1] = dynArr[j];
            j--;
        }
        dynArr[j + 1] = key;
    }
}

void merge(DynamicArray& dynArr, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    DynamicArray leftArr, rightArr;

    for (int i = 0; i < len1; i++) {
        leftArr.append(dynArr[left + i]);
    }
    for (int i = 0; i < len2; i++) {
        rightArr.append(dynArr[mid + 1 + i]);
    }

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            dynArr[k] = leftArr[i];
            i++;
        }
        else {
            dynArr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        dynArr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < len2) {
        dynArr[k] = rightArr[j];
        j++;
        k++;
    }
}

int calcMinRun(int n) {
    int r = 0;
    while (n >= 32) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void findRuns(DynamicArray& dynArr, Run runs[], int& numRuns) {
    int minRun = calcMinRun(dynArr.getSize());
    int i = 0;
    while (i < dynArr.getSize()) {
        int runSize = std::min((i + minRun - 1), dynArr.getSize() - 1);
        insertionSort(dynArr, i, runSize);
        runs[numRuns].start = i;
        runs[numRuns].length = runSize - i + 1;
        numRuns++;
        i = runSize + 1;
    }
}

void gallopingMerge(DynamicArray& dynArr, Run runs[], int numRuns) {
    int minRun = calcMinRun(dynArr.getSize());
    if (numRuns < 2)
        return;

    int i = 0;
    while (i < numRuns - 1) {
        int run1 = i;
        int run2 = i + 1;

        while (i < numRuns - 2) {
            int run3 = i + 2;
            if (runs[run1].length <= runs[run2].length + runs[run3].length) {
                if (runs[run1].length < runs[run3].length)
                    run2 = run1;
                i = run2;
                break;
            }

            i = run3;
        }

        merge(dynArr, runs[run1].start, runs[run2].start - 1, runs[run2].start + runs[run2].length - 1);
        runs[run2].length += runs[run1].length;
    }
}

void timSort(DynamicArray& dynArr) {
    int minRun = calcMinRun(dynArr.getSize());
    Run* runs = new Run[dynArr.getSize()];
    int numRuns = 0;

    findRuns(dynArr, runs, numRuns);
    gallopingMerge(dynArr, runs, numRuns);

    delete[] runs;
}

int main() {
    DynamicArray dynArr;
    dynArr.append(54);
    dynArr.append(34);
    dynArr.append(25);
    dynArr.append(14);
    dynArr.append(22);
    dynArr.append(11);
    dynArr.append(91);

    timSort(dynArr);

    dynArr.display();

    return 0;
}
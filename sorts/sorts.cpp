

#include "iostream"
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
	Node* next;
	Node* prev;
	int value;
public:
	Node(int data) {
		next = prev = nullptr;
		this->value = data;
	}
	Node() {
		next = prev = nullptr;
		value = 0;
	}
};


class LinkedList {
public:
	Node* head;
	Node* tail;
	int size;
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~LinkedList() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void appendFirstInd(int value) {
		size++;
		Node* temp = new Node(value);
		if (head == nullptr) {
			head = tail = temp;
		}
		else {
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
	}

	void appendLastInd(int value) {
		size++;
		Node* temp = new Node(value);
		if (tail == nullptr) {
			head = tail = temp;
		}
		else {
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}

	void append(int index, int value) {
		Node* temp = new Node(value);
		while (index > size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}

		if (index == size) {
			delete temp;
			appendLastInd(value);
			return;
		}
		if (!index) {
			delete temp;
			appendFirstInd(value);
			return;
		}
		if (size / 2 > index) {
			Node* curr = head;
			for (int i = 0; i < index - 1; i++) {
				curr = curr->next;
			}
			temp->prev = curr;
			temp->next = curr->next;
			curr->next->prev = temp;
			curr->next = temp;
		}
		else {
			Node* curr = tail;
			for (int i = 0; i < size - index - 1; i++) {
				curr = curr->prev;
			}
			curr->prev->next = temp;
			temp->next = curr;
			temp->prev = curr->prev;
			curr->prev = temp;
		}
		size++;
	}

	void showList() {
		Node* temp = head;
		while (temp) {
			cout << temp->value << " ";
			temp = temp->next;
		}
	}

	Node* findElement(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		Node* temp = head;
		while (index--) {
			temp = temp->next;
		}
		return temp;
	}

	void remove(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		if (!index) {
			Node* temp = head->next;
			if (temp == nullptr) {
				tail = nullptr;
			}
			else {
				temp->prev = nullptr;
			}
			delete head;
			head = temp;
		}
		else {
			Node* prev = findElement(index - 1);
			Node* temp = prev->next;
			prev->next = temp->next;
			if (temp->next != nullptr) {
				temp->next->prev = prev;
				delete temp;
			}
			else {
				tail = prev;
				delete temp;
			}
		}
		size--;
	}

};

class DynamicArray {
public:
	int* data;
	int size;
	int capacity;

public:
	DynamicArray(int capacity) {
		this->capacity = capacity;
		data = new int[capacity];
		this->size = 0;
	}
	~DynamicArray() {
		delete[] data;
	}
	void resize(int newSize) {
		int* temp = new int[newSize];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		for (int i = size; i < newSize; i++) {
			temp[i] = 0;
		}
		this->size = newSize;
		this->capacity = newSize;
		delete[] data;
		this->data = temp;
	}

	void reverse() {
		int* temp = new int[capacity * 2];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		this->capacity *= 2;
		this->data = temp;
	}

	void reverse(int capacity) {
		int* temp = new int[capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		this->capacity = capacity;
		this->data = temp;
	}


	void remove(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		for (int i = index; i < size - 1; i++) {
			data[i] = data[i + 1];
		}
		size--;
	}

	void insert(int index, int value) {
		while (index > size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		if (size == capacity) {
			reverse();
		}
		for (int i = size; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = value;
		size++;

	}

	int& operator[](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Индекс либо больше размера массива, либо меньше нуля");
		}
		return data[index];
	}
};

template <typename T>
class StackNode {
public:
	T value;
	StackNode<T>* next = nullptr;
public:
	StackNode(T value) {
		this->value = value;
	}
};

template <typename T>
class Stack {
public:
	StackNode<T>* top;

public:
	Stack<T>() {
		top = nullptr;
	}
	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}
	void push(T value) {
		StackNode<T>* temp = new StackNode<T>(value);
		temp->next = top;
		top = temp;
	}

	void pop() {
		if (!isEmpty()) {
			StackNode<T>* temp = top;
			temp = top->next;
			delete top;
			top = temp;
		}
		else {
			cout << "Стэк и так пуст";
			return;
		}
	}

	bool isEmpty() {
		return (top == nullptr);
	}

	T get() {
		if (!isEmpty()) {
			return top->value;
		}
		else {
			cout << "Стэк пуст";
			return T();
		}
	}

	int size() {
		StackNode<T>* cur = top;
		int count(0);
		while (cur) {
			cur = cur->next;
			count++;
		}
		return count;
	}

};


int binarySearch(DynamicArray& arr, int target, int left, int right) {
    int mid = (left + right) / 2;
    if (target == arr[mid]) {
        return mid;
    }
    if (target > arr[mid]) {
        return binarySearch(arr, target, mid+1, right);
    }
    else {
        return binarySearch(arr, target, left, mid-1);
    }
}



void insertionSort(DynamicArray& arr,int left, int right) {
    for (int i = left+1; i <= right; i++) {
        int value = arr[i];
        for (int j = i - 1; j >= left && arr[j] > value; j--) {
            arr[j + 1] = arr[j];
            arr[j] = value;
        }
    }
}


int calculateMinRun(int lenArr) {
	int reminder = 0;
	while (lenArr >= 64) {
		if (lenArr & 1) {
			reminder++;
		}
		lenArr >>= 1;
	}
	return lenArr + reminder;
}

void reverseRun(DynamicArray& arr, int left, int right) {
	while (left < right) {
		int tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
}

int gallopingModernizated(DynamicArray& arr, int start, int end, int value) {
	int limit = min(start + 7, end);
	int i = start;

	while (i < limit && arr[i] < value) {
		i++;
	}

	if (i < limit) {
		return i;
	}

	int step = 1;
	int posAfterFirstCheck = start + 7;

	while (posAfterFirstCheck < end && arr[posAfterFirstCheck] < value) {
		posAfterFirstCheck = start + 7 + (1 << step);
		step++;
	}

	int leftBound = start + 7 + (1 << (step - 1));
	int rightBound = min(posAfterFirstCheck, end);

	leftBound = min(leftBound, end);
	rightBound = min(rightBound, end);
	
	return binarySearch(arr, value, leftBound, rightBound);
	
}

void merge(DynamicArray& arr, int left, int mid, int right) {
	int i = 0, j = 0;
	int len1 = mid - left + 1;
	int len2 = right - mid;
	int* a = new int[len1 + 1];
	int* b = new int[len2 + 1];
	a[len1] = INT_MAX;
	b[len2] = INT_MAX;
	for (int i = 0; i < len1; i++) {
		a[i] = arr[left + i];
	}
	for (int i = mid + 1; i < right + 1; i++) {
		b[j++] = arr[i];
	}
	i = 0;
	j = 0;
	for (int k = left; k <= right; k++) {
		if (a[i] <= b[j]) {
			arr[k] = a[i++];
		}
		else {
			if (len2 - j > 7) {
				int gallopingJ = gallopingModernizated(arr, mid + 1 + j, right, a[i]);
				if (gallopingJ > mid + 1 + j) {
					while (mid + 1 + j < gallopingJ && k <= right) {
						arr[k++] = b[j++];
					}
					k--;
				}
			}
			arr[k] = b[j++];
		}
	}
	delete[] a;
	delete[] b;
}

void mergeRuns(DynamicArray& arr, Stack <pair<int, int>>& stack) {
	while (stack.size() > 1) {
		pair<int, int> X, Y, Z;
		Z = stack.get();
		stack.pop();
		Y = stack.get();
		stack.pop();
		bool hasX = false;
		if (!stack.isEmpty()) {
			X = stack.get();
			stack.pop();
			hasX = true;
		}
		bool merged = false;
		if (hasX && X.second <= Y.second + Z.second) {
			merge(arr, X.first, X.first + X.second - 1, Y.first + Y.second - 1);
			stack.push({ X.first, X.second + Y.second });
			stack.push(Z);
			merged = true;
		}
		else if (Y.second <= Z.second) {
			merge(arr, Y.first, Y.first + Y.second - 1, Z.first + Z.second - 1);
			stack.push({ Y.first, Y.second + Z.second });
			if (hasX) stack.push(X);
			merged = true;
		}

		if (!merged) {
			if (hasX) stack.push(X);
			stack.push(Y);
			stack.push(Z);
			break;
		}
	}
	while (stack.size() > 1) {
		pair<int, int> Z = stack.get(); stack.pop();
		pair<int, int> Y = stack.get(); stack.pop();
		merge(arr, Y.first, Y.first + Y.second - 1, Z.first + Z.second - 1);
		stack.push({ Y.first, Y.second + Z.second });
	}
}

void timSort(DynamicArray& arr, int lenArr) {
	int minRun = calculateMinRun(lenArr);
	Stack<pair<int,int>> stack;
	int counter;
	int startRun;
	for (int i = 0; i < lenArr; i++) {
		counter = 1;
		startRun = i;
		if (lenArr == i + 1) {
			stack.push({ i,counter });
			mergeRuns(arr, stack);
			break;
		}
		startRun = i;
		if (arr[i] <= arr[i + 1]) {
			while (i + 1 < lenArr && arr[i] <= arr[i + 1]) {
				counter++;
				i++;
			}
		}
		else {
			while (i + 1 < lenArr && arr[i] > arr[i+1]) {
				counter++;
				i++;
			}
			reverseRun(arr, startRun, startRun + counter - 1);
		}

		if (counter < minRun) {
			int minimal = min(lenArr - startRun, minRun);
			insertionSort(arr, startRun, startRun+minimal-1);
			counter = minimal;
			i = startRun + counter-1;
		}
		stack.push({ startRun, counter });
		mergeRuns(arr, stack);
	}

	mergeRuns(arr, stack);
}

int main() {

	cout << "Введите элементы массива через пробел: ";
	string input;
	getline(cin, input);

	stringstream ss(input);
	int value;

	int count = 0;
	while (ss >> value) {
		count++;
	}

	DynamicArray arr(count);

	ss.clear();
	ss.str(input);

	while (ss >> value) {
		arr.data[arr.size++] = value;
	}

	cout << "\nМассив до сортировки: ";
	for (int i = 0; i < arr.size; i++) {
		cout << arr.data[i] << " ";
	}

	timSort(arr, arr.size);

	cout << "\nМассив после сортировки: ";
	for (int i = 0; i < arr.size; i++) {
		cout << arr.data[i] << " ";
	}
}

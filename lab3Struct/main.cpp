#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class T>
struct comp {
	T data;
	comp* next;
};

template <class T>
void push(comp<T>** top, T D) {
	comp<T>* newElem = new comp<T>();
	newElem->data = D;
	if (top == nullptr) { // Если вершины нет, то стек пустой
		top = &newElem;
	}
	else {
		newElem->next = *top;
		*top = newElem;
	}
}

template <class T>
void del(comp<T>** top, T D) {
	comp<T>* q = *top; // вершина стека
	comp<T>* prev = nullptr; // указатель на предыдущий элемент
	while (q != nullptr) {
		if (q->data == D) { // если мы нашли число
			if (q == *top) { // если указатель равен вершине
				*top = q->next; // передвигаем вершину на следующий элемент
				delete q;
			}
			else { // если элемент находится не сверху
				prev->next = q->next;
				delete q;
			}
		}
		prev = q;// запоминаем ячейку как предыдущую 
		q = q->next; // двигаемся дальше
	}
}

template <class T>
T peek(comp<T>* top) {
	comp<T>* q = top;
	if (q)
		return q->data;
	else
		return NULL;
}

template <class T>
T pop(comp<T>** top) {
	comp<T>* q = *top;
	T res = NULL;
	if (q != nullptr) {
		 res = q->data;
		*top = q->next;
		delete q;
	}
	return res;
}

template <class T>
int count(comp<T>* top) {
	int c = 0;
	comp<T>* q = top;
	while (q) {
		c++;
		q = q->next;
	}
	return c;
}

template <class T>
void print(comp<T>* top) {
	comp<T>* q = top;
	while (q) {
		cout << q->data << endl;
		q = q->next;
	}
}

int indexOf(string inp, char c) { // поиск первого вхождения символа
	int index = -1;
	for (int i = 0; i < inp.length(); i++) {
		if (inp[i] == c) {
			index = i;
			break;
		}
	}
	return index;
}

bool checkString(string text, comp<char>* stack) {
	string check = "()[]{}";
	for (int i = 0; i < text.size(); i++) {
		if (indexOf(check, text[i]) % 2 == 0) { // если открытая скобка
			push(&stack, text[i]);
		}
		else if (indexOf(check, text[i]) % 2 == 1) // если закрытая скобка
		{
			if ((indexOf(check, text[i]) - indexOf(check, peek(stack))) == 1) {
				pop(&stack);
			}
		}
	}
	return count(stack) == 0;
}

int main() {
	comp<char>* stack = NULL;
	string line = "", text = "";
	ifstream in("input.txt");
	if (in.is_open()) {
		while (getline(in, line)) {
			text += line;
		}
	}
	cout << "text is correct?: " << boolalpha <<checkString(text, stack) << endl;
	system("pause");
	return 0;
}
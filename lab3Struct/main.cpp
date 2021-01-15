#include <iostream>
#include <fstream>
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
	if (top == NULL) { // ���� ������� ���, �� ���� ������
		top = &newElem;
	}
	else {
		newElem->next = *top;
		*top = newElem;
	}
}

template <class T>
void del(comp<T>** top, T D) {
	comp<T>* q = *top; // ������� �����
	comp<T>* prev = NULL; // ��������� �� ���������� �������
	while (q != NULL) {
		if (q->data == D) { // ���� �� ����� �����
			if (q == *top) { // ���� ��������� ����� �������
				*top = q->next; // ����������� ������� �� ��������� �������
				free(q);
				q->data = NULL; // �������� ������
				q->next = NULL;
			}
			else { // ���� ������� ��������� �� ������
				prev->next = q->next;
				free(q);
				q->data = NULL;
				q->next = NULL;
			}
		}
		prev = q;// ���������� ������ ��� ���������� 
		q = q->next; // ��������� ������
	}
}

template <class T>
T peek(comp<T>* top) {
	comp<T>* q = top;
	if (q)
		return q->data;
}

template <class T>
T pop(comp<T>** top) {
	comp<T>* q = *top;
	T res = NULL;
	if (q != NULL) {
		 res = q->data;
		*top = q->next;
		free(q);
		q->data = NULL;
		q->next = NULL;
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

int indexOf(string inp, char c) { // ����� ������� ��������� �������
	int index = -1;
	for (int i = 0; i < inp.length(); i++) {
		if (inp[i] == c) {
			index = i;
			break;
		}
	}
	return index;
}

int main() {
	comp<char>* stack = NULL;
	string check = "()[]{}";
	string test = "";
	ifstream in("input.txt");
	for (int i = 0; i < test.size(); i++) {
		if (indexOf(check, test[i]) % 2 == 0) { // ���� �������� ������
			push(&stack, test[i]);
		}
		else if (indexOf(check, test[i]) % 2 == 1) // ���� �������� ������
		{
			if ((indexOf(check, test[i]) - indexOf(check, peek(stack))) == 1) {
				pop(&stack);
			}
		}
	}
	cout << "stack count: " << count(stack) << endl;
	system("pause");
	return 0;
}
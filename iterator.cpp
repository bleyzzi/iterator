#include "List.h"
#include <windows.h>
using namespace std;
List l;

unsigned counting(ListIterator* li) {
	unsigned cnt = 0;
	if (li->first())
		do {
			cnt++;
			cerr << li->currentItem() << " ";
		} while (li->next());
		cerr << endl;
		return cnt;
}

bool predicate(int a)
{
	return a > 7;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	for(int i = 1; i < 11; i++)
	{
		l.append(i);
	}
	cout << "Список: ";
	l.print();
	cout << "\n";
	try {
		ListIterator* litS3 = l.createIterator(Iterators::STEP, 3);
		ListIterator* litV4 = l.createIterator(Iterators::VALUE, 2);
		ListIterator* litPred = l.createIterator(Iterators::PREDICATE, 0, predicate);
		litS3->first();
		cout << "Перегрузка *: " << **litS3 << "\n";
		++* litS3;
		cout << "Перегрузка * после ++ с шагом 3: " << **litS3 << "\n";
		cout << "\n";
		cout << "Итератор STEP: ";
		cout << "Количество элементов(шаг 3): " << counting((ListIteratorStep*)litS3) << endl;
		cout << "\n";
		cout << "Итератор VALUE: ";
		cout << "Количество элементов(значение 2): " << counting((ListIteratorValue*)litV4) << endl;
		cout << "\n";
		cout << "Итератор PREDICATE: ";
		cout << "Количество элементов(больше 7): " << counting((ListIteratorPredicate*)litPred) << endl;
		delete litS3;
		delete litV4;
		delete litPred;
	}
	catch(exception &e)
	{
		cerr << e.what();
	}

	return 0;
}

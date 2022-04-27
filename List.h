#pragma once
#include <iostream>
#include "forward_list.h"
#include "List.h"
using namespace std;

enum class Iterators {
	STEP,
	VALUE,
	PREDICATE
};
class ListIterator;
class List
{
public:
	forward_list lst;
	int top = 0;
	int _capacity = 0;
	friend class ListIterator;
	
	bool append(int a)
	{
		lst.push_back(a);
		top++;
		return true;
	}

	bool remove()
	{
		if (lst.is_empty()) return false;
		lst.remove_last();
		top--;
		return true;
	}
	
	void print()
	{
		lst.print();
	}
	
	virtual ~List(){}
	ListIterator* createIterator(Iterators its, const int aStep, bool(*_predicate)(int a) = nullptr) const;
};

class ListIterator {
protected:
	friend class List;
	const List* pList;
	int current;
public:
	ListIterator(const List* aPList) : pList(aPList) {}
	virtual bool first() = 0;
	virtual bool next() = 0;
	virtual int currentItem() = 0;
	virtual bool cnt() = 0;
	virtual int operator*() = 0;
	virtual ListIterator* operator++() = 0;
};

class ListIteratorStep : public ListIterator
{
private:
	int step;
public:
	friend class List;
	ListIteratorStep(const List* aPList, int aStep = 1) : ListIterator(aPList)
	{
		if (aStep < 0) throw exception("Шаг не может быть отрицательным");
		step = aStep - 1;
		//if (aStep < 0) return;//throw exception("Шаг не может быть отрицательным");
	}

	bool cnt() override
	{
		for (auto i = 0; current > -1 && i < step; i++) current--;
		return current > -1;
	}

	bool first() override
	{
		current = pList->top - 1;
		return cnt();
	}

	bool next() override
	{
		current--;
		return cnt();
	}

	int currentItem() override
	{
		if (current <= -1) throw logic_error("Can't obtain currentItem!");
		return pList->lst[current]->val;
	}
	
	int operator*() override
	{
		return currentItem();
	}

	ListIteratorStep* operator++() override
	{
		this->next();
		return this;
	}
	
};

class ListIteratorValue : public ListIterator
{
private:
	int value;
public:
	friend class List;
	ListIteratorValue(const List* aPList, int aValue) : ListIterator(aPList) {
		value = aValue;
	}

	bool cnt() override
	{
		while (current > -1 && pList->lst[current]->val != value) current--;
		return current > -1;
	}

	bool first() override {
		current = pList->top - 1;
		return cnt();
	}
	bool next() override
	{
		current--;
		return cnt();
	}
	int currentItem() override
	{
		if (current <= -1) throw logic_error("Can't obtain currentItem!");
		return pList->lst[current]->val;
	}

	int operator*() override
	{
		return currentItem();
	}

	ListIteratorValue* operator++() override
	{
		this->next();
		return this;
	}
};

class ListIteratorPredicate : public ListIterator
{
private:
	bool(* predicate)(int a);
public:
	ListIteratorPredicate(const List* aPList, bool(* aPredicate)(int a)) : ListIterator(aPList)
	{
		predicate = aPredicate;
	}

	bool first() override
	{
		current = pList->top - 1;
		return cnt();
	}

	bool next() override
	{
		current--;
		return cnt();
	}

	bool cnt()
	{
		while (current > -1 && !(predicate)(pList->lst[current]->val)) current--;
		return current > -1;
	}

	int currentItem() override
	{
		if (current <= -1) throw logic_error("Can't obtain currentItem!");
		return pList->lst[current]->val;
	}

	int operator*() override
	{
		return currentItem();
	}

	ListIteratorPredicate* operator++() override
	{
		this->next();
		return this;
	}

};

ListIterator* List::createIterator(Iterators its, const int aStep, bool(*_predicate)(int a)) const {
	if (its == Iterators::STEP)
		return new ListIteratorStep(this, aStep);
	if (its == Iterators::VALUE)
		return new ListIteratorValue(this, aStep);
	if (its == Iterators::PREDICATE)
		return new ListIteratorPredicate(this, _predicate);
	return nullptr;
};

#pragma once

#include <initializer_list>
#include <iterator>

class forward_list
{
	class Element {
		int m_data;
		Element* m_next;
	public:
		Element(int data, const Element* next = nullptr);
		Element(const Element& other);
		~Element();
		void debug();
		friend class forward_list;
		friend class iterator;
	};
public:
	class iterator : public std::iterator<std::forward_iterator_tag, int>
	{
		forward_list::Element* m_pElement;
	public:
		iterator(forward_list::Element* pElement = nullptr);
		iterator(const iterator* other);
		~iterator();
		iterator& operator=(const iterator& other);
		
		forward_list::iterator& operator++();
		forward_list::iterator operator++(int);

		int& operator*();
		const int& operator*() const;

		bool operator==(const iterator& rhs);
		bool operator!=(const iterator& rhs);
	};
private:

	Element* m_head;
public:
	forward_list();
	forward_list(std::initializer_list<int> list);
	~forward_list();

	void push_front(int value);
	void push_back(int value);

	void pop_front();
	void pop_back();

	void erase(std::size_t index);
	void erase_value(int value);
public:
	forward_list::iterator begin();
	forward_list::iterator end();

	forward_list::iterator begin() const;
	forward_list::iterator end() const;

	void debug();
};


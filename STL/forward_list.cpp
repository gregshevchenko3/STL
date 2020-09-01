#include "forward_list.h"

#include <iostream>

forward_list::Element::Element(int data, Element* next) : m_data(data), m_next(next)
{
	std::cout << "forward_list::Element::Element constructor" << std::endl;
}
forward_list::Element::Element(const Element& other) : m_data(other.m_data), m_next(other.m_next)
{
	std::cout << "forward_list::Element::Element copy constructor" << std::endl;
}
forward_list::Element::~Element()
{
	std::cout << "forward_list::Element::Element destructor" << std::endl;
	if (m_next) delete m_next;
}
void forward_list::Element::debug()
{
	std::cout << m_data;
	if (m_next == nullptr)
		std::cout << "->End." << std::endl;
	else {
		std::cout << "->";
		m_next->debug();
	}
}
forward_list::forward_list() : m_head(nullptr)
{
	std::cout << "forward_list::forward_list constructor" << std::endl;
}
forward_list::forward_list(std::initializer_list<int> list)
{
	auto it = list.end() - 1;
	while (it != list.begin()) 
		push_front(*it--);
	push_front(*it);
}
forward_list::~forward_list()
{
	if (m_head) delete m_head;
}
void forward_list::push_front(int value)
{
	Element* New = new Element(value);
	New->m_next = m_head;
	m_head = New;
}
void forward_list::pop_front()
{
	Element* tmp = m_head;
	m_head = m_head->m_next;
	tmp->m_next = nullptr;
	delete tmp;
}
void forward_list::pop_back()
{
	if (!m_head)
		forward_list::iterator(m_head);
	Element* el = m_head;
	while (el->m_next->m_next)
		el = el->m_next;
	delete el->m_next;
	el->m_next = nullptr;
}
void forward_list::erase(std::size_t index)
{
	if (!index) pop_front();
	else {
		auto el = m_head;
		auto i = 0;
		while (el->m_next && ++i < index) {
			el = el->m_next;
		}
		if (i == index) {
			auto for_delete = el->m_next;
			if(el->m_next)
				el->m_next = el->m_next->m_next;
			if (for_delete){
				for_delete->m_next = nullptr;
				delete for_delete;
			}
		}
		else {
			throw std::out_of_range("error : forward_list::erase(std::size_t index) : index out of range!");
		}
	}
	
}
void forward_list::erase_value(int value)
{
	if (m_head->m_data == value)
	{
		pop_front();
		return;
	}
	auto el = m_head;
	while (el->m_next) {
		if (el->m_next->m_data == value) 
		{
			auto for_delete = el->m_next;
			el->m_next = el->m_next->m_next;
			for_delete->m_next = nullptr;
			delete for_delete;
		}
		else 
		{
			el = el->m_next;
		}
	}
}
void forward_list::push_back(int value)
{
	if (!m_head)
		forward_list::iterator(m_head);
	Element* el = m_head;
	while (el->m_next)
		el = el->m_next;
	el->m_next = new Element(value);
}
forward_list::iterator forward_list::begin()
{
	return forward_list::iterator(m_head);
}
forward_list::iterator forward_list::end()
{
	if (!m_head)
		forward_list::iterator(m_head);
	Element* el = m_head;
	while (el->m_next)
		el = el->m_next;
	return el->m_next;
}
forward_list::iterator forward_list::begin() const
{
	return forward_list::iterator(m_head);
}
forward_list::iterator forward_list::end() const
{
	if (!m_head)
		forward_list::iterator(m_head);
	Element* el = m_head;
	while (el->m_next)
		el = el->m_next;
	return el->m_next;
}
void forward_list::debug()
{
	m_head->debug();
}

forward_list::iterator::iterator(forward_list::Element* pElement) : m_pElement(pElement)
{
	std::cout << "forward_list::iterator::iterator constructor" << std::endl;
}
forward_list::iterator::iterator(const iterator* other) : forward_list::iterator::iterator(other->m_pElement)
{
	std::cout << "forward_list::iterator::iterator copy constructor" << std::endl;
}
forward_list::iterator::~iterator()
{
	std::cout << "forward_list::iterator::iterator destructor" << std::endl;
}
forward_list::iterator& forward_list::iterator::operator=(const iterator& other)
{
	std::cout << "forward_list::iterator::iterator copy assignment operator" << std::endl;
	if (this == &other) return *this;
	this->m_pElement = other.m_pElement;
	return *this;
}
forward_list::iterator& forward_list::iterator::operator++()
{
	//if (m_pElement && m_pElement->m_next)
	m_pElement = m_pElement->m_next;
	return *this;
}
forward_list::iterator forward_list::iterator::operator++(int)
{
	forward_list::iterator tmp = *this;
	m_pElement = m_pElement->m_next;
	return tmp;
}
int& forward_list::iterator::operator*()
{
	return m_pElement->m_data;
}
const int& forward_list::iterator::operator*() const
{
	return m_pElement->m_data;
}

bool forward_list::iterator::operator==(const iterator& rhs)
{
	return m_pElement == rhs.m_pElement;
}
bool forward_list::iterator::operator!=(const iterator& rhs)
{
	return !(*this == rhs);
}


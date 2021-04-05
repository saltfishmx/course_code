//include the headers that you need here.
#include<iostream>
#include<assert.h>
#include <memory.h>
#include<cstdlib>
using namespace std;

template <typename T>
class CArrayIterator;

template <typename T>
class CArrayConstIterator;

template <typename T>
class CArray
{
public:
	typedef T Element;
	typedef CArrayIterator<T> Iterator;
	typedef CArrayConstIterator<T> ConstIterator;

public:
	CArray() {
		_buff=NULL;
		_cap=0;
		_size=0;
	}
	CArray(const CArray &rhs){
		_buff=rhs._buff;
		_size=rhs._size;
		_cap=rhs._cap;
	}
	~CArray() {
		delete[] _buff;
		_buff=NULL;
		_cap=0;
		_size=0;
	}

public:
	int capacity() const
	{
		return _cap;
	}
	int size() const
	{
		return _size;
	}

	void recap(int cap){
		Element *p1=NULL;
		p1 = new Element[cap];
		_size=_size>cap? cap : _size;
		memcpy(_buff,p1,4*_size);
		/*
        for(int i=0;i<_size;i++){
			p1[i]=_buff[i];
		}
        */
	    //delete[] _buff;
		_buff=p1;
		_cap=cap;

	}
	Element &at(int index)
	{
		return _buff[index];
	}
	Element at(int index) const
	{
		return _buff[index];
	}

	void append(Element element){
		if(_size==_cap){
			recap(_cap+1);
		}
		_buff[_size]=element;
		_size++;
	}
	void insert(int index, Element element){
		if(_size==_cap){
			recap(_cap+1);
		}
		for(int i=_size;i>index;i--){
			_buff[i]=_buff[i-1];
		}
		_buff[index]=element;
		_size++;
	}

	void copy(const CArray &rhs){
		recap(rhs._cap);
		for(int i=0;i<rhs._size;i++){
			_buff[i]=rhs._buff[i];
		}
		_size=rhs._size;
	}
	bool compare(const CArray &rhs) const{
		if(_size!=rhs._size)
			return false;
		else{
			for(int i=0;i<rhs._size;i++){
				if(_buff[i]!=rhs._buff[i])
					return false;
			}
			return true;
		}
	}
	ConstIterator begin()const{
		return ConstIterator(_buff);
	}
	ConstIterator end()const{
		return ConstIterator(_buff+_size);
	}
	Iterator begin(){
		return Iterator(_buff);
	}
	Iterator end(){
		return Iterator(_buff+_size);
	}
private:
	void _check_capacity(int minimal);
	Element *_buff;
	int _size;
	int _cap;
	};

	template <typename T>
	class CArrayIterator
	{

	public:
		CArrayIterator() {}
		CArrayIterator(T *current){
			_current=current;
		}
		CArrayIterator(const CArrayIterator &rhs){
			_current=rhs._current;
		}

		~CArrayIterator() {
			
		}

	public:
		//实现所需要的操作符重载函数
		T& operator*()const{
			return *_current;
		}
		T* operator->()const{
			return &this->operator*();
		}
		bool operator==(const CArrayIterator &it){
			if(_current==it._current)
				return true;
			else
				return false;
		}
		bool operator!=(const CArrayIterator &it){
			if(_current!=it._current)
				return true;
			else
				return false;
		}
		CArrayIterator& operator++(){
			++_current;
			return *this;
		}
		CArrayIterator  operator++(int){
			CArrayIterator ret=*this;
			++_current;
			return ret;
		}

	protected:
		T *_current;
		friend class CArray<T>;

	};

	template <class T>
	class CArrayConstIterator
	{
	public:
		CArrayConstIterator() {}
		CArrayConstIterator(T *current){
			_current=current;
		}
		CArrayConstIterator(const CArrayConstIterator &rhs){
			_current=rhs._current;
		}
		~CArrayConstIterator() {
			
		}

	public:
		//实现所需要的操作符重载函数
		T& operator*()const{
			return *_current;
		}
		T* operator->()const{
			return &this->operator*();
		}
		bool operator==(const CArrayConstIterator &it){
			if(_current==it._current)
				return true;
			else
				return false;
		}
		bool operator!=(const CArrayConstIterator &it){
			if(_current==it._current)
				return false;
			else
				return true;
		}
		CArrayConstIterator& operator++(){
			++_current;
			return *this;
		}
		CArrayConstIterator  operator++(int){
			CArrayConstIterator ret=*this;
			++_current;
			return ret;
		}
	protected:
		T *_current;
		friend class CArray<T>;
	};













	template <typename T>
	class Obj
	{
	public:
		Obj(){};
		Obj(int val) : data(val){};
		~Obj(){};

	public:
		T data;

	private:
		template <typename Tp>
		friend std::ostream &operator<<(std::ostream &os, const Obj<Tp> &obj);
	};

	template <typename Tp>
	std::ostream &operator<<(std::ostream &os, const Obj<Tp> &obj)
	{
		os << obj.data;
		return os;
	}

	int main(int argc, char const *argv[])
{
	
		CArray<int> array;

		array.recap(10);

		assert(array.capacity() == 10);

		for (int i = 0; i < 20; ++i)
		{
			array.append(i);
		}
		assert(array.size() == 20);
		for (int i = 0; i < array.size(); ++i)
		{
			assert(array.at(i) == i);
		}

		CArray<int> array2, array3;

		array2.copy(array);
		assert(array.compare(array2) == true);
		array3.copy(array);
		assert(array.compare(array3) == true);

		array2.insert(2, 3);
		assert(array.compare(array2) == false);

		array3.at(2) = 5;
		assert(array.compare(array3) == false);
		
		for (CArray<int>::Iterator it = array.begin(); it != array.end(); ++it)
		{
			std::cout << *it << " ";
			(*it) = (*it) + 10;
		}
		std::cout << std::endl;
		for (CArray<int>::Iterator it = array.begin(); it != array.end();)
		{
			std::cout << *(it++) << " ";
		}
		std::cout << std::endl;
	
	

		const CArray<int> tmp(array);
	
		for (CArray<int>::ConstIterator it = tmp.begin(); it != tmp.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

			

		CArray<Obj<int>> obj_arr;
		for (CArray<int>::ConstIterator it = tmp.begin(); it != tmp.end();)
		{
			obj_arr.append(Obj<int>(*it));
			std::cout << *(it++) << " ";
		}
		std::cout << std::endl;

		
		for (CArray<Obj<int>>::Iterator it = obj_arr.begin(); it != obj_arr.end(); ++it)
		{
			std::cout << (*it) << " ";
		}
		std::cout << std::endl;
		for (CArray<Obj<int>>::Iterator it = obj_arr.begin(); it != obj_arr.end(); ++it)
		{
			std::cout << it->data << " ";
		}
		std::cout << std::endl;
		
		system("pause");
		
		return 0;

	}

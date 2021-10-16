#pragma once
#include <iostream>

template<typename T>
class Stack
{   
public:

    Stack();
    ~Stack();

    void push(T data);
    T pop();
    T& top();

    bool isEmpty() const;
    size_t size() const;

    T& operator[](uint32_t i);
    const T& operator[](uint32_t i) const; 

private:

    void resize();
    bool isFull();

    T* m_data;
    size_t m_size, m_capacity;
};

template<typename T>
Stack<T>::Stack()
{
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
    resize();
}

template<typename T>
Stack<T>::~Stack()
{
    delete[] m_data;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
    return m_size == 0;
}

template<typename T>
bool Stack<T>::isFull()
{
    return m_size == m_capacity;
}

template<typename T>
size_t Stack<T>::size() const
{
    return m_size;
}

template<typename T>
void Stack<T>::resize()
{
    if(isEmpty())
    {
        m_data = new T[m_capacity];
        assert(m_data != nullptr);        
    }
    else
    {
        m_capacity *= 2;
        T* temp = new T[m_capacity];
        assert(temp != nullptr);
        for(int i = 0; i < m_size; i++)
            temp[i] = m_data[i];
        delete[] m_data;
        m_data = temp;
    }
}

template<typename T>
T& Stack<T>::operator[](uint32_t i)
{
    if(i >= 0 && i < m_size)
        return m_data[i];
    else
        assert(false);
}

template<typename T>
const T& Stack<T>::operator[](uint32_t i) const
{
    if(i >= 0 && i < m_size)
        return m_data[i];
    else
        assert(false);
}

template <typename T>
void Stack<T>::push(T data)
{
    if(isFull())
        resize();
    m_data[m_size++] = data;
}

template<typename T>
T Stack<T>::pop()
{
    if(!isEmpty())
        return m_data[--m_size];
    else
        return T();
}

template<typename T>
T& Stack<T>::top()
{
    if(!isEmpty())
        return m_data[m_size - 1];
    else
        asstrt(false);
}

template<typename T>
void printStack(const Stack<T>& s)
{
    for(int i = 0; i < s.size(); i++)
        std::cout << s[i] << ", ";
    std::cout << std::endl;
}
#pragma once

#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class ABS                                       // Array-based stack
{
private:
    // Member variables
    T* _data;                                   // Data stored in the stack
    unsigned int _size;                         // Current size of the stack
    unsigned int _capacity;                     // Current max capacity of the stack

    // Class variable
    float scale_factor = 2.0f;     // Scale factor for adjusting _capacity
    
    // Private behaviors
    void shrink_capacity();
    void increase_capacity();
    void add(T object);
    void copy_from_object(const ABS& object);

public:
    // Constructors
    ABS();                                      // Default constructor
    ABS(unsigned int capacity);                 // Constructor with specified capacity
    ABS(const ABS& rhs);                        // Copy constructor

    ABS& operator=(const ABS& rhs);             // Copy assignment operator
    
    ~ABS();                                     // Destructor

    // Behaviors
    void push(T data);                          // Add to stack
    T pop();                                    // Remove and return last item in stack
    
    // Accessors
    T peek() const;                             // Return last item in stack
    unsigned int getSize() const;               // _size getter
    unsigned int getMaxCapacity() const;        // _capacity getter
    T* getData() const;                         // _data getter
};

// Remove debug tools
template <typename T>
void ABS<T>::shrink_capacity()
{
    float size = getSize();
    float capacity = getMaxCapacity();

    if (size / capacity < 1 / scale_factor)
    {  
        //cout << "Shrinking... Old capacity: " << _capacity << endl;
        _capacity = _capacity / scale_factor;
        T *resized_data = new T[_capacity];
        for (unsigned int i = 0; i < _size + 1; i++)
            resized_data[i] = _data[i];
        _data = resized_data;
        //cout << "New shrunk capacity: " << _capacity << endl;
    }
    //cout << "" << size / capacity << " > " << 1 / scale_factor << endl;
}

// Remove debug tools
template <typename T>
void ABS<T>::increase_capacity()
{
    if (_size == _capacity)
    {
        //cout << "Expanding... Old capacity: " << _capacity << endl;
        _capacity = _capacity * scale_factor;
        T *resized_data = new T[_capacity];
        for (unsigned int i = 0; i < _size; i++)
            resized_data[i] = _data[i];
        _data = resized_data;
        //cout << "New increased capacity: " << _capacity << endl;
    }
}

template <typename T>
void ABS<T>::add(T object)
{
    _data[_size] = object;
    _size++;
}

template <typename T>
void ABS<T>::copy_from_object(const ABS& object)
{
    _size = object._size;
    _capacity = object._capacity;
    _data = new T[_capacity];

    for (unsigned int i = 0; i < object._size; i++)
        add(object[i]);
}

template <typename T>
ABS<T>::ABS()
{
    _size = 0;
    _capacity = 1;
    _data = new T[_capacity];
}

template <typename T>
ABS<T>::ABS(unsigned int capacity)
{
    _size = 0;
    _capacity = capacity;
    _data = new T[_capacity];
}

template <typename T>
ABS<T>::ABS(const ABS& rhs)
{
    copy_from_object(rhs);
}

template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs)
{
    delete[] _data;
    copy_from_object(rhs);

    return *this;
}

template <typename T>
ABS<T>::~ABS()
{
    delete[] _data;
}

//Remove debug statements
template <typename T>
void ABS<T>::push(T data)
{
    increase_capacity();
    add(data);
    //cout <<"PUSH! size: " << _size << " capacity: " << _capacity << endl;
}

// Add error-handling and remove debug statements
template <typename T>
T ABS<T>::pop()
{
    //cout << "" << _size / _capacity << " > " << 1 / scale_factor << endl;
    _size--;
    shrink_capacity();
    //cout << "POP! size: " << _size << " capacity: " << _capacity << endl;
    return _data[_size];
}

// Add error-handling
template <typename T>
T ABS<T>::peek() const
{
    return _data[_size - 1];
}

template <typename T>
unsigned int ABS<T>::getSize() const
{
    return _size;
}

template <typename T>
unsigned int ABS<T>::getMaxCapacity() const
{
    return _capacity;
}

template <typename T>
T* ABS<T>::getData() const
    {
        return _data;
    }





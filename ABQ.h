#pragma once

#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class ABQ                                       // Array-based queue
{
private:
    // Member variables
    T* _data;                                   // Data stored in the queue
    unsigned int _size;                         // Current size of the queue
    unsigned int _capacity;                     // Current max capacity of the queue
    unsigned int _location;

    // Class variable
    float scale_factor = 2.0f;     // Scale factor for adjusting _capacity
    
    // Private behaviors
    void shrink_capacity();
    void increase_capacity();
    void add(T object);
    void copy_from_object(const ABQ& object);
    unsigned int inc_location();

    public:
    // Constructors
    ABQ();                                      // Default constructor
    ABQ(unsigned int capacity);                 // Constructor with specified capacity
    ABQ(const ABQ& rhs);                        // Copy constructor

    ABQ& operator=(const ABQ& rhs);             // Copy assignment operator
    
    ~ABQ();                                     // Destructor

    // Behaviors
    void enqueue(T data);                          // Add to queue
    T dequeue();                                    // Remove and return last item in queue
    
    // Accessors
    T peek() const;                             // Return last item in queue
    unsigned int getSize() const;               // _size getter
    unsigned int getMaxCapacity() const;        // _capacity getter
    T* getData() const;                         // _data getter

    // Debug
    void print();
};


template <typename T>
void ABQ<T>::shrink_capacity()
{
    float size = getSize();
    float capacity = getMaxCapacity();

    if (size / capacity < 1 / scale_factor)
    {  
        _capacity = _capacity / scale_factor;
        T *resized_data = new T[_capacity + 1];

        for (unsigned int i = 0; i < _size + 1; i++)
            resized_data[i] = _data[i + _location];

        delete[] _data;
        _data = resized_data;
        _location = 0; 
    }
}

template <typename T>
void ABQ<T>::increase_capacity()
{
    if (_size == _capacity)
    {
        _capacity = _capacity * scale_factor;
        T *resized_data = new T[_capacity];

        for (unsigned int i = 0; i < _size; i++)
            resized_data[i] = _data[i + _location];

        delete[] _data;
        _data = resized_data;
        _location = 0;
    }
}

template <typename T>
void ABQ<T>::add(T object)
{
    _data[_size] = object;
    _size++;
}

template <typename T>
void ABQ<T>::copy_from_object(const ABQ& object)
{
    _size = object._size;
    _capacity = object._capacity;
    _location = object._location;
    _data = new T[_capacity];

    for (unsigned int i = 0; i < object._size; i++)
        add(object[i]);
}

template <typename T>
ABQ<T>::ABQ()
{
    _size = 0;
    _capacity = 1;
    _location = 0;
    _data = new T[_capacity];
}

template <typename T>
ABQ<T>::ABQ(unsigned int capacity)
{
    _size = 0;
    _capacity = capacity;
    _location = 0;
    _data = new T[_capacity];
}

template <typename T>
ABQ<T>::ABQ(const ABQ& rhs)
{
    delete[] _data;
    copy_from_object(rhs);
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs)
{
    delete[] _data;
    copy_from_object(rhs);

    return *this;
}

template <typename T>
ABQ<T>::~ABQ()
{
    delete[] _data;
}

template <typename T>
void ABQ<T>::enqueue(T data)
{
    increase_capacity();
    add(data);
}

template <typename T>
T ABQ<T>::dequeue()
{
    if (_size == 0)
        throw std::runtime_error("Queue is empty.");

    _size--;
    shrink_capacity();
    return _data[inc_location()];
}

template <typename T>
T ABQ<T>::peek() const
{
    if (_size == 0)
    throw std::runtime_error("Queue is empty.");

    return _data[_location];
}

template <typename T>
unsigned int ABQ<T>::getSize() const
{
    return _size;
}

template <typename T>
unsigned int ABQ<T>::getMaxCapacity() const
{
    return _capacity;
}

template <typename T>
T* ABQ<T>::getData() const
    {
        return _data;
    }

// DEBUGGER
template <typename T> 
void ABQ<T>::print()
{
    cout << "_data contents: ";
    for (unsigned int i = 0; i < _capacity; i++)
    {
        cout << _data[i] << " ";
    }
    cout << endl;
    cout << "_capacity: " << _capacity << ", _size: " << _size << ", next dequeue: " << _data[_location] << endl;
}

template <typename T> 
unsigned int ABQ<T>::inc_location()
{
    _location++;
    return _location - 1;
}
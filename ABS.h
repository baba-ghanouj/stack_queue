#pragma once

#include <iostream>

using std::cout;
using std::endl;

//ABS class is a dynamic array implemented as a stack data structure
template <typename T>
class ABS                                       // Array-based stack
{
private:
    // Member variables
    T* _data;                                   // Data stored in the stack
    unsigned int _size;                         // Current size of the stack
    unsigned int _capacity;                     // Current max capacity of the stack

    // Class variable
    float scale_factor = 2.0f;                  // Scale factor for adjusting _capacity
    
    // Private behaviors
    void shrink_capacity();                     // Reduce the capacity of the dynamic array
    void increase_capacity();                   // Increase capacity of dynamic array
    void add(T object);                         // Add a new object to the dynamic array
    void copy_from_object(const ABS& object);   // Tool for copy constructor and copy assignment

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

    // Debug
    void print();                               // Debug tool that prints all member variables
};

/*
* Shrinks _capacity if (size / capacity < 1 / SCALE_FACTOR).
*/
template <typename T>
void ABS<T>::shrink_capacity()
{
    float size = getSize();
    float capacity = getMaxCapacity();

    if (size / capacity < 1 / scale_factor)
    {  
        // Allocate memory for new array to store transferred objects
        _capacity = _capacity / scale_factor;
        T *resized_data = new T[_capacity + 1];

        // Transfer objects from old array to new array according to _size
        for (unsigned int i = 0; i < _size + 1; i++)
            {
                resized_data[i] = _data[i];
            }
        
        // Delete old array
        delete[] _data;
        // Assign _data to new array.
        _data = resized_data; 
    }
}

/*
* Increases _capacity if (_size == _capacity).
*/
template <typename T>
void ABS<T>::increase_capacity()
{
    if (_size == _capacity)
    {
        // Allocate memory for new array to store transferred objects
        _capacity = _capacity * scale_factor;
        T *resized_data = new T[_capacity];

        // Transfer objects from old array to new array according to _size
        for (unsigned int i = 0; i < _size; i++)
            {
                resized_data[i] = _data[i];
            }

        // Delete old array
        delete[] _data;
        // Assign _data to new array.
        _data = resized_data;
    }
}

/*
* Helper function.
* Adds new object to end of stack and increases size.
*
* Dependencies:
* - copy_from_object()
* - push()
*/
template <typename T>
void ABS<T>::add(T object)
{
    _data[_size] = object;
    _size++;
}

/*
* Helper function.
* Performs a member-to-member copy and allocates new dynamic memory for _data.
* 
* Parameter:
* - object: stack object (rhs) to be copied into another stack object.
*
* Dependencies:
* - copy constructor
* - copy assignment operator
*/
template <typename T>
void ABS<T>::copy_from_object(const ABS& object)
{
    _size = object._size;
    _capacity = object._capacity;
    _data = new T[_capacity];

    for (unsigned int i = 0; i < object._size; i++)
        add(object[i]);
}

/*
* Default constructor.
*/
template <typename T>
ABS<T>::ABS()
{
    _size = 0;
    _capacity = 1;
    _data = new T[_capacity];
}

/*
* Constructor with assignment to _capacity.
*
* Parameter:
* - capacity: Value to which _capacity will be set for new stack.
*/
template <typename T>
ABS<T>::ABS(unsigned int capacity)
{
    _size = 0;
    _capacity = capacity;
    _data = new T[_capacity];
}

/*
* Copy constructor.
*/
template <typename T>
ABS<T>::ABS(const ABS& rhs)
{
    copy_from_object(rhs);
}

/*
* Copy assignment operator.
*/
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs)
{
    delete[] _data;
    copy_from_object(rhs);

    return *this;
}

/*
* Destructor.
*/
template <typename T>
ABS<T>::~ABS()
{
    delete[] _data;
}

/*
* Add a new object to the stack.
* If necessary, resize the stack to make room for new object.

Parameter:
* - data: Object to be added to the end of stack.
*/
template <typename T>
void ABS<T>::push(T data)
{
    increase_capacity();
    add(data);
}

/*
* Remove the first object from the stack.
* If necessary, resize the stack to conserve memory.
* 
* Returns:
* Removed object.
*/
template <typename T>
T ABS<T>::pop()
{
    if (_size == 0)
        throw std::runtime_error("Stack is empty.");

    _size--;
    shrink_capacity();
    return _data[_size];
}

/*
* View the first object in the stack.
*/
template <typename T>
T ABS<T>::peek() const
{
    if (_size == 0)
    throw std::runtime_error("Stack is empty.");

    return _data[_size - 1];
}

/*
* Returns:
* Current size of the stack.
*/
template <typename T>
unsigned int ABS<T>::getSize() const
{
    return _size;
}

/*
* Returns:
* Current capacity of the stack.
*/
template <typename T>
unsigned int ABS<T>::getMaxCapacity() const
{
    return _capacity;
}

/*
* Returns:
* Stack's dynamic array.
*/
template <typename T>
T* ABS<T>::getData() const
    {
        return _data;
    }

/*
* Debug tool for printing all member variables of a stack.
*/
template <typename T> 
void ABS<T>::print()
{
    cout << "_data contents: ";
    for (unsigned int i = 0; i < _capacity; i++)
    {
        cout << _data[i] << " ";
    }
    cout << endl;
    cout << "_capacity: " << _capacity << " _size: " << _size << endl;
}



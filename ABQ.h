#pragma once

#include <iostream>

using std::cout;
using std::endl;

// ABQ class is a dynamic array that functions as a queue data structure.
template <typename T>
class ABQ                                       // Array-based queue
{
private:
    // Member variables
    T* _data;                                   // Data stored in the queue
    unsigned int _size;                         // Current size of the queue
    unsigned int _capacity;                     // Current max capacity of the queue
    unsigned int _location;                     // Track the first position of the queue

    // Class variable
    float SCALE_FACTOR = 2.0f;                  // Scale factor for adjusting _capacity
    
    // Private behaviors
    void shrink_capacity();                     // Reduce the capacity of the dynamic array
    void increase_capacity();                   // Increase capacity of dynamic array
    void add(T object);                         // Add a new object to the dynamic array
    void copy_from_object(const ABQ& object);   // Tool for copy constructor and copy assignment
    unsigned int inc_location();                // Increment the first first position of the queue

    public:
    // Constructors
    ABQ();                                      // Default constructor
    ABQ(unsigned int capacity);                 // Constructor with specified capacity
    ABQ(const ABQ& rhs);                        // Copy constructor

    ABQ& operator=(const ABQ& rhs);             // Copy assignment operator
    
    ~ABQ();                                     // Destructor

    // Behaviors
    void enqueue(T data);                       // Add to queue
    T dequeue();                                // Remove and return last item in queue
    
    // Accessors
    T peek() const;                             // Return last item in queue
    unsigned int getSize() const;               // _size getter
    unsigned int getMaxCapacity() const;        // _capacity getter
    T* getData() const;                         // _data getter

    // Debug
    void print();                               // Debug tool that prints all member variables.
};

/*
* Shrinks _capacity if (size / capacity < 1 / SCALE_FACTOR).
*/
template <typename T>
void ABQ<T>::shrink_capacity()
{
    float size = getSize();
    float capacity = getMaxCapacity();

    if (size / capacity < 1 / SCALE_FACTOR)
    {  
        _capacity = _capacity / SCALE_FACTOR;
        // Allocate memory for new array to store transferred objects
        T *resized_data = new T[_capacity + 1];
        
        // Transfer objects from old array to new array according to _size
        for (unsigned int i = 0; i < _size + 1; i++)
        {
            // _data[_location] will give the position of the first object in queue
            resized_data[i] = _data[i + _location];
        }
        
        // Delete old array
        delete[] _data;
        // Assign _data to new array.
        _data = resized_data;
        // Reset the tracked position of the queue
        _location = 0; 
    }
}

/*
* Increases _capacity if (_size == _capacity).
*/
template <typename T>
void ABQ<T>::increase_capacity()
{
    if (_size == _capacity)
    {
        _capacity = _capacity * SCALE_FACTOR;
        // Allocate memory for new array to store transferred objects
        T *resized_data = new T[_capacity];
        
        // Transfer objects from old array to new array according to _size
        for (unsigned int i = 0; i < _size; i++)
        {
            // _data[_location] will give the position of the first object in queue
            resized_data[i] = _data[i + _location];
        }

        // Delete old array
        delete[] _data;
        // Assign _data to new array.
        _data = resized_data;
        // Reset the tracked position of the queue
        _location = 0; 
    }
}

/*
* Helper function.
* Adds new object to end of queue and increases size.
*
* Dependencies:
* - copy_from_object()
* - enqueue()
*/
template <typename T>
void ABQ<T>::add(T object)
{
    _data[_size] = object;
    _size++;
}

/*
* Helper function.
* Performs a member-to-member copy and allocates new dynamic memory for _data.
* 
* Parameter:
* - object: Queue object (rhs) to be copied into another queue object.
*
* Dependencies:
* - copy constructor
* - copy assignment operator
*/
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

/*
* Helper function.
* Increments _location and returns (_location - 1). 
* Dependencies:
* - dequeue()
*/
template <typename T> 
unsigned int ABQ<T>::inc_location()
{
    _location++;
    return _location - 1;
}

/*
* Default constructor.
*/
template <typename T>
ABQ<T>::ABQ()
{
    _size = 0;
    _capacity = 1;
    _location = 0;
    _data = new T[_capacity];
}

/*
* Constructor with assignment to _capacity.
*
* Parameter:
* - capacity: Value to which _capacity will be set for new queue.
*/
template <typename T>
ABQ<T>::ABQ(unsigned int capacity)
{
    _size = 0;
    _capacity = capacity;
    _location = 0;
    _data = new T[_capacity];
}

/*
* Copy constructor.
*/
template <typename T>
ABQ<T>::ABQ(const ABQ& rhs)
{
    copy_from_object(rhs);
}

/*
* Copy assignment operator.
*/
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs)
{
    delete[] _data;
    copy_from_object(rhs);

    return *this;
}

/*
* Destructor.
*/
template <typename T>
ABQ<T>::~ABQ()
{
    delete[] _data;
}

/*
* Add a new object to the queue.
* If necessary, resize the queue to make room for new object.

Parameter:
* - data: Object to be added to the end of queue.
*/
template <typename T>
void ABQ<T>::enqueue(T data)
{
    increase_capacity();
    add(data);
}

/*
* Remove the first object from the queue.
* If necessary, resize the queue to conserve memory.
* 
* Returns:
* Removed object.
*/
template <typename T>
T ABQ<T>::dequeue()
{
    if (_size == 0)
        throw std::runtime_error("Queue is empty.");

    _size--;
    shrink_capacity();
    return _data[inc_location()];
}

/*
* View the first object in the queue.
*/
template <typename T>
T ABQ<T>::peek() const
{
    if (_size == 0)
    throw std::runtime_error("Queue is empty.");

    return _data[_location];
}

/*
* Returns:
* Current size of the queue.
*/
template <typename T>
unsigned int ABQ<T>::getSize() const
{
    return _size;
}

/*
* Returns:
* Current capacity of the queue.
*/
template <typename T>
unsigned int ABQ<T>::getMaxCapacity() const
{
    return _capacity;
}

/*
* Returns:
* Queue's dynamic array.
*/
template <typename T>
T* ABQ<T>::getData() const
    {
        return _data;
    }

/*
* Debug tool for printing all member variables of a queue.
*/
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

#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
const int MINIMUM_CAPACITY = 3;
using namespace std;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY)
{
    //make new dynamic array with capacity and return it
    T *p = new T[capacity];
    return p;
    // return new T[capacity];
}

template<class T>
void print(T* a, unsigned int how_many, ostream& outs = cout)
{
    //walk through array and print each element
    T* walker = a;
    for (int i = 0; i < how_many; ++i)
    {
        cout << *walker << " ";
        walker++;
    }
    // cout << endl;
}

template<class T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout)
{
    //print size / capacity
    cout << "(" << size << "/" << capacity << ")";
    // print(a, size);
}

template<class T>
T *search_entry(T *a, int size, const T &find_me)
{
    /*walk through array, compare dereferenced walker to find_me
    and return the address*/
    T* walker = a;
    for (int i = 0; i < size; ++i)
    {
        if (*walker == find_me)
        { 
            return walker;
        }
        walker++;
    }
    return nullptr;
}

template<class T>
int search(T *a, int size, const T &find_me) 
{
    /*walk through array, compare dereferenced walker to find_me
    and return i (not address)*/
    T* walker = a;
    for (int i = 0; i < size; ++i)
    {
        if (*walker == find_me)
        {
            return i;
        }
        walker++;
    }
    return -1;
}

template<class T>
void shift_left(T *a, int &size, int shift_here) 
{
    // T* walker = a + shift_here;
    // T* walker2 = a + shift_here  + 1;
    // for (int i = shift_here; i < size; ++i)
    // {
    //     // *walker += 1;
    //     *walker = *walker2;
    //     walker++;
    //     walker2++;
    // }
    // size--;
    /*2 walkers, one starts in front of the other
    begin walking at index of shifting and end at size-1 to prevent
    array from messing with null characters
    assign walker2 to walker and add*/
    T* walker = a + shift_here + 1;
    T* walker2 = a + shift_here;
    for (int i = shift_here; i < size-1; ++i)
    {
        *walker2 = *walker;
        walker++;
        walker2++;
    }
    size--;
    // T* walker = a + shift_here + 1;
    // T* walker2 = a + shift_here;
    // if(size != 0)
    // {
    //     int i = shift_here;
    //     while(i < size)
    //     {
    //         *walker2 = *walker;
    //         walker++;
    //         walker2++;
    //         i++;
    //     }
    //     size--;
    // }
}

template <class T>
void shift_left(T* a, int& size, T* shift_here)
{
    /*subtracts addresses and stores into an integer, which is used
    as a parameter for the templated shift_here*/
    int p = shift_here - a;
    // T *p = shift_here - a;
    // a = shift_here + *p;
    // cout<<"shift left with ptr. index: "<<shift_here - p<<endl;
    // cout << p << endl;
    /**/
    shift_left(a, size, p);
}

template <class T>
void shift_right(T *a, int &size, int shift_here)
{
    /*two walkers, starting from the end of the array (one in front
    of the other)
    begin walking at end of the array going backwards, assigning
    walker2 to walker as long as i is greater than 
    the index that is desired to shift at*/
    T* walker = a + size - 1;
    T* walker2 = a + size;
    for (int i = size; i > shift_here; --i)
    {
        *walker2 = *walker;
        walker--;
        walker2--;
    }
    size++;
    // for (int i = size; i > shift_here-1; --i)
    // {
    //     *walker2 = *walker;
    //     walker--;
    //     walker2--;
    // }
    // size++;
    // T* walker = a + size - 1;
    // T* walker2 = a + size;
    // int i = size;
    // if(i != 0)
    // {
    //     while(i >= shift_here)
    //     {
    //         *walker2 = *walker;
    //         walker--;
    //         walker2--;
    //         i--;
    //     }
    //     size++;
    // }
}

template<class T>
void shift_right(T *a, int &size, T* shift_here)
{
    /*same logic as templated shift_here on shift left
    subtracts addresses and stores into an integer, which is used
    as a parameter for the templated shift_here*/
    int p = shift_here - a;
    shift_right(a, size, p);
}

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy)
{
    /*make pointers for source and destination
    for loop while i is less than size (many_to_copy)
    assign destination to source*/
    const T *p = src;
    T *p2 = dest;

    // for (int i = 0; i < many_to_copy; ++i)
    // {
    //     *dest = *src;
    //     src++;
    //     dest++;
    // }

    if (src != NULL)
    {
        while (p != src + many_to_copy)
        {
        *p2++ = *p++;
        }
    }
}

template <class T>
T* copy_array(const T *src, int size)
{
    /*begin by allocating extra space to be used, then 
    copy given the new allocated array, source, and size*/
    
    T *p = allocate<T>(size);
    copy_array(p, src, size);
    return p;
}

template <class T>
string array_string(const T *a, int size)
{
    /*begin with empty string and setting a constant walker to a
    use tostring and add each value of array to empty string, then
    return it*/
    string s = "";
    const T* walker = a;
    for (int i = 0; i < size; ++i)
    {
        s += to_string(*walker);
        walker++;
    }
    return s;
}

// template<class T>
// T* reallocate(T* a, int size, int capacity)
// {
//     T *p = allocate<T>(capacity);
//     copy_array(p, a, size);

//     T* newarr = new T[capacity];

//     T* walker = p;

//     for (int i = 0; i < size; ++i)
//     {
//         T* p2 = newarr + i;
//         *walker = *p2;
//         walker++;
//     }

//     delete [] a;

//     return newarr;
// }

template<class T>
T* reallocate(T* a, int size, int capacity)
{
    /*make new dynamic array with capacity,
    then copy array (also allocates new space)
    then delete old array and return the new one*/
    T *p = new T[capacity];
    copy_array(p, a, size);
    delete [] a;
    return p;
}

#endif
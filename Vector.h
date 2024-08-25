#ifndef VECTOR_H
#define VECTOR_H

#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <cstddef>

template <typename T> 
class Vector
{
private:
    size_t size;
    size_t max_size;
    T* vec;
    void* mem_alloc(void* adr)
    {
        return mmap(adr, sizeof(T), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    };
    void repopulate(T val)
    {
        T* replacement = new T[size+1];
        for(int i = 0; i < size; i++)
        {
            replacement[i] = vec[i];
            std::cout<<vec[i]<<std::endl;
        }
        std::cout<<size<<std::endl;
        replacement[size] = val;
        // std::cout<<replacement[size]<<std::endl;
        size++;
        delete[] vec;
        vec = replacement;
        std::cout << "REPOPULATING\n"<<std::endl;
    };
public:
    Vector():
    size(0), max_size(-1)
    {
        vec = new T;
    };

    Vector(size_t max_size):
    max_size(max_size), size(0)
    {
        vec = new T;
    };
    
    void push_back(T val)
    {
        if(max_size == size) return;
        // if(size == 0)
        // {
        //     *vec = val;
        //     return;
        // }
        std::cout<<vec<<std::endl;
        std::cout<<vec+size<<std::endl;
        void* ptr = mem_alloc(vec+size);
        if(ptr == (void*)-1)
        {
            repopulate(val);
        }
        else
        {
            vec[size] = val;
            size++;
        }
    }
};


#endif
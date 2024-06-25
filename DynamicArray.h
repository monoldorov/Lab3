#include<exception>
#include<string.h>
using namespace std;

template<class T>
class DynamicArray {
    private:
        T* elements;
        size_t size;
        size_t capacity;
    public:
        DynamicArray(T* items, size_t count) {
            if (count <= 0)
                throw out_of_range("Wrong size!");

            elements = new T[count * 2];
            size = count;
            capacity = count * 2;
            for (size_t i = 0; i != count; ++i) {
                elements[i] = items[i];
            }
        }
        DynamicArray(std::initializer_list<T> items)
        {
            elements = new T[items.size()];
            this->size = items.size();
            this->capacity = items.size();
            size_t i = 0;
            for (auto &item : items)
            {
                (*this)[i] = item;
                ++i;
            }
        }
        DynamicArray(size_t size) {
            if (size <= 0) 
                throw out_of_range("Wrong size!");

            elements = new T[size];
            this->size = size;
            this->capacity = 2 * size;
        }

        DynamicArray() {
            elements = new T[0];
            this->size = 0;
            this->capacity = 0;
        }

        DynamicArray(const DynamicArray<T> & dynamicArray) {
            elements = new T[dynamicArray.GetLength()];
            this->size = dynamicArray.GetLength();
            this->capacity = dynamicArray.GetLength() * 2;
            for (int i = 0; i != dynamicArray.GetLength(); ++i) {
                elements[i] = dynamicArray.Get(i);
            }
        }

        T& Get(size_t index) const {
            if (index < 0 || index >= size)
                throw out_of_range("Uncorrect index!");

            return elements[index];
        }

        size_t GetSize() const {
            return this->size;
        }

        void Set(size_t index, T value) {
            if (index < 0 || index >= size)
                throw out_of_range("Uncorrect index!");
            elements[index] = value;
        }

        void Resize(size_t newSize) {
            if (newSize < 0) 
                throw std::length_error("Size is wrong!");
            
            if (newSize >= this->capacity) {
                this->capacity = newSize * 2;
                T* copied = new T[size];
                for (size_t i = 0; i != size; ++i)
                    copied[i] = elements[i];

                this->size = newSize;
                elements = new T[capacity];
                for (size_t i = 0; i != size; ++i)
                    elements[i] = copied[i];

                delete[] copied;
            } else {
                this->size = newSize;
            }
        }

        DynamicArray<T>* GetSubArray(size_t startIndex, size_t endIndex) {
            if (startIndex < 0 || endIndex >= this->size || (endIndex < startIndex))
                throw out_of_range("Index out of range!");
            DynamicArray<T> *newArray = new DynamicArray<T>(endIndex - startIndex);
            for (size_t i = 0; i != endIndex - startIndex; ++i) {
                newArray->Set(i, this->Get(i + startIndex));
            }
            return newArray;
        }

        ~DynamicArray() {
            delete[] elements;
        }

        DynamicArray<T>& operator=(const DynamicArray<T>& array) {
            this->elements = new T[array.GetSize()];
            for (size_t i = 0; i < array.GetSize(); ++i)
                elements[i] = array.Get(i);
            this->size = array.GetSize();
        }
};

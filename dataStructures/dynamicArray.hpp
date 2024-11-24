#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <stdexcept> // For std::out_of_range
#include <algorithm>
#include <string>

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

template <typename T>
class DynamicArray {

public:
    public:
    // Métodos adicionales para compatibilidad con range-based for loops
    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return data_ + size_;
    }

    /**
     *  Default constructor. The array is empty.            
     */
    DynamicArray() = default;


    DynamicArray(unsigned long long int size) : size_(size), capacity_(size) 
    {
        data_ = new T[capacity_];
    } 


    /**
     *  Constructor that initializes all elements with a constant value.
     */
    DynamicArray(const T& value, unsigned long long int size) : size_(size), capacity_(size)
    {
        data_ = new T[size_];
        for (unsigned long long int i = 0; i < size_; ++i)
            data_[i] = value;
    }

    /**
     *  Copy constructor.
     */
    DynamicArray(const DynamicArray& other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[size_];
        for (unsigned long long int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }    

    /**
     *  Move constructor.
     */
    DynamicArray(DynamicArray&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /**
     *  Destructor. Deallocates the memory.
     */
    ~DynamicArray()
    {
        if (data_ != nullptr)
            delete[] data_;
    }

    /**
     *  Copy assignment operator.
     */
    DynamicArray& operator=(const DynamicArray& other) 
    {
        if (this != &other) {

            if (data_ != nullptr)
                delete[] data_;

            size_ = other.size_;
            data_ = new T[size_];
            
            for (unsigned long long int i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        }

        return *this;
    }

    /**
     *  Move assignment operator.
     */
    DynamicArray& operator=(DynamicArray&& other) noexcept 
    {
        if (this != &other) {

            if (data_ != nullptr)
                delete[] data_;

            data_ = other.data_;
            size_ = other.size_;

            other.data_ = nullptr;
            other.size_ = 0;
        }

        return *this;
    }   
    

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& array)
    {   
        os << "[ ";

        if (array.empty())
        {
            os << "]";
        }
        else
        {
            for (unsigned long long int i = 0; i < array.size_; ++i)  
            {
                if (i != array.size_ - 1)
                {
                    os << array[i] << ", ";                         
                }
                else
                {
                    os << array[i] << " ]";
                }
            }
        }
        
        return os;
    }


    /**
     *  Returns the size of the array.
     */
    unsigned long long int size() const
    {
        return size_;
    }    


    unsigned long long int capacity() const 
    {
        return capacity_;
    }


    /**
     *  Checks if the array is empty.
     */
    bool empty() const
    {
        return size_ == 0;
    }

    /**
     *  Access an element of the array (without bound checking).
     *
     *  @param[in]  index   The index of the element to access.
     *
     *  @return The element at the given index.
     */
    T& operator[](unsigned long long int index)
    {
        return data_[index];
    }

    /**
     *  Access an element of the array (without bound checking).
     *
     *  @param[in]  index   The index of the element to access.
     *
     *  @return The element at the given index.
     */
    const T& operator[](unsigned long long int index) const
    {
        return data_[index];
    }

    /**
     *  Access an element of the array (with bound checking).
     *
     *  @param[in]  index   The index of the element to access.
     *
     *  @return The element at the given index.
     */
    T& at(unsigned long long int index)
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    /**
     *  Access an element of the array (with bound checking).
     *
     *  @param[in]  index   The index of the element to access.
     *
     *  @return The element at the given index.
     */
    const T& at(unsigned long long int index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    /**
     *  Access the first element of the array.
     */
    T& front()
    {
        return data_[0];
    }

    /**
     *  Access the first element of the array.
     */
    const T& front() const
    {
        return data_[0];
    }

    /**
     *  Access the last element of the array.
     */
    T& back()
    {
        return data_[size_ - 1];
    }

    /**
     *  Access the last element of the array.
     */
    const T& back() const
    {
        return data_[size_ - 1];
    }

    /**
     *  Fills the array with a value.
     *
     *  @param[in]  value   The value to fill the array with.
     */
    void fill(const T& value)
    {
        for (unsigned long long int i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    /**
     *  Finds the index of a value in the array.
     *
     *  @param[in]  value   The value to be found.
     *
     *  @return The index of the value in the array, or -1 if the value is not found.
     */
    long long int find(const T& value)
    {
        int index = -1;

        for (int i = 0; i < (int)size_; ++i) {
            if (data_[i] == value) {
                index = i;
                break;
            }
        }

        return index;
    }

    /**
     *  Clears the array and deallocates the memory.
     */
    void clear() 
    {
        if (data_ != nullptr)
            delete[] data_;

        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }    


    /**
     *  Inserts a new element at a specific position.
     *
     *  @param  index   The position where the element will be inserted.
     */
    void insert(unsigned long long int index, const T& value) 
    {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }

        resize(size_ + 1);

        for (unsigned long long int i = size_ - 1; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
    }

    /**
     *  Erases an element at a specific position.
     *
     *  @param[in]  index   The position of the element to erase.
     */
    void erase(unsigned long long int index) 
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }

        for (unsigned long long int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }

        resize(size_ - 1);
    }

    /**
     *  Inserts a new element at the end of the array.
     *
     *  @param[in]  value   The value to insert.
     */
    void push_back(const T& value) 
    {
        resize(size_ + 1);
        data_[size_ - 1] = value;
    }

    /**
     *  Removes the last element of the array.
     */
    void pop_back() 
    {
        if (size_ > 0) {
            resize(size_ - 1);
        }
    }

    /**
     *  Inserts a new element at the front of the array.
     * 
     *  @param[in]  value   The value to insert.
     */
    void push_front(const T& value) 
    {
        insert(0, value);
    }

    /**
     *  Removes the first element of the array.
     */
    void pop_front() 
    {
        erase(0);
    }


    /**
     *  Resizes the array and fills the new elements with a value.
     *
     *  @param  newSize The new size of the array.
     *  @param  value   The value to fill the new elements with.
     */
    void resize(unsigned long long int newSize)
    {
        if (newSize > capacity_)
        {
            capacity_ = 1;
            while (capacity_ < newSize)
            {
                capacity_ *= 2;
            }
            
            T* newData = new T[capacity_];
            for (unsigned long long int i = 0; i < size_; ++i) {
                newData[i] = data_[i];
            }

            delete[] data_;
            data_ = newData;               
        }
        
        size_ = newSize;
    }


    /**
     *  Resizes the array and fills the new elements with a value.
     * 
     *  @param  newSize The new size of the array.
     *  @param  value   The value to fill the new elements with.
     */
    void resize(unsigned long long int newSize, const T& value)
    {
        if (newSize > capacity_)
        {
            capacity_ = 1;
            while (capacity_ < newSize)
            {
                capacity_ *= 2;
            }
            
            T* newData = new T[capacity_];
            for (unsigned long long int i = 0; i < size_; ++i) {
                newData[i] = data_[i];
            }
            

            for (unsigned long long int i = size_; i < newSize; ++i) {
                newData[i] = value;
            }

            delete[] data_;
            data_ = newData;               
        }
        else
        {
            for (unsigned long long int i = size_; i < newSize; ++i) 
            {
                data_[i] = value; 
            }
        }
        
        size_ = newSize;    
    }

    void verificarOrden() const {
    bool ordenado = true;
    for (unsigned long long int i = 0; i < size_ - 1; ++i) {
        if (toLower(data_[i].name) > toLower(data_[i + 1].name)) {
            std::cout << "Desorden detectado entre: " 
                      << data_[i].name << " y " << data_[i + 1].name << std::endl;
            ordenado = false;
        }
    }
    if (ordenado) {
        std::cout << "El array está ordenado correctamente.\n";
    } else {
        std::cout << "El array tiene elementos fuera de orden.\n";
    }
}

private:

    T* data_{nullptr}; // Pointer to the dynamic array

    unsigned long long int size_{0}; // Current size of the array

    unsigned long long int capacity_{0}; 
};

#endif
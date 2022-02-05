#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include <cstdint>
#include <cstring>

#include <memory>
#include <string>
#include <sstream>
#include <utility>

namespace adt {
template <typename T>
class Array {
 public:
    static std::unique_ptr<Array> create(const size_t& capacity=static_cast<size_t>(DEFAULT_CAPACITY)) {
        if (0 < capacity) {
            return std::unique_ptr<Array>(new Array(capacity));
        }

        return nullptr;
    }

    static std::unique_ptr<Array> create(const size_t&& capacity) {
        if (0 < capacity) {
            return std::unique_ptr<Array>(new Array(capacity));
        }

        return nullptr;
    }

    Array(const Array& other) {
        mpData.reset(new T[other.mCapacity]);
        for (size_t i = 0; i < other.mSize; i++) {
            mpData[i] = other.mpData[i];
        }

        mSize = other.mSize;
        mCapacity = other.mCapacity;
    }

    Array& operator=(const Array& other) {
        if (&other != this) {
            this->mpData.reset(new T[other.mCapacity]);
            for (size_t i = 0; i < other.mSize; i++) {
                this->mpData[i] = other.mpData[i];
            }

            this->mSize = other.mSize;
            this->mCapacity = other.mCapacity;
        }

        return *this;
    }

    Array(Array&& other) {
        mpData = std::move(other.mpData);
        mSize = other.mSize;
        other.mSize = 0;

        mCapacity = other.mCapacity;
        other.mCapacity = 0;
    }

    Array& operator=(Array&& other) {
        if (&other != this) {
            this->mpData = std::move(other.mpData);
            this->mSize = other.mSize;
            other.mSize = 0;

            this->mCapacity = other.mCapacity;
            other.mCapacity = 0;
        }

        return *this;
    }

    ~Array() {
        mSize = 0;
        mCapacity = 0;
    }

    std::string toString() const {
        std::stringstream ss;

        ss << "[";
        for (size_t i = 0; i < mSize; i++) {
            ss << mpData[i] << " ";
        }

        ss << "]";

        return ss.str();
    }

    bool add(const T& value) {
        if (mSize < mCapacity) {
            mpData[mSize++] = value;
            return true;
        }

        return false;
    }

    bool add(const T&& value) {
        if (mSize < mCapacity) {
            mpData[mSize++] = value;
            return true;
        }

        return false;
    }

    bool insert(const T& value, const size_t index) {
        if (isFull()) {
            return false;
        }

        if (mSize <= index) {
            return false;
        }

        size_t tmp = mSize;
        while (index < tmp) {
            mpData[tmp] = mpData[tmp - 1];
            tmp--;
        }

        mpData[index] = value;
        mSize++;

        return true;
    }

    bool insert(const T&& value, const size_t index) {
        T tmpValue = value;
        return insert(tmpValue);
    }

    bool remove(size_t index) {
        if (mSize <= index) {
            return false;
        }

        size_t tmp = index + 1;
        while (mSize > tmp) {
            mpData[index++] = mpData[tmp++];
        }

        mSize--;

        return true;
    }

    ssize_t locate(const T& value) {
        for (size_t i = 0; i < mSize; i++) {
            if (value == mpData[i]) {
                return i;
            }
        }

        return false;
    }

    ssize_t locate(const T&& value) {
        T tmpValue = value;
        return locate(tmpValue);
    }

    T get(const size_t index) const {
        return mpData[index];
    }

    bool set(const T& value, const size_t index) {
        if (mSize <= index) {
            return false;
        }

        mpData[index] = value;
    }

    bool set(const T&& value, const size_t index) {
        if (mSize <= index) {
            return false;
        }

        mpData[index] = value;
    }

    T& operator[](const size_t& index) {
        return mpData[index];
    }

    ssize_t locateMax() {
        if (isEmpty()) {
            return static_cast<ssize_t>(-1);
        }

        size_t index = 0;
        size_t maxIndex = index++;

        while (mSize > index) {
            if (mpData[maxIndex] < mpData[index]) {
                maxIndex = index++;
            } else {
                index++;
            }
        }

        return maxIndex;
    }

    ssize_t locateMin() {
        if (isEmpty()) {
            return static_cast<ssize_t>(-1);
        }

        size_t index = 0;
        size_t minIndex = index++;

        while (mSize > index) {
            if (mpData[minIndex] > mpData[index]) {
                minIndex = index++;
            } else {
                index++;
            }
        }

        return minIndex;
    }

    bool reverse() {
        if (isEmpty()) {
            return false;
        }

        size_t li = 0;
        size_t ri = mSize - 1;

        T tmpValue;
        while (li < ri) {
            tmpValue = mpData[li];
            mpData[li++] = mpData[ri];
            mpData[ri--] = tmpValue;
        }

        return true;
    }

    bool rotate(const size_t count) {
        if (mSize <= count) {
            return false;
        }

        T tmpBuf[count];

        ssize_t i;
        for (i = 0; i < count; i++) {
            tmpBuf[i] = mpData[mSize - count - 1 + i];
        }

        i = (mSize - count - 1);
        while (0 <= i) {
            mpData[i + count] = mpData[i];
            i--;
        }

        for (i = 0; i < count; i++) {
            mpData[i] = tmpBuf[i];
        }

        return true;
    }

    bool isFull() {
        return (mCapacity == mSize);
    }

    bool isEmpty() {
        return (0 == mSize);
    }

    size_t getSize() {
        return mSize;
    }

    size_t getCapacity() {
        return mCapacity;
    }

    static constexpr size_t DEFAULT_CAPACITY = 1024;

 protected:
    explicit Array(const size_t& capacity) {
        mpData.reset(new T[capacity]);
        mCapacity = capacity;
        mSize = 0;
    }

    explicit Array(const size_t&& capacity) {
        mpData.reset(new T[capacity]);
        mCapacity = capacity;
        mSize = 0;
    }

 private:
    std::unique_ptr<T[]> mpData;
    size_t mSize;
    size_t mCapacity;
};

}   // namespace adt

#endif // __ARRAY_HPP__

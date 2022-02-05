#include <cstdio>
#include <memory>
#include <utility>

#include "Array.hpp"

#define log(str) printf("[%s][%d] %s", __func__, __LINE__, str)
#define logf(fmt, ...) printf("[%s][%d] " fmt, __func__, __LINE__, __VA_ARGS__)

int main() {
    std::unique_ptr<adt::Array<int>> arr = adt::Array<int>::create();
    int i = 10;
    arr->add(i++);
    arr->add(i++);
    arr->add(i++);
    arr->add(i++);
    arr->add(i++);
    arr->add(16);

    logf("Array 0: %s\n", arr->toString().c_str());

    if (arr->insert(i, arr->getSize() - 1)) {
        logf("-> Array 0: %s\n", arr->toString().c_str());
    } else {
        logf("Failed to insert %d at %d\n", i, static_cast<int>(arr->getSize() - 1));
    }

    i = 12;
    logf("Found %d at %d\n", i, static_cast<int>(arr->locate(i)));

    i = arr->locateMin();
    if (0 > i) {
        log("Could not locate Min value!\n");
    } else {
        logf("Min: %d at %d\n", (*arr.get())[i], i);
    }

    i = arr->locateMax();
    if (0 > i) {
        log("Could not locate Min value!\n");
    } else {
        logf("Min: %d at %d\n", (*arr.get())[i], i);
    }

    adt::Array<int> arr1(*arr.get());
    arr1.reverse();
    logf("Array 1: %s\n", arr1.toString().c_str());

    adt::Array<int> arr2(std::move(*arr.get()));
    arr2.remove(2);
    arr2.rotate(3);
    logf("Array 2: %s\n", arr2.toString().c_str());

    logf("Array 1 is empty? %s\n", arr->isEmpty()? "true":"false");

    return 0;
}

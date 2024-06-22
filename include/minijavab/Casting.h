#pragma once
#include <cstdint>

namespace MiniJavab {
namespace cast {

template <typename T>
bool GetAsBool(T value) {
    bool* ptr = reinterpret_cast<bool*>(const_cast<T*>(&value));
    return *ptr;
}

template <typename T>
uint8_t GetAsU8(T value) {
    uint8_t* ptr = reinterpret_cast<uint8_t*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
uint32_t GetAsU32(T value) {
    uint32_t* ptr = reinterpret_cast<uint32_t*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
uint64_t GetAsU64(T value) {
    uint64_t* ptr = reinterpret_cast<uint64_t*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
float GetAsF32(T value) {
    float* ptr = reinterpret_cast<float*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
double GetAsF64(T value) {
    double* ptr = reinterpret_cast<double*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
int8_t GetAsI8(T value) {
    int8_t* ptr = reinterpret_cast<int8_t*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
int32_t GetAsI32(T value) {
    int32_t* ptr = reinterpret_cast<int32_t*>(const_cast<T*>(&value));
    return *ptr;
}
template <typename T>
int64_t GetAsI64(T value) {
    int64_t* ptr = reinterpret_cast<int64_t*>(const_cast<T*>(&value));
    return *ptr;
}

}} // end namespace
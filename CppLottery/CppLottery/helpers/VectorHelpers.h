#pragma once
#include <vector>

template<typename T, typename Property>
bool propertyExists(const std::vector<T>& vec, Property T::* property, const Property& value) {
    for (const auto& obj : vec) {
        if (obj.*property == value) {
            return true;
        }
    }
    return false;
}

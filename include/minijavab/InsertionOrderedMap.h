#pragma once

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <list>

template <typename TKey, typename TValue> class InsertionOrderedMap;

/// Implements a custom iterator for properly traversing the ordered map
/// @tparam TKey The key type of the map
/// @tparam TValue The value type of the map
template <typename TKey, typename TValue> struct InsertionOrderedMapIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;

    InsertionOrderedMapIterator(InsertionOrderedMap<TKey, TValue>* data, size_t index)
        : _container(data),
        _index(index)
        {}

    std::pair<TKey&, TValue&> operator*() {
        TValue& second = _container->_storage[_index];
        TKey& first = _container->_reverseLookupMap[second];
        return std::pair<TKey&, TValue&>(first, second);
    }
    std::shared_ptr<std::pair<TKey&, TValue&>> operator->() {
        TValue& second = _container->_storage[_index];
        TKey& first = _container->_reverseLookupMap[second];
        return std::make_shared<std::pair<TKey&, TValue&>>(first, second);
    }
    InsertionOrderedMapIterator& operator++() {
        _index += 1;
        return *this;
    }
    InsertionOrderedMapIterator& operator++(int i) {
        _index += 1;
        return *this;
    }
    friend bool operator== (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index == b._index;
    };
    friend bool operator!= (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index != b._index;
    };
    friend bool operator> (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index > b._index;
    }
    friend bool operator>= (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index >= b._index;
    }
    friend bool operator< (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index < b._index;
    }
    friend bool operator<= (const InsertionOrderedMapIterator& a, const InsertionOrderedMapIterator& b) {
        return a._index <= b._index;
    }

    private:
        /// The current traversal index within the map. This value points within _storage in the map.
        size_t _index;

        /// The map that we're traversing over
        InsertionOrderedMap<TKey, TValue>* _container;
};

/// Implements a simple map data structure that maintains insertion order. This map is expected to be used
/// similarly to std::map and exposes a similar API. 
/// @example Inserting elements {1,2} results in a traversal starting at {1} and ending at {2}
/// @tparam TKey The key type of the map
/// @tparam TValue The value type of the map
template <typename TKey, typename TValue> class InsertionOrderedMap {
    public:
        using iterator = InsertionOrderedMapIterator<TKey, TValue>;

        /// Constructs an empty map
        InsertionOrderedMap() {}

        /// Get an iterator to the first element in the map
        /// @return An iterator starting at the first element in the map
        iterator begin() {
            return iterator(this, 0);
        }

        /// Get an iterator to the last element in the map
        /// @return An iterator starting at the last element in the map
        iterator end() {
            return iterator(this, _storage.size());
        }

        /// Insert a new unique value into the map. If the key already exists within the map, nothing happens
        /// @param valueToInsert The value to insert into the map
        /// @return An iterator to the location the element was inserted at
        iterator insert(std::pair<TKey, TValue>&& valueToInsert) {
            auto& [key, value] = valueToInsert;
            if (_lookupMap.find(key) == _lookupMap.end()) {
                _lookupMap.insert({key, _storage.size()});
                _reverseLookupMap.insert({value, key});
                _storage.push_back(value);
            }
            return end();
        }

        /// Search for an element within the map and return an iterator to it
        /// @param key The element's key to look for
        /// @return An iterator pointing to the element if it can be found, else end()
        iterator find(TKey&& key) {
            typename std::map<TKey, size_t>::iterator searchResult = _lookupMap.find(key);
            if (searchResult != _lookupMap.end()) {
                return iterator(this, searchResult->second);
            }
            return end();
        }

        /// @see find(TKey&& key)
        iterator find(TKey key) {
            typename std::map<TKey, size_t>::iterator searchResult = _lookupMap.find(key);
            if (searchResult != _lookupMap.end()) {
                return iterator(this, searchResult->second);
            }
            return end();
        }

        /// Get the number of elements stored in the map
        /// @return The number of elements in the map
        size_t size() {
            return _storage.size();
        }

    private:
        /// A mapping of keys to their location within _storage, used for finding elements in the map
        std::map<TKey, size_t> _lookupMap;

        /// A mapping of values to their associated keys, used for traversal
        std::map<TValue, TKey> _reverseLookupMap;

        /// A list of all the values stored within the map in the ordered they were inserted
        std::vector<TValue> _storage;
        friend struct InsertionOrderedMapIterator<TKey, TValue>;
};
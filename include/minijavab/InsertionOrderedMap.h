#include <map>
#include <vector>
#include <string>
#include <utility>
#include <list>

template <typename TKey, typename TValue> class InsertionOrderedMap;

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
        size_t _index;
        InsertionOrderedMap<TKey, TValue>* _container;
};

template <typename TKey, typename TValue> class InsertionOrderedMap {
    public:
        using iterator = InsertionOrderedMapIterator<TKey, TValue>;

        InsertionOrderedMap() {}

        iterator begin() {
            return iterator(this, 0);
        }
        iterator end() {
            return iterator(this, _storage.size());
        }

        iterator insert(std::pair<TKey, TValue>&& valueToInsert) {
            auto& [key, value] = valueToInsert;
            if (_lookupMap.find(key) == _lookupMap.end()) {
                _lookupMap.insert({key, _storage.size()});
                _reverseLookupMap.insert({value, key});
                _storage.push_back(value);
            }
            return end();
        }
        iterator find(TKey&& key) {
            typename std::map<TKey, size_t>::iterator searchResult = _lookupMap.find(key);
            if (searchResult != _lookupMap.end()) {
                return iterator(this, searchResult->second);
            }
            return end();
        }
        iterator find(TKey key) {
            typename std::map<TKey, size_t>::iterator searchResult = _lookupMap.find(key);
            if (searchResult != _lookupMap.end()) {
                return iterator(this, searchResult->second);
            }
            return end();
        }
        size_t size() {
            return _storage.size();
        }

    private:
        std::map<TKey, size_t> _lookupMap;
        std::map<TValue, TKey> _reverseLookupMap;
        std::vector<TValue> _storage;
        friend struct InsertionOrderedMapIterator<TKey, TValue>;
};
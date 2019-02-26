#pragma once
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <map>

template<template<typename T, typename Allocator> class Container, typename T, typename Allocator>
class WrappedSequenceContainer
{
private:
    Container<T, Allocator> container;

public:    
    WrappedSequenceContainer(){}

    WrappedSequenceContainer(const Container<T, Allocator> &vec) : container(vec.begin(), vec.end())
    {
        if (vec.begin() == vec.end())
            throw std::invalid_argument("Container should not be empty");
    }

    template<typename Op>
    T reduceLeft(Op f)
    {
        auto it_begin = container.begin();
        T ret = *it_begin;
        while(++it_begin != container.end())
            ret = f(ret, *it_begin );
        return ret;
    }

    template<typename Op>
    T reduceRight(Op f)
    {
        auto it_rbegin = container.rbegin();
        T ret = *it_rbegin;
        while(++it_rbegin != container.rend()){
            ret = f(ret, *it_rbegin );
        }
        return ret;
    }

    template<typename Op>
    WrappedSequenceContainer<Container, T, Allocator> filter(Op f)
    {
        WrappedSequenceContainer<Container, T, Allocator> ret;
        for (const auto &el : container)
            if(f(el))
                ret.container.emplace_back(el);
        return ret;
    }

    WrappedSequenceContainer<Container, T, Allocator> reverse()
    {
        WrappedSequenceContainer<Container, T, Allocator> ret;
        auto it_rbegin = container.rbegin();
        while(it_rbegin != container.rend()){
            ret.container.emplace_back(*it_rbegin++);
        }
        return ret;
    }

    template<typename Op>
    WrappedSequenceContainer<Container, decltype(std::declval<Op>()(std::declval<T>())), Allocator> map(Op f)
    {
        WrappedSequenceContainer<Container, decltype(std::declval<Op>()(std::declval<T>())), Allocator> ret;
        for(const auto &el : container)
            ret.emplace_back(f(el));
        return ret;
    }

    template<typename Op>
    std::map<decltype(std::declval<Op>()(std::declval<T>())), Container<T, Allocator>> groupBy(Op f)
    {
        std::map<decltype(std::declval<Op>()(std::declval<T>())), Container<T, Allocator>> ret;
        for(const auto &el : container)
            ret[f(el)].emplace_back(el);
        return ret;
    }

    template<typename Op>
    WrappedSequenceContainer<Container, typename decltype(std::declval<Op>()(std::declval<T>()))::value_type, Allocator> flatMap(Op f)
    {
        WrappedSequenceContainer<Container, typename decltype(std::declval<Op>()(std::declval<T>()))::value_type, Allocator> ret;
        this->map(f).foreach([&ret](const auto &item){ret.insert(ret, item);});
        return ret;
    }

    template<typename Op>
    void foreach(Op f)
    {
        for(const auto &el : container)
            f(el);
    }

    Container<T, Allocator> unWrap()
    {
        return container;
    }

    void emplace_back(const T &el)
    {
        container.emplace_back(el);
    }

    template<typename T1, typename T2>
    void insert(const T1 &destCont, const T2 &items)
    {
        container.insert(destCont.container.end(), items.begin(), items.end());
    }

    size_t size()
    {
        return container.size();
    }
};

template<template<typename T, typename Allocator> class Container, typename T>
WrappedSequenceContainer<Container, T, std::allocator<T>> wrap(const Container<T, std::allocator<T>> &v)
{
    return WrappedSequenceContainer<Container, T, std::allocator<T>>(v);
}

template<typename Key, typename T, template<typename...> class Container, typename... Args>
Container<Key, int, Args...> count(const Container<Key, T, Args...>& m)
{
    std::map<Key, int, Args...> cont;
    for (auto const& el : m)
        cont[el.first] = el.second.size();
    return cont;
}

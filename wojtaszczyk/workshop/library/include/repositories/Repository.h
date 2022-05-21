#ifndef CARRENTAL_REPOSITORY_H
#define CARRENTAL_REPOSITORY_H
#include "model/typedef.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "exceptions/ClientException.h"
#include "exceptions/RentException.h"
#include "exceptions/VehicleException.h"

template<class T, class U> class Repository {
protected:
    std::vector<std::shared_ptr<T>> objects;
public:
    std::shared_ptr<T> get(const unsigned int &i) const {
        if (i<size() && i>=0){
            return objects[i];}
        else
            throw U("Argument Error");
    }
    void add(std::shared_ptr<T> obj) {
        if(obj!= nullptr){
            objects.push_back(obj);
        }
        else{
            throw U("nullptr Error");
        }
    }
    void remove(std::shared_ptr<T> obj) {
        if(obj!= nullptr){
            objects.erase(std::remove(objects.begin(),objects.end(),obj),objects.end());
        }
        else{
            throw U("nullptr Error");
        }
    }
    std::string report() const {
        std::stringstream ss;
        unsigned int x=size();
        for (int i=0;i<x;i++)
        {
            ss << get(i)->getInfo() << '\n';
        }
        return ss.str();
    }
    unsigned int size() const{
        return objects.size();
    }
    template<class X>std::vector<std::shared_ptr<T>> findBy(const X &predicate) const {
        std::vector<std::shared_ptr<T>> found;
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> obj = get(i);
            if (obj != nullptr && predicate(obj)) {
                found.push_back(obj);
            }
        }
        return found;
    }
    std::vector<std::shared_ptr<T>> findAll() const {
        std::function<bool(std::shared_ptr<T>)> f= [](const std::shared_ptr<T> &ptr)->bool{return 1;};
        return findBy(f);
    }
    template<class I> std::shared_ptr<T> findById(I id) const {
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> object = get(i);
            if (object != nullptr && object->getId() == id) {
                return object;
            }
        }
        return nullptr;
    }
};




#endif //CARRENTAL_REPOSITORY_H

//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_REPOSITORY_H
#define HOTELPROJECT_REPOSITORY_H
#include <memory>
#include <string>
#include <vector>
#include <functional>

template<class T,class P> class Repository
{
protected:
    std::vector<std::shared_ptr<T>> objects;
public:
    Repository(){};
    virtual ~Repository(){};

    virtual std::shared_ptr<T> get(unsigned int i) const
    {
       if(i>=size() || i<0) throw P("ERROR Invalid index");

        return objects[i];
    };

    virtual const unsigned int size() const
    {
        return objects.size();
    };

    void remove(std::shared_ptr<T> ptr)
    {
        if(ptr == nullptr) throw P("ERROR Null pointer");

        objects.erase(std::remove(objects.begin(),objects.end(),ptr),objects.end());
    };


    virtual void add(std::shared_ptr<T> ptr)
    {
        if(ptr==nullptr) throw P("ERROR Null pointer");

        objects.push_back(ptr);
    };
    virtual std::vector<std::shared_ptr<T>> findBy(std::function<bool(std::shared_ptr<T>)> predicate) const{
        std::vector<std::shared_ptr<T>> found;
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> exist = get(i);
            if (exist != nullptr && predicate(exist)) {
                found.push_back(exist);
            }
        }
        return found;
    };
    virtual std::vector<std::shared_ptr<T>> findAll() const{
        return findBy([](std::shared_ptr<T>)->bool{return true;});
    };

    template<class I> std::shared_ptr<T> findById(I id) const{
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> object = get(i);
            if (object != nullptr && object->getId() == id) {
                return object;
            }
        }
        throw P("ERROR No Object");
    };

};



#endif //HOTELPROJECT_REPOSITORY_H

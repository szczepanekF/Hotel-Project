//
// Created by student on 29.05.2022.
//

#ifndef HOTELPROJECT_REPOSITORY_H
#define HOTELPROJECT_REPOSITORY_H
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <fstream>

template<class T,class P> class Repository
{
protected:
    std::vector<std::shared_ptr<T>> objects;
public:
    Repository()= default;;
    virtual ~Repository()= default;;

    virtual std::shared_ptr<T> get(unsigned int i) const ///zwraca i-ty element repozytorium, rzuca wyjątek gdy i<0 lub i> większe od rozmiaru repozytorium
    {
       if(i>=size() || i<0) throw P("ERROR Invalid index");

        return objects[i];
    };

    virtual unsigned int size() const
    {
        return objects.size();
    };

    void remove(std::shared_ptr<T> ptr) ///usuwa podany element z repozytorium, rzuca wyjątek gdy podany wskaźnik jest równy nullptr
    {
        if(ptr == nullptr) throw P("ERROR Null pointer");

        objects.erase(std::remove(objects.begin(),objects.end(),ptr),objects.end());
    };


    virtual void add(std::shared_ptr<T> ptr) ///dodaje element do repozytorium, rzuca wyjątek gdy podany wskaźnik jest równy nullptr
    {
        if(ptr==nullptr) throw P("ERROR Null pointer");

        objects.push_back(ptr);
    };
    virtual std::vector<std::shared_ptr<T>> findBy(std::function<bool(std::shared_ptr<T>)> predicate) const{ ///zwraca wszystkie lementy repozytorium spełniające dany predykat, rzuca wyjątek gdy żaden element nie pasuje do predykatu
        std::vector<std::shared_ptr<T>> found;
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> exist = get(i);
            if (exist != nullptr && predicate(exist)) {
                found.push_back(exist);
            }
        }
        if(found.empty()){
            throw P("ERROR No Objects");
        }
        return found;
    };
    virtual std::vector<std::shared_ptr<T>> findAll() const{ ///zwraca wszystkie elementy repozytorium, rzuca wyjątek gdy repozytorium jest puste
        return findBy([](std::shared_ptr<T>)->bool{return true;});
    };

    template<class I> std::shared_ptr<T> findById(I id) const{ ///zwraca element repozytorium o podanym unikatowym atrybucie, rzuca wyjątek gdy żaden element repozytorium nie pasuje do przekazanego wzorca
        for (unsigned int i = 0; i < size(); i++) {
            std::shared_ptr<T> object = get(i);
            if (object != nullptr && object->getId() == id) {
                return object;
            }
        }
        throw P("ERROR No Object");
    };
    virtual void saveInformations(const std::string &filePath, const std::string &title){ ///zapisuje informacje o wszystkich elementach repozytorium do pliku o podanej ścieżce
        std::ofstream file(filePath);
        file<<title<<" \n";
        for(int i=0;i<size();i++)
        {
            file<<get(i)->getInfo()<<'\n';
        }
        file.close();
    }

};



#endif //HOTELPROJECT_REPOSITORY_H

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//forward declarations
class Component;
class Entity;

inline std::size_t getComponentTypeID()
{
    static std::size_t lastID = 0; //increment ID and return it
    return lastID++;
}

template <typename T> inline std::size_t getComponentTypeID() noexcept 
{
    static std::size_t typeID = getComponentTypeID(); //this is called once on the first initialisation of an object, subsequent calls will skip this line as its static
    return typeID;
}

constexpr std::size_t maxComponents = 32; //compile time constant for array and bitset size

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

//abstract component class
class Component
{
    public:
        Entity* entity; //which entity this component belongs to
        
        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}
        virtual ~Component() {}
};


class Entity
{
    private:
        bool active = true;
        std::vector<std::unique_ptr<Component>> components; //components on this entity, automatically cleaned up on destroy

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
    public:
        void update()
        {
            for (auto &c : components) c->update(); //call update on all components 
        }
        void draw() 
        {
            for (auto &c : components) c->draw();
        }
        bool isActive() {return active;}
        void destroy() {active = false;}

        template <typename T> bool hasComponent() const{
            return componentBitSet[getComponentTypeID<T>()]; //searches T unique id, checks that bit in the bitset to see if active or not
        }
        template <typename T, typename... TArgs> //variadic template
        T& addComponent(TArgs&&... mArgs) //forward reference arguments, preserving lvalue/rvalue
        {
            T* c(new T(std::forward<TArgs>(mArgs)...)); //allocates T object on the heap, passes each arg thru
            c->entity = this; //set parent entity
            std::unique_ptr<Component>  uPtr{ c }; //create unique ptr to c
            components.emplace_back(std::move(uPtr)); //constructs new slot directly in vector

            componentArray[getComponentTypeID<T>()] = c; //stores raw ptr at the index
            componentBitSet[getComponentTypeID<T>()] = true; //flips bit on

            c->init(); //calls virtual init function
            return *c; //dereferences and returns c by reference
        }

        template<typename T> T& GetComponent() const
        {
            auto ptr(componentArray[getComponentTypeID<T>()]); 
            return *static_cast<T*>(ptr); //return a reference to the component
        }

};

class EntityManager
{
    private:
        std::vector<std::unique_ptr<Entity>> entities; //stores all entities
    public:
        void update() 
        {
            for (auto &e : entities) e->update();
        }
        void draw() 
        {
            for (auto &e : entities) e->draw();
        }
        void refresh()
        {
            //moves values to be removed to end of vector and deletes them
            entities.erase(
                std::remove_if(std::begin(entities), std::end(entities),
                    [](const std::unique_ptr<Entity> &mEntity) {
                        return !mEntity->isActive();
                    }),
                std::end(entities) 
            );
        }

        Entity& addEntity()
        {
            Entity* e = new Entity(); //creates new entity ptr
            std::unique_ptr<Entity> uPtr{e}; //creates unique ptr wrapped around e
            entities.emplace_back(std::move(uPtr)); //constructs in vector
            return *e;
        }
};

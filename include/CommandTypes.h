#ifndef COMMANDTYPES_H
#define COMMANDTYPES_H

#include "Entity.h"
#include <list>
#include <string>
#include <iostream>

//--- FUNCIONES LIBRES ---
void moveCommand(Entity& entity, const std::list<std::string>& args);
void renameCommand(Entity& entity, const std::list<std::string>& args);
void levelUpCommand(Entity& entity, const std::list<std::string>& args);

//--- FUNCTORES ---

//Functor para curación
class HealFunctor {
private:
    Entity& entity;
    int useCount = 0;
public:
    explicit HealFunctor(Entity& e) : entity(e) {}
    void operator()(const std::list<std::string>& args);
};

//functor para escudo(demostración de estado)
class ShieldFunctor {
private:
    Entity& entity;
public:
    explicit ShieldFunctor(Entity& e) : entity(e) {}
    void operator()(const std::list<std::string>& args);
};

//functor para experiencia
class ExpFunctor {
private:
    Entity& entity;
public:
    explicit ExpFunctor(Entity& e) : entity(e) {}
    void operator()(const std::list<std::string>& args);
};

#endif

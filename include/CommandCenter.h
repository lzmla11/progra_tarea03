#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "Entity.h"
#include <functional>
#include <map>
#include <list>
#include <string>
#include <utility>

//definición obligatoria del tipo Command 
using Command = std::function<void(const std::list<std::string>&)>;

class CommandCenter {
private:
    Entity& entity; //instancia compartida de Entity
    std::map<std::string, Command> commands; 
    std::list<std::string> executionHistory; 
    
    //diccionario para Macros: nombre -> lsta de (NombreComando, Argumentos) 
    std::map<std::string, std::list<std::pair<std::string, std::list<std::string>>>> macros;

public:
    explicit CommandCenter(Entity& e);

    //metodos principales del motor
    void registerCommand(const std::string& name, Command cmd); 
    void execute(const std::string& name, const std::list<std::string>& args); 
    void deleteCommand(const std::string& name); 

    //gestión de Macros 
    void registerMacro(const std::string& name, const std::list<std::pair<std::string, std::list<std::string>>>& steps);
    void executeMacro(const std::string& name);

    void printHistory() const;
};

#endif

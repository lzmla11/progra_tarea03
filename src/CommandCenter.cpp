#include "CommandCenter.h"
#include <iostream>

CommandCenter::CommandCenter(Entity& e) : entity(e) {}

void CommandCenter::registerCommand(const std::string& name, Command cmd) {
    //intentamos insertar. Si el nombre ya existe, lanza error
    if (commands.find(name) == commands.end()) {
        commands[name] = cmd;
    } else {
        throw std::invalid_argument("Error: El comando '" + name + "' ya esta registrado.");
    }
}

void CommandCenter::execute(const std::string& name, const std::list<std::string>& args) {
    //requisito:usar iterador explícito para std::map 
    std::map<std::string, Command>::iterator it = commands.find(name);

    if (it != commands.end()) {
        //1.registrar estado antes del impacto 
        std::string before = entity.toString();
        
        //2.ejecutar el comando (el objeto callable)
        it->second(args);
        
        //3.registrar estado después del impacto
        std::string after = entity.toString();
        
        //4.guardar en el historial 
        std::string record = "Comando: " + name + " | Antes: " + before + " | Despues: " + after;
        executionHistory.push_back(record);
    } else {
        throw std::invalid_argument("Error: Comando '" + name + "' no encontrado.");
    }
}

void CommandCenter::deleteCommand(const std::string& name) {
    //verificamos existencia antes de eliminar 
    std::map<std::string, Command>::iterator it = commands.find(name);
    if (it != commands.end()) {
        commands.erase(it);
    } else {
        throw std::invalid_argument("Error: No se puede eliminar. Comando '" + name + "' no existe.");
    }
}

void CommandCenter::registerMacro(const std::string& name, const std::list<std::pair<std::string, std::list<std::string>>>& steps) {
    if (macros.find(name) == macros.end()) {
        macros[name] = steps;
    } else {
        throw std::invalid_argument("Error: El macro '" + name + "' ya existe.");
    }
}

void CommandCenter::executeMacro(const std::string& name) {
    auto m_it = macros.find(name);
    if (m_it == macros.end()) {
        throw std::invalid_argument("Error: Macro '" + name + "' no encontrado.");
    }

    //requisito: recorrer pasos con iteradores explícitos 
    std::list<std::pair<std::string, std::list<std::string>>>& steps = m_it->second;
    std::list<std::pair<std::string, std::list<std::string>>>::iterator it;

    for (it = steps.begin(); it != steps.end(); ++it) {
        //it->first es el nombre del comando, it->second son los argumentos
        //toda ejecución debe ser a través de execute()
        try {
            this->execute(it->first, it->second);
        } catch (const std::exception& e) {
            //si un comando falla, la ejecución del macro se detiene 
            std::cerr << "Macro abortado: " << e.what() << std::endl;
            return;
        }
    }
}

void CommandCenter::printHistory() const {
    std::cout << "--- Historial de Ejecucion ---" << std::endl;
    //requisito: Usar iterador explícito para std::list 
    //al ser un método const, usamos const_iterator
    std::list<std::string>::const_iterator it;
    for (it = executionHistory.begin(); it != executionHistory.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

#include "Entity.h"
#include "CommandCenter.h"
#include "CommandTypes.h"
#include <iostream>

int main() {
    //inicialización
    Entity hero("Aragorn", 100.0, 0.0, 0.0, 1);
    CommandCenter center(hero);

    //registro de 3 Funciones Libres
    center.registerCommand("move", [&](const std::list<std::string>& args) { moveCommand(hero, args); });
    center.registerCommand("rename", [&](const std::list<std::string>& args) { renameCommand(hero, args); });
    center.registerCommand("levelUp", [&](const std::list<std::string>& args) { levelUpCommand(hero, args); });

    //registro de 3 Functores
    center.registerCommand("heal", HealFunctor(hero));
    center.registerCommand("shield", ShieldFunctor(hero));
    center.registerCommand("addExp", ExpFunctor(hero));

    //registro de 3 Lambdas
    center.registerCommand("damage", [&hero](const std::list<std::string>& args) {
        if (args.empty()) throw std::invalid_argument("Damage requiere valor");
        hero.setHealth(hero.getHealth() - std::stod(args.front()));
    });
    center.registerCommand("status", [&hero](const std::list<std::string>& args) {
        std::cout << "ESTADO: " << hero.toString() << std::endl;
    });
    center.registerCommand("resetPos", [&hero](const std::list<std::string>& args) {
        hero.setPosition(0, 0);
    });

    //Registro de 3 Macros (Requisito PDF)
    center.registerMacro("full_buff", {
        {"heal", {"50"}},
        {"shield", {}},
        {"levelUp", {}}
    });

    center.registerMacro("panic_button", {
        {"resetPos", {}},
        {"heal", {"100"}},
        {"status", {}}
    });

    center.registerMacro("evolve", {
        {"rename", {"Super Hero"}},
        {"addExp", {"1000"}},
        {"status", {}}
    });

    //demostración de Ejecución
    try {
        std::cout << "--- Ejecutando Macros ---" << std::endl;
        center.executeMacro("full_buff");
        center.executeMacro("evolve");

        std::cout << "\n--- Demo de Robustez y Errores ---" << std::endl;
        
        //ejecutar comando válido
        center.execute("move", {"10", "10"});

        //intento de comando inexistente
        std::cout << "Intentando comando 'fly'..." << std::endl;
        try { center.execute("fly", {}); } 
        catch (const std::exception& e) { std::cout << "Capturado: " << e.what() << std::endl; }

        //demo de deleteCommand (Requisito explícito)
        std::cout << "\nEliminando comando 'status' dinamicamente..." << std::endl;
        center.deleteCommand("status");
        
        try { center.execute("status", {}); }
        catch (const std::exception& e) { std::cout << "Capturado tras eliminar: " << e.what() << std::endl; }

    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
    }

    std::cout << "\n";
    center.printHistory();

    return 0;
}

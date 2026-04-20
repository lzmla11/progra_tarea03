#include "CommandTypes.h"
#include <stdexcept>

//---Implementación de Funciones Libres---

void moveCommand(Entity& entity, const std::list<std::string>& args) {
    if (args.size() < 2) throw std::invalid_argument("Move requiere 2 argumentos (x, y)");
    auto it = args.begin();
    double dx = std::stod(*it++);
    double dy = std::stod(*it);
    double cx, cy;
    entity.getPosition(cx, cy);
    entity.setPosition(cx + dx, cy + dy);
}

void renameCommand(Entity& entity, const std::list<std::string>& args) {
    if (args.empty()) throw std::invalid_argument("Rename requiere el nuevo nombre");
    entity.setName(args.front());
}

void levelUpCommand(Entity& entity, const std::list<std::string>& args) {
    entity.setLevel(entity.getLevel() + 1);
    std::cout << "[Log] Nivel aumentado a: " << entity.getLevel() << std::endl;
}

//---Implementación de Functores---

void HealFunctor::operator()(const std::list<std::string>& args) {
    if (args.empty()) throw std::invalid_argument("Heal requiere cantidad");
    entity.setHealth(entity.getHealth() + std::stod(args.front()));
    useCount++;
}

void ShieldFunctor::operator()(const std::list<std::string>& args) {
    std::cout << "[Shield] Escudo activado para " << entity.getName() << std::endl;
}

void ExpFunctor::operator()(const std::list<std::string>& args) {
    if (args.empty()) throw std::invalid_argument("Exp requiere cantidad");
    entity.setLevel(entity.getLevel() + std::stoi(args.front()));
}

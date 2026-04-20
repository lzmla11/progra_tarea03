#include "Entity.h"
#include <sstream>

Entity::Entity(std::string n, double h, double posX, double posY, unsigned int lvl) 
    : name(n), health(h), x(posX), y(posY), level(lvl) {}

void Entity::setHealth(double h) { health = h; }
double Entity::getHealth() const { return health; }

void Entity::setPosition(double posX, double posY) { x = posX; y = posY; }
void Entity::getPosition(double& posX, double& posY) const { posX = x; posY = y; }

void Entity::setName(const std::string& n) { name = n; }
std::string Entity::getName() const { return name; }

void Entity::setLevel(unsigned int lvl) { level = lvl; }
unsigned int Entity::getLevel() const { return level; }

std::string Entity::toString() const {
    std::ostringstream oss;
    oss << "[Entity: " << name << " | HP: " << health << " | Pos: (" << x << "," << y << ") | Lvl: " << level << "]";
    return oss.str();
}

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <vector>

class Entity {
private:
    std::string name;   
    double health;     
    double x, y;      
    unsigned int level;

public:
    Entity(std::string n, double h, double posX, double posY, unsigned int lvl);

    //metodos públicos para modificar/consultar el estado 
    void setHealth(double h);
    double getHealth() const;
    
    void setPosition(double posX, double posY);
    void getPosition(double& posX, double& posY) const;

    void setName(const std::string& n);
    std::string getName() const;

    void setLevel(unsigned int lvl);
    unsigned int getLevel() const;

    //para el historial:representación del estado antes y despues 
    std::string toString() const;
};

#endif

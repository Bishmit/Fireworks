#ifndef FIREWORK_HPP
#define FIREWORK_HPP
#define M_PI 3.14159265358979323846

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>

namespace Regmi {

    // Particle struct representing individual particles in the scatter effect
    struct Particle {
        sf::CircleShape shape;
        sf::Vector2f velocity;
        float alpha;

        Particle(sf::Vector2f position, sf::Vector2f velocity);
        void update(float dt);
        bool isAlive() const;
    };

    // Firework class handling the main particle movement and scattering
    class Firework {
    public:
        Firework(sf::Vector2f position, sf::Vector2f velocity);

        void reset();
        void update(float dt, std::vector<Particle>& particles);
        void draw(sf::RenderWindow& window) const;

    private:
        sf::CircleShape shape;
        sf::Vector2f startPos;
        sf::Vector2f velocity;
        bool hasScattered;
        float scatterTimer;

        void scatter(std::vector<Particle>& particles);
        void scatter2(std::vector<Particle>& particles);
        void doScatter(std::vector<Particle>& particles);
    };

} // namespace Regmi

#endif // FIREWORK_HPP

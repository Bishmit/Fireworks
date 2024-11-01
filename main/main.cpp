#include <SFML/Graphics.hpp>
#include "Firework.h"
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "FireWorks");
    window.setFramerateLimit(60);

    std::vector<Regmi::Firework> fireworks;
    fireworks.emplace_back(sf::Vector2f(100, 600), sf::Vector2f(70, -200));   // Left particle, steep angle
    fireworks.emplace_back(sf::Vector2f(200, 600), sf::Vector2f(60, -170));   // Left-middle particle, moderate angle
    fireworks.emplace_back(sf::Vector2f(300, 600), sf::Vector2f(50, -150));   // Middle-left particle, slight upward
    fireworks.emplace_back(sf::Vector2f(400, 600), sf::Vector2f(80, -190));   // Middle particle, sharp upward angle
    fireworks.emplace_back(sf::Vector2f(500, 600), sf::Vector2f(40, -180));   // Middle-right particle, moderate angle
    fireworks.emplace_back(sf::Vector2f(600, 600), sf::Vector2f(-30, -160));  // Right-middle particle, small leftward angle
    fireworks.emplace_back(sf::Vector2f(700, 600), sf::Vector2f(-70, -210));  // Right particle, steep angle
    fireworks.emplace_back(sf::Vector2f(250, 600), sf::Vector2f(100, -160));  // Left-center particle, fast upward
    fireworks.emplace_back(sf::Vector2f(450, 600), sf::Vector2f(-50, -180));  // Right-center particle, angled leftward
    fireworks.emplace_back(sf::Vector2f(350, 600), sf::Vector2f(90, -200));   // Center particle, quick upward
    fireworks.emplace_back(sf::Vector2f(550, 600), sf::Vector2f(-90, -190));  // Far-right particle, wide leftward angle

    std::vector<Regmi::Particle> particles;
    sf::Clock clock;
    sf::Texture bgtex;
    sf::Sprite bgsprite;
    if (!bgtex.loadFromFile("../Assets/Images/night.jpg")) {
        std::cout << "background not loaded" << "\n";
    }
    bgsprite.setTexture(bgtex);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        // Update fireworks and trigger scattering
        for (auto& firework : fireworks) {
            firework.update(dt, particles);
        }

        // Update particles
        for (auto& particle : particles) {
            particle.update(dt);
        }

        // Remove faded particles
        particles.erase(std::remove_if(particles.begin(), particles.end(),
            [](const Regmi::Particle& p) { return !p.isAlive(); }),
            particles.end());

        window.clear();
        window.draw(bgsprite); 
        for (const auto& firework : fireworks) {
            firework.draw(window);
        }
        for (const auto& particle : particles) {
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}

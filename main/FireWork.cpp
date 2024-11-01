#include "Firework.h"
#include <cmath>

namespace Regmi {

    // Particle constructor
    Particle::Particle(sf::Vector2f position, sf::Vector2f velocity)
        : shape(1.75f), velocity(sf::Vector2f(2 * velocity.x, 2 * velocity.y)), alpha(255.0f) {
        shape.setPosition(position);
        shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    }

    // Update the particle position and fade out over time
    void Particle::update(float dt) {
        shape.move(velocity * dt);
        alpha -= 45 * 5 * dt;
        sf::Color rgb;
        int colorIndex = (std::rand() % 3); // Change to % 3 for three possible bright colors
        switch (colorIndex) {
        case 0:
            rgb = sf::Color(255, 0, 0); // Bright Red
            break;
        case 1:
            rgb = sf::Color(0, 255, 0); // Bright Green
            break;
        case 2:
            rgb = sf::Color(0, 0, 255); // Bright Blue
            break;
        }

        rgb.a = static_cast<sf::Uint8>(alpha); // Set the alpha value
        shape.setFillColor(rgb);

    }

    // Check if particle is still visible
    bool Particle::isAlive() const {
        return alpha > 0;
    }

    // Firework constructor
    Firework::Firework(sf::Vector2f position, sf::Vector2f velocity)
        : shape(0.75f), startPos(position), velocity(velocity), hasScattered(false), scatterTimer(0.0f) {
      
        shape.setPosition(position);
        shape.setFillColor(sf::Color(255, 165, 0));
    }

    // Reset the firework to its starting position and reset properties
    void Firework::reset() {
        shape.setPosition(startPos);
        hasScattered = false;
        scatterTimer = 0.0f;
    }

    void Firework::doScatter(std::vector<Particle>& particles)
    {
        int selection = std::rand() % 2;
        switch (selection)
        {
        case 0:
            scatter(particles);
            break;
        case 1:
            scatter2(particles);
            break; 
        }
        hasScattered = true; 

    }

    // Update the firework position and handle scattering
    void Firework::update(float dt, std::vector<Particle>& particles) {
        scatterTimer += dt;
        if (!hasScattered) {
            shape.move(velocity * dt);
            if (scatterTimer >= 2.0f) {  // Scatter every 2 seconds
                doScatter(particles);
                reset();
            }
        }
    }

    // Draw the firework on the window
    void Firework::draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    // Scatter particles from the firework's current position
    void Firework::scatter(std::vector<Particle>& particles) {
        sf::Vector2f position = shape.getPosition();
        for (int i = 0; i < 100; ++i) {
            float angle = (i / 10.0f) * 2 * M_PI;
            sf::Vector2f velocity(std::cos(angle) * 50, std::sin(angle) * 50);
            particles.emplace_back(position, velocity);
        }
        hasScattered = true;
    }

    void Firework::scatter2(std::vector<Particle>& particles) {
        // Angles for 8 directions
        int speed = 70; 
        sf::Vector2f center = shape.getPosition(); 
        const float angles[8] = {
            0.0f,             // North
            M_PI / 4.0f,     // North-East
            M_PI / 2.0f,     // East
            3 * M_PI / 4.0f, // South-East
            M_PI,            // South
            5 * M_PI / 4.0f, // South-West
            3 * M_PI / 2.0f, // West
            7 * M_PI / 4.0f  // North-West
        };

        // Create particles in each direction
        for (int i = 0; i < 8; ++i) {
            sf::Vector2f velocity(std::cos(angles[i]) * speed, std::sin(angles[i]) * speed);
            particles.emplace_back(center, velocity);
        }
    }

} // namespace Regmi

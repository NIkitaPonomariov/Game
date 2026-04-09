#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // squere
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f);

    // world
    sf::RectangleShape world(sf::Vector2f(2000.f, 2000.f));
    world.setFillColor(sf::Color(50, 50, 50)); 
    world.setPosition(0, 0);

    float speed = 0.3f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float x = player.getPosition().x;
        float y = player.getPosition().y;

        // move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y>0)
            player.move(0, -speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y<2000)
            player.move(0, speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x > 0)
            player.move(-speed, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x<2000)
            player.move(speed, 0);

        view.setCenter(player.getPosition());
        window.setView(view);

        window.clear();

        window.draw(world);
        window.draw(player); // drawing squere

        window.display();
    }

    return 0;
}
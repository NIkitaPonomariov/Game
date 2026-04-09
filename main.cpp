#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // player
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f);

    //enemy
    sf::RectangleShape enemy(sf::Vector2f(50.f, 50.f));
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(100.f, 100.f);

    unsigned int w_size = 2000;
    // world
    sf::RectangleShape world(sf::Vector2f(w_size, w_size));
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y<w_size-50)
            player.move(0, speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x > 0)
            player.move(-speed, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x<w_size-50)
            player.move(speed, 0);

        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            window.close(); // death 
}

        view.setCenter(player.getPosition());
        window.setView(view);


        float enemyX = enemy.getPosition().x;
        float enemyY = enemy.getPosition().y;

        float playerX = player.getPosition().x;
        float playerY = player.getPosition().y;


        float dx = playerX - enemyX;
        float dy = playerY - enemyY;

        float enemySpeed = 0.2f;

        if (dx > 0) enemy.move(enemySpeed, 0);
        if (dx < 0) enemy.move(-enemySpeed, 0);

        if (dy > 0) enemy.move(0, enemySpeed);
        if (dy < 0) enemy.move(0, -enemySpeed);


        window.clear();

        window.draw(world);  // drawing world
        window.draw(enemy);  // draw enemy
        window.draw(player); // drawing squere

        window.display();
    }

    return 0;
}
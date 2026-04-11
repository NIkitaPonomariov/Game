#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // player
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f);

    // enemy
    sf::RectangleShape enemy(sf::Vector2f(50.f, 50.f));
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(100.f, 100.f);

    // bullets
    std::vector<sf::CircleShape> bullets;

    // world
    unsigned int w_size = 2000;
    sf::RectangleShape world(sf::Vector2f(w_size, w_size));
    world.setFillColor(sf::Color(30, 30, 30));
    world.setPosition(0, 0);

    float speed = 0.3f;

    // shoot cooldown
    sf::Clock shootClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float x = player.getPosition().x;
        float y = player.getPosition().y;

        // movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y > 0)
            player.move(0, -speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y < w_size - 50)
            player.move(0, speed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x > 0)
            player.move(-speed, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x < w_size - 50)
            player.move(speed, 0);

        // shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            shootClock.getElapsedTime().asMilliseconds() > 300) {

            sf::CircleShape bullet(5.f);
            bullet.setFillColor(sf::Color::Yellow);

            bullet.setPosition(
                player.getPosition().x + 25,
                player.getPosition().y + 25
            );

            bullets.push_back(bullet);

            shootClock.restart();
        }

        // bullets movement
        for (auto& bullet : bullets) {
            bullet.move(0, -0.7f);
        }

        // enemy movement (AI)
        float enemyX = enemy.getPosition().x;
        float enemyY = enemy.getPosition().y;

        float playerX = player.getPosition().x;
        float playerY = player.getPosition().y;

        float dx = playerX - enemyX;
        float dy = playerY - enemyY;

        float length = sqrt(dx * dx + dy * dy);

        if (length != 0) {
            dx /= length;
            dy /= length;
        }

        float enemySpeed = 0.2f;
        enemy.move(dx * enemySpeed, dy * enemySpeed);

        // collision: player vs enemy
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            window.close(); // death
        }

        // collision: bullet vs enemy
        for (auto& bullet : bullets) {
            if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                enemy.setPosition(-100, -100); // remove enemy
            }
        }

        // camera (with limits)
        float camX = player.getPosition().x;
        float camY = player.getPosition().y;

        if (camX < 400) camX = 400;
        if (camY < 300) camY = 300;

        if (camX > w_size - 400) camX = w_size - 400;
        if (camY > w_size - 300) camY = w_size - 300;

        view.setCenter(camX, camY);
        window.setView(view);

        // draw
        window.clear();

        window.draw(world);

        for (auto& bullet : bullets) {
            window.draw(bullet);
        }

        window.draw(enemy);
        window.draw(player);

        window.display();
    }

    return 0;
}
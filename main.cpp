#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

class Player;

class Enemy {
public:
    std::string name;
    int health;
    int attackPower;
    sf::RectangleShape shape;

    Enemy(const std::string& enemyName, int enemyHealth, int enemyAttackPower)
        : name(enemyName), health(enemyHealth), attackPower(enemyAttackPower) {
            shape.setSize(sf::Vector2f(50, 50));
            shape.setFillColor(sf::Color::Red);
        }

    void attack(Player& player);
};

class Player {
public:
    std::string name;
    int health;
    int attackPower;
    int level;
    sf::RectangleShape shape;

    Player(const std::string& playerName, int playerHealth, int playerAttackPower)
        : name(playerName), health(playerHealth), attackPower(playerAttackPower), level(1) {
            shape.setSize(sf::Vector2f(50, 50));
            shape.setFillColor(sf::Color::Green);
        }

    void attack(Enemy& enemy) {
        std::cout << name << " attacks " << enemy.name << " and deals " << attackPower << " damage." << std::endl;
        enemy.health -= attackPower;
    }

    void takeDamage(int damage) {
        health -= damage;
        std::cout << name << " takes " << damage << " damage." << std::endl;
    }

    void levelUp() {
        level++;
        attackPower += 5;
        std::cout << name << " leveled up! New level: " << level << std::endl;
    }

    bool isAlive() {
        return health > 0;
    }
};

void Enemy::attack(Player& player) {
    std::cout << name << " attacks " << player.name << " and deals " << attackPower << " damage." << std::endl;
    player.takeDamage(attackPower);
}

int main() {
    Player player("Player1", 100, 10);

    std::vector<Enemy> enemies;
    enemies.emplace_back("Enemy1", 50, 5);
    enemies.emplace_back("Enemy2", 70, 8);
    enemies.emplace_back("Enemy3", 60, 7);

    std::cout << "=== Game Start ===" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load font." << std::endl;
        return 1;
    }

    sf::Text text("", font, 24);
    text.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (auto& enemy : enemies) {
            enemy.shape.move(-1.f, 0.f); // Move enemies to the left

            window.draw(enemy.shape);

            if (player.shape.getGlobalBounds().intersects(enemy.shape.getGlobalBounds())) {
                player.takeDamage(enemy.attackPower);
            }
        }

        player.shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        window.draw(player.shape);
        window.display();
    }

    return 0;
}

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

    Enemy(const std::string& enemyName, int enemyHealth, int enemyAttackPower)
        : name(enemyName), health(enemyHealth), attackPower(enemyAttackPower) {}

    void attack(Player& player);
};

class Player {
public:
    std::string name;
    int health;
    int attackPower;
    int level;

    Player(const std::string& playerName, int playerHealth, int playerAttackPower)
        : name(playerName), health(playerHealth), attackPower(playerAttackPower), level(1) {}

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

        std::string gameInfo;

        for (auto& enemy : enemies) {
            gameInfo += "=== New Enemy: " + enemy.name + " ===\n";

            while (player.isAlive() && enemy.health > 0) {
                player.attack(enemy);
                if (enemy.health <= 0) {
                    gameInfo += "Player defeated " + enemy.name + "!\n";
                    player.levelUp();
                    break;
                }

                enemy.attack(player);
                if (player.health <= 0) {
                    gameInfo += enemy.name + " defeated the player!\n";
                    break;
                }
            }

            gameInfo += "\n";
        }

        gameInfo += "=== Game Over ===\n";

        text.setString(gameInfo);
        window.draw(text);
        window.display();
    }

    return 0;
}

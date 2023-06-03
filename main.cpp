#include <iostream>
#include <string>
#include <vector>

class Enemy {
public:
    std::string name;
    int health;
    int attackPower;

    Enemy(const std::string& enemyName, int enemyHealth, int enemyAttackPower) {
        name = enemyName;
        health = enemyHealth;
        attackPower = enemyAttackPower;
    }

    void attack(Player& player) {
        std::cout << name << " attacks " << player.name << " and deals " << attackPower << " damage." << std::endl;
        player.takeDamage(attackPower);
    }
};

class Player {
public:
    std::string name;
    int health;
    int attackPower;
    int level;

    Player(const std::string& playerName, int playerHealth, int playerAttackPower) {
        name = playerName;
        health = playerHealth;
        attackPower = playerAttackPower;
        level = 1;
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

int main() {
    Player player("Player1", 100, 10);

    std::vector<Enemy> enemies;
    enemies.push_back(Enemy("Enemy1", 50, 5));
    enemies.push_back(Enemy("Enemy2", 70, 8));
    enemies.push_back(Enemy("Enemy3", 60, 7));

    std::cout << "=== Game Start ===" << std::endl;

    for (const auto& enemy : enemies) {
        std::cout << "=== New Enemy: " << enemy.name << " ===" << std::endl;

        while (player.isAlive() && enemy.health > 0) {
            player.attack(enemy);
            if (enemy.health <= 0) {
                std::cout << "Player defeated " << enemy.name << "!" << std::endl;
                player.levelUp();
                break;
            }

            enemy.attack(player);
            if (player.health <= 0) {
                std::cout << enemy.name << " defeated the player!" << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    }

    std::cout << "=== Game Over ===" << std::endl;

    return 0;
}

#pragma once

#include "components/simple_scene.h"
#include "square.h"
#include "turret.h"
#include "star.h"
#include "enemy.h"
#include "object2D.h"
#include "transform2D.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void createStarIfTurretCanShoot(
            std::vector<Star*>& activeStarsLine,
            int& idOfStar,
            std::unordered_map<std::string, Mesh*> *meshes,
            Turret* turret,
            int turretCy,
            int nrEnemyBlueLane,
            int nrEnemyYellowLane,
            int nrEnemyPurpleLane,
            int nrEnemyOrangeLane
        );
        void updateStarsAndCheckCollisions(
            std::vector<Star*>& activeStarsLine,
            std::vector<Enemy*>& activeEnemiesLine,
            float deltaTimeSeconds,
            float starSpeed,
            float starAngularStep
        );
        template <typename T>
        void removeFromVector(std::vector<T*>& vector, T* item);
        void handleTurretCollision(std::vector<Turret*>& turretSpawned, Enemy* enemy, std::unordered_map<int, Square*>& squares);
        void spawnTurretIfPossible(
            Square* emptySquare,
            int& turretNumber,
            int nrOfStarsCollected,
            int turretCost,
            std::vector<Turret*>& turretSpawned,
            glm::vec3& cornerRomb,
            glm::vec3& offset,
            glm::vec3& turretColor,
            float rombSide
        );
        void decreaseEnemyCountAndMarkAsDead(Enemy* enemy, int* nrEnemyYellowLane, int* nrEnemyPurpleLane, int* nrEnemyOrangeLane, int* nrEnemyBlueLane);
        void updateAndRenderEnemy(Enemy* enemy, const glm::vec2& resolution, Square* square9, float deltaTimeSeconds, float enemySpeed, std::vector<Enemy*>& activeEnemiesLine);
        bool selectTurret(int mouseX, int mouseY, Square* emptySquare, std::vector<Turret*>& turretSpawned, int turretCost, int nrOfStarsCollected, bool& turretSelected);
        void moveSelectedTurret(int mouseX, int mouseY, Square* emptySquare, std::vector<Turret*>& turretSpawned, bool turretSelected, int resolutionY);
        void updateTurretProperties(std::vector<Turret*>& turretSpawned, Square** emptySquare, bool& turretSelected, float cx, float cy);
        void handleDeadTurret(Turret* turret, Square* emptySquare, std::unordered_map<std::string, Mesh*>& meshes,
            std::vector<Turret*>& turretSpawned, std::unordered_map<int, Square*> squares, float deltaTimeSeconds);

    protected:
        Square* square1;
        Square* square2;
        Square* square3;
        Square* square4;
        Square* square5;
        Square* square6;
        Square* square7;
        Square* square8;
        Square* square9;
        Square* emptySquare1;
        Square* emptySquare2;
        Square* emptySquare3;
        Square* emptySquare4;
        float translateX;
        float translateY;
        Turret* turret1;
        Turret* turret2;
        Turret* turret3;
        Turret* turret4;
        bool turret1Selected;
        bool turret2Selected;
        bool turret3Selected;
        bool turret4Selected;
        float mouseTurretX;
        float mouseTurretY;
        int numberOfLives;
        std::unordered_map<int, Square*> squares;
        std::unordered_map<int, Square*> hearts;
        std::vector <Turret*> turretSpawned1;
        std::vector <Turret*> turretSpawned2;
        std::vector <Turret*> turretSpawned3;
        std::vector <Turret*> turretSpawned4;
        std::vector <Enemy*> activeEnemiesTopLine;
        std::vector <Enemy*> activeEnemiesMidLine;
        std::vector <Enemy*> activeEnemiesBotLine;
        std::vector <Star*> activeStarsTopLine;
        std::vector <Star*> activeStarsMidLine;
        std::vector <Star*> activeStarsBotLine;
        std::vector <Star*> starsCollected;
        glm::vec3 yellow;
        glm::vec3 red;
        glm::vec3 blue;
        glm::vec3 colorSquare;
        glm::vec3 purple;
        glm::vec3 orange;
        glm::vec3 green;
        glm::vec3 grey;
        glm::vec3 colorRect;
        glm::vec3 cadetBlue;
        glm::vec3 pink;
        glm::vec3 silver;
        int idOfEnemy;
        int idOfStar;
        int enemySpeed;
        int starSpeed;
        int starAngularStep;
        int nrEnemyYellowTop;
        int nrEnemyYellowMid;
        int nrEnemyYellowBot;
        int nrEnemyPurpleTop;
        int nrEnemyPurpleMid;
        int nrEnemyPurpleBot;
        int nrEnemyOrangeTop;
        int nrEnemyOrangeMid;
        int nrEnemyOrangeBot;
        int nrEnemyBlueTop;
        int nrEnemyBlueMid;
        int nrEnemyBlueBot;
        int nrOfStarsCollected;
        Star* star1;
        Star* star2;
        Star* star3;
        Star* star4;
        Star* star5;
        Star* star6;
        Star* star7;
        Star* star8;
        float starSpawnTimer;
        std::vector <Star*> starsSpawned;
        glm::vec3 cornerRomb;
        float rombSide;
        int turretNumber;
        float squareSide;
        float enemySpawnTimer;                                     // avoid spawning enemies on top of each other
    };
}   // namespace m1

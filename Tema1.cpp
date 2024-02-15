#include "Tema1.h"
#include <random>
#include <chrono>

#define shootRatioGlobal 2.5
#define starSpawnerTimerGlobal 7
#define numberOfStarSpawned 3
#define turret1Cost 1
#define turret2Cost 2
#define turret3Cost 2
#define turret4Cost 3

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void m1::Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    translateX = 0;
    translateY = 0;

    turret1Selected = false;
    turret2Selected = false;
    turret3Selected = false;
    turret4Selected = false;

    mouseTurretX = 0;
    mouseTurretY = 0;

    numberOfLives = 3;
    idOfEnemy = 0;
    idOfStar = 0;

    enemySpeed = 50;
    starSpeed = 150;

    starAngularStep = 3;
    starSpawnTimer = 7;

    nrEnemyYellowTop = 0;
    nrEnemyYellowMid = 0;
    nrEnemyYellowBot = 0;
    nrEnemyPurpleTop = 0;
    nrEnemyPurpleMid = 0;
    nrEnemyPurpleBot = 0;
    nrEnemyOrangeTop = 0;
    nrEnemyOrangeMid = 0;
    nrEnemyOrangeBot = 0;
    nrEnemyBlueTop = 0;
    nrEnemyBlueBot = 0;
    nrEnemyBlueMid = 0;
    nrOfStarsCollected = 3;
    enemySpawnTimer = 1;

    glm::vec3 corner = glm::vec3(0, 0, 0);
    glm::vec3 cornerSquare = glm::vec3(150, 0, 0);
    glm::vec3 cornerEmptySquare = glm::vec3(50, resolution.y - 120, 0);
    squareSide = 100;
    float squarePosX = 0;
    float squarePosY = 0;
    float rectSide = 100;
    rombSide = 40;
    float cEmptySquareX = cornerEmptySquare.x + squareSide / 2;
    float cEmptySquareY = cornerEmptySquare.y + squareSide / 2;
    cornerRomb = glm::vec3(cEmptySquareX, cEmptySquareY, 0);

    green = glm::vec3(0, 1, 0);
    colorRect = glm::vec3(1, 0, 0);
    blue = glm::vec3(0, 0, 1);
    grey = glm::vec3(128, 128, 128);
    orange = glm::vec3(1, 0.5f, 0.0f);
    yellow = glm::vec3(1, 1, 0.2f);
    red = glm::vec3(1, 0, 0);
    purple = glm::vec3(0.5f, 0, 0.5f);
    cadetBlue = glm::vec3(0.372f, 0.619f, 0.627f);
    pink = glm::vec3(1.0f, 0.078f, 0.576f);
    silver = glm::vec3(0.752f, 0.752f, 0.752f);

    square1 = new Square("square1", &meshes, cornerSquare + glm::vec3(squarePosX, squarePosY, 0), green, squareSide, glm::mat3(1), true);
    square2 = new Square("square2", &meshes, cornerSquare + glm::vec3(squareSide + 50, squarePosY, 0), green, squareSide, glm::mat3(1), true);
    square3 = new Square("square3", &meshes, cornerSquare + glm::vec3(2 * squareSide + 100, squarePosY, 0), green, squareSide, glm::mat3(1), true);
    square4 = new Square("square4", &meshes, cornerSquare + glm::vec3(squarePosX, squareSide + 50, 0), green, squareSide, glm::mat3(1), true);
    square5 = new Square("square5", &meshes, cornerSquare + glm::vec3(squareSide + 50, squareSide + 50, 0), green, squareSide, glm::mat3(1), true);
    square6 = new Square("square6", &meshes, cornerSquare + glm::vec3(2 * squareSide + 100, squareSide + 50, 0), green, squareSide, glm::mat3(1), true);
    square7 = new Square("square7", &meshes, cornerSquare + glm::vec3(squarePosX, 2 * squareSide + 100, 0), green, squareSide, glm::mat3(1), true);
    square8 = new Square("square8", &meshes, cornerSquare + glm::vec3(squareSide + 50, 2 * squareSide + 100, 0), green, squareSide, glm::mat3(1), true);
    square9 = new Square("square9", &meshes, cornerSquare + glm::vec3(2 * squareSide + 100, 2 * squareSide + 100, 0), green, squareSide, glm::mat3(1), true);

    // Empty squares
    squares = {
    {1, square1},
    {2, square2},
    {3, square3},
    {4, square4},
    {5, square5},
    {6, square6},
    {7, square7},
    {8, square8},
    {9, square9}
    };

    emptySquare1 = new Square("emptySquare1", &meshes, cornerEmptySquare, grey, squareSide, glm::mat3(1), false);
    emptySquare2 = new Square("emptySquare2", &meshes, cornerEmptySquare + glm::vec3(squareSide + 75, 0, 0), grey, squareSide, glm::mat3(1), false);
    emptySquare3 = new Square("emptySquare3", &meshes, cornerEmptySquare + glm::vec3(2 * squareSide + 125, 0, 0), grey, squareSide, glm::mat3(1), false);
    emptySquare4 = new Square("emptySquare4", &meshes, cornerEmptySquare + glm::vec3(3 * squareSide + 200, 0, 0), grey, squareSide, glm::mat3(1), false);
    emptySquare1->isOcupied = true;
    emptySquare2->isOcupied = true;
    emptySquare3->isOcupied = true;
    emptySquare4->isOcupied = true;


    {
        vector<VertexFormat> vertices_rectangle
        {
            VertexFormat(corner, colorRect),
            VertexFormat(corner + glm::vec3(rectSide, 0, 0), colorRect),
            VertexFormat(corner + glm::vec3(rectSide, 4 * rectSide, 0), colorRect),
            VertexFormat(corner + glm::vec3(0, 4 * rectSide, 0), colorRect)
        };

        vector<unsigned int> indices_rectangle =
        {
            0, 1, 2,    // indices for first triangle
            0, 3, 2,    // indices for second triangle
        };

        // Actually create the mesh from the data
        meshes["rectangle"] = new Mesh("rectangle");
        meshes["rectangle"]->InitFromData(vertices_rectangle, indices_rectangle);
    }

    // 1st romb
    turret1 = new Turret("turret1", &meshes, cornerRomb, blue, rombSide, turret1Cost, glm::mat3(1));

    // 2nd romb
    turret2 = new Turret("turret2", &meshes, cornerRomb + glm::vec3(squareSide + 75, 0, 0), orange, rombSide, turret2Cost, glm::mat3(1));

    // 3rd romb
    turret3 = new Turret("turret3", &meshes, cornerRomb + glm::vec3(2 * squareSide + 125, 0, 0), yellow, rombSide, turret3Cost, glm::mat3(1));

    //4th romb
    turret4 = new Turret("turret4", &meshes, cornerRomb + glm::vec3(3 * squareSide + 200, 0, 0), purple, rombSide, turret4Cost, glm::mat3(1));

    turretSpawned1.push_back(turret1);
    turretSpawned2.push_back(turret2);
    turretSpawned3.push_back(turret3);
    turretSpawned4.push_back(turret4);

    turretNumber = 5;

    // Hearts
    {
        float heartSide = 75;
        glm::vec3 cornerHeart = cornerEmptySquare + glm::vec3(7 * squareSide, 20, 0);
        Square* heart1 = new Square("heart1", &meshes, cornerHeart, red, heartSide, glm::mat3(1), true);
        Square* heart2 = new Square("heart2", &meshes, cornerHeart + glm::vec3(heartSide + 100, 0, 0), red, heartSide, glm::mat3(1), true);
        Square* heart3 = new Square("heart3", &meshes, cornerHeart + glm::vec3(2 * heartSide + 200, 0, 0), red, heartSide, glm::mat3(1), true);
        
        hearts = {
	    {1, heart1},
	    {2, heart2},
	    {3, heart3}
	    };
    }

    // Stars for turrets
    star1 = new Star("star1EmptySquare1", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star2 = new Star("star1EmptySquare2", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star3 = new Star("star2EmptySquare2", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star4 = new Star("star1EmptySquare3", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star5 = new Star("star2EmptySquare3", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star6 = new Star("star1EmptySquare4", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star7 = new Star("star2EmptySquare4", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));
    star8 = new Star("star3EmptySquare4", &meshes, corner, grey, 0, 0, 5, 15.0f, 5.0f, glm::mat3(1));

    starsCollected.push_back(new Star("starCollectedDefault1", &meshes, glm::vec3(0, 0, 0), silver, 0, 0, 5, 15.f, 5.f, glm::mat3(1)));
    starsCollected.push_back(new Star("starCollectedDefault2", &meshes, glm::vec3(0, 0, 0), silver, 0, 0, 5, 15.f, 5.f, glm::mat3(1)));
    starsCollected.push_back(new Star("starCollectedDefault3", &meshes, glm::vec3(0, 0, 0), silver, 0, 0, 5, 15.f, 5.f, glm::mat3(1)));
}

void m1::Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void m1::Tema1::Update(float deltaTimeSeconds)
{
    if (numberOfLives != 0) {
        glm::vec2 resolution = window->GetResolution();
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square4"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square5"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square6"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square7"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square8"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["square9"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["emptySquare1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["emptySquare2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["emptySquare3"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["emptySquare4"], shaders["VertexColor"], glm::mat3(1));
        star1->modelMatrix = glm::mat3(1);
        star1->modelMatrix *= transform2D::Translate(63, resolution.y - 137);
        RenderMesh2D(meshes["star1EmptySquare1"], shaders["VertexColor"], star1->modelMatrix * transform2D::Rotate(0.31f));
        star2->modelMatrix = glm::mat3(1);
        star2->modelMatrix *= transform2D::Translate(63 + 177, resolution.y - 137);
        RenderMesh2D(meshes["star1EmptySquare2"], shaders["VertexColor"], star2->modelMatrix * transform2D::Rotate(0.31f));
        star3->modelMatrix = glm::mat3(1);
        star3->modelMatrix *= transform2D::Translate(63 + 177 + 35, resolution.y - 137);
        RenderMesh2D(meshes["star2EmptySquare2"], shaders["VertexColor"], star3->modelMatrix * transform2D::Rotate(0.31f));
        star4->modelMatrix = glm::mat3(1);
        star4->modelMatrix *= transform2D::Translate(63 + 327, resolution.y - 137);
        RenderMesh2D(meshes["star1EmptySquare3"], shaders["VertexColor"], star4->modelMatrix * transform2D::Rotate(0.31f));
        star5->modelMatrix = glm::mat3(1);
        star5->modelMatrix *= transform2D::Translate(63 + 327 + 35, resolution.y - 137);
        RenderMesh2D(meshes["star2EmptySquare3"], shaders["VertexColor"], star5->modelMatrix * transform2D::Rotate(0.31f));
        star6->modelMatrix = glm::mat3(1);
        star6->modelMatrix *= transform2D::Translate(63 + 500, resolution.y - 137);
        RenderMesh2D(meshes["star1EmptySquare4"], shaders["VertexColor"], star6->modelMatrix * transform2D::Rotate(0.31f));
        star7->modelMatrix = glm::mat3(1);
        star7->modelMatrix *= transform2D::Translate(63 + 500 + 35, resolution.y - 137);
        RenderMesh2D(meshes["star2EmptySquare4"], shaders["VertexColor"], star7->modelMatrix * transform2D::Rotate(0.31f));
        star8->modelMatrix = glm::mat3(1);
        star8->modelMatrix *= transform2D::Translate(63 + 500 + 70, resolution.y - 137);
        RenderMesh2D(meshes["star3EmptySquare4"], shaders["VertexColor"], star8->modelMatrix * transform2D::Rotate(0.31f));

        for (auto& heart : hearts) {
            RenderMesh2D(meshes[heart.second->name], shaders["VertexColor"], glm::mat3(1));
        }

        enemySpawnTimer -= deltaTimeSeconds;
        if (enemySpawnTimer <= 0) {
            int randomNum = rand() % 3;

            if (randomNum == 0) {
                int random = rand() % 4;
                switch (random) {
                case 0:
                    activeEnemiesTopLine.push_back(new Enemy("enemyTopLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, yellow, (float)resolution.x - 100, square9->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyYellowTop++;
                    break;
                case 1:
                    activeEnemiesTopLine.push_back(new Enemy("enemyTopLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, purple, (float)resolution.x - 100, square9->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyPurpleTop++;
                    break;
                case 2:
                    activeEnemiesTopLine.push_back(new Enemy("enemyTopLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, orange, (float)resolution.x - 100, square9->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyOrangeTop++;
                    break;
                case 3:
                    activeEnemiesTopLine.push_back(new Enemy("enemyTopLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, blue, (float)resolution.x - 100, square9->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyBlueTop++;
                    break;
                default:
                    break;
                }
            }

            if (randomNum == 1) {
                int random = rand() % 4;
                switch (random) {
                case 0:
                    activeEnemiesMidLine.push_back(new Enemy("enemyMidLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, yellow, (float)resolution.x - 100, square6->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyYellowMid++;
                    break;
                case 1:
                    activeEnemiesMidLine.push_back(new Enemy("enemyMidLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, purple, (float)resolution.x - 100, square6->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyPurpleMid++;
                    break;
                case 2:
                    activeEnemiesMidLine.push_back(new Enemy("enemyMidLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, orange, (float)resolution.x - 100, square6->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyOrangeMid++;
                    break;
                case 3:
                    activeEnemiesMidLine.push_back(new Enemy("enemyMidLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, blue, (float)resolution.x - 100, square6->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyBlueMid++;
                    break;
                default:
                    break;
                }
            }

            if (randomNum == 2) {
                int random = rand() % 4;
                switch (random) {
                case 0:
                    activeEnemiesBotLine.push_back(new Enemy("enemyBotLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, yellow, (float)resolution.x - 100, square3->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyYellowBot++;
                    break;
                case 1:
                    activeEnemiesBotLine.push_back(new Enemy("enemyBotLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, purple, (float)resolution.x - 100, square3->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyPurpleBot++;
                    break;
                case 2:
                    activeEnemiesBotLine.push_back(new Enemy("enemyBotLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, orange, (float)resolution.x - 100, square3->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyOrangeBot++;
                    break;
                case 3:
                    activeEnemiesBotLine.push_back(new Enemy("enemyBotLine" + std::to_string(idOfEnemy), idOfEnemy, &meshes, glm::vec3(0, 0, 0), cadetBlue, blue, (float)resolution.x - 100, square3->cy, 3, 30.0f, 30.0f, glm::mat3(1)));
                    idOfEnemy++;
                    nrEnemyBlueBot++;
                    break;
                default:
                    break;
                }
            }

            int randomTimer = rand() % 3;
            enemySpawnTimer = randomTimer + 2;
        }

        for (auto& enemy : activeEnemiesTopLine) {
            if (enemy->health == 0 && !enemy->isDead) {
                decreaseEnemyCountAndMarkAsDead(enemy, &nrEnemyYellowTop, &nrEnemyPurpleTop, &nrEnemyOrangeTop, &nrEnemyBlueTop);
            }
            else {
                handleTurretCollision(turretSpawned1, enemy, squares);

                handleTurretCollision(turretSpawned2, enemy, squares);

                handleTurretCollision(turretSpawned3, enemy, squares);

                handleTurretCollision(turretSpawned4, enemy, squares);

                if ((float)resolution.x + enemy->translateX > 120) {
                    updateAndRenderEnemy(enemy, resolution, square9, deltaTimeSeconds, enemySpeed, activeEnemiesTopLine);
                }
                else {
                    enemy->translateX = 0;
                    activeEnemiesTopLine.erase(activeEnemiesTopLine.begin());
                    if (enemy->color2 == yellow) {
                        nrEnemyYellowTop--;
                    }
                    else if (enemy->color2 == purple) {
                        nrEnemyPurpleTop--;
                    }
                    else if (enemy->color2 == orange) {
                        nrEnemyOrangeTop--;
                    }
                    else if (enemy->color2 == blue) {
                        nrEnemyBlueTop--;
                    }
                    hearts.erase(hearts.begin());
                    --numberOfLives;
                }
            }
        }

        for (auto& enemy : activeEnemiesMidLine) {
            if (enemy->health == 0 && !enemy->isDead) {
                decreaseEnemyCountAndMarkAsDead(enemy, &nrEnemyYellowMid, &nrEnemyPurpleMid, &nrEnemyOrangeMid, &nrEnemyBlueMid);
            }
            else {
                handleTurretCollision(turretSpawned1, enemy, squares);

                handleTurretCollision(turretSpawned2, enemy, squares);

                handleTurretCollision(turretSpawned3, enemy, squares);

                handleTurretCollision(turretSpawned4, enemy, squares);

                if ((float)resolution.x + enemy->translateX > 120) {
                    updateAndRenderEnemy(enemy, resolution, square6, deltaTimeSeconds, enemySpeed, activeEnemiesMidLine);
                }
                else {
                    enemy->translateX = 0;
                    activeEnemiesMidLine.erase(activeEnemiesMidLine.begin());
                    if (enemy->color2 == yellow) {
                        nrEnemyYellowMid--;
                    }
                    else if (enemy->color2 == purple) {
                        nrEnemyPurpleMid--;
                    }
                    else if (enemy->color2 == orange) {
                        nrEnemyOrangeMid--;
                    }
                    else if (enemy->color2 == blue) {
                        nrEnemyBlueMid--;
                    }
                    hearts.erase(hearts.begin());
                    --numberOfLives;
                }
            }
        }

        for (auto& enemy : activeEnemiesBotLine) {
            if (enemy->health == 0 && !enemy->isDead) {
                decreaseEnemyCountAndMarkAsDead(enemy, &nrEnemyYellowBot, &nrEnemyPurpleBot, &nrEnemyOrangeBot, &nrEnemyBlueBot);
            }
            else {
                handleTurretCollision(turretSpawned1, enemy, squares);

                handleTurretCollision(turretSpawned2, enemy, squares);

                handleTurretCollision(turretSpawned3, enemy, squares);

                handleTurretCollision(turretSpawned4, enemy, squares);

                if ((float)resolution.x + enemy->translateX > 120) {
                    updateAndRenderEnemy(enemy, resolution, square3, deltaTimeSeconds, enemySpeed, activeEnemiesBotLine);
                }
                else {
                    enemy->translateX = 0;
                    activeEnemiesBotLine.erase(activeEnemiesBotLine.begin());
                    if (enemy->color2 == yellow) {
                        nrEnemyYellowBot--;
                    }
                    else if (enemy->color2 == purple) {
                        nrEnemyPurpleBot--;
                    }
                    else if (enemy->color2 == orange) {
                        nrEnemyOrangeBot--;
                    }
                    else if (enemy->color2 == blue) {
                        nrEnemyBlueBot--;
                    }
                    hearts.erase(hearts.begin());
                    --numberOfLives;
                }
            }
        }

        for (auto& turret : turretSpawned1) {
            handleDeadTurret(turret, emptySquare1, meshes, turretSpawned1, squares, deltaTimeSeconds);

            if (turret->canShoot) {
                turret->shootRatio -= deltaTimeSeconds;
                if (turret->shootRatio <= 0) {
                    createStarIfTurretCanShoot(activeStarsBotLine, idOfStar, &meshes, turret, square3->cy, nrEnemyBlueBot, nrEnemyYellowBot,
                        nrEnemyPurpleBot, nrEnemyOrangeBot);
                    createStarIfTurretCanShoot(activeStarsMidLine, idOfStar, &meshes, turret, square6->cy, nrEnemyBlueMid, nrEnemyYellowMid,
                        nrEnemyPurpleMid, nrEnemyOrangeMid);
                    createStarIfTurretCanShoot(activeStarsTopLine, idOfStar, &meshes, turret, square9->cy, nrEnemyBlueTop, nrEnemyYellowTop,
                        nrEnemyPurpleTop, nrEnemyOrangeTop);
                }
            }
        }

        for (auto& turret : turretSpawned2) {
            handleDeadTurret(turret, emptySquare2, meshes, turretSpawned2, squares, deltaTimeSeconds);

            if (turret->canShoot) {
                turret->shootRatio -= deltaTimeSeconds;
                if (turret->shootRatio <= 0) {
                    createStarIfTurretCanShoot(activeStarsBotLine, idOfStar, &meshes, turret, square3->cy, nrEnemyBlueBot, nrEnemyYellowBot,
                        nrEnemyPurpleBot, nrEnemyOrangeBot);
                    createStarIfTurretCanShoot(activeStarsMidLine, idOfStar, &meshes, turret, square6->cy, nrEnemyBlueMid, nrEnemyYellowMid,
                        nrEnemyPurpleMid, nrEnemyOrangeMid);
                    createStarIfTurretCanShoot(activeStarsTopLine, idOfStar, &meshes, turret, square9->cy, nrEnemyBlueTop, nrEnemyYellowTop,
                        nrEnemyPurpleTop, nrEnemyOrangeTop);
                }
            }
        }

        for (auto& turret : turretSpawned3) {
            handleDeadTurret(turret, emptySquare3, meshes, turretSpawned3, squares, deltaTimeSeconds);

            if (turret->canShoot) {
                turret->shootRatio -= deltaTimeSeconds;
                if (turret->shootRatio <= 0) {
                    createStarIfTurretCanShoot(activeStarsBotLine, idOfStar, &meshes, turret, square3->cy, nrEnemyBlueBot, nrEnemyYellowBot,
                        nrEnemyPurpleBot, nrEnemyOrangeBot);
                    createStarIfTurretCanShoot(activeStarsMidLine, idOfStar, &meshes, turret, square6->cy, nrEnemyBlueMid, nrEnemyYellowMid,
                        nrEnemyPurpleMid, nrEnemyOrangeMid);
                    createStarIfTurretCanShoot(activeStarsTopLine, idOfStar, &meshes, turret, square9->cy, nrEnemyBlueTop, nrEnemyYellowTop,
                        nrEnemyPurpleTop, nrEnemyOrangeTop);
                }
            }
        }

        for (auto& turret : turretSpawned4) {
            handleDeadTurret(turret, emptySquare4, meshes, turretSpawned4, squares, deltaTimeSeconds);

            if (turret->canShoot) {
                turret->shootRatio -= deltaTimeSeconds;
                if (turret->shootRatio <= 0) {
                    createStarIfTurretCanShoot(activeStarsBotLine, idOfStar, &meshes, turret, square3->cy, nrEnemyBlueBot, nrEnemyYellowBot,
                        nrEnemyPurpleBot, nrEnemyOrangeBot);
                    createStarIfTurretCanShoot(activeStarsMidLine, idOfStar, &meshes, turret, square6->cy, nrEnemyBlueMid, nrEnemyYellowMid,
                        nrEnemyPurpleMid, nrEnemyOrangeMid);
                    createStarIfTurretCanShoot(activeStarsTopLine, idOfStar, &meshes, turret, square9->cy, nrEnemyBlueTop, nrEnemyYellowTop,
                        nrEnemyPurpleTop, nrEnemyOrangeTop);
                }
            }
        }

        updateStarsAndCheckCollisions(activeStarsTopLine, activeEnemiesTopLine, deltaTimeSeconds, starSpeed, starAngularStep);
        updateStarsAndCheckCollisions(activeStarsMidLine, activeEnemiesMidLine, deltaTimeSeconds, starSpeed, starAngularStep);
        updateStarsAndCheckCollisions(activeStarsBotLine, activeEnemiesBotLine, deltaTimeSeconds, starSpeed, starAngularStep);

        starSpawnTimer -= deltaTimeSeconds;
        if (starSpawnTimer <= 0) {
            for (int i = 0; i < numberOfStarSpawned; i++) {
                int randomX = rand() % (int)resolution.x;
                int randomY = rand() % (int)resolution.y;
                starsSpawned.push_back(new Star("randomStar" + std::to_string(idOfStar), &meshes, glm::vec3(randomX, randomY, 0), pink, 0, 0, 5, 40.0f, 15.0f, glm::mat3(1)));
                idOfStar++;
            }
            starSpawnTimer = rand() % 3 + 2;
        }

        for (auto& star : starsSpawned) {
            RenderMesh2D(meshes[star->name], shaders["VertexColor"], star->modelMatrix);
        }

        for (int i = 0; i < nrOfStarsCollected; i++) {
            Star* star = starsCollected.at(i);
            star->modelMatrix = glm::mat3(1);
            star->modelMatrix *= transform2D::Translate(740 + 35 * i, resolution.y - 130);
            RenderMesh2D(meshes[star->name], shaders["VertexColor"], star->modelMatrix * transform2D::Rotate(0.31f));
        }

        spawnTurretIfPossible(emptySquare1, turretNumber, nrOfStarsCollected, turret1Cost, turretSpawned1, cornerRomb, glm::vec3(0, 0, 0), blue, rombSide);
        spawnTurretIfPossible(emptySquare2, turretNumber, nrOfStarsCollected, turret2Cost, turretSpawned2, cornerRomb, glm::vec3(squareSide + 75, 0, 0), orange, rombSide);
        spawnTurretIfPossible(emptySquare3, turretNumber, nrOfStarsCollected, turret3Cost, turretSpawned3, cornerRomb, glm::vec3(2 * squareSide + 125, 0, 0), yellow, rombSide);
        spawnTurretIfPossible(emptySquare4, turretNumber, nrOfStarsCollected, turret4Cost, turretSpawned4, cornerRomb, glm::vec3(3 * squareSide + 200, 0, 0), purple, rombSide);
    }
}

void m1::Tema1::FrameEnd()
{
}

void m1::Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void m1::Tema1::OnKeyPress(int key, int mods)
{
}

void m1::Tema1::OnKeyRelease(int key, int mods)
{
}

void m1::Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::vec2 resolution = window->GetResolution();
    moveSelectedTurret(mouseX, mouseY, emptySquare1, turretSpawned1, turret1Selected, resolution.y);
    moveSelectedTurret(mouseX, mouseY, emptySquare2, turretSpawned2, turret2Selected, resolution.y);
    moveSelectedTurret(mouseX, mouseY, emptySquare3, turretSpawned3, turret3Selected, resolution.y);
    moveSelectedTurret(mouseX, mouseY, emptySquare4, turretSpawned4, turret4Selected, resolution.y);

}

void m1::Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::vec2 resolution = window->GetResolution();
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (auto& star : starsSpawned) {
            if ((mouseX >= star->corner.x - 40 && mouseX <= star->corner.x + 40)
                && ((resolution.y - mouseY) >= star->corner.y - 40 && (resolution.y - mouseY) <= star->corner.y + 40)) {
                removeFromVector(starsSpawned, star);
                nrOfStarsCollected++;
                starsCollected.push_back(new Star("starCollected" + std::to_string(idOfStar), &meshes, glm::vec3(0, 0, 0), silver, 0, 0, 5, 15.f, 5.f, glm::mat3(1)));
                idOfStar++;
                return;
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (selectTurret(mouseX, mouseY, emptySquare1, turretSpawned1, turret1Cost, nrOfStarsCollected, turret1Selected)) {
			return;
        }
        else if (selectTurret(mouseX, mouseY, emptySquare2, turretSpawned2, turret2Cost, nrOfStarsCollected, turret2Selected)) {
            return;
        }
        else if (selectTurret(mouseX, mouseY, emptySquare3, turretSpawned3, turret3Cost, nrOfStarsCollected, turret3Selected)) {
			return;
        }
        else if (selectTurret(mouseX, mouseY, emptySquare4, turretSpawned4, turret4Cost, nrOfStarsCollected, turret4Selected)) {
			return;
		}
	}

    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        for (auto& square : squares) {
            if ((mouseX >= square.second->corner.x && mouseX <= square.second->corner.x + square.second->squareSide) &&
                ((resolution.y - mouseY) >= square.second->corner.y && ((resolution.y - mouseY) <= square.second->corner.y + square.second->squareSide)) &&
                square.second->isOcupied) {
                for (auto& turret : turretSpawned1) {
                    if (square.second->cx == turret->cx && square.second->cy == turret->cy) {
                        turret->isDead = true;
                        square.second->isOcupied = false;
                        return;
                    }
                }
                for (auto& turret : turretSpawned2) {
                    if (square.second->cx == turret->cx && square.second->cy == turret->cy) {
                        turret->isDead = true;
                        square.second->isOcupied = false;
                        return;
                    }
                }
                for (auto& turret : turretSpawned3) {
                    if (square.second->cx == turret->cx && square.second->cy == turret->cy) {
                        turret->isDead = true;
                        square.second->isOcupied = false;
                        return;
                    }
                }
                for (auto& turret : turretSpawned4) {
                    if (square.second->cx == turret->cx && square.second->cy == turret->cy) {
                        turret->isDead = true;
                        square.second->isOcupied = false;
                        return;
                    }
                }
            }
        }
    }

}

void m1::Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    float cx = 0;
    float cy = 0;
    glm::vec2 resolution = window->GetResolution();
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (auto& square : squares) {
            if ((mouseX >= square.second->corner.x && mouseX <= square.second->corner.x + square.second->squareSide) &&
                ((resolution.y - mouseY) >= square.second->corner.y && ((resolution.y - mouseY) <= square.second->corner.y + square.second->squareSide)) &&
                !square.second->isOcupied) {
                cx = square.second->cx;
                cy = square.second->cy;
                square.second->isOcupied = true;
            }
        }

        if (turret1Selected) {
            updateTurretProperties(turretSpawned1, &emptySquare1, turret1Selected, cx, cy);
        }
        else if (turret2Selected) {
            updateTurretProperties(turretSpawned2, &emptySquare2, turret2Selected, cx, cy);
        }
        else if (turret3Selected) {
            updateTurretProperties(turretSpawned3, &emptySquare3, turret3Selected, cx, cy);
        }
        else if (turret4Selected) {
            updateTurretProperties(turretSpawned4, &emptySquare4, turret4Selected, cx, cy);
        }


        std::vector<std::vector<Turret*>> turretSpawnedAll = { turretSpawned1, turretSpawned2, turretSpawned3, turretSpawned4 };
        std::vector<int> turretCosts = { turret1Cost, turret2Cost, turret3Cost, turret4Cost };

        for (size_t i = 0; i < turretSpawnedAll.size(); ++i) {
            for (auto& turret : turretSpawnedAll[i]) {
                if (turret->isSelected) {
                    if (turret->cx == 0 && turret->cy == 0) {
                        turret->modelMatrix = glm::mat3(1);
                        turret->isSelected = false;
                        turret->isMoved = false;
                    }
                    else {
                        turret->isSelected = false;
                        turret->isMoved = true;
                        nrOfStarsCollected -= turretCosts[i];
                    }
                }
            }
        }
	}
}

void m1::Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void m1::Tema1::OnWindowResize(int width, int height)
{
}

void m1::Tema1::createStarIfTurretCanShoot(
    std::vector<Star*>& activeStarsLine,
    int& idOfStar,
    std::unordered_map<std::string, Mesh*>* meshes,
    Turret* turret,
    int turretCy,
    int nrEnemyBlueLane,
    int nrEnemyYellowLane,
    int nrEnemyPurpleLane,
    int nrEnemyOrangeLane
) {
    if (turret->cy == turretCy) {
        if (
            (turret->color == blue && nrEnemyBlueLane > 0) ||
            (turret->color == yellow && nrEnemyYellowLane > 0) ||
            (turret->color == purple && nrEnemyPurpleLane > 0) ||
            (turret->color == orange && nrEnemyOrangeLane > 0)
            ) {
            activeStarsLine.push_back(
                new Star("star" + std::to_string(idOfStar), meshes, glm::vec3(0, 0, 0), turret->color, turret->cx, turret->cy, 5, 40.0f, 15.0f, glm::mat3(1))
            );
            idOfStar++;
            turret->shootRatio = shootRatioGlobal;
        }
    }
}

void m1::Tema1::updateStarsAndCheckCollisions(std::vector<Star*>& activeStarsLine, std::vector<Enemy*>& activeEnemiesLine, float deltaTimeSeconds, float starSpeed, float starAngularStep)
{
    for (auto& star : activeStarsLine) {
        star->modelMatrix = glm::mat3(1);
        star->modelMatrix *= transform2D::Translate(star->cx, star->cy);
        star->translateX += deltaTimeSeconds * starSpeed;
        star->modelMatrix *= transform2D::Translate(star->translateX, 0);
        star->angularStep -= deltaTimeSeconds * starAngularStep;
        star->modelMatrix *= transform2D::Rotate(star->angularStep);
        RenderMesh2D(meshes[star->name], shaders["VertexColor"], star->modelMatrix * transform2D::Rotate(0.32f));

        for (auto& enemy : activeEnemiesLine) {
            if (star->cx + star->translateX >= enemy->cx && star->color == enemy->color2) {
                removeFromVector(activeStarsLine, star);
                enemy->health--;
            }
        }
    }
}

template<typename T>
void m1::Tema1::removeFromVector(std::vector<T*>& vector, T* item)
{
    auto it = std::find(vector.begin(), vector.end(), item);
	int index = it - vector.begin();
	vector.erase(vector.begin() + index);
}

void m1::Tema1::handleTurretCollision(std::vector<Turret*>& turretSpawned, Enemy* enemy, std::unordered_map<int, Square*>& squares)
{
    bool ok = false;
    for (auto& turret : turretSpawned) {
        if (turret->cy == enemy->cy && enemy->cx <= turret->cx + 0.5 && enemy->cx >= turret->cx - 0.5) {            // 0.5 for errors
            turret->isDead = true;
		}
	}
}

void m1::Tema1::spawnTurretIfPossible(Square* emptySquare, int& turretNumber, int nrOfStarsCollected, int turretCost, std::vector<Turret*>& turretSpawned, glm::vec3& cornerRomb, glm::vec3& offset, glm::vec3& turretColor, float rombSide)
{
    if (!emptySquare->isOcupied && nrOfStarsCollected >= turretCost) {
        turretSpawned.push_back(new Turret(
            "turret" + std::to_string(turretNumber),
            &meshes,
            cornerRomb + offset,
            turretColor,
            rombSide,
            turretCost,
            glm::mat3(1)
        ));
        turretNumber++;
        emptySquare->isOcupied = true;
    }
}

void m1::Tema1::decreaseEnemyCountAndMarkAsDead(Enemy* enemy, int* nrEnemyYellowLane, int* nrEnemyPurpleLane, int* nrEnemyOrangeLane, int* nrEnemyBlueLane)
{
    if (enemy->color2 == yellow) {
        (*nrEnemyYellowLane)--;
    }
    else if (enemy->color2 == purple) {
        (*nrEnemyPurpleLane)--;
    }
    else if (enemy->color2 == orange) {
        (*nrEnemyOrangeLane)--;
    }
    else if (enemy->color2 == blue) {
        (*nrEnemyBlueLane)--;
    }

    enemy->isDead = true;
}

void m1::Tema1::updateAndRenderEnemy(Enemy* enemy, const glm::vec2& resolution, Square* square, float deltaTimeSeconds, float enemySpeed, std::vector<Enemy*>& activeEnemiesLine)
{
    if (enemy->isDead) {
        enemy->scaleX -= deltaTimeSeconds;
        enemy->scaleY -= deltaTimeSeconds;
        enemy->modelMatrix = glm::mat3(1);
        enemy->modelMatrix *= transform2D::Translate(enemy->cx, enemy->cy);
        enemy->modelMatrix *= transform2D::Scale(enemy->scaleX, enemy->scaleY);
        RenderMesh2D(meshes[enemy->name], shaders["VertexColor"], enemy->modelMatrix * transform2D::Rotate(0.53f));
        if (enemy->scaleX <= 0 && enemy->scaleY <= 0) {
            removeFromVector(activeEnemiesLine, enemy);
        }
    }
    else {
        enemy->modelMatrix = glm::mat3(1);
        enemy->modelMatrix *= transform2D::Translate(resolution.x - 100, square->cy);
        enemy->translateX -= deltaTimeSeconds * enemySpeed;
        enemy->cx -= deltaTimeSeconds * enemySpeed;
        enemy->modelMatrix *= transform2D::Translate(enemy->translateX, 0);
        RenderMesh2D(meshes[enemy->name], shaders["VertexColor"], enemy->modelMatrix * transform2D::Rotate(0.53f));
    }
}

bool m1::Tema1::selectTurret(int mouseX, int mouseY, Square* emptySquare, std::vector<Turret*>& turretSpawned, int turretCost, int nrOfStarsCollected, bool& turretSelected)
{
    glm::vec2 resolution = window->GetResolution();
    if ((mouseX >= emptySquare->corner.x && mouseX <= emptySquare->corner.x + emptySquare->squareSide) &&
        ((resolution.y - mouseY) >= emptySquare->corner.y && ((resolution.y - mouseY) <= emptySquare->corner.y + emptySquare->squareSide)) &&
        turretSpawned.size() > 0 && nrOfStarsCollected >= turretCost) {

        turretSelected = true;
        for (auto& turret : turretSpawned) {
            if (!turret->isSelected && !turret->isMoved) {
                turret->isSelected = true;
                return true;
            }
        }
    }
    return false;
}

void m1::Tema1::moveSelectedTurret(int mouseX, int mouseY, Square* emptySquare, std::vector<Turret*>& turretSpawned, bool turretSelected, int resolutionY)
{
    if (turretSelected) {
        for (auto& turret : turretSpawned) {
            if (turret->isSelected) {
				turret->modelMatrix = glm::mat3(1);
				turret->modelMatrix *= transform2D::Translate((float)mouseX - emptySquare->cx, (float)resolutionY - (float)mouseY - emptySquare->cy);
			}
		}
	}
}

void m1::Tema1::updateTurretProperties(std::vector<Turret*>& turretSpawned, Square** emptySquare, bool& turretSelected, float cx, float cy)
{
    for (auto& turret : turretSpawned) {
        if (turret->isSelected) {
            turret->modelMatrix = glm::mat3(1);
            turret->modelMatrix *= transform2D::Translate(cx - (*emptySquare)->cx, cy - (*emptySquare)->cy);
            turret->canShoot = true;
            turret->cx = cx;
            turret->cy = cy;
            (*emptySquare)->isOcupied = false;
            turretSelected = false;
            break;
        }
    }
}

void m1::Tema1::handleDeadTurret(Turret* turret, Square* emptySquare, std::unordered_map<std::string, Mesh*>& meshes, std::vector<Turret*>& turretSpawned, std::unordered_map<int, Square*> squares, float deltaTimeSeconds)
{
    if (turret->isDead) {
        turret->scaleX -= deltaTimeSeconds;
        turret->scaleY -= deltaTimeSeconds;
        turret->modelMatrix = glm::mat3(1);
        turret->modelMatrix *= transform2D::Translate(turret->cx - emptySquare->cx, turret->cy - emptySquare->cy);
        turret->modelMatrix *= transform2D::Scale(turret->scaleX, turret->scaleY);
        RenderMesh2D(meshes[turret->name], shaders["VertexColor"], turret->modelMatrix);

        if (turret->scaleX <= 0 && turret->scaleY <= 0) {
            for (auto& square : squares) {
                if (square.second->cy == turret->cy && square.second->cx == turret->cx) {
                    square.second->isOcupied = false;
                    break;
                }
            }
            removeFromVector(turretSpawned, turret);
        }
    }
    else {
        RenderMesh2D(meshes[turret->name], shaders["VertexColor"], turret->modelMatrix);
    }
}

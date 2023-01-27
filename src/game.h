#ifndef _GAME_H
#define _GAME_H

#include <list>
#include "macro.h"
#include "image.h"

#define BRICKS_PER_LEVEL 4

constexpr float __scale = 100.0f;
constexpr float __size = 20.0f;

enum struct UserCommand {
    None,
    JumpLeft,
    JumpRight,
};

struct ColliderRect {
    float2 position;
    float2 dim;
    float2 min;
    float2 max;
    colorf color = { 1.0f, 1.0f, 1.0f };
    void draw(Image & image, float height) const;
    void calcBound();
    bool hit(ColliderRect const& other) const;
};

struct Player {
    ColliderRect collider;
    float2 speed;
    
    float jumpSpeedY = 4.0f * __scale;
    float jumpSpeedX = 2.0f * __scale;
    float2 gravity = { 0.0f, -9.8f * __scale };

    void init(Image & image);
    void tick(UserCommand command, float deltaTime);
};

struct Level {
    int id;
    ColliderRect collider;
    ColliderRect gates[2];
    ColliderRect bricks[BRICKS_PER_LEVEL];

    bool isHit(Player const& player) const;
    bool isPass(Player const& player) const;
    void draw(Image & image, float height) const;

    static Level generate(float2 const& position, float2 const& dim, int id);
};

struct Game {
    Image & image;
    std::list<Level> levels;
    Player player;
    float height;
    float displayHeight;
    int score;
    int id;

    Game(Image & image);

    bool isHit() const;

    void init();
    bool tick(UserCommand command, float deltaTime);
    void draw() const;
};

#endif
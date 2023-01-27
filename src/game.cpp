#include "game.h"

static void fillRect(Image & image, float2 const& position, float2 const& dim, colorf const& color) {
    int x0 = std::max(ftoi(position.x), 0);
    int y0 = std::max(ftoi(position.y), 0);
    int x1 = std::min(ftoi(position.x + dim.x), image.width);
    int y1 = std::min(ftoi(position.y + dim.y), image.height);

    for (int x = x0; x < x1; ++x) for (int y = y0; y < y1; ++y) {
        image.setPixel(x, y, color, true);
    }
}

void ColliderRect::draw(Image & image, float height) const {
    fillRect(image, {
        position.x,
        position.y - height,
    }, dim, color);
}

void ColliderRect::calcBound() {
    min = position;
    max = position + dim;
}

bool ColliderRect::hit(ColliderRect const& other) const {
    if (max.x > other.min.x && min.x < other.max.x
     && max.y > other.min.y && min.y < other.max.y) return true;
    
    return false;
}

void Player::init(Image & image) {
    speed.x = 0.0f;
    speed.y = 0.0f;
    collider.dim.x = __size;
    collider.dim.y = __size;
    collider.position.x = (image.width - collider.dim.x) * 0.5f;
    collider.position.y = (image.height - collider.dim.y) * 0.5f;
    collider.color = { 1.0f, 0.0f, 0.0f };
    collider.calcBound();
}

void Player::tick(UserCommand command, float deltaTime) {
    switch (command) {
    case UserCommand::None:
        break;
    case UserCommand::JumpLeft:
        speed.y = jumpSpeedY;
        speed.x = -jumpSpeedX;
        break;
    case UserCommand::JumpRight:
        speed.y = jumpSpeedY;
        speed.x = jumpSpeedX;
        break;
    }

    speed = speed + gravity * deltaTime;
    collider.position = collider.position + speed * deltaTime;
    collider.calcBound();
}

bool Level::isHit(Player const& player) const {
    if (player.collider.hit(gates[0])) return true;
    if (player.collider.hit(gates[1])) return true;

    for (int i = 0; i < BRICKS_PER_LEVEL; ++i)
        if (player.collider.hit(bricks[i])) return true;

    return false;
}

bool Level::isPass(Player const& player) const {
    if (player.collider.min.y > gates[0].max.y) return true;
    return false;
}


void Level::draw(Image & image, float height) const {
    // draw gates
    gates[0].draw(image, height);
    gates[1].draw(image, height);

    for (int i = 0; i < BRICKS_PER_LEVEL; ++i) bricks[i].draw(image, height);
}

Level Level::generate(float2 const& position_, float2 const& dim_, int id_) {
    const float enterHeight = __size;
    const float enterPadding = dim_.x * 0.2f;
    const float enterRange = dim_.x * 0.6f;
    const float enterWidth = __size * 5.0f;
    
    Level level;
    level.id = id_;
    level.collider.position = position_;
    level.collider.dim = dim_;
    level.collider.calcBound();

    float enterPosition = enterPadding + rnd() * enterRange - enterWidth * 0.5f;

    level.gates[0].position.x = 0;
    level.gates[0].position.y = position_.y;
    level.gates[0].dim.x = enterPosition;
    level.gates[0].dim.y = enterHeight;
    level.gates[0].calcBound();

    level.gates[1].position.x = enterPosition + enterWidth;
    level.gates[1].position.y = position_.y;
    level.gates[1].dim.x = dim_.x - enterPosition - enterWidth;
    level.gates[1].dim.y = enterHeight;
    level.gates[1].calcBound();

    // generate bricks
    for (int i = 0; i < BRICKS_PER_LEVEL; ++i) {
        if (rnd() < 0.5f) {
            level.bricks[i].position.x = level.gates[0].position.x + rnd() * level.gates[0].dim.x;
        }
        else {
            level.bricks[i].position.x = level.gates[1].position.x + rnd() * level.gates[1].dim.x;
        }
        level.bricks[i].position.y = position_.y + rnd() * dim_.y;
        level.bricks[i].dim.x = __size;
        level.bricks[i].dim.y = __size;
        level.bricks[i].calcBound();
    }

    return level;
}

Game::Game(Image & image_)
    : image(image_) {}

void Game::init() {
    height = 0.f;
    id = 1;
    score = 0;
    displayHeight = image.height * 0.5f;
    player.init(image);
    levels.clear();

    levels.push_back(Level::generate({
        0, (float)image.height,
    }, {
        (float)image.width, (float)image.height * 0.5f,
    }, id++));
}

bool Game::isHit() const {
    if (player.collider.position.x < 0
     || player.collider.position.x + player.collider.dim.x > image.width
     || player.collider.position.y < 0)
        return true;
    return false;
}

bool Game::tick(UserCommand command, float deltaTime) {
    auto const& back = levels.back();
    if (back.collider.max.y - height < (float)image.height) {
        levels.push_back(Level::generate({
            0, back.collider.max.y,
        }, {
            (float)image.width, (float)image.height * 0.5f,
        }, id++));
    }

    auto const& front = levels.front();
    if (front.collider.max.y - height < 0.0f) {
        levels.pop_front();
    }

    player.tick(command, deltaTime);

    float newHeight = player.collider.position.y - displayHeight;
    height = std::max(height, newHeight);

    if (isHit()) return true;

    for (auto const& level : levels) {
        if (level.isHit(player)) return true;
        if (level.isPass(player)) {
            score = std::max(score, level.id);
        }
    }

    return false;
}

void Game::draw() const {
    for (auto const& level : levels) level.draw(image, height);
    player.collider.draw(image, height);
}

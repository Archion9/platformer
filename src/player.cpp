#include "player.h"

float velocity = 0.0f;
bool isGrounded = false;

// Axis Aligned Bounding Box collision detection 
// https://en.wikipedia.org/wiki/Axis-aligned_bounding_box#Intersection_test
bool AABB(Rectangle a, Rectangle b);

Player::Player(Vector2 position, float speed)
{
    this->position = position;
    this->speed = speed;
    this->hitbox = {position.x, position.y, TILE_SIZE, TILE_SIZE};
}

void Player::Update(Camera2D &camera, World &world)
{
    float deltaTime = GetFrameTime();

    float lastPosX = position.x;
    float lastPosY = position.y;

    // Input check for jump
    if (IsKeyDown(KEY_SPACE) && isGrounded && velocity == 0.0f) // isGrounded can be removed if i want it to be sticky on top
    {
        velocity = -GRAVITY * 0.7f;
    }

    // Horizontal movement input
    if (IsKeyDown(KEY_RIGHT))
    {
        position.x += speed * deltaTime;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        position.x -= speed * deltaTime;
    }

    // Gravity and vertical velocity update
    float acceleration = GRAVITY;
    velocity += acceleration * deltaTime;
    position.y += velocity * deltaTime;

    Rectangle hitboxY = hitbox;
    hitboxY.y = position.y;

    Rectangle hitboxX = hitbox;
    hitboxX.x = position.x;

    // Unified collision loop
    for (int i = 0; i < world.width; i++)
    {
        for (int j = 0; j < world.height; j++)
        {
           if (world.tileMap[i][j] != World::SOLID) continue;

            Rectangle tileRect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            // --- Y Collision ---
            //Rectangle tempHitboxY = hitbox;
            //tempHitboxY.y = position.y;

            // Y axis collision
            if (AABB(hitboxY, tileRect)) {
                if (velocity > 0.0f)  // Falling
                {
                    position.y = tileRect.y - TILE_SIZE;
                    isGrounded = true;
                } else if (velocity < 0.0f)  // Jumping
                { 
                    isGrounded = false;
                    position.y = tileRect.y + TILE_SIZE;
                }
                velocity = 0.0f;
                hitboxY.y = position.y; 
            }

            // X axis collision
            if (AABB(hitboxX, tileRect)) {
                if (position.x > lastPosX)  // Moving right
                {
                    position.x = tileRect.x - TILE_SIZE;
                } else if (position.x < lastPosX)  // Moving left
                {
                    position.x = tileRect.x + TILE_SIZE;
                }
                hitboxX.x = position.x;
            }
        }
    }

    // Camera follow player
    camera.target.x = position.x + GetScreenWidth() - TILE_SIZE;

    // Final hitbox update
    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::Draw()
{
    DrawRectangleRec(hitbox, RED);
}

bool AABB(Rectangle a, Rectangle b)
{
    return (a.x < b.x + b.width &&
            a.x + a.width > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
}

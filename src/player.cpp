#include "player.h"

float velocity = 0.0f;

bool AABB(Rectangle a, Rectangle b);

Player::Player(Vector2 position, float speed)  
{
    this->position = position;
    this->speed = speed;
    this->hitbox = { position.x, position.y, 50.0f, 50.0f }; 
}

void Player::Update(Camera2D& camera, World& world) {

    // Delta time
    float deltaTime = GetFrameTime();

    // Needed for Y axis
    float acceleration = GRAVITY;
    // Velocity: something like m/s^2
    velocity += acceleration * deltaTime;

    this->position.y += velocity * deltaTime;

    //Y axis check
    hitbox.y = position.y;

    for (int i = 0; i < world.width; i++)
    {
        for (int j = 0; j < world.height; j++)
        {
            if (world.tileMap[i][j] == World::SOLID){

                if (AABB(this->hitbox, (Rectangle){j*50,i*50,50,50}))
                {
                 
                    if(velocity > 0.0f) // Falling
                    {
                        this->position.y = i * TILE_SIZE - TILE_SIZE;
                        velocity = 0.0f; 
                    }
                    else if(velocity < 0.0f) // I believe i can fly
                    {
                        this->position.y = i * TILE_SIZE + TILE_SIZE;
                        velocity = 0.0f;
                    }

                    hitbox.y = position.y;
                }
            }
        }
    }

   
    if (IsKeyPressed(KEY_SPACE) && velocity == 0.0f)
    {
        velocity = -10.0f;
    }
    
    float lastPos = position.x;

    if (IsKeyDown(KEY_RIGHT)) {
        position.x += speed * deltaTime;
    }
    if (IsKeyDown(KEY_LEFT)) {
        position.x -= speed * deltaTime;
    }
   
    //X axis check
    hitbox.x = position.x;
 
      for (int i = 0; i < world.width; i++)
    { 
        for (int j = 0; j < world.height; j++)
        {
            if (world.tileMap[i][j] == World::SOLID){

                if (AABB(this->hitbox, (Rectangle){j*50,i*50,50,50}))
                {
                 
                    if(position.x > lastPos) // Left
                    {
                        this->position.x = j * TILE_SIZE - TILE_SIZE;
                        velocity = 0.0f;
                    }
                    else if(position.x < lastPos) // Right
                    {
                        this->position.x = j * TILE_SIZE + TILE_SIZE;
                        velocity = 0.0f;
                    }

                    hitbox.x = position.x;
                }
            }
        }
    }
    camera.target.x = position.x + GetScreenWidth() - TILE_SIZE;
    // Update hitbox position
    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::Draw() {
    DrawRectangleRec(hitbox, RED);
}

bool AABB(Rectangle a, Rectangle b) {
    return (a.x < b.x + b.width &&
            a.x + a.width > b.x &&
            a.y < b.y + b.height &&
            a.y + a.height > b.y);
}

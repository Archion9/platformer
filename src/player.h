#ifndef PLAYER_H
#define PLAYER_H

#include "include.h"
#include "world.h"

class Player
{
public:
    Player(Vector2 position, float speed);
    void Update(Camera2D &camera, World &world);
    void Draw();
    Vector2 GetPosition() const { return position; }

private:
    Vector2 position;
    float speed;
    Rectangle hitbox;
};

#endif // PLAYER_H
#include "Ball.h"

bool Ball::IsCollidingWith(GameObject* other) {
    Vector2 otherPos = other->GetPosition();

    // if collosion is with pad check the collision and if pad is not an empty pointer
    Pad* pad = dynamic_cast<Pad*>(other);
    if (pad != nullptr) {
        int width = pad->GetWidth();

        //same row
        if (position.y == otherPos.y) {
            // inside pad width
            if (position.x >= otherPos.x - width &&
                position.x <= otherPos.x + width) {
                return true;
            }
        }
        return false;
    }

    // otherwise, normal behaiviour
    return position == otherPos;
}

bool Ball::HasObjectAtPosition(int x, int y) {
    Vector2 targetPosition(x, y);

    for (int i = 0; i < objects->size(); i++) {
        if ((*objects)[i] == this) {
            continue;
        }

        if ((*objects)[i]->GetPosition() == targetPosition) {
            return true;
        }
    }

    return false;
}

void Ball::Bounce(GameObject* other) {
    Vector2 otherPosition = other->GetPosition();

    bool hasObjectAbove = HasObjectAtPosition(otherPosition.x, otherPosition.y - 1);
    bool hasObjectBelow = HasObjectAtPosition(otherPosition.x, otherPosition.y + 1);
    bool hasObjectLeft = HasObjectAtPosition(otherPosition.x - 1, otherPosition.y);
    bool hasObjectRight = HasObjectAtPosition(otherPosition.x + 1, otherPosition.y);

    bool bounceHorizontal = hasObjectAbove || hasObjectBelow;
    bool bounceVertical = hasObjectLeft || hasObjectRight;

    if (!bounceHorizontal && !bounceVertical) {
        direction.x = -direction.x;
        direction.y = -direction.y;
        return;
    }

    if (bounceVertical) {
        direction.y = -direction.y;
    }

    if (bounceHorizontal) {
        direction.x = -direction.x;
    }
}

void Ball::Update() {
    position.x = position.x + direction.x;
    position.y = position.y + direction.y;

    for (int i = 0; i < objects->size(); i++) {
        GameObject* currentObject = (*objects)[i];

        if (currentObject == this) {
            continue;
        }

        if (IsCollidingWith(currentObject)) {
            Bounce(currentObject);
            break;
        }
    }
}
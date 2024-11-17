#include <vector>
#include "object.hpp"

class CollisionSolver {
public:
    // checks for collisions between objects
    // and resolves them if they occur
    void solveCollisions(std::vector<Object>& objects) {
        for (size_t i = 0; i < objects.size(); ++i) {
            for (size_t j = i + 1; j < objects.size(); ++j) {
                checkCollision(objects[i], objects[j]);
            }
        }
    }

private:
    void checkCollision(Object& A, Object& B) {
        // calculate the distance between the two object centres
        double dist = A.c_pos.Distance(B.c_pos);
        double radiiSum = A.r + B.r;

        // if the distance is less than or equal to the sum of their radii, there's a collision
        if (dist < radiiSum) {
            resolveCollision(A, B, dist);
        }
    }

    // move each object by half of the overlap length into opposite directions
    void resolveCollision(Object& A, Object& B, double dist) {
        const Vec2 collision_axis = A.c_pos - B.c_pos;
        const Vec2 n = collision_axis * ( 1.0 / dist);
        const float overlap = (A.r + B.r) - dist;
        const Vec2 delta = n * (overlap * 0.5);  // half the length of the overlap
        A.c_pos += delta;
        B.c_pos -= delta;
    }

};

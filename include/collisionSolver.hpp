#ifndef COLLISIONSOLVER_HPP
#define COLLISIONSOLVER_HPP

#include <vector>
#include "grid.hpp"

class CollisionSolver {
public:
    // checks for collisions between objects
    // and resolves them if they occur

    void solveCollisions(Grid* grid) {
        // iterate through the grid skipping cells next to walls
        for (int x = 1; x < grid->columns - 1; ++x) {
            for (int y = 1; y < grid->rows - 1; ++y) {

                Cell& current_cell = grid->grid[y][x];
                // iterate through surrounding cells (including the current cell)
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        Cell& other_cell = grid->grid[y + dy][x + dx];
                        checkCellsCollisions(current_cell, other_cell);
                    }
                }
            }
        }
    }

private:
    void checkCellsCollisions(Cell& cellA, Cell& cellB) {
        for (Object* objA : cellA.objects) {
            for (Object* objB : cellB.objects) {
                if (objA != objB && objA < objB) { // avoid duplicate checks
                    checkCollision(*objA, *objB);
                }
            }
        }
    }

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
        const Vec2 n = collision_axis * (1.0 / dist);
        const float overlap = (A.r + B.r) - dist;
        const Vec2 delta = n * (overlap * 0.5);  // half the length of the overlap
        if (!A.isStatic) A.c_pos += delta;
        if (!B.isStatic) B.c_pos -= delta;
    }

};

#endif

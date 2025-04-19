#ifndef GRID_HPP
#define GRID_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include "object.hpp"

class Cell {
public:
    std::vector<Object*> objects;

    void clear() {
        objects.clear();
    }

    void add(Object* object) {
        objects.push_back(object);
    }

    void printContents() const {
        if (objects.empty()) {
            std::cout << "No objects in this cell." << std::endl;
        }
        else {
            std::cout << "Objects in this cell: ";
            for (const auto& obj : objects) {
                std::cout << "(" << obj->c_pos.x << ", " << obj->c_pos.y << ") ";
            }
            std::cout << std::endl;
        }
    }
};

class Grid {
public:
    Grid(double width, double height, const double maxR) {
        cellSize = static_cast<int>(maxR * 2.0);  // Ensure the correct size calculation
        rows = static_cast<int>(std::ceil(height / cellSize)) + 2;
        columns = static_cast<int>(std::ceil(width / cellSize)) + 2;

        grid.resize(rows, std::vector<Cell>(columns));
    }

    int rows, columns, cellSize;
    std::vector<std::vector<Cell>> grid;

    // Function to place objects in the correct cells
    void Update(const std::vector<std::unique_ptr<Object>>* objects) {
        // Clear all cells
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < columns; ++col) {
                grid[row][col].clear();
            }
        }

        // Place each object in the corresponding cell
        for (const auto& object : *objects) {
            int col = static_cast<int>(std::floor(object->c_pos.x / cellSize)) + 1;
            int row = static_cast<int>(std::floor(object->c_pos.y / cellSize)) + 1;

            // Ensure that the indices are within bounds
            if (col >= 0 && col < columns && row >= 0 && row < rows) {
                grid[row][col].add(object.get());
            }
            else {
                // Handle case where object is out of bounds
                std::cerr << "Object at position (" << object->c_pos.x << ", " << object->c_pos.y << ") is out of bounds!" << std::endl;
            }
        }
    }

    // Debugging purposes: Print the grid and its contents
    void printGrid() const {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < columns; ++col) {
                std::cout << "Cell (" << row << ", " << col << "): ";
                grid[row][col].printContents();
            }
        }
    }
};

#endif

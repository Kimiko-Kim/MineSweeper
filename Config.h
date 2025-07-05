#pragma once

constexpr int GRID_SIZE = 10;
constexpr int TILE_SIZE = 48;

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 850;
constexpr int OFFSET_Y = 120;
constexpr int OFFSET_X = (WINDOW_WIDTH - GRID_SIZE * TILE_SIZE) / 2;

enum class CellType : int {
    Empty = 0,
    Mine = 9,
    Closed = 10,
    Flag = 11,
};

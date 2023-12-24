#pragma once

#include <iostream>
#include <utility>

namespace GameState {
    class Board {
        private:
            char **board;
            short size = 3;
        public:
            Board();
            ~Board();
            char** GetBoard();
            void SetField(std::pair<int, int> coord, char player);
            short GetSize();
            bool isFree(int i, int j);
    };

    class Game {
        private:
            Board board;
            bool turn;
        public:
            Game(bool player = true);
            void Start();
            short isEnded();
        };
}

namespace AI {
    std::pair<int, int> Move(GameState::Board &board);
}

namespace Player {
    std::pair<int, int> Move(GameState::Board &board);
    void Print(GameState::Board &board);
}
#include "game.hpp"
using namespace GameState;

Board::Board()
{
    // tworzy dwuwymiarową tablicę o rozmiarze "size" i wypełnia ją znakami "."
    this->board = new char *[size];
    for (int i = 0; i < size; i++)
        this->board[i] = new char[size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            this->board[i][j] = '.';
}

Board::~Board()
{
    // usuwa zaalokowaną wcześniej pamięć z tablicy dwuwymiarowej
    for (int i = 0; i < size; i++)
        delete board[i];
    delete board;
}

char **Board::GetBoard()
{
    // zwraca wskaźnik do tablicy dwuwymiarowej reprezentującej planszę
    return board;
}

void Board::SetField(std::pair<int, int> coord, char player)
{
    // ustawia znak gracza na polu o współrzędnych "coord"
    this->board[coord.first][coord.second] = player;
}

short Board::GetSize()
{
    // zwraca rozmiar planszy
    return size;
}

bool Board::isFree(int i, int j)
{
    // sprawdza, czy pole o współrzędnych (i, j) jest wolne (czyli nie jest zajęte przez żadnego gracza)
    return this->board[i][j] == '.';
}

Game::Game(bool player) : board()
{
    // konstruktor klasy Game, ustawiający wartość zmiennej "turn" na "player"
    turn = player;
}

void Game::Start()
{
    Player::Print(board);
    do
    {
        // Jeśli jest tura gracza, wykonaj ruch gracza i ustaw pole na planszy.
        if (turn)
        {
            board.SetField(Player::Move(board), 'X');
            turn = false;
        }
        // W przeciwnym wypadku wykonaj ruch AI i ustaw pole na planszy.
        else
        {
            board.SetField(AI::Move(board), 'O');
            turn = true;
        }
        // Wydrukuj planszę po wykonanym ruchu.
        Player::Print(board);
    } while (this->isEnded() == -1);

    // Sprawdź, czy gra się zakończyła.
    if (this->isEnded() == 1)
    {
        if (!turn)
            std::cout << "Player wins!\n";
        else
            std::cout << "Computer wins!\n";
    }
    else
        std::cout << "Draw!\n";
}

short Game::isEnded()
{
    char **state = board.GetBoard(); // Pobiera aktualny stan planszy.

    // Sprawdza czy któreś z trzech pól na każdym wierszu lub kolumnie jest takie samo, odróżnione od pustego pola.
    for (int i = 0; i < board.GetSize(); i++)
    {
        if (state[i][0] == state[i][1] && state[i][1] == state[i][2] && state[i][0] != '.')
            return 1; // Zwraca 1, jeśli ktoś wygrał.

        if (state[0][i] == state[1][i] && state[1][i] == state[2][i] && state[0][i] != '.')
            return 1; // Zwraca 1, jeśli ktoś wygrał.
    }

    // Sprawdza czy któryś z dwóch skosów jest taki sam i nie jest to puste pole.
    if (state[0][0] == state[1][1] && state[1][1] == state[2][2] && state[1][1] != '.')
        return 1; // Zwraca 1, jeśli ktoś wygrał.
    if (state[0][2] == state[1][1] && state[1][1] == state[2][0] && state[1][1] != '.')
        return 1; // Zwraca 1, jeśli ktoś wygrał.

    // Sprawdza czy plansza jest pełna, a nie ma zwycięzcy (remis).
    for (int i = 0; i < board.GetSize(); i++)
        for (int j = 0; j < board.GetSize(); j++)
            if (state[i][j] == '.')
                return -1; // Zwraca -1, jeśli plansza jest jeszcze niepełna.

    return 0; // Zwraca 0, jeśli nie ma zwycięzcy, ale plansza jest już pełna (remis).
}

std::pair<int, int> AI::Move(GameState::Board &board)
{
    // Najlepsze ruchy zaczynamy od środka planszy.
    if (board.isFree(1, 1))
        return std::pair<int, int>{1, 1};

    // Kolejne dobre ruchy to pola po krzyżu.
    else if (board.isFree(0, 1))
        return std::pair<int, int>{0, 1};
    else if (board.isFree(1, 0))
        return std::pair<int, int>{1, 0};
    else if (board.isFree(2, 1))
        return std::pair<int, int>{2, 1};
    else if (board.isFree(1, 2))
        return std::pair<int, int>{1, 2};

    // Jeśli wszystkie ruchy po krzyżu zostały wykonane, pozostają jeszcze rogi planszy.
    else if (board.isFree(0, 0))
        return std::pair<int, int>{0, 0};
    else if (board.isFree(2, 2))
        return std::pair<int, int>{2, 2};
    else if (board.isFree(0, 2))
        return std::pair<int, int>{0, 2};

    // Jeśli nie ma wolnych pól po krzyżu ani w rogach, wybieramy pozostałe pola.
    return std::pair<int, int>{2, 0};
}

std::pair<int, int> Player::Move(GameState::Board &board)
{
    // Deklaracja zmiennej przechowującej wybór gracza
    int column;
    char row;

    // Wypisanie instrukcji wyboru pola
    std::cout << "Choose a field \"row column\"\n";

    // Pobranie wyboru gracza
    std::cin >> row >> column;

    // Sprawdzenie poprawności wyboru
    while (row < 'A' || row > 'C' || column < 0 || column > 2 || !board.isFree(row - 'A', column))
    {
        std::cout << "Invalid coordinates!\n";

        // Ponowne pobranie wyboru gracza
        std::cin >> row >> column;
    }

    // Zwrócenie wyboru gracza jako pary (wiersz, kolumna)
    return std::pair<int, int>{row - 'A', column};
}

void Player::Print(GameState::Board &board)
{
    // Pobranie stanu planszy
    char **state = board.GetBoard();

    // Wypisanie nagłówka gry
    std::cout << "Tic Tac Toe\n";
    std::cout << "Player - X : Computer - O\n\n";

    // Wypisanie planszy w formacie 3x3
    std::cout << "   0   1   2  \n";
    printf("A  %c | %c | %c \n",
           state[0][0] == '.' ? ' ' : state[0][0],
           state[0][1] == '.' ? ' ' : state[0][1],
           state[0][2] == '.' ? ' ' : state[0][2]);
    std::cout << "  -----------\n";

    printf("B  %c | %c | %c \n",
           state[1][0] == '.' ? ' ' : state[1][0],
           state[1][1] == '.' ? ' ' : state[1][1],
           state[1][2] == '.' ? ' ' : state[1][2]);
    std::cout << "  -----------\n";

    printf("C  %c | %c | %c \n",
           state[2][0] == '.' ? ' ' : state[2][0],
           state[2][1] == '.' ? ' ' : state[2][1],
           state[2][2] == '.' ? ' ' : state[2][2]);
}

#include <iostream>
#include <vector>
#include <string>

enum Piece { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum Color { NONE, UPPER, LOWER };

struct ChessPiece {
    Piece piece;
    Color color;
};

class ChessBoard {
public:
    ChessBoard() {
        board.resize(8, std::vector<ChessPiece>(8, { EMPTY, NONE }));
        setupBoard();
    }

    void displayBoard() {
        std::cout << "    a   b   c   d   e   f   g   h  " << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        for (int i = 0; i < 8; ++i) {
            std::cout << 8 - i << " |";
            for (int j = 0; j < 8; ++j) {
                std::cout << " " << getPieceSymbol(board[i][j]) << " |";
            }
            std::cout << " " << 8 - i << std::endl;
            std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        }
        std::cout << "    a   b   c   d   e   f   g   h  " << std::endl;
    }

    bool makeMove(const std::string& moveStr, Color playerColor) {
        int startCol = moveStr[0] - 'a';
        int startRow = 8 - (moveStr[1] - '0');
        int endCol = moveStr[2] - 'a';
        int endRow = 8 - (moveStr[3] - '0');

        if (isValidMove(startRow, startCol, endRow, endCol, playerColor)) {
            board[endRow][endCol] = board[startRow][startCol];
            board[startRow][startCol] = { EMPTY, NONE };
            return true;
        } else {
            std::cout << "Movimento inválido!" << std::endl;
            return false;
        }
    }

private:
    std::vector<std::vector<ChessPiece>> board;

    void setupBoard() {
        for (int i = 0; i < 8; ++i) {
            board[1][i] = { PAWN, UPPER };
            board[6][i] = { PAWN, LOWER };
        }
        board[0][0] = board[0][7] = { ROOK, UPPER };
        board[7][0] = board[7][7] = { ROOK, LOWER };
        board[0][1] = board[0][6] = { KNIGHT, UPPER };
        board[7][1] = board[7][6] = { KNIGHT, LOWER };
        board[0][2] = board[0][5] = { BISHOP, UPPER };
        board[7][2] = board[7][5] = { BISHOP, LOWER };
        board[0][3] = { QUEEN, UPPER };
        board[7][3] = { QUEEN, LOWER };
        board[0][4] = { KING, UPPER };
        board[7][4] = { KING, LOWER };
    }

    char getPieceSymbol(const ChessPiece& piece) {
        if (piece.color == UPPER) {
            switch (piece.piece) {
            case PAWN: return 'P';
            case KNIGHT: return 'N';
            case BISHOP: return 'B';
            case ROOK: return 'R';
            case QUEEN: return 'Q';
            case KING: return 'K';
            default: return '.';
            }
        } else if (piece.color == LOWER) {
            switch (piece.piece) {
            case PAWN: return 'p';
            case KNIGHT: return 'n';
            case BISHOP: return 'b';
            case ROOK: return 'r';
            case QUEEN: return 'q';
            case KING: return 'k';
            default: return '.';
            }
        } else {
            return '.';
        }
    }

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Color playerColor) {
        ChessPiece startPiece = board[startRow][startCol];
        ChessPiece endPiece = board[endRow][endCol];

        if (startPiece.color != playerColor || startPiece.color == NONE) return false;
        if (endPiece.color == playerColor) return false;

        return true;
    }
};

int main() {
    ChessBoard board;
    Color currentPlayer = UPPER;
    std::string move;

    while (true) {
        board.displayBoard();
        std::cout << (currentPlayer == UPPER ? "Jogador 1 (maiúsculas)" : "Jogador 2 (minúsculas)") << ", faça seu movimento (ex: e2e4): ";
        std::cin >> move;

        if (move == "exit") break;

        if (move.length() == 4 && board.makeMove(move, currentPlayer)) {
            currentPlayer = (currentPlayer == UPPER) ? LOWER : UPPER;
        } else {
            std::cout << "Movimento inválido. Tente novamente." << std::endl;
        }
    }

    return 0;
}

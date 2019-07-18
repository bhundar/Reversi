#include "textdisplay.h"

TextDisplay::TextDisplay(int n): gridSize{n}{
    for (size_t height = 0; height < n; ++height) {
        std::vector<char> cell;
        for (size_t width = 0; width < n; ++width) {
            if (((height == (n /2) - 1) && (width == (n /2) - 1)) || (((height == (n /2)) && (width == (n /2))))) {
                cell.emplace_back('B');
            } else if (((height == (n/2)) && (width == (n /2) - 1)) ||  ((height == (n/2) - 1) && (width == (n /2)))){
                cell.emplace_back('W');
            } else {
                cell.emplace_back('-');
            }
        }
        theDisplay.emplace_back(cell);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    if ((whoNotified.getState().type == StateType::NewPiece) || (whoNotified.getState().type == StateType::Relay)) {
        if (whoNotified.getState().colour == Colour::Black) {
            this->theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
        } else if (whoNotified.getState().colour == Colour::White) {
            this->theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
        } else {
            this->theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = '-';
        }
    }
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
    for (int height = 0; height < td.theDisplay.size(); ++height) {
        for (int width = 0; width < td.theDisplay.size(); ++width) {
            std::cout << td.theDisplay[height][width];
        }
        std::cout << std::endl;
    }
    return out;
}


#include "grid.h"


Grid::~Grid(){
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
    
}

bool Grid::isFull() const {
    int fullCounter = 0;
    for (int i = 0; i < theGrid.size(); ++i) {
        for (int j = 0; j < theGrid.size(); ++j) {
            if ((theGrid[i][j].getInfo().colour == Colour::Black) || (theGrid[i][j].getInfo().colour == Colour::White)) {
                fullCounter += 0;
            }
        }
    }
    if (fullCounter == theGrid.size() * theGrid.size()) {
        return true;
    }
    return false;
}

Colour Grid::whoWon() const {
    int wCount = 0;
    int bCount = 0;
    for (int i = 0; i < theGrid.size(); ++i) {
        for (int j = 0; j < theGrid.size(); ++j) {
            if (theGrid[i][j].getInfo().colour == Colour::Black) {
                bCount += 1;
            } else if (theGrid[i][j].getInfo().colour == Colour::White) {
                wCount += 1;
            }
        }
    }
    if (bCount > wCount) {
        return Colour::Black;
    } else if (bCount < wCount) {
        return Colour::White;
    } else {
        return Colour::NoColour;
    }
}

void Grid::init(size_t n) {
    if ((n % 2 != 0) || (n < 3)) {
        throw std::exception();
    }
    for (int i = 0; i < theGrid.size(); ++i) {
        theGrid[i].clear();
    }
    theGrid.clear();
    for (size_t height = 0; height < n; ++height) {
        std::vector<Cell> cell;
        for (size_t width = 0; width < n; ++width) {
            Cell temp(height, width);
            if (((height == (n /2) - 1) && (width == (n /2) - 1)) || (((height == (n /2)) && (width == (n /2))))) {
                temp.setPiece(Colour::Black);
                cell.emplace_back(temp);
            } else if (((height == (n/2)) && (width == (n /2) - 1)) ||  ((height == (n/2) - 1) && (width == (n /2)))){
                temp.setPiece(Colour::White);
                cell.emplace_back(temp);
            } else {
                temp.setPiece(Colour::NoColour);
                cell.emplace_back(temp);
            }
        }
        theGrid.emplace_back(cell);
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
    if (r == 0 && c == 0) {
        theGrid[r][c].attach(&theGrid[r][c+1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
        theGrid[r][c].attach(&theGrid[r+1][c+1]);
    } else if (r == n - 1 && c == 0) {
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r-1][c+1]);
        theGrid[r][c].attach(&theGrid[r][c+1]);
    } else if (r == n - 1 && c == n - 1) {
        theGrid[r][c].attach(&theGrid[r-1][c-1]);
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r][c-1]);
    } else if (r == 0 && c == n - 1) {
        theGrid[r][c].attach(&theGrid[r][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
    } else if (r == 0) {
        theGrid[r][c].attach(&theGrid[r][c-1]);
        theGrid[r][c].attach(&theGrid[r][c+1]);
        theGrid[r][c].attach(&theGrid[r+1][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
        theGrid[r][c].attach(&theGrid[r+1][c+1]);
    } else if (c == n-1) {
        theGrid[r][c].attach(&theGrid[r-1][c-1]);
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
    } else if (r == n-1) {
        theGrid[r][c].attach(&theGrid[r-1][c-1]);
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r-1][c+1]);
        theGrid[r][c].attach(&theGrid[r][c-1]);
        theGrid[r][c].attach(&theGrid[r][c+1]);
    } else if (c == 0) {
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r-1][c+1]);
        theGrid[r][c].attach(&theGrid[r][c+1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
        theGrid[r][c].attach(&theGrid[r+1][c+1]);
    } else {
        theGrid[r][c].attach(&theGrid[r-1][c-1]);
        theGrid[r][c].attach(&theGrid[r-1][c]);
        theGrid[r][c].attach(&theGrid[r-1][c+1]);
        theGrid[r][c].attach(&theGrid[r][c-1]);
        theGrid[r][c].attach(&theGrid[r][c+1]);
        theGrid[r][c].attach(&theGrid[r+1][c-1]);
        theGrid[r][c].attach(&theGrid[r+1][c]);
        theGrid[r][c].attach(&theGrid[r+1][c+1]);
    }
        }
    }
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if ((r > theGrid.size()) && (c > theGrid.size())) {
        throw std::exception();
    }
    if (theGrid[r][c].getInfo().colour == Colour::NoColour) {
        if (colour == Colour::White) {
            theGrid[r][c].setPiece(Colour::White);
        } else if (colour == Colour::Black) {
            theGrid[r][c].setPiece(Colour::Black);
        }  
    } else {
        throw std::exception();
    }
}

void Grid::toggle(size_t r, size_t c) {
    theGrid[r][c].toggle();
}

std::ostream & operator<<(std::ostream &out, const Grid &g) {
    for (int height = 0; height < g.theGrid.size(); ++height) {
        for (int width = 0; width < g.theGrid.size(); ++width) {
            if (g.theGrid[height][width].getInfo().colour == Colour::Black) {
                out << "B";
            } else if (g.theGrid[height][width].getInfo().colour == Colour::White) {
                out << "W";
            } else {
                out << "-";
            }
        }
        std::cout << std::endl;
    }
    return out;
}


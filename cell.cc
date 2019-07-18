#include "cell.h"
#include <iostream>

Cell::Cell(size_t r, size_t c): r{r}, c{c}{}

void Cell::setPiece(Colour colour) {
    State s;
    s.type = StateType::NewPiece;
    this->colour = colour;
    this->setState(s);
    this->notifyObservers();
}

void Cell::toggle() {
    if (this->colour == Colour::White) {
        this->colour = Colour::Black;
    } else if (this->colour == Colour::Black) {
        this->colour = Colour::White;
    }
}

Direction oppDirection(Direction dir){
    if (dir == Direction::NW) {
        return Direction::SE;
     } else if (dir == Direction::N) {
       return  Direction::S;
     } else if (dir == Direction::NE) {
        return Direction::SW;
     } else if (dir == Direction::W) {
        return Direction::E;
    } else if (dir == Direction::E) {
        return Direction::W;
    } else if (dir == Direction::SW) {
        return Direction::NE;
    } else if (dir == Direction::S) {
        return Direction::N;
    } else if (dir == Direction::SE) {
        return Direction::NW;
    }
}


void Cell::notify(Subject<Info, State> &whoFrom) {
    // Set direction
    if (this->getInfo().colour == Colour::NoColour){
        return;
    }
    if (whoFrom.getInfo().row < this->getInfo().row) {
        if (whoFrom.getInfo().col < this->getInfo().col) {
            State s;
            s.direction = Direction::NW;
            this->setState(s);
        } else if (whoFrom.getInfo().col > this->getInfo().col) {
            State s;
            s.direction = Direction::NE;
            this->setState(s);
        } else {
            State s;
            s.direction = Direction::N;
            this->setState(s);
        }
    } else if (whoFrom.getInfo().row > this->getInfo().row) {
        if (whoFrom.getInfo().col < this->getInfo().col) {
            State s;
            s.direction = Direction::SW;
            this->setState(s);
        } else if (whoFrom.getInfo().col > this->getInfo().col) {
            State s;
            s.direction = Direction::SE;
            this->setState(s);
        } else {
            State s;
            s.direction = Direction::S;
            this->setState(s);
        }
    } else {
        if (whoFrom.getInfo().col < this->getInfo().col) {
            State s;
            s.direction = Direction::W;
            this->setState(s);
        } else if (whoFrom.getInfo().col > this->getInfo().col) {
            State s;
            s.direction = Direction::E;
            this->setState(s);
        } 
    } 

    if (whoFrom.getState().type == StateType::NewPiece) {
        if (whoFrom.getInfo().colour != this->getInfo().colour) {
            State s;
            s.type = StateType::Relay;
            s.colour = whoFrom.getInfo().colour;
            s.direction = this->getState().direction;
            this->setState(s);
            this->notifyObservers();
        } else {
            return;
        }
    } else if (whoFrom.getState().type == StateType::Relay) {
        if (whoFrom.getState().colour != this->getInfo().colour) {
            if (whoFrom.getState().direction == this->getState().direction) {
                State s;
                s.type = StateType::Relay;
                s.direction = whoFrom.getState().direction;
                s.colour = whoFrom.getState().colour;
                this->setState(s);
                this->notifyObservers();
            } else {
                return;
            }
        } else {
            if (whoFrom.getState().direction == this->getState().direction) {
                State s;
                s.type = StateType::Reply;
                s.direction = oppDirection(whoFrom.getState().direction);
                s.colour = this->getState().colour;
                this->setState(s);
                this->notifyObservers();
            } else {
                return;
            }
        }
    } else if (whoFrom.getState().type == StateType::Reply) {
        if (whoFrom.getState().direction == this->getState().direction) {
            if (whoFrom.getState().colour != this->getInfo().colour) {
                this->toggle();
                State s;
                s.type = StateType::Reply;
                s.colour = whoFrom.getInfo().colour; 
                s.direction = whoFrom.getState().direction;
                this->setState(s);
                this->notifyObservers();
            } else {
                return;
            }
        } else {
            return;
        }
    }
}

Info Cell::getInfo() const {
    return Info{r, c, colour};
}


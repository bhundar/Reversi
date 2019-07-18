#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "cell.h"
#include "state.h"
#include "textdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  int turn = 1;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // Add code here
      try {
        g.init(n);
        cout << g;
      } catch (std::exception& e) {
        continue;
      }
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      try {
        if (turn % 2 == 0) {
          g.setPiece(r, c, Colour::Black);
        } else {
          g.setPiece(r, c, Colour::White);
        }
        cout << g;
      } catch (std::exception& e) {
        continue;
      }
    }
    turn += 1;
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}


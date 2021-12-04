#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;
#define BOARDS 99

void show_board(int score[5][5], vector<vector<int >> board) {
    for (int j = 0; j < 5; j++) {
          for (int k = 0; k < 5; k++) {
              if (score[j][k]) {
                cout << " [!" << board[j][k] << "!] ";
              } else {
                cout << " [ " << board[j][k] << " ] ";
              }
          }
          cout << endl;
      }
      cout << endl;
}

int displayBoards(int scores[BOARDS][5][5], vector<vector<vector<int> > > boards) {
    for (int i=0; i < BOARDS; i++) {
      show_board(scores[i], boards[i]);
  }
  return 0;
}

vector<int> split_numbers (const string &s, char delim) {
    vector<int> result;
    stringstream ss (s);
    string item;
    while (getline(ss, item, delim)) {
        if (item == "")
            continue;
        result.push_back(stoi(item));
    }
    return result;
}

tuple<vector<vector<vector<int> > > , vector<int> > getInput(string fileName) {
    ifstream file(fileName);
    vector<int> bingoNumbers;
    vector<vector<int> > board;
    vector<vector<vector<int> > > boards;
    string line;

    getline(file, line);
    bingoNumbers = split_numbers(line, ',');
    getline(file, line);
    while (getline(file, line)) {
        if (line.length() == 0) {
            boards.push_back(board);
            board.clear();
            continue;
        }
        board.push_back(split_numbers(line, ' '));
    }
    file.close();
    boards.push_back(board);
    return {boards, bingoNumbers};
}

int is_winner_board(int score[5][5]) {
    for (int j = 0; j < 5; j++) {
          int colSum = 0;
          int rowSum = 0;
          for (int k = 0; k < 5; k++) {
              rowSum += score[j][k];
              colSum += score[k][j];
          }
          if (rowSum == 5 || colSum == 5) {
              return 1;
          }
      }
      return 0;
}

int markBingo(int (&scores)[BOARDS][5][5], vector<vector<vector<int> > > boards, int number) {
    for (int i=0; i < BOARDS; i++) {
        if (is_winner_board(scores[i]))
            continue;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                    if (boards[i][j][k] == number) {
                        scores[i][j][k] = 1;
                    }
            }
        }
  }
  return 0;
}

vector<int> winner_board(int (&scores)[BOARDS][5][5]) {
    vector<int> winners;
    for (int i=0; i < BOARDS; i++) {
      if (is_winner_board(scores[i]))
        winners.push_back(i);
    }
    return winners;
}

int calculate_score(int score[5][5], vector<vector<int> > board, int number) {
    int sum = 0;
    for (int j = 0; j < 5; j++) {
          for (int k = 0; k < 5; k++) {
              if (!score[j][k]) {
                  sum += board[j][k];
              }
          }
      }
      cout << "sum: " << sum << endl;
      return sum * number;
}

int main()
{
  tuple<vector<vector<vector<int> > > , vector<int> > input = getInput("Day4input.txt");
  vector<vector<vector<int> > > boards = get<0>(input);
  vector<int> numbers = get<1>(input);
  int scores[BOARDS][5][5] = {0};
  int lastWin;
  int lastWinner = -1;
  vector<int> winners;
  vector<int> pastWinners;
  for(int i = 0; i < numbers.size(); i++) {
      int number = numbers[i];
      cout << "number: " << number << endl;
      markBingo(scores, boards, number);
      displayBoards(scores, boards);
      winners = winner_board(scores);
      if (i == 0) {
          pastWinners = winners;
      }

      for(int j = 0; j < winners.size(); j++) {
          if (!count(pastWinners.begin(), pastWinners.end(), winners[j])) {
              lastWinner = winners[j];
              lastWin = number;
          }
      }
      pastWinners = winners;
  }
  show_board(scores[lastWinner], boards[lastWinner]);
  cout << "winner: " << lastWinner << endl;
  cout << "score: " << calculate_score(scores[lastWinner], boards[lastWinner], lastWin);
  return 0;
}
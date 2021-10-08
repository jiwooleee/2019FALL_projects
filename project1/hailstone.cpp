/*******************************************************************************
 *  Name:   Jiwoo Lee
 *  Email:  leeji-22@rhodes.edu
 *
 *  Description:  This program performs Hailstone Sequence algorithm in the
 *                range of numbers the user specifies and reports the number of
 *                steps each number in the range took to hit 1.
 *
 *  Written:       09/05/19
 *  Last updated:  09/13/19
 ******************************************************************************/

#include <iostream>
using namespace std;

int main() {
  long long int userNum;
  long long int length = 0;

  cout << "Enter a number: ";
  cin >> userNum;

  while (userNum != 1) {

    length++;

    if (userNum % 2 == 0) {
      userNum /= 2;
      cout << userNum << " ";
    }
    else {
      userNum = userNum * 3 + 1;
      cout << userNum << " ";
    }

  }

  cout << endl << "Length: " << length;

  return 0;
  }

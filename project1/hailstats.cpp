/*******************************************************************************
 *  Name:   Jiwoo Lee
 *  Email:  leeji-22@rhodes.edu
 *
 *  Description:  This program performs Hailstone Sequence algorithm in the
 *                range of numbers the user specifies and reports the shortest
 *                and longest number of steps the number in the range took to
 *                hit 1.
 *
 *  Written:       09/05/19
 *  Last updated:  09/13/19
 ******************************************************************************/

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// prompt the user for what they want to do
int act() {
  int userAct;

  cout << "Menu:" << endl << endl;
  cout << "1) Look for max and min in a specified range" << endl << endl;
  cout << "2) Look for every number that has a specified length";
  cout << " in a specified range" << endl << endl;
  cout << "3) Quit" << endl << endl;
  cout << "What do you want do? (Please enter a number)" << endl;
  cin >> userAct;
  cout << endl;

  return userAct;
}

int main() {
  long long int upperRan, lowerRan, upperlengRan, lowerlengRan;
  int userAct = act();

  // start the loop if the user does not want to quit
  while (userAct != 3) {

    // look for max & min lengths in a user-specified range
    if (userAct == 1) {
      long long int minLeng = INT_MAX;
      long long int maxLeng = -1;
      vector<long long> minNums(1);
      vector<long long> maxNums(1);

      // get the range from the user
      cout << "Enter the range you want to search: ";
      cin >> lowerRan >> upperRan;
      cout << endl << endl;

      // check if the range is valid
      while(lowerRan > upperRan) {

        // reset userAct
        cout << "Invalid range" << endl << endl;
        userAct = act();

        // reset the range
        cout  << "Enter the range you want to search: ";
        cin >> lowerRan >> upperRan;
        cout << endl << endl;

      }

      // calculate the length for each number in the range
      for (long long int i = lowerRan; i <= upperRan; ++i) {
        long long int currNum = i;
        long long int length = 0;

        while (currNum != 1) {
          length++;
          if (currNum % 2 == 0) {
            currNum /= 2;

          }
          else {
            currNum = currNum * 3 + 1;
          }
        }

        // update maxLeng, maxNum, minLeng, minNum
        if (length > maxLeng) {
            maxLeng = length;
            maxNums.resize(1);
            maxNums.at(0) = i;
          }
        else if (length == maxLeng) {
            maxNums.push_back(i);
          }
        if (length < minLeng) {
            minLeng = length;
            minNums.resize(1);
            minNums.at(0) = i;
          }
        else if (length == minLeng) {
            minNums.push_back(i);
         }
      }

      // print minimum length & numbers that achieve it
      cout << "Minimum length: " << minLeng << endl;
      cout << "Achieved by: ";
      if (minNums.size() == 1) cout << "1 number" << endl;
      else cout << minNums.size() << " numbers" << endl;
      for (int i = 0; i < minNums.size(); i++) {
        cout << minNums.at(i) << " ";
      }
      cout << endl << endl;

      // print maximum length & numbers that achieve it
      cout << "Maximum length: " << maxLeng << endl;
      cout << "Acheived by: ";
      if (maxNums.size() == 1) cout << "1 number" << endl;
      else cout << maxNums.size() << " numbers" << endl;
      for (int i = 0; i < maxNums.size(); i++) {
        cout << maxNums.at(i) << " ";
      }
      cout << endl << endl;

      // reset the userAct
      userAct = act();
    }

    else {
      // keep track of how many numbers fit the range
      int cnt = 0;

      // get the range from the user
      cout << "Enter the range you want to search: ";
      cin >> lowerRan >> upperRan;

      // check if the range is valid
      while(lowerRan > upperRan) {

        // reset userAct
        cout << "Invalid range" << endl;
        userAct = act();

        // reset the range
        cout  << "Enter the range you want to search: ";
        cin >> lowerRan >> upperRan;
      }

      cout << "Enter the range of 'length' you are looking for: ";
      cin >> lowerlengRan >> upperlengRan;
      cout << endl << endl;

      while(lowerlengRan > upperlengRan) {

        // reset userAct
        cout << "Invalid range" << endl;
        userAct = act();

        // reset the range
        cout << "Enter the range of 'length' you are looking for: ";
        cin >> lowerlengRan >> upperlengRan;
      }

      // calculate the length for each number in the range
      for (long long int i = lowerRan; i <= upperRan; ++i) {
        long long int currNum = i;
        long long int length = 0;

        while (currNum != 1) {
          length++;
          if (currNum % 2 == 0) {
            currNum /= 2;

          }
          else {
            currNum = currNum * 3 + 1;
          }
        }

        // print the result
        if (length >= lowerlengRan && length <= upperlengRan) {
          cout << i << " ";
          cnt++;
        }
      }

      if (cnt == 0) cout << "There are no such number." << endl;
      else if (cnt == 1) cout << "There is 1 number." << endl;
      else cout << "There are " << cnt << " numbers." <<endl;

      // reset userAct
      userAct = act();
    }
  }
  return 0;
}

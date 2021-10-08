/* *****************************************************************************
 *  Name: Jiwoo Lee
 *  Email: leeji-22@rhodes.edu
 *
 *  Description:  This program simulates the toilet-paper problem.
 *
 *  Written:       26/09/2019
 *  Last updated:  04/10/2019
 *
 *  % g++ -o tp tp.cpp
 *  % ./tp
 *
 **************************************************************************** */
#include <iostream>   // Basic I/O => cin, cout, etc.
#include <cstdlib>    // Other helpful functions => rand(), RANDMAX
#include <ctime>      // Enables use of time() function
#include <cmath>      // for fab() in changeP

using namespace std;

// Returns a uniformly-distributed number in the range [0,1]
double randUniform() {
  double randNum;
  double numer = rand();

  if (numer == 0) {
    randNum = 0;
  }
  else {
    randNum = numer / RAND_MAX;
  }

  return randNum;
}

// Randomly generate the number of squres used each time
int randSqr(int maxSqr, int minSqr) {
  int patronSqr;

  if (maxSqr < minSqr) {
    patronSqr = 1;
  }
  else if (maxSqr > minSqr) {
    patronSqr = rand() % (maxSqr + 1 - minSqr) + minSqr;
  }
  else {
    patronSqr = maxSqr;
  }

  return patronSqr;
}


/* Return the number of squares on the non-empty roll for this simulation
   of the problem */
int singleSim(int N, double p, int maxSqr, int minSqr) {
  int roll1 = N;
  int roll2 = N;

  while (roll1 != 0 && roll2 != 0) {
    int patronSqr = randSqr(maxSqr, minSqr);
    if (roll1 == roll2) {
      roll1 -= patronSqr;
    }
    else {
      double randNum = randUniform();
      /* Assume if patronSqr > roll1 or roll2, it first uses up the roll designated
      according to the randNum AND uses (patronSqr - designated roll) squares
      on the other roll
      */
      if (randNum > p) {
        if (roll1 >= patronSqr) roll1 -= patronSqr;
        else {
          roll2 -= (patronSqr - roll1);
          roll1 = 0;
        }
      }
      else {
        if (roll2 >= patronSqr) roll2 -= patronSqr;
        else {
          roll1 -= (patronSqr - roll2);
          roll2 = 0;
        }
      }
    }
  }
  if (roll1 < roll2) return roll2;
  else return roll1;
}

int main() {
    int N;                // initial number of squares on each roll
    double p;             // probability of a big-chooser
    int sims;             // number of trials for our simulation
    int maxSqr, minSqr;   // max / min number of squares the patrons use
    double avg = 0.00;    // average of remaining squares
    srand(time(0));

    cout << "How many squares on the roll? ";
    cin >> N;
    cout << "Probability of a big-chooser? ";
    cin >> p;
    cout << "How many simulations? ";
    cin >> sims;
    cout << "Maximum number of squares the patrons use? ";
    cin >> maxSqr;
    cout << "Minimum number of squares the patrons use? ";
    cin >> minSqr;

    //if the range is invalid set the number of squares to 1
    if (maxSqr < minSqr) {
      cout << "Invalid Range" << endl;
      cout << "Setting it to 1." << endl;
    }

    for (int i = 0; i < sims; i++) {
      avg += singleSim(N, p, maxSqr, minSqr);
    }

    avg /= sims;
    cout << "Average: " << avg;


    return 0;
  }

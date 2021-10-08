/*******************************************************************************
 *  Name:   Jiwoo Lee
 *  Email:  leeji-22@rhodes.edu
 *
 *  Description: This program models a social network.
 *
 *  Written:       12/02/19
 *  Last updated:  12/04/19
 ******************************************************************************/

#include "network.h"
#include "user.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {

    Network network;
    network.read_friends(argv[1]);

    string userCmd;
    istringstream ss;
    int cmdNum = 0;

      do {
        try {
          cout << "============================Menu===========================" << endl;
          cout << "1) Add a user: Enter \"1 name year zipcode\"" << endl;
          cout << "2) Add friend connection: Enter \"2 name1 name2\"" << endl;
          cout << "3) Remove friend connection: Enter \"3 name1 name2\"" << endl;
          cout << "4) Print users: Enter \"4\"" << endl;
          cout << "5) Print friends: Enter \"5 name\"" << endl;
          cout << "6) Write to file: Enter \"6 file name\"" << endl;
          cout << "7) End the program: Enter any number other than 1~6" << endl;
          cout << "===========================================================" << endl;

          cout << "Enter the command: ";
          getline(cin, userCmd);
          ss.clear();
          ss.str(userCmd);

          cmdNum = 0;
          ss >> cmdNum;

          if (cmdNum == 1) {
            string first, last;
            int year = -1, zip = -1;
            ss >> first >> last >> year >> zip;

            if (ss.bad()) {
              throw runtime_error("Failure getting the input.");
            }
            if (first == "" || last == "") {
              throw runtime_error("Enter both first and last name.");
            }
            if (year == -1) {
              throw runtime_error("Enter year.");
            }
            if (zip == -1) {
              throw runtime_error("Enter zipcode.");
            }

            string name = first + " " + last;

            User newuser(network.get_numusers(), name, year, zip);
            network.add_user(newuser);
          }
          else if (cmdNum == 2) {
            string first1, last1, first2, last2;
            ss >> first1 >> last1 >> first2 >> last2;

            if (ss.bad()) {
              throw runtime_error("Failure getting the input.");
            }
            if (first1 == "" || last1 == "" || first2 == "" || last2 == "") {
              throw runtime_error("Enter both first and last name.");
            }

            string name1 = first1 + " " + last1;
            string name2 = first2 + " " + last2;

            network.add_connection(name1, name2);
          }
          else if (cmdNum == 3) {
            string first1, last1, first2, last2;
            ss >> first1 >> last1 >> first2 >> last2;

            if (ss.bad()) {
              throw runtime_error("Failure getting the input.");
            }
            if (first1 == "" || last1 == "" || first2 == "" || last2 == "") {
              throw runtime_error("Enter both first and last name.");
            }

            string name1 = first1 + " " + last1;
            string name2 = first2 + " " + last2;

            network.remove_connection(name1, name2);
          }
          else if (cmdNum == 4) {
            network.print_users();
          }
          else if (cmdNum == 5) {
            string first, last;
            ss >> first >> last;

            if (ss.bad()) {
              throw runtime_error("Failure getting the input.");
            }
            if (first == "" || last == "") {
              throw runtime_error("Enter both first and last name.");
            }

            string name = first + " " + last;
            network.print_users(name);
          }
          else if (cmdNum == 6) {
            string filename;
            ss >> filename;

            if (ss.bad()) {
              throw runtime_error("Failure getting the input.");
            }
            if (filename == "") {
              throw runtime_error("Enter the new file name.");
            }

            network.write_friends(filename.c_str());
          }
        } catch(runtime_error& excpt) {
              cout << excpt.what() << endl;
        }
      } while (cmdNum >= 1 && cmdNum <= 6);
    }
  else {
    cout << "Please provide a file name." << endl;
  }

  cout << "Exiting the program.";

  return 0;

}

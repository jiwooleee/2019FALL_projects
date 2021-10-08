#include "network.h"

// Constructor
Network::Network() {
  vector <User> userlist;
}

// Initialize the network by reading from the file
int Network::read_friends(const char* filename) {

  // open the file
  ifstream inFS;
  inFS.open(filename);

  if(!inFS.is_open()) {
    throw runtime_error("Unable to open the file.");
  }
  else {
    int listSize, userId, userYear, userZip, friendId;
    string line, userName, first, last;

    inFS >> listSize;

    while (!inFS.eof()) {

      inFS >> userId >> first >> last >> userYear >> userZip;
      userName = first + " " + last;

      // Initialize a new user
      User newuser(userId, userName, userYear, userZip);

      inFS.ignore();
      getline(inFS, line);
      istringstream inFriend(line);

      do {
          inFriend >> friendId;
          newuser.add_friend(friendId);
        } while(inFriend);

      // Add the new user to the network
      this->add_user(newuser);

    }

    // Close the file
    inFS.close();

    return 0;
  }
}

// Writes the network to a file
int Network::write_friends(const char* filename) {

  // Open the file
  ofstream outFS;
  outFS.open(filename);

  if (!outFS.is_open()) {
    throw runtime_error("Unable to write the file.");
  }
  else {
    outFS << userlist.size() << endl;

    // Iterate through userlist
    for (User user : userlist) {
      outFS << user.get_id() << endl;
      outFS << "  " << user.get_name() << endl;
      outFS << "  " << user.get_zip() << endl;
      outFS << "  ";

      std::vector <int> userfriends = user.get_friend();

      for (int id : userfriends) {
        outFS << id << " ";
      }

      outFS << endl;
    }

    // Close the file
    outFS.close();

    return 0;
  }
}

// Add user to userlist
void Network::add_user(User newuser) {

  bool Added = false;

  for (User user : userlist) {
    if (user.get_name() == newuser.get_name() &&
        user.get_year() == newuser.get_year() &&
        user.get_zip() == newuser.get_zip()) {
      Added = true;
    }
  }

  if (!Added) {
    this->userlist.push_back(newuser);
  }
}

// Add name1 to name2 friends and vice versa
int Network::add_connection(const string& name1, const string& name2) {
  User user1, user2;
  int ind1 = -1, ind2 = -1, userid1, userid2;

  if (name1 != name2) {
    // Iterate through userlist & look for name1 and name2
    for (int i = 0; i < userlist.size(); i++) {
      string username = userlist.at(i).get_name();
      if (username == name1) {
        userid1 = userlist.at(i).get_id();
        ind1 = i;
      }
      if (username == name2) {
        userid2 = userlist.at(i).get_id();
        ind2 = i;
      }
    }

    if (ind1 == -1) {
      throw runtime_error("The first user is not in the network.");
    }
    if (ind2 ==-1) {
      throw runtime_error("The second user is not in the network.");
    }

    // Add friend
    userlist.at(ind1).add_friend(userid2);
    userlist.at(ind2).add_friend(userid1);

    return 0;
  }
  else throw runtime_error("You typed in same names.");
}

// Remove name1 from name2 friends and vice versa
int Network::remove_connection(const string& name1, const string& name2) {
  User user1, user2;
  int ind1 = -1, ind2 = -1, userid1, userid2;

  if (name1 != name2) {
    // Iterate through userlist & look for name1 and name2
    for (int i = 0; i < userlist.size(); i++) {
      string username = userlist.at(i).get_name();
      if (username == name1) {
        userid1 = userlist.at(i).get_id();
        ind1 = i;
      }
      if (username == name2) {
        userid2 = userlist.at(i).get_id();
        ind2 = i;
      }
    }

    if (ind1 == -1) {
      throw runtime_error("The first user is not in the network.");
    }
    if (ind2 ==-1) {
      throw runtime_error("The second user is not in the network.");
    }

    // Remove friend
    userlist.at(ind1).delete_friend(userid2);
    userlist.at(ind2).delete_friend(userid1);

    return 0;
  }
  else throw runtime_error("You typed in same names.");
}

// Returns id based on name
int Network::get_id(const std::string& username) const{

  for (User user : userlist) {
    if (user.get_name() == username) {
      return user.get_id();
    }
  }

  return -1;
}

// Returns number of users
int Network::get_numusers() const {
  return userlist.size();
}

void Network::print_users() {

  cout << setw(8) << left << "ID";
  cout << setw(16) << left << "Name";
  cout << setw(9) << left << "Year";
  cout << "Zip" << endl;
  cout << setw(60) << left <<
  "===========================================================" << endl;

  for (User user : userlist) {
    cout << user.get_id() << "." << setw(6) << left << " ";
    cout << setw(16) << left << user.get_name();
    cout << setw(9) << left << user.get_year();
    cout << user.get_zip() << endl;
  }
}

void Network::print_users(const string& username) {

  int userid;

  if (this->get_id(username) != -1) {
    userid = this->get_id(username);
    cout << setw(8) << left << "ID";
    cout << setw(16) << left << "Name";
    cout << setw(9) << left << "Year";
    cout << "Zip" << endl;
    cout << setw(60) << left <<
    "===========================================================" << endl;
  }
  else {
    throw runtime_error("The user is not in the network.");
  }

  for (User user : userlist) {
    vector <int> friendlist = user.get_friend();
    vector <int>::iterator it = find(friendlist.begin(), friendlist.end(), userid);
    if (it != friendlist.end()) {
      cout << user.get_id() << "." << setw(6) << left << " ";
      cout << setw(16) << left << user.get_name();
      cout << setw(9) << left << user.get_year();
      cout << user.get_zip() << endl;
    }
  }

}

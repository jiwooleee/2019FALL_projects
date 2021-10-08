#include "user.h"

// Constructor
User::User(int id, const string& name, int year, int zipcode)
: id(id), name(name), year(year), zipcode(zipcode)
{
  vector <int> friends;
}

// Add friend if the id is not in the vector
void User::add_friend(int id) {
  bool isFriend = false;

  for (int i = 0; i < friends.size(); i++) {
    if (friends.at(i) == id) {
      isFriend = true;
    }
  }

  if (!isFriend) {
    friends.push_back(id);
    return;
  }
}

// Delete friend if the id is in the vector
void User::delete_friend(int id) {
  bool isFriend = false;
  int index = -1;

  for (int i = 0; i < friends.size(); i++) {
    if (friends.at(i) == id) {
      isFriend = true;
      index = i;
    }
  }

  if (isFriend) {
    friends.erase(friends.begin() + index);
    return;
  }
}

// Returns id
int User::get_id() const {
  return id;
}

// Returns zipcode
int User::get_zip() const {
  return zipcode;
}

// Returns year
int User::get_year() const {
  return year;
}

// Returns name
string User::get_name() const {
  return name;
}

// Returns friends
vector <int> User::get_friend() const {
  return friends;
}

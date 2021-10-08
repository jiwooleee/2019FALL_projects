#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
#include <cstring>
#include <stdexcept>

using namespace std;

class User {
 public:
   User(int id = 0, const string& name = "", int year = 0, int zipcode = 0);
   void add_friend(int id);
   void delete_friend(int id);
   int get_id() const;
   string get_name() const;
   int get_year() const;
   int get_zip() const;
   vector <int> get_friend() const;

 private:
   int id;
   string name;
   int year;
   int zipcode;
   vector <int> friends;

};


#endif

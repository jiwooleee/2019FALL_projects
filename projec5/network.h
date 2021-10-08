#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"

class Network : public User {
 public:
  Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(User newuser);
  int add_connection(const string& name1, const string& name2);
  int remove_connection(const string& name1, const string& name2);
  int get_id(const string& username) const;
  int get_numusers() const;
  void print_users();
  void print_users(const string& username);

 private:
   vector <User> userlist;

};


#endif

#ifndef ADMIN_H
#define ADMIN_H

bool cheack_password_f(std::string& password, std::string& second, int start);
std::string cheack_login_f(std::string& login, std::string& password);
void zapis_new(std::string& add_name, std::string& add_secndN, std::string& add_fathland, std::string& id);
int sum_user();
bool check_admin();
bool admin();

#include "admin.cpp"
#endif

#include "perevod.h"

bool cheack_password_f(std::string& password, std::string& second, int start) {
	
	if (second.size() - start != password.size()) return false;

	for (unsigned int i = 0; i < password.size(); ++i) {
		
		if (password[i] != second[start]) return false;
		
		start++;    
	}

	return true;
}

std::string cheack_login_f(std::string& login, std::string& password) {
	int start,end;
	
	std::ifstream input("login.txt");
	if (input.is_open()) {
		std::string second;

		while (getline(input, second)) {

			start = 0;
			start = poisk_probel(start, second);
			int prvt = start;
			end = poisk_probel(start + 1, second);

			if (login.size() == end - start - 1) {

				int count_error = 0;
				for (int n = 0; n < login.size(); ++n) {
					start++;

					if (login[n] != second[start]) {
						count_error++;
						break;
					}
				}

				if (count_error == 0) {
					bool status_password = cheack_password_f(password, second, end + 1);

					if (status_password == true) {
						int size = second.size();
						
						for (int n = 0; n < size - prvt ; ++n) second.erase(second.end() - 1);
						return second;
					}
				}
			}
		}
	}
	input.close();
	return "0";
}



void login_list_f(std::string& id){
	std::string login, password;
	std::cout << "Login and password: " << '\n';

	std::cin >> login >> password;

	std::ofstream zapis("login.txt", std::ios::app);

	if (zapis.is_open()) {
		zapis << id <<" "<<  login  << " " << password << '\n';
	}
	zapis.close();
}

int sum_user_f() {
	int user_sem = 0;

	std::ifstream input("login.txt");
	if (input.is_open()) {
		std::string second;

		while (getline(input, second)) {
			++user_sem;
		}
	}
	input.close();

	return user_sem;
}

void zapis_new(std::string& add_name, std::string& add_secndN, std::string& add_fathland, std::string& id) {
	std::ofstream zapis("users.txt", std::ios::app);

	if (zapis.is_open()) {
		zapis <<  id  << " " <<add_name << " " << add_secndN << " " << add_fathland <<'\n';
	}
	zapis.close();
}

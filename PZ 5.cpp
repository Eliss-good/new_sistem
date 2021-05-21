#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cctype>

#include "admin.h"
#include "history.h"
#include "perevod.h"


int real_sum_user;
std::string status_user = "0";
struct spisok_struct* glav_p;

struct spisok_struct {
    std::string NAME = "";
	std::string Second_Name = "";
	std::string Fatherland = "";
	std::string id = "";

	struct spisok_struct* next = NULL;
};

// Функция считывает файл, который содержит в себе данные пользователей. После завершения программы данные пользователей не стираются, а записываются в файл.
// Данные с файла подгружаются после завершения программы
void start_add_f() {
	int start, end;
    std::ifstream input("users.txt");

	if (input.is_open()) {
	    std::string second = "";

		while (getline(input, second)) {
			spisok_struct* new_person_card;
			new_person_card = new spisok_struct;

			start = 0;
			start = poisk_probel(start, second);

			for (int n = 0; n < start; ++n) new_person_card->id.insert(n, 1, second[n]);

			end = poisk_probel(start + 1, second);
			for (int n = start + 1; n < end; ++n) new_person_card->NAME.insert(n - start - 1, 1, second[n]);

			start = end;
			end = poisk_probel(start + 1, second);
            for (int n = start + 1; n < end; ++n) new_person_card->Second_Name.insert(n - start - 1, 1, second[n]);

			start = end;
			for (int n = start + 1; n < second.size(); ++n) new_person_card->Fatherland.insert(n - start - 1, 1, second[n]);

			if (glav_p == NULL) {
				glav_p = new_person_card;
			}
			else {
				spisok_struct* cur = glav_p;
				while (cur->next != NULL) {
					cur = cur->next;
				}

				cur->next = new_person_card;
			}
			
		}
	}
	input.close();

}

void add_f(std::string& add_name, std::string& add_secndN, std::string& add_fathland) {
	static int i = sum_user_f() - 1;
	++i;

	spisok_struct *new_person_card;
	new_person_card = new spisok_struct;
    new_person_card -> NAME = add_name;
	new_person_card -> Second_Name = add_secndN;
	new_person_card -> Fatherland = add_fathland;
	new_person_card -> id = perevod(i);
	
	zapis_new(add_name, add_secndN, add_fathland, new_person_card->id);
	login_list_f(new_person_card->id);
	
	if (status_user != "SU") status_user = new_person_card->id;
	if (glav_p == NULL) glav_p = new_person_card;

	else {
		spisok_struct* cur = glav_p;
		while (cur->next != NULL) {
			cur = cur->next;
		}

		cur->next = new_person_card;
	}
	
}

void see_f() {

	int i = 0;
	spisok_struct* cur = glav_p;
	while (cur != NULL) {
		i++;
		std::cout << '\t' << i <<". " <<cur -> NAME << " " <<cur -> Second_Name << " "<< cur ->Fatherland  <<'\n';
		if (status_user == "SU")  std::cout << '\t' <<"id user: "<< cur->id << '\n';
		cur = cur->next;	
	}
}

void del_f(int n) {

	spisok_struct* cur = glav_p;

	for (int i = 0; i < n - 1; ++i) {
		
		if (cur != NULL) cur = cur ->next;
	}


	if (cur != NULL && n > 0) {
		spisok_struct* buf = cur -> next;
		cur->next = buf -> next;

		delete  buf;
	}
	else if (n == 0) {
		spisok_struct* buf = glav_p;
		glav_p = cur->next;

		delete buf;
	}

}

void change_user_f(std::string& vibor) {
	spisok_struct* cur = glav_p;

	while (cur->next != NULL) {
		if (cur->id != status_user) cur = cur->next;
	}

	std::string newAtribut;
	std::cin >> newAtribut;
	if (vibor == "surname") cur->Second_Name = newAtribut;

	if(vibor == "name") cur->NAME = newAtribut;

	if(vibor == "fhatherland") cur->Fatherland = newAtribut;
	
	log(newAtribut);
}


void change_admin_f(std::string& vibor) {
	spisok_struct* cur = glav_p;

	std::string poisk_new;
	if (vibor == "surname") {
		std::cin >> poisk_new;
		
		while (cur != NULL) {
			
			if (cur -> Second_Name == poisk_new) {
				std::cin >> poisk_new;
				cur -> Second_Name = poisk_new;

				return;
			}
			cur = cur->next;
		}
	}
	else if (vibor == "name") {
		std::cin >> poisk_new;
		while (cur != NULL) {

			if (cur -> NAME == poisk_new) {
				std::cin >> poisk_new;
				cur -> NAME = poisk_new;

				return;
			}
			cur = cur->next;
		}
	} 
	else if (vibor == "fhatherland") {
		std::cin >> poisk_new;
		while (cur != NULL) {

			if (cur->Fatherland == poisk_new) {
				std::cin >> poisk_new;
				cur->Fatherland = poisk_new;

				return;
			}
			cur = cur->next;
		}

	}
	
	log(poisk_new);

	std::cout << '\t' <<"No have this " << vibor << '\n';
}

void rand_f() {
	
    std::cout << '\t' << "Please enter the line size ";
	int n;
	std::cin >> n;

	std::string stroka = perevod(n);
	log(stroka);
	std::string add_name , add_secndN , add_fathland;

	for (int i = 0; i < n ; ++i) {
		add_name.push_back(rand() % 26 + 97);
		add_secndN.push_back(rand() % 26 + 97);
		add_fathland.push_back(rand() % 26 + 97);
		}

	std::cout << '\n' << '\t' << add_name << " " << add_secndN  << " "<< add_fathland << '\n';
	//Sleep(1500);
	add_f(add_name, add_secndN, add_fathland);
}

void command_f(std::string command) {
	if (command == "add") {
		std::string add_name, add_secndN, add_fathland;
		std::cin >> add_name >> add_secndN >> add_fathland;
		log(add_name);
		log(add_secndN);
		log(add_fathland);
		add_f(add_name, add_secndN, add_fathland);

	} else if (command == "see") {
		see_f();
	} else if (command == "del") {
		int n;
		std::cin >> n;

		std::string stroka = perevod(n);
		log(stroka);
		del_f(n-1);
    } else if (command == "rand" && status_user == "SU") {
		rand_f();
	} else if (command == "stop") {
		exit(0);
	} else if (command == "help") {
		std::cout << "Ну вы там разбиритесь и составте help" << std::endl;

		Sleep(7000);
	} else if (command == "change") {
		std::cout << '\t' << "name | secondname | fatherland?" << '\n';
		
		std::string vibor;
		std::cin >> vibor;
		log(vibor);

		str_tolower(vibor);
		if (status_user == "SU") {
			change_admin_f(vibor);
		}
		else {
			change_user_f(vibor);
		}
	} else if (command == "history") {
		history_f();
	}
} 

void vhod_account_f() {

	std::string login, password;
	std::cout << "Для входа в аккаунт введите совои данные" << '\n'
		<< "Если у вас нет аккаунта введите new new" << '\n'
		<< "login and password: ";

	std::cin >> login >> password;
	status_user = cheack_login_f(login, password);

	if (login == "new" && password == "new") {
		std::cout << "Введите ФИО" << '\t';
		command_f("add");
	}

	if (status_user != "0") std::cout << "Ты вошёл в систему" << '\n';
}


int main() {
	start_add_f(); // Подгрузка пользователей из файла
	setlocale(LC_ALL, "Russian");
	vhod_account_f();

	std::string command;
	std::cout << '\n' <<"E/G" << "   ADD | CHANGE | SEE | DEL | RAND | HELP | STOP " << std::endl;
	while (true) {
		std::cout << '\n' <<"Введите что-то: ";

		std::cin >> command;
		str_tolower(command);
		log(command);

		if (status_user != "0") {
			str_tolower(command);
			command_f(command);
		}
		else {
			vhod_account_f();
		}
	}

	return 0;
}

/* NEXT UPDATE
*  1. Подгрузка аккаунтов из файла **DONE** 
*  2. Связать login and users 
*  3. Разделить уровень доступа для обычного юзера и админа
*   а) Пользователь может удалить только свой аккаунт 
*   б) Пользователь может изменить только свои данные
*   в) Сделать рейтинг для приаязать этот код к игре жизнь, бкдет выступать в роле рейтинга
* 
*Если админ, то может удалять любого по id при этом должно происходить удаление из файлов
*Еслм обычный юзер,то происходит только его аккаунта
*При этом достаточно только одной общей функции удаления, в которую приходит id
*/

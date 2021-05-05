void log(std::string& new_command) {
	std::ofstream zapis("data.txt", std::ios::app);

	if (zapis.is_open()) {
		zapis << new_command << '\n';
	}
	zapis.close();

}

void history_f() {
	std::ifstream input("data.txt");
	if (input.is_open()) {
		std::string second;

		while (getline(input, second)) {
			std::cout << second ;
		}
	}
	input.close();
}
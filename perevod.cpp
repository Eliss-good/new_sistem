
int poisk_probel(int start, std::string& stroka) {

	while (start < stroka.size()) {
		if (stroka[start] == ' ') break;
		start++;
	}

	return start;
}

void str_tolower(std::string& stroka) {
	for (int i = 0; i < stroka.size(); ++i)
		stroka[i] = tolower(stroka[i]);
}

std::string perevod(int input_num) {

	std::string stroka = "";

	int digit;
	char chislo;

	while (input_num > 0)
	{
		digit = input_num % 10;

		input_num = input_num / 10;
		chislo = '0' + digit;

		stroka.append(1, chislo);

	}


	for (int i = 0; i < stroka.size() / 2; ++i) {
		chislo = stroka[i];
		stroka[i] = stroka[stroka.size() - i - 1];
		stroka[stroka.size() - i - 1] = chislo;
	}

	return stroka;
}
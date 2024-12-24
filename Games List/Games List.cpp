#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

class Games {
	std::string name;
	float rating;
public:
	Games() :name{ "Unknown" }, rating{} {};
	Games(std::string name, float rating) :name{ name }, rating{ rating } {}
	friend bool operator<(const Games& lhs, const Games& rhs) {
		return lhs.name > rhs.name;
	}
	bool operator==(const Games& obj) {
		return (this->name == obj.name && this->rating == obj.rating);
	}
	bool operator<(const Games& obj) {
		return this->rating < obj.rating;
	}
	friend std::ostream& operator<<(std::ostream& os, Games& obj) {
		os << obj.name << ": (" << obj.rating << "/10)";
		return os;
	}
};

template<typename T>
void displayQ(std::priority_queue<T> s) {
	static int gameNumber;
	while (!s.empty()) {
		gameNumber++;
		T element = s.top();
		s.pop();
		std::cout << gameNumber << "- " << element << std::endl;
	}
}

void printGames();
void addGames();

int main()
{
	std::cout << "Welcome to the application" << std::endl;
	bool done{ false };
	char choice{};
	do {
		std::cout << "1- Add Games\n2- Print Games\n3- QUIT" << std::endl;
		std::cout << "Enter your choice:" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case '1':
			addGames();
			std::cout << std::endl;
			break;
		case '2':
			printGames();
			std::cout << std::endl;
			break;
		case '3':
			done = true;
			break;
		default:
			std::cerr << "Error! invalid choice.\n" << std::endl;
			continue;
		}
	} while (done == false); {
		std::cout << "\nThanks for using the app" << std::endl;
	}
}

void printGames() {
	std::string gameName{};
	std::string entry{};
	float rating{};
	std::fstream inFile;
	std::priority_queue<Games> pq;
	inFile.open("Games.txt");

	if (!inFile.is_open()) {
		std::cerr << "Error" << std::endl;
	}
	else {
		while (std::getline(inFile, gameName) && std::getline(inFile, entry)) {
			std::istringstream validator{ entry };
			if (validator >> rating)
				pq.emplace(gameName, rating);
			else
				std::cerr << "Error, couldn't add: " << gameName << std::endl;
		}
		displayQ(pq);
	}
	inFile.close();
}

void addGames() {
	std::fstream onFile{ "Games.txt",std::ios::app };
	std::string gameName{};
	float rating{};
	if (!onFile.is_open()) {
		std::cerr << "Error" << std::endl;
	}
	else {
		std::cout << "\nEnter the game name:" << std::endl;
		std::cin >> std::ws;
		std::getline(std::cin, gameName);
		std::cout << "Enter the rating:" << std::endl;
		std::cin >> rating;
		if (std::cin.good()) {
			onFile << "\n" << gameName << std::endl;
			onFile << rating;
		}
		else if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "You didnt enter a number" << std::endl;
		}
	}
	onFile.close();
}
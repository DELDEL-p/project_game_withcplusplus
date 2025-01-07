#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

class Roulette  {
private:
    string color;
public:
    Roulette() {
        srand(time(NULL));
        int number = rand() % 15;
        if (number == 0) {
            color = "green";
        } else if (number >= 1 && number <= 7) {
            color = "orange";
        } else {
            color = "black";
        }
    }
    string getColor() {
        return color;
    }
    bool operator==(const Roulette& other) const {
        return this->color == other.color;
    }

    bool operator!=(const Roulette& other) const {
        return this->color != other.color;
    }

};

class Player : public Roulette {
private:
    int money;
public:
    Player(int m) {
        money = m;
    }
    void addMoney(int m);
    void subtractMoney(int m);
    int getMoney() {
        return money;
    }

    Player operator+(const int& m) {
        Player p(*this);
        p.money += m;
        return p;
    }
};

void Player::addMoney(int m){
    money +=m;
};

void Player::subtractMoney(int m){
    money -=m;
};


class Bet : public Roulette{
private:
    string color;
    int amount;
public:
    Bet(string c, int a) {
        color = c;
        amount = a;
    }
    string getColor() {
        return color;
    }
    int getAmount() {
        return amount;
    }

    Bet operator+(const Bet& other) {
        string newColor = (color == other.color) ? color : "unknown";
        int newAmount = amount + other.amount;
        return Bet(newColor, newAmount);
    }
};

int main() {
    int startingMoney = 0;
    string color;
    int amount;
    char choice;
    

    std::cout << " ______     ______     ______     ______     ______     __    __     ______  " << std::endl;
    std::cout << "/\\  ___\\   /\\  ___\\   /\\  ___\\   /\\  __ \\   /\\  ___\\   /\\ \"-.\\  \\   /\\  == \\ " << std::endl;
    std::cout << "\\ \\ \\____  \\ \\___  \\  \\ \\ \\__ \\  \\ \\ \\/\\ \\  \\ \\  __\\   \\ \\ \\-./\\ \\  \\ \\  _-\\ " << std::endl;
    std::cout << " \\ \\_____\\  \\/\\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_\\   " << std::endl;
    std::cout << "  \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_____/   \\/_/  \\/_/   \\/_/   " << std::endl;
    cout << "###########################################################################" <<endl;


   
    while(startingMoney==0){
        cout << "\n\n\033[31mEnter your starting amount of money: \033[0m" ;
        cin >> startingMoney;
        if (startingMoney <= 0) {
            cout << "➤  You have no Money " << endl;
            cout << "!!!You cannot play!!! " << endl;
            }
            
        }
        
        Player player(startingMoney);
        cout <<"➤  You have " << player.getMoney() << " Baht." << endl;
        
    ofstream outFile("roulette.txt");

    bool continuePlaying = true;
    

    while (player.getMoney() > 0 && continuePlaying) {
    string color;
    bool validColor = false;

    do {
       cout << "\033[31mEnter your bet color \033[0m (\033[38;5;208morange\033[0m, \033[38;5;0mblack\033[0m, or \33[38;5;46mgreen\033[0m) \033[31m:\033[0m ";
       cin >> color;
       transform(color.begin(), color.end(), color.begin(), [](unsigned char c){ return tolower(c); });

       if (color == "orange" || color == "black" || color == "green") {
          validColor = true;
        } else {
        cout << "Invalid color entered. Please enter either \033[38;5;208morange\033[0m, \033[38;5;0mblack\033[0m, or \33[38;5;46mgreen\033[0m" << endl;
    }
}   while (!validColor); 
      
    bool validInput = false;   
    while (!validInput) {
        cout << "\033[31mEnter your bet amount:\033[0m ";
        string input;
        cin >> input;
        
        validInput = true;
            for (int i = 0; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                    validInput = false;
                    break;
            }
        }
        if (validInput) {
                amount = stoi(input);
            } else {
                cout << "Invalid input. Please enter a valid number." << endl;
            }
        }
        Bet bet(color, amount);

        Roulette roulette;
        string rouletteColor = roulette.getColor();
        cout << "\n↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓" << endl;
        cout << "➤  The roulette color is  \033[38;5;";
        if (rouletteColor == "orange") {
            cout << "208morange";
        } else if (rouletteColor == "black") {
            cout << "0mblack";
        } else { 
            cout << "46mgreen";
        }
        cout << "\033[0m" << endl;

        if (rouletteColor == "green" && bet.getColor() == "green") {
            cout << "➤  You  \033[4mwin\033[0m  double your bet amount!" << endl;
            player.addMoney(bet.getAmount() * 10);
            player.subtractMoney(amount); 
        } else if (rouletteColor == "orange" && bet.getColor() == "orange") {
            cout << "➤  You  \033[4mwin\033[0m  double your bet amount!" << endl;
            player.addMoney(bet.getAmount() * 2);
            player.subtractMoney(amount); 
        } else if (rouletteColor == "black" && bet.getColor() == "black") {
            cout << "➤  You  \033[4mwin\033[0m  double your bet amount!" << endl;
            player.addMoney(bet.getAmount() * 2);
            player.subtractMoney(amount); 
        } else {
            cout << "➤  You \033[4mlose\033[0m your bet amount." << endl;
            player.subtractMoney(bet.getAmount());
        }

        cout << "➤  You have " << player.getMoney() << " Baht." << endl;
        outFile << bet.getColor() << " " << bet.getAmount() << " " << rouletteColor << endl;

        
        
        while (true) {
        cout << "\033[35mY = continue | N = Withdraw : \033[0m";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            continuePlaying = true;
        break;
        } else if (choice == 'n' || choice == 'N') {
             continuePlaying = false;
        break;
    } else {
        cout << "Invalid input. Please enter 'y' or 'Y' to continue." << endl;
        cout << "Invalid input. Please enter 'n' or 'N' to withdraw." << endl;
    }
  }

    if (player.getMoney() <= 0) {
       cout << "➤  You have no Money " << endl;
}

    }

    outFile.close();

    ifstream inFile("roulette.txt");

    if (inFile.is_open()) {
        string color;
        int amount;
        string rouletteColor;
        while (inFile >> color >> amount >> rouletteColor) {
            
        }
        inFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
    if (player.getMoney() > 0){
            cout << "➤  You withdraw : " << player.getMoney() << " Baht." << endl;
        
    }
    
    
    return 0;
}
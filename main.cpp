#include<iostream>
#include<cstdlib>
#include<string>
#include<regex>
#include<fstream>
using namespace std;

void exit();
void banner();
int askUser();
void signup();
void login();
void checknumber(string number);
bool checkFile(string file);


#ifdef _WIN32 
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif


void banner() {
    system(CLEAR_COMMAND);
    cout << " ___________________________________" << endl;
    cout << "|                                   |" << endl;
    cout << "|        TUI-BANKING SYSTEM         |" << endl;
    cout << "|___________________________________|" << endl;
}

int askUser() {
    banner();
    int temp = 0;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. exit" << endl;
    cout << "Please enter your choice : ";
    std::cin >> temp;
    return temp;
}



bool continueLogin = false;
void login() {
    banner();
    continueLogin = false;
    string usernumber;
    cout << "Please enter you phone number : ";
    std::cin >> usernumber;
    checknumber(usernumber);
    if(continueLogin) {
        string firstname;
        string lastname;
        string email;
        string password;
        string enteredpassword;
        long int balance;
        string filename;
        cout << "Enter your first name: ";
        std::cin >> firstname;
        cout << "Enter your last name: ";
        std::cin >> lastname;
        filename = firstname + " " + lastname+" "+usernumber+ ".txt";
        if(checkFile(filename)) {
            ifstream user(filename);
            getline(user, firstname);
            getline(user, lastname);
            getline(user, usernumber);
            getline(user, email);
            getline(user, password);
            user>>balance;
            cout <<"Enter your password: ";
            std::cin >> enteredpassword;
            if(enteredpassword == password){
                int choice = -1;
                do{
                banner();
                cout << "Welcome " << firstname << " " << lastname << "!" << endl;
                cout << "1. Check Balance "<<endl;
                cout << "2. Withdraw money " <<endl;
                cout << "3. Transfer money " <<endl;
                cout << "4. exit " <<endl;
                cout << "Please enter your choice : ";
                string choice;
                std::cin >> choice;
                }
                while(choice<=0 || choice>=5);
                switch (choice)
                {
                case 1:
                    cout << "Your balance is : "<<balance;
                    break;
                
                case 2:
                    banner();
                    int currentBalance = balance;
                    cout << "Enter the withdraw amount : ";
                    int amount;
                    cin >> amount;
                    if(amount > currentBalance) {
                        cout <<"Insufficient funds."<<endl;
                    }
                    else{
                        currentBalance -= amount;
                        cout << "Balance: " << currentBalance;
                    }
                }
        }
            else{
                cout <<"Password mismatch. "<< endl;
            }
    }
    else{
        cout<<"Username mismatch. "<<endl;
    }
    }
    else{
        cout << "Provided phone number is not registered." << endl;
    }
     cout << "do you want to retry?(y/n): ";
    char choice;
    std::cin >> choice;
    if(choice == 'y'||choice == 'Y'){
        login();
    }
    else{
        exit();
    }
    return;
}



bool continueSignup = true;
void signup(){
    banner();
    string phonenumber;
    do {
        cout << "Enter your phone number: ";
        std::cin >> phonenumber;
        if (phonenumber.length() != 10) {
            cout << "Please enter a valid number." << endl;
        }
    } while (phonenumber.length() < 8);
    checknumber(phonenumber);
    if(continueSignup) {
        cout << "Enter your first name : ";
        string firstname;
        std::cin >> firstname;

        cout << "Enter your last name : ";
        string lastname;
        std::cin >> lastname;

        string password;
        do {
            cout << "Create a password : ";
            std::cin >> password;
            if (password.length() < 8) {
                cout << "Password must be at least 8 characters long." << endl;
            }
        } while (password.length() < 8);

        string confirmPassword;
        do{
        cout << "Confirm password : ";
        std::cin >> confirmPassword;
        if (password!= confirmPassword) {
            cout << "Passwords do not match." << endl;
        }
        }while (password != confirmPassword);
    
        string email;
        regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        do {
            cout << "Enter your email address : ";
            std::cin >> email;
        
            if ( !regex_match(email, pattern)) {
                cout << "Please enter a valid email." << endl;
            }
        } while (!regex_match(email, pattern));

        ofstream users;
        users.open("registeredUsers.txt", ios::app);
        users  <<phonenumber<< endl;
        users.close();
        
        string user = firstname + " " + lastname+ " "+phonenumber+".txt";
        ofstream account;
        account.open(user, ios::app);
        account << firstname<<endl;
        account << lastname<<endl;
        account<<phonenumber <<endl;
        account<< email<<endl;
        account<<password <<endl;
        long int balance = 0;
        account<<balance<<endl;
        account.close();
        cout <<"Account created successfully."<<endl;
    }
    else{
         cout << "Account already exists." << endl;
    }
    cout << "do you want to login?(y/n): ";
    char choice;
    std::cin >> choice;
    if(choice == 'y'||choice == 'Y'){
        login();
    }
    else{
        exit();
    }
    return;
}
bool stop = false;
void exit(){
    banner();
    cout << "Thank you for using our service." << endl;
    stop = true;
    return;
}


void checknumber(string number){
    ifstream user("registeredUsers.txt");
   string registerNumber;

    if (!user.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    while (getline(user, registerNumber)) {
        if (registerNumber == number) {
            continueLogin = true;
            continueSignup = false;
            break;
        }
    }
}

bool checkFile(string filename){
    ifstream file(filename);
    return file.good();
}
int main() {
    do{
    int userInput;
    do{
        userInput = askUser();
    }while (userInput <= 0 || userInput >= 4);


    switch (userInput) {
    case 1:
        login();
        break;
    case 2:
        signup();
        break;
    case 3:
        exit();
        break;
    default:
        cout << "Invalid choice" << endl;
    }
    }while(stop==false);
    return 0;
}

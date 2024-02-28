#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<limits>
using namespace std;

class User{
    string userName;
    int password;
    public:
    User(string data, int pass){
        userName = data;
        password = pass;
    }
    string getUserName()const{
        return userName;
    }
    int getPassword()const{
        return password;
    }
};

bool isUsernameExist(string name) {
    ifstream userFile("Userdetail.txt");
    if (userFile.is_open()) {
        string storedName;
        int storedPass;
        while (userFile >> storedName >> storedPass) {
            if (name == storedName) {
                userFile.close();
                return true;
            }
        }
        userFile.close();
    }
    return false;
}

bool isLogin(string name, int pass){
    ifstream userFile;
    userFile.open("Userdetail.txt",ios::in); //open a file to perform read operation using file object
    if(userFile.is_open()){
        string line;
        while(getline(userFile, line)){
            string storedName;
            int storedPass;
            stringstream ss(line);
            if(ss >> storedName >> storedPass){
                if(name == storedName && pass == storedPass){
                    userFile.close();
                    return true;
                }
            }
        }
        userFile.close();
    }
    return false;
}

bool registerUser(const User& user){
    //create and open file
    ofstream userFile;
    userFile.open("Userdetail.txt", ios::app);
    if (!userFile.is_open()) {
        cout << "Error: registration failed!" << endl;
        return false;
    }
    if (isUsernameExist(user.getUserName())){
        cout<<"Same Username exist please change username!"<<endl;
        return false;
    }   
    else{
        userFile<<user.getUserName()<<" "<<user.getPassword()<<endl;
        cout<<"\t\t Registration Successful."<<endl;
    }
    return true;
    // Close file
    userFile.close();
}

bool hasGap(const std::string& str) {
    for (char ch : str) {
        if (isspace(ch)) {
            return true; // If a whitespace character is found, return true
        }
    }
    return false; // No whitespace characters found, return false
}

int main() {
    int choice;
    string name;
    int password;
    bool check=false;
    cout << "\t\t 1. LOGIN" << endl;
    cout << "\t\t 2. REGISTER" << endl;
    cout << "\t\t  ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
        case 1:
            system("cls");
            cout << "\t\t  -----------LOGIN-----------" << endl;
            cout << "\t\t Case Sensitive fill carefully! (spaces are not allowed)\n" << endl;
            cout << "\t\t UserName : ";
            getline(cin, name);
            if(hasGap(name)){
                cout<<"Invalid Username!"<<endl;
                int x;
                cout<<"Enter 1 to try again ";
                cin>>x;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                if(x==1){
                    system("cls");
                    main();
                }
                else{
                    break;
                }
            }
            else{
                cout << "\t\t Password : ";
                cin >> password;
                if (isLogin(name, password)) {
                    cout << "Login Successful!" << endl;
                } else {
                    cout << "Login failed. Incorrect username or password." << endl;
                    int x;
                    cout<<"Enter 1 to try again ";
                    cin>>x;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    if(x==1){
                        system("cls");
                        main();
                    }
                    else{
                        cin.ignore(); 
                        cin.get();
                        break;
                    }
                }
            }
            break;

        case 2:
            system("cls");
            cout << "\t\t  ---------Register----------" << endl;
            cout << "\t\t Case Sensitive fill carefully!\n" << endl;
            cout << "\t\t UserName : ";
            getline(cin, name);
            if(hasGap(name)){
                cout<<"Invalid Username spaces are not allowed!"<<endl;
                int x;
                cout<<"Enter 1 to try again ";
                cin>>x;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                if(x==1){
                    system("cls");
                    main();
                }
                else{
                    break;
                }
            }
            else{
                cout << "\t\t Password : ";
                cin >> password;
                User newUser(name, password);
                check = registerUser(newUser);
                if(!check){
                    int x;
                    cout<<"Enter 1 to register ";
                    cin>>x;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    if(x==1){
                        system("cls");
                        main();
                    }
                    else{
                        break;
                    }
                }
            }
            break;

        default:
            cout << "Invalid choice." << endl;
            break;
    }

    return 0;
}
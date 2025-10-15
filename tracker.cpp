#include <iostream>  
#include <fstream>  
#include <string>   
#include <sstream> 
#include <cctype>   
#include <numeric>  
#include <limits>   
#include <vector>  

using namespace std;  

void menu() {
    for (int i = 0; i < 25; i++) {
        cout << "-";  
    }
    cout << endl;  
    cout << "This is an expense tracker, you have the following choices:\n";  
    cout << "Välj A: You will add an expense and its cost\n";  
    cout << "Välj S: You will see your list of items and their cost\n";  
    cout << "Välj R: You will remove an item from your list\n";  
    cout << "Välj T: You will see the total cost\n";  
    cout << "Välj E: You will exit from the program\n"; 
    for (int i = 0; i < 25; i++) {
        cout << "-";  
    }
    cout << endl; 
}

int main() {
    menu();  

    vector<string> list_1;  
    vector<int> list_2;    

  
    ifstream infile("tracker.txt");  
    if (infile.is_open()) { 
        string line; 
        while (getline(infile, line)) {  
            stringstream ss(line);  
            string item, costStr;  
            if (getline(ss, item, ',') && getline(ss, costStr)) { 
                list_1.push_back(item);  
                list_2.push_back(stoi(costStr));  
            }
        }
        infile.close();  
    } else {
        cout << "No existing file found. Starting with an empty list.\n";  
    }

    char choices;  

    while (true) {  
        cout << "Pick a letter between A, S, R, T, E: \n"; 
        cin >> choices;  
        choices = tolower(choices);  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (choices == 'e') { 
            break; 
        }

        if (choices == 'a') { 
            string add;  
            cout << "Add something to the list and its cost: \n"; 
            getline(cin, add);  

            stringstream ss(add);  
            string item, costStr;  
            getline(ss, item, ','); 
            getline(ss, costStr);  

            list_1.push_back(item);  
            list_2.push_back(stoi(costStr));  


            ofstream outfile("tracker.txt", ios::app);  
            if (outfile.is_open()) {  
                outfile << item << "," << costStr << "\n";  
                outfile.close(); 
                cout << "Item added successfully.\n";  
            } else {
                cout << "Error: Could not open file to add item.\n";  
            }
        } else if (choices == 's') {  
            cout << "Here is the list of items and their cost: \n"; 
            if (list_1.empty()) {  
                cout << "Your list is empty.\n";  
            } else {
                for (size_t i = 0; i < list_1.size(); i++) { 
                    cout << list_1[i] << " - " << list_2[i] << " kr\n";  
                }
            }
        } else if (choices == 'r') { 
            if (list_1.empty()) {  
                cout << "Your list is empty, nothing to remove.\n";  
                continue;  
            }

            string remove;
            cout << "Write the item and its cost to remove: \n";  // 
            getline(cin, remove);  

            stringstream ss(remove);  
            string item, costStr;  
            getline(ss, item, ',');  
            getline(ss, costStr); 
            int r_cost = stoi(costStr);  

            for (size_t i = 0; i < list_1.size(); i++) { 
                if (list_1[i] == item && list_2[i] == r_cost) {  
                    list_1.erase(list_1.begin() + i);  
                    list_2.erase(list_2.begin() + i);  
                    i--;  
                }
            }

            
            ofstream outfile("tracker.txt");  
            if (outfile.is_open()) {
                for (size_t i = 0; i < list_1.size(); i++) {  
                    outfile << list_1[i] << "," << list_2[i] << "\n";  
                }
                outfile.close();  
                cout << "Item removed successfully.\n";  // 
            } else {
                cout << "Error: Could not open file to update.\n";  
            }
        } else if (choices == 't') {  
            if (list_2.empty()) {  
                cout << "Your list is empty, total cost is 0.\n";  // 
            } else {
                int total_cost = accumulate(list_2.begin(), list_2.end(), 0);  
                cout << "Total cost: " << total_cost << " kr\n";  
            }
        } else {
            cout << "Invalid choice, please try again.\n";  
        }
    }

    cout << "Exiting the program. Goodbye!\n"; 
    return 0; 
}

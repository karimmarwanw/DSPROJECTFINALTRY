#include <iostream>
#include "Functions.h"

int main() {
    // Suppose we allow a maximum of 10 users
    Functions app(10);

    while (true) {
        std::cout << "\n---- MAIN MENU ----\n"
                  << "1. Sign Up\n"
                  << "2. Sign In\n"
                  << "3. Add Friend (Immediate)\n"
                  << "4. Remove Friend\n"
                  << "5. Send Request\n"
                  << "6. Accept Friend\n"
                  << "7. Reject Friend\n"
                  << "8. View Friends\n"
                  << "9. Recommend Friends\n"
                  << "10. Sign Out\n"
                  << "0. Exit\n"
                  << "Enter choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                app.signUp();
            break;
            case 2:
                app.signIn();
            break;
            case 3:
                app.addFriend();
            break;
            case 4:
                app.removeFriend();
            break;
            case 5:
                app.sendRequest();
            break;
            case 6:
                app.acceptFriend();
            break;
            case 7:
                app.rejectFriend();
            break;
            case 8:
                app.viewFriends();
            break;
            case 9:
                app.recommendFriends();
            break;
            case 10:
                app.signOut();
            break;
            case 0:
                std::cout << "Exiting...\n";
            return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}

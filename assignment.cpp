/*
 * Clock App
 *
 *  Date: 1/26/2025
 *  Author: Johnny Chen
 */

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Function to display the clocks
void displayClocks(int hour12, int minute, int second, int hour24) {
    cout << "\n*******************************************************************************" << endl;
    cout << "*                                    Clocks                                   *" << endl;
    cout << "*******************************************************************************" << endl;

    cout << "\n**************************************  ***************************************\n"
        << "*      "
        << "12-Hour Clock: " << setw(2) << setfill('0') << hour12 << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second
        << (hour24 < 12 ? " AM" : " PM")
        << "    *"
        << "  "
        << "*    "
        << "24-Hour Clock: " << setw(2) << setfill('0') << hour24 << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second << "          *" << endl
        << "**************************************  ***************************************" << endl;
}

// Function to add an hour
void addHour(int& hour12, int& hour24) {
    // Increment the 24-hour clock hour by 1, resetting to 0 if it reaches 24
    hour24 = (hour24 + 1) % 24;
    // Update the 12-hour clock hour, resetting to 12 if the hour is 0
    hour12 = (hour24 % 12 == 0) ? 12 : hour24 % 12;
}

// Function to add a minute
void addMinute(int& minute, int& hour12, int& hour24) {
    // Increment the minute by 1, resetting to 0 if it reaches 60
    minute = (minute + 1) % 60;
    // If minutes reset to 0, increment the hour
    if (minute == 0) {
        addHour(hour12, hour24);
    }
}

// Function to add a second
void addSecond(int& second, int& minute, int& hour12, int& hour24) {
    // Increment the second by 1, resetting to 0 if it reaches 60
    second = (second + 1) % 60;
    // If seconds reset to 0, increment the minute
    if (second == 0) {
        addMinute(minute, hour12, hour24);
    }
}

int main() {
    // Get the current system time
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    // Initialize time variables
    int hour24 = localTime.tm_hour; // Get the current hour in 24-hour format
    int hour12 = (hour24 % 12 == 0) ? 12 : hour24 % 12; // Convert to 12-hour format
    int minute = localTime.tm_min; // Get the current minute
    int second = localTime.tm_sec; // Get the current second

    while (true) {
        // Display the clocks
        displayClocks(hour12, minute, second, hour24);

        // Display the menu
        cout << "\nMenu:" << endl;
        cout << "1. Add One Hour" << endl;
        cout << "2. Add One Minute" << endl;
        cout << "3. Add One Second" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue; // Restart the loop
        }

        switch (choice) {
            case 1:
                addHour(hour12, hour24);
                break;
            case 2:
                addMinute(minute, hour12, hour24);
                break;
            case 3:
                addSecond(second, minute, hour12, hour24);
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

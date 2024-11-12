#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

struct Device {
    string name;
    bool isOn;
};

struct LogEntry {
    string action;
    string deviceName;
    string timestamp;
};

vector<LogEntry> logHistory;

void logAction(const string& action, const string& deviceName) {
    time_t now = time(0);
    char* dt = ctime(&now);
    string timestamp(dt);
    timestamp.pop_back();
    logHistory.push_back({action, deviceName, timestamp});
}

void turnOn(Device& device) {
    device.isOn = true;
    cout << device.name << " is now ON" << endl;
    logAction("Turned ON", device.name);
}

void turnOff(Device& device) {
    device.isOn = false;
    cout << device.name << " is now OFF" << endl;
    logAction("Turned OFF", device.name);
}

void displayStatus(const Device& device) {
    cout << device.name << " is " << (device.isOn ? "ON" : "OFF") << endl;
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void controlDevice(Device devices[], int numDevices, const string& deviceName, bool turnOn) {
    string lowerDeviceName = toLower(deviceName);
    for (int i = 0; i < numDevices; i++) {
        if (toLower(devices[i].name) == lowerDeviceName) {
            if (turnOn) {
                ::turnOn(devices[i]);
            } else {
                ::turnOff(devices[i]);
            }
            return;
        }
    }
    cout << "Device not found!" << endl;
}

void showStatus(const Device devices[], int numDevices) {
    for (int i = 0; i < numDevices; i++) {
        displayStatus(devices[i]);
    }
}

void showLogHistory() {
    cout << "\n--- Command History ---\n";
    for (const auto& log : logHistory) {
        cout << "[" << log.timestamp << "] " << log.action << " on " << log.deviceName << endl;
    }
}

int main() {
    const int maxDevices = 3;
    Device devices[maxDevices] = {
        {"Light", false},
        {"Thermostat", false},
        {"Camera", false}
    };

    int choice;
    string deviceName;
    cout << "\nSmart Home Automation System" << endl;
    
    while (true) {
        cout << "\nPress 1 to Turn On Device." << endl;
        cout << "Press 2 to Turn Off Device." << endl;
        cout << "Press 3 to Show Status" << endl;
        cout << "Press 4 to Show Command History" << endl;
        cout << "Press 5 to Exit." << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cout<<endl;

        switch (choice) {
        case 1:
            cout << "Enter device name: ";
            cin >> deviceName;
            controlDevice(devices, maxDevices, deviceName, true);
            break;
        case 2:
            cout << "Enter device name: ";
            cin >> deviceName;
            controlDevice(devices, maxDevices, deviceName, false);
            break;
        case 3:
            showStatus(devices, maxDevices);
            break;
        case 4:
            showLogHistory();
            break;
        case 5:
            cout << "Exiting Program..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }
    return 0;
}

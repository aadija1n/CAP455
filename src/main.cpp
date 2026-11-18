#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <ctime>

using namespace std;

// Maximum number of bikes that can be handled in one program run.
const int MAX_BIKES = 100;
const char DATA_FILE[] = "data/bikes.dat";
const char BACKUP_FILE[] = "data/bikes_backup.dat";
const char CSV_FILE[] = "data/bikes_export.csv";

// A small custom exception used when a bike cannot be found.
class BikeNotFoundException : public runtime_error {
public:
    BikeNotFoundException() : runtime_error("Bike with this registration number was not found.") {}
};

// Base class: common details shared by all bikes.
class Bike {
private:
    string regNo;
    string ownerName;
    string model;
    int currentKm;
    int lastServiceKm;
    int serviceIntervalKm;
    int daysSinceService;
    int serviceIntervalDays;

    // Every Bike object gets a simple running number.
    static int totalBikes;

public:
    // Default constructor.
    Bike() {
        regNo = "";
        ownerName = "";
        model = "";
        currentKm = 0;
        lastServiceKm = 0;
        serviceIntervalKm = 3000;
        daysSinceService = 0;
        serviceIntervalDays = 180;
        totalBikes++;
    }

    // Parameterised constructor.
    Bike(string regNo, string owner, string model, int currentKm,
         int lastKm, int intervalKm, int days, int intervalDays) {
        this->regNo = regNo; // this pointer distinguishes the member from the parameter.
        this->ownerName = owner;
        this->model = model;
        this->currentKm = currentKm;
        this->lastServiceKm = lastKm;
        this->serviceIntervalKm = intervalKm;
        this->daysSinceService = days;
        this->serviceIntervalDays = intervalDays;
        totalBikes++;
    }

    // Copy constructor.
    Bike(const Bike &other) {
        regNo = other.regNo;
        ownerName = other.ownerName;
        model = other.model;
        currentKm = other.currentKm;
        lastServiceKm = other.lastServiceKm;
        serviceIntervalKm = other.serviceIntervalKm;
        daysSinceService = other.daysSinceService;
        serviceIntervalDays = other.serviceIntervalDays;
        totalBikes++;
    }

    // Virtual destructor is needed because objects may be deleted through a base pointer.
    virtual ~Bike() {}

    // Inline getter and setter examples.
    string getRegNo() const { return regNo; }
    int getCurrentKm() const { return currentKm; }
    void setCurrentKm(int km) { if (km >= 0) currentKm = km; }
    void setLastServiceKm(int km) { if (km >= 0) lastServiceKm = km; }
    void setDaysSinceService(int days) { if (days >= 0) daysSinceService = days; }

    static int getTotalBikes() { return totalBikes; }

    // Virtual functions demonstrate run-time polymorphism.
    virtual string getBikeType() const { return "Regular"; }
    virtual int getSuggestedInterval() const { return serviceIntervalKm; }

    // Operator overloading: compare bikes using their current kilometre readings.
    bool operator<(const Bike &other) const { return currentKm < other.currentKm; }
    bool operator>(const Bike &other) const { return currentKm > other.currentKm; }
    bool operator==(const Bike &other) const { return regNo == other.regNo; }
    Bike& operator+=(int km) { if (km > 0) currentKm += km; return *this; }

    // A simple conversion function: a bike can be converted to its current kilometre value.
    operator int() const { return currentKm; }

    // Friend function can access private members to print a bike.
    friend void showBike(const Bike &bike);
    friend ostream& operator<<(ostream &out, const Bike &bike);
    friend istream& operator>>(istream &in, Bike &bike);
    Bike& operator=(const Bike &other) {
        if (this != &other) {
            regNo = other.regNo; ownerName = other.ownerName; model = other.model;
            currentKm = other.currentKm; lastServiceKm = other.lastServiceKm;
            serviceIntervalKm = other.serviceIntervalKm; daysSinceService = other.daysSinceService;
            serviceIntervalDays = other.serviceIntervalDays;
        }
        return *this;
    }

    // Used by the binary-file code to access all fields safely.
    string getOwner() const { return ownerName; }
    string getModel() const { return model; }
    int getLastServiceKm() const { return lastServiceKm; }
    int getServiceIntervalKm() const { return serviceIntervalKm; }
    int getDaysSinceService() const { return daysSinceService; }
    int getServiceIntervalDays() const { return serviceIntervalDays; }

    void setDetails(string reg, string owner, string bikeModel, int nowKm,
                    int lastKm, int intervalKm, int days, int intervalDays) {
        regNo = reg; ownerName = owner; model = bikeModel;
        currentKm = nowKm; lastServiceKm = lastKm; serviceIntervalKm = intervalKm;
        daysSinceService = days; serviceIntervalDays = intervalDays;
    }

    virtual void display() const {
        showBike(*this);
    }

    bool isServiceDue() const {
        return (currentKm - lastServiceKm >= getSuggestedInterval()) ||
               (daysSinceService >= serviceIntervalDays);
    }
};

// Stream operators are overloaded so a Bike can be printed/read with standard streams.
ostream& operator<<(ostream &out, const Bike &bike) {
    out << bike.regNo << " | " << bike.ownerName << " | " << bike.model
        << " | " << bike.currentKm << " KM";
    return out;
}

istream& operator>>(istream &in, Bike &bike) {
    cout << "Registration number: "; in >> bike.regNo;
    cout << "Owner name (one word): "; in >> bike.ownerName;
    cout << "Model (one word): "; in >> bike.model;
    cout << "Current KM: "; in >> bike.currentKm;
    return in;
}

int Bike::totalBikes = 0;

// Derived class 1: commuter bikes usually have a longer service interval.
class CommuterBike : public Bike {
public:
    CommuterBike() : Bike() {}
    CommuterBike(string r, string o, string m, int c, int l, int i, int d, int id)
        : Bike(r, o, m, c, l, i, d, id) {}
    string getBikeType() const override { return "Commuter"; }
    int getSuggestedInterval() const override { return getServiceIntervalKm(); }
};

// Derived class 2: sports bikes use a slightly shorter interval for this project.
class SportsBike : public Bike {
public:
    SportsBike() : Bike() {}
    SportsBike(string r, string o, string m, int c, int l, int i, int d, int id)
        : Bike(r, o, m, c, l, i, d, id) {}
    string getBikeType() const override { return "Sports"; }
    int getSuggestedInterval() const override { return getServiceIntervalKm() > 500 ? getServiceIntervalKm() - 500 : getServiceIntervalKm(); }
};

// Friend function definition.
void showBike(const Bike &bike) {
    cout << "Registration: " << bike.regNo << " | Owner: " << bike.ownerName
         << " | Model: " << bike.model << " | Type: " << bike.getBikeType()
         << " | Current KM: " << bike.currentKm
         << " | Last service KM: " << bike.lastServiceKm
         << " | Service: " << (bike.isServiceDue() ? "DUE" : "Not due") << '\n';
}

// Fixed-size record for binary storage. Fixed char arrays make each record the same size.
struct BikeRecord {
    char regNo[25];
    char owner[50];
    char model[50];
    char type[15];
    int currentKm;
    int lastServiceKm;
    int intervalKm;
    int daysSinceService;
    int intervalDays;
};

// Convert a Bike object into a fixed-size record before writing to the file.
BikeRecord makeRecord(const Bike &bike) {
    BikeRecord r{};
    strncpy(r.regNo, bike.getRegNo().c_str(), sizeof(r.regNo) - 1);
    strncpy(r.owner, bike.getOwner().c_str(), sizeof(r.owner) - 1);
    strncpy(r.model, bike.getModel().c_str(), sizeof(r.model) - 1);
    strncpy(r.type, bike.getBikeType().c_str(), sizeof(r.type) - 1);
    r.currentKm = bike.getCurrentKm();
    r.lastServiceKm = bike.getLastServiceKm();
    r.intervalKm = bike.getServiceIntervalKm();
    r.daysSinceService = bike.getDaysSinceService();
    r.intervalDays = bike.getServiceIntervalDays();
    return r;
}

// Re-create the correct derived object from a record.
Bike* makeBike(const BikeRecord &r) {
    if (string(r.type) == "Sports")
        return new SportsBike(r.regNo, r.owner, r.model, r.currentKm, r.lastServiceKm,
                              r.intervalKm, r.daysSinceService, r.intervalDays);
    if (string(r.type) == "Commuter")
        return new CommuterBike(r.regNo, r.owner, r.model, r.currentKm, r.lastServiceKm,
                                r.intervalKm, r.daysSinceService, r.intervalDays);
    return new Bike(r.regNo, r.owner, r.model, r.currentKm, r.lastServiceKm,
                    r.intervalKm, r.daysSinceService, r.intervalDays);
}

// Function template: the same display function can print different data types.
template <class T>
void printValue(string label, T value) {
    cout << label << value << '\n';
}

// Class template: a very small generic box used to keep the last deleted record.
template <class T>
class SimpleBox {
private:
    T value;
    bool hasValue;
public:
    SimpleBox() : hasValue(false) {}
    void put(T item) { value = item; hasValue = true; }
    bool isEmpty() const { return !hasValue; }
    T get() const { return value; }
    void clear() { hasValue = false; }
};

// Input helper prevents invalid text from getting stuck in numeric input.
int readNumber(string prompt, int minimum = 0) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Please enter a valid number (minimum " << minimum << ").\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readText(string prompt) {
    string value;
    do {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) cout << "This field cannot be empty.\n";
    } while (value.empty());
    return value;
}

class BikeManager {
private:
    // Array of base-class pointers allows objects of derived classes too.
    Bike *bikes[MAX_BIKES];
    int count;
    SimpleBox<BikeRecord> lastDeleted; // used for the simple undo feature

    int findIndex(string reg) const {
        for (int i = 0; i < count; i++) {
            Bike *ptr = bikes[i]; // pointer walks through the array
            if (ptr->getRegNo() == reg) return i;
        }
        return -1;
    }

    void saveAll() const {
        ofstream out(DATA_FILE, ios::binary | ios::trunc);
        if (!out) throw runtime_error("Could not open the data file for saving.");
        for (int i = 0; i < count; i++) {
            BikeRecord r = makeRecord(*bikes[i]);
            out.write(reinterpret_cast<const char*>(&r), sizeof(r));
        }
    }

    void loadAll() {
        ifstream in(DATA_FILE, ios::binary);
        if (!in) return; // First run: data file may not exist yet.
        BikeRecord r;
        while (in.read(reinterpret_cast<char*>(&r), sizeof(r))) {
            if (count < MAX_BIKES && findIndex(r.regNo) == -1)
                bikes[count++] = makeBike(r);
        }
    }

public:
    BikeManager() : count(0) {
        for (int i = 0; i < MAX_BIKES; i++) bikes[i] = nullptr;
        loadAll();
    }

    ~BikeManager() {
        for (int i = 0; i < count; i++) delete bikes[i];
    }

    void addBike() {
        if (count >= MAX_BIKES) { cout << "Bike list is full.\n"; return; }
        string reg = readText("Registration number: ");
        if (findIndex(reg) != -1) { cout << "This registration number already exists.\n"; return; }
        string owner = readText("Owner name: ");
        string model = readText("Bike model: ");
        cout << "1. Regular  2. Commuter  3. Sports\n";
        int type = readNumber("Choose bike type: ", 1);
        while (type > 3) type = readNumber("Choose 1, 2 or 3: ", 1);
        int current = readNumber("Current kilometres: ");
        int last = readNumber("Kilometres at last service: ");
        while (last > current) { cout << "Last service KM cannot exceed current KM.\n"; last = readNumber("Enter again: "); }
        int interval = readNumber("Service interval in KM (e.g. 3000): ", 1);
        int days = readNumber("Days since last service: ");
        int intervalDays = readNumber("Service interval in days (e.g. 180): ", 1);
        if (type == 2) bikes[count] = new CommuterBike(reg, owner, model, current, last, interval, days, intervalDays);
        else if (type == 3) bikes[count] = new SportsBike(reg, owner, model, current, last, interval, days, intervalDays);
        else bikes[count] = new Bike(reg, owner, model, current, last, interval, days, intervalDays);
        count++;
        saveAll();
        cout << "Bike added and saved.\n";
    }

    void showAll() const {
        if (count == 0) { cout << "No bike records available.\n"; return; }
        for (int i = 0; i < count; i++) bikes[i]->display();
        printValue("Total bikes in this program: ", count);
    }

    void searchBike() {
        string reg = readText("Enter registration number to search: ");
        int index = findIndex(reg);
        if (index == -1) throw BikeNotFoundException();
        bikes[index]->display();
    }

    void updateBike() {
        string reg = readText("Enter registration number to update: ");
        int index = findIndex(reg);
        if (index == -1) throw BikeNotFoundException();
        cout << "1. Update current KM  2. Update last-service KM  3. Update days since service\n";
        int choice = readNumber("Choice: ", 1);
        if (choice == 1) {
            int km = readNumber("New current KM: ");
            if (km < bikes[index]->getLastServiceKm()) { cout << "Current KM cannot be below last service KM.\n"; return; }
            bikes[index]->setCurrentKm(km);
        } else if (choice == 2) {
            int km = readNumber("New last-service KM: ");
            if (km > bikes[index]->getCurrentKm()) { cout << "Last service KM cannot exceed current KM.\n"; return; }
            bikes[index]->setLastServiceKm(km);
        } else if (choice == 3) {
            bikes[index]->setDaysSinceService(readNumber("New days since service: "));
        } else { cout << "Invalid choice.\n"; return; }
        saveAll();
        cout << "Bike updated.\n";
    }

    void deleteBike() {
        string reg = readText("Enter registration number to delete: ");
        int index = findIndex(reg);
        if (index == -1) throw BikeNotFoundException();
        bikes[index]->display();
        cout << "Are you sure? (y/n): ";
        char answer; cin >> answer; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (answer != 'y' && answer != 'Y') { cout << "Delete cancelled.\n"; return; }
        lastDeleted.put(makeRecord(*bikes[index]));
        delete bikes[index];
        for (int i = index; i < count - 1; i++) bikes[i] = bikes[i + 1];
        bikes[count - 1] = nullptr;
        count--;
        saveAll();
        cout << "Bike deleted. Use Undo delete to restore the last deleted bike.\n";
    }

    void undoDelete() {
        if (lastDeleted.isEmpty()) { cout << "There is no recent deletion to undo.\n"; return; }
        BikeRecord r = lastDeleted.get();
        if (findIndex(r.regNo) != -1 || count >= MAX_BIKES) { cout << "Cannot restore this record.\n"; return; }
        bikes[count++] = makeBike(r);
        lastDeleted.clear();
        saveAll();
        cout << "Last deleted bike restored.\n";
    }

    void showDue() const {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (bikes[i]->isServiceDue()) { bikes[i]->display(); found = true; }
        }
        if (!found) cout << "No services are due right now.\n";
    }

    void sortByKilometres() {
        // STL vector and sort algorithm are used on a temporary list of pointers.
        vector<Bike*> list;
        for (int i = 0; i < count; i++) list.push_back(bikes[i]);
        sort(list.begin(), list.end(), [](Bike *a, Bike *b) { return *a < *b; });
        for (Bike *b : list) b->display();
    }

    void showStatistics() const {
        // count_if is used to count bikes that need service.
        vector<Bike*> list;
        for (int i = 0; i < count; i++) list.push_back(bikes[i]);
        int due = count_if(list.begin(), list.end(), [](Bike *b) { return b->isServiceDue(); });
        cout << "Total records: " << count << " | Service due: " << due << '\n';
        // find_if finds the first bike with a service due.
        auto it = find_if(list.begin(), list.end(), [](Bike *b) { return b->isServiceDue(); });
        if (it != list.end()) cout << "First due bike: " << (*it)->getRegNo() << '\n';
    }

    void backupData() const {
        ifstream source(DATA_FILE, ios::binary);
        ofstream backup(BACKUP_FILE, ios::binary | ios::trunc);
        if (!source || !backup) { cout << "Backup could not be created.\n"; return; }
        backup << source.rdbuf();
        cout << "Backup created at " << BACKUP_FILE << '\n';
    }

    void exportCSV() const {
        ofstream out(CSV_FILE);
        if (!out) { cout << "CSV file could not be created.\n"; return; }
        out << "Registration,Owner,Model,Type,CurrentKM,LastServiceKM,ServiceIntervalKM,DaysSinceService,ServiceIntervalDays\n";
        for (int i = 0; i < count; i++) {
            out << '"' << bikes[i]->getRegNo() << "\",\"" << bikes[i]->getOwner() << "\",\""
                << bikes[i]->getModel() << "\",\"" << bikes[i]->getBikeType() << "\"," 
                << bikes[i]->getCurrentKm() << ',' << bikes[i]->getLastServiceKm() << ','
                << bikes[i]->getServiceIntervalKm() << ',' << bikes[i]->getDaysSinceService() << ','
                << bikes[i]->getServiceIntervalDays() << '\n';
        }
        cout << "CSV exported to " << CSV_FILE << '\n';
    }

    // CA2 demonstration: seekg reads a fixed-size record by its position.
    void demonstrateSeekg() const {
        string reg = readText("Registration number to locate in binary file: ");
        ifstream in(DATA_FILE, ios::binary);
        BikeRecord r;
        bool found = false;
        while (in) {
            streampos position = in.tellg();
            if (!in.read(reinterpret_cast<char*>(&r), sizeof(r))) break;
            if (reg == r.regNo) {
                in.seekg(position); // move the read pointer back to this record
                in.read(reinterpret_cast<char*>(&r), sizeof(r));
                cout << "Record found using seekg: " << r.regNo << " | " << r.model << '\n';
                found = true; break;
            }
        }
        if (!found) cout << "Record not found in file.\n";
    }

    // CA2 demonstration: seekp updates one fixed-size record in place.
    void demonstrateSeekp() {
        string reg = readText("Registration number to update using seekp: ");
        fstream file(DATA_FILE, ios::in | ios::out | ios::binary);
        if (!file) { cout << "Data file is not available.\n"; return; }
        BikeRecord r;
        bool found = false;
        while (file) {
            streampos position = file.tellg();
            if (!file.read(reinterpret_cast<char*>(&r), sizeof(r))) break;
            if (reg == r.regNo) {
                int newKm = readNumber("Enter corrected current KM: ");
                if (newKm < r.lastServiceKm) { cout << "KM cannot be below last service KM.\n"; return; }
                r.currentKm = newKm;
                file.seekp(position); // move write pointer to the start of this record
                file.write(reinterpret_cast<const char*>(&r), sizeof(r));
                cout << "File record updated using seekp. Reload the program to see it.\n";
                found = true; break;
            }
        }
        if (!found) cout << "Record not found in file.\n";
        file.close();
        // Reload the in-memory list so the display matches the file.
        for (int i = 0; i < count; i++) delete bikes[i];
        count = 0;
        loadAll();
    }

    void menu() {
        int choice;
        do {
            cout << "\n===== BIKE SERVICE INTERVAL REMINDER =====\n"
                 << "1. Add bike (Create)\n2. View all bikes (Read)\n3. Search bike\n"
                 << "4. Update bike\n5. Delete bike\n6. Show service reminders\n"
                 << "7. Sort bikes by current KM\n8. Show statistics\n9. Backup data\n"
                 << "10. Export CSV\n11. Undo last delete\n12. Demonstrate seekg search\n"
                 << "13. Demonstrate seekp update\n0. Exit\n";
            choice = readNumber("Enter choice: ");
            try {
                switch (choice) {
                    case 1: addBike(); break;
                    case 2: showAll(); break;
                    case 3: searchBike(); break;
                    case 4: updateBike(); break;
                    case 5: deleteBike(); break;
                    case 6: showDue(); break;
                    case 7: sortByKilometres(); break;
                    case 8: showStatistics(); break;
                    case 9: backupData(); break;
                    case 10: exportCSV(); break;
                    case 11: undoDelete(); break;
                    case 12: demonstrateSeekg(); break;
                    case 13: demonstrateSeekp(); break;
                    case 0: cout << "Thank you. Data is already saved.\n"; break;
                    default: cout << "Please choose a menu option from 0 to 13.\n";
                }
            } catch (const BikeNotFoundException &e) {
                cout << e.what() << '\n';
            } catch (const exception &e) {
                cout << "Error: " << e.what() << '\n';
            }
        } while (choice != 0);
    }
};

int main() {
    try {
        BikeManager manager;
        manager.menu();
    } catch (const exception &e) {
        cout << "Program could not start: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

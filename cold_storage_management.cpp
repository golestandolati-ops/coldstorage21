#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class FoodItem {
protected:
    string name;
    int code;
    float temperature;
    int quantity;

public:
    FoodItem() {
        name = "";
        code = 0;
        temperature = 0;
        quantity = 0;
    }

    FoodItem(string n, int c, float t, int q) {
        name = n;
        code = c;
        temperature = t;
        quantity = q;
    }

    virtual ~FoodItem() {
    }

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "Code: " << code << endl;
        cout << "Temperature: " << temperature << endl;
        cout << "Quantity: " << quantity << endl;
    }

    int getCode() const {
        return code;
    }

    string getName() const {
        return name;
    }

    float getTemperature() const {
        return temperature;
    }

    int getQuantity() const {
        return quantity;
    }
};

class DairyProduct : public FoodItem {
private:
    string expiryDate;

public:
    DairyProduct() : FoodItem() {
        expiryDate = "";
    }

    DairyProduct(string n, int c, float t, int q, string e)
        : FoodItem(n, c, t, q) {
        expiryDate = e;
    }

    ~DairyProduct() {
    }

    void display() const override {
        cout << "\nDairy Product" << endl;
        FoodItem::display();
        cout << "Expiry Date: " << expiryDate << endl;
    }

    string getExpiryDate() const {
        return expiryDate;
    }

    friend ostream& operator<<(ostream& os, const DairyProduct& d);
};

ostream& operator<<(ostream& os, const DairyProduct& d) {
    os << d.name << "," << d.code << "," << d.temperature << ","
       << d.quantity << "," << d.expiryDate;
    return os;
}

class ProteinProduct : public FoodItem {
private:
    string packagingType;

public:
    ProteinProduct() : FoodItem() {
        packagingType = "";
    }

    ProteinProduct(string n, int c, float t, int q, string p)
        : FoodItem(n, c, t, q) {
        packagingType = p;
    }

    ~ProteinProduct() {
    }

    void display() const override {
        cout << "\nProtein Product" << endl;
        FoodItem::display();
        cout << "Packaging Type: " << packagingType << endl;
    }

    string getPackagingType() const {
        return packagingType;
    }

    friend ostream& operator<<(ostream& os, const ProteinProduct& p);
};

ostream& operator<<(ostream& os, const ProteinProduct& p) {
    os << p.name << "," << p.code << "," << p.temperature << ","
       << p.quantity << "," << p.packagingType;
    return os;
}

class ColdStorage {
private:
    vector<DairyProduct> dairyProducts;
    vector<ProteinProduct> proteinProducts;

public:
    void addDairyProduct() {
        string name;
        string expiryDate;
        int code;
        float temperature;
        int quantity;

        cout << "Enter dairy product name: ";
        cin >> name;
        cout << "Enter code: ";
        cin >> code;
        cout << "Enter temperature: ";
        cin >> temperature;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter expiry date: ";
        cin >> expiryDate;

        DairyProduct d(name, code, temperature, quantity, expiryDate);
        dairyProducts.push_back(d);

        cout << "Dairy product added successfully.\n";
    }

    void addProteinProduct() {
        string name;
        string packagingType;
        int code;
        float temperature;
        int quantity;

        cout << "Enter protein product name: ";
        cin >> name;
        cout << "Enter code: ";
        cin >> code;
        cout << "Enter temperature: ";
        cin >> temperature;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter packaging type: ";
        cin >> packagingType;

        ProteinProduct p(name, code, temperature, quantity, packagingType);
        proteinProducts.push_back(p);

        cout << "Protein product added successfully.\n";
    }

    void showAllProducts() const {
        if (dairyProducts.empty() && proteinProducts.empty()) {
            cout << "Storage is empty.\n";
            return;
        }

        cout << "\n--- Dairy Products ---" << endl;
        for (int i = 0; i < dairyProducts.size(); i++) {
            dairyProducts[i].display();
        }

        cout << "\n--- Protein Products ---" << endl;
        for (int i = 0; i < proteinProducts.size(); i++) {
            proteinProducts[i].display();
        }
    }

    void saveToFile() const {
        ofstream outFile("coldstorage.txt");

        if (!outFile) {
            cout << "File error.\n";
            return;
        }

        for (int i = 0; i < dairyProducts.size(); i++) {
            outFile << "D," << dairyProducts[i] << endl;
        }

        for (int i = 0; i < proteinProducts.size(); i++) {
            outFile << "P," << proteinProducts[i] << endl;
        }

        outFile.close();
        cout << "Data saved to file.\n";
    }

    void loadFromFile() {
        ifstream inFile("coldstorage.txt");

        if (!inFile) {
            cout << "File not found.\n";
            return;
        }

        dairyProducts.clear();
        proteinProducts.clear();

        string type;

        while (getline(inFile, type, ',')) {
            if (type == "D") {
                string name, codeStr, tempStr, quantityStr, expiryDate;

                getline(inFile, name, ',');
                getline(inFile, codeStr, ',');
                getline(inFile, tempStr, ',');
                getline(inFile, quantityStr, ',');
                getline(inFile, expiryDate);

                int code = stoi(codeStr);
                float temperature = stof(tempStr);
                int quantity = stoi(quantityStr);

                DairyProduct d(name, code, temperature, quantity, expiryDate);
                dairyProducts.push_back(d);
            }
            else if (type == "P") {
                string name, codeStr, tempStr, quantityStr, packagingType;

                getline(inFile, name, ',');
                getline(inFile, codeStr, ',');
                getline(inFile, tempStr, ',');
                getline(inFile, quantityStr, ',');
                getline(inFile, packagingType);

                int code = stoi(codeStr);
                float temperature = stof(tempStr);
                int quantity = stoi(quantityStr);

                ProteinProduct p(name, code, temperature, quantity, packagingType);
                proteinProducts.push_back(p);
            }
        }

        inFile.close();
        cout << "Data loaded from file.\n";
    }
};

int main() {
    ColdStorage storage;
    int choice;

    do {
        cout << "\n===== Cold Storage Management =====" << endl;
        cout << "1. Add Dairy Product" << endl;
        cout << "2. Add Protein Product" << endl;
        cout << "3. Show All Products" << endl;
        cout << "4. Save To File" << endl;
        cout << "5. Load From File" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            storage.addDairyProduct();
            break;
        case 2:
            storage.addProteinProduct();
            break;
        case 3:
            storage.showAllProducts();
            break;
        case 4:
            storage.saveToFile();
            break;
        case 5:
            storage.loadFromFile();
            break;
        case 0:
            cout << "Program ended." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 0);

    return 0;
}

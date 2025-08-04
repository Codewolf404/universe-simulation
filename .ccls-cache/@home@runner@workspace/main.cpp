#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

string classify_universe(double omega_m, double omega_lambda) {
    double total = omega_m + omega_lambda;
    if (abs(total - 1.0) < 1e-2)
        return "Flat";
    else if (total < 1.0)
        return "Open";
    else
        return "Closed";
}

void print_explanation(string type) {
    if (type == "Flat")
        cout << "The universe is flat.";
    else if (type == "Open")
        cout << "The universe is open.";
    else if (type == "Closed")
        cout << "The universe is closed.";
    else
        cout << "Invalid universe type.";
}

bool get_valid_input(string label, double& var) {
    while (true) {
        cout << label;
        cin >> var;

        if (!cin.fail()) return true;

        cin.clear();                  // clear the fail flag
        cin.ignore(10000, '\n');      // discard invalid input
        cout << "Invalid input! Please enter a number.\n";
    }
}

int main() {
    double HO, omega_m, omega_lambda;

    cout << "A Simulation for the Expansion of Universe by Beast\n";

    get_valid_input("Enter the Hubble constant (HO) in km/s/Mpc: ", HO);
    get_valid_input("Enter the matter density parameter (omega_m): ", omega_m);
    get_valid_input("Enter the dark energy density parameter (omega_lambda): ", omega_lambda);

    string universe_type = classify_universe(omega_m, omega_lambda);
    print_explanation(universe_type);

    cout << "\n(Next: Plotting expansion graph...)\n";

    return 0;
}
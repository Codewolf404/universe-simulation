#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

// Constants
const double METER_PER_MPC = 3.085677581491367e22;
const double SEC_PER_GYR = 3.15576e16; // seconds in one billion years

// Function to classify the universe based on omega_m and omega_lambda
string classify_universe(double omega_m, double omega_lambda) {
    double total = omega_m + omega_lambda;
    if (total < 0 || total > 2.0) return "Invalid_universe";
    if (fabs(total - 1.0) <= 1e-2) return "Flat";
    if (total < 1.0) return "Open";
    return "Closed";
}

// Function to print detailed explanation of each universe type
void print_explanation(string type) {
    if (type == "Flat") {
        cout << "The universe is flat.\n";
        cout << "It has exactly the critical density needed to make space geometrically flat.\n";
        cout << "Expansion slows over time but never stops entirely.\n";
    }
    else if (type == "Open") {
        cout << "The universe is open.\n";
        cout << "It has less than the critical density, meaning space has negative curvature like a saddle.\n";
        cout << "Gravity cannot halt the expansion, so it will expand forever at a significant rate.\n";
    }
    else if (type == "Closed") {
        cout << "The universe is closed.\n";
        cout << "It has more than the critical density, meaning space has positive curvature like a sphere.\n";
        cout << "Gravity will eventually reverse the expansion, leading to a Big Crunch.\n";
    }
    else if (type == "Invalid_universe") {
        cout << "Invalid universe parameters.\n";
        cout << "The sum of densities must be between 0 and about 2 for realistic cosmological models.\n";
        return;
    }
    cout << "\nOur actual universe is very close to flat, with accelerated expansion due to dark energy.\n";
    cout << "This allows galaxies, stars, and life to exist for billions of years into the future.\n";
}

// Function to get valid numerical input from the user
bool get_valid_input(string label, double& var) {
    while (true) {
        cout << label;
        cin >> var;
        if (!cin.fail()) return true;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Please enter a number.\n";
    }
}

// Hubble parameter H(a) for given scale factor
double H_of_a(double a, double H0_s, double Om, double Ol) {
    double Ok = 1.0 - Om - Ol; // curvature
    return H0_s * sqrt(Om * pow(a, -3.0) + Ok * pow(a, -2.0) + Ol);
}

int main() {
    double H0, omega_m, omega_lambda;

    cout << "A Simulation for the Expansion of Universe by Atufa Vora\n\n";

    get_valid_input("Enter the Hubble constant (H0) in km/s/Mpc: ", H0);
    get_valid_input("Enter the matter density parameter (omega_m): ", omega_m);
    get_valid_input("Enter the dark energy density parameter (omega_lambda): ", omega_lambda);

    string universe_type = classify_universe(omega_m, omega_lambda);
    print_explanation(universe_type);
    if (universe_type == "Invalid_universe") return 0;

    // Convert H0 to per second (SI)
    double H0_s = (H0 * 1000.0) / METER_PER_MPC;

    // Integration parameters
    double a_min = 1e-6; // near Big Bang
    double a_max = 1.0;  // today
    int N = 200000;       // steps
    double da = (a_max - a_min) / N;

    // Integrate to get the age of universe in seconds, then convert to Gyr
    double t_sec = 0.0;
    double a = a_min;
    for (int i = 0; i < N; ++i) {
        double f1 = 1.0 / (a * H_of_a(a, H0_s, omega_m, omega_lambda));
        double a2 = a + da;
        double f2 = 1.0 / (a2 * H_of_a(a2, H0_s, omega_m, omega_lambda));
        t_sec += 0.5 * (f1 + f2) * da;
        a = a2;
    }
    double age_gyr = t_sec / SEC_PER_GYR; // convert seconds to billion years
    cout << fixed << setprecision(3);
    cout << "\nEstimated age of the universe: " << age_gyr << " billion years\n";

    // Generate data file for plotting t vs a (limited decimals for readability)
    ofstream out("t_vs_a.txt");
    out << "# a    t_Gyr\n";
    double t_accum = 0.0;
    a = a_min;
    for (int i = 0; i < N; ++i) {
        double f1 = 1.0 / (a * H_of_a(a, H0_s, omega_m, omega_lambda));
        double a2 = a + da;
        double f2 = 1.0 / (a2 * H_of_a(a2, H0_s, omega_m, omega_lambda));
        t_accum += 0.5 * (f1 + f2) * da;
        out << a2 << " " << t_accum/SEC_PER_GYR << "\n";
        cout << fixed << setprecision(6);
        if (i % 5000 == 0) {
    cout << "a=" << a2 << " t=" << t_accum/SEC_PER_GYR << " Gyr\n";
        }
    }
    out.close();
    cout << "Data saved to t_vs_a.txt for plotting.\n";

    return 0;
}
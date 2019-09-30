#include <iostream>
using namespace std;

int main(){
    cout << "Odometer at start: ";
    int startValue;
    cin >> startValue;
    if (startValue < 0) {                   /*  Condition to determine if starting odometer reading is negative */
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative." << endl;   /*  Error message 1 */
        return 1;
    }
    
    cout << "Odometer at end: ";
    int endValue;
    cin >> endValue;
    if (endValue < startValue) {            /*  Condition to determine if final odometer reading is not at least as large as starting reading   */
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;    /*  Error message 2 */
        return 2;
    }
    
    cout << "Rental days: ";
    int days;
    cin >> days;
    cin.ignore(10000, '\n');
    if (days <= 0) {                        /*  Condition to determine if number of rental days is nonpositive  */
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;  /*  Error message 3 */
        return 3;
    }
    
    cout << "Customer name: ";
    string name;
    getline(cin, name);
    if (name == "") {                       /*  Condition to determine if customer name is an empty string  */
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;  /*  Error message 4 */
        return 4;
    }
    
    cout << "Luxury car? (y/n): ";
    string luxury;
    getline(cin, luxury);
    if (luxury != "y" && luxury != "n") {   /*  Condition to determine if neither y nor n is entered for question about luxury car  */
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;   /* Error message 5 */
        return 5;
    }
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    if (month < 1 or month > 12) {          /* Condition to determine if month number is not in the range 1 through 12 */
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;  /* Error message 6  */
        return 6;
    }
    
    cout << "---" << endl;
    
    int dailyCharge;
    int distance = endValue - startValue;
    double mileCharge = 0.27;
    double postMileCharge;
    double postPostMileCharge = 0.19;
    double totalCharge;
    
    if (luxury == "y")
        dailyCharge = 61;
    else
        dailyCharge = 33;
    
    if (month >= 4 and month <= 11)
        postMileCharge = 0.21;
    else
        postMileCharge = 0.27;
    
    if (distance <= 100)
        totalCharge = dailyCharge * days + mileCharge * distance;   /* Formula for determining rental charge when distance is less than or equal to 100 */
    else if (distance <= 400)
        totalCharge = dailyCharge * days + 27 + postMileCharge * (distance - 100);  /* Formula for determining rental charge when distance is between 101 and 400 */
    else
        totalCharge = dailyCharge * days + 27 + postMileCharge * 300 + postPostMileCharge * (distance - 400); /* Formula for determining rental charge when distance is greater than 400 */
    
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "The rental charge for " << name << " is $" << totalCharge;
    return 0;
}

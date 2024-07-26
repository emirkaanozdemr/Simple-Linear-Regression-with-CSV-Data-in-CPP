#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

vector<vector<double>> readCSV(const string& filename) {
    vector<vector<double>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "File could not be opened!" << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            row.push_back(stod(value));
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

int main() {
    string filename = "data.csv";
    vector<vector<double>> data = readCSV(filename);

    if (data.empty()) {
        cerr << "No data or file could not be opened." << endl;
        return -1;
    }

    int rows = data.size();
    int cols = data[0].size();


    MatrixXd X(rows, 2); 
    VectorXd y(rows);

    for (int i = 0; i < rows; ++i) {
        X(i, 0) = 1;
        X(i, 1) = data[i][0];
        y(i) = data[i][1];
    }

    VectorXd beta = (X.transpose() * X).inverse() * X.transpose() * y;
    cout << "Coefficients (beta):" << endl << beta << endl;
    VectorXd x_new(2);
    x_new << 1, 6;

    double y_pred = x_new.transpose() * beta;
    cout << "Prediction for new data point (x = 6): " << y_pred << endl;

    return 0;
}

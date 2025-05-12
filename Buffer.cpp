#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;


const size_t BUFFER_SIZE = 4096;

void readWithoutBuffer(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    char ch;
    auto start = high_resolution_clock::now();

    while (file.get(ch)) {}

    auto end = high_resolution_clock::now();
    cout << "Time without buffer: "
        << duration_cast<milliseconds>(end - start).count()
        << " ms\n";

    file.close();
}

void readWithBuffer(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<char> buffer(BUFFER_SIZE);
    auto start = high_resolution_clock::now();

    while (file.read(buffer.data(), buffer.size())) {}

    auto end = high_resolution_clock::now();
    cout << "Time with buffer: "
        << duration_cast<milliseconds>(end - start).count()
        << " ms\n";

    file.close();
}

int main() {
    string filename = "C:\\Users\\2M group\\Documents\\sample.txt";

    readWithoutBuffer(filename);
    readWithBuffer(filename);

    return 0;
}

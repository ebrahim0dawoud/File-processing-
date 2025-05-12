#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;



struct FAT12Entry {
    char filename[8];
    char ext[3];
    uint8_t attr;
    uint8_t reserved[10];
    uint16_t time;
    uint16_t date;
    uint16_t firstCluster;
    uint32_t fileSize;
};

void readFAT12(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    file.seekg(512 * 19); // موقع دليل الجذر في FAT12
    vector<FAT12Entry> entries(224); // دليل الجذر يمكن أن يحتوي على 224 إدخالاً

    file.read(reinterpret_cast<char*>(entries.data()), sizeof(FAT12Entry) * 224);

    cout << "Filename      Ext  Size       First Cluster\n";
    cout << "-----------------------------------------\n";
    for (const auto& entry : entries) {
        if (entry.filename[0] == 0x00) break; // نهاية الإدخالات
        if ((uint8_t)entry.filename[0] == 0xE5) continue; // محذوف

        cout << setw(8) << entry.filename << "  "
            << setw(3) << entry.ext << "  "
            << setw(10) << entry.fileSize << "  "
            << setw(10) << entry.firstCluster << "\n";
    }

    file.close();
}

int main() {
    string diskImage = "fat.img";
    readFAT12(diskImage);
    return 0;
}

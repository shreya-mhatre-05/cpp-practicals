// Practical 11: CSV Student Records using File I/O (fstream)
//
// CSV format used (one student per line, no header):
//     id,name,marks
//     101,Shreya Mhatre,88.5
// Names must not contain commas.
//
// PART A: write, read and validate a CSV file.
// PART B: demonstrate tellg(), seekg(), tellp(), seekp() on a simple text file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    double marks;
};

// Write all students to a CSV file. Returns false on failure.
bool writeCsv(const string& filename, const vector<Student>& students) {
    ofstream out(filename);                       // opens for writing (overwrites)
    if (!out.is_open()) {
        cout << "  Error: cannot open '" << filename << "' for writing.\n";
        return false;
    }
    for (const Student& s : students) {
        out << s.id << "," << s.name << "," << s.marks << "\n";
    }
    if (!out) {                                   // check that writing succeeded
        cout << "  Error: writing to '" << filename << "' failed.\n";
        return false;
    }
    return true;
}

// Read students from a CSV file. Bad lines are reported and skipped.
vector<Student> readCsv(const string& filename) {
    vector<Student> students;
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "  Error: cannot open '" << filename << "' for reading.\n";
        return students;
    }

    string line;
    int lineNo = 0;
    while (getline(in, line)) {
        lineNo++;
        if (!line.empty() && line.back() == '\r') line.pop_back();   // Windows line ending
        if (line.empty()) continue;

        stringstream ss(line);
        string idText, name, marksText;
        if (!getline(ss, idText, ',') || !getline(ss, name, ',') || !getline(ss, marksText)) {
            cout << "  Line " << lineNo << " skipped (expected 3 fields): " << line << "\n";
            continue;
        }
        try {
            Student s;
            s.id = stoi(idText);
            s.name = name;
            s.marks = stod(marksText);
            students.push_back(s);
        } catch (...) {
            cout << "  Line " << lineNo << " skipped (bad number): " << line << "\n";
        }
    }
    return students;
}

void printTable(const vector<Student>& students) {
    cout << "  " << left << setw(6) << "ID" << setw(20) << "Name" << "Marks\n";
    cout << "  " << string(32, '-') << "\n";
    for (const Student& s : students) {
        cout << "  " << left << setw(6) << s.id << setw(20) << s.name << s.marks << "\n";
    }
}

int main() {
    // ============================================================
    cout << "=== PART A: CSV write and read ===\n";
    vector<Student> students = {
        {101, "Shreya Mhatre", 88.5},
        {102, "Rahul Patil", 72},
        {103, "Anita Sharma", 91.25}
    };

    cout << "Writing students.csv ...\n";
    if (writeCsv("students.csv", students)) cout << "  Written " << students.size() << " records.\n";

    cout << "\nReading students.csv back:\n";
    printTable(readCsv("students.csv"));

    cout << "\nTesting a missing file:\n";
    readCsv("no_such_file.csv");

    cout << "\nTesting malformed lines (bad_students.csv):\n";
    {
        ofstream bad("bad_students.csv");
        bad << "201,Good Student,80\n";
        bad << "202,Missing Marks\n";            // too few fields
        bad << "abc,Bad Id,70\n";                // id is not a number
        bad << "204,Another Good,65.5\n";
    }
    printTable(readCsv("bad_students.csv"));

    // ============================================================
    cout << "\n=== PART B: file position functions ===\n";
    // Binary mode is used so that byte counts are the same on every system
    // (text mode on Windows turns "\n" into 2 bytes).

    // Create a simple file with known contents (26 letters)
    {
        ofstream f("alphabet.txt", ios::binary);
        f << "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    // ---- GET position (input): tellg() and seekg() ----
    ifstream in("alphabet.txt", ios::binary);
    cout << "\nInput (get) position:\n";
    cout << "  tellg() at start         = " << in.tellg() << "\n";
    char c;
    in.get(c);
    in.get(c);
    in.get(c);
    cout << "  after reading 3 chars    = " << in.tellg() << " (last char read: " << c << ")\n";
    in.seekg(10, ios::beg);                       // 10 bytes from the beginning
    in.get(c);
    cout << "  seekg(10, beg), read     = " << c << "\n";
    in.seekg(-1, ios::end);                       // 1 byte before the end
    in.get(c);
    cout << "  seekg(-1, end), read     = " << c << "\n";
    in.close();

    // ---- PUT position (output): tellp() and seekp() ----
    // fstream with in|out lets us overwrite inside an existing file
    fstream io("alphabet.txt", ios::in | ios::out | ios::binary);
    cout << "\nOutput (put) position:\n";
    cout << "  tellp() at start         = " << io.tellp() << "\n";
    io.seekp(5, ios::beg);                        // move the write position to index 5
    cout << "  after seekp(5, beg)      = " << io.tellp() << "\n";
    io.write("**", 2);                            // overwrite 2 characters
    cout << "  after writing 2 chars    = " << io.tellp() << "\n";
    io.close();

    ifstream check("alphabet.txt", ios::binary);
    string content;
    getline(check, content);
    cout << "  file now contains        : " << content << "\n";

    return 0;
}

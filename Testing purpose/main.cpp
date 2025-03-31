#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inp("input.inp");
    ofstream out("out.out");

    int t;
    inp >> t;
    inp.ignore(); // Bỏ qua dòng newline sau số t

    while (t--) {
        string line;
        getline(inp, line);

        set<string> unique_words; //('a')
        stringstream ss(line); // ("a", "b" , "c", "d")
        string word;
        
        while (ss >> word) {
            unique_words.insert(word);
        }

        out << unique_words.size() << "\n";
    }

    inp.close();
    out.close();
    
    return 0;
}

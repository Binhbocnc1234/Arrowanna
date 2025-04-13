#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
// #include <c
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, A;
    cin >> n >> A;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    //  prefix sum cho dãy b với b[i] = a[i] - A
    vector<long long> P(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        P[i] = P[i - 1] + (a[i - 1] - A);
    }
    
    // Xây dựng stack chứa các chỉ số của mảng P theo thứ tự giảm dần của giá trị P
    stack<int> st;
    for (int i = 0; i <= n; i++) {
        if (st.empty() || P[i] < P[st.top()]) {
            st.push(i);
            // cout << i << ' ';
        }
    }
    
    int maxLength = 0;
    int l = 0, r = INT_MAX;
    for (int j = n; j >= 0; j--) {
        while (!st.empty() && P[j] >= P[st.top()]) {
            if (j - st.top() > maxLength && j < r){
                maxLength = max(maxLength, j - st.top());
                r = j;
                l = st.top() + 1;
            }
            
            st.pop();
        }
    }
    
    cout << maxLength << "\n";
    cout << l << ' ' << r;
    return 0;
}

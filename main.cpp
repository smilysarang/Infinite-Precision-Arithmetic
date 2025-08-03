#include<bits/stdc++.h>
using namespace std;
string add(string num1, string num2){
    int len1 = num1.size(), len2 = num2.size();
    if(len1 > len2) return add(num2, num1);
    int i = len1-1, j = len2-1;
    string ans = "";
    int carry = 0;
    while (i >= 0 || j >= 0) {
        int d1 = (i >= 0) ? num1[i] - '0' : 0;
        int d2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = d1 + d2 + carry;
        ans.push_back('0' + (sum % 10));
        carry = sum / 10;

        i--;
        j--;
    }
    if(carry) ans.push_back('0' + carry);
    reverse(ans.begin(), ans.end());
    return ans;
}
int main(){
    string num1, num2;
    cin >> num1 >> num2;

    int len1 = num1.size(), len2 = num2.size();
    int i = len1-1, j = len2-1;

    string sum = add(num1, num2);
    cout << sum;
}
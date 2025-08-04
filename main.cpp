#include<bits/stdc++.h>
using namespace std;

int findGreater(string num1, string num2);
string subtract(string num1, string num2);
string add(string num1, string num2);
string multiply(string num1, string num2);
string multdig(string num, string d);
string divide(string num1, string num2);
void trimLeadingZeros(string &s) {
    while (s.size() > 1 && s[0] == '0')
        s.erase(s.begin());
}
string multdig(string num, string d){
    int len = num.size();
    int j = len-1;
    string ans = "";
    int dig = d[0] - '0';
    int carry = 0;
    while(j >= 0){
        int strd = num[j] - '0';
        int prod = dig * strd + carry;
        ans.push_back('0' + (prod % 10));
        carry = prod / 10;
        j--;
    }
    if(carry) ans.push_back('0' + carry);
    reverse(ans.begin(), ans.end());
    trimLeadingZeros(ans);
    return ans;
}
string add(string num1, string num2){
    if(num1[0] == '-' && num2[0] == '-'){
        num1.erase(num1.begin());
        num2.erase(num2.begin());
        return '-' + add(num1, num2);
    }
    if(num1[0] == '-'){
        num1.erase(num1.begin());
        return subtract(num2, num1);
    }
    if(num2[0] == '-'){
        num2.erase(num2.begin());
        return subtract(num1, num2);
    }
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
    trimLeadingZeros(ans);
    return ans;
}

string subtract(string num1, string num2){
    if(num1[0] == '-' && num2[0] == '-'){
        num2.erase(num2.begin());
        num1.erase(num1.begin());
        return subtract(num2, num1);
    }
    else if(num1[0] == '-'){
        num1.erase(num1.begin());
        return '-' + add(num1, num2);
    }
    else if(num2[0] == '-') {
        num2.erase(num2.begin());
        return add(num1, num2);
    }
    int len1 = num1.size(), len2 = num2.size();
    int big =  findGreater(num1, num2);
    if(big == 2) return "-" + subtract(num2, num1);
    if(big == 0) return "0";
    int i = len1-1, j = len2-1;
    int carry = 0;
    string ans = "";
    while(i >= 0 || j >= 0){
        int d1 = (i >= 0) ? num1[i] - '0': 0;
        int d2 = (j >= 0) ? num2[j] - '0': 0;

        ans.push_back('0' + (10+d1-d2-carry)%10);
        if(d1 - d2 - carry< 0) carry = 1;
        else carry = 0;

        i--;
        j--;
    }
    
    reverse(ans.begin(), ans.end());

    trimLeadingZeros(ans);

    return ans;
}

int findGreater(string num1, string num2){
    int len1 = num1.size(), len2 = num2.size();
    if(len1 > len2) return 1;
    else if(len2 > len1) return 2;
    else{
        int i = 0, j = 0;
        while(i < len1 && j < len2 && num1[i] == num2[j]){
            i++;
            j++;
        }
        if(i >= len1) return 0;
        else if(num1[i]-'0' > num2[j]-'0') return 1;
        else if(num1[i]-'0' < num2[j]-'0') return 2;
    }
    return -1;
}

string multiply(string num1, string num2){
    if(num1[0] == '-' && num2[0] == '-'){
        num1.erase(num1.begin());
        num2.erase(num2.begin());
        return multiply(num1, num2);
    }
    if(num1[0] == '-'){
        num1.erase(num1.begin());
        return "-" + multiply(num1, num2);
    }
    if(num2[0] == '-'){
        num2.erase(num2.begin());
        return "-" + multiply(num1, num2);
    }
    int len1 = num1.size(), len2 = num2.size();
    if(len1 < len2) return multiply(num2, num1);
    int i = len1-1, j = len2-1;
    string ans = "";
    int c = 0;
    while(j >= 0){
        string d = "";
        d += num2[j];
        string m = multdig(num1, d);
        for(int i = 0; i < c; i++) m.push_back('0');
        ans = add(m, ans);
        c++;
        j--;
    }
    trimLeadingZeros(ans);
    return ans;
}
bool isZero(string num){
    for(auto ch: num) if(ch != '0') return false;
    return true;
}
string divide(string num1, string num2){
    if(num1[0] == '-' && num2[0] == '-'){
        num1.erase(num1.begin());
        num2.erase(num2.begin());
        return divide(num1, num2);
    }
    if(num1[0] == '-'){
        num1.erase(num1.begin());
        return "-" + divide(num1, num2);
    }
    if(num2[0] == '-'){
        num2.erase(num2.begin());
        return "-" + divide(num1, num2);
    }
    if(isZero(num2)) return "Error: Division by 0 not possible";
    int len1 = num1.size(), len2 = num2.size();
    if(findGreater(num1, num2) == 2) return "0";

    int j = 0;
    string ans = "";
    string cur = "";
    while(j < len1){
        cur.push_back(num1[j]);
        trimLeadingZeros(cur);

        int count = 0;
        while(findGreater(cur, num2) != 2){
            cur = subtract(cur, num2);
            count++;
            trimLeadingZeros(cur);
        }
        ans.push_back('0' + count);
        j++;
    }
    trimLeadingZeros(ans);
    return ans;
}
int main(){
    string num1, op, num2;
    cin >> num1 >> op >> num2;

    trimLeadingZeros(num1);
    trimLeadingZeros(num2);
    if(op == "+"){
    string sum = add(num1, num2);
    cout << sum << endl;
    }
    else if(op == "-"){
    string difference = subtract(num1, num2);
    cout << difference << endl;
    }
    else if(op == "*" || op == "x"){
        string product = multiply(num1, num2);
        cout << product << endl;
    }
    else if(op == "/"){
        string quotient = divide(num1, num2);
        cout << quotient << endl;
    }
}
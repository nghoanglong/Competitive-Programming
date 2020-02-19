#include<iostream>
#include<string>
#include<math.h>
#define maxN 1000

bool arr_s[maxN][maxN];
int max_pal = -1*maxN;
int result[maxN];
using namespace std;

//Bài toán tìm chuỗi đối xứng liên tiếp dài nhất từ chuỗi đích được nhập vào từ bàn phím
//Ví dụ: abcdcbaabcd -> output: dcbaabcd
//time complexity: 0(n^2), quy hoạch động cơ bản
//Có thể giảm time xuống O(n) với thuật toán Manacher ở folder Algorithm
void DP_FindLongPal(string s){
    int pos_right;
    int pos_first;
    int pos_end;
    for(int i = 0;i < s.length();++i){
        arr_s[i][i] = true;
    }
    for(int num = 2;num <= s.length();num++){
        for(int i = 0;i <= s.length() - num;++i){
            pos_right = i + (num - 1);
            if(s[i] == s[pos_right]){
                if(num == 2){
                    arr_s[i][pos_right] = true;
                }
                else if(num > 2){
                    arr_s[i][pos_right] = arr_s[i + 1][pos_right - 1];
                }
                if(arr_s[i][pos_right] && (abs(i - pos_right) + 1) > max_pal){
                    max_pal = i - pos_right + 1;
                    pos_first = i;
                    pos_end = pos_right;
                }
            }
            else{
                arr_s[i][pos_right] = false;
            }
        }
    }
    for(int i = pos_first;i <= pos_end;i++){
        cout << s[i];
    }
}

/*Bài toán chia một chuỗi thành ít nhất các Palindrome có thể có được
  Ví dụ: bobseesanna = bob + sees + sanna -> 3 pal
                     = bob + s + ee + s + anna -> 5 pal
                     .......
    -> 3 là số lượng palindrome nhỏ nhất có thể chia*/
bool checkPal(int j, int i,string s){
    while(j <= i){
        if(s[j] != s[i])
            return false;
        else{
            j++;
            i--;
        }
    }
    return true;
}
void DP_FindMinDivPal(string s){
    //chuỗi bắt đầu từ 0 -> n - 1
    result[-1] = 0;
    int n = s.length();
    for(int i = 0;i < n;i++){
        result[i] = i + 1;
        for(int j = i;j >= 0;j--){
            if(checkPal(j,i,s)){
                result[i] = min(result[i],result[j - 1] + 1);
            }
        }
    }
    cout << result[n - 1];
}

int main(){
    string s;
    cin >> s;
    DP_FindLongPal(s);
    //DP_FindMinDivPal(s);
    return 0;
}
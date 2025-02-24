// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

void PrintArray(int arr[], int len){
    cout << "\n";
    for(int i = 0; i < len; i++){
        cout << arr[i]  << " ";
    }
}
void getOutCode(int arr[], int x, int y, int Xmin, int Ymin, int Xmax, int Ymax){
    for(int i = 0; i < 4; i++)
        arr[i] = 0;
    
    if(x < Xmin)
        arr[3] = 1;
    if(x > Xmax)
        arr[2] = 1;
    if(y < Ymin)
        arr[1] = 1;
    if(y > Ymax)
        arr[0] = 1;
}
int main() {
    // int xa, ya, xb, yb, Xmin, Ymin, Xmax, Ymax;
    int xa = 45, ya = 15; 
    int xb = 75, yb = 45;
    int Xmin = 50, Ymin = 10; 
    int Xmax = 80, Ymax = 40;

    float m;
    // cout << "\nEnter xa, ya: ";
    // cin >> xa >> ya;
    // cout << "\nEnter xb, yb: ";
    // cin >> xb >> yb;
    
    // cout << "\nEnter Xmin, Ymin: ";
    // cin >> Xmin >> Ymin;
    // cout << "\nEnter Xmax, Ymax: ";
    // cin >> Xmax >> Ymax;
    
    m = (yb - ya) / (xb - xa);
    // cout << m;
    int A[4], B[4];
    getOutCode(A, xa, ya, Xmin, Ymin, Xmax, Ymax);
    getOutCode(B, xb, yb, Xmin, Ymin, Xmax, Ymax);
    
    int flag = 0;
    for(int i = 0; i < 4; i++){
        if(A[i] == 1 || B[i] == 1){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        cout << "\nRejected or Partially accepted!";
        
        int flag = 0;
        for(int i = 0; i < 4; i++){
            if(A[i] && B[i]){
                flag = 1;
            }
        }
            if(flag == 1){
                cout << "\nCompletely rejected";
            }else{
                cout << "\nPartially accepted";
            }
        
        
    }else{
        cout << "Completely inside!";
    }
   
    return 0;
}
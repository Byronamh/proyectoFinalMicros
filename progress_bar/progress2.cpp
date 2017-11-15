#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
  cout << endl;

  for (int i=0; i <= 100; ++i){

    string progress = "[" + string(i, '|') + string(100-i, ' ') + "]";
    cout << "\r\033[1A" << i << "\n" << progress << flush;
    usleep(10000);
 
  }

cout<<endl;
}

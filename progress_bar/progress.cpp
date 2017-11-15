#include <string>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;


// function prototype
void progress( int percent );

// main code
int main(int argc, char* argv[]) {

  int N = 100;
	
  for(int i = 0; i < N; i++) {
    // compute percentage
    float p = (i / (float) N) * (float) 100;
    progress(p);
    //cout << p << endl;
    usleep(20000);
  }

  progress(100);
  cout << endl;

  return 0;
}

// print progress
void progress( int percent ){
  string bar;

  for(int i=0; i<50; i++){

    if( i<(percent/2) ){
      bar.replace(i,1,"|");
    }
   else{
      bar.replace(i,1," ");
    }

  }

  cout<< "\r"<< bar<<" ";
  cout.width( 3 );
  cout<< percent << " %     " << std::flush;
}

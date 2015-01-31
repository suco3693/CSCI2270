
#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS

using namespace std;

int main( )
{
	int i= 0;
	for (int n=0; n<7;++n)
	{
		for (int m=0; m<12; ++m)
		{
			i++;
			cout << i << endl;
		}	
	}	
}

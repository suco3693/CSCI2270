
#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS
using namespace std;


double underflow_double( );

float underflow_float( );

int main( )
{
    cout << underflow_float() << endl;
    cout << underflow_double() << endl;
    return EXIT_SUCCESS;
}

double underflow_double( )
{
    double eps1 = 1;
    while (eps1 > 0)
    {
		eps1=0.5 * eps1;		
		double eps2=0.5*eps1;
		if (eps2==0)
			break;
		
	}		
	return eps1;	
}

float underflow_float( )
{
    float eps1 = 1;
     while (eps1 > 0)
    {
		eps1=0.5 * eps1;		
		float eps2=0.5*eps1;
		if (eps2==0)
			break;
		
	}		
	return eps1;	
}


#include <iostream>

using namespace std;

int str(int);

int main()
{
	int n=4;

	str(n);

	return 0;
}





int str(int n)
{	int x;
	if(n==0)
	return -1;

	for(int i=0;i<n;i++)
		cout<<"*";
		cout<<endl;

		x= str(n-1);
	for(int j=0;j<n;j++)
		cout<<"*";
		cout<<endl;
		return 0;


}

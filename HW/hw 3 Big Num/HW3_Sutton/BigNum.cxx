// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		digits[0]=0;
		used=1;
		positive= true;		
	}    

	BigNum::BigNum(int num)
	{
		capacity= DEFAULT_CAPACITY;
		digits = new unsigned int [capacity];
		used=0;	
		if (num == 0)
		{
			capacity = DEFAULT_CAPACITY;
			digits = new unsigned int[capacity];
			digits[0]=0;
			used=1;
			positive= true;	
		}	
		if(num<0)
		{
			num=num*-1;
			positive = false;
		}	
		else
		{
			positive = true;
		}	
		while(num > 0)
		{
			digits[used]= num%10;
			num= (num-digits[used])/10;
			used++;
		}
		
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		
		capacity = strin.length();
		digits = new unsigned int[capacity];
		used=0;
		if( strin[0] == '-')
		{	
			positive = false;
			for(int i=0; i<(capacity-1);i++)
			{
			digits[i]=strin[capacity-i-1]-'0';
			used++;
			}
		}		
		else{
			positive=true;
			for(int i=0; i<(capacity);i++)
			{	
			digits[i]=strin[capacity-1-i]-'0';
			used++;
			}	
		}
		while(digits[used-1]==0 && used>1)
		{
			used--;
		}			
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
			capacity = anotherBigNum.capacity;
			positive = anotherBigNum.positive;
			used=anotherBigNum.used;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i< used; i++)
			{
				digits[i]=anotherBigNum.digits[i];
			}
    }

    BigNum::~BigNum()
    {
		delete [] digits;
		used = 0;
    }
    
    void BigNum::resize(unsigned int n)
	{
		unsigned int* newdigits = digits;
		digits = new unsigned int[n];
		for (unsigned int i = 0; i< used; i++)
		{
			digits[i]=newdigits[i];
		}	
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if (this != &anotherBigNum)
		{
			delete [] digits;
			capacity = anotherBigNum.capacity;
			positive = anotherBigNum.positive;
			used=anotherBigNum.used;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i< used; i++)
			{
				digits[i]=anotherBigNum.digits[i];
			}
			return *this;
		}
		else
		{		
		return *this;
		}
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{	
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		if(a.capacity >= b.capacity){
			this->capacity=2*a.capacity;}
		else{
			this->capacity=2*b.capacity;}
		int carry;
		carry= 0;
		unsigned int k;
		k=0;
		this->used=0;
		while(k <b.used){
				if(a.digits[k]<b.digits[k]+carry){
					this->digits[k]=a.digits[k]+10-b.digits[k]-carry;
					carry=1;
				}
				else if(a.digits[k]==b.digits[k]+carry){
					this->digits[k]=0;
					carry=0;
				}	
				else{
					this->digits[k]=a.digits[k]-carry-b.digits[k];
					carry=0;
				}
				k++;
				used++;
			}	
		while(k<a.used){
				if(a.digits[k]<carry){
					this->digits[k]=a.digits[k]-carry;
					carry=1;
				}
				else{
					this->digits[k]=a.digits[k]-carry;
					carry=0;
				}
				k++;
				used++;
			}			
		while(digits[used-1]==0 && used>1)
		{
			used--;
		}			
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		// Something is wrong here causes error
		if(a.capacity >= b.capacity){
			this->capacity=2*a.capacity;}
		else{
			this->capacity=2*b.capacity;}
		int carry;
		carry= 0;
		unsigned int k;
		k=0;
		this->used=0;	
		if(b.used>=a.used){	
			while(k <a.used){
				this->digits[k]=a.digits[k]+b.digits[k]+carry;		
				if(this->digits[k]>=10){
				this->digits[k]=this->digits[k]-10;
					carry=1;
				}
				else{
					carry=0;
				}
				this->used++;
				k++;		
			}
			while(k<b.used){
				this->digits[k]=b.digits[k]+carry;
				if(this->digits[k]>=10){
					this->digits[k]=this->digits[k]-10;
					carry=1;
				}
				else{
					carry=0;
				}
				this->used++;
				k++;
			}
			if(carry==1)
			{
				this->digits[k]=1;
				this->used++;
			}			
		}
		if(b.used<=a.used){	
			while(k <b.used){
				this->digits[k]=a.digits[k]+b.digits[k]+carry;		
				if(this->digits[k]>=10){
				this->digits[k]=this->digits[k]-10;
					carry=1;
				}
				else{
					carry=0;
				}
				this->used++;
				k++;		
			}
			while(k<a.used){
				this->digits[k]=a.digits[k]+carry;
				if(this->digits[k]>=10){
					this->digits[k]=this->digits[k]-10;
					carry=1;
				}
				else{
					carry=0;
				}
				this->used++;
				k++;
			}
			if(carry==1)
			{
				this->digits[k]=1;
				this->used++;
			}			
		}		
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		int k;
		if(a.positive==true && b.positive ==true){
			result.sum(a,b);
			result.positive=true;
		}
		if(a.positive==false && b.positive==false){
			result.sum(a,b);
			result.positive=false;
		}
		if(a.positive==true && b.positive ==false){
			if(a.used>b.used){
				result.diff(a,b);
				result.positive=true;
			}
			else if(a.used<b.used){
				result.diff(b,a);
				result.positive=false;
			}
			else{
				while(a.digits[k]==b.digits[k]){
					k++;
				}
				if(a.digits[k]<b.digits[k]){
				result.diff(b,a);
				result.positive=false;
				}
				else{
				result.diff(a,b);
				result.positive=true;
				}
			}							
		}
		k=0;
		if(a.positive==false && b.positive ==true){
			if(a.used>b.used){
				result.diff(a,b);
				result.positive=false;
			}
			else if(a.used<b.used){
				result.diff(b,a);
				result.positive=true;
			}
			else{
				while(a.digits[k]==b.digits[k]){
					k++;
				}
				if(a.digits[k]>b.digits[k]){
				result.diff(a,b);
				result.positive=false;
				}
				else{
				result.diff(b,a);
				result.positive=true;
				}
			}							
		}
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		int k;
		k=0;
		if(a.positive==true && b.positive ==true){
			if(a.used>b.used){
				result.diff(a,b);
				result.positive=true;
			}
			else if(a.used<b.used){
				result.diff(b,a);
				result.positive=false;
			}
			else{
				while(a.digits[k]==b.digits[k]){
					k++;
				}
				if(a.digits[k]<b.digits[k]){
				result.diff(b,a);
				result.positive=false;
				}
				else{
				result.diff(a,b);
				result.positive=true;
				}
			}							
		}
		k=0;
		if(a.positive==false && b.positive ==false){
			if(a.used>b.used){
				result.diff(a,b);
				result.positive=false;
			}
			else if(a.used<b.used){
				result.diff(b,a);
				result.positive=true;
			}
			else{
				while(a.digits[k]==b.digits[k]){
					k++;
				}
				if(a.digits[k]>b.digits[k]){
				result.diff(a,b);
				result.positive=false;
				}
				else{
				result.diff(b,a);
				result.positive=true;
				}
			}							
		}
		if(a.positive==true && b.positive ==false){
			result.sum(a,b);
			result.positive=true;	
		}	
		if(a.positive==false && b.positive ==true){
			result.sum(a,b);
			result.positive=false;
		}		
		if(result.digits[0]==0 && result.used==1){
			result.positive=true;
		}			
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if(a.positive==b.positive && a.positive==true)
		{
			if(a.used==b.used)
			{
				for(int i=a.used-1;1>=0;i--)
				{
					if(a.digits[i]>b.digits[i])
					{
						return true;	
					}
					else 
					{
						return false;
					}	
				}		
			}
			if(a.used> b.used)
			{
				return true;
			}
			else
			{
				return false;
			}		
		}
		else if(a.positive==b.positive && a.positive!=true)
		{
			if(a.used==b.used)
			{
				for(int i=a.used-1;1>=0;i--)
				{
					if(a.digits[i]<b.digits[i])
					{
						return true;	
					}
					else 
					{
						return false;
					}	
				}		
			}
			if(a.used< b.used)
			{
				return true;
			}
			else
			{
				return false;
			}		
		}
		else
		{
			if (a.positive==true)
			{
				return true;
			}
			else
			{	
				return false;
			}
		}			
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		if(!(a<b))
		{
			return true;
		}
		else
		{
			return false;
		}		
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		if(a.positive==b.positive && a.positive== true)
		{
			if(a.used==b.used)
			{
				for(int i=a.used-1;i>=0;i--)
				{
					if(b.digits[i]>a.digits[i]){ return true;}
					else
					{
						return false;
					}		
				}	
			}
			else{
				if(a.used< b.used)
				{
					return true;
				}
				else{ return false;}
			}	
		}
		if(a.positive==b.positive && a.positive!= true)
		{
			if(a.used==b.used)
			{
				for(int i=a.used-1;i>=0;i--)
				{
					if(b.digits[i]<a.digits[i])
					{
						return true;
					}
					else
					{
						return false;
					}		
				}	
			}
			else
			{
				if(b.used<a.used)
				{
					return true;
				}
				else
				{
					return false;
				}			
			}
		}
		else
		{
			if(b.positive==true)
			{
				return true;
			}
			else
			{
				return false;
			}		
		}		
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		if(!(a>b))
		{
			return true;
		}
		else
		{
			return false;
		}	
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if(a.positive==b.positive)
		{
			if(a.used==b.used)
			{
				for(int i=a.used-1;i>=0;i--)
				{
					if(a.digits[i]==b.digits[i])
					{
						return true;
					}
					else
					{
						return false;
					}		
				}
			}
			else
			{
				return false;
			}	
		}
		else
		{
			return false;
		}				
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		if(!(a==b))
		{
			return true;
		}
		else 
		{
			return false;
		}		
	}

	// trim leading zeros
	void BigNum::trim()
	{
		
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if(bignum.positive==false)
		{
			os << '-';
		}
		for(unsigned int i=0; i< bignum.used; i++)
		{
			os<< bignum.digits[(bignum.used-1)-i];
		}		
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string a;
		is >> a;
		BigNum temp = BigNum(a);
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }



#endif





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
		digits[0] = 0;
		positive = true;      
		used = 1;
	}    

	BigNum::BigNum(int num)
	{
		digits = nullptr;

		if (num == 0) 
		{
			BigNum zero;
			*this = zero;
		}
    
		else 
		{
			if (num > 0) 
			{
				positive = true;
			}
			else 
			{
				positive = false;
				num = -num;
			}
      
			unsigned int i = 0, temp = num;
      
			// count the digits
			while (temp > 0) 
			{
				temp = temp/10; 
				i++;
			}

			capacity = i; 
		
			digits = new unsigned int[capacity];

			temp = num;
		
			for (used = 0; used < i; ++used) 
			{
				digits[used] = temp % 10;
				temp /= 10;
			}
		}
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		digits = nullptr;
		
		int len = strin.length();
		
		if (len == 0)
		{
			BigNum zero;
			*this = zero;
			return;
		}

		used = len;
		positive = true;
		
		int i = 0;

		if(strin[i] == '-')  
		{
			positive = false;
			i = 1;
			used--;
		}
		else if(strin[i] == '+')  
		{
			i = 1;
			used--;
		}
		
		capacity = used;
	
		digits = new unsigned int[capacity];

		for(unsigned int k = 0; k < used; ++k) 
		{
			digits[used - k - 1] = strin[i++] - '0';
		}
		
		if (used == 1 && digits[0] == 0)
			positive = true;
			
		trim();
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		digits = nullptr;
		
		// makes operator = do the work; use that function if you use this
		*this = anotherBigNum;
    }

    BigNum::~BigNum()
    {
		delete [] digits;
    }
        
    // assume doubling is done before passing in n
	void BigNum::resize(unsigned int n)
	{
		unsigned int *largerArray;

		if (n < used) return; // Can't allocate less than we are using

		capacity = n;
		largerArray = new unsigned int[capacity];
		
		copy(digits, digits + used, largerArray);
		
		delete [] digits;
		digits = largerArray;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if (this == &anotherBigNum)  return *this;
		
		if (digits != nullptr)
			delete [] digits;
			
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];
		
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
  
		return *this;
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		BigNum a=*this;
		a=a+addend;
		*this=a;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		BigNum a=*this;
		a=a-subtractand;
		*this=a;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		BigNum a=*this;
		a=a*multiplicand;
		*this=a;
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
		*this=*this+1;
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		*this=*this-1;
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		if(a.capacity >= b.capacity)
		{
			this->resize(3*a.capacity);
		}
		else
		{
			this->resize(3*b.capacity);
		}	
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
				if(a.digits[k]< (unsigned int)carry){
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
		if(a.capacity >= b.capacity)
		{
			this->resize(3*a.capacity);
		}
		else
		{
			this->resize(3*b.capacity);
		}
		BigNum temp;
				
		int carry=0;
		temp.used=a.used+b.used;
		temp.resize(temp.used);
		int over=0;
		for(unsigned int i=0;i<temp.used;i++){
			temp.digits[i]=0;
		}	
		for(unsigned int i=0;i<b.used;i++){
			for(unsigned int k=0;k<a.used;k++){
				temp.digits[i+k]=a.digits[k]*b.digits[i]+carry+temp.digits[i+k];
				carry=temp.digits[i+k]/10;
				temp.digits[i+k]=temp.digits[i+k]%10;
				over=k+i;
			}
			if(carry>0){
				temp.digits[over+1]=carry;
				carry=0;
			}	
		}
		temp.trim();		
		*this=temp;			
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		if(a.capacity >= b.capacity)
		{
			this->resize(3*a.capacity);
		}
		else
		{
			this->resize(3*b.capacity);
		}
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
			while(k<a.used)
			{ 
				this->digits[k]=a.digits[k]+carry;
				if(this->digits[k]>=10)
				{
					this->digits[k]=this->digits[k]-10;
					carry=1;
				} 
				else
				{
					this->digits[k]=this->digits[k];
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
		BigNum result=0;
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
				while(a.digits[a.used-k-1]==b.digits[b.used-k-1]){
					k++;
				}
				if(a.digits[a.used-k-1]>b.digits[b.used-k-1]){
				result.diff(a,b);
				result.positive=false;
				}
				else{
				result.diff(b,a);
				result.positive=true;
				}
			}							
		}
		{
		while (result.used > 1 && result.digits[result.used-1] == 0)
			result.used--;
		}
	
		if(result.digits[0]==0 && result.used==1){
			result.positive=true;
		}	
		return result;
	}


	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		int k;
		k=0;
		if(a.positive==true && b.positive ==true)
		{
			if(a==b)
			{
				return result;
			}	
			if(a.used>b.used)
			{
				result.diff(a,b);
				result.positive=true; 
			} 
			else if(a.used<b.used)
			{
				result.diff(b,a);
				result.positive=false;
			}

			else
			{
				while(a.digits[b.used-k-1]==b.digits[b.used-k-1] && b.used != (unsigned int)k && a.used != (unsigned int)k)
				{
					k++;
				}
				if(a.digits[a.used-k-1]<b.digits[b.used-k-1])
				{
					result.diff(b,a);
					result.positive=false;
				}
				else
				{
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
				while(a.digits[a.used-k-1]==b.digits[b.used-k-1]){
					k++;
				}
				if(a.digits[a.used-k-1]>b.digits[b.used-k-1]){
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
		{
		while (result.used > 1 && result.digits[result.used-1] == 0)
			result.used--;
		}		
		return result;
	}
      

	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if(a.positive==true && b.positive==true){
			result.mult(a,b);
			result.positive=true;
		}
		if(a.positive==false && b.positive==false){
			result.mult(a,b);
			result.positive=true;
		}
		if(a.positive==true && b.positive==false){
			result.mult(a,b);
			result.positive=false;
		}
		if(a.positive==false && b.positive==true){
			result.mult(a,b);
			result.positive=false;
		}	
		return result;
	}


	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result = a;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if (a.positive == true && b.positive == false) return true;
		
		else if (a.positive == false && b.positive == true) return false;
		
		else 
		{
			if (a.used > b.used) 
			{
				if (a.positive == true) return true;
				else return false;
			}
			
			else if (a.used < b.used) 
			{
				if (a.positive == true) return false;
				else return true;
			}
	
			else 
			{
				for (unsigned int i = 0; i < a.used; ++i) 
				{
					if (a.digits[a.used - 1 - i] < b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return false;
						else return true;
					}
					if (a.digits[a.used - 1 - i] > b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return true;
						else return false;
					}
				}
			}          
		}
		return false;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return ((a > b) || (a == b));
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		return !(a >= b);
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return !(a > b);
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if ((a.positive != b.positive) || (a.used != b.used))
			return false;

		for (unsigned int i = 0; i < a.used; i++) 
		{
			if (a.digits[a.used - 1 - i] != b.digits[b.used - 1 - i]) 
				return false;
		}

		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
	}

	// trim leading zeros
	void BigNum::trim()
	{
		while (used > 1 && digits[used-1] == 0)
			used--;
	}
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		unsigned int i = 0;
		unsigned int j = 0;

		if (bignum.positive == false)  os << '-';

		for (i=0; i<bignum.used; ++i) 
		{
			os << bignum.digits[bignum.used - i - 1];
			if (j < 60) ++j; 
			else 
			{
				os << endl;
				j = 0;
			}
		}
    
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string str;
		is >> str;

		BigNum temp = str;
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result=1;
		int temp=0;
		BigNum temp1;
		result.resize(10*a.capacity); 	
		if(a.used==1 && a.digits[0]==0){
			return result;
		}
		/*
		else
		{
			for(unsigned int i=0;i<a.used;i++){
				temp=temp+a.digits[i]*pow(10,i);
			}
			for(unsigned int i=1;i<temp+1;i=i+2){
				temp1.mult(a,a-1);
				result=result+temp1;
				
			}	
				
		}
		*/ 
		return result;		
    }
  }


#endif




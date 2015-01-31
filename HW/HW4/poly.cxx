#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest default
		
		head_ptr= new polynode(0,0);
		current_degree=0;
		if(fabs(c) >EPSILON && exponent > 0){
			tail_ptr= new polynode(c,exponent,nullptr,head_ptr);
			head_ptr->set_fore(tail_ptr);
			current_degree=exponent;
		}				
		if(head_ptr->fore()== nullptr)
		{
			tail_ptr=head_ptr;
		}
		recent_ptr=head_ptr;	
    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		//write the rest
		if(head_ptr==source.head_ptr){
			return *this;
		}
		if(head_ptr != nullptr){
			clear();
		}
		delete head_ptr;
		head_ptr= new polynode(source.head_ptr->coef(),source.head_ptr->exponent());
		tail_ptr=head_ptr;
		recent_ptr=head_ptr;
		current_degree=0;
		for(int i = source.next_term(0); i!= 0; i=source.next_term(i)){
			assign_coef(source.coefficient(i),i);
		}
		current_degree=source.current_degree;	
		
		return *this;	
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest copy 
		head_ptr=nullptr;
		*this = source; 	
    }

    polynomial::~polynomial()
    {
		clear();
    }

    void polynomial::clear()
    {
		while(head_ptr != tail_ptr)
		{
			recent_ptr=head_ptr;
			head_ptr=head_ptr->fore();
			delete recent_ptr;
		}
		recent_ptr=head_ptr;
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		tail_ptr=head_ptr;
		current_degree=0;	
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		if(recent_ptr->exponent() == exponent)
		{
			return recent_ptr->coef();
		}
		return 0;		
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);
		if(recent_ptr->exponent() != exponent){
			assign_coef(amount,exponent);
		}	
		else{	
			double sum = amount+recent_ptr->coef();
			assign_coef(sum,exponent);
		}	
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		
		set_recent(exponent);
		if(exponent==0){
			recent_ptr->set_coef(coefficient);
		}		
		else if(coefficient == 0 && exponent > current_degree){
			return;
		}
		else if(fabs(coefficient)< EPSILON && exponent <= current_degree && recent_ptr->exponent() == exponent){
			if(recent_ptr==head_ptr){
				return;
			}	
			if(recent_ptr == tail_ptr){
				polynode* temp;
				temp=tail_ptr->back();
				temp->set_fore(nullptr);
				delete tail_ptr;
				tail_ptr=temp;
				set_recent(tail_ptr->exponent());
				current_degree=tail_ptr->exponent();	
			}
			else{
				polynode* temp=recent_ptr;
				recent_ptr=recent_ptr->back();
				recent_ptr->set_fore(temp->fore());
				recent_ptr=temp->fore();
				recent_ptr->set_back(temp->back());
				delete temp;
				set_recent(exponent);
				
			}
		}		
		else if(recent_ptr->exponent() < exponent){
			polynode* temp= new polynode(coefficient,exponent, recent_ptr->fore(),recent_ptr);
			if(recent_ptr->fore() != nullptr){

				recent_ptr->fore()->set_back(temp);
				
			}
			else{
		
				current_degree=exponent;
				tail_ptr=temp;
				
			}
			recent_ptr->set_fore(temp);
		}
		else if(fabs(coefficient) > EPSILON  || exponent==0){
			
			recent_ptr->set_coef(coefficient);
			
		}
		else if(exponent == current_degree){
			
			tail_ptr=recent_ptr->back();
			delete recent_ptr;
			recent_ptr=tail_ptr;
			current_degree=tail_ptr->exponent();				
		}
		else if(exponent > current_degree){
			recent_ptr= new polynode(coefficient,exponent,nullptr,tail_ptr);
			tail_ptr->set_fore(recent_ptr);
			tail_ptr=recent_ptr;
			current_degree=exponent;	
		}		
		
    }

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
			set_recent(exponent);
			if(recent_ptr->fore() == nullptr){
				return 0;
			}
			else{
				recent_ptr=recent_ptr->fore();
				return recent_ptr->exponent();
			}		
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		set_recent(exponent);
		if(head_ptr->coef()==0){
			if(head_ptr->fore()->exponent()==exponent){
			 return UINT_MAX;
			} 
		}	
		else if(exponent == recent_ptr->exponent() && recent_ptr->back() != nullptr && exponent){
			return recent_ptr->back()->exponent();
		}	 
		else if(exponent > current_degree){	
			return tail_ptr->exponent();
		}
		else if(exponent == current_degree && current_degree!= 0){	
			return tail_ptr->back()->exponent();
		}
		else if(exponent > recent_ptr->exponent()){
			return recent_ptr->exponent();
		}
		return UINT_MAX;
    }
    
    void polynomial::set_recent(unsigned int exponent) const
    {
		recent_ptr= head_ptr;
		if(exponent==0){
			recent_ptr=head_ptr;
			return;
		}
		else if(exponent >= current_degree){
			recent_ptr=tail_ptr;
			return;
		}
		while(recent_ptr->fore() != nullptr && recent_ptr->exponent() <exponent){
			recent_ptr=recent_ptr->fore();
		}
		if(recent_ptr->exponent() >exponent){
			recent_ptr=recent_ptr->back();
		}
		return;					
								
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		polynode* curr=head_ptr;
		while(curr->fore() != nullptr){
			total=total+curr->coef()*pow(x,curr->exponent());
			curr=curr->fore();
		}
		total=total+curr->coef()*pow(x,curr->exponent());	
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		recent_ptr=head_ptr->fore();
		while(recent_ptr->fore() != nullptr)
		{
			p_prime.assign_coef(recent_ptr->coef()*recent_ptr->exponent(),recent_ptr->exponent()-1);
			recent_ptr=recent_ptr->fore();
		}
		p_prime.assign_coef(recent_ptr->coef()*recent_ptr->exponent(),recent_ptr->exponent()-1);
		p_prime.current_degree=recent_ptr->exponent()-1;
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p=p1;
		polynomial temp=p2;
		int degree=temp.degree();
		int i=0;
		while(i < degree)
		{
			p.add_to_coef(temp.coefficient(i),i);
			i=temp.next_term(i);
		}
		p.add_to_coef(temp.coefficient(i),i); 	
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p=p1;
		polynomial temp=p2;
		int degree=temp.degree();
		int i=0;
		while(i < degree)
		{
			p.add_to_coef(-temp.coefficient(i),i);
			i=temp.next_term(i);
		}
		p.add_to_coef(-temp.coefficient(i),i); 	
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial result;
		polynomial p=p1;
		polynomial temp=p2;
		int degree1=p.degree();
		int degree2=temp.degree();
		int i=0;
		int k=0;
		while(i<degree1){
			while(k<degree2){
				result.add_to_coef(p.coefficient(i)*temp.coefficient(k),i+k);
				k=temp.next_term(k);
			}
			result.add_to_coef(p.coefficient(i)*temp.coefficient(k),i+k);
			k=0;
			i=p.next_term(i);
		}
		while(k<degree2){
			result.add_to_coef(p.coefficient(i)*temp.coefficient(k),i+k);
			k=temp.next_term(k);
		}
		result.add_to_coef(p.coefficient(i)*temp.coefficient(k),i+k);				
		return result;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo=0;
		do
		{
			out<<p.coefficient(expo)<< "x^"<<expo;
			expo=p.next_term(expo);
			if(expo !=0){
				out<<"+";
			}
		}while(expo != 0);		
		return out;
    }
    
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
	}
}

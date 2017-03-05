#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <list>
#include <cassert>
#include <cstdlib>


using namespace std;
#pragma once
class Student
{
	public:
///////////////////CONSTRUCTORS//////////////////////////////////
	Student(string new_student);
	Student(string new_student, int num_prefs);
///////////////////ACCESSORS/////////////////////////////////////
	const string & GetName() const  {return student_;}
	bool HasOffer() { return HasOffer_; }
	string GetBestOffer() { return BestOffer_;}
///////////////////MODIFIERS/////////////////////////////////////
	void AddSchool(string school_name);
	void RemoveSchoolFromStudentPreferenceList(string school_name);
	bool IsOfferTentativelyAccepted(string school_name);
///////////////////PRINTS/////////////////////////////////////
	void print_students(std::ostream & ostr) const;
	void PrintStudentDecision(ofstream & ostr);
//modifiers


private:
string student_;
string BestOffer_;
list<string> school_names_;
list<string>::iterator itr_;
int num_prefs_;
bool HasOffer_;
string temp_accept_;
};
///////////////////CONSTRUCTORS//////////////////////////////////
Student::Student(string new_student)
{
	
	student_=new_student;
	num_prefs_=0;
	itr_=school_names_.begin();
	HasOffer_=false;
	BestOffer_="";
}
Student::Student(string new_student, int num_prefs)
{
	student_=new_student;
	num_prefs_=num_prefs;
	itr_=school_names_.begin();
	HasOffer_=false;
	BestOffer_="";
}
///////////////////MODIFIERS/////////////////////////////////////
void Student::AddSchool(string school_name)
{
	list<string>::iterator itr_=school_names_.begin();
	for(itr_=school_names_.begin();itr_!=school_names_.end();itr_++)//FIND SCHOOL
	{
		if(*itr_==school_name)
		{
			return;
		}
	}
	school_names_.push_back(school_name);
}

void Student::RemoveSchoolFromStudentPreferenceList(string school_name)
{
num_prefs_--;
list<string>::iterator itr_=school_names_.begin();
	for(itr_=school_names_.begin();itr_!=school_names_.end();itr_++)//FIND SCHOOL
	{
		if(*itr_==school_name)
		{
			school_names_.erase (itr_);
			return;
		}
	}
}
bool Student::IsOfferTentativelyAccepted(string school_name)
{	
	int i=0;//variable for comparing to the previous offer
	list<string>::iterator itr_=school_names_.begin();

	for(itr_=school_names_.begin();itr_!=school_names_.end();itr_++)//FIND SCHOOL
	{	 
		if (*itr_==school_name) 
		{	
			if(HasOffer_==true)
			{
				
				int j=0;
				list<string>::iterator it_temp;
				list<string>::iterator something_else;
				for( something_else=school_names_.begin();something_else!=school_names_.end();something_else++)//FIND SCHOOL
				{
					
					if(BestOffer_==*something_else)
					{
						if(i<j) // comparing to the previous offer
						{
							BestOffer_=school_name;
							return true;//if new offer is better than the old offer it is accepted

						}
						else {return false;}
						
					}
					j++;
				}
			}
			else 
			{
				HasOffer_=true;
				BestOffer_=school_name;
				return true;
			}
		}
		i++;
	}
	return false;
}
///////////////////PRINTS/////////////////////////////////////

void Student::print_students(std::ostream & ostr) const
{
	ostr<<student_<<" preference list:"<<endl;
	int i=1;
	list<string>::const_iterator itr_=school_names_.begin();
	for(itr_=school_names_.begin();itr_!=school_names_.end();itr_++)//FIND SCHOOL
	{
		ostr<<"  "<<i<<". "<<*itr_<<endl;
		i++;
	}
	ostr<<endl;
}
void Student::PrintStudentDecision(ofstream & ostr)
{
	if(BestOffer_=="")
	{
		ostr<<student_<<" has not received an acceptable offer"<<endl;
	}
	else
	{
		ostr<<student_<<" will be attending "<<BestOffer_<<endl;
	}
}
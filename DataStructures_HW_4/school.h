#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <list>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <algorithm>


using namespace std;

#pragma once
class  School
{
public:
///////////////////CONSTRUCTORS//////////////////////////////////
	School( string school_name,int num_slots, int num_prefs) ; 
///////////////////ACCESSORS/////////////////////////////////////
	list<string> get_student_list(){return student_name_;}
	const string & GetName() const {return school_name_; }
	int NumAcceptedStudents() {return NumAcceptedStudents_;}
	int MaxAcceptedStudents() {return MaxAcceptedStudents_;}
	string MakeNextOffer() ;
///////////////////MODIFIERS/////////////////////////////////////
	void AddStudent(string student);
	void InsertStudentIntoSchoolPreferenceList(string new_student_name, string insert_before_student_name);
	void StudentDeclinesTentativeAcceptance( string student);
	void StudentTentativelyAcceptsOffer(string student);
///////////////////PRINTS/////////////////////////////////////
	void   print_school(  std::ostream & ostr) const;
	void PrintSchoolEnrollment(ofstream& ostr) ;
private:
list <string> tent_student_name_;
list <string> student_name_;
int remaining_slots_;
string school_name_;
int num_slots_;
list <string>::iterator itr_;
list <string>::iterator itr_makeOffer_;
int num_prefs;
int NumAcceptedStudents_;
int MaxAcceptedStudents_;
};

//=======================CONSTRUCTORS========================
School::School( string school_name,int num_slots, int num_prefs)  
{
	school_name_=school_name;
	itr_=student_name_.begin();
	num_slots_=num_slots;
	NumAcceptedStudents_=0;
	MaxAcceptedStudents_=num_slots;
	itr_makeOffer_=student_name_.begin();
	
}
//===============MODIFIERS==================================
void School::AddStudent(string student) 
{
	list<string>::iterator itr_=student_name_.begin();
	for(itr_=student_name_.begin();itr_!=student_name_.end();itr_++)
	{
		if(*itr_==student)
		{
			return;
		}

	}
	student_name_.push_back(student);
}
void School::InsertStudentIntoSchoolPreferenceList(string new_student_name, string insert_before_student_name)
{
itr_=student_name_.begin();

	for(itr_=student_name_.begin();itr_!=student_name_.end();itr_++)//FIND STUDENT
	{
		if(*itr_==insert_before_student_name)
		{
			student_name_.insert(itr_,new_student_name);
		}
	
	}
}
void School::StudentDeclinesTentativeAcceptance( string student)
{
	itr_=student_name_.begin();
	list<string>::iterator itr_remove_student=tent_student_name_.begin();//remove student ITERATOR from tent.student list
	for(itr_remove_student=tent_student_name_.begin();itr_remove_student!=tent_student_name_.end();itr_remove_student++)//FIND STUDENT
	{
		if(*itr_remove_student==student)
		{
			tent_student_name_.erase(itr_remove_student);
			NumAcceptedStudents_--;
			return;
		}
	}

}

void School::StudentTentativelyAcceptsOffer(string student)
{
	NumAcceptedStudents_++;
	tent_student_name_.push_back(student);
}
string School::MakeNextOffer() 
{ 
	itr_makeOffer_=student_name_.begin();
	if(itr_makeOffer_!=student_name_.end())
	{
		string temp=*itr_makeOffer_;
		student_name_.erase(itr_makeOffer_);// MINUS MINUS
		return(temp);
	}
	else
	{
		return "";
	}

}
//===============PRINTS==================================
void  School:: print_school(  std::ostream & ostr) const
{
list<string>::const_iterator itr_=student_name_.begin();
	ostr<<school_name_<<" preference list:"<<endl;
	int i=1;

	for(itr_=student_name_.begin();itr_!=student_name_.end();itr_++)
	{
		if(i>=10)//MAKES THE OUTPUT LOOK GOOD
		{
			ostr<<" "<<i<<". "<<*itr_<<endl;
			i++;

		}  
		if(i<10)
		{
		ostr<<"  "<<i<<". "<<*itr_<<endl;
		i++;
		}
	}
	
	ostr<<endl;
	
}
void School::PrintSchoolEnrollment(ofstream& ostr)
{
	int num_slots= num_slots_-NumAcceptedStudents_;
	ostr<<"student(s) who will be attending "<<school_name_<<":"<<endl;
	tent_student_name_.sort();
	for(itr_=tent_student_name_.begin();itr_!=tent_student_name_.end();itr_++)
	{
		ostr<<"  "<<*itr_<<endl;
	}
	if(num_slots>0)
	{
		ostr<<"  ["<<num_slots<<" remaining slot(s) in enrollment]\n";
	}
}

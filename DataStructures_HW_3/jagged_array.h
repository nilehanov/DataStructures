#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <iomanip>

using namespace std;

template <class T> 
#pragma once
class JaggedArray
{
public:
	T data;
	JaggedArray(const T & init);
	JaggedArray(int n);

	
//FUNCTIONS
	void addElement(int box_number,T Element);
	void removeElement(int box_number,int Element_num);
	void print();
	void pack();
	void unpack();
	void clear();
//ACCESSORS
	int numBins();
	int numElements();
	bool isPacked();
	T getElement(int bin_num,int bin_array_num);
	int numElementsInBin(int number_of_bin);

//VARIABLES
private:
	int numBins_;
	int numElements_;
	bool isPacked_;
	T** bins_;
	int* offsets_;
	T* Elements_;
	T* packed_values_;
	int * numElements_by_bin_;
	int sum_elements;
	
};
template <class T> 
int JaggedArray<T>::numBins()
{
	return numBins_;
}
template <class T> 
int JaggedArray<T>::numElements()
{
	return numElements_;
}
template <class T> 
bool JaggedArray<T>::isPacked()
{
	return isPacked_;
}


template <class T> 
void JaggedArray<T>::addElement(int box_number,T Element)
{
	T * temp= new T[numElements_by_bin_[box_number]];
	T * column=new T[numElements_by_bin_[box_number]+1];
	
	for(int i=0;i<numElements_by_bin_[box_number];i++)
	{
		temp[i]=bins_[box_number][i];
	}
	bins_[box_number]=column;
	for(int i=0;i<numElements_by_bin_[box_number];i++)
	{
		bins_[box_number][i]=temp[i];
	}
	
	 bins_[box_number][numElements_by_bin_[box_number]]=Element;
	 numElements_++;
	 numElements_by_bin_[box_number]= numElements_by_bin_[box_number]+1;
	 delete [] temp;
	
	
}

template <class T> 
int JaggedArray<T>::numElementsInBin(int number_of_bin)
{	
	return numElements_by_bin_[number_of_bin];
}
template <class T> 
T JaggedArray<T>::getElement(int bin_num,int bin_array_num)
{
	if(isPacked_==false)
	{
		return bins_[bin_num][bin_array_num];
	}
	else if(isPacked_==true)
	{
		int temp_num_bin;
		if(bin_num!=(numBins_-1))
		{
		temp_num_bin=offsets_[bin_num+1]-(offsets_[bin_num+1]-offsets_[bin_num])+bin_array_num;
		return packed_values_[temp_num_bin];
		}
		else if(bin_num==(numBins_-1))
		{
		temp_num_bin=numElements_-(numElements_-offsets_[bin_num])+bin_array_num;
		return packed_values_[temp_num_bin];
		}
	}
}

template <class T> 
JaggedArray<T>::JaggedArray(int n)
{
	numBins_=n;//bins is T**
	bins_= new T*[n];
	numElements_=0;
	isPacked_=false;
	numElements_by_bin_=new int [n];
	offsets_=NULL;
	packed_values_=NULL;
		

	for (int i=0; i<numBins_;i++)
	{	
			
			numElements_by_bin_[i]=0;
			bins_[i]=NULL;
		
	}
}
template <class T> 
void JaggedArray<T>::pack()
{
	isPacked_=true;
	offsets_=new int[numBins_];
	offsets_[0]=0;
	
	for(int i=1;i<numBins_;i++)
	{

		offsets_[i]=offsets_[i-1]+numElements_by_bin_[i-1];//
	
	}

	sum_elements=0;
	for(int j=0;j<numBins_;j++)
	{
		sum_elements+=numElements_by_bin_[j];
	}
	if(packed_values_!=NULL)
	{
		delete []packed_values_;
	}
	packed_values_=new T[sum_elements];
	int count_plus=0;
	for(int i=0;i<numBins_;i++)
	{
		for(int j=0;j<numElements_by_bin_[i];j++)
		{
			packed_values_[count_plus]=bins_[i][j];
			count_plus++;
		}

	}
}
template <class T> 
void JaggedArray<T>::unpack()
{
	
	isPacked_=false;
	delete [] numElements_by_bin_;
	numElements_by_bin_=NULL;
	numElements_by_bin_=new int [numBins_];
	for(int i=0;i<numBins_;i++)
	{
		
		if(i==(numBins_ -1))
		{
			numElements_by_bin_[i]=numElements_-offsets_[numBins_-1];
			
		}
		else 
		{
		numElements_by_bin_[i]=offsets_[i+1]-offsets_[i];
		
		}
		
	}
	for(int i=0;i<numBins_;i++)
	{	
		delete []bins_[i];
	}
	delete [] bins_;
	bins_= new T*[numBins_];
	
	for (int i=0; i<numBins_;i++)
	{	
			T * column=new T[numElements_by_bin_[i]];
			bins_[i]=column;
			
	}
	
	for(int i=0;i<numBins_;i++)
	{
		for(int j=0;j<numElements_by_bin_[i];j++)
		{
			if(i!=(numBins_-1))
			{
				bins_[i][j]=packed_values_[offsets_[i+1]-(offsets_[i+1]-offsets_[i])+j];
			}
			else if(i==(numBins_-1))
			{
				bins_[i][j]=packed_values_[numElements_-(numElements_-offsets_[i])+j];
			}
		}
		

	}
	delete [] offsets_;
		offsets_=NULL;
}
template <class T> 
void JaggedArray<T>::removeElement(int box_number,int Element_num)
{
if(isPacked_==false)
{
	
	T * temp= new T[numElements_by_bin_[box_number]];
	T * column=new T[numElements_by_bin_[box_number]-1];
	
	for(int i=0;i<numElements_by_bin_[box_number];i++)
	{
		temp[i]=bins_[box_number][i];
	}
	temp[Element_num]=NULL;

	bins_[box_number]=column;
	bool it_is_null=false;
	for(int i=0;i<(numElements_by_bin_[box_number]-1);i++)
	{
		if(temp[i]==NULL&&it_is_null==false)
		{
			it_is_null=true;
			i=i-1;
		}
		else if(it_is_null==false) 
		{
			bins_[box_number][i]=temp[i];
		}
		else if(it_is_null==true) 
		{
			bins_[box_number][i]=temp[i+1];
		}
	}
	
	
	 numElements_--;
	 numElements_by_bin_[box_number]= numElements_by_bin_[box_number]-1;
}
else if(isPacked_==true)
{
	cout<<"CAN'T MODIFY WHILE PACKED";
		exit(1);
}


}
template <class T> 
void JaggedArray<T>::clear()
{
	numElements_=0;
	for(int i=0;i<numBins_;i++)
	{
		numElements_by_bin_[i]=0;
	}
}
template <class T> 
void JaggedArray<T>::print()
{
	
	if(isPacked_==false)
	{
		cout<<"unpacked JaggedArray"<<endl;
		cout<<"  num_bins: "<<numBins_<<endl;
		cout<<"  num_elements: "<<numElements_<<endl;
		cout<<"  counts:  ";
		for(int i=0;i<numBins_;i++)
		{
			cout<<numElements_by_bin_[i]<<" ";
		}

		cout<<endl;
		cout<<"  values:  ";
		int max_length;
		int max_num_elements;
		max_length=numElements_by_bin_[0];
		for(int i=0;i<numBins_-1;i++)
		{
			if(numElements_by_bin_[i]<numElements_by_bin_[i+1])
			{
				max_length=numElements_by_bin_[i+1];
			}
		}
		max_num_elements=max_length;
		if(max_length<numBins_)
		{
			max_num_elements=numBins_;
		}
		max_length=std::max(max_length,numBins_);
		for(int i=0;i<max_length;i++)
		{  
			for(int j=0;j<numBins_;j++)
			{
				if((bins_[j]==NULL)||(numElements_by_bin_[j]<=i))
				{
					cout<<"  ";
				}
				else cout<<bins_[j][i]<<" ";
			}
			cout<<endl<<setw(13);
			
		}
	}
	else if(isPacked_==true)
	{
		cout<<"packed JaggedArray"<<endl;
		cout<<"  num_bins: "<<numBins_<<endl;
		cout<<"  num_elements: "<<numElements_<<endl;
		cout<<"  offsets:  ";
		for(int i=0;i<numBins_;i++)
		{
			cout<<offsets_[i]<<" ";
		}
		cout<<endl<<"  values:   ";
		for(int i=0;i<numElements_;i++)
		{
			cout<<packed_values_[i]<<" ";
		}
		cout<<endl;
		cout<<endl;

	}
}

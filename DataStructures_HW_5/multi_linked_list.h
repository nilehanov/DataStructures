#ifndef dslist_h_
#define dslist_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular../

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <iomanip>
#include "MersenneTwister.h"
using namespace std;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
    Node() : chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), sorted_prev(NULL),random_next(NULL) {}

    // REPRESENTATION
    T value_;

    Node<T>* chrono_next;
    Node<T>* chrono_prev;

    Node<T>* sorted_next;
    Node<T>* sorted_prev;
    Node<T>* random_next;
};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
    ///CONSTRUCTORS & DESTRUCTORS
    list_iterator() : ptr_(NULL), type(0) {}
    list_iterator(Node<T>* p, int type_) : ptr_(p), type(type_) {}
    list_iterator(list_iterator<T> const& old) : ptr_(old.ptr_), type(old.type) {}
    ~list_iterator() {}

    //OPERATORS

    list_iterator<T> & operator=(const list_iterator<T> & old)
    {
        ptr_ = old.ptr_;
        type=old.type;
        return *this;
    }

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_;  }

    // increment & decrement operators
    list_iterator<T> & operator--() //pre-decrement
    {
        if(type==1)//chrono
        {
            ptr_ = ptr_->chrono_prev;
            return *this;
        }
        else if(type==2)//sorted
        {
            ptr_ = ptr_->sorted_prev;
            return *this;
        }
        else
        {
            cerr<<"Invalid operation. Cannot decrement random iterator"<<endl;
            return *this;
        }
    }

    list_iterator<T> operator--(int) //post-decrement
    {
        list_iterator<T> temp(*this);
        if(type==1)//chrono
        {
            ptr_ = ptr_->chrono_prev;
            return temp;
        }
        else if(type==2)//sorted
        {
            ptr_ = ptr_->sorted_prev;
            return temp;
        }
        else
        {
            cerr<<"Invalid operation. Cannot decrement random iterator"<<endl;
            return temp;
        }

    }

    list_iterator<T> operator++(int) //post-increment
    {
        if(type==1)//chrono
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->chrono_next;
            return temp;
        }
        else if(type==2)//sorted
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->sorted_next;
            return temp;
        }
        else //if(type==3)//random
        {
            list_iterator<T> temp(*this);
            ptr_ = ptr_->random_next;
            return temp;
        }

    }

    list_iterator<T> operator++() //pre-increment
    {
        if(type==1)//chrono
        {
            ptr_ = ptr_->chrono_next;
            return *this;
        }
        else if(type==2)//sorted
        {
            ptr_ = ptr_->sorted_next;
            return *this;
        }
        else //if(type==3)//random
        {
            ptr_ = ptr_->random_next;
            return *this;
        }

    }


    friend class MultiLL<T>;

    // Comparions operators are straightforward
    friend bool operator==(const list_iterator<T>& l, const list_iterator<T>& r) {
        return l.ptr_ == r.ptr_; }
    friend bool operator!=(const list_iterator<T>& l, const list_iterator<T>& r) {
        return l.ptr_ != r.ptr_; }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int type;

};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class MultiLL {
public:
    //CONSTRUCTORS & DESTRUCTORS
    MultiLL() : chrono_head(NULL), chrono_tail(NULL),sorted_head(NULL), sorted_tail(NULL),random_head(NULL), size_(0) {}
    // ~MultiLL() { this->destroy_list(); }
    MultiLL& operator= (const MultiLL<T>& old);
    MultiLL(const MultiLL<T>& old) { this->copy_list(old); }//copy

    //FUNCTIONS
    typedef list_iterator<T> iterator;
    void add(const T& v);


    iterator begin_chronological()
    {
        return iterator(chrono_head,1);
    }
    iterator end_chronological()
    {
        return iterator(chrono_tail->chrono_next, 1);
    }
    iterator begin_sorted()
    {
        return iterator(sorted_head,2);
    }
    iterator end_sorted()
    {
        return iterator(sorted_tail->sorted_next,2);
    }
    iterator end_random()
    {
        return iterator(NULL);
    }
    iterator begin_random();


    unsigned int size() const { return size_; }
    bool empty() const
    {
        if(size_>0)return false;
        else return true;
    }
    void clear() { this->destroy_list(); }

    iterator erase(iterator itr);


private:
    void copy_list(MultiLL<T> const & old);
    void destroy_list();

    //REPRESENTATION
    Node<T>* chrono_head;
    Node<T>* chrono_tail;

    Node<T>* sorted_head;
    Node<T>* sorted_tail;

    Node<T>* random_head;
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
void MultiLL<T>:: copy_list(MultiLL<T> const & old)
{
    size_ = old.size_;
    // Handle the special case of an empty list.
    if (size_ == 0)
    {
        chrono_head=chrono_tail=sorted_head=sorted_tail=NULL;
        return;
    }
    const iterator copier=old.begin_chronological();

    for(unsigned int i=0;i<old.size();i++,copier.ptr_=copier.ptr_->chrono_next)
    {
        this->add(copier.ptr_->value_);
    }
}
template <class T>
void  MultiLL<T>:: add(const T& v)
{
    Node<T>* new_node= new Node<T>();
    new_node->value_=v;
    if (chrono_head == NULL||size_==0)
    {
        size_++;
        //chrono_head = new MultiLL();
        chrono_head=new_node;
        chrono_tail=new_node;
        chrono_head->value_ = v;
        chrono_head->chrono_next = NULL;
        chrono_head->chrono_prev=NULL;

        sorted_head = new_node;
        sorted_tail = new_node;
        sorted_head->sorted_next=NULL;
        sorted_head->sorted_prev=NULL;

    }
    else
    {
        size_++;
        Node<T>* current;
        for (current = chrono_head; current->chrono_next != NULL; current = current->chrono_next) {}
        // current is now pointing to the last NOde
        new_node->chrono_prev=current;
        current->chrono_next = new_node;

        current->chrono_next->value_ = v;
        current->chrono_next->chrono_next = NULL;
        chrono_tail= current->chrono_next;

        //SORTED IMPLEMENTATION
        if(v<sorted_head->value_)
        {
            new_node->sorted_next=sorted_head;
            sorted_head->sorted_prev=new_node;
            sorted_head=new_node;
        }
        else if(v>sorted_tail->value_)
        {
            sorted_tail->sorted_next=new_node;
            new_node->sorted_prev=sorted_tail;
            sorted_tail=new_node;
            sorted_tail->sorted_next=NULL;
        }

        else
        {
            Node<T>* current_new;
            for(current_new = sorted_head; current_new!= NULL; current_new = current_new->sorted_next)
            {

                if(v<current_new->value_)
                {
                    new_node->sorted_next=current_new;
                    current_new->sorted_prev->sorted_next=new_node;
                    new_node->sorted_prev=current_new->sorted_prev;
                    current_new->sorted_prev=new_node;
                    break;
                }

            }
        }
    }

}
template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
    if (&old != this)
    {
        this->destroy_list();
        this->copy_list(old);
    }
    return *this;
}

template <class T>
typename MultiLL<T>::iterator MultiLL<T>:: begin_random()
{

    int temp_array[100];
    MTRand create_rand;

    for(unsigned int i=0;i<size_;i++)//get unique numbers
    {
        int temp=create_rand.randInt(size_-1);
        bool has_appeared=false;
        for(int j=0;j<i;j++)
        {
            if(temp_array[j]==temp)
            {
                has_appeared=true;
                break;
            }

        }

        while(has_appeared==true)//if appeared get another number
        {
            temp=create_rand.randInt(size_-1);
            for(int k=0; k<i;k++)
            {
                if(temp_array[k]==temp)
                {
                    has_appeared=true;
                    break;
                }
                if(k==(i-1)&&temp_array[k]!=temp)
                {
                    has_appeared=false;
                    break;
                }
            }

        }
        temp_array[i]=temp;
    }

    Node<T>* current_new;
    Node<T>* random_temp=random_head;

    for(unsigned int k=0;k<size_;k++)//assign positions
    {

        current_new = chrono_head;
        for(int j=0;j<temp_array[k];j++)
        {
            current_new = current_new->chrono_next;
        }
        if(k==0)
        {
            random_head=current_new;
            random_temp=random_head;
        }
        else
        {

            random_temp->random_next=current_new;
            random_temp=random_temp->random_next;
        }
    }
    current_new->random_next=random_head;
    return iterator(random_head,3);
}
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr)
{
    assert (size_ > 0);
    --size_;
    iterator result=itr;//
    result++;
    iterator itr_rand=itr;//
    iterator itr_rand_helper=itr;
    bool it_is_head=false;
    if(itr.ptr_==random_head)
    {
        it_is_head=true;
    }
    for(unsigned int i=0;i<=size_-1;i++)
    {
        itr_rand.ptr_= itr_rand.ptr_->random_next;
    }
    itr_rand_helper.ptr_=itr_rand_helper.ptr_->random_next;
    itr_rand.ptr_->random_next= itr_rand_helper.ptr_;
    if(it_is_head==true)
    {
        random_head=itr_rand_helper.ptr_;
    }

    //CHRONO RE-DIRECT
    // One node left in the list.
    if (itr.ptr_ == chrono_head && chrono_head == chrono_tail)
    {
        chrono_head = chrono_tail = NULL;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == chrono_head)
    {
        chrono_head = chrono_head -> chrono_next;
        chrono_head -> chrono_prev = NULL;

    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == chrono_tail)
    {
        chrono_tail = chrono_tail -> chrono_prev;
        chrono_tail -> chrono_next = NULL;

    }
    // Normal remove
    else
    {
        itr.ptr_ -> chrono_prev -> chrono_next = itr.ptr_ -> chrono_next;
        itr.ptr_ -> chrono_next -> chrono_prev = itr.ptr_ -> chrono_prev;

    }
    //re-direct sorted pointers
    if (itr.ptr_ == sorted_head && sorted_head == sorted_tail)
    {
        sorted_head = sorted_tail = NULL;
    }
    else if(itr.ptr_==sorted_tail)
    {
        sorted_tail=sorted_tail->sorted_prev;
        sorted_tail->sorted_next=NULL;
    }
    else if (itr.ptr_ == sorted_head)
    {
        sorted_head = sorted_head ->sorted_next;
        sorted_head ->sorted_prev = NULL;
    }
    else
    {
        itr.ptr_ ->sorted_prev->sorted_next = itr.ptr_ ->sorted_next;
        itr.ptr_ ->sorted_next->sorted_prev = itr.ptr_ ->sorted_prev;
    }

    delete itr.ptr_;
    return result;
}


template <class T>
void MultiLL<T>::destroy_list()
{
    if(size_==0)
        return;

    Node<T>* temp_del=chrono_head->chrono_next;
    while(temp_del!=chrono_tail)
    {
        delete temp_del->chrono_prev;
        temp_del=temp_del->chrono_next;
    }
    delete chrono_tail->chrono_prev;
    delete chrono_tail;
    chrono_head=NULL;
    chrono_tail=NULL;
    sorted_head=NULL;
    sorted_tail=NULL;
    random_head=NULL;
    temp_del=NULL;
    size_=0;
}

#endif

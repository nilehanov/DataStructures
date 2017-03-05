// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"
#include "MersenneTwister.h"

// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
    if (a.size() != b.size()) return false;
    typename std::list<T>::const_iterator a_itr = a.begin();
    typename std::list<T>::const_iterator b_itr = b.begin();
    while (a_itr != a.end()) {
        if (*a_itr != *b_itr) return false;
        a_itr++;
        b_itr++;
    }
    return true;
}


// ================================================================================
// This program stress tests the templated MultiLL container class
int main() {


    // The test data (stored in STL lists)
    std::list<std::string> songs;
    songs.push_back("hound dog");
    songs.push_back("poker face");
    songs.push_back("brown eyed girl");
    songs.push_back("let it be");
    songs.push_back("walk like an egyptian");
    songs.push_back("man in the mirror");
    songs.push_back("stairway to heaven");
    songs.push_back("dancing in the street");
    songs.push_back("every breath you take");
    songs.push_back("hotel california");
    // the same data, sorted!
    std::list<std::string> sorted_songs(songs);
    sorted_songs.sort();


    // create an empty multi-linked list and fill it with the test data
    MultiLL<std::string> my_list;
    for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
        my_list.add(*itr);
    }
    assert (songs.size() == my_list.size());
    //cout<<"Hey_25"<<endl;


    // -------------------
    // iterator tests

    // test the chronological iterator (forwards)
    std::cout << "chronological order" << std::endl;
    std::list<std::string> chrono_order;
    MultiLL<std::string>::iterator itr = my_list.begin_chronological();
    while (itr != my_list.end_chronological())
    {
        std::cout << "  " << *itr << std::endl;
        chrono_order.push_back(*itr);
        itr++;
    }
    std::cout << std::endl;
    assert (same(songs,chrono_order));


    // test the sorted order iterator (forwards)
    std::cout << "sorted order" << std::endl;
    std::list<std::string> sorted_order;
    itr = my_list.begin_sorted();
    while (itr != my_list.end_sorted())
    {
        std::cout << "  " << *itr << std::endl;
        sorted_order.push_back(*itr);
        itr++;

    }
    std::cout << std::endl;

    assert (same(sorted_songs,sorted_order));

    // test the random order iterator
    std::cout << "random order" << std::endl;
    std::list<std::string> random_order;
    itr = my_list.begin_random();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++)
    {
        std::cout << "  " << *itr << std::endl;
        random_order.push_back(*itr);
    }
    std::cout << std::endl;

    // loop through the elements a second time (the order should be the same!)
    std::list<std::string>::iterator itr2 = random_order.begin();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
        // verify that the elements repeat the order
        assert (*itr == *itr2);
    }
    std::list<std::string> random_order_check(random_order);
    random_order_check.sort();
    // verify that all of the elements appeared in the initial loop
    assert (same(sorted_songs,random_order_check));

    // test the re-randomization by creating a new random iterator
    std::cout << "random order 2" << std::endl;
    std::list<std::string> random_order2;
    itr = my_list.begin_random();
    for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
        std::cout << "  " << *itr << std::endl;
        random_order2.push_back(*itr);
    }
    std::cout << std::endl;
    // with over 3 million different possible permutations of 10
    // elements, it is highly unlikely they will be the same!
    assert (!same(random_order,random_order2));

    // -------------------
    // erase tests

    // erase the first element inserted
    itr = my_list.begin_chronological();
    assert (*itr == "hound dog");
    itr = my_list.erase(itr);
    //cout<<*itr<<endl;
    assert (*itr == "poker face");
    assert (my_list.size() == 9);
    std::cout << "erased: hound dog" << std::endl;

    // erase the second to last element in sorted order
    itr = my_list.begin_sorted();
    for (int i = 0; i < 7; i++) { itr++; }
    assert (*itr == "stairway to heaven");
    itr = my_list.erase(itr);
    assert (*itr == "walk like an egyptian");
    assert (my_list.size() == 8);
    std::cout << "erased: stairway to heaven" << std::endl;

    // erase the third element in the random order
    itr = my_list.begin_random();
    itr++;
    itr++;
    std::string tmp = *itr;
    // note that the return value of erase with a random iterator is undefined
    my_list.erase(itr);
    std::cout << "erased: " << tmp << std::endl;
    assert (my_list.size() == 7);
    assert (!my_list.empty());

    my_list.clear();
    assert (my_list.empty());
    assert (my_list.size() == 0);
    std::cout << "cleared the whole list!" << std::endl << std::endl;

    std::cout << " ***  OUTPUT FROM YOUR TEST CASES ***" << std::endl;


    // ---------------------------
    // ADD YOUR OWN TEST CASES BELOW
    //  assignment operator

    // CREATE A LIST FOR TESTING
    std::cout <<endl<< "ANIMALS: Test" << std::endl;
    std::list<std::string> animals;
    animals.push_back("dog");
    animals.push_back("opossum");
    animals.push_back("cat");
    animals.push_back("gold_fish");
    // create an empty multi-linked list and fill it with the test data
    MultiLL<std::string> my_pets;
    for (std::list<std::string>::iterator itr = animals.begin(); itr != animals.end(); itr++)
    {
        my_pets.add(*itr);
    }

    ///COPY TEST///
   // MultiLL<std::string> my_pets_copied(my_pets);
    //MultiLL<std::string>::iterator itr_test_1= my_pets_copied.begin_chronological();

    //cout<<*itr_test_1;
    //END COPY TEST///

    //////////////RAND ERASE FIRST ELEMENT/////////////
    MultiLL<std::string>::iterator  itr_rand = my_pets.begin_random();
    itr_rand = my_pets.erase(itr_rand);
    //assert(*itr_rand=="opossum");
    //////////////END RAND ERASE FIRST ELEMENT/////////////

    ////PRE-DECREMENT POST-DECREMENT   PRE-INCREMENT   POST-INCREMENT///
    MultiLL<std::string>::iterator itr_test_2= my_pets.begin_chronological();
    ++itr_test_2;
    --itr_test_2;
    itr_test_2++;
    itr_test_2--;
    ////END PRE-DECREMENT POST-DECREMENT   PRE-INCREMENT   POST-INCREMENT///

    ///DESTRUCTOR///
    my_pets.clear();
    ///END DESTRUCTOR TEST///

    // TEST W/ OTHER THAN STRINGS
    std::cout <<endl<< "nums: Test" << std::endl;
    std::list<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(4);
    // create an empty multi-linked list and fill it with the test data
    MultiLL<int> my_nums;
    for (std::list<int>::iterator itr = nums.begin(); itr != nums.end(); itr++)
    {
        my_nums.add(*itr);
    }
    my_nums.clear();
    // END TEST W/ OTHER THAN STRINGS

}

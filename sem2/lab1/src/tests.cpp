#include <gtest/gtest.h>
#include "list.h"

#include <string>

using namespace std; 



// 
// ----------------------------- ADD
// 

TEST(Add_size, Head_int) {
  List<int> mylist;

  mylist.Add(7);

  ASSERT_EQ(mylist.GetSize(), 1);
}

TEST(Add_size, Head_float) {
  List<float> mylist;

  mylist.Add(7.7);

  ASSERT_EQ(mylist.GetSize(), 1);
}

TEST(Add_size, Head_string) {
  List<string> mylist;

  mylist.Add("den");

  ASSERT_EQ(mylist.GetSize(), 1);
}


TEST(Add_size, NoHead_int) {
  List<int> mylist;

  mylist.Add(4);
  mylist.Add(7, 1);

  ASSERT_EQ(mylist.GetSize(), 2);
}

TEST(Add_size, NoHead_float) {
  List<float> mylist;

  mylist.Add(4.5);
  mylist.Add(7.7, 1);

  ASSERT_EQ(mylist.GetSize(), 2);
}

TEST(Add_size, NoHead_string) {
  List<string> mylist;

  mylist.Add("kate");
  mylist.Add("den", 1);

  ASSERT_EQ(mylist.GetSize(), 2);
}



TEST(Add_value, Head_int) {
  List<int> mylist;

  mylist.Add(7);

  ASSERT_EQ(mylist[0], 7);
}

TEST(Add_value, Head_float) {
  List<float> mylist;

  mylist.Add(7.7);

  ASSERT_EQ(to_string(mylist[0]), to_string(7.7));
}

TEST(Add_value, Head_str) {
  List<string> mylist;

  mylist.Add("den");

  ASSERT_EQ(mylist[0], "den");
}


TEST(Add_value, NoHead_int) {
  List<int> mylist;

  mylist.Add(4);
  mylist.Add(7, 1);

  ASSERT_EQ(mylist[1], 7);
}

TEST(Add_value, NoHead_float) {
  List<float> mylist;

  mylist.Add(4.5);
  mylist.Add(7.7, 1);

  ASSERT_EQ(to_string(mylist[1]), to_string(7.7));
}

TEST(Add_value, NoHead_str) {
  List<string> mylist;

  mylist.Add("kate");
  mylist.Add("den", 1);

  ASSERT_EQ(mylist[1], "den");
}



// 
// ----------------------------- DEL
// 

TEST(Del_size, Head_int) {
  List<int> mylist;

  mylist.Add(7);
  mylist.Del();

  ASSERT_EQ(mylist.GetSize(), 0);
}

TEST(Del_size, Head_float) {
  List<float> mylist;

  mylist.Add(7.7);
  mylist.Del();

  ASSERT_EQ(mylist.GetSize(), 0);
}

TEST(Del_size, Head_str) {
  List<string> mylist;

  mylist.Add("den");
  mylist.Del();

  ASSERT_EQ(mylist.GetSize(), 0);
}


TEST(Del_size, NoHead_int) {
  List<int> mylist;

  mylist.Add(3);
  mylist.Add(4);
  mylist.Add(7, 2);
  mylist.Del(1);

  ASSERT_EQ(mylist.GetSize(), 2);
}

TEST(Del_size, NoHead_float) {
  List<float> mylist;

  mylist.Add(3.4);
  mylist.Add(4.5);
  mylist.Add(7.7, 2);
  mylist.Del(1);

  ASSERT_EQ(mylist.GetSize(), 2);
}

TEST(Del_size, NoHead_str) {
  List<string> mylist;

  mylist.Add("fedya");
  mylist.Add("kate");
  mylist.Add("den", 2);
  mylist.Del(1);

  ASSERT_EQ(mylist.GetSize(), 2);
}



TEST(Del_value, NoHead_int) {
  List<int> mylist;

  mylist.Add(3);
  mylist.Add(4);
  mylist.Add(7, 2);
  mylist.Del(1);

  ASSERT_EQ(mylist[0], 4);
  ASSERT_EQ(mylist[1], 7);
}

TEST(Del_value, NoHead_float) {
  List<float> mylist;

  mylist.Add(3.4);
  mylist.Add(4.5);
  mylist.Add(7.7, 2);
  mylist.Del(1);

  ASSERT_EQ(to_string(mylist[0]), to_string(4.5));
  ASSERT_EQ(to_string(mylist[1]), to_string(7.7));
}

TEST(Del_value, NoHead_str) {
  List<string> mylist;

  mylist.Add("fedya");
  mylist.Add("kate");
  mylist.Add("den", 2);
  mylist.Del(1);

  ASSERT_EQ(mylist[0], "kate");
  ASSERT_EQ(mylist[1], "den");
}



// 
// ----------------------------- SORT
// 

TEST(Sort, Int) {
  List<int> mylist;

  mylist.Add(8);
  mylist.Add(14);
  mylist.Add(-5);
  mylist.Add(0);
  mylist.Add(-13);
  mylist.Add(99);
  mylist.Add(7);
  mylist.Sort();

  for (int i{0}; i < mylist.GetSize() - 1; i++)
    ASSERT_LE(mylist[i], mylist[i + 1]);
}

TEST(Sort, Float) {
  List<float> mylist;

  mylist.Add(8.56);
  mylist.Add(14);
  mylist.Add(-5.2);
  mylist.Add(0);
  mylist.Add(-13.4);
  mylist.Add(99.9);
  mylist.Add(7.7);
  mylist.Sort();

  for (int i{0}; i < mylist.GetSize() - 1; i++)
    ASSERT_LE(mylist[i], mylist[i + 1]);
}

TEST(Sort, Str) {
  List<string> mylist;

  mylist.Add("roga");
  mylist.Add("Stasik");
  mylist.Add("4monya");
  mylist.Add("nik");
  mylist.Add("fedya");
  mylist.Add("kate");
  mylist.Add("Den");
  mylist.Sort();

  for (int i{0}; i < mylist.GetSize() - 1; i++)
    ASSERT_LE(mylist[i], mylist[i + 1]);
}



// 
// ----------------------------- SEARCH
// 

TEST(Search, Int){
  List<int> mylist;

  mylist.Add(8);
  mylist.Add(14);
  mylist.Add(-5);
  mylist.Add(0);
  mylist.Add(-13);
  mylist.Add(99);
  mylist.Add(7);

  ASSERT_EQ(mylist[mylist.Search(-13)], -13);
}

TEST(Search, Float){
  List<float> mylist;

  mylist.Add(8.56);
  mylist.Add(14);
  mylist.Add(-5.2);
  mylist.Add(0);
  mylist.Add(-13.4);
  mylist.Add(99.9);
  mylist.Add(7.7);

  ASSERT_EQ(to_string(mylist[mylist.Search(-13.4)]), to_string(-13.4));
}

TEST(Search, Str){
  List<string> mylist;

  mylist.Add("roga");
  mylist.Add("Stasik");
  mylist.Add("4monya");
  mylist.Add("nik");
  mylist.Add("fedya");
  mylist.Add("kate");
  mylist.Add("Den");

  ASSERT_EQ(mylist[mylist.Search("fedya")], "fedya");
}



// 
// ----------------------------- UNION
// 

TEST(Union, Size_int){
  List<int> A_list;
  List<int> B_list;
  List<int> C_list;

  A_list.Add(8);
  A_list.Add(14);
  A_list.Add(-5);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99);
  A_list.Add(7);

  B_list.Add(2);
  B_list.Add(-1);
  B_list.Add(-5);
  B_list.Add(46);
  B_list.Add(99);
  B_list.Add(-5);

  C_list = A_list + B_list;

  ASSERT_EQ(C_list.GetSize(), 11);
}

TEST(Union, Size_str){
  List<string> A_list, B_list, C_list;

  A_list.Add("roga");
  A_list.Add("Stasik");
  A_list.Add("4monya");
  A_list.Add("nik");
  A_list.Add("fedya");
  A_list.Add("kate");
  A_list.Add("Den");

  B_list.Add("ddfd");
  B_list.Add("Stasik");
  B_list.Add("4monya");
  B_list.Add("moly");
  B_list.Add("nofedy");
  B_list.Add("Stasik");

  C_list = A_list + B_list;

  ASSERT_EQ(C_list.GetSize(), 11);
}

TEST(Union, Size_float){
  List<float> A_list, B_list, C_list;

  A_list.Add(8.5);
  A_list.Add(14.6);
  A_list.Add(-5.23);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99.4);
  A_list.Add(7.7);

  B_list.Add(2);
  B_list.Add(-1.1);
  B_list.Add(-5.23);
  B_list.Add(46);
  B_list.Add(99.4);
  B_list.Add(-5.23);

  C_list = A_list + B_list;

  ASSERT_EQ(C_list.GetSize(), 11);
}


TEST(Union, A_in_result_int){
  List<int> A_list;
  List<int> B_list;
  List<int> C_list;

  A_list.Add(8);
  A_list.Add(14);
  A_list.Add(-5);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99);
  A_list.Add(7);

  B_list.Add(2);
  B_list.Add(-1);
  B_list.Add(-5);
  B_list.Add(46);
  B_list.Add(99);
  B_list.Add(-5);

  C_list = A_list + B_list;
  for (int i{0}; i < A_list.GetSize(); i++)
    ASSERT_NE(C_list.Search(A_list[i]), -1);

}

TEST(Union, A_in_result_str){
  List<string> A_list, B_list, C_list;

  A_list.Add("roga");
  A_list.Add("Stasik");
  A_list.Add("4monya");
  A_list.Add("nik");
  A_list.Add("fedya");
  A_list.Add("kate");
  A_list.Add("Den");

  B_list.Add("ddfd");
  B_list.Add("Stasik");
  B_list.Add("4monya");
  B_list.Add("moly");
  B_list.Add("nofedy");
  B_list.Add("Stasik");

  C_list = A_list + B_list;

  for (int i{0}; i < A_list.GetSize(); i++)
    ASSERT_NE(C_list.Search(A_list[i]), -1);
}

TEST(Union, A_in_result_float){
  List<float> A_list, B_list, C_list;

  A_list.Add(8.5);
  A_list.Add(14.6);
  A_list.Add(-5.23);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99.4);
  A_list.Add(7.7);

  B_list.Add(2);
  B_list.Add(-1.1);
  B_list.Add(-5.23);
  B_list.Add(46);
  B_list.Add(99.4);
  B_list.Add(-5.23);

  C_list = A_list + B_list;

  for (int i{0}; i < A_list.GetSize(); i++)
    ASSERT_NE(C_list.Search(A_list[i]), -1);
}



// 
// ----------------------------- INTERSECTION
// 

TEST(Intersection, Size_int){
  List<int> A_list;
  List<int> B_list;
  List<int> C_list;

  A_list.Add(8);
  A_list.Add(14);
  A_list.Add(-5);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99);
  A_list.Add(7);

  B_list.Add(2);
  B_list.Add(-1);
  B_list.Add(-5);
  B_list.Add(46);
  B_list.Add(99);
  B_list.Add(-5);

  C_list = A_list ^ B_list;

  ASSERT_EQ(C_list.GetSize(), 2);
}

TEST(Intersection, Size_str){
  List<string> A_list, B_list, C_list;

  A_list.Add("roga");
  A_list.Add("Stasik");
  A_list.Add("4monya");
  A_list.Add("nik");
  A_list.Add("fedya");
  A_list.Add("kate");
  A_list.Add("Den");

  B_list.Add("ddfd");
  B_list.Add("Stasik");
  B_list.Add("4monya");
  B_list.Add("moly");
  B_list.Add("nofedy");
  B_list.Add("Stasik");

  C_list = A_list ^ B_list;

  ASSERT_EQ(C_list.GetSize(), 2);
}

TEST(Intersection, Size_float){
  List<float> A_list, B_list, C_list;

  A_list.Add(8.5);
  A_list.Add(14.6);
  A_list.Add(-5.23);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99.4);
  A_list.Add(7.7);

  B_list.Add(2);
  B_list.Add(-1.1);
  B_list.Add(-5.23);
  B_list.Add(46);
  B_list.Add(99.4);
  B_list.Add(-5.23);

  C_list = A_list ^ B_list;

  ASSERT_EQ(C_list.GetSize(), 2);
}


TEST(Intersection, Result_in_AandB_int){
  List<int> A_list;
  List<int> B_list;
  List<int> C_list;

  A_list.Add(8);
  A_list.Add(14);
  A_list.Add(-5);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99);
  A_list.Add(7);

  B_list.Add(2);
  B_list.Add(-1);
  B_list.Add(-5);
  B_list.Add(46);
  B_list.Add(99);
  B_list.Add(-5);

  C_list = A_list ^ B_list;


  for (int i{0}; i < C_list.GetSize(); i++){
    ASSERT_NE(A_list.Search(C_list[i]), -1);
    ASSERT_NE(B_list.Search(C_list[i]), -1);
  }
}

TEST(Intersection, Result_in_AandB_str){
  List<string> A_list, B_list, C_list;

  A_list.Add("roga");
  A_list.Add("Stasik");
  A_list.Add("4monya");
  A_list.Add("nik");
  A_list.Add("fedya");
  A_list.Add("kate");
  A_list.Add("Den");

  B_list.Add("ddfd");
  B_list.Add("Stasik");
  B_list.Add("4monya");
  B_list.Add("moly");
  B_list.Add("nofedy");
  B_list.Add("Stasik");

  C_list = A_list ^ B_list;


  for (int i{0}; i < C_list.GetSize(); i++){
    ASSERT_NE(A_list.Search(C_list[i]), -1);
    ASSERT_NE(B_list.Search(C_list[i]), -1);
  }
}

TEST(Intersection, Result_in_AandB_float){
  List<float> A_list, B_list, C_list;

  A_list.Add(8.5);
  A_list.Add(14.6);
  A_list.Add(-5.23);
  A_list.Add(0);
  A_list.Add(-13);
  A_list.Add(99.4);
  A_list.Add(7.7);

  B_list.Add(2);
  B_list.Add(-1.1);
  B_list.Add(-5.23);
  B_list.Add(46);
  B_list.Add(99.4);
  B_list.Add(-5.23);

  C_list = A_list ^ B_list;


  for (int i{0}; i < C_list.GetSize(); i++){
    ASSERT_NE(A_list.Search(C_list[i]), -1);
    ASSERT_NE(B_list.Search(C_list[i]), -1);
  }
}



// 
// ----------------------------- INCORRECT INPUT
// 

TEST(Incorrect, Add){
  List<int> list;

  ASSERT_THROW({
    list.Add(7, -10);
  }, invalid_argument);
}

TEST(Incorrect, Del){
  List<int> list;

  ASSERT_THROW({
    list.Del(-10);
  }, invalid_argument);
}

TEST(Incorrect, Search_data){
  List<int> list;

  list.Add(7);
  list.Add(1);
  ASSERT_THROW({
    list[490];
  }, invalid_argument);
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

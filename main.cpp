
//  TODO(mosrour_tafadar):  This project  is about 
//  movie/book/ songs recommendations  base on user  interest
//  Project 1 Starter Code - Recommendations
//  Author: Mosrour Tafadar
//  spring 2021
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
 //creative component command

// "data"  -> this will show all the rating as a nested form
//
// "Total Sum" -> this will add up all the rating from
// all user and show print the total sum
//
// "top rated" -> this will show how many and name of
// movie/songs/podcats were  rated 5/5 by current user
//
// "medium rated" -> this will show how many and name of
// movie/songs/podcats were  rated 3/5 by current user
//
// "ok rated" -> this will show how many and name
// movies/songs/podcats were  rated 1/5 by current user
//
// "not watched" ->  this will show how many and name
// movie/songs/podcats were   rated 0 which means not rated
//
// "low rated" -> this will show how many  and name of
// movies were rated -1/5 by current user
//
// "bad rated" -> this will show up how many  and
// name movies were rated -3/5  by current user
//
// "terribly rated" -> this will show how many and
// name of movies are rated -5/5 by currentUser user
//
// "name" -> this will only show all the user name
// "elements" -> this will show what are the elements in the file
//

using namespace std;

int search(vector < string > x, string name);
void statmentNotFound();
void ChekingFIle(ifstream & file);
void readFile(ifstream & infile, string file, vector < string > & Mname);
void readFile2(ifstream & onfile, string file, vector < string > & name,
               vector < string > & rating, vector < vector < int > > & data);

void displayAnother(vector < string > x,      vector < string > y);
void display(vector < string > x);
void operationIncomplete();
void showCommand(vector < vector < int > > & data,
                 vector < string > & Mname, int & index);
void printCommand(vector < string > & Mname);
void printUsers(vector < string > & name);
void ratingChange(vector < vector < int > > & data,
                  vector < string > & Mname, int index);
void summation(vector < vector < int > > & data,
               vector < int > & sumV);
bool contains(int target, vector < int > v);
void getSumIndexSorted(vector < int > & rating,
                       vector < int > & sortedSumIndex);
void basicRecommendation(vector < vector < int > > & data,
                         vector < string > & Mname, vector < int >
                         &sortedSumIndex, int index);
void product(vector < vector < int > > & data,
             vector < int > & productV, int index);
void maximumMatch(vector < int > & productV, vector < string > & name,
                  string currentUser, int & advance_index);

void nameF(vector < string > & name, string currentUser);

void elementsF(vector < string > & Mname, string currentUser);

void allSum(vector < vector < int > > & data, string currentUser);

void dataShow(vector < vector < int > > & data, string currentUser);

void teriblyRated(vector < vector < int > > & data, int &index,
                  string currentUser, vector < string > & Mname);

void badlyRated(vector < vector < int > > & data, int & index,
                string currentUser, vector < string > & Mname);

void lowRated(vector < vector < int > > & data, int & index,
              string currentUser, vector < string > & Mname);

void okRated(vector < vector < int > > & data, int & index,
             string currentUser, vector < string > & Mname);

void noRated(vector < vector < int > > & data, int & index,
             string currentUser, vector < string > & Mname);

void mediumRated(vector < vector < int > > & data, int & index,
                 string currentUser, vector < string > & Mname);

void topRated(vector < vector < int > > & data, int & index,
              string currentUser, vector < string > & Mname);
void totalFailur();
void NotWatchedFailur();
void Failur();

int main() {
  vector < string > Mname;  //holding movie podcast or   songs
  vector < string > name;  //holding rater/customer name
  vector < string > rating;  //holding  rating of the customer
  vector < vector < int > > data;  //this function hold nested rating as whole
  vector < int > sumV;  //this vector hold summation
  vector < int > sortedSumIndex;  // this rvector hold indexes base on data highest to lowest
  vector < int > productV;  // this  vector hold  dot product

  bool loguser;  // keeping track of login/logout
  int x;
  string currentUser;
  int index = 0;

  cout << "To start the app, load the data." << endl;
  cout << "Type \"load itemsFile ratingsFile\" and press enter." << endl;
  cout << endl;

  string cmd;
  cout << "Enter command or # to quit: ";
  cin >> cmd;

  while (cmd != "#") {

    if (cmd == "load") {

      string filename1; //declaring files to let user input
      string filename2;

      cin >> filename1;
      cin >> filename2;

      ifstream infile(filename1);
      readFile(infile, filename1, Mname);  //reading  movies/podcasts/ songs file
      ifstream onfile(filename2);
      readFile2(onfile, filename2, name, rating, data);  //reading  rating along with customer name file

      cout << endl;
      display(Mname);  //displaying movies/podcasts/songs file
      cout << endl;
      displayAnother(name, rating);  //displaying user along with their rating
      cout << endl;

      cout << "Welcome to the Recommendations App!" << endl;
    } else if (cmd == "login") {

      string userName;
      cin.ignore(); //to ignore  whitespace
      getline(cin, userName);

      x = search(name, userName);  //alling search function 
        //to check whether the  user exist

      if (x == -1) {
        loguser = false;
        statmentNotFound();  //if user account not found in the folder
      } else {
        currentUser = name[x];
        index = x;
        cout << "Success." << endl;
        cout << "Logged in as: " << currentUser << endl;
        loguser = true;
      }
    } else if (cmd == "show" && loguser == false) {  //if command entered without logging in
      operationIncomplete();
    } else if (cmd == "show" && loguser == true) {  //shows movies that  user rated

      cout << currentUser << "'s Ratings:" << endl;
      showCommand(data, Mname, index);  //calling show function
      cout << endl;
      cout << "Logged in as: " << currentUser << endl;
    } else if (cmd == "print" && loguser == false) {  // In this command printing 
        //items && users without logging in information

      string temp;
      cin >> temp;

      if (temp == "items") {
        printCommand(Mname);  // calling printCommand function to
          //print  movies/songs/books/podcats
        cout << endl;
        cout << "Logged in as: N/A " << endl;
      } else if (temp == "users") {
        printUsers(name);  //calling printUsers function to  print users name
        cout << endl;
        cout << "Logged in as: N/A " << endl;
      }
    } else if (cmd == "print" && loguser == true) {  // In this command printing 
        //items && users with logging in information

      string temp;
      cin >> temp;

      if (temp == "items") {
        printCommand(Mname);
        cout << endl;
        cout << "Logged in as: " << currentUser << endl;
      } else if (temp == "users") {
        printUsers(name);
        cout << endl;
        cout << "Logged in as: " << currentUser << endl;
      }

    } else if (cmd == "add") { //In this command  I am add new user and rating,

      string temp;
      cin >> temp;
      if (temp == "user") {

        string username;
        cout << "Please enter the username: ";
        cin.ignore(); // to Ignore the whitespace
        getline(cin, username);

        name.push_back(username);  // push back the username into name vector
        currentUser = name[name.size() - 1]; // 
        index = name.size() - 1;

        vector < int > temp;  // a temp vector

        for (int i = 0; i < Mname.size(); i++) {
          temp.push_back(0);
        }

        data.push_back(temp);  // puttting it as nested vector to caluculate 
          //mathemthically  (basic and advanced command)
        loguser = true;
        cout << "Logged in as: " << currentUser << endl;
      } else if (temp == "rating" && loguser == false) {  //can't  add rating without login information

        operationIncomplete();
      } else if (temp == "rating" && loguser == true) {

        ratingChange(data, Mname, index);  // caling ratingChange 
          //function to change  the rating
        cout << "Logged in as: " << currentUser << endl;

      }

    } else if (cmd == "basic" && loguser == false) {  // we can't get 
        //rececommendation without login information
      operationIncomplete();
    } else if (cmd == "basic" && loguser == true) {
      summation(data, sumV);  // summing up rating column by comun and 
        //putting them into sumV vector which gives average
      cout << endl;

      getSumIndexSorted(sumV, sortedSumIndex);  // this will return indexes base
        //on subV vector higest to lowest
      cout << endl;

      cout << "Basic recommendations:" << endl;
      basicRecommendation(data, Mname, sortedSumIndex, index);  // and base on the 
        //SumV it will give top 5 movies
      cout << endl;
      cout << "Logged in as: " << currentUser << endl;

      sumV.clear();
      sortedSumIndex.clear();
        // clearing this vector so that when we 
        //login some one else it hold those values
    } else if (cmd == "advanced" && loguser == false) {  // can't get advance 
        //recommendation without login information
      operationIncomplete();
    } else if (cmd == "advanced" && loguser == true) {
      int advance_index = 0;
      product(data, productV, index);  
        // getting product of 
        //the user that login with all other user
      maximumMatch(productV, name, currentUser, advance_index);  
        // taking the best match with the user 
        //also avoiding dummy index 

      vector < int > bestMatchUserRating;
      bestMatchUserRating = data[advance_index];  // putting best match user rating here
      vector < int > bestMatchSorted;  // sorting Index of the  best match user information
      getSumIndexSorted(bestMatchUserRating, bestMatchSorted);

      int val;
      int count = 0;

      cout << "Advanced recommendations:" << endl;

      for (int i = 0; i < bestMatchUserRating.size(); i++) {
        if (bestMatchUserRating[i] != 0 || bestMatchUserRating[i] == 0) {
          val = bestMatchSorted[i]; //  giving the highest index to best match sorted  to val
          if (data[index][val] == 0) { // id that index movie has not watched yet
            cout << Mname[val] << endl;  // print that movie name
            count++;

            if (count == 5) {  //only 5 required, terminate if  count is 5
              break;
            }
          }
        }
      }

      cout << endl;
      cout << "Logged in as: " << currentUser << endl;
      bestMatchSorted.clear();
      productV.clear();
      bestMatchUserRating.clear();

    } else if (cmd == "elements" && loguser == false) {  // can't print element without login information
      operationIncomplete();
    } else if (cmd == "elements" && loguser == true) {  // priting elements in  a file
      elementsF(Mname, currentUser);
    } else if (cmd == "data" && loguser == false) {
        // can't print rating without login information
      operationIncomplete();
    } else if (cmd == "data" && loguser == true) {  // priting all rating together
      dataShow(data, currentUser);
    } else if (cmd == "name" && loguser == false) {
        // can't print he user information without login
      operationIncomplete();
    } else if (cmd == "name" && loguser == true) {
      nameF(name, currentUser);
    } else if (cmd == "Total" && loguser == false) {
      totalFailur();
    } else if (cmd == "Total" && loguser == true) {  // priting all together
        //the total sum of rating
      allSum(data, currentUser);
    } else if (cmd == "top" && loguser == false) {
      Failur();
    } else if (cmd == "top" && loguser == true) { 
        // counting  top rated movies 5/5 movie  by specfic user
      topRated(data, index, currentUser, Mname);
    } else if (cmd == "medium" && loguser == false) {
      Failur();
    } else if (cmd == "medium" && loguser == true) {
        // counting averag rated movies by specific user 3/5
      mediumRated(data, index, currentUser, Mname);
    } else if (cmd == "ok" && loguser == false) {
      Failur();
    } else if (cmd == "ok" && loguser == true) {  // counting ok rated movies by specific user 1/5
      okRated(data, index, currentUser, Mname);
    } else if (cmd == "Not" && loguser == false) {  // counting if the user have not watch/read
      NotWatchedFailur();
    } else if (cmd == "not" && loguser == true) {
      noRated(data, index, currentUser, Mname);
    } else if (cmd == "low" && loguser == false) {
      Failur();
    } else if (cmd == "low" && loguser == true) {
        // couting  low rated  movies by user
      lowRated(data, index, currentUser, Mname);
    } else if (cmd == "bad" && loguser == false) {
      Failur();
    } else if (cmd == "bad" && loguser == true) {  // counting -3/5 rated movies
      badlyRated(data, index, currentUser, Mname);
    } else if (cmd == "terribly" && loguser == false) {
      Failur();
    } else if (cmd == "terribly" && loguser == true) {
        // user absulately this movies
      teriblyRated(data, index, currentUser, Mname);
    }

    cout << "Enter command or # to quit: ";
    cin >> cmd;

    cout << endl;
    cout << "-----------------------------" << endl;
    cout << endl;

  }
  cout << "Thank you for using the Recommendations app!" << endl;
}

// this function will  will loop through the name
// if the name found then it will return the index
// if not found it will return -1
int search(vector < string > x, string name) {

  for (int i = 0; i < x.size(); i++) {
    if (name == x[i]) {
      return i;
    }
  }
  return -1;

}

//
// if a user does not exist in given vector
//  return this statement
//
void statmentNotFound() {
  cout << "User not found, please try again." << endl;
  cout << "Logged in as: N/A" << endl;
}
//
// if a file does not exist then show following stament
//
void ChekingFIle(ifstream & file) {

  if (!file.good()) {
    cout << "This file does exist please try again" << endl;
  }
}

void readFile(ifstream & infile, string file, vector < string > & Mname) {

  string movie;
  ChekingFIle(infile);  // calling function to check
    //whether the file is good or no
  while (!infile.eof()) {
    getline(infile, movie);
    if (!infile.fail()) {
      Mname.push_back(movie);
    }
  }
}

// this function read two values and   from
//  input and assign to vector
// data is nested vector

void readFile2(ifstream & onfile, string file, vector < string >
               &name, vector < string > & rating, vector < vector < int > > & data) {

  string customer_name;
  string customer_rating;
  ChekingFIle(onfile);  // calling function to
    //check whether its good or no

  while (!onfile.eof()) {
    getline(onfile, customer_name);
    getline(onfile, customer_rating);

    if (!onfile.fail()) {
      name.push_back(customer_name);
      rating.push_back(customer_rating);

      vector < int > temp;
      int ratings;

      istringstream buffer(customer_rating);

      while (buffer >> ratings) {
        temp.push_back(ratings);
      }

      data.push_back(temp);  // putting temp vector  to data
        // which  is nested rating
    }
  }
}

// creating another function  for nested rating;
// this function will display  ratings
// it also display name
void displayAnother(vector < string > x, vector < string > y) {
  cout << "Reading ratings file..." << endl;
  for (int i = 0; i < x.size(); i++) {
    cout << x[i] << endl;
    cout << y[i] << endl;
  }
}

// this function will display  reading items
void display(vector < string > x) {

  cout << "Reading items file..." << endl;
  for (int i = 0; i < x.size(); i++) {
    cout << x[i] << endl;
  }
}

//
// show this when  a login failed
//
void operationIncomplete() {

  cout << "To complete the operation, you must first login." << endl;
  cout << "Type \"login username\". " << endl;
  cout << endl;
  cout << "Logged in as: N/A" << endl;
}

//
// this function  takes a nested vector
// and a index and another string vector
// print the element of the string vector
// followed by nested vector at given index
//
void showCommand(vector < vector < int > > & data,
                 vector < string > & Mname, int & index) {
  for (int i = 0; i < data[index].size(); i++) {
    if (data[index].at(i) != 0) {
      cout << Mname[i] << ", " << data[index].at(i) << "/5" << endl;
    }
}
}
//
// this function takes a vector and returns
// the element of it with numbers
//
void printCommand(vector < string > & Mname) {
  for (int i = 0; i < Mname.size(); i++) {
    cout << i << ". " << Mname[i] << endl;
}
}
//
// this function  takes vector returns   its all element
//
void printUsers(vector < string > & name) {
  for (int i = 0; i < name.size(); i++) {
    cout << name[i] << endl;
}
}
//
// this function updates the rating base on user input
//
void ratingChange(vector < vector < int > > & data,
                  vector < string > & Mname, int index) {

  int number;
  cout << "Item number to add/change rating: ";
  cin >> number;
  cout << "Add the rating for " << Mname[number] << ": ";
  int rate;
  cin >> rate;
  data[index][number] = rate;

}
//
// this function  take a nested vector
// its sum up  column by column and assign that to another vector
//
void summation(vector < vector < int > > & data, vector < int > & sumV) {
  int sum;
  for (int i = 0; i < data[0].size(); i++) {
    sum = 0;
    for (int j = 0; j < data.size(); j++) {
      sum = sum + data[j][i];
    }
    sumV.push_back(sum);
}

}

//
// this function is a helper function of getSumIndexSorted
// its check whether target value already in the given vector
bool contains(int target, vector < int > v) {
  for (int i: v) {
    if (i == target) {
      return true;
    }
}
  return false;
}

//
// this function will take a int type vector and
// a vector which will hold sorted index
//
void getSumIndexSorted(vector < int > & rating,
                       vector < int > & sortedSumIndex) {

  for (int i = 0; i < rating.size(); i++) {
    int max = -9999;
    int maxIndex = -1;

   for (int j = 0; j < rating.size(); j++) {
      if (rating[j] > max && !contains(j, sortedSumIndex)) {
        max = rating[j];
        maxIndex = j;
      }
    }
    sortedSumIndex.push_back(maxIndex);
  }

}

// this function take a nested  vector , a name of product
// and its also take index which refers to current user
// it print of best 5 movie base on  best average
void basicRecommendation(vector < vector < int > > & data,
                        vector < string > & Mname, vector < int > & 
                         sortedSumIndex, int index) {
  int val;
  int count = 0;
  for (int i = 0; i < Mname.size(); i++) {
    val = sortedSumIndex[i];
    if (data[index][val] == 0) {
      cout << Mname[val] << endl;
      count++;
    }
    if (count == 5) {
      break;
    }
  }
}
//
// this this function  will get dot  product
// the index will be the one that multiply 
// and sum with other values
//
void product(vector < vector < int > > & data,
             vector < int > & productV, int index) {
  int product;
  for (int i = 0; i < data.size(); i++) {
    product = 0;

    for (int j = 0; j < data[index].size(); j++) {
      product += data[index][j] * data[i][j];
    }
    productV.push_back(product);
  }
}
//
// pre- condition
// maximum index can not be index value
// post condition
// it should return the closet number of maximum
//
void maximumMatch(vector < int > & productV,
                 vector < string > & name, string currentUser, int & advance_index) {

  int max = -99999;
  for (int i = 0; i < productV.size(); i++) {
    if (productV[i] > max) {
      if (name[i] != currentUser) {
       max = productV[i];
        advance_index = i;
      }
    }
  }
}

//
//###################################################
//#################################################//
// the following function  are for creative component

void allSum(vector < vector < int > > & data, string currentUser) {
  string temp;
  int sum = 0;
  cin >> temp;
  if (temp == "Sum") {
    for (int i = 0; i < data.size(); i++) {
      for (int j = 0; j < data[i].size(); j++) {
        sum = sum + data[i][j];

      }
    }
  }

 cout << "The total sum of all rating is  " << sum << endl;
  cout << "Logged in as: " << currentUser << endl;
}

void dataShow(vector < vector < int > > & data, string currentUser) {
  cout << endl;
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      cout << data[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Logged in as: " << currentUser << endl;
}

void topRated(vector < vector < int > > & data,
              int & index, string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == 5) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " rated " << count << " elements " ;
  cout << " 5/5  from this list." << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function  returns  number and  
// name that are rated by 1/5
//
void mediumRated(vector < vector < int > > & data,
                 int & index, string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == 3) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " rated " << count << " elements ";
  cout << " 3/5  from this list." << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function  returns  number and
// name that are rated by 1/5
//
void okRated(vector < vector < int > > & data,
             int & index, string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == 1) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " rated " << count << " elements " ;
  cout << " 1/5  from this list." << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function  returns  number and  name that
// are rated by 0/5
//
void noRated(vector < vector < int > > & data, int & index,
             string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "watched") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == 0) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " have not watch this ";
  cout <<"number of items " << count << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function  returns  number and  name 
// that are rated by -1/5
//
void lowRated(vector < vector < int > > & data, int &index,
              string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == -1) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " rated " << count << " elements ";
  cout<< " -1/5  from this list." << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function  returns  number and
// name that are rated by -3/5
//
void badlyRated(vector < vector < int > > & data, int &index,
                string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == -3) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
  cout << endl;
  cout << currentUser << " rated " << count << " elements ";
  cout << "-3/5  from this list." << endl;
  cout << "Logged in as: " << currentUser << endl;
}

//
// this functions  returns  name and number
//  of teribly Rated   movies  -5/5
//
void teriblyRated(vector < vector < int > > & data,
                  int & index, string currentUser, vector < string > & Mname) {
  string temp;
  int count = 0;
  cin >> temp;
  if (temp == "rated") {
    for (int i = 0; i < data[index].size(); i++) {
      if (data[index][i] == -5) {
        cout << Mname[i] << endl;
        count++;
      }
    }
  }
     cout << endl;
    cout << currentUser << " rated " << count << " elements ";
    cout << "-5/5  from this list." << endl;
    cout << "Logged in as: " << currentUser << endl;
}
//
// this function print out names of the users
// with index which start from 1
//
void nameF(vector < string > & name, string currentUser) {
  cout << endl;
  for (int i = 0; i < name.size(); i++) {
    cout << i + 1 << ", " << name[i] << endl;
  }
  cout << "Logged in as: " << currentUser << endl;
}

//
// this function print out element for current users
//
void elementsF(vector < string > & Mname, string currentUser) {
  cout << endl;
  for (int i = 0; i < Mname.size(); i++) {
    cout << Mname[i] << endl;
  }
  cout << endl;
  cout << "Logged in as: " << currentUser << endl;
}

// this function shows  user  has not login yet so can't
// perform what they are trying to do
void totalFailur() {
  string temp;
  cin >> temp;
  if (temp == "Sum") {
    operationIncomplete();
  }
}

// this function shows  user  has not login yet so can't
// perform what they are trying to do
void Failur() {
  string temp;
  cin >> temp;
  if (temp == "rated") {
    operationIncomplete();
  }
}

// this function shows  user  has not login yet so can't
// perform what they are trying to do
void NotWatchedFailur() {
  string temp;
  cin >> temp;
  if (temp == "Watched") {
    operationIncomplete();
  }
}

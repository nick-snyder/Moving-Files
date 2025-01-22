#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

double doit(istream &in)
{
   // YOUR CODE GOES HERE
   vector<double> rainfall;

   // convert istream to stringstream
   string s;
   getline(in, s);
   stringstream ss(s);

   double x;
   while (!ss.fail())
   {
      ss >> x;
      if ((x == -99) || (ss.fail()))
      {
         break;
      }
      else if (x >= 0)
      {
         rainfall.push_back(x);
      }
   }

   // calculate sum of vector
   double sum = 0;
   for (int i = 0; i < rainfall.size(); i++) 
   {
      sum += rainfall.at(i);
   }

   if (rainfall.size() == 0)
   {
      return 0;
   }

   // divide sum by size of vector
   double result = sum / rainfall.size();

   //cout << "sum: " << sum << "\nsize: " << rainfall.size() << endl;

   // return result
   return result;
}

// Testing framework for doit function
int main(int argc, char *argv[])
{
   cout << "------Basic test------" << endl;
   string data[] = {"1 2 3 -99",
                  "1 2 3 0 -6 -99",
                  "-99"
                  };

   for (string &in : data)
   {
      stringstream input(in);
      try
      {
         cout << "Your result: " << doit(input) << endl;
      } catch (int e)
      {
         cout << "Call threw an exception!" << endl;
      }
   }

   cout << "------Test using input data------" << endl;
   double result = doit(cin);
   cout << "Your result: " << result << endl;
}

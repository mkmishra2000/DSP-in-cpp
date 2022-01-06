#include <iostream>
#include <vector>
#include <iterator>
#include "MyMatrixOperation.h"


using namespace std;



// Function for printing the vector on the console output.
void PrintVectorDouble(vector<double> vectrIn)
{
    std::copy(begin(vectrIn), end(vectrIn),  std::ostream_iterator<double>(std::cout, " , "));
    cout<<endl;
}


int main()
{
    
    return 0;
}
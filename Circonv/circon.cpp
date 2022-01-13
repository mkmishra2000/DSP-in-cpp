
#include<iostream>
#include <vector>
#include <iterator>
#include "MyMatrixOperation.h"

using namespace std;


// Function for printing the vector on the console output.
void PrintVectorDouble(vector<double> vectr)
{
    std::copy(begin(vectr), end(vectr),  std::ostream_iterator<double>(std::cout, "   "));
    cout<<endl;
}


// Function for shifting the elements in the vector 
// Input is the vector of finite length.
// Output is the shifted version of the vector.
// If type =0 left shift otherwise rightshift 
vector<double> ShiftingOperation(vector<double>xSignal, const int type)
{
    double temp;
    double moving;
    if(type ==0){
        moving = xSignal[0];
        temp = xSignal[1];
        for(int i =1;i <xSignal.size(); i++){
            xSignal[i-1] = temp;
            temp = xSignal[i+1];
        }
        xSignal[xSignal.size()-1] = moving;

    }else if(type ==1){
        moving = xSignal[xSignal.size()-1];
        temp = xSignal[xSignal.size()-2];
        for(int i =xSignal.size()-2; i>=0; i--){
            xSignal[i+1] = temp;
            temp = xSignal[i-1];
        }
        xSignal[0] = moving;
       
    }else{
        cout<<"Not valid shift!!!"<<endl;
        
    }

    return xSignal;
}


// Function for generating the circular Shift matrix in that matrix elements
// are shifted by one unit.
// Input is a vector.
// Output is a Matrix.
vector<vector<double>> CircularShiftMatrix(vector<double> xSignal)
{
    vector<vector<double>> Matrix;

    Matrix.insert(Matrix.end(), xSignal);
    for(int j =1; j <xSignal.size(); j++){
        xSignal = ShiftingOperation(xSignal, 1);
        Matrix.insert(Matrix.end(), xSignal);
    }

    // PrintMat(Matrix);
    return Matrix;

}


// Function for calculating the circular convolution of two Discrete time signal 
// Inputs are two signals 
// Output is the circularly convolved output.
vector<double> CirConv(vector<double> xSignal, vector<double> hSignal)
{

    vector<vector<double>> InterMat;
    vector<vector<double>> ResultantMat;
    vector<double> Result;

    int xSize = xSignal.size();
    int hSize = hSignal.size();

    int maxSize = xSize > hSize ? xSize : hSize;
    vector<vector<double>>Mat;

    // cout<<maxSize<<endl;
    if(maxSize == xSize){
        Mat = CircularShiftMatrix(xSignal);

        for(int num =0;num<xSize - hSize; num++){
            hSignal.insert(hSignal.end(), 0);
        }

        InterMat = convertVectorToMatrix(hSignal);
        InterMat = Transpose_MAT(InterMat);

        ResultantMat = MatrixMulti(Mat, InterMat);
        ResultantMat = Transpose_MAT(ResultantMat);
        Result = ResultantMat[0];

    }else{

        Mat = CircularShiftMatrix(hSignal);

        for(int num =0;num<hSize - xSize; num++){
            xSignal.insert(xSignal.end(), 0);
        }

        InterMat = convertVectorToMatrix(hSignal);
        InterMat = Transpose_MAT(InterMat);

        ResultantMat = MatrixMulti(Mat, InterMat);
        ResultantMat = Transpose_MAT(ResultantMat);
        Result = ResultantMat[0];

    }
    return Result;
}


int main()
{
    vector<double> xSignal = {1, 2, 3, 2, 1};
    vector<double> hSignal = {1, 2, 1};
  
    vector<double> Result = CirConv(xSignal, hSignal);
    PrintVectorDouble(Result);

    return 0;
}
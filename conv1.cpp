#include <iostream>
#include <vector>
#include <iterator>
#include "MyMatrixOperation.h"

using namespace std;


// Function for printing the vector on the console output.
void PrintVectorDouble(vector<double> vectr)
{
    std::copy(begin(vectr), end(vectr),  std::ostream_iterator<double>(std::cout, " , "));
    cout<<endl;
}



vector<double> DiagonalSum(vector<vector<double> > & MAT)
{
    vector<double> result;
    result.insert(result.end(), MAT[0][0]);

    int col =1;
    int raw =0;
    double sum =0;
    int colIndex, rowIndex;

    while(col<MAT[0].size()){

        colIndex = col;
        rowIndex = 0;

        while(colIndex>=0){
            
            sum = sum + MAT[rowIndex][colIndex];
            rowIndex++;
            colIndex--;
            if(rowIndex==MAT.size()){
                break;
            }
        }
        result.insert(result.end(), sum);
        sum =0;
        col++;
    }

    raw=1;

    while(raw<MAT.size()){

        rowIndex = raw;
        colIndex = col-1;

        while(colIndex>=0){

            sum = sum + MAT[rowIndex][colIndex];

            rowIndex++;
            colIndex--;
            if(rowIndex==MAT.size()){
                break;
            }
        }

        result.insert(result.end(), sum);
        sum =0;
        raw++;
    }

    return result;

}



int main()
{
    vector<vector<double>> MAT1{{4,8,7,5,6}};

    vector<vector<double>> MAT2{{1,2,3}};
    MAT2 = Transpose_MAT(MAT2);
    // PrintMat(MAT2);
    
    vector<vector<double>> MatRes = MatrixMulti(MAT2, MAT1);

    vector<double> res = DiagonalSum(MatRes);

    PrintVectorDouble(res);

    PrintMat(MatRes);
    return 0;
}
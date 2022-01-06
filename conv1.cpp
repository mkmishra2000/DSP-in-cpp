#include <iostream>
#include <vector>
#include <iterator>

using namespace std;


// Function for sum of two double numbers.
// Input is double numbers.
// Output is the sum of two double numbers.
double SumValue(double a, double b)
{
    return (a+b);
}


// Function for mul of two binary number in galois filed 2.
// Input binary numbers either 0 or 1.
// Output is the mul of two binary numbers according to galois 2.
// 0 0 | 0
// 0 1 | 0
// 1 0 | 0
// 1 1 | 1 
double MulValue(double a, double b){

    return (a*b);

}


// Function of error message in matrices multiplications.
void errorMSG(){
    cout<<endl;
    cout<<"! Matrices size are not proper for multiplication !!! :-("<<endl;
    cout<<endl;
}

// Function for printing the matrix on console.
void PrintMat(vector<vector<double> > & MAT)
{
    for(int j =0; j<MAT.size();j++){
        for(int k =0; k<MAT[j].size(); k++){
            cout<<MAT[j][k]<< "   ";
        }
        cout<<endl;
    }
}



// Function for printing the vector on the console output.
void PrintVectorDouble(vector<double> vectr)
{
    std::copy(begin(vectr), end(vectr),  std::ostream_iterator<double>(std::cout, " , "));
    cout<<endl;
}



// Function for taking transpose of the given matrix. 
// Input is the matrix for some m*n dimension.
// Output is the matrix with n*m dimension having transpose of actual matrix 
vector<vector <double> > Transpose_MAT(vector<vector <double> > MAT)
{
    vector<vector<double> > TransMAT;
    vector <double> interMAT;

    for(int i =0; i<MAT[0].size(); i++){
        for(int j =0; j<MAT.size(); j++){
            interMAT.insert(interMAT.end(), MAT[j][i]);
        }
        TransMAT.push_back(interMAT);
        interMAT.clear();
    }

    return TransMAT;
}



// Function for multiply two matrices by galois filed 2.
// Input two matries.
// Output is the resultant Matrix if input vectors are proper otherwise zero matrix return.
vector<vector<double> >MatrixMulti(vector< vector<double> > &MAT1, vector< vector<double> > &MAT2)
{
    int Raws = MAT1.size(); //raws of the final vector.
    int Column = MAT2[0].size(); //Columns of the final vector.

    vector<double> finalRaw(Column, 0); //All zero entry in rows. 1*columns size.
    vector<vector<double>> resltantMAT(Raws, finalRaw); // raws*columns size.

    vector<double> inter1;
    vector<double> inter2;

    for(int i =0; i<resltantMAT.size(); i++){
        for(int j =0; j<resltantMAT[0].size(); j++){

            for(int col =0; col<MAT1[0].size(); col++){
                inter1.insert(inter1.end(), MAT1[i][col]);
            }
            for(int row = 0; row<MAT2.size(); row++){
                inter2.insert(inter2.end(), MAT2[row][j]);
            }

            // Columns of first matrixs should be same as raws of second matrix.
            if(inter1.size() == inter2.size()){
                for(int len =0; len<inter2.size(); len++){
                    resltantMAT[i][j] =SumValue(resltantMAT[i][j], MulValue(inter1[len], inter2[len]));
                }
            }else{
                errorMSG();
            }

            inter1.clear(); //Clear out intermediate vector
            inter2.clear(); //Clear out intermediate vector
            
        }
    }

    return resltantMAT;
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
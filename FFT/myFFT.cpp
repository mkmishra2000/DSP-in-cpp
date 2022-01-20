//////////////////////////////////////////////////////////////////////////////////////////////////
// FFT decimation in time algorithm
// Author:- Manas Kumar Mishra
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include "MyMatrixOperation.h"

#define pi 3.14159

using namespace std;


// function for converting signal into another signal of length exponent of 2
// Input is the vector
// Output is the another vector  
vector<double> CheckAndPadFunc (vector<double> signal)
{
    vector<double> newSignal;
    int sizeOfSignal = signal.size();
    double check = log2(sizeOfSignal);
    
    double Val = abs(check -int(check)); //check that number is integer or float

    newSignal = signal;

    if(Val==0){ // if length is exponent of 2.
        ;
    }else{

        int desireLength = pow(2, int(check)+1);
        
        for(int p=sizeOfSignal; p<desireLength; p++){
            newSignal.insert(newSignal.end(), 0);
        }
    }

    return newSignal;
}


// function for printing the fft results 
// Input is the FFT matrix top raw as all real part and bottom raw as imazinary part. 
// Output is nothing but it display the fft results in the form of complex numbers  
void printfftResult(vector<vector<double>> Mat )
{
    vector<double> realPart = Mat[0];
    vector<double> imzPart = Mat[1];

    for(int i =0; i<realPart.size(); i++){
        cout<<"\n";
        cout<<realPart[i]<<" +  j( "<<imzPart[i]<<" ) "<<endl;
    }
    cout<<endl;
}


// function for spliting the sequence in even signal and odd signal 
// Inout is the vector 
// Output are two vectors pairs one for even index signal, second for odd index signal 
pair<vector<double>, vector<double>> splitIn2vectors(vector<double> signal)
{
    vector<double> firstVec, secondVec;

    for(int t =0; t<(signal.size()/2); t++){
        firstVec.insert(firstVec.end(), signal[2*t]); //even index values 
        secondVec.insert(secondVec.end(), signal[2*t+1]); // Odd index values
    }

    return make_pair(firstVec, secondVec);
}


// function for last step for fft algorithm
// Input is a vector of two points 
// Ouptut is the 2-point fft
vector<double> LastStepDesign(vector<double> signal)
{
    double temp[2];
    vector<double> ResVec;

    temp[0] = signal[0]+signal[1];
    temp[1] = signal[0]-signal[1];

    for(int i =0; i<2; i++){
        ResVec.insert(ResVec.end(), temp[i]);
    }

    return ResVec;
}


// function for expanding the values for combining the fft results.
// INput is the Matrix that contains first row as real quantity and second raw as imazinary
// Output are the pairs of expended values.
pair<vector<double>, vector<double>> ExpandMatrix(vector<vector<double>> Mat)
{
    vector<double> temp1;
    vector<double> temp2;

    for(int times =0; times<2; times++){
        for(int t =0; t<Mat[0].size(); t++){
            temp1.insert(temp1.end(), Mat[0][t]);
            temp2.insert(temp2.end(), Mat[1][t]);
        }
    }

    return make_pair(temp1, temp2);
}


// function for computing Twiddle factor
// Input is the constant value N (number of points)
// Outputs are the pair of real and imazinary values of the twiddle factors
pair<vector<float>, vector<float>> TwiddleFactors(const int & N)
{
    vector<float> cosineFactor, sinFactors;
    double normal = (2*pi)/N;

    for(int i =0; i<N; i++){
        cosineFactor.insert(cosineFactor.end(), cos(normal*i));
        sinFactors.insert(sinFactors.end(), sin(-1*normal*i));
    }

    return make_pair(cosineFactor, sinFactors);

}


// Function for calculating multiplication of twiddle factor with second component of N-point fft 
// Inputs are the real and imazinary part of second component and twiddle factor. 
// Outputs are the  pairs of vector as the result of complex multiplication   
pair<vector<double>, vector<double>> MultiplyOfComplexNumber(vector<double> ReSig2,
                                                             vector<double> ImSig2, 
                                                             vector<float> cosineTerm, 
                                                             vector<float> sinTerm)
{
    vector<double> realPart, imzpart;

    double putreal, putimz;

    for(int i=0; i<ReSig2.size(); i++){
        putreal = ReSig2[i]*cosineTerm[i]-ImSig2[i]*sinTerm[i]; // real part after muliplication
        putimz =  ReSig2[i]*sinTerm[i]+ImSig2[i]*cosineTerm[i]; // imz part after multiplication

        realPart.insert(realPart.end(), putreal);
        imzpart.insert(imzpart.end(), putimz);
    }

    return make_pair(realPart, imzpart);

}


// function for combining both N/2 fft's to get N point FFT
// Inputs are the real and imz parts of the first component and result of multiplication of twiddle factor and second component 
// Output are the pair of vector that contain real and imazinary part of resultant complex number.
pair<vector<double>, vector<double>> fftoperation(vector<double> ReSig1,
                                                  vector<double> ImSig1,
                                                  vector<double> ReSig2,
                                                  vector<double> ImSig2)
{
    auto twiddle = TwiddleFactors(ReSig1.size());
    vector<float> cosineTerms = twiddle.first;
    vector<float> sineTerms = twiddle.second;

    auto secondPart = MultiplyOfComplexNumber(ReSig2, ImSig2, cosineTerms, sineTerms);
    vector<double> realPart = secondPart.first;
    vector<double> imzpart = secondPart.second;

    for(int i=0; i<ReSig1.size(); i++){
        realPart[i] = realPart[i]+ReSig1[i];
        imzpart[i] = imzpart[i]+ImSig1[i];

        if(realPart[i]<0.001& realPart[i]>-0.001){
            realPart[i] =0;
        }
        if(imzpart[i]<0.001& imzpart[i]>-0.001){
            imzpart[i] =0;
        }
    }

    return make_pair(realPart, imzpart);

}


// function for calculating the fft results using recursive algorithm
// Input is the Matrix that contain real as first row and imazinary as bottom rows.
// Output is the result of the fft in matrix for first raw as real values and second raw as imazinary value  
vector<vector<double>> fftResult(vector<vector<double>> SignalMat)
{
    vector<double> RealPart = SignalMat[0];

    vector<double> ImzPart  = SignalMat[1];

    int size = RealPart.size();
    vector<double> RealPartFFT, ImzPartFFT;
    
    vector<vector<double>> ResMat;

    if(size == 2){
        
        RealPartFFT = LastStepDesign(RealPart);
        ImzPartFFT = LastStepDesign(ImzPart);

        ResMat.insert(ResMat.end(), RealPartFFT);
        ResMat.insert(ResMat.end(), ImzPartFFT);

        return ResMat;

    }else{

        auto Realret = splitIn2vectors(RealPart);
        vector<double> RealPartfirst = Realret.first;
        vector<double> RealPartsecond = Realret.second;


        auto Imzret = splitIn2vectors(ImzPart);
        vector<double> ImzPartfirst = Imzret.first;
        vector<double> ImzPartsecond = Imzret.second;

        vector<vector<double>> Mat1, Mat2;

        Mat1.insert(Mat1.end(), RealPartfirst);
        Mat1.insert(Mat1.end(), ImzPartfirst);
        Mat1 = fftResult(Mat1);
        RealPartfirst.clear();
        ImzPartfirst.clear();

        auto expend1 = ExpandMatrix(Mat1);
        RealPartfirst = expend1.first;
        ImzPartfirst = expend1.second;
       

        Mat2.insert(Mat2.end(), RealPartsecond);
        Mat2.insert(Mat2.end(), ImzPartsecond);
        Mat2 = fftResult(Mat2);
        RealPartsecond.clear();
        ImzPartsecond.clear();

        auto expend2 = ExpandMatrix(Mat2);
        RealPartsecond = expend2.first;
        ImzPartsecond = expend2.second;
        

        auto fftop = fftoperation(RealPartfirst, ImzPartfirst, RealPartsecond, ImzPartsecond);
        ResMat.insert(ResMat.end(), fftop.first);
        ResMat.insert(ResMat.end(), fftop.second);

        return ResMat;
    }
}

// function for fft 
vector<vector<double>> myFFT(vector<double> realPartOfSignal, vector<double> imzPartOfSignal)
{
    vector<vector<double>> Matrix;

    //If real and imz part has same length.
    if(realPartOfSignal.size()== imzPartOfSignal.size()){

        vector<double> newSignal1 = CheckAndPadFunc(realPartOfSignal);
        vector<double> newSignal2 = CheckAndPadFunc(imzPartOfSignal);
        
        Matrix.insert(Matrix.end(), newSignal1);
        Matrix.insert(Matrix.end(), newSignal2);

        Matrix = fftResult(Matrix);
    }
    else{
        cout<<" Real and imazinary parts should be of same size !!!! \n"<<endl;

        vector<double> newSignal1 ={0};
        vector<double> newSignal2 ={0};

        Matrix.insert(Matrix.end(), newSignal1);
        Matrix.insert(Matrix.end(), newSignal2);
    }
    
    return Matrix;
}


int main()
{
    vector<double> signal1= {1, 2, 2, 3, 5, 6, 7, 12 ,12, 23, 23, 2 };
    vector<double> signal2= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    vector<vector<double>> FFTresult = myFFT(signal1, signal2);

    printfftResult(FFTresult);

    return 0;
}
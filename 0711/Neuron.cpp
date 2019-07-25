#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Neuron
{
    public:
        double w;
        double b;
        vector<double> X;
        vector<double> Y;
        double dw;
        double db;

        double activation(const double sigma)
        {
            //linear activation function
            return sigma;
        }

        double feedForward(const double input)
        {
            const double sigma = w * input + b;

            return activation(sigma);
        }

        double feedForwardAndPrint(const double input)
        {
            printf("Input : %f,  sigma : %f \n", input, feedForward(input));
        }

        Neuron()
        {

        }

        Neuron(double w_input, double b_input)
        {
            this->w = w_input;
            this->b = b_input;
        }

        ~Neuron()
        {

        }
    /*
        void backProp(double target, double input)
        {
            printf("target : %.1f  ",target);
            double learning_rate = 0.1;
            double gradient = (feedForward(input)- target);

            w = w - learning_rate*gradient*input;
            b = b - learning_rate*gradient;
        }
    */
        void backProp(vector<double> inputX, vector<double> inputY)
        {
            const double alpha = 0.001;  //learning rate
            double dw = 0;
            double db = 0;
            
            int n = static_cast<int>(inputX.size());

            for(int i=0; i<n ; i++){
                dw += (feedForward(inputX[i]) - inputY[i])*inputX[i];
                db += (feedForward(inputX[i]) - inputY[i]);
            }

            dw /= n;
            db /= n;

            w = w - alpha*dw;
            b = b - alpha*db;
        }

        void assignData(vector<double> inputX, vector<double> inputY)
        {
            X.resize(inputX.size());
            Y.resize(inputY.size());
            copy(inputX.begin(),inputX.end(),X.begin());
            copy(inputY.begin(),inputY.end(),Y.begin());
        }


        double getCost(double input, double output)
        {
            double cost = (output - feedForward(input))*(output - feedForward(input));

            return cost;
        }

        double getTotalCost(vector<double> inputX, vector<double> inputY)
        {
            int n = static_cast<int>(inputX.size());
            double cost = 0;

            for(int i = 0; i<n ; i++){
                cost += getCost(inputX[i],inputY[i]);
            }

            return cost/n;
        }
};

int main()
{
    vector<double> X, Y;

    for(int i=0; i<3; i++){
        X.push_back(double(i) + 0.0);
        Y.push_back(3*double(i) + 2.0);
    }

    Neuron N2(1.0,3.0);
    N2.assignData(X,Y);

    double cost;
    double target = 2.5;

    for(int i=0; i<100000; i++){
        if(i%10000 == 0){
            printf("target : %f \n", target);
            printf("Training : %d  \n",i);
            N2.feedForwardAndPrint(2.5);
            printf("W = %f, b = %f  \n", N2.w, N2.b);
            printf("Cost = %f \n\n", cost);
        }
        cost = N2.getTotalCost(N2.X, N2.Y);
        N2.backProp(N2.X, N2.Y);
    }

    return 0;
}


/*
int main()
{
    //initialize testNeuron
    Neuron N1(1.0,3.0);

    double input;
    double output;

    for(int i=0; i<150 ; i++){
        N1.backProp(2.5, 2.5);
        printf("%3d training   w: %.5f  b: %.5f  y: %.4f  \n",i+1,N1.w,N1.b,N1.feedForward(2.5));
    }

 //   for(double i=0; i<3.0 ; i=i+0.5){
 //     input = i;
 //     N1.feedForwardAndPrint(input);
    }

    return 0;
}
*/

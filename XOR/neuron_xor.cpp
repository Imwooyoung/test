#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Neuron
{
public:
	double w1_1, w2_1,  w1_2, w2_2,  w1_y, w2_y;
	double wb_1, wb_2, wb_y;
	vector<double> X1, X2;
	vector<double> Y;
	double dw1_1, dw2_1,  dw1_2, dw2_2,  dw1_y, dw2_y;
	double db_1, db_2, db_y;

	double getActivation(const double sigma)  //Activation Function
	{
		//sigmoid function
		return 1 / (1 + exp(-sigma));
	}

	double feedForward_1(const double x1, const double x2)    //sigma calculation
	{
		const double sigma = w1_1*x1 + w2_1*x2 + wb_1 * 1;

		return getActivation(sigma);
	}

	double feedForward_2(const double x1, const double x2)    
	{
		const double sigma = w1_2*x1 + w2_2*x2 + wb_2 * 1;

		return getActivation(sigma);
	}

	double feedForward_y(const double x1, const double x2)    
	{
		const double y1 = feedForward_1(x1, x2);
		const double y2 = feedForward_2(x1, x2);
		const double sigma = w1_y * y1 + w2_y * y2 + wb_y * 1;

		return getActivation(sigma);
	}

	double feedForwardAndPrint(const double x1, const double x2)
	{
		printf("x1 : %.f, x2 : %.f, sigma : %f \n", x1, x2, feedForward_y(x1, x2));
		return 0.0;
	}

	Neuron()
	{
	}

	Neuron(double w1_1_input, double w2_1_input, double wb_1_input, double w1_2_input, double w2_2_input, double wb_2_input,
			double w1_y_input, double w2_y_input, double wb_y_input)
	{
		w1_1 = w1_1_input;
		w2_1 = w2_1_input;
		wb_1 = wb_1_input;

		w1_2 = w1_2_input;
		w2_2 = w2_2_input;
		wb_2 = wb_2_input;

		w1_y = w1_y_input;
		w2_y = w2_y_input;
		wb_y = wb_y_input;
	}

	~Neuron()
	{
	}

	void xorGenerate()
	{
		//XOR
		X1.push_back(0);
		X1.push_back(0);
		X1.push_back(1);
		X1.push_back(1);

		X2.push_back(0);
		X2.push_back(1);
		X2.push_back(0);
		X2.push_back(1);

		Y.push_back(0);
		Y.push_back(1);
		Y.push_back(1);
		Y.push_back(0);
	}

	double getActGrad(const double x1, const double x2, double output)
	{
		double y1 = feedForward_1(x1, x2);
		double y2 = feedForward_2(x1, x2);

		double sigma0_1 = w1_1*x1 + w2_1*x2 + wb_1 * 1;
		double sigma0_2 = w1_2*x1 + w2_2*x2 + wb_2 * 1;
		double sigma_1 = w1_y*y1 + w2_y*y2 + wb_y * 1;

		double ewxb0_1 = exp(-sigma0_1) / ((1 + exp(-sigma0_1))*(1 + exp(-sigma0_1)));
		double ewxb0_2 = exp(-sigma0_2) / ((1 + exp(-sigma0_2))*(1 + exp(-sigma0_2)));
		double ewxb_1 = exp(-sigma_1) / ((1 + exp(-sigma_1))*(1 + exp(-sigma_1)));

		dw1_1 += x1 * ewxb0_1 * w1_y * ewxb_1 * (feedForward_y(x1,x2)-output);
		dw2_1 += x2 * ewxb0_1 * w1_y * ewxb_1* (feedForward_y(x1,x2)-output);
		db_1 += 0.5*(ewxb0_1 * w1_y * ewxb_1 + ewxb0_1 * w2_y * ewxb_1)* (feedForward_y(x1,x2)-output);

		dw1_2 += x1 * ewxb0_2 * w2_y * ewxb_1* (feedForward_y(x1,x2)-output);
		dw2_2 += x2 * ewxb0_2 * w2_y * ewxb_1* (feedForward_y(x1,x2)-output);
		db_2 += 0.5*(ewxb0_2 * w2_y * ewxb_1 + ewxb0_2 * w2_y * ewxb_1)* (feedForward_y(x1,x2)-output);

		dw1_y += ewxb_1 * y1* (feedForward_y(x1,x2)-output);
		dw2_y += ewxb_1 * y2* (feedForward_y(x1,x2)-output);
		db_y += ewxb_1* (feedForward_y(x1,x2)-output);

		return 0.0;
	}


	void backProp(vector<double> X1, vector<double> X2, vector<double> Y)
	{
		const double alpha = 0.01;
		int n = static_cast<int>(X1.size());
		dw1_1 = 0;
		dw2_1 = 0;
		db_1 = 0;

		dw1_2 = 0;
		dw2_2 = 0;
		db_2 = 0;

		dw1_y = 0;
		dw2_y = 0;
		db_y = 0;

		for (int i = 0; i<n; i++){
			getActGrad(X1[i], X2[i], Y[i]);
		}

		w1_1 = w1_1 - alpha * dw1_1/n;
		w2_1 = w2_1 - alpha * dw2_1/n;
		wb_1 = wb_1 - alpha * db_1/n;

		w1_2 = w1_2 - alpha * dw1_2/n;
		w2_2 = w2_2 - alpha * dw2_2/n;
		wb_2 = wb_2 - alpha * db_2/n;

		w1_y = w1_y - alpha * dw1_y/n;
		w2_y = w2_y - alpha * dw2_y/n;
		wb_y = wb_y - alpha * db_y/n;
	}

	
	double getLogisticCost(double x1, double x2, double y)
	{
		double sigma = feedForward_1(x1, x2);
		double p = getActivation(sigma);

		if (y == 1)
		{
			return -log(p);
		}
		else
		{
			return -log(1 - p);
		}
	}

	double getTotalLogisticCost(vector<double> X1, vector<double>X2, vector<double> Y)
	{
		int n = static_cast<int>(X1.size());
		double cost = 0;

		for (int i = 0; i<n; i++){
			cost += getLogisticCost(X1[i], X1[i], Y[i]);
		}

		return cost / n;
	}
};

int main()
{
	
	Neuron N(5.0, 5.0, -5.0, -5.0, -5.0, 5.0, -10.0, -10.0, 5.0);
	N.xorGenerate();

	double cost = 0;

	for (int i = 0; i<100000; i++){
		if (i % 10000 == 0){
			printf("Training : %d  \n", i);
			N.feedForwardAndPrint(0, 0);
			N.feedForwardAndPrint(0, 1);
			N.feedForwardAndPrint(1, 0);
			N.feedForwardAndPrint(1, 1);
			printf("w1_1 = %f, w2_1 = %f, wb_1 = %f  \n", N.w1_1, N.w2_1, N.wb_1);
			printf("w1_2 = %f, w2_2 = %f, wb_2 = %f  \n", N.w1_2, N.w2_2, N.wb_2);
			printf("w1_y = %f, w2_y = %f, wb_y = %f  \n\n", N.w1_y, N.w2_y, N.wb_y);
			printf("Cost = %f \n\n", cost);
		}
		cost = N.getTotalLogisticCost(N.X1, N.X2, N.Y);
		N.backProp(N.X1, N.X2, N.Y);
	}

	return 0;
}


/*
 Project : Simple Perceptron
 
 Data : Petal lengths and widths of red and blue flowers {Red : 1 , Blue : 0}
 
 Description : This project aims in building a simple perceptron that aims to classify flower data
 
 Engineer : Srimanth Tenneti
 
 Date : 10th July 2020

 Data : {lenght , width , red/blue} 
 
*/

/*
 *   ****************************************    Code    **********************************************************
 */

double data[10][10] = {{3,1.5,1},{2,1,0},{4,1.5,1},{3,1,0},{3.5,0.5,1},{2,0.5,0},{5.5,1,1},{1,1,0}}; // Dataset

int randomseed = 200; // Random seed 

float lr = 0.06; // Learning rate

// Function for generating random numbers

double generate_random_number_float(float x)
{
  return (random(x)/(100.0));
}

// Sigmoid activation function

double sigmoid(double x)
{
  return(1/1+exp(-x));
}

// Differentiation of sigmoid 

double sigmoid_d(double x)
{
  return(sigmoid(x) * (1 - (sigmoid(x))));
}

double w1 = generate_random_number_float(randomseed); // Weight 1
double w2 = generate_random_number_float(randomseed); // Weight 2
double b  = generate_random_number_float(randomseed); // Bias 

// Function to print the parameters

void print_params()
{
  Serial.print("w1:");
  Serial.println(w1);
 
  Serial.print("w2:");
  Serial.println(w2);

  Serial.print("b:");
  Serial.println(b);
  
  Serial.println();
}

double costs[100];

// Training Function

double train_model(int n_epochs)
{
  for(int i = 0 ; i < n_epochs ; i++)
  {
   int ri = generate_random_number_float(randomseed);
   double point[2];

   for(int i = 0 ; i < 2 ; i++)
   {
    point[i] = data[ri][i];
   }
   
   double z = point[0] * w1 + point[1] * w2 + b;
   double pred = sigmoid(z);

   double target = point[2];
   double cost = ((pred - target) * (pred - target));

   costs[i] = cost;

   double dcost_pred = 2 * (pred - target);
   double dpred = sigmoid_d(z);

   double dz_dw1 = point[0];
   double dz_dw2 = point[1];
   double dz_db  = 1;

   double dzcost_dz = dcost_pred * dpred;

   double dcost_dw1 = dzcost_dz * dz_dw1;
   double dcost_dw2 = dzcost_dz * dz_dw2;
   double dcost_db  = dzcost_dz * dz_db;

   w1 = w1 - lr * dcost_dw1;
   w2 = w2 - lr * dcost_dw2;
   b = b - lr * dcost_db;
  }
}

// Predictor function

String pred(float l1,float l2)
{
  double score = l1*w1 + l2*w2 + b;
  if(score > 0.57)
  {
    return ("It is a red flower");
  }
  else
  {
    return("It is a blue flower");
  }
}

void setup() {

  int n_epochs = 10000;
  
  Serial.begin(9600);
  Serial.println("Default 100 x 100 ...");
  print_params();

  Serial.println("Beginning Training ...");
  train_model(n_epochs); // Parameter is number of epochs

  Serial.println("Parameters after Training ...");
  print_params();

  String result = pred(3 , 1.5);

  Serial.println("Prediction :");
  Serial.print(result);
}

void loop() {
  
}

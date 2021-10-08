/*******************************************************************************
 *  Name:   Jiwoo Lee
 *  Email:  leeji-22@rhodes.edu
 *
 *  Description: This program performs simple kernel based image processing
 *               filters on an image.
 *
 *  Written:       10/10/19
 *  Last updated:  10/11/19
 ******************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>      // srand(time(0)) for rand() in glass
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================

void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);

void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
              int N, double kernel[][11]);

void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);

void gaussian(double k[][11], int N, double sigma);

void gaussian_filter(unsigned char out[][SIZE][3], unsigned char in[][SIZE][3],
                     int N, double sigma);

void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3],
             int N, double sigma, double alpha);

// a <= b
void glass(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
           int a, int b);

// 0 <= angle <= 2π
void rotate(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
           double angle);

void noisecancel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);

void wave(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
          double amplitude, double frequency);

//============================Do not change code in main()======================

int main(int argc, char* argv[])
{
    srand(time(0));

   //First check argc
  if(argc < 3)
    {
      //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
      return -1;
    }
   //then check to see if we can open the input file
   unsigned char input[SIZE][SIZE][RGB];
   unsigned char output[SIZE][SIZE][RGB];
   char* outfile;
   int N, a, b, amplitude, frequency; // a and b for glass
                                      // amplitude and frequency for wave
   double sigma, alpha, angle; // angle for rotate
   double kernel[11][11];

   // read file contents into input array
   int status = readRGBBMP(argv[1], input);
   if(status != 0)
   {
      cout << "unable to open " << argv[1] << " for input." << endl;
      return -1;
   }
   //Input file is good, now look at next argument
   if( strcmp("sobel", argv[2]) == 0)
   {
     sobel(output, input);
     outfile = argv[3];
   }
   else if( strcmp("blur", argv[2]) == 0)
   {
     if(argc < 6)
       {
	 cout << "not enough arguments for blur." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     outfile = argv[5];
     gaussian_filter(output, input, N, sigma);
   }
   else if( strcmp("unsharp", argv[2]) == 0)
   {
     if(argc < 7)
       {
	 cout << "not enough arguments for unsharp." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     alpha = atof(argv[5]);
     outfile = argv[6];
     unsharp(output, input, N, sigma, alpha);

   }
   else if( strcmp("dummy", argv[2]) == 0)
   {
     //do dummy
     dummy(output, input);
     outfile = argv[3];
   }
   else if ( strcmp("glass", argv[2]) == 0)
   {
     if(argc < 6)
       {
  cout << "not enough arguments for glass." << endl;
  return -1;
       }
     // If a > b, return -1
     if(atoi(argv[3]) > atoi(argv[4])) {
       cout << "Lower bound is greater than the upper bound." << endl;
       return -1;
     }

     a = atoi(argv[3]);
     b = atoi(argv[4]);
     glass(output, input, a, b);
     outfile = argv[5];
   }
   else if ( strcmp("rotate", argv[2]) == 0)
   {
     if(argc < 5)
       {
  cout << "not enough arguments for glass." << endl;
  return -1;
       }
    // If angle > 2π OR angle < 0, return -1
    if(atof(argv[3]) > 2 * M_PI || atof(argv[3]) < 0) {
         cout << "Angle is out of the range [0, 2*pi]" << endl;
         return -1;
    }

     angle = atof(argv[3]);
     rotate(output, input, angle);
     outfile = argv[4];
   }
   else if( strcmp("noisecancel", argv[2]) == 0)
   {
     noisecancel(output, input);
     outfile = argv[3];
   }
   else if ( strcmp("wave", argv[2]) == 0)
   {
     if(argc < 6)
       {
  cout << "not enough arguments for wave." << endl;
  return -1;
       }
     amplitude = atof(argv[3]);
     frequency = atof(argv[4]);
     wave(output, input, amplitude, frequency);
     outfile = argv[5];
   }
   else
   {
      cout << "unknown filter type." << endl;
      return -1;
   }

   if(writeRGBBMP(outfile, output) != 0)
   {
      cout << "error writing file " << argv[3] << endl;
   }

}

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   for (int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         k[i][j] = 0;
      }
   }
   k[1][1] = 1;
   convolve(out, in, 3, k);
}


// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the
//  instructions in the comments
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
	            int N, double kernel[][11])
{

   int padded[SIZE+10][SIZE+10][RGB];  // Use for input image with appropriate
                                       // padding
   int temp[SIZE][SIZE][RGB];          // Use for the unclamped output pixel
                                       // values then copy from temp to out,
                                       // applying clamping

   //first set all of padded to 0 (black)
   for (int i = 0; i < SIZE + 10; i++) {
     for (int j = 0; j < SIZE + 10; j++) {
       for (int k = 0; k < RGB; k++) {
         padded[i][j][k] = 0;
       }
     }
   }

   //now copy input into padding to appropriate locations
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {
         padded[i+5][j+5][k] = in[i][j][k];
       }
     }
   }



   //initialize temp pixels to 0 (black)
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {
         temp[i][j][k] = 0;
       }
     }
   }



  //now perform convolve (using convolution equation on each pixel of the
  // actual image) placing the results in temp (i.e. unclamped result)
  //Here we give you the structure of the convolve for-loops, you need
  //to figure out the loop limits
  for(int y = 0; y < SIZE; y++) {
    for(int x = 0; x < SIZE; x++) {
      for(int k = 0; k < RGB; k++) {
        for(int i = 0; i < N; i++) {
          for(int j = 0; j < N; j++) {
            temp[y][x][k] += padded[y + (11 - N)/2 + i][x + (11 - N)/2 + j][k]
                             * kernel[i][j];
          }
        }
      }
    }
  }


   //now clamp and copy to output
   // You may need to cast to avoid warnings from the compiler:
   // (i.e. out[i][j][k] = (unsigned char) temp[i][j][k];)
   for (int i = 0; i < SIZE; i++) {
     for (int j = 0; j < SIZE; j++) {
       for (int k = 0; k < RGB; k++) {

         // Clamping
         if (temp[i][j][k] >= 0 && temp[i][j][k] <= 255)
          out[i][j][k] = static_cast<unsigned char> (temp[i][j][k]);
         else if (temp[i][j][k] < 0)
          out[i][j][k] = 0;
         else if (temp[i][j][k] > 255)
          out[i][j][k] = 255;

         }
       }
     }
}

// You will need to complete this function by following the
//  instructions in the comments
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   double s_h1[3][3] = { {-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1} };
   double s_h2[3][3] = { {1, 0, -1},
                         {2, 0, -2},
                         {1, 0, -1} };

   unsigned char h1_soble[SIZE][SIZE][RGB]; //hold intemediate images
   unsigned char h2_soble[SIZE][SIZE][RGB];

   for (int i = 0; i < 11; i++) {
     for (int j = 0; j < 11; j++) {
       k[i][j] = 0;
     }
   }

   // Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 3; j++) {
       k[i][j] = s_h1[i][j];
     }
   }


   // Call convolve to apply horizontal sobel kernel with result in h1_soble
   convolve(h1_soble, in, 3, k);


   // Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 3; j++) {
       k[i][j] = s_h2[i][j];
     }
   }


   // Call convolve to apply horizontal sobel kernel with result in h2_soble
   convolve(h2_soble, in, 3, k);


   // Add the two results (applying clamping) to produce the final output
   for (int p = 0; p < SIZE; p++) {
     for (int q = 0; q < SIZE; q++) {
       for (int r = 0; r < RGB; r++) {

         // Assign the sum to int variable first
         int temp = h1_soble[p][q][r] + h2_soble[p][q][r];

         // Clamping
         if (temp >= 0 && temp <= 255)
          out[p][q][r] = static_cast<unsigned char> (temp);
        else if (temp < 0)
          out[p][q][r] = 0;
        else if (temp > 255)
          out[p][q][r] = 255;

       }
     }
   }


}

void gaussian(double k[][11], int N, double sigma) {

    // Array to store gaussian values following C++ 2D array indexing rules
    double gauss[N][N];

    // Required when normalizing the values
    double sum = 0;

    // Calculate raw gaussian values
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        double a = static_cast<double>(i) - N/2;
        double b = static_cast<double>(j) - N/2;
        double val = exp(-(pow(a, 2) + pow(b, 2))/ (2 * pow(sigma, 2)));
        gauss[i][j] = val;
        sum += val;
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << gauss[i][j] << " ";
      }
      cout << endl;
    }

    // Normalize the values so that their sum = 1
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        gauss[i][j] /= sum;
      }
    }

    // Copy the gaussian values to k
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        k[i][j] = gauss[i][j];
      }
    }

    // Print k
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        cout << k[i][j] << " ";
      }
      cout << endl;
    }

  }

void gaussian_filter(unsigned char out[][SIZE][3], unsigned char in[][SIZE][3],
                     int N, double sigma)
{
    double k[11][11];

    // Setting the initial values to 0
    for (int i = 0; i < 11; i++) {
      for (int j = 0; j < 11; j++) {
        k[i][j] = 0;
      }
    }

  gaussian(k, N, sigma);
  convolve(out, in, N, k);

}

void unsharp(unsigned char out[][SIZE][3], unsigned char in[][SIZE][3], int N,
             double sigma, double alpha)
{
  // Arrays to hold blurred values & detail map values
  unsigned char blur[SIZE][SIZE][RGB], detailMap[SIZE][SIZE][RGB];

  // Setting the initial values to 0
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        blur[i][j][k] = 0;
      }
    }
  }

  gaussian_filter(blur, in, N, sigma);

  // D = IM - B
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        // Assign IM - B to an int variable first
        int temp = in[i][j][k] - blur[i][j][k];

        // Clamping
        if (temp >= 0 && temp <= 255)
         detailMap[i][j][k] = static_cast<unsigned char> (temp);
       else if (temp < 0)
         detailMap[i][j][k] = 0;
       else if (temp > 255)
         detailMap[i][j][k] = 255;

      }
    }
  }


  // S = IM + alpha * D
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        // Assign IM + alpha * D to an int variable first
        int temp = in[i][j][k] + alpha * detailMap[i][j][k];

        // Clamping
        if (temp >= 0 && temp <= 255)
         out[i][j][k] = static_cast<unsigned char> (temp);
       else if (temp < 0)
         out[i][j][k] = 0;
       else if (temp > 255)
         out[i][j][k] = 255;

      }
    }
  }

}

void glass(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
           int a, int b)
{
  // Copy in to out
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        out[i][j][k] = in[i][j][k];
      }
    }
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {

      // Generate random numbers for ii and jj
      int xRand = rand() % (b - a + 1) + a;
      int yRand = rand() % (b - a + 1) + a;

      // New index for out
      int ii = (SIZE + i + xRand) % SIZE;
      int jj = (SIZE + j + yRand) % SIZE;

      out[ii][jj][0] = in[i][j][0];
      out[ii][jj][1] = in[i][j][1];
      out[ii][jj][2] = in[i][j][2];

    }
  }

}

void noisecancel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{

  // If a pixel is black, set its value to the average of its neighbors
  for (int i = 1; i < SIZE - 1; i++) {
    for (int j = 1; j < SIZE - 1; j++) {

      int sum = in[i][j][0] + in[i][j][1] + in[i][j][2];

      for (int k = 0; k < RGB; k++) {
        if (sum == 0) {
          out[i][j][k] = (in[i - 1][j][k]
                        + in[i - 1][j - 1][k]
                        + in[i - 1][j + 1][k]
                        + in[i][j - 1][k]
                        + in[i][j + 1][k]
                        + in[i + 1][j + 1][k]
                        + in[i + 1][j - 1][k]
                        + in[i + 1][j][k]) / 8;
        }
        else {
          out[i][j][k] = in[i][j][k];
        }

      }
    }
  }
}

void rotate(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
            double angle)
{
  unsigned char rotated[SIZE][SIZE][RGB];

  // Set the background color to black
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        rotated[i][j][k] = 0;
      }
    }
  }

  // Rotate
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {

       /*

       rotated row index = (source row index − center index) * cos(angle)
                         − (source column index - center index) * sin(angle)
                         + center index

       rotated column index = (source row index − center index) * sin(angle)
                             + (source column index − center index) * cos(angle)
                             + center index

      */

      int center = (SIZE - 1) / 2;
      int ii = (i - center) * cos(angle) - (j - center) * sin(angle) + center;
      int jj = (i - center) * sin(angle) + (j - center) * cos(angle) + center;

      if (ii >= 0 && ii <= 255 && jj >= 0 && jj <= 255) {
        for (int k = 0; k < RGB; k++) {
          rotated[ii][jj][k] = in[i][j][k];
        }
      }
    }
  }

  noisecancel(out, rotated);
}

void wave(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
          double amplitude, double frequency)
{
  unsigned char waved[SIZE][SIZE][RGB];

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < RGB; k++) {
        out[i][j][k] = 0;
      }
    }
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        int ii = i;

        int jj = static_cast<int>(j + amplitude * sin(2 * M_PI * i / frequency));
        if (jj >= 0 && jj <= 255) {
          for (int k = 0; k < RGB; k++) {
            out[ii][jj][k] = in[i][j][k];
          }
        }
      }
    }

}

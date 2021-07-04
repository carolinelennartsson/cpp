#include "5_10.h"
#include <iostream>
using namespace std;

/*

void guassian_elimination(double **A, double *b, double *u, int n);
5.10 Write a module for solving the n × n linear system Au = b using
 Gaussian elimination with pivoting, where A is nonsingular.

*/


void swap_rows(double **A, int r1, int r2, int n) {
    for (int i = 0; i < n; i++) {
        double tmp = A[r1][i];
        A[r1][i] = A[r2][i];
        A[r2][i] = tmp;
    }
}

void swap_places(double *b, int r1, int r2) {
    double tmp = b[r1];
    b[r1] = b[r2];
    b[r2] = tmp;
}


void subract_rows(double **A, double *b, int r1, int r2, int n) {
    double times = A[r2][r1];
    for (int c = 0; c < n; c++) {
        A[r2][c] = A[r2][c] - times * A[r1][c];
    }
    b[r2] = b[r2] - times * b[r1];
}

void diag_ones(double **A, double *b, int n)
{
    for (int i= 0; i<n; i++)
    {
        double factor = A[i][i];
        if (factor != 0) {
            for (int j = 0; j <n; j++)
            {
                A[i][j] = A[i][j]/factor;
            }
            b[i] = b[i] /factor;
        }
    }
}


void guassian_elimination(double **A, double *b, double *u, int n)
{
    // for 1 dim matrices
    if (n == 1)
    {
        u[0] = b[0] / A[0][0];
    } else {
        for (int k = 0; k < n; k++)
        {
            if (A[k][k] == 0)
            {
                for (int i = k +1; i < n; i++)
                {
                    if (A[i][k] != 0)
                    {
                        swap_rows(A, k, i, n);
                        swap_places(b, k, i);
                    }
                }
            }
        }
    }
    
    
    diag_ones(A, b, n);
    
    for (int i = 0; i <n -1; i++)
    // never wanting to subract the last row from itself
    {
        diag_ones(A, b, n);
        for (int j= i+1; j <n; j++)
        {
            diag_ones(A, b, n);
            /*
            if (i == n-2 && j == n-1)
             {
                for (int i = 0; i < n; i++)
                {
                    for (int j=0; j < n; j++)
                    {
                        cout<< " " << A[i][j] << " ";
                    }
                    cout << "\n";
                }
                cout << "\n";
            } */
            subract_rows(A, b, i, j, n);
        }
    }
    
    diag_ones(A, b, n);
    
    for (int z = n  -1; z > -1; z--)
    {
        double sum = 0.0;
        for (int t = z+1; t < n; t++)
        {
            sum += u[t] * A[z][t];
        }
        u[z] = (b[z] - sum);
    }

}
    

double** AllocateMemory(int rows, int cols)
{
    double** A = new double* [rows];
    
    for (int i = 0; i < rows; i++)
    {
        A[i] = new double [cols];
    }
    
    return A;
}


void FreeMemory(double** A, int rows_A)
{
    for (int i = 0; i < rows_A; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}


/*

int main() {
  	
    
    int n = 2; // size of matrix
    
    // defining b
    double* b = new double [n];
    b[0] = 2; b[1] = 7;
    
    double* u = new double [n];

    // defining a matrix A
    cout << "Matrix A: \n";
    double** A = AllocateMemory(n, n);
    A[0][0] = 5.0; A[0][1] = 3.0; A[1][0] = 2.0; A[1][1] = 2.0;
    
    // print matrix A
    
    for (int i = 0; i < n; i++)
    {
        for (int j=0; j < n; j++)
        {
            cout<< " " << A[i][j] << " ";
        }
        cout << "\n";
    }
     

    guassian_elimination(A, b, u, n);
    
    
    // print u
    
    for (int i = 0; i < n; i++)
    {
        cout<< " " << u[i] << " ";
    }
    cout << "\n";
    
    // correct answer
    //x1 = -4.25
    //x2 = 7.75
    
    // 0 1.5 -5 3
    // 2 0 0 -10
    // 5 1 0 15.7
    // 1 7 0 0
    
    
    int n = 4; // size of matrix
    
    // defining b
    double* b = new double [n];

    double* u = new double [n];

    // defining a matrix A
    cout << "Matrix A: \n";
    double** A = AllocateMemory(n, n);
    
    A[0][0] = 0; A[0][1] = 1.5; A[0][2] = -5; A[0][3] = 3;
    A[1][0] = 2; A[1][1] = 0; A[1][2] = 0; A[1][3] = -10;
    A[2][0] = 5; A[2][1] = 1; A[2][2] = 0; A[2][3] = 15.7;
    A[3][0] = 1; A[3][1] = 7; A[3][2] = 1; A[3][3] = 0;
    
    // b: 1 3 -2 0
    b[0] = 1; b[1] = 3; b[2] = -2; b[3] = 0;
    
    guassian_elimination(A, b, u, n);
    
    for (int i = 0; i < n; i++)
    {
        cout<< " " << u[i] << " ";
    }
    cout << "\n";

    delete[] u;
    delete[] b;
    FreeMemory(A, n);
	return(0);
}


*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define N 50
#define M 50
#define F 4
#define T 2
#define TH 3
/* put your #defines and typedefs here*/
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[F], int n, int m);
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);
void print_array(int a[N][M], int n, int m);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/



 /*-------------------------------------------------------------------------
   The main program
  -------------------------------------------------------------------------*/
//this is the main that scans the image pixles and sends to the right functions 

int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = { {0} };
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);
    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}
//this function computes the integral image and puts it in integral_image array
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M])
{
    integral_image[0][0] = image[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j!= 0)
                integral_image[i][j] = integral_image[i][j - 1] + image[i][j];
            else if(j == 0 && i!= 0)
                integral_image[i][j] = integral_image[i-1][j] + image[i][j];
            else if(j!= 0 && i!= 0)
                integral_image[i][j] = integral_image[i][j - 1] + integral_image[i - 1][j] - integral_image[i - 1][j - 1] + image[i][j];
        }
    }
}
//this function calculate a spicifec square and deals with undefines cordinates
int sum_rect(int integral_image[][M], int rect[F], int n, int m)
{
    int rect_result = 0;
    if (rect[0] <= 0)
        rect[0] = 0;
    if (rect[1] <= 0)
        rect[1] = 0;
    if (rect[T] >= n)
        rect[T] = n - 1;
    if (rect[TH] >= m)
        rect[TH] = m - 1;
    if (rect[0] <= 0 && rect[1] <= 0 && rect[T] < n && rect[TH] < m) // the case that the square is the same as integral image
        rect_result = integral_image[rect[T]][rect[TH]];
    else
        rect_result = integral_image[rect[T]][rect[TH]] - integral_image[rect[0] - 1][rect[TH]] - integral_image[rect[T]][rect[1] - 1] + integral_image[rect[0] - 1][rect[1] - 1];

    return rect_result;
}
//this function calculate the average of every pixel according to a given nxm matrix 
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int t = i - h / T;
            int l = j - w / T;
            int b = i + h / T;
            int r = j + w / T;
            int rect[F] = {t,l,b,r};
           
            average[i][j] = round((double)sum_rect(integral_image, rect, n, m) / (double)(h * w));
            
       }
    }
}
//print matrixes
void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
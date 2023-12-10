#include <stdio.h>

int main()
{
    int h, w;
    
    printf("Enter the height of the rectangle: ");
    scanf("%d", &h);
    printf("Enter the width of the rectangle: ");
    scanf("%d", &w);

    // check if the dimensions are valid
    if (h <= 2 || w <= 2) {
        printf("Dimensions must be greater than 2.\n");
        return 1;
    }

    // top edge
    for(int i = 0; i < w; i++)
    {
      printf("*");
    }

    printf("\n");

    // middle part
    for(int j = 0; j < h-2; j++)
    {
      printf("*");
      for (int i = 0; i < w-2; i++)
      {
        printf(" ");
      }
      printf("*\n");
    }

    // bottom edge
    for(int i = 0; i < w; i++)
    {
        printf("*");
    }

    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Variables :
int pages;
int frames;
char algorithm[500];
int count = 0;
int faults = 0;
int ref[100];

//Function to take the input from the user
void UserInput()
{

    scanf("%d",&frames);
    scanf("%s",algorithm);

    int temp = 0;

    while (1)
    {
        scanf("%d",&temp);
        if(temp != -1)
        {
            ref[count++]=temp;
        }
        else
        {
            break;
        }
    }
}

//normal reading of the file if needed

/*
int readFile(char *x)
{
    FILE *f ;
    char c[1000];
    f = fopen (x, "r");

    if (f==NULL)
    {
        printf("FILE NOT FOUND !! \n");

        char x[50];
        printf("Enter your file name:\n");
        scanf("%s",x);
        readFile(x);
    }


    fscanf(f, "%d",&frames);
    printf("%d\n",frames);

    fscanf(f,"%s",algorithm);
    printf("%s\n",algorithm);

    while (!feof(f))
    {
        fscanf(f, "%d",& ref[count]);
        if(ref[count] ==-1)
        {
            ref[count]=0;
            break;
        }

        else
            printf("%d\n",ref[count]);
        count++ ;
    }
    return 1;
}
*/

//Least Recent used function
int TimeLRU(int temp[], int n)
{
    int i;
    int minimum = temp[0];
    int pos = 0;

    for(i = 1; i < n; ++i)
    {
        if(temp[i] < minimum)
        {
            minimum = temp[i];
            pos = i;
        }
    }

    return pos;
}
void LRU ()
{
    int frame[frames];
    int temp[10];
    int counter=0;
    int pos;
    int flag1,flag2;
    int i,j;


    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    for(i = 0; i < count; ++i)
    {
        flag1 = flag2 = 0;

        for(j = 0; j < frames; ++j)
        {
            if(frame[j] == ref[i])
            {
                counter++;
                temp[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0)
        {
            for(j = 0; j < frames; ++j)
            {
                if(frame[j] == -1)
                {
                    counter++;
                    //faults++;
                    frame[j] = ref[i];
                    temp[j] = counter;

                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0)
        {
            pos = TimeLRU(temp, frames);
            counter++;
            faults++;
            frame[pos] = ref[i];
            temp[pos] = counter;
            printf("%02d F   ",ref[i]);
            for(j = 0; j < frames; ++j)
            {
                printf("%02d ", frame[j]);
            }
            printf("\n");

        }
        else
        {
            printf("%02d     ",ref[i]);
            for(j = 0; j < frames; ++j)
            {
                if(frame[j] != -1)
                {
                    printf("%02d ", frame[j]);
                }
            }
            printf("\n");
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
}

//First in First out algorithm
void FIFO ()
{
    int arr[frames];
    int i,j,k=0;
    int flag;
    for(i=0; i<frames; i++)
    {
        arr[i]=-1;
    }
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i=0; i<count; i++)
    {
        printf("%02d ",ref[i]);
        flag=0;
        for(j=0; j<frames; j++)
        {
            if(arr[j]==ref[i])
                flag=1;
        }
        if(flag == 1)
        {
            printf("    ");
            for(j=0; j<frames; j++)
                if(arr[j] != -1)
                {
                    printf("%02d ",arr[j]);
                }

        }
        else if (flag == 0)
        {
            if(arr[k]==-1)
            {
                arr[k]=ref[i];
                k=(k+1)% frames;
                printf("    ");
                for(j=0; j<frames; j++)
                    if(arr[j] != -1)
                    {
                        printf("%02d ",arr[j]);
                    }
            }
            else
            {
                faults++;
                arr[k]=ref[i];
                k=(k+1)% frames;
                printf("F   ");
                for(j=0; j<frames; j++)
                    printf("%02d ",arr[j]);

            }
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
}

void OPTIMAL ()   // OPTIMAL algorithm func
{
    int i,j,k ;
    int pos ;
    int temp[10] ;
    int flag1,flag2,flag3 ;
    int max ;
    int arr[frames];

    printf("Replacement Policy = OPTIMAL\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    for(i = 0; i < frames; ++i)
    {
        arr[i] = -1;
    }

    for(i = 0; i < count; ++i)
    {
        flag1 = flag2 = 0;

        for(j = 0; j < frames; ++j)
        {
            if(arr[j] == ref[i])
            {
                flag1 = flag2 = 1;
                printf("%02d     ",ref[i]);
                for(j = 0; j < frames; ++j)
                {
                    if(arr[j] != -1)
                    {
                        printf("%02d ", arr[j]);
                    }

                }
                printf("\n");
                break;

            }
        }

        if(flag1 == 0)
        {
            for(j = 0; j < frames; ++j)
            {
                if(arr[j] == -1)
                {
                    arr[j] = ref[i];
                    flag2 = 1;
                    printf("%02d     ",ref[i]);
                    for(j = 0; j < frames; ++j)
                    {
                        if(arr[j] != -1)
                        {
                            printf("%02d ", arr[j]);
                        }
                    }
                    printf("\n");
                    break;
                }
            }

        }

        if(flag2 == 0)
        {
            flag3 =0;

            for(j = 0; j < frames; ++j)
            {
                temp[j] = -1;

                for(k = i + 1; k < count; ++k)
                {
                    if(arr[j] == ref[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }

            }

            for(j = 0; j < frames; ++j)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if(flag3 ==0)
            {
                max = temp[0];
                pos = 0;

                for(j = 1; j < frames; ++j)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }

            }

            arr[pos] = ref[i];
            faults++;
            printf("%02d F   ",ref[i]);
            for(j = 0; j < frames; ++j)
            {
                printf("%02d ", arr[j]);
            }
            printf("\n");
        }
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
}

void clock()
{
    int frame[frames] ;
    int use[frames] ;
    int index = 0;
    int pointer = 0;
    int flag = 0;
    int flagRemove = 0;

    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");


    for(int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }


    for(int i = 0; i < count; i++)
    {
        flag = 0;
        for(int j = 0; j < frames; j++)
        {
            if(ref[i] == frame[j])
            {
                flag = 1;
                use[j] = 1;
                break;
            }
        }

        if(flag == 0)
        {
            if(frame[index] == -1)
            {
                frame[index] = ref[i];
                use[index++] = 1;
                printf("%02d     ",ref[i]);
                for(int j = 0 ; j < index ; j++)
                {
                    printf("%02d ",frame[j]);
                }
                printf("\n");
            }
            else
            {
                flagRemove = 0;
                while(!flagRemove)
                {
                    pointer = pointer % frames;
                    if(use[pointer] == 1)
                    {
                        use[pointer++] = 0;
                    }
                    else if(use[pointer] == 0)
                    {
                        frame[pointer] = ref[i];
                        use[pointer++] = 1;
                        flagRemove = 1;
                    }
                }
                faults++;
                printf("%02d F   ",ref[i]);
                for(int j = 0 ; j < frames ; j++)
                {
                    printf("%02d ",frame[j]);
                }
                printf("\n");
            }
        }
        else
        {
            printf("%02d     ",ref[i]);
            for(int j = 0 ; j < index ; j++)
            {
                printf("%02d ",frame[j]);
            }
            printf("\n");
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
}

int main()
{
    UserInput();

    if (strcmp(algorithm,"LRU")==0)
    {
        LRU();
    }

    if (strcmp(algorithm,"FIFO")==0)
    {
        FIFO();
    }
    if (strcmp(algorithm,"OPTIMAL")==0)
    {
        OPTIMAL();
    }

    if (strcmp(algorithm,"CLOCK")==0)
    {
        clock();
    }
    return 0;
}


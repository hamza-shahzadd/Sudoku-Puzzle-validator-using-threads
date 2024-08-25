#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <mutex> 
using namespace std;

pthread_t threadrow; //row thread
pthread_t threadcol; //column thread
pthread_t threadsub[9]; //sub matrices threads
bool valid = true;
int dRow;
int count=0;
int target;
int noswaps=0;
int ans;
int extra;
int b = -1;
bool duplicateRow;
bool dupCol;
int element[10];
int number;
pthread_mutex_t mut; //for locking

int invalidE = 0;
int choose = 0;

//initializing sudo code
int sud[9][9] ={
	{5,8,1,5,7,2,4,3,9},
	{7,9,2,8,4,3,6,5,1},
	{3,6,4,5,9,1,7,8,2},
	{4,3,8,9,5,7,2,1,6},
	{2,5,6,1,8,4,9,7,3},
	{1,7,9,3,2,6,8,4,5},
	{8,4,5,2,1,9,3,6,7},
	{9,1,3,7,6,8,5,2,4},
	{6,2,7,4,3,5,1,9,8}
};

//making struct to send rows and cols as arguments in pthread_create
struct argums
{
	int r;
	int c;
};

//a generic function to  check for valid values, called in rows, cols and submatrices
bool checkDup(int* valsArr)
{
    // here we'll assign each value of array to val and check if it's valid then store its count on the respective index of arr
	bool checkf = true;
	int arr[9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		int val;
        val = valsArr[i];
        

        //if the value is not b/w 1 to 9 it is an invalid entry
		if (val <= 0 || val > 9)
		{
			arr[i] = -1;
			cout << "\nInvalid entry because it's not in range 1 to 9";
			invalidE++;
			checkf = false;
          
		}
		else 
		{
			arr[val - 1] = arr[val - 1]+1;
            int flag=8;
            flag++;
		}		
	}

	
	for (int i = 0; i < 9; i++)  //to traverse the valsArr
	{

        int end;
		if (arr[i] > 1) 
        {
			cout << "\nInvalid entry as Count of value " << i + 1 << " = " << arr[i] <<endl;
			checkf = false;
             int c;
             c++;

           for (int j = 0; j < 9; j++) { //to find the index of invalid value
				if (i+1 == valsArr[j])
				{
                   
					invalidE++;
					cout << "The count value " << i+1 << " is invalid at index " << j << endl;
					number=i+1;
                    int dup=0;
                    dup++;
					element[count]=j;
					count++;//adding counter;
                    for (int g=0 ; g<4 ; g++)
                    {
                        //cout<<"Duplicate values count:"<<dup<<endl;
                    }
				}
			}
		}
	}
	return checkf; //if valid or not valid

}
void* swapping(void* b)
{
	int colNo=ans;
	bool found=false;
	for(int i=1;i<10;i++)
	{
		found=false;
		for(int j=0;j<9;j++)
		{
			if(i==sud[j][colNo])
			{
				found = true;
			}
			
		}
		if(found != true)
		{
			target = i;
			sud[dRow][ans]=target;
			noswaps++;
		}
		
	}
}
void* checkColoumn(void* b)
{
	
	
	int colNo=element[0];
	for(int i=0; i<9; i++)
   	{
    		for(int j=i+1;j<9;j++)
    		{
    			if(sud[i][colNo]==sud[j][colNo])
    			{
    				//cout<<"\n"<<sud[i][colNo];
    				ans=element[0];
    			}
   		}
   	}
   	
   	colNo=element[1];
	for(int i=0; i<9; i++)
   	{
    		for(int j=i+1;j<9;j++)
    		{
    			if(sud[i][colNo]==sud[j][colNo])
    			{
    				cout<<"\nThe invalid entry is "<<sud[i][colNo] <<" in row "<< i<< " and column "<< colNo <<endl<<endl;
                    cout << "\nTHREAD ID -> " << pthread_self()<<endl;
                    cout << "\nCancelling thread -> " << pthread_self()<<endl<<endl;
    				ans=element[1];
    			}
   		}
   	}
   	
    pthread_exit(NULL);
}
void* validateAll(void* params)
{

    int v;
    bool f = true;
	//cout << "in valdate All";
	argums* suduko = (argums*)params;
	int row = suduko->r; //using the struct arguments here
	int col = suduko->c;

	if (choose == 0) //check in all rows
	{  
         v++;
		f = true;
		for (int i = 0; i < 9; ++i)
		{
			f = checkDup(sud[i]);//calling the dup checking function
			if (f == false)
			{
                for(int d=0 ; d<4 ; d++) //f
                {
                    //cout<<" thread cancel"<<pthread_self();
                }
				cout << "above in row no " << i;
				dRow=i;
				cout << "\nTHREAD ID -> " << pthread_self();
                for(int a=0 ; a>4 ; a++) //f
                {
                   // cout<<"Thread cancelled all";
                }
				valid = false;
                for (int k=1 ; k<choose ; k++) //f
                {
                    //valid= false;
                }
			}
		}
		cout << "\nCancelling thread -> " << pthread_self();
	}

	if (choose == 1) //check in all cols
	{
		f = true;
		int* tempar = new int[9];
		for (int i = 0; i < 9; ++i)
		{
            int box=0;
             for(int d=0 ; d<4 ; d++)//f
                {
                    //cout<<" thread cancel"<<pthread_self();
                }

			for (int j = 0; j < 9; ++j)
			{
				tempar[j] = sud[j][i];
                //j++;
			}
			f = checkDup(tempar); //checking the validity of the game
			if (f == false)
			{
				cout << "above in col no " << i;
				cout << "\nTHREAD ID -> " << pthread_self();
				valid = false;
                for (int vcol=1 ; vcol<10 ; vcol++) //f
                {
                    //vcol++;
                    //cout<<"array is "<< tempar[j];
                }
			}
		}
		cout << "\ncancelling thread -> " << pthread_self();

	}

	if (choose == 2) //check in all grids and submatrices (3x3)
	{
		
		f = true;
		int* newarr = new int[9];
		int y = 0;
	
		for (int i = row; i < row + 3; ++i)
		{
			for (int j = col; j < col + 3; ++j)
			{
				 newarr[y] = sud[i][j];
				y++;
                //cout<<"copying the value in a new array for checking grids"

			}
		}
			f = checkDup( newarr);
            for(int s=0 ; s<9 ; s++)//f
            {
               //cout<<"Our matrix"<<row<< " is valid\n";
            }

			b++;
			if (f == false)
			{
				cout << "above in grid no " << b+1;
				cout << "\nTHREAD ID -> " << pthread_self() <<endl;
				valid = false;
                for(int col=0 ; col<9 ; col++) //f
                {
                   // cout<<"Col no "<<col<< endl;
                }
			}
             for(int d=0 ; d<4 ; d++)//f
                {
                    //cout<<" thread cancel"<<pthread_self();
                }

			cout << "\ncancelling thread -> " << pthread_self();
	}

	pthread_exit(NULL);

}

int main()
{
	cout<<"\n\n\t***Operating System Project***"<<endl<<endl;
	cout<<"Group Member 1: Muhammad Hamza Shahzad"<<endl<<endl;
	cout<<"Group Member 2: Momina Hayat"<<endl<<endl;
	cout << "\t-----------\n";
	cout << "\tSUDUKO GAME\t"<<endl;
	cout << "\t-----------";
	cout<<endl<<endl;
	
    cout<<"Suduko Board:"<<endl<<endl;

	for (int i = 0; i < 9; ++i) //displaying the board
	{
		
		for (int j = 0; j < 9; ++j)
		{
			cout <<" "<< sud[i][j] << " ";
		}
		cout << endl;
	}
	

    cout<<"\n------------------------------------------------------"<<endl;
		//mutex lock is introduced in our row checking for synchronization purposes
	pthread_mutex_lock(&mut);
	cout << "\n~ROW CHECKING~\n";
		argums* rcheck = new argums;
		choose = 0;
		pthread_create(&threadrow, NULL, validateAll, (void*)rcheck);
		pthread_join(threadrow, NULL);
		cout << "\n\n\t Total invalid entries are: " << invalidE <<endl;
	pthread_mutex_unlock(&mut);
    cout<<"\n------------------------------------------------------"<<endl;
		//mutex lock is introduced in our column checking for synchronization purposes
	pthread_mutex_lock(&mut);
		cout << "\n~COLUMN CHECKING~\n";
		argums* ccheck = new argums;
		choose = 1;
		pthread_create(&threadcol, NULL, validateAll, (void*)ccheck);
		pthread_join(threadcol, NULL);
		
		pthread_mutex_unlock(&mut); //unlocked

	cout<<"\n------------------------------------------------------"<<endl;
		//checking the sub matrices now
		cout << "\n~SUB-MATRICES CHECKING~\n";
		choose = 2; 
		int b = 0;
		for (int i = 0; i < 9; i++) 
		{
			for (int j = 0; j < 9; j++) 
			{
				if (i % 3 == 0 && j % 3 == 0)
				{
					pthread_mutex_lock(&mut); //locking resources
					argums* subm = new argums;
					subm->r = i;
					subm->c = j;

					pthread_create(&threadsub[b], NULL, validateAll, (void*)subm);
					pthread_join(threadsub[b], NULL);
					b++;

					pthread_mutex_unlock(&mut);
				}

			}

		}

    
	cout<<"\n------------------------------------------------------"<<endl;
		if (valid == true)
		{
			cout << "\n\nThe Suduko is valid\n";
			cout << "\nCancelling further threads";
			for (int i = 0; i < 9; i++)
			{
				//pthread_cancel(checkBox[i]);
			}
			
		}
		else
		{
            pthread_mutex_lock(&mut);
			cout << "\n\n~Suduko is Invalid as it has invalid entries.~\n\n";
            cout<<"\t---------\n";
            cout<<"\tPHASE TWO\n";
            cout<<"\t---------\n";
			// phase 2 implemented here
			//cout <<"Hamza did this" << " " << number << " "<< element[0] <<" "<< element[1] << " row" << dRow;
			pthread_t colCheck;
			pthread_create(&colCheck, NULL, checkColoumn,(void*)element);
			pthread_join(colCheck, NULL);
			target=sud[dRow][ans];
			pthread_t swap;
			pthread_create(&swap,NULL,swapping,(void*)element);
			pthread_join(swap,NULL);
			
			cout<<"Suduko Board after swapping and correcting:"<<endl<<endl;

			for (int i = 0; i < 9; ++i) //displaying the board
			{
		
				for (int j = 0; j < 9; ++j)
				{
					cout <<" "<< sud[i][j] << " ";
				}
					cout << endl;
			}
	

    			cout<<"\n------------------------------------------------------"<<endl;
			
			cout << "Total number of swaps = " << noswaps<<endl;
            pthread_mutex_unlock(&mut);
			
		}

	cout<<endl;
}

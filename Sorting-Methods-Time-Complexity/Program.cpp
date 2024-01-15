#include <iostream>
#include <time.h>
#include <chrono>
#include <fstream>
void Randomizer(int RandomArray[])
{
	int Num;                            // this function randomizes the array
	srand(time(NULL));
	for (int i = 0; i < 100000; i++)
	{
		Num = rand() % 100000;
		RandomArray[i] = Num;
	}
}
void Selection(int Arr[],double &Avg,int flag)
{
	Avg = 0;
	int n = 100000;
	int small, temp;
	for (int total = 1; total <= 10; total++)
	{
		auto start = std::chrono::high_resolution_clock::now(); // Start the timer

		for (int i = 0; i < n - 1; i++)
		{
			small = i;
			for (int j = i + 1; j < n; j++)
			{
				if (Arr[j] < Arr[small])
				{
					small = j;
				}

			}
			if (small != i)
			{
				temp = Arr[small];
				Arr[small] = Arr[i];
				Arr[i] = temp;
			}
		}
		auto stop = std::chrono::high_resolution_clock::now(); // Stop the timer
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		Avg = Avg + duration.count();
		if (flag == 1)
		{
			Randomizer(Arr);
		}
	}
	Avg = Avg / 10;


}

void Bubble(int Arr[], double& Avg,int flag)
{
	Avg = 0;
	int n = 100000;
	int Check=0, temp;
	//int Arr[] = { 36,2,1,4,5 };

	for (int total = 1; total <= 10; total++)
	{
		auto start = std::chrono::high_resolution_clock::now(); // Start the timer

		for (int j = 0; j < n - 1; j++)
		{
			Check = 0;
			for (int i = 0; i < n - j - 1; i++) // here, we are substracting the j  because after j iterations, the last terms are already adjusted, so need to check those terms
			{

				if (Arr[i] > Arr[i + 1])
				{
					temp = Arr[i];
					Arr[i] = Arr[i + 1];
					Arr[i + 1] = temp;
					Check = 1;
				}
			}
			if (Check == 0) 
			{
				break;
			}
		}
		auto stop = std::chrono::high_resolution_clock::now(); // Stop the timer
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		Avg = Avg + duration.count() ;
		if (flag == 1) 
		{
			Randomizer(Arr);
		}
	}
	Avg = Avg / 10;

	

}
void insertion(int Arr[], double& Avg,int flag)
{
	int n = 100000;
	int value, point;
	for (int total = 1; total <= 10; total++)
	{
		auto start = std::chrono::high_resolution_clock::now(); // Start the timer

		for (int i = 1; i < n; i++)
		{
			point = i;
			value = Arr[i];
			while (point > 0 && value < Arr[point - 1]) {
				Arr[point] = Arr[point - 1];
				point--;
			}
			Arr[point] = value;
		}
		auto stop = std::chrono::high_resolution_clock::now(); // Stop the timer
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		Avg = Avg + duration.count() ;
		if (flag == 1)
		{
			Randomizer(Arr);
		}
	}
	Avg = Avg / 10;

}
	

void Sorted(int Arr[])
{                                  // creates a sorted array
	for (int i = 0; i <100000; i++)
	{
		Arr[i]=i;
	}
}


int main()
{
	std::cout << "please wait, sorting 3 million values will take up 10 mins" << std::endl;
	std::fstream data;
	double average = 0;
	int Flag = 1;

	double SelectionAvg[2] = { 0 }, BubbleAvg[2] = { 0 }, insertionAvg[2] = { 0 };
	int RandomArray[100000];
	int SortedArray[100000];
	Sorted(SortedArray);
	// for average case
	Randomizer(RandomArray);   
	Selection(RandomArray, average,Flag); // sorts the array 10 times
	SelectionAvg[0] = average;
	Randomizer(RandomArray);
	Bubble(RandomArray,average,Flag);
	BubbleAvg[0] = average;
	insertion(RandomArray, average, Flag);
	insertionAvg[0] = average;

	Flag = 0;

	// for best case

	Selection(SortedArray, average, Flag); 
	SelectionAvg[1] = average;
    Bubble(SortedArray, average, Flag);
	BubbleAvg [1] = average;
	insertion(SortedArray, average, Flag);
	insertionAvg[1] = average;


	//writing the results here
	data.open("Results1.csv", std::ios::out);
	if (data.is_open())
	{
		data << "Algorithm,ArraySize,ArrayType,Numberofruns,Average_Time" << std::endl;
		data << "Selection,100k,Random,10," << SelectionAvg[0] << " MicroSecs" << std::endl;
		data << "Selection,100k,sorted,10," << SelectionAvg[1] << " MicroSecs" <<std:: endl;

		data << "Bubble,100k,Random,10," << BubbleAvg [0]<< " MicroSecs" <<std:: endl;
		data << "Bubble,100k,sorted,10," << BubbleAvg[1] << " MicroSecs" <<std:: endl;

		data << "Insertion,100k,Random,10," << insertionAvg[0] << " MicroSecs" <<std:: endl;
		data << "Insertion,100k,sorted,10," << insertionAvg[1] << " MicroSecs" <<std:: endl;



	}
	data.close();


}


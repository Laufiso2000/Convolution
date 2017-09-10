#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define FILTER_SIZE 32
int main(){

	float x[FILTER_SIZE];	
	float h[FILTER_SIZE];
	float tempH; 
	float y = 0; 
	int i = 0;
	
	float start_time = 0; 
	float end_time = 0; 
 
	
	FILE* dataFile = fopen("signal.txt","r");
	if(dataFile == NULL) printf("signal broke\n");

	FILE* outputFile = fopen("outputFile.txt","w");
	if(outputFile == NULL) printf("outputFile broke\n");

	FILE* tapWeightsFile = fopen("coeff.txt","r");
	if(tapWeightsFile == NULL) printf("coefficients broke\n");

	printf("initializeing values\n");
  	//initialize arrays to 0. 
	for (i = 0; i<FILTER_SIZE;i++){
		x[i] = 0;
		h[i] = 0; 
	}
	
	printf("getting tap weights\n");
	//get the coefficients
	
	i = 0; 
	while(!feof(tapWeightsFile)){

		fscanf(tapWeightsFile,"%f",&h[i]);
		i++;  
	}


	printf("performing filtering\n");

	start_time = (float)clock()/CLOCKS_PER_SEC;

	//get each sample point until EOF is found 
	while(!feof(dataFile)){

		fscanf(dataFile, "%f", x);

		//perform the convolution 
		y = 0; 
		for(i=0; i< FILTER_SIZE; i++){
			y += x[i] * h[i]; 
		}

		//time delay samples by 1 time unit. 
		for(i=FILTER_SIZE-2; i > 0; i--){
			x[i+1] = x[i];
		}

		//print results to file
		fprintf(outputFile,"%f\n",y);

	}//end of while fscanf

	end_time = (float)clock()/CLOCKS_PER_SEC;

	printf("total time = %f\n",(end_time-start_time));

	//clean house 
	fclose(tapWeightsFile);
	fclose(dataFile);
	fclose(outputFile);
	

	return 0; 
}//end of main method
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;


	int main()
	{
		
		int number=0;//number of symbols in the alphabet
		int i=0, j=0;//i and j are loop control variables
		double temp_d;//temporary variable for double datatype
		char temp_c;//temporary variable for character datatype
		cout<<"Enter the number of message symbols in the source alphabet"<<endl;
		cin>>number;
		char c[number];//array of symbols
		double prob[number];//array of probabilities of symbols
		double psum = 0;//psum is the sum of all probabilities of symbols. It should always be 1
		int cycles = number-2;//cycles is the number of stages involved in the huffman tree generation
		int lastc = 0;//lastc is the last relevant variable in the column of the probabilites
		double lsum = 0;//lsum is the sum of the last 2 elements in the column of the probabilities
		string codewords[number];
		string symbols[number];
		cout<<"Enter the character of representation of each of the message symbols"<<endl;
		for(i=0;i<number;i++)
		{
			cin>>c[i];
		}

		for(i=0;i<number;i++)
		{
			cout<<"Enter the probability for "<<c[i]<<endl;
			cin>>prob[i];
			psum = psum + prob[i];
			if(prob[i] < 0 || prob[i] > 1)
			{
				cout<<"Impossible probability encountered. Terminating huffman module with return code 1"<<endl;
				return 1;
			}
		}

		if(psum!=1)
		{
			cout<<"Error:Sum of probabilities does not add up to 1.0"<<endl;
			cout<<"Terminating huffman module with error code 2"<<endl;
			return 2;
		}

		for(i=0;i<number;i++)
		{
			
			for(j=0;j<number-1;j++)
			{
				if(prob[j]<prob[j+1])
				{
					temp_d = prob[j];
					prob[j] = prob[j+1];
					prob[j+1] = temp_d;
				

					temp_c = c[j];
					c[j] = c[j+1];
					c[j+1] = temp_c;

				}
			}
		}



		cout<<"Probabilities sorting complete. Symbol:Probability array-"<<endl;
		for(i=0;i<number;i++)
		{
			cout<<c[i]<<":"<<prob[i]<<endl;
		}

		//the first column of the codewords array will now contain the number of their symbols
		for(i=0;i<number;i++)
		{
			codewords[i] = c[i];
			symbols[i] = "";
			cout<<codewords[i]<<endl;
		}
		string symname = "";
		//Produce the huffman tree
		cout<<"Beginning huffman tree generation cycles now..."<<endl;
		cout<<cycles<<" number of cycles left"<<endl;
		lastc = number-1;
		int column = 0;
		//symbols[lastc] +="1";
		//symbols[lastc-1] +="0";
		while(cycles>0)
		{
			cout<<"Length is "<<codewords[lastc].length()<<endl;
			cout<<"Codeword 0 is "<<codewords[lastc-1];
			cout<<"Codeword 1 is "<<codewords[lastc];
			for(i=0;i<codewords[lastc-1].length();i++)
			{
				for(j=0;j<number;j++)
				{
					if(c[j]==codewords[lastc-1].at(i))
						break;
				}
				cout<<"Codeword character is "<<c[j]<<endl;
				symbols[j] += "0";
			}
			cout<<"----------------------------------------------"<<endl;

			for(i=0;i<codewords[lastc].length();i++)
			{
				for(j=0;j<number;j++)
				{
					if(c[j]==codewords[lastc].at(i))
						break;
				}
				cout<<"Codeword character is "<<c[j]<<endl;
				symbols[j] += "1";
			}
			cout<<"----------------------------------------------"<<endl;
			cout<<"Codeword status"<<endl;
			for(j=0;j<number;j++)
			{
				cout<<symbols[j]<<"              "<<codewords[j]<<endl;
			}


			cout<<"Testing here"<<endl;

			prob[lastc-1] += prob[lastc];
			prob[lastc] = 0;
			codewords[lastc-1] += codewords[lastc];
			symname = codewords[lastc-1];
			codewords[lastc] = "_";
			psum = prob[lastc-1];
			i = lastc-2;
			while(prob[lastc-1] > prob[i] && i>=0)
			{
				i--;
			}
			
			for(j=lastc-1;j>i+1;j--)
			{
				prob[j] = prob[j-1];
				codewords[j] = codewords[j-1];
			}
			prob[i+1] = psum;
			codewords[i+1] = symname;
			cout<<"Probability status"<<endl;
			for(j=0;j<number;j++)
			{
				cout<<prob[j]<<endl;
			}

			
			
			if(cycles==1)
			{
				break;
			}
			

			

			lastc--;
			cycles--;
			cout<<"Cycles left:"<<cycles<<endl;

		}

		cout<<"Codeword generation almost complete..."<<endl;
		cout<<"Updating last cycle bits to codewords..."<<endl;
		cout<<"Last symbol is "<<codewords[lastc-1]<<endl;
		cout<<"Last but one symbol is "<<codewords[lastc-2]<<endl;
		for(i=0;i<codewords[lastc-1].length();i++)
			{
				for(j=0;j<number;j++)
				{
					if(c[j]==codewords[lastc-1].at(i))
						break;
				}
				cout<<"Codeword character is "<<c[j]<<endl;
				symbols[j] += "1";
			}
			cout<<"----------------------------------------------"<<endl;

			for(i=0;i<codewords[lastc-2].length();i++)
			{
				for(j=0;j<number;j++)
				{
					if(c[j]==codewords[lastc-2].at(i))
						break;
				}
				cout<<"Codeword character is "<<c[j]<<endl;
				symbols[j] += "0";
			}
		cout<<"----------------------------------------------"<<endl;

cout<<"Codeword generation complete..."<<endl;
cout<<"Reversing codewords to get prefix codes..."<<endl;
cout<<endl<<endl<<endl<<endl<<endl;
cout<<"Final codewords are "<<endl;
		for(i=0;i<number;i++)
		{
			reverse(symbols[i].begin(), symbols[i].end());
			cout<<c[i]<<"\t"<<symbols[i]<<endl;
		}



	}
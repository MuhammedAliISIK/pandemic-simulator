/*
	Muhammed Ali Işık
	github.com/MuhammedAliISIK/
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class Entities
{
	public:
		string gate;
		int status,positionx,positiony,incubationcounter,infectioncounter;
		/*
			if
				status=0 immune
				status=1 potential carrier(carries the disease but don't die. Don't have 3 of A,B,C,D)
				status=2 potential sick(healthy but can be sick. have 3 of A,B,C,D)
				status=3 infected    status=-3 infected from start    status=-1 infected carrier
				status=4 dead
				status=5 removed
				status=6 recovered
		*/

};


int main()
{
	ifstream info;
	info.open("input.txt",ios::in);
	if(info.fail())
	{
		cerr<<"Error opening file";
	}

	//defining variables
	int turn,size,numoflines=0,immunecounter,potentialcounter,xpos,poscounter,normalcounter=0,infcounter=0,deathcounter=0;
	string temp="",postemp="",line,strsize,strturn;
    while (getline(info, line))
        ++numoflines;


	info.close();
	info.open("input.txt",ios::in);


	//getting size value
	getline(info,strsize);
	if((int)strsize[6]>=48 && (int)strsize[6]<=57)
	{
		size=10*((int)strsize[5]-48)+(int)strsize[6]-48;
	}
	else
	{
		size=(int)strsize[5]-48;
	}


	char environment[size+2][size+2];

	//getting turn value
	getline(info,strturn);
	if((int)strturn[12]>=48 && (int)strturn[12]<=57)
	{
		turn=10*((int)strturn[11]-48)+(int)strturn[12]-48;
	}
	else
	{
		turn=(int)strturn[11]-48;
	}


	info.close();
	info.open("input.txt",ios::in);


	//getting entity information
	int numofentities=numoflines-(turn+2);


	Entities entityinfo[numofentities];

	getline(info,line);
	getline(info,line);

	//reading entity's gates, starting position and checking if it is infected or not at the beginning
	for(int i=0;i<numofentities;i++)
	{
		getline(info,temp);
		if(i>=9)//getting gate information
		{
			entityinfo[i].gate=temp.substr(10,5);
		}
		else
		{
			entityinfo[i].gate=temp.substr(9,5);
		}

		if(temp[22] == 'i' || temp[22] == 'n' || temp[22] == 'f' || temp[22] == 'e')
		{
			entityinfo[i].status=3;
		}
		temp[22]=' ';


		if(i>=9)//getting starting position information
		{
			postemp=temp.substr(16,5);
		}
		else
		{
			postemp=temp.substr(15,5);
		}

		for(int j=0;j<5;j++)
		{
			if((int)postemp[j] == 120)
			{
				xpos=j;
			}
		}

		if(xpos==1)
		{
			entityinfo[i].positionx = (int)postemp[0]-48;
			if((int)postemp[xpos+2]>=48 && (int)postemp[xpos+2]<=57)
			{
				entityinfo[i].positiony = 10*((int)postemp[2]-48)+((int)postemp[3]-48);
			}
			else
			{
				entityinfo[i].positiony = (int)postemp[2]-48;
			}
		}
		else if(xpos == 2)
		{
			entityinfo[i].positionx = 10*((int)postemp[0]-48)+((int)postemp[1]-48);
			if((int)postemp[xpos+2]>=48 && (int)postemp[xpos+2]<=57)
			{
				entityinfo[i].positiony = 10*((int)postemp[3]-48)+((int)postemp[4]-48);
			}
			else
			{
				entityinfo[i].positiony = (int)postemp[2]-48;
			}
		}

	}


	//processing entity's gates, checking immunity
	for(int i=0;i<numofentities;i++)
	{
		immunecounter=0;
		potentialcounter=0;
		for(int j=0;j<5;j++) //checking entity's status
		{
			if(entityinfo[i].gate[j] == 'A' || entityinfo[i].gate[j] == 'B' ) //checking if entity is immune
			{
				immunecounter=1;
			}

			if(entityinfo[i].gate[j] == 'A' || entityinfo[i].gate[j] == 'B' || entityinfo[i].gate[j] == 'C' || entityinfo[i].gate[j] == 'D') //checking if entity is potential carrier or potential sick
			{
				potentialcounter++;
			}

		}


		if(immunecounter == 0)
		{
			entityinfo[i].status=0;
		}
		else if((entityinfo[i].status == 3) && (potentialcounter < 3))
		{
			entityinfo[i].status = -1;
			continue;
		}
		else if(entityinfo[i].status == 3)
		{
			continue;
		}
		else if(immunecounter == 1 && potentialcounter<3)
		{
			entityinfo[i].status=1;
		}
		else if(immunecounter == 1 && potentialcounter>=3)
		{
			entityinfo[i].status=2;
		}
	}


	int a,casecount=0,infcount=0,incubatedcount=0,recoveredcounter=0;
	int turnxpos[numofentities+1],potcases[numofentities-1],potinfectors[numofentities-1],incentities[numofentities-1];
	string strpos;
	for(int i=0;i<numofentities;i++)
	{
		entityinfo[i].incubationcounter=0;
		entityinfo[i].infectioncounter=0;
	}


	//processing turns
	for(int i=1;i<=turn;i++)
	{
		getline(info,temp);

		a=0;
		casecount=0;
		infcount=0;
		for(int j=0;j<temp.length();j++) //gettin positions of 'x' in a line to use it for getting positions
		{
			if(temp[j] == 'x')
			{
				turnxpos[a]=j;

				a++;
			}
		}




		for(int j=0;j<numofentities;j++)//checking death
		{
			if((entityinfo[j].status == 3) || (entityinfo[j].status == 4))
			{
				if(entityinfo[j].infectioncounter < 14)
				{
					entityinfo[j].infectioncounter++;
				}
				else if((entityinfo[j].infectioncounter >= 14) && (entityinfo[j].infectioncounter < 19))
				{
					entityinfo[j].status=4;
					entityinfo[j].infectioncounter++;
				}
				else if((entityinfo[j].infectioncounter >= 19))
				{
					entityinfo[j].status=5;
				}
			}



			if(entityinfo[j].status == -1)
			{
				entityinfo[j].infectioncounter++;
				if((entityinfo[j].infectioncounter == 29))
				{
					recoveredcounter++;
					entityinfo[j].status=6;
				}
			}
		}


		//getting entities' positions for each turn
		for(int j=0;j<numofentities;j++)
		{
			if(entityinfo[j].status <= 3)
			{
					if((j != numofentities-1) && ((int)temp[turnxpos[j]-2])!= 32 && ((int)temp[turnxpos[j]+2] != 32))
					{
						entityinfo[j].positionx = 10*((int)temp[turnxpos[j]-2]-48)+((int)temp[turnxpos[j]-1]-48);
						entityinfo[j].positiony = 10*((int)temp[turnxpos[j]+1]-48)+((int)temp[turnxpos[j]+2]-48);
					}
					else if((j != numofentities-1) && ((int)temp[turnxpos[j]-2] == 32) && ((int)temp[turnxpos[j]+2] != 32))
					{
						entityinfo[j].positionx = ((int)temp[turnxpos[j]-1]-48);
						entityinfo[j].positiony = 10*((int)temp[turnxpos[j]+1]-48)+((int)temp[turnxpos[j]+2]-48);
					}
					else if((j != numofentities-1) && ((int)temp[turnxpos[j]-2] != 32) && (((int)temp[turnxpos[j]+2] == 32) || ((int)temp[turnxpos[j]+2] == 0)))
					{
						entityinfo[j].positionx = 10*((int)temp[turnxpos[j]-2]-48)+((int)temp[turnxpos[j]-1]-48);
						entityinfo[j].positiony = ((int)temp[turnxpos[j]+1]-48);

					}
					else if((j != numofentities-1) && ((int)temp[turnxpos[j]-2] == 32) && (((int)temp[turnxpos[j]+2] == 32) || ((int)temp[turnxpos[j]+2] == 0)))
					{
						entityinfo[j].positionx = ((int)temp[turnxpos[j]-1]-48);
						entityinfo[j].positiony = ((int)temp[turnxpos[j]+1]-48);
					}


					if((int)temp[turnxpos[numofentities-1]+2] == 0 ) //last entity's position is calculated in this block
					{
						if(((int)temp[turnxpos[numofentities-1]-2] != 32))
						{
							entityinfo[numofentities-1].positionx = 10*((int)temp[turnxpos[numofentities-1]-2]-48)+((int)temp[turnxpos[numofentities-1]-1]-48);
							entityinfo[numofentities-1].positiony = ((int)temp[turnxpos[numofentities-1]+1]-48);
						}
						else if(((int)temp[turnxpos[numofentities-1]-2] == 32))
						{
							entityinfo[numofentities-1].positionx = ((int)temp[turnxpos[numofentities-1]-1]-48);
							entityinfo[numofentities-1].positiony = ((int)temp[turnxpos[numofentities-1]+1]-48);
						}
					}
					else if((int)temp[turnxpos[numofentities-1]+3] == 0)
					{
						if(((int)temp[turnxpos[numofentities-1]-2]) != 32)
						{
							entityinfo[numofentities-1].positionx = 10*((int)temp[turnxpos[numofentities-1]-2]-48)+((int)temp[turnxpos[numofentities-1]-1]-48);
							entityinfo[numofentities-1].positiony = 10*((int)temp[turnxpos[numofentities-1]+1]-48)+((int)temp[turnxpos[numofentities-1]+2]-48);
						}
						else if(((int)temp[turnxpos[numofentities-1]-2] == 32))
						{
							entityinfo[numofentities-1].positionx = ((int)temp[turnxpos[numofentities-1]-1]-48);
							entityinfo[numofentities-1].positiony = 10*((int)temp[turnxpos[numofentities-1]+1]-48)+((int)temp[turnxpos[numofentities-1]+2]-48);
						}
					}
				}
		}


		for(int j=0;j<numofentities;j++)
		{
			if((entityinfo[j].status == 1) || (entityinfo[j].status == 2))
			{
				potcases[casecount]=j;// saves possible cases
				casecount++;
			}

		}



		for(int j=0;j<numofentities;j++)
		{
			if(((entityinfo[j].status == 3) || (entityinfo[j].status == 4) || (entityinfo[j].status == -1)))
			{
				potinfectors[infcount]=j;// saves infector entities
				infcount++;
			}
		}




		for(int j=0;j<infcount;j++)
		{
			for(int k=0;k<casecount;k++)
			{
				if(entityinfo[potcases[k]].status == 1 || entityinfo[potcases[k]].status == 2)
				{
						if(entityinfo[potcases[k]].incubationcounter == 0)
						{
							entityinfo[potcases[k]].infectioncounter=0;

							if(((entityinfo[potinfectors[j]].positionx -  entityinfo[potcases[k]].positionx <= 3) && (entityinfo[potinfectors[j]].positionx -  entityinfo[potcases[k]].positionx >= -3)) && ((entityinfo[potinfectors[j]].positiony -  entityinfo[potcases[k]].positiony <= 3) && (entityinfo[potinfectors[j]].positiony -  entityinfo[potcases[k]].positiony >= -3)))
							{
								if(entityinfo[potcases[k]].status == 1)
								{
									entityinfo[potcases[k]].incubationcounter=1;
								}
								else if(entityinfo[potcases[k]].status == 2)
								{
									entityinfo[potcases[k]].incubationcounter=1;
								}
							}

						}

				}
			}

		}

		//processing incubation
		for(int j=0;j<casecount;j++)
		{
			if((entityinfo[potcases[j]].status == 1) || (entityinfo[potcases[j]].status == 2))
			{
				if((entityinfo[potcases[j]].incubationcounter > 0 ) && (entityinfo[potcases[j]].incubationcounter < 3))
				{
					entityinfo[potcases[j]].incubationcounter++;
					break;
				}
				else if(entityinfo[potcases[j]].incubationcounter == 3)
				{
					if(entityinfo[potcases[j]].status == 1)
					{
						entityinfo[potcases[j]].status = -1;
						entityinfo[potcases[j]].infectioncounter=0;
					}
					else if(entityinfo[potcases[j]].status == 2)
					{
						entityinfo[potcases[j]].status = 3;
					}
					entityinfo[potcases[j]].incubationcounter++;
				}

			}
		}


	ofstream turns;
	turns.open("turns.txt",ios::app);

	for(int i=0;i<size+2;i++)
	{

		environment[0][i]='-';
		environment[i][0]='-';
		environment[i][size+1]='-';
		environment[size+1][i]='-';
	}
	for(int i=1;i<size+1;i++)
	{
		for(int j=1;j<size+1;j++)
		{
			environment[i][j]=' ';
		}
	}



	for(int m=0;m<numofentities;m++)
	{
		if((entityinfo[m].status == 0) || (entityinfo[m].status == 1) || (entityinfo[m].status == 2) || (entityinfo[m].status == 6))
		{
			environment[entityinfo[m].positionx][entityinfo[m].positiony]='O';
		}
		else if((entityinfo[m].status == 3) || (entityinfo[m].status == -1))
		{
			environment[entityinfo[m].positionx][entityinfo[m].positiony]='X';
		}
		else if((entityinfo[m].status == 4))
		{
			environment[entityinfo[m].positionx][entityinfo[m].positiony]='D';
		}

	}

	turns<<"Turn: "<<i<<endl;
	for(int i=0;i<size+2;i++)
	{
		for(int j=0;j<size+2;j++)
		{
			turns<<environment[i][j];
		}
		turns<<endl;
	}

	}





	for(int i=0;i<numofentities;i++)
	{
		if((entityinfo[i].status == 0) || (entityinfo[i].status == 1) || (entityinfo[i].status == 2))
		{
			normalcounter++;
		}
		else if((entityinfo[i].status == 3) || (entityinfo[i].status == -1))
		{
			infcounter++;
		}
		else if((entityinfo[i].status == 4) || (entityinfo[i].status == 5))
			deathcounter++;
	}
	info.close();
	ofstream output;
	output.open("output.txt",ios::out);



	output<<"Normal: "<<normalcounter<<endl;
	output<<"Infected: "<<infcounter<<endl;
	output<<"Dead: "<<deathcounter<<endl;
	output<<"Recovered: "<<recoveredcounter<<endl;

	for(int i=0;i<numofentities;i++)
	{
		if((entityinfo[i].status == 3) || (entityinfo[i].status == -1))
			output<<"Entity "<<i+1<<" "<<entityinfo[i].positionx<<"x"<<entityinfo[i].positiony<<" infected"<<endl;
		else if((entityinfo[i].status == 1) || (entityinfo[i].status == 2) || (entityinfo[i].status == 0) || (entityinfo[i].status == 6))
			output<<"Entity "<<i+1<<" "<<entityinfo[i].positionx<<"x"<<entityinfo[i].positiony<<" normal"<<endl;
		else if((entityinfo[i].status == 4) || (entityinfo[i].status == 5))
			output<<"Entity "<<i+1<<" "<<entityinfo[i].positionx<<"x"<<entityinfo[i].positiony<<" dead"<<endl;
	}



	return 0;

}

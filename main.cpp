#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//This function will output responses based on the number inputed from choices 0 1 and 2
void hazardFunction(int choices)
{
  if (choices == 0)
      {
        cout << "There is a stop sign approaching ahead of you.";
        cout << " Remember to stop." << endl;
      }
      //the number 1 represents a red light
      else if (choices == 1)
      {
        cout << "There is a traffic signal approaching ahead of you.";
        cout << " Remember to stop if the lights are red." << endl;
      }
      //the number 2 represents an accident
      else if(choices == 2)
      {
        cout << "There is an accident in the route.";
        cout << " Remember to drive slow." << endl;
      }
}

//the main function
int main() {
  const int HOURS = 23;
  //to greet the user
  string userName = "User Name";
  bool carOn = true;
  srand(time(0));
  int timeCurrent = rand() % HOURS;
  string locationFile = "data.txt";
  string locations[HOURS];
  ifstream inputFile;

  if(carOn == true)
  {
    cout << "Welcome Back <" << userName << ">" << endl;

    //opening an input file name stored in variable locationFile
    inputFile.open(locationFile);
    if(inputFile.is_open())
    {
      //copies the content from the file into an array called       
      //locations[]
      for(int i = 0; i < HOURS; i++)
      {
        getline(inputFile, locations[i]);
      }
      //displays the time when the user accesses the car
      cout << "Currently it is " << timeCurrent << ":00" << endl;
      cout << endl;
      
    //Checking if there is a task to be completed at the time
    //"None" represents that there are no tasks to do
    if (locations[timeCurrent] == "None")
    { 
      //following messages are displayed when there are no places to go
      cout << "There is nothing scheduled for " << timeCurrent << ":00" << endl;
      cout << "Sending notification to a family member stating that the driver tried to access the car." << endl << endl;
      while(locations[timeCurrent] == "None")
        {
          //If there are no tasks to be completed, it checks for the upcoming times until there is a task 
          for(int i = timeCurrent; i < HOURS; i++)
          {  
            //cout << endl;
            //cout << "Checking for " << i+1 << ":00" << endl;
            if(locations[i+1] != "None")
            {
              //displays the upcoming tasks 
              cout << "You have " << locations[i+1] << " scheduled at " << (i+1) << ":00" << endl;
              cout << "Sending notification to a family member stating";
      cout << " that the driver is accessing the car." << endl;
      cout << "Starting directions to " << locations[i+1] << endl;
      cout << "Sending you over to the GPS system..." << endl;
              break;
            } 
          }
          break;
        }
    }
    //if there is a task assigned for the time when the user enters
    //then it directs the user to complete that task
    else
    {
      cout << "You have " << locations[timeCurrent] << " scheduled at " << timeCurrent << ":00" << endl;
      cout << "Sending notification to a family member stating";
      cout << " that the driver is accessing the car." << endl;
      cout << "Starting directions to " << locations[timeCurrent] << endl;
      cout << "Sending you over to the GPS system..." << endl;
      }
    }
    inputFile.close();
  }


  //this part of the code alerts the driver about any upcoming hazards
  
  const int NUM_OF_HAZARDS = 3;
  string hazards[NUM_OF_HAZARDS];
  int approachHazard;// = rand() % (NUM_OF_HAZARDS + 1);

  cout << endl;

  approachHazard = rand() % 3;
  hazardFunction(approachHazard);
  



  //this part of the code allows the user to make a decision if they want to complete a task during the drive 
  //it takes an input from the user and routes or re-routes accordingly
  
  const int TASKS = 4;
  //defining arrays to store the tasks and the distance from the user
  string tasks[TASKS];
  int places[TASKS];
  string tasksFile = "tasks.txt";
  int count = 0;

  //opens an input file called tasks 
  inputFile.open("tasks.txt");
  if (inputFile)
  {
    //inputs the data from the file into two arrays called tasks and places
    while (count < TASKS && inputFile >> tasks[count] >> places[count])
			count++;
		inputFile.close();
  }
  //sets the user location to 0 in this case
  int userLocation = 0;
  cout << endl;
  for (int i =0; i<TASKS; i++)
    {
      //calculates the distance between the user and a location
      //if the distance is more than 2 miles and less than or equal to 6 then the following messages are displayed
      if (places[i]-userLocation >= 2 && places[i]-userLocation <= 6)
      {
        cout << "You can complete your task: " << tasks[i] << " in " << (places[i]-userLocation) << " miles" << endl;
        string userChoice;

        //prompts the user if they want to re-route
        cout << "Would you like to complete the stated task? (Say Yes or No) ";
        cin >> userChoice;
        //the following if statement is executed if the answer is "yes"
        if (userChoice == "yes" || userChoice == "Yes")
        {
          cout << "You will now be re-routed to the location" << endl;
          cout << endl;
          approachHazard = rand() % 3;
          hazardFunction(approachHazard);
        }
        //the following statement is executed if the answer is "no"
        else 
        {
          cout << "No changes to the route will be made" << endl;
          approachHazard = rand() % 3;
          hazardFunction(approachHazard);
        }
      }
      
    }
  cout << "You have reached your destination!" << endl;
return 0;
}
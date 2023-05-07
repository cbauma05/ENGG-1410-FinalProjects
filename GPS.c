#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// structure defining our user
typedef struct user_t {
  char name[100];                     //char name allows us to read uo to 50 characters for the name of our user
  double time;                        //time will allows us to read the time of our user
  double longitude;                   //longitude, latitude, and altitude will allow us to read the position of our user
  double latitude;
  double altitude;
} user_t;

// Name and distance output
typedef struct finalLoc {
  char name[50];                      //allows us to read name of person closest to our user
  double distance;                    //allows us to read the distance of the other user and our user
} finalLoc;


// declare functions and structures
user_t scan_user();

finalLoc find_ClosestUser(finalLoc val2[], int n);

void calcDistance(user_t normal, user_t val1[], finalLoc val2[], int n);

int scanUserFile(user_t fileData[], char fileName[]);


int main() {
  user_t our_user;                                                      //giving our_user the contents of the user_t structure


  printf("Enter your name, time, and xyz coordinates...\n");            // prompts user to enter in name time and position

  our_user = scan_user();                                               //the scan user function will get the contents of the our_user variable
 
  int userCount;
  char fileName[50];
  
    printf("\nEnter the name of the input file and its extension: ");   //Promt the user for file name
    scanf("%s", fileName);        //read the file name that the user inputs
                                            

    user_t otherUser[100];                                              //Declaring otherUSer to get the same info user_t gathers
 
    userCount = scanUserFile(otherUser, fileName);                      //amt of users scanned from filename inputed by user

    finalLoc otherUserPos[userCount];                                   //finalLoc structure infrmation given to other users based on 'n' users

    calcDistance(our_user, otherUser, otherUserPos, userCount);         //find the distance of the other users

    finalLoc closestUser;                                               //get the location and distance of the closest user

    closestUser = find_ClosestUser(otherUserPos, userCount);
   
    printf("\nThe closest user to %s is %s", our_user.name, closestUser.name);
    printf("\nDistance between users: %.2lf", closestUser.distance);
     
  return 0;
}


// Input for our user
user_t scan_user() {
    user_t var;

  printf("\nName: ");
  scanf("%s", var.name);

  printf("Time: ");
  scanf("%lf", &var.time);

  printf("Longitude: ");
  scanf("%lf", &var.longitude);

  printf("Latitude: ");
  scanf("%lf", &var.latitude);

  printf("Altitude: ");
  scanf("%lf", &var.altitude);

  return var;
}


//Scan input file 1 line at a time
int scanUserFile(user_t fileData[], char fileName[]) {
  FILE *In = fopen(fileName, "r"); // open file in read mode (in file pointer)

  int numUsers;

  fscanf(In, "%d", &numUsers); // scan for number of users 

  for (int i = 0; i < numUsers; ++i) { // repeat for loop until i is less than number of other users
    fscanf(In, "%s", fileData[i].name); 
    fscanf(In, "%lf", &fileData[i].time);
    fscanf(In, "%lf", &fileData[i].longitude);
    fscanf(In, "%lf", &fileData[i].latitude);
    fscanf(In, "%lf", &fileData[i].altitude);
  }       
                          // scans each structure segment of file for each member of the user_t structure (name, time, long, lat, alt)
  return numUsers;
  
}


//finds the distance between both people
void calcDistance(user_t normal, user_t val1[], finalLoc val2[], int n) {
  for (int i = 0; i < n; i++) {

    strcpy(val2[i].name, val1[i].name); // get coordinate values of closest person to use for the distance calculation

   double longsum, latsum, altsum, totalsum; // declaring variables to simplify square root function

   longsum = (normal.longitude - val1[i].longitude) * (normal.longitude - val1[i].longitude);
   latsum = (normal.latitude - val1[i].latitude) * (normal.latitude - val1[i].latitude);
   altsum = (normal.altitude - val1[i].altitude) *  (normal.altitude - val1[i].altitude);
   totalsum = longsum + latsum + altsum;

   val2[i].distance = sqrt(totalsum); 
  }
}


//will find the closest person by comparing distance
finalLoc find_ClosestUser(finalLoc val2[], int n) { //val2 is name of array for finalLoc structure (which stores: closest user name and distance)
  finalLoc val;
  val = val2[0];
  for (int i = 1; i < n; ++i) { // val2 will increment in user data from the structure and compare each of the users distances
    if (val2[i].distance < val.distance) { // the user with the closest distance will be set equal to val
      val = val2[i];
    }
  }
  return val;
}
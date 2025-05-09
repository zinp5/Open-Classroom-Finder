/*
improved parsing of schedule builder times

Takes raw schedule builder output
parses into clean sets of either human readable or csv output file

Input: raw html of schedule builder, must pipe
Output: cleaned csv of schedule builder, must pipe
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/*
----------------- pseudo ----------------------
if we enter a meeting
	until we exit the meeting
		if we enter a set
			until we enter a set
				parse
					check if the line is big enough,, check if line content matches what is desired

cleanup parse,, add individual days when possibles (sometimes a class is held on multiple days)


>>>>>>>>>>>>>>>>>>>>> understand the difference between object and map_object2 before going deep <<<<<<<<<<<<<<<<<<<<<<<<<
object vector :::: holds raw unclean lines that have the data

...we clean lines and then put those lines into....

object map 2 :::: holds clean data
	index by day & hall, then = rest of data
----------------- pseudo ----------------------

-------------- note that --------------------
Non-meeting
	meeting
		set 1
		set 2
		set x
set is what contains meeting times
	different set for same class means that class meets at 2+ spots (lab, discussion, lec @ diff time & place)
-------------- note that --------------------

*/


//=================== object class ===============================
struct coursetimesandlocation{

	string hall;
	string starttime;
	string endtime;
	string room;
	string day;

	void printone(){
		
		cout << "day: " << day 
			<< "\t" << "start: " << starttime 
			<< "\t" << "end: " << endtime
			<< "\t" << "hall: " << hall
			<< "\t" << "room: " << room 
			<< '\n';
	}

};


void printmap2readable( unordered_map< string, unordered_map<string, vector<coursetimesandlocation>> >& map_object2 ){
	for (const auto& day_pair : map_object2) {              // day_pair is (key=day, value=halls)
		//cout << "Day: " << day_pair.first << '\n';

		for (const auto& hall_pair : day_pair.second) {     // hall_pair is (key=hall, value=vector)
			//cout << "  Hall: " << hall_pair.first << '\n';

			for (const auto& course : hall_pair.second) {   // course is coursetimesandlocation
				cout << "Day: " << day_pair.first << " "
						<< "Hall: " << hall_pair.first << " "
						<< "Start: " << course.starttime << " "
						<< "End: " << course.endtime << " "
						<< "Room: " << course.room << "\n";
			}
		}
	}
}

void printmap2csv( unordered_map< string, unordered_map<string, vector<coursetimesandlocation>> >& map_object2 ){
	for (const auto& day_pair : map_object2) {              // day_pair is (key=day, value=halls)
		//cout << "Day: " << day_pair.first << '\n';

		for (const auto& hall_pair : day_pair.second) {     // hall_pair is (key=hall, value=vector)
			//cout << "  Hall: " << hall_pair.first << '\n';

			for (const auto& course : hall_pair.second) {   // course is coursetimesandlocation
				cout << day_pair.first << ","
						<< hall_pair.first << ","
						<< course.starttime << ","
						<< course.endtime << ","
						<< course.room << "\n";
			}
		}
	}
}

//=================== object class ===============================


//-------------------- proto funcs ------------------
	//--------- meeting checks -------------
	bool checkifmeeting(const string& given);
	bool checkifendmeeting(const string& given);
	bool checkifmeeting2(const string& given);
	bool checkifendmeeting2(const string& given);
	//--------- meeting checks -------------

	//------------ check main data ---------------
	bool checkifendtime(const string& given);
	bool checkifstarttime(const string& given);
	bool checkifhall(const string& given);
	bool checkifroom(const string& given);
	bool checkifday(const string& given);
	//------------ check main data ---------------

	//-------------- clean up data ----------------
	void cleanupstart(string& given);
	void cleanupend(string& given);
	void cleanuphall(string& given);
	void cleanuproom(string& given);
	void cleanupday(string& given);
	//-------------- clean up data ----------------
//-------------------- proto funcs ------------------


//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//============================================== main ========================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
int main(){

	string holding; //holds raw

	vector<coursetimesandlocation> object; //holds raw lines

	
	//double map where key1 is day and <key2, value> is hall and vector of remaining data
	
				   //day                 //hall        list of object
	unordered_map< string, unordered_map<string, vector<coursetimesandlocation>> > map_object2; //holds clean lines
	
	
	//======================================= while reading ==============================
	while( getline(cin, holding) ){

		//------------------- if we enter a meeting ---------------------
		if( checkifmeeting(holding) ){

			//-------------- until we reach end of meeting --------------------
			while( checkifendmeeting(holding) ){

				getline(cin,holding); //grab next line
				
				//---------------- if we enter a set ----------------
				if( checkifmeeting2(holding) ){

					object.push_back({"n","n","n","n", "n"}); //create new object
					//------------- until we reach end of set -----------------
					while( checkifendmeeting2(holding) ){

						getline(cin,holding); //grab new line

						int spotinobject = object.size()-1;
						//------------ checks and adding ----------------
							if(checkifendtime(holding)){ object[spotinobject].endtime = holding; } //add end time
							else if(checkifstarttime(holding)){ object[spotinobject].starttime = holding; } //add start time
							else if(checkifhall(holding)){ object[spotinobject].hall= holding;} //add hall
							else if(checkifroom(holding)){ object[spotinobject].room = holding;} //add room of hall
							else if(checkifday(holding)){ object[spotinobject].day = holding;} //add day of week
						//------------ checks and adding ----------------
					}
					//------------- until we reach end of set -----------------
				}
				//---------------- if we enter a set ----------------
			}	
			//-------------- until we reach end of meeting --------------------	
		}
		//------------------- if we enter a meeting ---------------------
	}
	//======================================= while reading ==============================


	//--------------------------- final cleanup ---------------------------------------
	for(int i = 0 ; i < object.size() ; i ++){
		
		cleanupstart( object[i].starttime );
		cleanupend( object[i].endtime );
		cleanuphall( object[i].hall );
		cleanuproom( object[i].room );
		cleanupday( object[i].day );
		
		//--------------------- split days up and move to map 2 ---------------------------
		//---------- if TBA ------------
		if ( object[i].day == "TBA"){ map_object2[ object[i].day ][ object[i].hall ].push_back( object[i] ); } //we dont wanna split this into days, so just add
		//and honestly, why do I even bother adding TBAs to the map? TBAs arent even considered in the timedisplayer. I could just not pushback anything...
		//---------- if TBA ------------

		//------------ if normal day, add individual days to map 2 ------------------
		else{
			for( int d = 0 ; d < object[i].day.length() ; d ++){
			
				//put the individual day char into a string (chars cannot be cast into strings (you must input string))
				string ifuckinghatecasting; ifuckinghatecasting.push_back(object[i].day[d]); //cast to string quick (create empty string, add char to it)

							//day                            hall             room, times
				map_object2[ ifuckinghatecasting ] [ object[i].hall ].push_back( object[i] ); //add object to map

			}
		}
		//------------ if normal day, add individual days to map 2 ------------------
		//--------------------- split days up and move to map 2 ---------------------------

		//object[i].printone();
	}
	//--------------------------- final cleanup ---------------------------------------


	//-------------------------- output the map2 for final output --------------------------
	//printmap2readable(map_object2); //readable version for human reading/testing
	printmap2csv(map_object2);
	//-------------------------- output the map2 for final output --------------------------

	return 0;
}
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//============================================== main ========================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
//=======================================================================================================
















//================================== cleanups ======================================
//---------------------- start clean -------------------
void cleanupstart(string& given){
	int size = given.size();
	string holdforgiven;
	if(size < 33){ given = "n";  }//if it doesnt have a time
	else{
		for(int i = 30 ; i < size-2 ; i++){
			holdforgiven.push_back(given[i]);
		}
		given = holdforgiven;
	}
	
}
//---------------------- start clean -------------------

//---------------------- end clean -------------------
void cleanupend(string& given){
	int size = given.size();
	string holdforgiven;
	if(size < 31){ given = "n";  }//if it doesnt have a time
	else{
		for(int i = 28 ; i < size-2 ; i++){
			holdforgiven.push_back(given[i]);
		}
		given = holdforgiven;
	}
	
}
//---------------------- end clean -------------------

//---------------------- hall clean -------------------
void cleanuphall(string& given){
	int size = given.size();
	string holdforgiven;
	if(size < 32){ given = "n";  }//if it doesnt have a hall
	else{
		for(int i = 29 ; i < size-2 ; i++){
			holdforgiven.push_back(given[i]);
		}
		given = holdforgiven;
	}
	
}
//---------------------- hall clean -------------------

//---------------------- clean room -------------------
void cleanuproom(string& given){
	int size = given.size();
	string holdforgiven;
	if(size < 27){ given = "n";  }//if it doesnt have a room
	else{
		for(int i = 25 ; i < size-1 ; i++){//only -1 because theres no comma at the end
			holdforgiven.push_back(given[i]);
		}
		given = holdforgiven;
	}
	
}
//---------------------- clean room -------------------

//---------------------- clean day -------------------
void cleanupday(string& given){
	int size = given.size();
	string holdforgiven;
	if(size < 31){ given = "n";  }//if it doesnt have a day
	else{
		for(int i = 31 ; i < size-2 ; i++){
			holdforgiven.push_back(given[i]);
		}
		given = holdforgiven;
	}
	
}
//---------------------- clean day -------------------
//================================== cleanups ======================================



//=============================================================================
//=============================== checking functions ===============================
//=============================================================================

//============================ check meeting ============================
//--------------- check meeting start ----------------
bool checkifmeeting(const string& given){

	string checkifmeeting =
"        \"meeting\": ["; //these must be EXACT

	if(given == checkifmeeting){ return true; }
	return false;
}
//--------------- check meeting start ----------------

//--------------- check meeting end ----------------
bool checkifendmeeting(const string& given){
	string checkifendmeeting =
"        ],";

	if(given == checkifendmeeting){ return false; }
	return true;
}
//--------------- check meeting end ----------------

//--------------- check set start ----------------
bool checkifmeeting2(const string& given){

	string checkifmeeting2 =
"            {";

	if(given == checkifmeeting2){ return true; }
	return false;
}
//--------------- check set start ----------------

//--------------- check set end ----------------
bool checkifendmeeting2(const string& given){
	string checkifendmeeting21 =
"            },";//if its not the last in the set
	string checkifendmeeting22 =
"            }";//if its the last in the set

	if(given == checkifendmeeting21){ return false; }
	if(given == checkifendmeeting22){ return false; }
	return true;
}
//--------------- check set end ----------------
//============================ check meeting ============================

//--------------- check start ----------------
bool checkifstarttime(const string& given){

	string checkifstart = "startTime";

	if(given.size() < checkifstart.size() + 17) { return false; } //not big enough	

	for(int i = 0 ; i < checkifstart.size() ; i ++){
		if( given[i + 17] != checkifstart[i] ){ return false; }
	}
	
	return true;
}
//--------------- check start ----------------

//--------------- check end ----------------
bool checkifendtime(const string& given){
	string checkifend = "endTime";

	if(given.size() < checkifend.size() + 17) { return false; } //not big enough	

	for(int i = 0 ; i < checkifend.size() ; i ++){
		if(given[i + 17] != checkifend[i]){ return false; }
	}

	return true;
}
//--------------- check end ----------------

//--------------- check hall ----------------
bool checkifhall(const string& given){

	string checkifbuilding = "building\""; //there are two types of building lines, but the undesired one can be avoided by specifying an extra quote

	if(given.size() < checkifbuilding.size() + 17) { return false; } //not big enough	

	for(int i = 0 ; i < checkifbuilding.size() ; i ++){
		if(given[i + 17] != checkifbuilding[i]){ return false; }
	}

	return true;
}
//--------------- check hall ----------------

//--------------- check room ----------------
bool checkifroom(const string& given){

	string checkifroom = "room";

	if(given.size() < checkifroom.size() + 17) { return false; } //not big enough	

	for(int i = 0 ; i < checkifroom.size() ; i ++){
		if(given[i + 17] != checkifroom[i]){ return false; }
	}

	return true;
}
//--------------- check room ----------------

//--------------- check day of week ----------------
bool checkifday(const string& given){
	string checkifday = "daysString";

	if(given.size() < checkifday.size() + 17) { return false; } //not big enough	

	for(int i = 0 ; i < checkifday.size() ; i ++){
		if(given[i + 17] != checkifday[i]){ return false; }
	}

	return true;
}
//--------------- check day of week ----------------
//=============================================================================
//=============================== checking functions ===============================
//=============================================================================

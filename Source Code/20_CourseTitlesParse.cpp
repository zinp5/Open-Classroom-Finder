/*
parse course titles

takes raw course title html as input
parses course titles

input: raw html of course titles from console, must pipe
output: cleaned course titles into console, must pipe
*/

#include <iostream>
#include <string> //for getline
using namespace std;


/*
------------------ pseudo ---------------------
set bounds

while reading
	if enter bound
		until bounds left
			parse

------------------ pseudo ---------------------

----------------- note that -----------------
stringstream may not be made const if :::: >> ::: is to be used
----------------- note that -----------------
*/

int main(){

	//------------- base variables ---------------
	string grabtheinput;
	bool outermarked = false;
	//------------- base variables ---------------
	
	//------------ set bounds (must be EXACT) -----------
	string outerlook = 
"		<select name=\"subject\"  label=\"Subject\" tabindex=\"50\" style=\"border:1px solid #B2BED1;  margin-top:3px;\" >";
	string outerend = 
"		</select>";
	//------------ set bounds (must be EXACT) -----------


	//---------------------------- bounds check and print -----------------------------------------
	while( getline(cin,grabtheinput) ){

		//------ check outer bounds ------
		if(grabtheinput == outerlook ){ outermarked = true; continue; } //continue to skip the select name line (not needed)
		if(grabtheinput == outerend){ outermarked = false; }
		//------ check outer bounds ------

		//-------- if in outer boudns (main parsing) --------
		if( outermarked ){ //While we are inside the bounds
			//--------------  cut off undesirable bits / parse --------------------
			if(grabtheinput.size() > 33){ 
				for(int i = 20 ; i <= 22 ; i ++){ cout << grabtheinput[i]; }
				cout << '\n';
			}
			//--------------  cut off undesirable bits / parse --------------------
		}
		//-------- if in outer boudns (main parsing) --------
	}
	//---------------------------- bounds check and print -----------------------------------------

	return 0;
}
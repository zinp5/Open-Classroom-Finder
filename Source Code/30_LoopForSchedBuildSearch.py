"""
grab raw html from schedule builder, classcode by classcode

Input: CourseNamesParsed.txt in the same folder
Output: Responses/ : file for each class code
"""


"""
----------- pseudo --------------
for each line in course title file
    strip line of newline chars etc
    pass data to make requests
    turn request data into json and clean

    store cleaned json into file
----------- pseudo --------------

------------ note that ---------------
f'{ ::: is required for reading line as line(data) instead of just plain "line"
    what we are working with :::: "filters":'{"searchTerm":"mat","addFilters":""}',
    syntax ::::: paramtopass4["filters"] = f'{{"searchTerm":"{var}","addFilters":""}}'
------------ note that ---------------
"""

#-------------- imports -----------------
import requests
import json
#-------------- imports -----------------

#------------- default input --------------
url4 = "https://my.ucdavis.edu/schedulebuilder/cf/search/search.cfc"
paramtopass4 = { 
   "method":"search",
    "termCode":"202503",
    "filters":'{"searchTerm":"mat","addFilters":""}',
    "pidm":"4112908",
}
#------------- default input --------------

#================= file reading ========================
with open("CourseNamesParsed.txt", "r", encoding="utf-16") as file: #uf16 to properly format it,,, extra whitespace w/o it
    for line in file: #for each and every course code
        line = line.strip() #grab line w/o any extra chars (\n \0 \x...)

        #--------------- requests creation -----------------------
        paramtopass4["filters"] = f'{{"searchTerm":"{line}","addFilters":""}}' #edit param to pass using current course code

        rrr = requests.post(url4, data=paramtopass4 ) #make object
        print(rrr.status_code) #print err code
        #--------------- requests creation -----------------------

        #------------------ json cleanup ------------------------
        parsed_json = json.loads(rrr.text) 

        cleanedupjson = json.dumps(parsed_json, indent=4)
        #------------------ json cleanup ------------------------

        #------------------ file output ---------------------
        with open(f"responses/{line}.txt", "w", encoding="utf-8") as outfile: #set folder to output
            outfile.write(cleanedupjson) #print json output to respective file
        #------------------ file output ---------------------
#================= file reading ========================

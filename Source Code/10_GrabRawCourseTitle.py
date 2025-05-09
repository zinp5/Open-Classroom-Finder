"""
grab raw html from registrar

input: none
output: console output, must pipe
"""

#======================================= main  =======================================

#--------------- requests -------------
import requests

url2 = "https://registrar-apps.ucdavis.edu/courses/search/index.cfm"
rrr = requests.post(url2 ) #make object
print(rrr.status_code) #print err code
print(rrr.text) #print raw html
#--------------- requests -------------


#======================================= main  =======================================

print("^-^-^-^-^-^-^-^-^-^")
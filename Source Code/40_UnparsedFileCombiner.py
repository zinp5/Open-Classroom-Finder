#to 
"""
combine all the unparsed responses into one singular file

input: filepath to responses
output: unparsedCombined.txt
"""
import os #for interaction with path(s), file(s) and directorie(s)
import subprocess #for calling the cpp exe


#---------------- paths --------------------
input_folder = r"C:\Users\hdjrj\Desktop\vstudio code\python files\OpenClassFinder\newerResponses"
output_file = "UnparsedCombined.txt"
#---------------- paths --------------------

#------------------ folder directory loop --------------------
with open(output_file, "w", encoding="utf-8") as outfile:
    for filename in os.listdir(input_folder):
        if filename.endswith(".txt"):
            filepath = os.path.join(input_folder, filename)
            with open(filepath, "r", encoding="utf-8") as infile:
                outfile.write(infile.read())
                outfile.write("\n")  # Add newline to separate files
#------------------ folder directory loop --------------------
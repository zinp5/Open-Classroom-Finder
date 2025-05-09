"""
display user desired times in a visual manner

Input: csvFormatFull.txt
Output: nothing
"""


"""
--------------- Pseudo --------------- 
read from full csv
    create list of possible halls using csv data
loop
    prompt user for day and hall
    parse CSV looking for day and hall 
    print data, restart loop
--------------- Pseudo --------------- 
"""


#---------- import -----------------
import matplotlib.pyplot as plt #to display timieline
import csv #to easily read the csv.txt
#---------- import -----------------


#---------------- create the hall selection list -----------------------
hall_map = {} #to test if we've seen the hall before
hall_list = [] #empty array for hall names
with open("csvFormatFull.txt", "r", encoding="utf-16") as f:
    reader = csv.reader(f)
    for row in reader: #for each row in file
        hall = row[1] #get hallname
        if hall not in hall_map: #if we've never seen hall name
            hall_number = len(hall_map) + 1 #hall number for name increment
            hall_map[hall] = hall_number #add hall to map so we know weve seen it
            hall_list.append(hall) #add hall to array for access later

hall_list.sort() #quick sort to clean up the future prompt
#---------------- create the hall selection list -----------------------

#=============================================== main loop ===============================================
while(True):

    #----------------------------------- prompt and grab inputs ---------------------------------------------
    #------------------ get desired day -----------------------
    daylistarray = ["U", "M", "T", "W", "R", "F", "S"]
    print("Days to choose from")
    for thespec in range( len(daylistarray) ):
        print(thespec , ": ", daylistarray[thespec] )
    choice = int(input("Which day would you like? (enter # not in range to quit): "))
    if choice < 0 or choice > 6:
        print("Not a proper input... quitting...")
        break
    desiredday = daylistarray[choice]
    
    #------------------ get desired day -----------------------

    #------------------ get desired hall -----------------------
    print("Available halls:")
    cleanprintcount = 0
    for num in range( len(hall_list) ):
        print(f"{num:>2}: {hall_list[num]:<30}", end="") #special formatted print
        cleanprintcount +=1
        if cleanprintcount % 4 == 0: #tabled print
            print() #empty newline
    choice = int(input("Enter the number of the hall (enter # not in range to quit): "))
    if choice < 0 or choice > len(hall_list)-1:
        print("Not a proper input... quitting...")
        break
    desiredhall = hall_list[choice]
    #------------------ get desired hall -----------------------
    #----------------------------------- prompt and grab inputs ---------------------------------------------


    #---------------- plot configs ------------------
    plt.figure(figsize=(10, 5)) #has to be above all other plt calls
    #---------------- plot configs ------------------

    #-------------------- build data and prepare to display -------------------------------
    with open("csvFormatFull.txt", "r", encoding="utf-16") as f:
        reader = csv.reader(f)
        for row in reader:
            day, hall, start, end, room = row
            if day == desiredday and hall == desiredhall: #if hall meets criteria
                start = int(start) #prep for bar in graph
                end = int(end) #prep for bar in graph
                plt.barh(y=room, width=end - start, left=start, height=0.45) #build the plots
    #-------------------- build data and prepare to display -------------------------------



    #----------------- display data ---------------------
    plt.xlabel("Day of week: " + desiredday)
    plt.xticks(ticks=range(400, 2400, 100))
    plt.ylabel("Room number")
    plt.title("Room Occupancy for: " + desiredhall)
    plt.grid(True)
    plt.tight_layout()
    plt.show()
    #----------------- display data ---------------------

    print("\n\n-----------------Next Set!--------------\n\n") 
#=============================================== main loop ===============================================
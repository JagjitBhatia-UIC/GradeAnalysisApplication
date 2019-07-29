# Grade Analysis Application
 A command-line application for looking up grade-related information for a department or course such as DFW Rates and grade distributions; Implemented using C++
 
 **User Guide:**  
 To run the program, open terminal, type 'make all' and hit enter.  
 To begin, enter the name of the .csv file that contains information regarding a school's grade distribution (must be in the     same directory and follow the same format as the 'fall-2018.csv' file. Once the file name is entered, you will receive a  prompt to enter a command.  
 
 There are currently 5 supported commands:      
    1.) *summary* - The summary command outputs a college-wide summary or a departmental summary. The user is prompted for a department name, e.g. "CS", or "all" which means the college. The input is case-sensitive.  
   2.) *search* - The search command performs a departmental or college-wide search by course number or instructor prefix. The user is first prompted for a department name, e.g. "CS", or "all" which means the college. The user is then prompted to enter a course number or instructor prefix. All input is case-sensitive.  
   3.) *unknown* - The unkown command performs a departmental or college-wide search for all courses whose Grading type is unknown. The user is prompted for a department name, e.g. "CS", or "all" which means the college.  
   4.) *dfw* - The dfw command performs a departmental or college-wide search for all courses whose DFW rate exceeds the threshold set by the user. The user is prompted for a dfw threshold, which must be a number from 0.0 to 99.9 and must follow the format: (one or two digit number).(one digit number)    
   5.) *letterA* - The letterA command performs a departmental or college-wide search for all courses whose percentage of letter A grades exceeds a threshhold set by the user. The user is prompted for a letterA threshold, which must be a number from 0.0 to 99.9 and must follow the format: (one or two digit number).(one digit number) 
 
 

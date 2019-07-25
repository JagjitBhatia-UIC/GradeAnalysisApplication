/*main.cpp*/

#include "gradeutil.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

void addCourse(College &C, const Course &c)
{
    auto dept = find_if(C.Depts.begin(), C.Depts.end(),
                        [=](const Dept& d)
                        {
                            return (d.Name == c.Dept);
                        });

    if(dept == C.Depts.end())
    {
        Dept new_dept = Dept(c.Dept);
        new_dept.Courses.push_back(c);
        C.Depts.push_back(new_dept);
        return;
    }

    dept->Courses.push_back(c);


}


void printSummary(Dept &d)
{
    cout << d.Name << ":" << endl;
    
    cout << " # of courses taught: " << d.Courses.size() << endl;
    int numStudents = 0;
    for(Course c : d.Courses)
    {
        numStudents += c.getNumStudents();
    }
    cout << " # of students taught: " << numStudents << endl;
    
    //Grade distribution printing
    GradeStats cgs = GetGradeDistribution(d);
    cout << " grade distribution (A-F): " << cgs.PercentA << "%, " << cgs.PercentB << "%, " << cgs.PercentC << "%, " << cgs.PercentD << "%, " << cgs.PercentF << "%" << endl;
    int a, b;
    cout << " DFW rate: " << GetDFWRate(d, a, b) << "%" << endl;
    
    
    
    cout << endl;
}

void printSummary(Course &c)
{
    cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
    cout << " # students: " << c.getNumStudents() << endl;
    auto type = c.getGradingType();
    string type_s;
    if(type == Course::Letter) type_s = "letter";
    else if(type == Course::Satisfactory) type_s = "satisfactory";
    else type_s = "unknown";
    cout << " course type: " << type_s << endl;
    //Grade distribution printing
    GradeStats cgs = GetGradeDistribution(c);
    cout << " grade distribution (A-F): " << cgs.PercentA << "%, " << cgs.PercentB << "%, " << cgs.PercentC << "%, " << cgs.PercentD << "%, " << cgs.PercentF << "%" << endl;
    int a, b;
    cout << " DFW rate: " << GetDFWRate(c, a, b) << "%" << endl;
}

bool findDept(College &c, string name, vector<Dept>::iterator &it)
{
    it = find_if(c.Depts.begin(), c.Depts.end(),
                        [=](const Dept& d)
                        {
                            return (d.Name == name);
                        });
                if(it == c.Depts.end())
                {
                    cout << "**dept not found" << endl;
                    return false;
                }

    return true;
}

void summary(College &c)
{
     string cmd;
     cout << "dept name, or all? " << endl;

     cin >> cmd;

     if(cmd == "all")
      {
        
        sort(c.Depts.begin(), c.Depts.end(), [](const Dept& d1, const Dept& d2)
             {
                 return (d1.Name < d2.Name);
             });
          
        for(Dept d : c.Depts)
            {
                 printSummary(d);
            }
        }

        else
        {
           vector<Dept>::iterator d;
           bool found = findDept(c, cmd, d);
           if(found) printSummary(*d);
            
         }


    cmd = ""; //reset input
}


College ParseInput(ifstream &f, string &sem, int &numCourses, int &numStudents)
{
    numCourses = 0;
    numStudents = 0;
    string line;
    getline(f, line, ',');
    College C = College(line);
    getline(f, line, ',');
    sem = line + " ";
    getline(f, line, '\n');
    sem += line;

    getline(f, line);

    while(getline(f, line))
    {
        Course c = ParseCourse(line);
        addCourse(C, c);
        numCourses++;
        numStudents += c.getNumStudents();
    }

    return C;




}

void search(College &c)
{
    string cmd;
    vector<Course> results;
    int courseNumber;
    cout << "dept name, or all? " << endl;
    
    cin >> cmd;
    
    if(cmd == "all")
    {
        cout << "course # or instructor prefix? ";
        cin >> cmd;
        if(isdigit(cmd[0]))
        {
            courseNumber = stoi(cmd);
            results = FindCourses(c, courseNumber);
        }
        
        else
        {
            results = FindCourses(c, cmd);
        }
        
    }
    
    else
    {
        vector<Dept>::iterator d;
        bool found = findDept(c, cmd, d);
      
        
        if(found) {
            cout << "course # or instructor prefix? ";
            cin >> cmd;
            if(isdigit(cmd[0]))
            {
                courseNumber = stoi(cmd);
                results = FindCourses(*d, courseNumber);
            }
            
            else
            {
                results = FindCourses(*d, cmd);
            }
            
        }
        
    }
    
    for(Course c : results)
    {
        printSummary(c);
    }
    
    cmd = ""; //reset input
}



int main() {
    cout << std::fixed;
    cout <<std::setprecision(2);
    ifstream f;

    string fname;
    cin >> fname;
    f.open(fname);

    if(f.is_open())
    {
        string sem = "";
        int numCourses, numStudents;
        College c = ParseInput(f, sem, numCourses, numStudents);
        cout << "** College of " <<c.Name << ", " << sem << " **" << endl;
        cout << "# of courses taught: " << numCourses << endl;
        cout << "# of students taught: " << numStudents << endl;

        //Grade distribution printing
        GradeStats cgs = GetGradeDistribution(c);
        cout << "grade distribution (A-F): " << cgs.PercentA << "%, " << cgs.PercentB << "%, " << cgs.PercentC << "%, " << cgs.PercentD << "%, " << cgs.PercentF << "%" << endl;
        int a, b;
        cout << "DFW rate: " << GetDFWRate(c, a, b) << "%" << endl;

        cout << endl;

        cout << "Enter a command> ";

        string cmd;
        cin >> cmd;
        
        

        while(cmd != "#")
        {
            if(cmd == "summary")
            {
               summary(c);
            }

            
            else if(cmd == "search")
            {
                search(c);
            }
            
            
            else if(cmd == "unknown")
            {
                //unknown(c);
            }
            
            else if(cmd == "dfw")
            {
                //dfw(c);
            }
            
            else if(cmd == "letterA")
            {
                //letterA(c);
            }
            
            else cout << "**unknown command" << endl;
            
            
            
            
            


            cout << "Enter a command> ";
            cin >> cmd;
        }


    }















}

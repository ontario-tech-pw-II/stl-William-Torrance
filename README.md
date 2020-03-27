## STL Containers and Iterators

Learning outcomes highlights: 
- How to use a <code>list</code> of objects (e.g., <code>Student</code>)
- How to use <code> set </code>
- How to use <code> map </code>
### Task1: 
Write a program that reads the names and grades of students then adds students objects in a <code>list</code> of <code>Student</code>, so that the <code>list</code> is always sorted in ascending order of grades (you need to find the appropriate position for any insertion).
The program prints the <code>list</code> (both name and grade) in ascending, and then in descending order (based on grade). 

Note: The <code>Student</code> class is implemented for you.

**Hint:** You can define a <code>list</code> container like:
```C++
list<Student> c;
``` 
## Task2:
Write a program that reads the names and and grades of students form an input file and print the name of students that have at least one mark less that 50 for a report. The printed list should not have any duplicate.

Hint: You can define a <code>set</code> container like:
```C++
set<string> c;
``` 
Sample input file:
```C++
John 25
Amanda 35
John 45
Sarah  80
Jessica 65
Sarah 30
John 70
```
Sample output file (the order is not important):
```C++
John 
Amanda 
Sarah  
```

### Task3: 
Write a program that reads the names and grades of students from an input file, then prints the student's names and the number of time that one student has a mark less than 50.

Hint: You can define a list container like:
```C++
map<string, int> c;
```
Sample output file (the order is not important):
```C++
John 2
Amanda 1
Sarah  1
Jessica 0
```
  


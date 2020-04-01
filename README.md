# Advanced-C
This repository consists of advanced C programming concepts and gives a good fundamental approach to Procedural Programming.

Each folder is a standalone project. You will find a Makefile in each folder.

Platform used to write the C code is gcc (Ubuntu 6.2.0-5ubuntu12) 6.2.0 20161005

#Compilation and Running the Programs
1) Check if gcc is installed on your system
   $gcc --version
2) Compile the C source code
   $gcc <filename>.c -o <filename>.out
3) Run the class file created
   $./<filename>.out

# About Directory 
# DataParser
## Overview
* This project is an example to parse large data from text file and export it to comma seperated file.
* Porject also uses dirent.h POSIX library to recursive do directory walk and find required text file for data parsing.
* Care is taken to handle heap memory appriopriate to avoid memory leak

## Steps to Run

* Inside Dataparser folder run as follows -
    <blockquote>
        <p>$ make</p>
        <p>$ make run</p>
     </blockquote>
  This will create info.csv and data.csv
* To clean the directory
        <blockquote>
        <p>$ make clean</p>
     </blockquote>

# LinkList (Under development)
## Overview

# misc (Under development)



# CS440_Assignment_3

The following command will compile the code:

g++ -std=c++11 main.cpp block.cpp record.cpp bucket.cpp -o main.out

To create the EmployeeIndex file:
main.out -C

Once the EmployeeIndex file is created, to lookup a record:
main.out -L <ID Number>

The assignment stated that the csv file should be named "Employee.csv" so that is what my code reads in, even though that is different from the example file.  If the csv file to be used it not named "Employee.csv", please rename it to that.

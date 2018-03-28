//Author:		Yao Yao, yjy5094, 17.39 Nov. 21
//Class:		CMPSC 121
//Project:		03

/*******************************************************************\
*Academic Integrity Affidavit:                                      *
*                                                                   *
*I certify that, this program code is my work. Others may have      *
*assisted me with planning and concepts, but the code was written,  *
*solely, by me.                                                     *
*                                                                   *
*I understand that submitting code which is totally or partially    *
*the product of other individuals is a violation of the Academic    *
*Integrity Policy and accepted ethical precepts. Falsified          *
*execution results are also results of improper activities. Such    *
*violations may result in ero credit for the assignment, reduced    *
*credit for the assignment, or course failure.                      *
\*******************************************************************/
//Sources of logic assistance:121 Study Group: Yao Yao

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Employee {
	string lastName, firstName;
	int num;
	string department;
	double salary;
};

void findByName(const vector <Employee> &V);

void getEmployee(vector <Employee> &V);

void employeesPerDept(const vector <Employee> &V);

void employeeList(const vector <Employee> &V);

void salaryByDept(const vector <Employee> &V);

bool readFile(vector <Employee> &V);

int binSearch(const vector<Employee> &V, string fName, string lName);

void ShellSort(vector<Employee> &V);

void putData(const vector<Employee> &V);

void insertData(vector <Employee>& V, Employee toAdd);

template<class CType>
void swapper(CType& a, CType& b);

int displayMenu();

int main() {
	vector <Employee> employee;
	int menu;

	if (!readFile(employee))
		cout << "No File Found!" << endl;
	else {
		ShellSort(employee);
		do {
			menu = displayMenu();
			switch (menu) {
			case 1: findByName(employee); break;
			case 2: employeesPerDept(employee); break;
			case 3: getEmployee(employee); break;
			case 4: employeeList(employee); break;
			case 5: salaryByDept(employee); break;
			}
		} while (menu != 6);
		putData(employee);
	}
	return 0;
}

//Reads the payroll file and fills the vector of structs
//Called by main
bool readFile(vector <Employee> &V) {
	ifstream fin;
	Employee input;
	bool canRead = true;
	fin.open("Payroll.txt");
	if (fin.fail())
		canRead = false;
	else
		while (fin >> input.lastName >> input.firstName
			>> input.num >> input.department >> input.salary)
			V.push_back(input);
	fin.close();
	return canRead;
}

//Writes sorted file at end. Called by main
void putData(const vector<Employee> &V) {
	ofstream fout;
	fout.open("Output.txt");
	cout << fixed << setprecision(2);
	for (int i = 0; i < V.size(); i++) {
		fout << V[i].firstName << "\t\t" << V[i].lastName << "\t\t"
			<< V[i].num << "\t" << V[i].department << "\t\t$"
			<< V[i].salary << endl;
	}
	fout.close();
}

// Called by main Displays menu
int displayMenu() {
	int choice;
	cout << "--------------------------------------------------" << endl
		<< "Choose Desired Function :" << endl
		<< "1. Find Employee by Name" << endl
		<< "2. Enter Department and display its employees" << endl
		<< "3. Add Employee" << endl
		<< "4. Get list of Employees" << endl
		<< "5. Display total of salaries for a department" << endl
		<< "6. End Program" << endl
		<< "--------------------------------------------------" << endl;
	cin >> choice;
	while (choice < 1 || choice > 6) {
		cout << "Wrong Requirement, Please Reenter" << endl;
		cin >> choice;
	}
	system("cls");
	return choice;
}

// Sorts vector called by main
void ShellSort(vector<Employee> &V) {
	bool flag = true;
	int i, numLength = V.size();
	int d = numLength;

	while (flag || (d > 1)) {   // bool flag 
		flag = false;  //reset flag to 0 to check for
					   // future swaps
		d = (d + 1) / 2;
		for (i = 0; i < (numLength - d); i++) {
			if (V[i + d].lastName < V[i].lastName || (V[i + d].lastName == V[i].lastName && V[i + d].firstName < V[i].firstName)) {
				swapper(V[i], V[i + d]);
				flag = true;     //tells swap has occurred
			}
		}
	}
}

//templated swap function
template<class CType>
void swapper(CType& a, CType& b) {
	CType temp;
	temp = a;
	a = b;
	b = temp;
}

// Locates an employee by last name 
//Called by main
void findByName(const vector <Employee> &V) {
	string fName, lName;
	int location;
	cout << "Enter the first and last name of the employee you want to search: ";
	cin >> fName >> lName;
	location = binSearch(V, fName, lName);
	cout << fixed << setprecision(2);
	if (location == -1)
		cout << "No result found!" << endl;
	else
		cout << V[location].firstName << " " << V[location].lastName << " "
			<< V[location].num << " " << V[location].department << " $"
			<< V[location].salary << endl;
}

//Called by findByName to return the index of lName
int binSearch(const vector<Employee> &V, string fName, string lName) {
	int lo = 0,
		hi = V.size() - 1,
		mid, loc;
	bool find = false;
	do {
		mid = (lo + hi) / 2;
		if (V[mid].lastName == lName && V[mid].firstName == fName)
			find = true;
		else if (V[mid].lastName < lName || (V[mid].lastName == lName && V[mid].firstName < fName))
			lo = mid + 1;
		else
			hi = mid - 1;
	} while (!find && lo <= hi);
	if (find)
		loc = mid;
	else
		loc = -1;
	return loc;
}

//Lists employee names in a given department
// Called by main
void employeesPerDept(const vector <Employee> &V) {
	string dept;
	cout << "Enter the department you want to list: ";
	cin >> dept;
	cout << fixed << setprecision(2);
	for (int i = 0; i < V.size(); i++)
		if (V[i].department == dept)
			cout << V[i].firstName << "\t\t" << V[i].lastName << "\t\t"
			<< V[i].num << "\t" << V[i].department << "\t\t$"
			<< V[i].salary << endl;
}

// Asks for employee info and calls insertData to add employee to vector
// Called by main
void getEmployee(vector <Employee> &V) {
	Employee addEm;
	cout << "Enter the new employee infomation: fist name, last name, number, department, salary" << endl;
	cin >> addEm.firstName >> addEm.lastName >> addEm.num
		>> addEm.department >> addEm.salary;
	insertData(V, addEm);
}

void insertData(vector <Employee>& V, Employee toAdd) {
	bool findLoc = false;
	int lo = 0,
		hi = V.size() - 1,
		mid;
	do {
		mid = (lo + hi) / 2;
		if (V[mid].lastName < toAdd.lastName || (V[mid].lastName == toAdd.lastName && V[mid].firstName < toAdd.firstName))
			if (V[mid+1].lastName > toAdd.lastName || (V[mid+1].lastName == toAdd.lastName && V[mid+1].firstName > toAdd.firstName))
				findLoc = true;
			else
				lo = mid + 1;
		else
			hi = mid;
	} while (!findLoc && lo <= hi);
	V.push_back(V[V.size() - 1]);
	for (int i = V.size() - 1; i > mid + 1; i--)
		V[i] = V[i - 1];
	V[mid + 1] = toAdd;
}

//Lists all employees Called by main
void employeeList(const vector <Employee> &V) {
	cout << fixed << setprecision(2);
	for (int i = 0; i < V.size(); i++) {
		cout << V[i].firstName << "\t\t" << V[i].lastName << "\t\t"
			<< V[i].num << "\t" << V[i].department << "\t\t$"
			<< V[i].salary << endl;
		if (i % 24 == 23)
			system("pause");
	}
}

//Displays the total of salaries for a given department
//Called by main
void salaryByDept(const vector <Employee> &V) {
	string dept;
	double total = 0;
	cout << "Enter the department you want to calculate: ";
	cin >> dept;
	for (int i = 0; i < V.size(); i++)
		if (V[i].department == dept)
			total += V[i].salary;
	cout << fixed << setprecision(2);
	cout << "The total salaries for the department "
		<< dept << " is $" << total << endl;
}
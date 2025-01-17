// Mercedes Figueiredo
// 23/05/2022
// file catalogue_main.cpp
// This file contains the main program for the star catalogue. It must include the header file "star_catalogue.h".

#include<iostream>
#include "star_catalogue.h"

// ~~~~~~~~ main ~~~~~~~~
int main()
{
	std::cout << "~~~~~~~~ Star Catalogue ~~~~~~~~" << std::endl;
	std::cout << "Compiled on " << __DATE__ << " at " << __TIME__ << std::endl;
	std::cout << "\nThis program takes in and stores data from observed astronomical objects. ";
	std::cout << "It can output a star chart, a graph of magnitude against distance and the main sequence." << std::endl;
	std::cout << "It is possible to search the database.\n" << std::endl;

	// Ask what to do
	bool valid{ 1 };
	std::string search_or_out;
	while (valid) {
		std::cout << "Would you like to search the database (d) or output graphs and report (o)? ";
		std::cin >> search_or_out;
		valid = check(search_or_out, 3);
	}
	
	// Create vector of observed objects
	std::vector<std::unique_ptr<object>> objects;
	
	if (search_or_out == "o") {

		// Input data into vector
		input(objects);

		// Print information for each object
		std::string yes_no;
		valid = 1;
		while (valid) {
			std::cout << "Do you want to print out the data for each object? (Y/N) ";
			std::cin >> yes_no;
			valid = check(yes_no, 1);
		}
		if (yes_no == "Y") {
			for (int i = 0; i < objects.size(); i++) {
				objects[i]->info();
			}
		}

		// Plot a star chart
		plot_chart(objects);

		// Plot magnitude vs distance graph
		plot_mag_dist_graph(objects);

		// Plot the main sequence
		main_sequence(objects);

		// Create final report
		report(objects);
	}
	if (search_or_out == "d") {
		// Input data from database into vector
		file_in(objects, "database.txt");

		// Search the database
		search_database(objects);
	}

	// Delete data
	std::cout << "Deleting data." << std::endl;
	objects.clear();

	return 0;
}

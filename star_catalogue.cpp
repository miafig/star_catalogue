// Mercedes Figueiredo
// 23/05/2022
// file star_catalogue.cpp
// This file contains the function definitions for the star catalogue. It must include the header file "star_catalogue.h".

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "star_catalogue.h"

// ~~~~~~~~ function definitions ~~~~~~~~
// Print object information
void galaxy::info() {
	std::cout.precision(4);
	std::cout << name << " galaxy:\n" << std::endl;
	std::cout << "  Apparent Magnitude =      " << magnitude << std::endl;
	std::cout << "  Distance =		    " << distance << " pc" << std::endl;
	std::cout << "  Radius =		    " << radius << " ly" << std::endl;
	std::cout.precision(8);
	std::cout << "  Right Ascension =	    " << right_ascension << std::endl;
	std::cout << "  Declination =		    " << declination << "\n" << std::endl;
}
void star::info() {
	std::cout.precision(4);
	std::cout << name << " star:\n" << std::endl;
	std::cout << "  Apparent Magnitude =	    " << magnitude << std::endl;
	std::cout << "  Distance =		    " << distance << " pc" << std::endl;
	std::cout << "  Radius =		    " << radius << " R_sun" << std::endl;
	std::cout.precision(8);
	std::cout << "  Right Ascension =	    " << right_ascension << std::endl;
	std::cout << "  Declination =		    " << declination << "\n" << std::endl;
}
void planet::info() {
	std::cout.precision(4);
	std::cout << name << " planet:\n" << std::endl;
	std::cout << "  Host Star Apparent Magnitude =	    " << magnitude << std::endl;
	std::cout << "  Distance =			    	  " << distance << " pc" << std::endl;
	std::cout << "  Radius of orbit =			    " << radius << " AU" << std::endl;
	std::cout.precision(8);
	std::cout << "  Right Ascension =			    " << right_ascension << std::endl;
	std::cout << "  Declination =				    " << declination << "\n" << std::endl;
}
void nebula::info() {
	std::cout.precision(4);
	std::cout << name << " nebula:\n" << std::endl;
	std::cout << "  Apparent Magnitude =	    " << magnitude << std::endl;
	std::cout << "  Distance =		    " << distance << " pc" << std::endl;
	std::cout << "  Radius =		    " << radius << " ly" << std::endl;
	std::cout.precision(8);
	std::cout << "  Right Ascension =	    " << right_ascension << std::endl;
	std::cout << "  Declination =		    " << declination << "\n" << std::endl;
}

// Ask for object input type
void input(std::vector<std::unique_ptr<object>>& objects) {
	std::string file_or_console;
	while (1) {
		std::cout << "Would you like to input the celestial object data as a file (f), console input (c), or use the default file given (d)? ";
		std::cin >> file_or_console;
		if (file_or_console == "f") {
			std::cin.ignore();
			std::string file_name;
			std::cout << "\nPlease format the file as [type, name, apparent magnitude, declination, right ascension, distance, radius]." << std::endl;
			std::cout << "Enter the filename : ";
			std::getline(std::cin, file_name);
			try {
				file_in(objects, file_name);
			}
			catch (int error_flag) {
				if (error_flag == constants::no_data) {
					std::cerr << "Error: No data in file." << std::endl;
					exit(error_flag);
				}
				if (error_flag == constants::no_file) {
					std::cerr << "Error: File not found." << std::endl;
					exit(error_flag);
				}
			}
			break;
		}
		if (file_or_console == "c") {
			console_in(objects);
			break;
		}
		if (file_or_console == "d") {
			try {
				file_in(objects, "database.txt");
			}
			catch (int error_flag) {
				if (error_flag == constants::read_file) {
					std::cerr << "Error: Could not open file." << std::endl;
					exit(error_flag);
				}
			}
			break;
		}
		else {
			std::cout << "Invalid input. Insert 'f', 'c' or 'd'.\n";
		}
	}
}

// Input data from file
void file_in(std::vector<std::unique_ptr<object>>& objects, std::string file_name) {

	std::ifstream myfile;
	myfile.open(file_name);
	// throw error if can't open file
	if (!myfile.is_open()) throw constants::no_file;

	if (myfile.is_open()) {
		std::cout << "\nFile '" << file_name << "' successfully opened.\n" << std::endl;
	}

	if (!myfile.good()) throw constants::read_file;

	std::string dataline;

	while (std::getline(myfile, dataline)) {

		std::stringstream linestream(dataline);
		std::string type, name, magnitude, declination, right_ascension, distance, radius;
		// Read data in a line
		std::getline(linestream, type, ',');
		std::getline(linestream, name, ',');
		std::getline(linestream, magnitude, ',');
		std::getline(linestream, declination, ',');
		std::getline(linestream, right_ascension, ',');
		std::getline(linestream, distance, ',');
		std::getline(linestream, radius, ',');

		// Create new objects according to type with data in line and append to vector
		if (type == "galaxy") {
			objects.push_back(std::make_unique<galaxy>(name, std::stod(magnitude), std::stod(declination),
				std::stod(right_ascension), std::stod(distance), std::stod(radius)));
		}
		if (type == "star") {
			objects.push_back(std::make_unique<star>(name, std::stod(magnitude), std::stod(declination),
				std::stod(right_ascension), std::stod(distance), std::stod(radius)));
		}
		if (type == "planet") {
			objects.push_back(std::make_unique<planet>(name, std::stod(magnitude), std::stod(declination),
				std::stod(right_ascension), std::stod(distance), std::stod(radius)));
		}
		if (type == "nebula") {
			objects.push_back(std::make_unique<nebula>(name, std::stod(magnitude), std::stod(declination),
				std::stod(right_ascension), std::stod(distance), std::stod(radius)));
		}
	}
	myfile.close();
	std::cout << "File closed.\n" << std::endl;
	// Throw error if file is empty
	if (objects.size() == 0) throw constants::no_data;
}

// Input data from console
void console_in(std::vector<std::unique_ptr<object>>& objects) {
	std::string type{};
	double magnitude{0}, declination{0}, right_ascension{0}, distance{0}, radius{0};

	bool new_obj{ true };
	while (new_obj) {
		// Ask for input of data for an object
		// Type
		while (1) {
			std::cout << "\nIs the object a galaxy, star, planet or nebula? ";
			std::cin >> type;
			if (type == "galaxy" || type == "star" || type == "planet" || type == "nebula") {
				break;
			}
			else {
				std::cout << "Invalid input. ";
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
		}
		// Magnitude
		while (1) {
			std::cout << "Input the magnitude. ";
			std::cin >> magnitude;
			if (std::cin.good()) {
				break;
			}
			else {
				std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
		}
		// Declination
		while (1) {
			std::cout << "Input the declination in format ddmmss (degree, arminute, arcsecond). ";
			std::cin >> declination;
			if (!std::cin.good()) {
				std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
			if (declination < -900000 || declination > 900000) {
				std::cout << "Invalid Input. Must be between -90 and 90 degrees. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
			else {
				break;
			}
		}
		// Right ascension
		while (1) {
			std::cout << "Input the right ascension in format hhmmss (hour, minute, second). ";
			std::cin >> right_ascension;
			if (!std::cin.good()) {
				std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
			if (right_ascension < 0 || right_ascension > 240000) {
				std::cout << "Invalid Input. Must be between 0 and 24 hours. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
			else {
				break;
			}
		}
		// Distance
		while (1) {
			std::cout << "Input the distance from earth in pc. ";
			std::cin >> distance;
			if (!std::cin.good()) {
				std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
				std::cin.clear();
				std::cin.ignore(100000, '\n');
			}
			else {
				break;
			}
		}
		
		// Append a new object to the appropriate vector
		if (type == "galaxy") {
			// Radius
			while (1) {
				std::cout << "Input the radius of the galaxy in ly. ";
				std::cin >> radius;
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			// Name
			std::string name;
			while (1) {
				std::cout << "Input the name of the galaxy. ";
				std::getline(std::cin, name);
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a string. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			objects.push_back(std::make_unique<galaxy>(name, magnitude, declination, right_ascension, distance, radius));
		}
		if (type == "star") {
			// Radius
			while (1) {
				std::cout << "Input the radius of the star in units of solar radius. ";
				std::cin >> radius;
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			// Name
			std::string name;
			while (1) {
				std::cout << "Input the name of the star. ";
				std::getline(std::cin, name);
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a string. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			objects.push_back(std::make_unique<star>(name, magnitude, declination, right_ascension, distance, radius));
		}
		if (type == "planet") {
			// Radius
			while (1) {
				std::cout << "Input the radius of the planet's orbit in units of AU. ";
				std::cin >> radius;
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			// Name
			std::string name;
			while (1) {
				std::cout << "Input the name of the planet. ";
				std::getline(std::cin, name);
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a string. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			objects.push_back(std::make_unique<planet>(name, magnitude, declination, right_ascension, distance, radius));
		}
		if (type == "nebula") {
			// Radius
			while (1) {
				std::cout << "Input the radius of the nebula in ly. ";
				std::cin >> radius;
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			// Name
			std::string name;
			while (1) {
				std::cout << "Input the name of the nebula. ";
				std::getline(std::cin, name);
				if (!std::cin.good()) {
					std::cout << "Invalid Input. Please input a string. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
				else {
					break;
				}
			}
			objects.push_back(std::make_unique<nebula>(name, magnitude, declination, right_ascension, distance, radius));
		}

		std::string yes_no;
		bool valid{ 1 };
		while (valid) {
			std::cin.ignore();
			std::cout << "Do you have another object? (Y/N) ";
			std::cin >> yes_no;
			valid = check(yes_no, 1);
		}
		if (yes_no == "N") {
			new_obj = false;
		}
	}
}

// Edit plot
void plot_what(std::string & show_planets, std::string& show_galaxies, std::string& show_nebulae, std::string& save_format,
	bool ask_planet, bool ask_format) {
	bool valid{ 1 };
	while (valid) {
		std::cout << "Do you want to show the galaxies on the plot? (Y/N) ";
		std::cin >> show_galaxies;
		valid = check(show_galaxies, 1);
	}
	valid = 1;
	if(ask_planet == 1) {
		while (valid) {
			std::cout << "Do you want to show the planets? (Y/N) ";
			std::cin >> show_planets;
			valid = check(show_planets, 1);
		}
	}
	valid = 1;
	while (valid) {
		std::cout << "Do you want to show the nebulae? (Y/N) ";
		std::cin >> show_nebulae;
		valid = check(show_nebulae, 1);
	}
	valid = 1;
	if (ask_format == 1) {
		while (valid) {
			std::cout << "Do you want to save as an image (i) or a txt file (f)? ";
			std::cin >> save_format;
			valid = check(save_format, 2);
		}
	}	
}
void def_limits(double& decl_min, double& decl_max, double& ra_min, double& ra_max) {
	while (1) {
		std::cout << "To define the range of the plot desired, insert the minimum declination: ";
		std::cin >> decl_min;
		if (std::cin.good()) {
			break;
		}
		else {
			std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
			std::cin.clear();
			std::cin.ignore(100000, '\n');
		}
	}
	while (1) {
		std::cout << "Maximum declination: ";
		std::cin >> decl_max;
		if (std::cin.good()) {
			break;
		}
		else {
			std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
			std::cin.clear();
			std::cin.ignore(100000, '\n');
		}
	}
	while (1) {
		std::cout << "Minimum right ascension: ";
		std::cin >> ra_min;
		if (std::cin.good()) {
			break;
		}
		else {
			std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
			std::cin.clear();
			std::cin.ignore(100000, '\n');
		}
	}
	while (1) {
		std::cout << "Maximum right ascension: ";
		std::cin >> ra_max;
		if (std::cin.good()) {
			break;
		}
		else {
			std::cout << "Invalid Input. Please input a numerical value. " << std::endl;
			std::cin.clear();
			std::cin.ignore(100000, '\n');
		}
	}
	// Throw error if limits are not valid
	if (decl_min > decl_max) throw constants::y_limit_flag;
	if (ra_min > ra_max) throw constants::x_limit_flag;
}
void convert_units(std::vector<double>&right_asc, std::vector<double>&declination){
	// Convert right ascension [hhmmss] to hours
	for_each(right_asc.begin(), right_asc.end(),[](double& c) {
		c /= 100;
		double sec, min, hour, hour_min;
		sec = std::modf(c, &hour_min);
		hour_min /= 100;
		min = std::modf(hour_min, &hour);
		c = hour + (min / 60) + (sec / 3600);});

	// Convert declination [ddmmss] to degrees
	for_each(declination.begin(), declination.end(), [](double& c) {
		c /= 100;
		double asec, amin, deg, deg_amin;
		asec = std::modf(c, &deg_amin);
		deg_amin /= 100;
		amin = std::modf(deg_amin, &deg);
		if (deg < 0) {
			c = deg - (amin / 60) - (asec / 3600);
		}
		else {
			c = deg + (amin / 60) + (asec / 3600);
		}});
}
void convert_units(double& right_asc, double& declination) {
	// Convert right ascension [hhmmss] to hours
	right_asc /= 100;
	double sec, min, hour, hour_min;
	sec = std::modf(right_asc, &hour_min);
	hour_min /= 100;
	min = std::modf(hour_min, &hour);
	right_asc = hour + (min / 60) + (sec / 3600);

	// Convert declination [ddmmss] to degrees
	declination /= 100;
	double asec, amin, deg, deg_amin;
	asec = std::modf(declination, &deg_amin);
	deg_amin /= 100;
	amin = std::modf(deg_amin, &deg);
	if (deg < 0) {
		declination = deg - (amin / 60) - (asec / 3600);
	}
	else {
		declination = deg + (amin / 60) + (asec / 3600);
	}
}
// Check inputs
bool check(std::string input, int test) {
	// Check Y/N
	if (test == 1) {
		if (input == "Y" || input == "N") {
			return 0;
		}
		else {
			std::cout << "Invalid input. Insert 'Y' or 'N'. ";
			return 1;
		}
	}
	if (test == 2) {
		if (input == "i" || input == "f") {
			return 0;
		}
		else {
			std::cout << "Invalid input. Insert 'i' or 'f'. ";
			return 1;
		}
	}
	if (test == 3) {
		if (input == "d" || input == "o") {
			return 0;
		}
		else {
			std::cout << "Invalid input. Insert 'd' or 'o'. ";
			return 1;
		}
	}
	if (test == 4) {
		if (input == "c" || input == "n") {
			return 0;
		}
		else {
			std::cout << "Invalid input. Insert 'n' or 'c'. ";
			return 1;
		}
	}
	return 1;
}

// Create a star chart
void plot_chart(std::vector<std::unique_ptr<object>>& objects) {
	std::string yes_no;
	bool valid{ 1 };
	while (valid) {
		std::cout << "\nDo you want to create a star chart? (Y/N) ";
		std::cin >> yes_no;
		valid = check(yes_no, 1);
	}

	if (yes_no == "Y") {

		std::string show_planets, show_galaxies, show_nebulae, save_how;
		plot_what(show_planets, show_galaxies, show_nebulae, save_how, 1, 1);

		std::string def_range;
		valid = 1;
		while (valid) {
			std::cout << "Do you want to define the range of the plot? (Y/N) ";
			std::cin >> def_range;
			valid = check(def_range, 1);
		}

		double decl_min{ -910000 }, decl_max{ 910000 }, ra_min{ -000100 }, ra_max{ 240100 };
		if (def_range == "Y") {
			try {
				def_limits(decl_min, decl_max, ra_min, ra_max);
			}
			catch (int error_flag) {
				if (error_flag == constants::x_limit_flag) {
					std::cerr << "Error: Minimum x axis limit larger than maximum." << std::endl;
					exit(error_flag);
				}
				if (error_flag == constants::y_limit_flag) {
					std::cerr << "Error: Minimum y axis limit larger than maximum." << std::endl;
					exit(error_flag);
				}
			}
		}

		try {
			plot_star_chart(objects, decl_min, decl_max, ra_min, ra_max, show_planets, show_galaxies, show_nebulae, save_how);
		}
		catch (int error_flag) {
			if (error_flag == constants::no_plot_data) {
				std::cerr << "Error: No data to plot star chart." << std::endl;
				exit(error_flag);
			}
		}
	}
}
void plot_star_chart(std::vector<std::unique_ptr<object>>& objects, double decl_min, double decl_max, double ra_min, double ra_max,
	std::string show_planets, std::string show_galaxies, std::string show_nebulae, std::string save_how) {

	std::vector<double> st_declination, st_ra, pl_declination, pl_ra, gal_declination, gal_ra, neb_declination, neb_ra;

	// separate data by type and set range
	for (int i = 0; i < objects.size(); i++) {
		double decl = objects[i]->get_decl();
		double ra = objects[i]->get_ra();
		if (decl >= decl_min && decl <= decl_max && ra >= ra_min && ra <= ra_max) {
			if (objects[i]->get_type() == "star") {
				st_declination.push_back(decl);
				st_ra.push_back(ra);
			}
			if (objects[i]->get_type() == "planet") {
				pl_declination.push_back(decl);
				pl_ra.push_back(ra);
			}
			if (objects[i]->get_type() == "galaxy") {
				gal_declination.push_back(decl);
				gal_ra.push_back(ra);
			}
			if (objects[i]->get_type() == "nebula") {
				neb_declination.push_back(decl);
				neb_ra.push_back(ra);
			}
		}
	}
	std::vector<double> all_ra = st_ra;
	std::vector<double> all_declination = st_declination;
	// create a single vector with desired data
	if (show_planets == "Y") {
		all_ra.insert(std::end(all_ra), std::begin(pl_ra), std::end(pl_ra));
		all_declination.insert(std::end(all_declination), std::begin(pl_declination), std::end(pl_declination));
	}
	if (show_galaxies == "Y") {
		all_ra.insert(std::end(all_ra), std::begin(gal_ra), std::end(gal_ra));
		all_declination.insert(std::end(all_declination), std::begin(gal_declination), std::end(gal_declination));
	}
	if (show_nebulae == "Y") {
		all_ra.insert(std::end(all_ra), std::begin(neb_ra), std::end(neb_ra));
		all_declination.insert(std::end(all_declination), std::begin(neb_declination), std::end(neb_declination));
	}

	// throw error if there is no data to plot
	if (all_ra.size() == 0) throw constants::no_plot_data;
	
	// save to a txt file
	if (save_how == "f") {
		std::ofstream outfile("star_chart.txt");
		outfile << "# Right Ascension [hhmmss]\tDeclination [ddmmss]" << std::endl;
		for (int i = 0; i < all_ra.size(); i++) {
			outfile << all_ra[i] << "\t" << all_declination[i] << std::endl;
		}
		outfile.close();
		std::cout << "File 'star_chart.txt' was saved.\n" << std::endl;
	}

	// create the plot
	if (save_how == "i") {
		// convert units of data
		convert_units(st_ra, st_declination);
		convert_units(pl_ra, pl_declination);
		convert_units(gal_ra, gal_declination);
		convert_units(neb_ra, neb_declination);
		convert_units(decl_min, ra_min);
		convert_units(decl_max, ra_max);

		// create the figure
		bool success;
		StringReference* errorMessage = new StringReference();
		RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

		// create the scatter plots
		ScatterPlotSeries* stars = GetDefaultScatterPlotSeriesSettings();
		stars->xs = &st_ra;
		stars->ys = &st_declination;
		stars->linearInterpolation = false;
		stars->pointType = toVector(L"dots");
		stars->color = CreateRGBColor(1, 0, 0);
		
		ScatterPlotSeries* planets = GetDefaultScatterPlotSeriesSettings();
		planets->xs = &pl_ra;
		planets->ys = &pl_declination;
		planets->linearInterpolation = false;
		planets->pointType = toVector(L"circles");
		planets->color = CreateRGBColor(0, 0, 1);
		
		ScatterPlotSeries* galaxies = GetDefaultScatterPlotSeriesSettings();
		galaxies->xs = &gal_ra;
		galaxies->ys = &gal_declination;
		galaxies->linearInterpolation = false;
		galaxies->pointType = toVector(L"triangles");
		galaxies->color = CreateRGBColor(0, 1, 0);

		ScatterPlotSeries* nebulae = GetDefaultScatterPlotSeriesSettings();
		nebulae->xs = &neb_ra;
		nebulae->ys = &neb_declination;
		nebulae->linearInterpolation = false;
		nebulae->pointType = toVector(L"filled triangles");
		nebulae->color = CreateRGBColor(1, 0, 1);

		ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = false;
		settings->xMax = ra_max;
		settings->xMin = ra_min;
		settings->yMax = decl_max;
		settings->yMin = decl_min;
		settings->autoPadding = true;
		settings->title = toVector(L"Star Chart");
		settings->xLabel = toVector(L"Right Ascension (hours)");
		settings->yLabel = toVector(L"Declination (degrees)");

		settings->scatterPlotSeries->push_back(stars);
		// only show desired plots
		if (show_galaxies == "Y") {
			settings->scatterPlotSeries->push_back(galaxies);
		}
		if (show_planets == "Y") {
			settings->scatterPlotSeries->push_back(planets);
		}
		if (show_nebulae == "Y") {
			settings->scatterPlotSeries->push_back(nebulae);
		}

		success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);
		// save the image
		if (success) {
			std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, "star_chart.png");
			DeleteImage(imageReference->image);
			std::cout << "Image 'star_chart.png' was saved." << std::endl;
			std::cout << "Red dots are stars. Blue circles are planets. Green open triangles are galaxies. Purple triangles are nebulae.\n" << std::endl;
		}
		else {
			std::cerr << "Error: ";
			for (wchar_t c : *errorMessage->string) {
				std::cerr << c;
			}
			std::cerr << std::endl;
		}
	}
}

// Plot magnitude against distance
void plot_mag_dist_graph(std::vector<std::unique_ptr<object>>& objects) {
	std::string yes_no;
	bool valid{ 1 };
	while (valid) {
		std::cout << "Do you want to create a plot of magnitude vs. distance? (Y/N) ";
		std::cin >> yes_no;
		valid = check(yes_no, 1);
	}

	if (yes_no == "Y") {
		std::string show_planets, show_galaxies, show_nebulae, save_format;
		plot_what(show_planets, show_galaxies, show_nebulae, save_format, 0, 0);
		// try and catch any errors in plotting
		try {
			plot_mag_vs_dis(objects, show_planets, show_galaxies, show_nebulae);
		}
		catch (int error_flag) {
			if (error_flag == constants::no_plot_data) {
				std::cerr << "Error: No data to plot graph." << std::endl;
				exit(error_flag);
			}
		}
	}
}
void plot_mag_vs_dis(std::vector<std::unique_ptr<object>>& objects, std::string show_planets, std::string show_galaxies,
	std::string show_nebulae) {

	std::vector<double> st_distances, st_magnitudes, gal_distances, gal_magnitudes, neb_distances, neb_magnitudes;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_type() == "star") {
			st_distances.push_back(objects[i]->get_dist());
			st_magnitudes.push_back(objects[i]->get_mag());
		}
		else if (objects[i]->get_type() == "galaxy") {
			gal_distances.push_back(objects[i]->get_dist());
			gal_magnitudes.push_back(objects[i]->get_mag());
		}
		else if (objects[i]->get_type() == "nebula") {
			neb_distances.push_back(objects[i]->get_dist());
			neb_magnitudes.push_back(objects[i]->get_mag());
		}
	}

	std::vector<double> all_distances = st_distances;
	std::vector<double> all_magnitudes = st_magnitudes;

	if (show_galaxies == "Y") {
		all_distances.insert(std::end(all_distances), std::begin(gal_distances), std::end(gal_distances));
		all_magnitudes.insert(std::end(all_magnitudes), std::begin(gal_magnitudes), std::end(gal_magnitudes));
	}
	if (show_nebulae == "Y") {
		all_distances.insert(std::end(all_distances), std::begin(neb_distances), std::end(neb_distances));
		all_magnitudes.insert(std::end(all_magnitudes), std::begin(neb_magnitudes), std::end(neb_magnitudes));
	}
	// throw error if there is no data to plot
	if (all_distances.size() == 0 || all_magnitudes.size() == 0) throw constants::no_plot_data;

	std::ofstream outfile("mag_vs_dist.txt");
	outfile << "#Distance (pc) \t Magnitude" << std::endl;
	for (int i = 0; i < all_distances.size(); i++) {
		outfile << all_distances[i] << "\t" << all_magnitudes[i] << std::endl;
	}
	outfile.close();
	std::cout << "File 'mag_vs_dist.txt' was saved.\n" << std::endl;
}

// Plot the main sequence
void main_sequence(std::vector<std::unique_ptr<object>>&objects) {
	std::string yes_no;
	bool valid{ 1 };
	while (valid) {
		std::cout << "Do you want to create a plot of the main sequence? (Y/N) ";
		std::cin >> yes_no;
		valid = check(yes_no, 1);
	}

	if (yes_no == "Y") {
		std::string save_how;
		valid = 1;
		while (valid) {
			std::cout << "Do you want to save as an image (i) or a txt file (f)? ";
			std::cin >> save_how;
			valid = check(save_how, 2);
		}

		// try and catch any errors in plotting
		try {
			plot_main_seq(objects, save_how);
		}
		catch (int error_flag) {
			if (error_flag == constants::no_plot_data) {
				std::cerr << "Error: No data to plot graph." << std::endl;
				exit(error_flag);
			}
		}
	}
}
void plot_main_seq(std::vector<std::unique_ptr<object>>& objects, std::string save_how) {
	
	std::vector<double> radii, app_magnitudes, abs_magnitude, temperatures, distances;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->get_type() == "star") {
			radii.push_back(objects[i]->get_radius());
			app_magnitudes.push_back(objects[i]->get_mag());
			distances.push_back(objects[i]->get_dist());
		}
	}

	// throw error if there is no data to plot
	if (radii.size() == 0 || app_magnitudes.size() == 0) throw constants::no_plot_data;

	// calculate temperature and absolute magnitude of stars
	for (int i = 0; i < radii.size(); i++) {

		double abs_mag = app_magnitudes[i] - (5 * log10(distances[i])) + 5;
		abs_magnitude.push_back(abs_mag);

		double lum = constants::zero_point_lum * pow(10, - abs_mag / 2.5);

		double temp = constants::sun_temp * pow(1 / radii[i], 0.5) * pow(lum / constants::sun_lum, 0.25);

		temperatures.push_back(temp);
	}

	if (save_how == "f") {

		std::ofstream outfile("main_sequence.txt");
		outfile << "#Temperature (K) \t Absolute Magnitude" << std::endl;
		for (int i = 0; i < radii.size(); i++) {
			outfile << temperatures[i] << "\t" << abs_magnitude[i] << std::endl;
		}
		outfile.close();
		std::cout << "File 'main_sequence.txt' was saved." << std::endl;
	}

	if (save_how == "i") {
		bool success;
		StringReference* errorMessage = new StringReference();
		RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

		ScatterPlotSeries* stars = GetDefaultScatterPlotSeriesSettings();
		stars->xs = &temperatures;
		stars->ys = &abs_magnitude;
		stars->linearInterpolation = false;
		stars->pointType = toVector(L"dots");
		stars->color = CreateRGBColor(1, 0, 0);

		ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = true;
		settings->autoPadding = true;
		settings->title = toVector(L"Main sequence");
		settings->xLabel = toVector(L"Temperature (K)");
		settings->yLabel = toVector(L"Absolute Magnitude");
		settings->scatterPlotSeries->push_back(stars);

		success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

		if (success) {
			std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, "main_sequence.png");
			DeleteImage(imageReference->image);
			std::cout << "Image 'main_sequence.png' was saved." << std::endl;
		}
		else {
			std::cerr << "Error: ";
			for (wchar_t c : *errorMessage->string) {
				std::cerr << c;
			}
			std::cerr << std::endl;
		}
	}
}

// Create final report
void report(std::vector<std::unique_ptr<object>>& objects) {
	std::string brightest, dimmest, closest, furthest;
	double max_magnitude{ -100 }, min_magnitude{ 100 }, min_distance{ 100000 }, max_distance{ 0 };
	// Iterate vector and find max/min
	for (int i = 0; i < objects.size(); i++) {
		
		if (objects[i]->get_mag() > max_magnitude) {
			dimmest = objects[i]->get_name() + " " + objects[i]->get_type();
			max_magnitude = objects[i]->get_mag();
		}
		if (objects[i]->get_mag() < min_magnitude) {
			brightest = objects[i]->get_name() + " " + objects[i]->get_type();
			min_magnitude = objects[i]->get_mag();
		}
		if (objects[i]->get_dist() > max_distance) {
			furthest = objects[i]->get_name() + " " + objects[i]->get_type();
			max_distance = objects[i]->get_dist();
		}
		if (objects[i]->get_dist() < min_distance) {
			closest = objects[i]->get_name() + " " + objects[i]->get_type();
			min_distance = objects[i]->get_dist();
		}
	}
	std::cout.precision(5);
	std::cout << "\n----------------------------------------------------------------------------------------" << std::endl;
	std::cout << "| This catalogue contains:								|" << std::endl;
	std::cout << "| \t" << star::n_stars << " stars									|" << std::endl;
	std::cout << "| \t" << planet::n_planets << " planets									|" << std::endl;
	std::cout << "| \t" << galaxy::n_galaxies << " galaxies									|" << std::endl;
	std::cout << "| \t" << nebula:: n_nebulae << " nebulae									|" << std::endl;
	std::cout << "| The brightest object is " << brightest << " at an apparent magnitude " << min_magnitude << "			|" << std::endl;
	std::cout << "| The dimmest object is " << dimmest << " at an apparent magnitude " << max_magnitude << "			|" << std::endl;
	std::cout << "| The furthest object is " << furthest << " at a distance	" << max_distance << "pc		|" << std::endl;
	std::cout << "| The closest object is " << closest << " at a distance " << min_distance << "pc			|" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------\n" << std::endl;
}

// Search the database
void search_database(std::vector<std::unique_ptr<object>>& objects) {
	
	bool repeat{ 1 };
	while (repeat) {
		bool valid{ 1 };
		std::string search_how;
		while (valid) {
			std::cin.ignore();
			std::cout << "Would you like to search by object name (n) or right ascension and declination coordinates (c)? ";
			std::cin >> search_how;
			valid = check(search_how, 4);
		}
		// Search name
		bool found{ 0 };
		if (search_how == "n") {
			std::cin.ignore();
			std::string name;
			std::cout << "Please insert the name of the object: ";
			std::getline(std::cin, name);

			for (int i = 0; i < objects.size(); i++) {

				if (objects[i]->get_name() == name) {
					std::cout << "Object found." << std::endl;
					objects[i]->info();
					found = 1;
				}
			}
			if (!found) {
				std::cout << "Object not found." << std::endl;
			}
		}
		// Search coordinates
		if (search_how == "c") {
			double ra_in, decl_in;
			while (1) {
				std::cout << "Please insert the right ascension of the object in the format hhmmss (hour, minute, second): ";
				std::cin >> ra_in;
				if (std::cin.good()) {
					break;
				}
				else {
					std::cout << "Invalid Input. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
			}
			while (1) {
				std::cout << "Please insert the declination of the object in the format ddmmss(degree, arminute, arcsecond): ";
				std::cin >> decl_in;
				if (std::cin.good()) {
					break;
				}
				else {
					std::cout << "Invalid Input. " << std::endl;
					std::cin.clear();
					std::cin.ignore(100000, '\n');
				}
			}

			found = 0;
			for (int i = 0; i < objects.size(); i++) {
				double ra = objects[i]->get_ra();
				double decl = objects[i]->get_decl();
				if (ra_in >= (ra - 1) && ra_in <= (ra + 1) && decl_in >= (decl - 1) && decl_in <= (decl + 1)) {
					std::cout << "Object found." << std::endl;
					objects[i]->info();
					found = 1;
				}
			}

			if (!found) {
				std::cout << "Object not found." << std::endl;
			}
		}
		// Ask to repeat
		std::string yes_no;
		valid = 1;
		while (valid) {
			std::cin.ignore();
			std::cout << "\nWould you like to search another object? (Y/N) ";
			std::cin >> yes_no;
			valid = check(yes_no, 1);
		}
		if (yes_no == "N") {
			std::cout << "Exiting." << std::endl;
			repeat = 0;
		}
	}
}


// Static data members
int galaxy::n_galaxies{};
int star::n_stars{};
int planet::n_planets{};
int nebula::n_nebulae{};

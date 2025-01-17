// PHYS30762 Object Oriented Programming in C++
// Project: Star Catalogue
// Mercedes Figueiredo
// 10541186
// 23/05/2022
// file star_catalogue.h

#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>

#ifndef STAR_CATALOGUE_H
#define STAR_CATALOGUE_H

// ~~~~~~~~ classes ~~~~~~~~
// Base class as interface for observed objects
class object
{
public:
	// Default constructor
	object() = default;
	// Virtual destructor
	virtual ~object() {}
	// Move constructor
	object(object&&) noexcept {}
	// Virtual functions
	virtual void info() = 0;
	virtual double get_mag() { return 0; }
	virtual double get_dist() { return 0; }
	virtual double get_ra() { return 0; }
	virtual double get_decl() { return 0; }
	virtual double get_radius() { return 0; }
	virtual int get_num() { return 0; }
	virtual std::string get_type() { return "none"; }
	virtual std::string get_name() { return "none"; }
};

// Derived classes for galaxies, stars, planets & nebulae
class galaxy : public object
{
private:
	double magnitude, declination, right_ascension, distance, radius;
	std::string name;

public:
	// Default constructor
	galaxy() : name{}, magnitude{}, declination{}, right_ascension{}, distance{}, radius{} {n_galaxies++; }

	// Parameterised constructor
	galaxy(std::string in_name, double in_magnitude, double in_declination, double in_right_ascension, double in_distance, 
		double in_radius) : name{ in_name }, magnitude{ in_magnitude }, declination{ in_declination }, 
		right_ascension{ in_right_ascension }, distance{ in_distance }, radius{ in_radius } {n_galaxies++; }
	// Virtual destructor
	virtual ~galaxy() { n_galaxies--; }
	// Override virtual base class functions
	void info();
	double get_mag() { return magnitude; }
	double get_dist() { return distance; }
	double get_ra() { return right_ascension; }
	double get_decl() { return declination; }
	double get_radius() { return radius; }
	int get_num() { return n_galaxies; }
	std::string get_type() { return "galaxy"; }
	std::string get_name() { return name; }
	// Static data member
	static int n_galaxies;
};

class star : public object
{
private:
	double magnitude, declination, right_ascension, distance, radius;
	std::string name;

public:
	// Default constructor
	star() : name{}, magnitude{}, declination{}, right_ascension{}, distance{}, radius{} {n_stars++; }

	// Parameterised constructor
	star(std::string in_name, double in_magnitude, double in_declination, double in_right_ascension, double in_distance,
		double in_radius) : name{ in_name }, magnitude{ in_magnitude }, declination{ in_declination },
		right_ascension{ in_right_ascension }, distance{ in_distance }, radius{ in_radius } {n_stars++; }
	// Virtual destructor
	virtual ~star() { n_stars--; }
	// Override base class virtual functions
	void info();
	double get_mag() { return magnitude; }
	double get_dist() { return distance; }
	double get_ra() { return right_ascension; }
	double get_decl() { return declination; }
	double get_radius() { return radius; }
	int get_num() { return n_stars; }
	std::string get_type() { return "star"; }
	std::string get_name() { return name; }
	static int n_stars;
};

class planet : public object
{
private:
	double magnitude, declination, right_ascension, distance, radius;
	std::string name;

public:
	// Default constructor
	planet() : name{}, magnitude{}, declination{}, right_ascension{}, distance{}, radius{} {n_planets++; }

	// Parameterised constructor
	planet(std::string in_name, double in_magnitude, double in_declination, double in_right_ascension, double in_distance,
		double in_radius) : name{ in_name }, magnitude{ in_magnitude }, declination{ in_declination },
		right_ascension{ in_right_ascension }, distance{ in_distance }, radius{ in_radius } {n_planets++; }
	// Virtual destructor
	virtual ~planet() { n_planets--; }
	// Override base class virtual functions
	void info();
	double get_mag() { return magnitude; }
	double get_dist() { return distance; }
	double get_ra() { return right_ascension; }
	double get_decl() { return declination; }
	double get_radius() { return radius; }
	int get_num() { return n_planets; }
	std::string get_type() { return "planet"; }
	std::string get_name() { return name; }
	static int n_planets;
};

class nebula : public object
{
private:
	double magnitude, declination, right_ascension, distance, radius;
	std::string name;

public:
	// Default constructor
	nebula() : name{}, magnitude{}, declination{}, right_ascension{}, distance{}, radius{} {n_nebulae++; }

	// Parameterised constructor
	nebula(std::string in_name, double in_magnitude, double in_declination, double in_right_ascension, double in_distance,
		double in_radius) : name{ in_name }, magnitude{ in_magnitude }, declination{ in_declination },
		right_ascension{ in_right_ascension }, distance{ in_distance }, radius{ in_radius } {n_nebulae++; }
	// Virtual destructor
	virtual ~nebula() { n_nebulae--; }
	// Override base class virtual functions
	void info();
	double get_mag() { return magnitude; }
	double get_dist() { return distance; }
	double get_ra() { return right_ascension; }
	double get_decl() { return declination; }
	double get_radius() { return radius; }
	int get_num() { return n_nebulae; }
	std::string get_type() { return "nebula"; }
	std::string get_name() { return name; }
	static int n_nebulae;
};

// ~~~~~~~~ functions ~~~~~~~~
void input(std::vector<std::unique_ptr<object>>& objects);
void file_in(std::vector<std::unique_ptr<object>>& objects, std::string file_name);
void console_in(std::vector<std::unique_ptr<object>>& objects);
void plot_what(std::string& show_planets, std::string& show_galaxies, std::string& show_nebulae, std::string& save_format);
void plot_chart(std::vector<std::unique_ptr<object>>& objects);
void plot_star_chart(std::vector<std::unique_ptr<object>>& objects, double decl_min, double decl_max, double ra_min, double ra_max,
	std::string show_planets, std::string show_galaxies, std::string show_nebulae, std::string save_how);
void plot_mag_dist_graph(std::vector<std::unique_ptr<object>>& objects);
void plot_mag_vs_dis(std::vector<std::unique_ptr<object>>& objects, std::string show_planets, std::string show_galaxies, std::string show_nebulae);
void report(std::vector<std::unique_ptr<object>>& objects);
bool check(std::string input, int test);
void convert_units(std::vector<double>& right_asc, std::vector<double>& declination);
void convert_units(double& right_asc, double& declination);
void def_limits(double& decl_min, double& decl_max, double& ra_min, double& ra_max);
void main_sequence(std::vector<std::unique_ptr<object>>& objects);
void plot_main_seq(std::vector<std::unique_ptr<object>>& objects, std::string save_how);
void search_database(std::vector<std::unique_ptr<object>>& objects);

// Namespace with global constants
namespace constants
{
	// Error flags
	const int no_data(-1);
	const int x_limit_flag(-2);
	const int y_limit_flag(-3);
	const int no_plot_data(-4);
	const int read_file(-5);
	const int no_file(-6);
	// Physical constants
	const double sun_mag(-26.74); // apparent magnitude
	const double sun_flux(1373); // W m^-2
	const double stef_boltzmann(5.670e-8); // W m^-2 K^-4
	const double parsec(3.086e16); // m
	const double sun_radius(6.955e8); // m
	const double sun_lum(3.84e26); // W
	const double zero_point_lum(3.0128e28); // W
	const double sun_temp(5778); // K
}

#endif
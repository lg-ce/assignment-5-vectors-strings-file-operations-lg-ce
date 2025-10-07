#include <stdio.h>
#include "pixel.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>      // for std::stoi, std::stof


std::vector<Pixel> pixel_list;

void average_colors(std::vector<Pixel> &pixel_list);
void flip_vertically(std::vector<Pixel> &pixel_list);
void print_pixels(std::vector<Pixel> &pixel_list);


//print function (for practice)
void print_pixels(std::vector<Pixel> &pixel_list) {
	for(int k = 0; k < (int)pixel_list.size(); k++) {
		Pixel &p = pixel_list[k];
		std::cout << "Pixel #" << k << ": ";
		std::cout << "x = " << p.x << ", ";
		std::cout << "y = " << p.y << ", ";
		std::cout << "r = " << p.r << ", ";
		std::cout << "g = " << p.g << ", ";
		std::cout << "b = " << p.b << std::endl;
	}
	printf("\n");
}

void average_colors(std::vector<Pixel> &pixel_list){
	float sum_r = 0.0;
	float sum_b = 0.0;
	float sum_g = 0.0;
		
	for(int k = 0; k < (int)pixel_list.size(); k++) {
		Pixel &p = pixel_list[k];
		sum_r += p.r;
		sum_b += p.b;
		sum_g += p.g;
	}
		
	float average_r = sum_r/((float)pixel_list.size());
	std::cout << "Average r: " << average_r << "\n";
		
	float average_g = sum_g/((float)pixel_list.size());
	std::cout << "Average g: " << average_g << "\n";

	float average_b = sum_b/((float)pixel_list.size());
	std::cout << "Average b: " << average_b << "\n\n";
}



void flip_vertically(std::vector<Pixel> &pixel_list) {
	Pixel p_temp = pixel_list[0];
	int size_loop = (int)pixel_list.size();
	
	for(int k = 0; k < (size_loop/2); k++) {
		std::swap(pixel_list[k], pixel_list[size_loop - k - 1]);
		//p_temp = pixel_list[k];
		//pixel_list[k] = pixel_list[size_loop - k - 1];
		//pixel_list[size_loop - k - 1] = p_temp;
	}
	
	std::cout << "Flipped.dat:\n";
	print_pixels(pixel_list);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file>\n";
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open pixels.dat\n";
		return 1;
	}

/* wrong
	std::ifstream file("pixels.dat");
	if (!file.is_open()) {
		std::cerr << "Error: Could not open pixels.dat file\n";
		return 1;  // Exit early
	}
	*/
	
	std::string line;
	
	size_t length_x;
	size_t length_y;
	size_t length_r;
	size_t length_g;
	//size_t length_b;
	
	while (std::getline(file, line)){
		// find length of x,y,r,g,b by searching for commas
		length_x = line.find(",");
		length_y = line.find(",",length_x + 1);
		length_r = line.find(",",length_y + 1);
		length_g = line.find(",",length_r + 1);
		//length_b = line.find("\n",length_g + 1);

		
		// extract substrings for x,y,r,g,b
		std::string string_x = line.substr(0, length_x);
		std::string string_y = line.substr((length_x + 1), (length_y - length_x - 1));
		std::string string_r = line.substr((length_y + 1), (length_r - length_y - 1));
		std::string string_g = line.substr((length_r + 1), (length_g - length_r - 1));
		std::string string_b = line.substr((length_g + 1)); // function will automatically extract through end of the line
		
		// try-catch to extract error messages
		try{
			Pixel p;
			p.x = std::stoi(string_x); // std::stoi - casts string to integer
			p.y = std::stoi(string_y);
			p.r = std::stof(string_r); // std::stof - parse string as a floating-point number and return float value
			p.g = std::stof(string_g);
			p.b = std::stof(string_b);
			
			pixel_list.push_back(p); // add the pixel to the pixel_list vector
		} catch (const std::exception& e) {
			std::cerr << "Error parsing line: - " << e.what() << "\n"; // std::cerr - "output error messages to the standard error stream"
		} // end try-catch
	}
	

	printf("\n\n");
	print_pixels(pixel_list);
	average_colors(pixel_list);
	flip_vertically(pixel_list);
	
	
	/*# Step 5
	After flipping the image, save the new pixel list to a file called flipped.dat.  
	Output the individual x, y, r, g, b values in the same format as the input file.
	*/
	std::ofstream newfile("flipped.dat"); // create file & automatically open it	
	if(!newfile.is_open()) { // if the file didn't open...
		std::cerr << "Error: could not open flipped.dat.\n";
		return 1;
	}
	
	for(int k = 0; k < (int)pixel_list.size(); k++) {		
		newfile << pixel_list[k].x << "," << pixel_list[k].y << "," << pixel_list[k].r << "," << pixel_list[k].g << "," << pixel_list[k].b << std::endl;
	}
	
	return 0;
}


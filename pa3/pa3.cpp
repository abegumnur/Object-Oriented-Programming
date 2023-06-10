#pragma region include - using directives

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>
using std::vector;
using std::string;
using std::cout;
using std::fstream;
using std::cin;
using std::getline;
using std::ifstream;
using std::ofstream;

#pragma endregion

#pragma region constants

const int MIN_PIX = 0; 
const int MAX_PIX = 255;
const string FORMAT = "P3"; // image format
const int MAX_WSPACE = 100; // maximum whitespace char to ignore

#pragma endregion

#pragma region Pixel Class

class Pixel{

    public:
        Pixel();
        Pixel(int r, int b, int g);
        Pixel(const Pixel& p);
        Pixel& convertGrayscale(float coef_r, float coef_b, float coef_g, int max);
        Pixel& operator=(const Pixel& left);
        Pixel operator+(const Pixel& left);
        Pixel operator-(const Pixel& left);
        const int& at(int choice) const;
        int& getRed();
        int& getBlue();
        int& getGreen();
        void setRed(int r);
        void setBlue(int b);
        void setGreen(int g);
        int getValidPixel(int p);

    private:
        int red;
        int blue;
        int green;

    friend std::ostream& operator<<(std::ostream& out, const Pixel& pix);
};


#pragma endregion

#pragma region Pixel 

Pixel::Pixel() : red(0), blue(0), green(0)
{}

Pixel::Pixel(int r, int b, int g) : red(r), blue(b), green(g)
{}

int& Pixel::getRed()
{ return red; }

int& Pixel::getBlue()
{ return blue; }

int& Pixel::getGreen() 
{ return green; }

void Pixel::setRed(int r)
{ 
    red = getValidPixel(r);
}

void Pixel::setBlue(int b)
{ 
    blue = getValidPixel(b);
}

void Pixel::setGreen(int g)
{   
    green = getValidPixel(g);
}

const int& Pixel::at(int choice) const
{
    switch (choice)
    {
    case 1:
        return red;
        break;
    case 2:
        return blue;
        break;    
    case 3:
        return green;
        break;
    default:
        std::cerr << "Out of bounds.\n";
        static int ret = -1;
        return ret;
        break;
    }
}

int Pixel::getValidPixel(int p)
{
    if(p > MAX_PIX)
        return MAX_PIX;
        
    if( p < MIN_PIX)
        return MIN_PIX;
        
    return p;

}

Pixel::Pixel(const Pixel &p)
{
    red = p.red;
    blue = p.blue;
    green = p.green;

}

Pixel &Pixel::convertGrayscale(float coef_r, float coef_b, float coef_g, int max)
{
    // calculating the grayscale values
    int res = (((coef_r * red) + (coef_b * blue) + (coef_g * green)) >  max ) 
                ? max : ((coef_r * red) + (coef_b * blue) + (coef_g * green));
 
    red = res;
    blue = res;
    green = res;

    return *this;
}

Pixel &Pixel::operator=(const Pixel &left)
{
    red = left.red;
    blue = left.blue;
    green = left.green;

    return *this;

}


Pixel Pixel::operator+(const Pixel &left)
{
    Pixel result;   

    ( red + left.red > MAX_PIX) ? (result.red = MAX_PIX) : (result.red = red + left.red);
    ( blue + left.blue > MAX_PIX) ? (result.blue = MAX_PIX) : (result.blue = blue + left.blue);
    ( green + left.green > MAX_PIX) ? (result.green = MAX_PIX) : (result.green = green + left.green);

    return result;

}

Pixel Pixel::operator-(const Pixel &left)
{
    Pixel result;   

    ( red - left.red < MIN_PIX) ? (result.red = MIN_PIX) : (result.red = red - left.red);
    ( blue - left.blue < MIN_PIX) ? (result.blue = MIN_PIX) : (result.blue = blue - left.blue);
    ( green - left.green < MIN_PIX) ? (result.green = MIN_PIX) : (result.green = green - left.green);

    return result;

}

std::ostream &operator<<(std::ostream &out, const Pixel &pix)
{
    out << pix.red << " ";
    out << pix.blue << " ";
    out << pix.green << " ";

    return out;

}

#pragma endregion

#pragma region PpmImage Class


class PpmImage{

    public:
        PpmImage();      // no parameter constructor is set to default 
        PpmImage(const std::string fileName);   
        PpmImage(const PpmImage& im);
        PpmImage(int h, int w);    
        PpmImage(int h, int w, int max);
        void resizePpmImage(const int h, const int w);
        void writePpmImage(const std::string fileName);
        PpmImage& convertGrayscale(float c_r, float c_b, float c_g);
        PpmImage& operator=(const PpmImage& left); 
        PpmImage operator+(const PpmImage& left);
        PpmImage operator-(const PpmImage& left);
        void setPixel(const int row, const int column, const Pixel& pixel);
        void setPixel(int row, int column, int red, int blue, int green);
        bool SwapPixels(int row, int column, int choice);
        const Pixel& getPixel(const int row, const int column) const;
        int& operator()(int row, int column, int color);
        const int& operator()(int row, int column, int color) const;
        int getWidth() const;
        int getHeight() const;
        int getMax() const;
        void setMax(const int m);
        void setWidth(const int w);
        void setHeight(const int h);
        void setName(const std::string n);
        std::string getName() const;

    private:
        std::string name;  // name of the image 
        int width;         //dimensions of the image
        int height;
        int maximum;
        std::vector<std::vector<Pixel>> image;

        friend std::ostream& operator<<( std::ostream& out,const PpmImage im);

};

#pragma endregion

#pragma region PpmImage
/* mutator and accessor functions   */
int PpmImage::getWidth() const
{   return width;     }

int PpmImage::getHeight() const
{   return height;    }

string PpmImage::getName() const
{   return name;      }

int PpmImage::getMax() const
{   return maximum;    }

void PpmImage::setMax(int m) 
{   maximum = m;       }

void PpmImage::setWidth(const int w)
{   width = w;        }

void PpmImage::setHeight(const int h)
{   height = h;       }

void PpmImage::setName(const string n)
{   name = n;         }

void PpmImage::setPixel(const int row, const int column, const Pixel &pixel)
{   image[row][column] = pixel;  }

const Pixel& PpmImage::getPixel(const int row, const int column) const
{   return image[row][column];   }

void PpmImage::setPixel(int row, int column, int red, int blue, int green){

    setPixel(row, column, Pixel(red, blue, green));
}


PpmImage::PpmImage() : name(""), width(0), height(0), maximum(0)
{
    image = std::vector<std::vector<Pixel>>();
}

PpmImage::PpmImage(const string fileName){

    /* converting the fileName string to c-type string for the open() function */
    char file[ fileName.length() + 1];
    strcpy(file, fileName.c_str());  
                                    
    string form;
    ifstream fin(file);  /* opens the file   */

    int w, h, r, g, b;  /* width - height etc */
    int max;
    int cur_col = 0, cur_row = 0;

    /* if the file opening is unsucsessful*/
    if( fin.fail() ){       
        std::cerr << "Error opening file. Terminating the program...\n";
        exit(EXIT_FAILURE);

    }

    fin >> form; /* get the format of the image */

    if( form != FORMAT)
        std::cerr << "Invalid format.\n";

    fin >> w >> h;          /* get the width and height of the image    */

    if( w < 0 || h < 0)
        std::cerr << "Negative width or height value.\n";

    width = w;
    height = h;

    image.reserve(height);         /* reserve the number of rows for the vector     */
    
    for(int i = 0; i < height; i++){    /* reserve the number of columns for the vector    */
        image.emplace_back();
        image[i].reserve(width);
    }

    fin >> max;

    if( max > MAX_PIX)
        std::cerr << "Invalid max value.\n";

    maximum = max;
    name = fileName;         /* assign the fileName as the name of the object   */

    while( fin >> r >> b >> g ){    /* get the red - blue - green values    */

            if( r < MIN_PIX || b < MIN_PIX || g < MIN_PIX )
                std::cerr << "Negative.\n";
            else if( r > max || g > max || b >  max)
                std::cerr << "Too high.\n";

            image[cur_col].emplace_back(r, b, g);  /* assign the pixels one by one  */
            
            if( ++cur_row == width ){       
                cur_col++;
                cur_row = 0;
            }
    
    }

    fin.close();
    
}

PpmImage::PpmImage(const PpmImage& im){

    height = im.getHeight();
    width = im.getWidth();

    maximum = im.getMax();
    name = im.getName();

    image = im.image;
}


/* Constructs a blank page by the given dimensions  */
PpmImage::PpmImage(int h, int w)
{
    height = h;
    width = w;

    /* reserving the vector columns-rows    */
    image.reserve(height);
    for(int i = 0; i < height; i++){
        image.emplace_back();
        image[i].reserve(width);
    }

    int i, k;
    maximum = MAX_PIX;
    /* assign 255 to every pixel value  */
    for(i = 0; i < height; i++)
        for(k = 0; k < width; k++){   
            image[i].push_back( Pixel(MAX_PIX, MAX_PIX, MAX_PIX));        
        }

    /* Every blank page has the same name   */
    name = "Blank-Page.ppm";

}

PpmImage::PpmImage(int h, int w, int max){

    height = h;
    width = w;

    /* reserving the vector columns-rows    */
    image.reserve(height);
    for(int i = 0; i < height; i++){
        image.emplace_back();
        image[i].reserve(width);
    }

    int i, k;
    maximum = max;
    /* assign 255 to every pixel value  */
    for(i = 0; i < height; i++)
        for(k = 0; k < width; k++){   
            image[i].push_back( Pixel(maximum, maximum, maximum));        
        }

    /* Every blank page has the same name   */
    name = "Blank-Page-by-Max.ppm";

}

void PpmImage::resizePpmImage(const int h, const int w){

    /* clearing the old vector  */
    image.clear();

    /* resizing the image vector accordingly*/
    image.resize(h);
    for(auto& row : image)
        row.resize(w);

}

bool PpmImage::SwapPixels(int row, int column, int choice){

    int new_green, new_red, new_blue;
    int red, green, blue;

    switch (choice)
    {
    case 1: /* swap red and green*/
        new_green = operator()(row, column, 1);
        new_red =  operator()(row, column, 3);
        blue =  operator()(row, column, 2);
        setPixel(row, column, Pixel(new_red, blue, new_green));
        break;
    case 2: /* swap red and blue*/
        new_blue = operator()(row, column, 1);
        new_red = operator()(row, column, 2);
        green = operator()(row, column, 3);
        //Pixel pixel(new_red, new_blue, green); 
        setPixel(row, column, Pixel(new_red, new_blue, green));
        break;
    case 3: /* swaps green and blue*/
        red =  operator()(row, column, 1);
        new_green =  operator()(row, column, 2);
        new_blue =  operator()(row, column, 3);
        setPixel(row, column, Pixel(red, new_blue, new_green));
        break;
    default:
        break;
    }

    return true;
}

PpmImage& PpmImage::operator=(const PpmImage &left)
{
    setWidth( left.getWidth() );
    setHeight( left.getHeight() );
    setMax( left.getMax() );

    /* clearing the old vector  */
    image.clear();

    /* resizing the image vector accordingly*/
    image.resize(height);
    for(auto& row : image)
        row.resize(width);
    
    /* assign the new values */
    for(int i = 0; i < height; i++)
        for(int k = 0; k < width; k++)
            image[i][k] = left.image[i][k];
            

    return *this;

}

PpmImage PpmImage::operator+(const PpmImage& left){
    /* check if the width and height is the same for both objects*/
    if(width != left.getWidth() || height != left.getHeight() ){
        PpmImage empty;
        return empty;
    }

    /* adding the pixel values one by one*/
    PpmImage result(height, width, maximum);
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
                result.image[i][k] = image[i][k] + left.image[i][k];
        }
    }

    return result;

}

PpmImage PpmImage::operator-(const PpmImage& left){
    
    /* check if the width and height is the same for both objects*/
    if(width != left.getWidth() || height != left.getHeight() ){
        PpmImage empty;
        return empty;
    }
    /* substracting the pixel values one by one*/
    PpmImage result(height, width, maximum);
    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){
                result.image[i][k] = image[i][k] - left.image[i][k];
        }
    }

    return result;

}

int& PpmImage::operator()(int row, int column, int color){
    
    switch (color)
    {
    case 1:
        return image[row][column].getRed();
        break;
    case 2:
        return image[row][column].getBlue();
        break;
    case 3: 
        return image[row][column].getGreen();
        break;
    default:
        std::cerr << "Colour value should be between 1-3 (red, blue and green).";
        static int default_val = -1;
        return default_val;
        break;
    }

}

const int& PpmImage::operator()(int row, int column, int color) const{
    
    switch (color)
    {
    case 1:
        return image[row][column].at(1);
        break;
    case 2:
        return image[row][column].at(2);
        break;
    case 3: 
        return image[row][column].at(3);
        break;
    default:        
        std::cerr << "Colour value should be between 1-3 (red, blue and green).";
        static int default_val = -1;
        return default_val;
        break;
    }

}

PpmImage& PpmImage::convertGrayscale(float c_r, float c_b, float c_g){

    /* check the given coefficient values are between 0-1 */
    bool valid = ( ( c_r <= 1 && c_r >= 0) && ( c_b <= 1 && c_b >= 0) 
                    && ( c_g <= 1 && c_g >= 0) );
    
    if( !valid ){
        std::cerr << "Invalid coefficient for converting to grayscale.\n";
        exit(EXIT_FAILURE);
    }
    
    /* calls the convertGrayscale function of the Pixel class   */
    for(int i = 0; i < image.size(); i++)
        for(int k = 0; k < image[i].size(); k++)
            image[i][k].convertGrayscale(c_r, c_b, c_g, maximum);
    
    return *this;
}


void PpmImage::writePpmImage(const string fileName){

    char file[fileName.length() + 1];
    strcpy(file, fileName.c_str() ); 

    ofstream fout(file);

    /* if opening the file has failed print error and terminate   */
    if(fout.fail()){
        std::cerr << "Error opening output file. Terminating the program...\n";
        exit(EXIT_FAILURE);
    }
    
    /* writing P3 - width - height - maximum value  */
    fout << FORMAT <<"\n";
    fout << width << " " << height << "\n";
    fout << maximum << "\n";

    /* hands things off to Pixel class friend extraction operator */
    for(int i = 0; i < image.size(); i++){
        for(int k = 0; k < image[i].size(); k++)
            fout << image[i][k];
        fout << "\n";
    }


    fout.close();

}

std::ostream &operator<<(std::ostream &out, const PpmImage im)
{
    /* print the name of the image*/
    out << im.getName() << "\n";

    out << FORMAT << "\n";
    out << im.getWidth() << " " << im.getHeight() << "\n";
    out << im.getMax() << "\n";

    /* hand things off to << operator overloaded by the Pixel class */
    for (const auto& row : im.image) {
        for (const auto& col : row) {
            out << col;
        }
        out << "\n";
    }

    return out;

}

#pragma endregion

#pragma stand-alone functions

int read_ppm(const string source_ppm_file_name, PpmImage& destination_object){

    /* converting the fileName string to c-type string for the open() function */
    char file[source_ppm_file_name.length() + 1];
    strcpy(file, source_ppm_file_name.c_str());  
                                    
    string form;
    ifstream fin(file);  /* opens the file   */

    int w, h, r, g, b;  /* width - height etc */
    int max;
    int cur_col = 0, cur_row = 0;

    /* if the file opening is unsucsessful*/
    if( fin.fail() ){       
        std::cerr << "Error opening file!\n";
        return 0;
    }

    getline(fin, form );    /* get the format of the image */

    if( form != FORMAT){
        std::cerr << "Invalid format.\n";
        return 0;
    }

    fin >> w >> h;          /* get the width and height of the image    */
    if( w < 0 || h < 0){
        std::cerr << "Negative width or height value.\n";
        return 0;
    }

    destination_object.setWidth(w);
    destination_object.setHeight(h);

    destination_object.resizePpmImage(h, w);

    fin >> max;
    if( max > MAX_PIX){
        std::cerr << "Invalid max value.\n";
        return 0;
    }
    destination_object.setMax(max);
    destination_object.setName(source_ppm_file_name);

    while( fin >> r >> b >> g ){    /* get the red - blue - green values    */

            if( r < MIN_PIX || b < MIN_PIX || g < MIN_PIX )
                std::cerr << "Negative Pixel value.\n";
            else if( r > max || g > max || b >  max){
                std::cerr << "Too high Pixel value.\n";
            }

            Pixel pixel(r, b, g);
            destination_object.setPixel(cur_col, cur_row, pixel);

            if( ++cur_row == w ){       
                cur_col++;
                cur_row = 0;
            }
    }

    fin.close();
    return 1;
}

int write_ppm(const string destination_ppm_file_name, const PpmImage& source_object){

    char file[destination_ppm_file_name.length() + 1];
    strcpy(file, destination_ppm_file_name.c_str() ); 

    ofstream fout(file);

    /* if opening the file has failed print error and terminate   */
    if(fout.fail()){
        std::cerr << "Error opening output file. Terminating the program...\n";
        return 0;    
    }
    
    /* writing P3 - width - height - maximum value  */
    fout << FORMAT <<"\n";
    fout << source_object.getWidth() << " " << source_object.getHeight() << "\n";
    fout << source_object.getMax() << "\n";

    /* hands things off to Pixel class friend extraction operator */
    for(int i = 0; i < source_object.getHeight(); i++){
        for(int k = 0; k < source_object.getWidth(); k++)
            fout << source_object.getPixel(i, k);

        fout << "\n";
    }

    fout.close();

    return 1;

}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){

    PpmImage image_1;
    PpmImage image_2;
    
    if(! read_ppm(filename_image1, image_1)){
        std::cerr << "Error reading the first file.\n";
        return 0;
    }

    if(! read_ppm(filename_image2, image_2)){
        std::cerr << "Error reading the second file.\n";
        return 0;
    }

    PpmImage result = image_1 + image_2;

    if(! write_ppm(filename_image3, result)){
        std::cerr << "Error writing the result to file.\n";
        return 0;
    }

    return 1;
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
 
    PpmImage image_1;
    PpmImage image_2;
    
    if(! read_ppm(filename_image1, image_1)){
        std::cerr << "Error reading the first file.\n";
        return 0;
    }

    if(! read_ppm(filename_image2, image_2)){
        std::cerr << "Error reading the second file.\n";
        return 0;
    }

    PpmImage result = image_1 - image_2;

    if(! write_ppm(filename_image3, result)){
        std::cerr << "Error writing the result to file.\n";
        return 0;
    }

    return 1;

}

int test_print(const string filename_image1){

    PpmImage image(filename_image1);
    cout << image;

    return 1;
}

// implement this using the function-call operator overloaded.
// this function swaps the color values of every pixel in a given ppm image.
// this function does not create a new object but modifies the given one.
// if swap_choice is 1: swaps red and green
// if swap_choice is 2: swaps red and blue
// if swap_choice is 3: swaps green and blue
// if swap_choice is not 1, 2 or 3: no swaps (this does not mean that the operation is notsuccessful. the function should return 1 in this case if everything is normal)
// returns 1 if the operation is successful. otherwise, returns 0.
int swap_channels(PpmImage& image_object_to_be_modified, int swap_choice){

    int height = image_object_to_be_modified.getHeight();
    int width = image_object_to_be_modified.getWidth();

    for(int i = 0; i < height; i++)
        for(int k = 0; k < width; k++)
            image_object_to_be_modified.SwapPixels(i, k, swap_choice);
        

    return 1;
}

// implement this using the function-call operator overloaded.
// creates and returns a copy of a new ppmImage object which stores only one color at each pixel. 
//This simply takes the source and copies only one color information and stores it ina new object.
//The other color channels are simply going to be zeros
//if color_choice is 1: red channel is preserved
//if color_choice is 2: green channel is preserved
//if color_choice is 3: blue channel is preserved
PpmImage single_color(const PpmImage& source, int color_choice){

    int height = source.getHeight();
    int width = source.getWidth();
    
    PpmImage single_col(height, width, 0);
    
    single_col.setName(source.getName());
    single_col.setMax(source.getMax());
    int red, blue, green;

    for(int i = 0; i < height; i++){
        for(int k = 0; k < width; k++){

            switch (color_choice)
            {
            case 1:
                red = source(i, k, 1);
                single_col.setPixel(i, k, Pixel(red, 0, 0));
                break;
            case 2:
                blue = source(i, k, 2);
                single_col.setPixel(i, k, Pixel(0, blue, 0));
                break;            
            case 3:
                green = source(i, k, 3);
                single_col.setPixel(i, k, Pixel(0, 0, green));
                break;
            
            default:
                break;
            }
        }
    }

    return single_col;

        
}


#pragma endregion

int main(int argc, char** argv){

    if(argc < 3){
        cout << "At least 3 arguments should be given." << "\n";
        exit(EXIT_FAILURE);
    }

    int choice = std::stoi(argv[1]);    // choice number

    string ppm_file_name1(argv[2]);   // given file name

    PpmImage image_read;    //image read from the given file
    PpmImage single_color_img;

    switch (choice)
    {
    case 1:
        if(argc != 5)   return 0;
        test_addition(ppm_file_name1, argv[3], argv[4]);
        break;
    case 2:
        if(argc != 5)   return 0;
        test_subtraction(ppm_file_name1, argv[3], argv[4]);
        break;
    case 3:
        read_ppm(ppm_file_name1, image_read);   // check error return value
        swap_channels(image_read, 2);
        write_ppm("ppm_file_name2.txt", image_read);
        break;
    case 4:
        read_ppm(ppm_file_name1, image_read);   // check error return value
        swap_channels(image_read, 3);
        write_ppm("ppm_file_name2.txt", image_read);
        break;
    case 5:
        read_ppm(ppm_file_name1, image_read);
        single_color_img = single_color(image_read, 1);
        write_ppm("ppm_file_name2.txt", single_color_img);
        break;
    case 6:
        read_ppm(ppm_file_name1, image_read);
        single_color_img = single_color(image_read, 2);
        write_ppm("ppm_file_name2.txt", single_color_img);
        break;
    case 7:
        read_ppm(ppm_file_name1, image_read);
        single_color_img = single_color(image_read, 3);
        write_ppm("ppm_file_name2.txt", single_color_img);
        break;
    default:
        std::cerr << "Invalid choice (1-7). Terminating the program...\n";
        break;
    }

return 0;
    

}


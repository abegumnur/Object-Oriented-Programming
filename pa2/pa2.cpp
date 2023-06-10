#pragma region include - using directives

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

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
        Pixel& convertGrayscale(float coef_r, float coef_b, float coef_g);
        Pixel& operator=(const Pixel& left);
        int getRed() const;
        int getBlue() const;
        int getGreen() const;
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

int Pixel::getRed() const
{ return red; }

int Pixel::getBlue() const
{ return blue; }

int Pixel::getGreen() const
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
    red = p.getRed();
    blue = p.getBlue();
    green = p.getGreen();

}

Pixel &Pixel::convertGrayscale(float coef_r, float coef_b, float coef_g)
{
    // calculating the grayscale values
    int res = (((coef_r * red) + (coef_b * blue) + (coef_g * green)) > MAX_PIX ) 
                ? MAX_PIX : ((coef_r * red) + (coef_b * blue) + (coef_g * green));
 
    red = res;
    blue = res;
    green = res;

    return *this;
}

Pixel &Pixel::operator=(const Pixel &left)
{
    red = left.getRed();
    blue = left.getBlue();
    green = left.getGreen();

    return *this;

}

std::ostream &operator<<(std::ostream &out, const Pixel &pix)
{
    out << pix.getRed() << " ";
    out << pix.getBlue() << " ";
    out << pix.getGreen() << " ";

    return out;

}

#pragma endregion

#pragma region PpmImage Class


class PpmImage{

    public:
        PpmImage() = default;      // no parameter constructor is set to default 
        PpmImage(const std::string fileName);   
        PpmImage(int h, int w);    
        void writePpmImage(const std::string fileName);
        PpmImage& convertGrayscale(float c_r, float c_b, float c_g);
        PpmImage operator=(const PpmImage& left); 
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
        int max = MAX_PIX;
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
{   return max;       }

void PpmImage::setMax(const int m)
{   max = m;  }

void PpmImage::setWidth(const int w)
{   width = w;        }

void PpmImage::setHeight(const int h)
{   height = h;       }

void PpmImage::setName(const string n)
{   name = n;         }

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

    getline(fin, form );    /* get the format of the image */

    //if( form != FORMAT)
    //    std::cerr << "Invalid format.\n";

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
    this->max = max;
    
    //if( max != MAX_PIX)
    //    std::cerr << "Invalid max value.\n";

    name = fileName;         /* assign the fileName as the name of the object   */

    while( fin >> r >> b >> g ){    /* get the red - blue - green values    */

            if( r < MIN_PIX || b < MIN_PIX || g < MIN_PIX )
                std::cerr << "Negative.\n";
            else if( r > max|| g > max || b > max)
                std::cerr << "Too high.\n";

            image[cur_col].emplace_back(r, b, g);  /* assign the pixels one by one  */
            
            if( ++cur_row == width ){       
                cur_col++;
                cur_row = 0;
            }
    
    }

    fin.close();
    

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

    /* assign 255 to every pixel value  */
    for(i = 0; i < height; i++)
        for(k = 0; k < width; k++){   
            image[i].push_back( Pixel(MAX_PIX, MAX_PIX, MAX_PIX));        
        }

    /* Every blank page has the same name   */
    name = "Blank-Page.ppm";

}


PpmImage PpmImage::operator=(const PpmImage &left)
{
    setWidth( left.getWidth() );
    setHeight( left.getHeight() );

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


PpmImage& PpmImage::convertGrayscale(float c_r, float c_b, float c_g){

    /* check the given coefficient values are between 0-1 */
    bool valid = ( ( c_r <= 1 && c_r >= 0) || ( c_b <= 1 && c_b >= 0) 
                    ||( c_g <= 1 && c_g >= 0) );
    
    if( !valid ){
        std::cerr << "Invalid coefficient for converting to grayscale.\n";
        exit(EXIT_FAILURE);
    }
    
    /* calls the convertGrayscale function of the Pixel class   */
    for(int i = 0; i < image.size(); i++){
        for(int k = 0; k < image[i].size(); k++){
        	image[i][k].convertGrayscale(c_r, c_b, c_g);
        }
    
    }

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
    fout << max << "\n";

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
    out << MAX_PIX << "\n";

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

#pragma region ImageEditor Class

class ImageEditor{

    public:
        ImageEditor();  /* no parameter constructor */
        /* image manipulation functions */
        int imageExists(const std::string name) const;
        void addImage(const PpmImage& newImage);
        bool deleteImage(const std::string name);
        bool deleteImage(PpmImage image);
        bool convertGrayscale(const std::string name);
        /* all  menu related functions   */
        void startMenu();   
        void subMenu(int subMenu);
        void openImageMenu();
        void saveImageMenu();
        void scriptsMenu();
        void convertGrayMenu();
        int getChoice() const;
        std::string getStringInput() const;
        int getSize() const;

    private:    
        PpmImage image;  /* for now, the image editor can only hold single image at a time*/
        int size = 0;    /* number of images present in the editor    */

        friend std::ostream& operator<<( std::ostream& out, ImageEditor& editor);  

};

#pragma endregion

#pragma region ImageEditor

int ImageEditor::getSize() const
{   return size;    }

ImageEditor::ImageEditor() : size(0)
{   
    startMenu();    
}


void ImageEditor::addImage(const PpmImage &newImage)
{

    if( size >= 1 ){    // if the editor is full
        std::cout << "Image editor memory is full!\n";
        std::cout << "Can not add more images.\n";
        exit(EXIT_FAILURE);
    }

    size++;
    image = newImage;
    
}

bool ImageEditor::deleteImage(const string name)
{   
    if(size == 0){
        std::cout << "Image does not exists.\n";
        return false;
    }

    size--;

    return true;
}

int ImageEditor::imageExists(const string name) const
{ 
    if(size == 1)
        return 1;

    return 0;

}


bool ImageEditor::deleteImage(PpmImage image)
{

    int size = imageExists( image.getName() );
    
    if(size == 0 ){
        std::cout << "The image already does not exist.\n";
        return false;
    }

    /* erasing the image   */
    size--;

    return true;
}


bool ImageEditor::convertGrayscale(const string name)
{
    int index = imageExists( name );
    float c_r, c_b, c_g;
    
    if( index == 0 ){
        std::cerr << "The image does not exist. Nothing to convert.\n";
        return false;
    }

    //std::cout << "Enter The Coefficients One By One (0-1).\n";
    std::cin >> c_r >> c_b >> c_g;

    /* Hand things off to PpmImage class function with
        the same name   */
    image.convertGrayscale(c_r, c_b, c_g);
    
    return true;
}

void ImageEditor::startMenu(){

    int choice = -1;
    string line;

    do{
        std::cout << "MAIN MENU\n";
        std::cout << "0 - Exit\n";
        std::cout << "1 - Open an Image (D)\n";
        std::cout << "2 - Save Image Data (D)\n";
        std::cout << "3 - Scripts (D)\n";        
       
        try {
            choice = getChoice();

            if( choice > 3 || choice < 0 ){
                std::cout <<"Please enter a number betweeen 0-3.\n";
                continue;
            }
            if( choice == 1 || choice == 2 || choice == 3)
                subMenu(choice);

            if (choice == 0) // Exit the loop if choice is 0
                break;

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

    } while( choice != 0); // Always true, loop terminates only when choice is 0

}



void ImageEditor::subMenu(int subMenu){

    switch (subMenu)
    {
        case 1:
            openImageMenu();
            break;

        case 2:
            saveImageMenu();
            break;

        case 3:
            scriptsMenu();
            break;

        default:
            std::cerr << "Invalid choice.\n";
            break;
    }

}

void ImageEditor::openImageMenu()
{

    int ch;
    string buffer;

    while (true) {
        std::cout << "OPEN AN IMAGE MENU\n";
        std::cout << "0 - UP\n";
        std::cout << "1 - Enter The Name Of The Image File\n";

        ch = getChoice();

        if (ch < 0 || ch > 1) {
            std::cout << "Invalid choice (0-1).\n";
        } 
        else if (ch == 0) {
            break;
        } 
        else {
            try {
                //std::cout << "Enter Name: ";
                buffer = getStringInput();

                PpmImage newImage(buffer);
                addImage(newImage);
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }

        }
    }

}

void ImageEditor::saveImageMenu() 
{
    int ch;

    do {
        std::cout << "SAVE IMAGE DATA MENU\n";
        std::cout << "0 - UP\n";
        std::cout << "1 - Enter A File Name\n";  

        try {
            ch = getChoice();

            if (ch < 0 || ch > 1) {
                std::cout << "Invalid choice (0-1). Try again.\n";
                continue; // Go back to the beginning of the loop
            }

            if (ch) {
                try {
                    //std::cout << "Enter Name: ";
                    string name = getStringInput();
                    int index = imageExists(name);

                    if (index == 0) {
                        std::cout << "This image does not exist.\n";
                        std::cin.clear();
                        std::cin.ignore(MAX_WSPACE, '\n');
                        continue; // Go back to the beginning of the loop
                    }

                    image.writePpmImage(name);
                        

                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }

            }

        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

    } while (ch != 0);

}


void ImageEditor::scriptsMenu() 
{
    while (true) {
        std::cout << "SCRIPTS MENU\n";
        std::cout << "0 - UP\n";
        std::cout << "1 - Convert To Grayscale (D)\n";  

    try {
        int ch = getChoice();

        if (ch < 0 || ch > 1) {
            std::cout << "Invalid choice (0-1).\n";
            continue; // Continue to next iteration of the loop
        }

        if (ch == 1) {
            convertGrayMenu();
        } else {
            break; // Exit loop
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    }

}

void ImageEditor::convertGrayMenu()
{
    int ch;
    float coef_r, coef_b, coef_g;
    string name;

    while (true) {
        std::cout << "CONVERT TO GRAYSCALE MENU\n";
        std::cout << "0 - UP\n";
        std::cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels.\n";

        try {
            int ch = getChoice();

            if (ch < 0 || ch > 1) {
                std::cout << "Invalid choice (0-1).\n";
                continue;
            }

            if (ch == 0) 
                break;

            //std::cout << "Please First Enter The Name Of The Image.\n";
            //std::cin >> name;

            if (!convertGrayscale(name)) {
                continue;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

    }

}


int ImageEditor::getChoice() const {
    
    string input;
    int num;

    //while (true) {
   // std::cout << "Enter Your Choice: ";
    //    std::getline(std::cin, input);
    if ( !(std::cin >> num)  ) 
        throw std::invalid_argument("Invalid input. Please enter an integer."); 
            
    return num;

}

std::string ImageEditor::getStringInput() const 
{    
    std::string result;

    std::getline(std::cin >> std::ws, result);  // read the entire line from the input buffer
    // ignore the leading whitespaces
    if (std::cin.fail()) {                      // check if there was an error reading from the input stream
        std::cin.clear();                       // clear the error flags
        std::cin.ignore(MAX_WSPACE, '\n');      // discard the rest of the line
        throw std::runtime_error("Input error. Please try again.");  // throw an exception
    }

    return result;
}


std::ostream &operator<<(std::ostream &out, ImageEditor &editor)
{
    out << "Printing all the images inside the editor.\n";
    out << "Current number of images present: "<< editor.getSize(); 
    out << "\n";

    out << editor.image << "\n"; 

    return out;

}

#pragma endregion


int main(){

    ImageEditor myEditor;   /*instantiate the image editor */
    
    //std::cout << myEditor;
}


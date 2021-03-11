#include <iostream>
#include <string>


std::string translate( std::string line, std::string argument )
{ 
  std::string result = ""; // implementeer dit
  
  if(argument == "caesar3"){
    for(unsigned int i = 0; i < line.size(); i++){
      if (isupper(line[i])){ 
        result += char(int(line[i]+3-65)%26 +65); 
      }
      else{
        result += char(int(line[i]+3-97)%26 +97); 
      } 
    }
  }
  if(argument == "caesar6"){
    for(unsigned int i = 0; i < line.size(); i++){
      if (isupper(line[i])){ 
        result += char(int(line[i]+6-65)%26 +65); 
      }
      else{
        result += char(int(line[i]+6-97)%26 +97); 
      } 
    }
  }
  if(argument == "caesar9"){
    for(unsigned int i = 0; i < line.size(); i++){
      if (isupper(line[i])){ 
        result += char(int(line[i]+9-65)%26 +65); 
      }
      else{
        result += char(int(line[i]+9-97)%26 +97); 
      } 
    }
  }
    


  // ls || caesar 5 || less 
  // line || caesar 5 || result
  return result; 
  }


int main(int argc, char *argv[]){
{ 
  std::string line;

  if(argc != 2)
  { std::cerr << "Deze functie heeft exact 1 argument nodig" << std::endl;
    return -1; }

  while(std::getline(std::cin, line))
  { std::cout << translate(line, argv[1]) << std::endl; } 

  return 0; }
}
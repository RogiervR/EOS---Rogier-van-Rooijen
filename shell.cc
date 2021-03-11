#include "shell.hh"

int main()
{ std::string input;
  std::string prompt; 
    // fd = File Descriptor
  int fd = syscall(SYS_open, "prompt.txt", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1)){                  // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    prompt.append(byte); 
    }   


  while(true)
  { std::cout << prompt;                   // Print het prompt
    std::getline(std::cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "seek") seek();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (std::cin.eof()) return 0; } }      // EOF is een exit

void new_file() 
{ 
    std::string bestandsnaam = "";
    std::string invoertekst = "";
    std::cout << "Geef de bestandsnaam: " << std::endl;
    std::getline(std::cin, bestandsnaam);
    const char* bestand[] = {bestandsnaam.c_str()};
    int fd = syscall(SYS_creat, bestand[0] , 0755);
    std::cout << "Geef je tekst voor in het bestand en sluit de tekst af met EOF: " << std::endl;
    std::string file_tekst = "";
    while(std::getline(std::cin,invoertekst)){
        if(invoertekst == "<EOF>"){
            break;
        }
        file_tekst += invoertekst + "\n";
    }
    const char* file[] = {file_tekst.c_str()};
    syscall(SYS_write , fd , file[0] , file_tekst.size());
    
}

void list() 
{ 
    if(syscall(SYS_fork) == 0){
        const char* flags[] = {"/bin/ls" , "-l" , "-a" , NULL};
        syscall(SYS_execve , flags[0] , flags , NULL);
    }
    else{
        syscall(SYS_wait4 , 0 , NULL , NULL , NULL);
    }
}

void find() 
{ 
    std::cout << "Geef argument voor find:  " << std::endl;
    std::string input_find = "";
    std::getline(std::cin, input_find);
    int fd[2];
    syscall(SYS_pipe, &fd);
    if(syscall(SYS_fork) == 0){
        syscall(SYS_close, fd[0]);
        syscall(SYS_dup2, fd[1], 1);
        const char* flags[] = {"/usr/bin/find" , "." , NULL};
        syscall(SYS_execve , flags[0] , flags , NULL);
    }
    else{
        syscall(SYS_wait4 , 0 , NULL , NULL , NULL);
    }
    if(syscall(SYS_fork) == 0){
        syscall(SYS_close, fd[1]);
        syscall(SYS_dup2, fd[0], 0);
        const char* flags2[] = {"/bin/grep", input_find.c_str() , NULL};
        syscall(SYS_execve , flags2[0] , flags2 , NULL);
    }
    else{
        syscall(SYS_close, fd[0]);
        syscall(SYS_close, fd[1]);
        syscall(SYS_wait4 , 0 , NULL , NULL , NULL);
    }
}

void seek() 
{ 
    int seek = syscall(SYS_creat, "seek", 0755);
    int loop = syscall(SYS_creat, "loop", 0755);
    char byte[1] = {'x'};
    char byte2[1] = {'\0'};
    int miljoen5 = 5000000;
    syscall(SYS_write , seek , byte , 1);
    syscall(SYS_lseek , seek , miljoen5 , 1);
    syscall(SYS_write , seek , byte , 1);

    syscall(SYS_write , loop , byte , 1);
    for(int i= 0 ; i < miljoen5 ; i++ ){
        syscall(SYS_write , loop , byte2 , 1);
    }
    syscall(SYS_write , loop , byte , 1);
}





void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1)){                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
}
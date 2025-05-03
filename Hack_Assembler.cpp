#include <iostream>
using namespace std;
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include "functions.cpp"
#include <map>
#include <string.h>


int main()
{
  /* 
         IMPORTANT NOTE :: 
         count function is used to check whether value exists in a hash table

         if hash.count(value) == 1 then it means value exits in the hash table 
         if hash.count(value) == 0 then it means value doesn't exist in the hash table  
  */
    unordered_map<string, string> c_to_bin;
    c_to_bin["0"] = "0101010";
    c_to_bin["1"] = "0111111";
    c_to_bin["-1"] = "0111010";
    c_to_bin["D"] = "0001100";
    c_to_bin["A"] = "0110000";
    c_to_bin["!D"] = "0001101";
    c_to_bin["!A"] = "0110001";
    c_to_bin["-D"] = "0001111";
    c_to_bin["-A"] = "0110011";
    c_to_bin["D+1"] = "0011111";
    c_to_bin["A+1"] = "0110111";
    c_to_bin["D-1"] = "0001110";
    c_to_bin["A-1"] = "0110010";
    c_to_bin["D+A"] = "0000010";
    c_to_bin["D-A"] = "0010011";
    c_to_bin["A-D"] = "0000111";
    c_to_bin["D&A"] = "0000000";
    c_to_bin["D|A"] = "0010101";
    
    c_to_bin["M"] ="1110000";
    c_to_bin["!M"] = "1110001";
    c_to_bin["-M"] = "1110011";
    c_to_bin["M+1"] = "1110111";
    c_to_bin["M-1"] = "1110010";
    c_to_bin["D+M"] = "1000010";
    c_to_bin["D-M"] = "1010011";
    c_to_bin["M-D"] = "1000111";
    c_to_bin["D&M"] = "1000000";
    c_to_bin["D|M"] = "1010101";  
    
    unordered_map<string, string>  j_to_bin;
    j_to_bin["JGT"] = "001";
    j_to_bin["JEQ"] = "010";
    j_to_bin["JGE"] = "011";
    j_to_bin["JLT"] = "100";
    j_to_bin["JNE"] = "101";
    j_to_bin["JLE"] = "110";
    j_to_bin["JMP"] = "111"; 

    unordered_map<string, string> d_to_bin; 
    d_to_bin["M"] = "001";
    d_to_bin["D"] = "010";
    d_to_bin["MD"] = "011";
    d_to_bin["A"] = "100";
    d_to_bin["AM"] = "101";
    d_to_bin["AD"] = "110";
    d_to_bin["AMD"] = "111";

    unordered_map<string, string>  a_to_bin;  
    a_to_bin["SP"] = "0000000000000000";
    a_to_bin["LCL"] = "0000000000000001";
    a_to_bin["ARG"] = "0000000000000010";
    a_to_bin["THIS"] = "0000000000000011";
    a_to_bin["THAT"] = "0000000000000100";
    a_to_bin["SCREEN"] = "0100000000000000";
    a_to_bin["KBD"] = "0110000000000000";
    a_to_bin["R0"] = "0000000000000000";

    a_to_bin["R1"] = "0000000000000001";
    a_to_bin["R2"] = "0000000000000010";
    a_to_bin["R3"] = "0000000000000011";
    a_to_bin["R4"] = "0000000000000100";
    a_to_bin["R5"] = "0000000000000101";
    a_to_bin["R6"] = "0000000000000110";
    a_to_bin["R7"] = "0000000000000111";
    a_to_bin["R8"] = "0000000000001000";
    a_to_bin["R9"] = "0000000000001001";
    a_to_bin["R10"] = "0000000000001010";
    a_to_bin["R11"] = "0000000000001011";
    a_to_bin["R12"] = "0000000000001100";
    a_to_bin["R13"] = "0000000000001101";
    a_to_bin["R14"] = "0000000000001110";
    a_to_bin["R15"] = "0000000000001111";
    
    int comp_check = 0;
    char text;
    string line;
    ifstream outfile;
    ofstream write;
    string num = "";
    
    unordered_map<string, string> var; // the variable hashes 

    unordered_map<string, string> labels; // the labels hashes
    
    int st_value = 16; // this is the starting value of a variable
                       // which is 16, 
                       // it is incremented by one each time another variable is made   
    
    outfile.open("C:/Users/ABDULLAH/Desktop/Rectangle2.asm", ios::in); // this is path of input file
    write.open("C:/Users/ABDULLAH/Desktop/Rectangle2.hack", ios::out); // this is path of output file 
    int line_num = 0;
    string dest = "";
    string comp = "";
    string jmp = "";
    int index = 0;
    bool has_eq = false;
    bool has_sem = false; // tells us if semi colon is reached 
    bool is_A = false; // tells us if a given instruction is an A instruction
    int ac_line_num = 1; // this is line count, it starts from 1 as Notepad starts counting from 1 onwards 
    int empty_check = 0; // this check is for checking whether a line is empty 
    bool is_commented = false; // tells us if rest of the line is commented or not
    bool has_brack = false; // true if line contains '('
    int max_count = 0;
    int check = 0;
    
    bool should_ignore = false; // tells us whether we should ignore rest of line
    string label_name = "";
     while(!outfile.eof())
     {
       getline(outfile, line);
      for (index = 0; index < line.size(); index++)
      {
        if (line[index] == ' ')
        {
            empty_check++;
        }
        
        if (line[index] == '/') // check comments validity if there is a '/' in line
        { 
            
          if (is_comment_valid(line, index))
              { 
                index = line.size() + 1;
                is_commented = true;
              }   

          else 
              { 
                  index = line.size() + 1;
                  should_ignore = true;
              }
                // break inner loop here 
        } 
        
        else if (line[index] == '(')
        {
             has_brack = true;
             label_name = isolate_label(line, index);// name of label saved
             labels[label_name] = to_string(line_num + 1); 
             index = line.size() + 1; // breaks inner loop
             should_ignore = true;
        }

        else
        { 
         if (line[index] == '=')
            { 
             has_eq = true;
            } // when has_eq set to true, it means there is a destination

         else if (line[index] == ';')
           {
            has_sem = true;
           } 

         else if (line[index] == '@')
          {
            check = 0;
            is_A = true;
            index++;
            for ( ; index < line.size(); index++)
            {
                if(line[index] == '/')
                {
                  if (is_comment_valid(line, index))
                      { 
                        index = line.size() + 1;
                        is_commented = true;
                      }   

                   else 
                       { 
                        index = line.size() + 1; 
                        should_ignore = true;
                       }    
                }
                
                else if (line[index] != ' ')
                { 
                  num = num + line[index];
                }
            }
        
           if (labels.count(num) == 0 && !is_number(num) && a_to_bin.count(num) == 0) // check if num is not a label  
           {                                                                          // and not a number and not a predefined symbol 
            var[num] = to_string(st_value);                                           // then it surely is a variable
            st_value++;
           } 
           
           if (labels.count(num) == 1 && var.count(num) == 1)
             {var.erase(num);} // makes sure a variable isn't counted as a label


           index = line.size() + 1; // breaks loop, once A instruction is encountered

          }    

         else if (has_sem && line[index] != ' ')
          {   
              if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                       index = line.size() + 1;
                       is_commented = true;
                     }

                else 
                    {
                       index = line.size() + 1;
                       should_ignore = true;

                    }    
              }

              else
              {
                  jmp = jmp + line[index]; // jmp has higher priority over dest
              }
          }
           
         else if (has_eq && line[index] != ' ') 
          {  
              if (comp_check == 0)
              {
                comp = "";
                comp_check++;
              }

              // what if there is no destination and no jump but there is a computation
             if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                        index = line.size() + 1;
                        is_commented = true;
                     }

                else 
                    {
                       index = line.size() + 1;
                       should_ignore = true;

                    }    // if comment isn't valid then break loop 
              }

             else 
              {
                comp = comp + line[index];
              }
          }

          else if (!has_eq && line[index] != ' ')
          {
             if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                        index = line.size() + 1; // break inner loop
                        is_commented = true;
                     }

                else 
                    {
                       index = line.size() + 1; // break inner loop
                       should_ignore = true;
                    }         
              }  

            else
            {
               dest = dest + line[index];
            }  
          }  
       
        
        }

         
      }   // inner for loop terminated here
      
      if (empty_check == line.size())
      {
        should_ignore = true; 
      } 

     if (!should_ignore)
     { 
      
      if (empty_check == line.size())
          {
            should_ignore = true;
          }    
      if (!has_eq && !has_sem) // sets destination to empty if there was no equal sign and no semicolon in line
          { comp = dest; }
        // assigns dest to comp if no dest and no jump exists

        if (!has_eq && has_sem)
        { comp = dest; } // assigns dest to comp if no destination exists
 
        if (!has_eq)
        {  comp = dest; }
       
        if (!has_eq) // sets destination to empty if there was no equal sign in line
        { dest = ""; }
        
        
        if (!has_sem) // sets jump to empty if there was no semicolon in line
        { jmp = ""; }
       
        // what if there is no destination and no jump but there is a computation
         
        if (is_A)
        {   
            if (a_to_bin.count(num) == 1) // if num is a predefined symbol
            {  line_num++; }
            
            else if (labels.count(num) == 1) // if num is a label
            {  line_num++; }
               
            else if (var.count(num) == 1 && labels.count(num) == 0) // if num is a variable
            { line_num++; }
            
            else if (is_number(num))
            { line_num++; }
            
        } 
        
        else if(!is_A && c_to_bin.count(comp) == 1 && !has_brack)
        {
        

         if(has_eq && has_sem) // if both dest and jump exist, check if their opcodes are valid
         {
           if (d_to_bin.count(dest) == 1 && j_to_bin.count(jmp) == 1) 
               { line_num++; }  
         } 

         else if(!has_eq && has_sem) // if only jump exists, check if its opcodes are valid
         {
           if (j_to_bin.count(jmp) == 1)  
               { line_num++; }     
         }
                                                            
         else if(has_eq && !has_sem) // if only dest exists, check if its opcodes are valid
         { 
            if (d_to_bin.count(dest) == 1)
                { line_num++; }      
         }    
           
         else if(!has_eq && !has_sem) // if both dest and jump don't exist, only computation exists
         { line_num++; }  
          
        }    
     }     
       has_brack = false;
       has_sem = false;
       is_A = false;
       has_eq = false;
       index = 0;
       dest = "";               
       comp = "";
       jmp = "";
       num = "";
       comp_check = 0;
       is_commented = false;
       empty_check = 0;
       max_count = 0;
       ac_line_num++; 
       should_ignore = false;
     }
    
    st_value = 16;
    index = 0;
    outfile.close();
    outfile.open("C:/Users/ABDULLAH/Desktop/Rectangle2.asm", ios::in); // this is path of input file
    outfile.seekg(0); // set file pointer back to start
    ac_line_num = 1;


     for (;!outfile.eof();)
     {  
        getline(outfile, line); 
       for(; index < line.size() ; index++)
       { 

         if (line[index] == ' ')
        {
            empty_check++;
        }  
         
        if (line[index] == '/') // check comments validity if there is a '/' in line
        { 
            
          if (is_comment_valid(line, index))
              { 
                index = line.size() + 1;
                is_commented = true;
              }   

          else 
              { 
                write << "Illegal comment at line number  " << ac_line_num << '\n';
                index = line.size() + 1;
                should_ignore = true;
              } // break inner loop here 
        } 

        else if (line[index] == '(')
         {   
             should_ignore = true;
             has_brack = true;
             index = line.size() + 1; // breaks inner loop
            
         }

        else
        { 
         if (line[index] == '=')
            { 
             has_eq = true;
            } // when has_eq set to true, it means there is a destination

         else if (line[index] == ';')
           {
            has_sem = true;
           } 

         else if (line[index] == '@')
          {
            check = 0;
            is_A = true;
            index++;
            for ( ; index < line.size(); index++)
            {
                if(line[index] == '/')
                {
                  if (is_comment_valid(line, index))
                      { 
                        index = line.size() + 1;
                        is_commented = true;
                      }   

                   else 
                      { 
                        write << "Illegal comment at line number  " << ac_line_num << '\n';
                        index = line.size() + 1;
                        should_ignore = true;
                      }    
                }
                
                else if (line[index] != ' ')
                { 
                  num = num + line[index];
                }
            }
                 
                                                                    
           if (labels.count(num) == 0 && !is_number(num) && a_to_bin.count(num) == 0) // check if num is not a label  
           {                                                                          // and not a number and not a predefined symbol 
            var[num] = to_string(st_value);                                           // then it surely is a variable
            st_value++;
           } 
           
           if (labels.count(num) == 1 && var.count(num) == 1)
             {var.erase(num);} // makes sure a variable isn't counted as a label

           index = line.size() + 1; // breaks loop, once A instruction is encountered

          }    

         else if (has_sem && line[index] != ' ')
          {   
              if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                       index = line.size() + 1;
                       is_commented = true;
                     }

                else 
                     { 
                       write << "Illegal comment at line number  " << ac_line_num << '\n';
                       index = line.size() + 1;
                       should_ignore = true;
                    }    
              }

              else
              {
                  jmp = jmp + line[index]; // jmp has higher priority over dest
              }
          }
           
         else if (has_eq && line[index] != ' ') 
          {  
              if (comp_check == 0)
              {
                comp = "";
                comp_check++;
              }

              // what if there is no destination and no jump but there is a computation
             if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                        index = line.size() + 1;
                        is_commented = true;
                     }

                else 
                     { 
                        write << "Illegal comment at line number  " << ac_line_num << '\n';
                        index = line.size() + 1;
                        should_ignore = true;
                     }    
              }

             else 
              {
                comp = comp + line[index];
              }
          }

          else if (!has_eq && line[index] != ' ')
          {
             if (line[index] == '/')
              {
                if (is_comment_valid(line, index))
                     { 
                        index = line.size() + 1;
                        is_commented = true;
                     }

                else 
                     { 
                       write << "Illegal comment at line number  " << ac_line_num << '\n';
                       should_ignore = true;
                     }    
              }  

            else
            {
               dest = dest + line[index];
            }  
          }  
        // add empty line check   
        
        }


       } // inner for loop terminated here 

     
        if (!has_eq && !has_sem) // sets destination to empty if there was no equal sign and no semicolon in line
        {   
            comp = dest; // assigns dest to comp if no dest and no jump exists
        }

        if (!has_eq && has_sem)
        {
            comp = dest; // assigns dest to comp if no destination exists
        }
        
        if (!has_eq)
        {
            comp = dest;
        }
        if (!has_eq) // sets destination to empty if there was no equal sign in line
        {
            dest = "";
        }
        
        if (!has_sem) // sets jump to empty if there was no semicolon in line
        {
            jmp = "";
        }
        // what if there is no destination and no jump but there is a computation
         
        if (is_A)
        {   
            if (a_to_bin.count(num) == 1) // if num is a predefined symbol
            {

               write << "Line Number " << ac_line_num << " binary code : ";
               write << a_to_bin[num];
               write << '\n';

            } 
            
            else if (labels.count(num) == 1) // if num is a label
            { 
              write << "Line Number " << ac_line_num << " binary code : ";
              dec_to_bin2(labels[num], write);
              write << '\n';
            }    
            else if (var.count(num) == 1 && labels.count(num) == 0) // if num is a variable
            {
              write << "Line Number " << ac_line_num << " binary code : ";
              dec_to_bin2(var[num], write);
              write << '\n';
            }
            
            else if (is_number(num)) // if num is a number check if overflow occurs
            {
             if (!does_overflow_occur(num))
             { 
              write << "Line Number " << ac_line_num << " binary code : ";
              dec_to_bin2(num, write);
              write << '\n';
             } 
             else 
             {
              write << "Overflow occurred at line number " << ac_line_num;
             }
            }

            else if (!is_number(num))
            {
             write << "Illegal A instruction at  " << ac_line_num << '\n';
            }
          
        } 
        
        else if(!is_A && c_to_bin.count(comp) == 1 && !has_brack)
        {
        

         if(has_eq && has_sem) // if both dest and jump exist, check if their opcodes are valid
         {
           if (d_to_bin.count(dest) == 1 && j_to_bin.count(jmp) == 1) 
               {
                write << "Line Number " << ac_line_num << " binary code : ";
                write << "111" << c_to_bin[comp] << d_to_bin[dest] << j_to_bin[jmp] << '\n';
               }

            else if (d_to_bin.count(dest) == 1 && j_to_bin.count(jmp) == 0)
               {
                 write << "Jump error at line number  " << ac_line_num << '\n';
               }   

            else if (d_to_bin.count(dest) == 0 && j_to_bin.count(jmp) == 1)
               {
                 write << "Destination  error at line number  " << ac_line_num << '\n';
               }  

            else
               { 
                write << "Illegal jump and destination at line number  " << ac_line_num << '\n';
               }
                
         } 

         else if(!has_eq && has_sem) // if only jump exists, check if its opcodes are valid
         {
           if (j_to_bin.count(jmp) == 1)  
               {
              
               write << "Line Number " << ac_line_num << " binary code : ";
               write << "111" << c_to_bin[comp] << "000" << j_to_bin[jmp] << '\n';
               }
            
            else if(j_to_bin.count(jmp) == 0) 
               {
               
                write << "Jump error at line number  " << ac_line_num << '\n';
               }
         }
         
                                                            
         else if(has_eq && !has_sem) // if only dest exists, check if its opcodes are valid
         { 
            if (d_to_bin.count(dest) == 1)
                {
                
                 write << "Line Number " << ac_line_num << " binary code : ";
                 write << "111" << c_to_bin[comp] << d_to_bin[dest] << "000" << '\n';
                }

            else if (d_to_bin.count(dest) == 0)
                {
                 
                 write << "Destination  error at line number  " << ac_line_num << '\n';
                }        
         }    
           
         else if(!has_eq && !has_sem) // if both dest and jump don't exist, check if its opcodes are valid
         {
          
           write << "Line Number " << ac_line_num << " binary code : ";
           write << "111" << c_to_bin[comp] << "000000" << '\n';
         }  
          
        }  

        else if (c_to_bin.count(comp) == 0 && !is_commented && !is_line_empty(line) && !has_brack)
        {
         
          write << "Computation  error at line number  " << ac_line_num << '\n';
        }            

        else if (is_line_empty(line))
        {
        
         write << "Line number " << ac_line_num << " ignored due to being an empty line \n";
        }  
           
                              
                     
       
       has_brack = false;
       has_sem = false;
       is_A = false;
       has_eq = false;
       index = 0;
       dest = "";               
       comp = "";
       jmp = "";
       num = "";
       ac_line_num++;
       comp_check = 0;
       is_commented = false;
       empty_check = 0;
       max_count = 0;
       
    }   

    return 0;
}
#include <iostream> 
#include <fstream> 

int main()
{
    std::ofstream ff; 
    ff.open("tst.txt"); 
    for (int i = 0; i < 5; ++i )
    {
        ff << "hello" << '\n'; 
    }
    

    ff.close();

    return 0; 
}
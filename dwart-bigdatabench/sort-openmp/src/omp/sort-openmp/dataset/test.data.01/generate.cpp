#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
   ofstream ffd;
   ffd.open("ha.txt");
   for(int i=0;i<1000000;i++)
   {
	ffd<<rand()<<endl;
   }
}

#include "stdio.h"
#include <boost/shared_ptr.hpp>
int main()
{
	boost::shared_ptr<int> testvariable(new int);
	*testvariable = 1;
	printf("Hello world! %d\n",*testvariable);
}

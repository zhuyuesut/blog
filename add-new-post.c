#include <stdio.h>
#include <string.h>
#include <time.h>

#define CCT (+8)

int main() {


	// get name
	//
	char name[100];
	
	printf("new blog filename:");
	fgets(name, sizeof name, stdin);
	*strchr(name, '\n') = '\0';


	// get date as yyyy-mm-dd
	//
	char date[11];

	time_t rt;
	struct tm *i;
	time(&rt);
	i = gmtime(&rt);
	sprintf(date, "%d-%02d-%02d", i->tm_year+1900, i->tm_mon+1, i->tm_mday);


	// get filename with date
	
	char filename[130];
	sprintf(filename, "_posts/%s-%s.md", date, name);


	// add new post file

	FILE * file = fopen(filename, "w+");

	if(file == NULL) {
		perror("fopen:");
		return(-1);
	}
	fputs("---\n\nlayout: post\ntitle: \"\"\nauthor: Zhu Yue\n\n---\n", file);
	
	fclose(file);


	// the end
	//
	printf("new post file: %s\n", filename);
	
	return(0);
}



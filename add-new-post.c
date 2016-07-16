#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main() {


	// get name
	//
	char name[100];
	
	printf("new blog filename:");
	fgets(name, sizeof name, stdin);
	char *found = strchr(name, '\n');
	if (found != NULL) {
		*found = '\0';
	}


	// get date as yyyy-mm-dd
	//
	char date[11];

	time_t rt;
	struct tm *st;
	time(&rt);
	st = gmtime(&rt);
	sprintf(date, "%d-%02d-%02d", (st->tm_year+1900) % 1e4, st->tm_mon+1, st->tm_mday);


	// get filename with date
	//
	const char *format = "_posts/%s-%s.md";
	char filename[sizeof format + sizeof date + sizeof name];
	sprintf(filename, format, date, name);


	// add new post file
	//
	FILE * file = fopen(filename, "w");

	if (file == NULL) {
		perror("fopen: ");
		return EXIT_FAILRUE;
	}
	fputs("---\n\nlayout: post\ntitle: \"\"\nauthor: Zhu Yue\n\n---\n", file);
	
	fclose(file);


	// the end
	//
	printf("new post file: %s\n", filename);
	
	return EXIT_SUCCESS;
}



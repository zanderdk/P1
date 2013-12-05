#include <stdio.h>
#include <sqlite3.h>
#include "graph.h"

void addPath(Vertex *v1, Vertex *v2, Vertex *list, int wght){
  int rc; //Variable for return code

  sqlite3 *db; // Create a handle for database connection, create a pointer to sqlite3
    
  rc = sqlite3_open("paths.sqlite3",&db); // If connection failed, handle returns NULL
  if(rc!=SQLITE_OK){
    printf("Can't open database");
    sqlite3_close(db);
    return 1;
  }

  printf("Connection successful\n");
    
  // Create the SQL query for creating a table
  char *query = "CREATE TABLE IF NOT EXISTS paths (source TEXT PRIMARY KEY, destination TEXT NOT NULL, Vertices TEXT NOT NULL, weight INTEGER)";
    
  // Execute the query for creating the table
  rc = sqlite3_exec(db,query,0,0,0);
  if(rc!=SQLITE_OK){
    printf("Error creating database");
  }

  char *zSQL = sqlite3_mprintf("INSERT INTO paths VALUES(%Q,%Q,%Q)", "1", "2", "3");
	rc = sqlite3_exec(db, zSQL, 0, 0, 0);
	sqlite3_free(zSQL);

	if(rc!=SQLITE_OK){
    printf("SQL error");
  }else{
  	printf("SQL OK");
  }

  sqlite3_close(db);
}

Path getPath(Vertex *v1, Vertex *v2){

}


int main(int argc, char const *argv[]) {

	addPath(*v1, *v2, *list, wght);

	getPath(*v1, *v2);

	return 0;
}
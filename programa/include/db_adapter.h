#ifndef DB_ADAPTER_H
#define DB_ADAPTER_H

#include <stdio.h>

// Initialization
int db_init(const char *db_path);

// Check login credentials
int db_login(const char *user, const char *pass);

// Setup initial tables
void db_setup_tables();

// Execute raw SQL (Helper)
void db_exec(const char *sql);

#endif

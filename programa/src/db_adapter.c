#include "../include/db_adapter.h"
#include "../lib/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sqlite3 *db;

int db_init(const char *db_path) {
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        // fprintf(stderr, "Opened database successfully\n");
        db_setup_tables();
        return 1;
    }
}

void db_exec(const char *sql) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void db_setup_tables() {
    // Users Table
    const char *sql_users = 
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "role TEXT DEFAULT 'admin');";

    // Families Table
    const char *sql_families = 
        "CREATE TABLE IF NOT EXISTS familias ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "descripcion TEXT UNIQUE NOT NULL);";

    // Products Table
    const char *sql_products = 
        "CREATE TABLE IF NOT EXISTS productos ("
        "id TEXT PRIMARY KEY,"
        "nombre TEXT NOT NULL,"
        "familia_id INTEGER,"
        "costo REAL,"
        "precio REAL,"
        "stock INTEGER,"
        "FOREIGN KEY(familia_id) REFERENCES familias(id));";

    // Invoices (Facturas) Table - Renamed to 'facturas' to match requirements
    const char *sql_invoices = 
        "CREATE TABLE IF NOT EXISTS facturas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "fecha DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "cliente TEXT,"
        "subtotal REAL,"
        "impuesto REAL,"
        "total REAL,"
        "estado TEXT DEFAULT 'PENDIENTE');"; // PENDIENTE or FACTURADO

    // Invoice Details
    const char *sql_invoice_items = 
        "CREATE TABLE IF NOT EXISTS detalle_facturas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "factura_id INTEGER,"
        "producto_id TEXT,"
        "cantidad INTEGER,"
        "precio_unitario REAL,"
        "subtotal REAL,"
        "FOREIGN KEY(factura_id) REFERENCES facturas(id));";

    db_exec(sql_users);
    db_exec(sql_families);
    db_exec(sql_products);
    db_exec(sql_invoices);
    db_exec(sql_invoice_items);

    // Seed default admin if not exists
    // Simple check via INSERT OR IGNORE
    db_exec("INSERT OR IGNORE INTO usuarios (username, password) VALUES ('admin', 'admin123');");
}

int db_login(const char *user, const char *pass) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id FROM usuarios WHERE username = ? AND password = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    int valid = 0;
    if (step == SQLITE_ROW) {
        valid = 1;
    }

    sqlite3_finalize(stmt);
    return valid;
}

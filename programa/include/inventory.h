#ifndef INVENTORY_H
#define INVENTORY_H

// Registers a new product family. Returns 1 on success, 0 on error/duplicate.
int inv_register_family(const char *description);

// Registers a new product. Returns 1 on success.
int inv_register_product(const char *id, const char *name, int family_id, double cost, double price, int stock);

// Loads inventory updates from a file. Returns number of lines processed.
int inv_load_inventory(const char *filepath);

// Lists all products (Catalog).
void inv_show_catalog();

int inv_load_families_batch(const char *filepath);
int inv_load_products_batch(const char *filepath);
int inv_delete_product(const char *id);

#endif

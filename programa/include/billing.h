#ifndef BILLING_H
#define BILLING_H

// Creates a new quote/invoice record. Returns ID.
int bill_create_quote(const char *client);

// Adds item to quote. Returns 1 on success, 0 on insufficient stock/error.
int bill_add_item(int quote_id, const char *product_id, int quantity);

// Finalizes a quote into an invoice (deducts stock). Returns 1 on success.
int bill_process_invoice(int quote_id, const char *payment_method);

// Shows specific invoice details.
void bill_show_invoice(int invoice_id);

int bill_remove_item(int quote_id, const char *product_id);
void bill_get_stats();

#endif

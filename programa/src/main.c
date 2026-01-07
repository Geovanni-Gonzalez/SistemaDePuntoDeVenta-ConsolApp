#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db_adapter.h"
#include "../include/inventory.h"
#include "../include/billing.h"
#include "../include/ui.h"

void admin_menu();
void general_menu();

int main() {
    ui_init(); // Fix UTF-8 for Windows
    ui_clear();
    
    // Banner intro
    printf("%s\n", BANNER);
    printf("Iniciando Sistema...\n");
    
    if (!db_init("sistema.db")) {
        if (!db_init("../db/sistema.db")) {
             ui_print_error("Error iniciando Base de Datos.");
             return 1;
        }
    }

    while(1) {
        ui_header("MENÚ PRINCIPAL");
        printf(C_CYAN "  [1]" C_RESET " Opciones Administrativas\n");
        printf(C_CYAN "  [2]" C_RESET " Opciones Generales\n");
        printf(C_RED  "  [3]" C_RESET " Salir\n");
        printf("\n");
        
        int opt = ui_input_int("Seleccione una opción: ");
        
        switch(opt) {
            case 1:
                {
                    char u[50], p[50];
                    ui_header("ACCESO ADMINISTRATIVO");
                    ui_input_str("Usuario: ", u);
                    ui_input_str("Clave: ", p);
                    
                    if (db_login(u, p)) {
                        ui_print_success("Acceso Concedido.");
                        ui_pause();
                        admin_menu();
                    } else {
                        ui_print_error("Credenciales inválidas.");
                        ui_pause();
                    }
                }
                break;
            case 2:
                general_menu();
                break;
            case 3:
                printf("Saliendo...\n");
                return 0;
            default:
                ui_print_error("Opción inválida.");
                ui_pause();
        }
    }
    return 0;
}

void admin_menu() {
    while(1) {
        ui_header("MENÚ ADMINISTRATIVO");
        printf(C_CYAN "  [1]" C_RESET " Registro de Familias\n");
        printf(C_CYAN "  [2]" C_RESET " Registro de Productos\n");
        printf(C_CYAN "  [3]" C_RESET " Cargar Inventario (Batch)\n");
        printf(C_CYAN "  [4]" C_RESET " Consultar Facturas\n");
        printf(C_CYAN "  [5]" C_RESET " Estadísticas\n");
        printf(C_RED  "  [6]" C_RESET " Volver\n");
        printf("\n");
        
        int op = ui_input_int("Opción: ");
        
        if (op == 6) break;
        
        if (op == 1) {
            char desc[100];
            ui_input_str("Descripción Familia: ", desc);
            // Check if batch or single? Single for now as per prompt flow "Registro de familias"
            // Wait, requirement says "incluir en lote". 
            // Let's ask user? "Manual or File?"
            int type = ui_input_int("1. Manual, 2. Desde Archivo (FamID,Desc): ");
            if (type == 1) {
                 if(inv_register_family(desc)) ui_print_success("Familia registrada.");
                 else ui_print_error("Error registrando familia.");
            } else {
                 char fpath[100];
                 ui_input_str("Ruta archivo: ", fpath);
                 int n = inv_load_families_batch(fpath);
                 if (n>=0) { char m[50]; sprintf(m,"Procesados: %d", n); ui_print_success(m); }
            }
            ui_pause();
        }
        else if (op == 2) {
             ui_header("GESTIÓN DE PRODUCTOS");
             printf("1. Agregar (Manual)\n2. Agregar (Lote)\n3. Eliminar\n");
             int sub = ui_input_int("Opción: ");
             
             if (sub == 1) {
                char id[20], nom[100];
                ui_input_str("ID: ", id);
                ui_input_str("Nombre: ", nom);
                int fam = ui_input_int("ID Familia: ");
                double cost = ui_input_double("Costo: ");
                double pre = ui_input_double("Precio: ");
                int stk = ui_input_int("Stock Inicial: ");
                if(inv_register_product(id, nom, fam, cost, pre, stk)) ui_print_success("Producto registrado.");
                else ui_print_error("Error.");
             } else if (sub == 2) {
                char f[100];
                ui_input_str("Ruta (ID,Nombre,Fam,Cost,Prec,Stk): ", f);
                int n = inv_load_products_batch(f);
                char m[50]; sprintf(m,"Procesados: %d", n); ui_print_success(m);
             } else if (sub == 3) {
                char id[20];
                ui_input_str("ID Producto a Eliminar: ", id);
                if(inv_delete_product(id)) ui_print_success("Eliminado.");
                else ui_print_error("No se pudo eliminar (Puede tener ventas asociadas).");
             }
             ui_pause();
        }
        else if (op == 3) {
            char path[100];
            ui_input_str("Ruta archivo (ID,CANT): ", path);
            int n = inv_load_inventory(path);
            if (n >= 0) {
                 char msg[50];
                 sprintf(msg, "Procesados: %d", n);
                 ui_print_success(msg);
            } else {
                 ui_print_error("No se pudo abrir el archivo.");
            }
            ui_pause();
        }
        else if (op == 4) {
             ui_header("LISTA DE FACTURAS");
             db_exec("SELECT id, fecha, cliente, total FROM facturas;"); 
             printf("\n");
             int fid = ui_input_int("ID Factura a ver detalle (0 para volver): ");
             if (fid > 0) {
                 bill_show_invoice(fid);
                 ui_pause();
             }
        }
        else if (op == 5) {
             bill_get_stats();
        }
    }
}

void general_menu() {
    int current_quote = -1;
    
    while(1) {
        ui_header("MENÚ GENERAL");
        // Store Info Header (Basic Requirement)
        printf("  Local: Supermercado El Tico  |  Tel: 2222-2222\n");
        printf("  Horario: 8am - 8pm           |  Ced: 3-101-123456\n");
        printf("  --------------------------------------------------------\n\n");
        
        if (current_quote != -1) {
            printf(C_GREEN "  [COTIZACIÓN ACTIVA: #%d]\n" C_RESET, current_quote);
        }
        printf(C_CYAN "  [1]" C_RESET " Catálogo de Productos\n");
        printf(C_CYAN "  [2]" C_RESET " Crear Cotización\n");
        printf(C_CYAN "  [3]" C_RESET " Agregar Item a Cotización\n");
        printf(C_CYAN "  [4]" C_RESET " Remover Item de Cotización\n"); // New
        printf(C_CYAN "  [5]" C_RESET " Facturar Cotización\n");
        printf(C_RED  "  [6]" C_RESET " Volver\n");
        printf("\n");
        
        int op = ui_input_int("Opción: ");
        
        if (op == 6) break;
        
        if (op == 1) {
            inv_show_catalog();
            ui_pause();
        }
        else if (op == 2) {
            char cli[100];
            ui_input_str("Nombre Cliente: ", cli);
            current_quote = bill_create_quote(cli);
            if (current_quote > 0) {
                char msg[50];
                sprintf(msg, "Cotización #%d creada.", current_quote);
                ui_print_success(msg);
            }
            else ui_print_error("Error creando cotización.");
            ui_pause();
        }
        else if (op == 3) {
            if (current_quote == -1) {
                ui_print_error("Debe crear una cotización primero.");
                current_quote = ui_input_int("O ingrese número existente: ");
            }
            if (current_quote > 0) {
                char pid[20];
                ui_input_str("ID Producto: ", pid);
                int qty = ui_input_int("Cantidad: ");
                if (bill_add_item(current_quote, pid, qty)) ui_print_success("Item agregado.");
                else ui_print_error("No se pudo agregar (Stock insuficiente o ID inválido).");
                ui_pause();
            }
        }
        else if (op == 4) {
             if (current_quote <= 0) {
                 ui_print_error("No hay cotización activa.");
             } else {
                 char pid[20];
                 ui_input_str("ID Producto a remover: ", pid);
                 bill_remove_item(current_quote, pid);
                 ui_print_success("Item removido (si existía).");
             }
             ui_pause();
        }
        else if (op == 5) {
            int qid = current_quote;
            if (qid <= 0) qid = ui_input_int("Número Cotización: ");
            
            char pay[20];
            ui_input_str("Pago (Efectivo/Tarjeta): ", pay);
            
            if (bill_process_invoice(qid, pay)) {
                ui_print_success("Factura procesada correctamente.");
                if (qid == current_quote) current_quote = -1; // Reset active
            } else {
                ui_print_error("Error al procesar factura.");
            }
            ui_pause();
        }
    }
}


# Sistema de Punto de Venta (C) 🛒

**Estudiante:** Geovanni Gonzalez Aguilar
**Carné:** 2022163324
**Curso:** Lenguajes de Programación

## Descripción

Sistema de punto de venta en consola desarrollado en C standard con integración de SQLite para persistencia de datos. Permite la gestión completa de un comercio, desde el mantenimiento de inventarios hasta la facturación, cumpliendo con estándares de gestión de memoria y modularidad.

**Novedades v2.0:**

- Interfaz Gráfica de Texto (TUI) con colores y banners.
- Soporte UTF-8 nativo para caracteres especiales.
- Sistema de estadísticas de ventas.

## Tecnologías

- **Lenguaje**: C (C11)
- **Base de Datos**: SQLite3 (Integrado/Amalgamation)
- **Interfaz**: Librería propia `ui.h` para manejo de colores ANSI y layouts.
- **Compilador**: GCC

## Características Principales

### 📦 Inventario

- **Gestión de Familias y Productos**: Alta, baja y consulta.
- **Carga en Lote**: Soporte para archivos CSV (`familias_batch.txt`, `productos_batch.txt`).
- **Validación de Stock**: Control automático al facturar.

### 💰 Facturación

- **Cotizaciones**: Creación, edición y eliminación de items.
- **Facturación Automática**: Conversión de cotización a factura con deducción de inventario e impuestos (13%).
- **Persistencia**: Histórico completo en base de datos.
- **Reportes**: Ventas por familia, productos más vendidos, promedios.

## Estructura del Proyecto

- `src/`: Código fuente (`main.c`, `inventory.c`, `billing.c`, `ui.c`, `db_adapter.c`).
- `include/`: Archivos de cabecera.
- `lib/`: Librería SQLite3.
- `db/`: Base de datos (creada automáticamente).
- `documentacion/`: Manual de usuario y técnico.

## Ejecución Rápida

Desde la carpeta `programa`:

```powershell
powershell .\build.ps1
```

O compilación manual:

```bash
gcc src/main.c src/db_adapter.c src/inventory.c src/billing.c src/ui.c lib/sqlite3.c -o pos_app.exe -I./include -I./lib
```

## Credenciales de Acceso

- **Usuario**: `admin`
- **Contraseña**: `admin123`

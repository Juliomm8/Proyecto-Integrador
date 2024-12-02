#ifndef INFOPRODUCTOS_H
#define INFOPRODUCTOS_H

#include <stdio.h>
#include <string.h>
#include "validación.h"

void ingresarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int *numProductos) {
    // Verificar si el inventario está lleno
    if (*numProductos >= 1000) {
        printf("\033[1;31mNo se pueden agregar más productos [Inventario lleno]\033[0m\n");
        return;
    }

    printf("\n\033[1;32m-----Ingreso de un nuevo producto-----\033[0m\n");

    // Ingreso del nombre del producto
    int nombreValido = 0;
    do {
        printf("Ingresa el nombre del producto: ");
        fgets(nombres[*numProductos], sizeof(nombres[*numProductos]), stdin);
        nombres[*numProductos][strcspn(nombres[*numProductos], "\n")] = '\0';

        // Validar si el nombre es único
        if (!esNombreUnico(nombres[*numProductos], nombres, *numProductos)) {
            printf("\033[1;31mEl nombre del producto ya existe, ingresa con otro nombre.\033[0m\n");
        } else {
            nombreValido = 1;
        }
    } while (!nombreValido);
    
    // Ingreso del fabricante
    printf("Ingresa el nombre del fabricante: ");
    fgets(fabricantes[*numProductos], sizeof(fabricantes[*numProductos]), stdin);
    fabricantes[*numProductos][strcspn(fabricantes[*numProductos], "\n")] = '\0';

    // Ingreso del código del producto
    int codigoValido = 0;
    do {
        ingresarCodigoValido(codigos[*numProductos], sizeof(codigos[*numProductos]));
        if (!esCodigoUnico(codigos[*numProductos], codigos, *numProductos)) {
            printf("\033[1;31mEl código ya está en uso, ingresa otro\033[0m\n");
        } else {
            codigoValido = 1;
        }
    } while (!codigoValido);

     // Ingreso de la cantidad de unidades
    do {
        printf("Cantidad de unidades: ");
        scanf("%d", &cantidades[*numProductos]);
        getchar();//limpiar el buffer
        if (!validarCantidadProducto(cantidades[*numProductos])) {
            printf("\033[1;31mCantidad no válida, ingresa de nuevo\033[0m\n");
        }
    } while (!validarCantidadProducto(cantidades[*numProductos]));

    // Ingreso del precio sin impuestos
    do {
        printf("Precio del producto (sin impuestos): ");
        scanf("%f", &precios[*numProductos]);
        getchar(); // Limpiar el buffer
        if (precios[*numProductos] <= 0) {
            printf("\033[1;31mEl precio debe ser mayor que 0, ingresa de nuevo\033[0m\n");
        }
    } while (precios[*numProductos] <= 0);

    // Ingreso del porcentaje de impuestos
    do {
        printf("Porcentaje del impuesto para este producto: ");
        scanf("%f", &impuestos[*numProductos]);
        getchar(); // Limpiar el buffer
        if (impuestos[*numProductos] < 0) {
            printf("\033[1;31mEl impuesto no puede ser negativo, ingresa de nuevo\033[0m\n");
        }
    } while (impuestos[*numProductos] < 0);

    // Ingreso de si requiere prescripción médica
    do {
        printf("\033[1;31m-----¿Requiere prescripción médica?-----\033[0m\n");
        printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
        scanf("%d", &requierePrescripcion[*numProductos]);
        getchar(); // Limpiar el buffer
        if (requierePrescripcion[*numProductos] != 0 && requierePrescripcion[*numProductos] != 1) {
            printf("\033[1;31mOpción no válida, ingresa 1 para Sí o 0 para No\033[0m\n");
        }
    } while (requierePrescripcion[*numProductos] != 0 && requierePrescripcion[*numProductos] != 1);

    // Incrementar el contador de productos
    (*numProductos)++;
    printf("\033[1;32m-----Producto agregado con éxito :)-----\033[0m\n");
}

void imprimirTodosLosProductos(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos) {
    // Validar si el inventario está vacío
    if (numProductos == 0) {
        printf("\033[1;31m-----No hay productos en el inventario-----\033[0m\n");
        return;
    }

     // Imprimir información de cada producto
    printf("\033[1;34m\nLista de productos:\033[0m\n");
    for (int i = 0; i < numProductos; i++) {
        float precioConImpuestos = precios[i] * (1 + impuestos[i] / 100);
        printf("\033[1;33mProducto %d:\033[0m\n", i + 1);
        printf("  Nombre: %s\n", nombres[i]);
        printf("  Código: %s\n", codigos[i]);
        printf("  Fabricante: %s\n", fabricantes[i]);
        printf("  Unidades: %d\n", cantidades[i]);
        printf("  Precio (sin impuestos): %.2f\n", precios[i]);
        printf("  Impuesto: %.2f%%\n", impuestos[i]);
        printf("  P.V.P: %.2f\n", precioConImpuestos);
        printf("  Requiere prescripción: %s\n", requierePrescripcion[i] ? "\033[1;31mSí\033[0m" : "\033[1;32mNo\033[0m");
        printf("\033[1;34m----------------------------------------\033[0m\n");
    }
}

#endif // INFOPRODUCTOS_H

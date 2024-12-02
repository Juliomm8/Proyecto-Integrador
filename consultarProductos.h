#ifndef CONSULTARPRODUCTOS_H
#define CONSULTARPRODUCTOS_H

#include <stdio.h>
#include <string.h>

void buscarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos);

void consultarProductoPorNombre(char *nombreBusqueda, char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos);

void consultarProductoPorCodigo(char *codigoBusqueda, char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos);

void eliminarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int *numProductos);

void editarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos);

void buscarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos) {
    
    int criterio=0;
    
    char entrada[50];

    // Mostrar opciones al usuario
    printf("¿Desea buscar por:\n");
    printf("Nombre [1]\n");
    printf("Código [2]\n");
    printf("Seleccione una opción: ");
    scanf("%d", &criterio);
    getchar(); // Limpiar el buffer de entrada

    if (criterio == 1) { // Buscar por nombre
        printf("Ingrese el nombre del producto: ");
        
        fgets(entrada, sizeof(entrada), stdin);
        
        entrada[strcspn(entrada, "\n")] = '\0';
        
        consultarProductoPorNombre(entrada, nombres, codigos, fabricantes, cantidades, precios, impuestos, requierePrescripcion, numProductos);
        
    } else if (criterio == 2) { // Buscar por código
        printf("Ingrese el código del producto: ");
        
        fgets(entrada, sizeof(entrada), stdin);
        
        entrada[strcspn(entrada, "\n")] = '\0';
        
        consultarProductoPorCodigo(entrada, nombres, codigos, fabricantes, cantidades, precios, impuestos, requierePrescripcion, numProductos);
        
    } else {
        printf("\033[1;31m-----Opción no válida-----\033[0m\n");
    }
}

void consultarProductoPorNombre(char *nombreBusqueda, char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos) {
    int encontrado = 0; // Indicador para saber si el producto fue encontrado

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBusqueda) == 0) { // Comparar nombres
            printf("\033[1;32mProducto encontrado:\033[0m\n");
            
            printf("  Nombre: %s\n", nombres[i]);
            
            printf("  Código: %s\n", codigos[i]);
            
            printf("  Fabricante: %s\n", fabricantes[i]);
            
            printf("  Cantidad: %d\n", cantidades[i]);
            
            printf("  Precio (sin impuestos): %.2f\n", precios[i]);
            
            printf("  Porcentaje de impuesto: %.2f%%\n", impuestos[i]);
            
            printf("  P.V.P: %.2f\n", precios[i] * (1 + impuestos[i] / 100));
            
            printf("  Requiere prescripción: %s\n", requierePrescripcion[i] ? "\033[1;31mSi\033[0m" : "\033[1;32mNo\033[0m");
            
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\033[1;31mNo se encontró ningún producto con ese nombre\033[0m\n");
    }
}

void consultarProductoPorCodigo(char *codigoBusqueda, char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos) {
    int encontrado = 0;

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(codigos[i], codigoBusqueda) == 0) { // Comparar códigos
            printf("\033[1;32mProducto encontrado:\033[0m\n");

            // Imprimir información del producto (similar a la función anterior)
            printf("  Nombre: %s\n", nombres[i]);
            
            printf("  Código: %s\n", codigos[i]);
            
            printf("  Fabricante: %s\n", fabricantes[i]);
            
            printf("  Cantidad: %d\n", cantidades[i]);
            
            printf("  Precio (sin impuestos): %.2f\n", precios[i]);
            
            printf("  Porcentaje de impuesto: %.2f%%\n", impuestos[i]);
            
            printf("  P.V.P: %.2f\n", precios[i] * (1 + impuestos[i] / 100));
            
            printf("  Requiere prescripción: %s\n", requierePrescripcion[i] ? "\033[1;31mSi\033[0m" : "\033[1;32mNo\033[0m");
            
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
    }
}

void eliminarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int *numProductos) {
    char entrada[50];
    printf("Ingrese el código del producto a eliminar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(codigos[i], entrada) == 0) {
            // Desplazar los elementos siguientes para eliminar el producto
            for (int j = i; j < *numProductos - 1; j++) {
                strcpy(nombres[j], nombres[j + 1]);
                
                strcpy(codigos[j], codigos[j + 1]);
                
                strcpy(fabricantes[j], fabricantes[j + 1]);
                
                cantidades[j] = cantidades[j + 1];
                
                precios[j] = precios[j + 1];
                
                impuestos[j] = impuestos[j + 1];
                
                requierePrescripcion[j] = requierePrescripcion[j + 1];
            }
            (*numProductos)--; // Reducir el contador de productos
            
            printf("\033[1;32m-----Producto eliminado con éxito-----\033[0m\n");
            
            return;
        }
    }

    printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
}

void editarProducto(char nombres[][50], char codigos[][20], char fabricantes[][50], int *cantidades, float *precios, float *impuestos, int *requierePrescripcion, int numProductos) {
    char entrada[50];
    
    printf("Ingrese el código del producto a editar: ");
    
    fgets(entrada, sizeof(entrada), stdin);
    
    entrada[strcspn(entrada, "\n")] = '\0';

    for (int i = 0; i < numProductos; i++) {
        if (strcmp(codigos[i], entrada) == 0) {
            
            printf("\033[1;32m-----Editanto Producto-----\033[0m\n");

            // Solicitar nuevos datos del producto
            printf("Nuevo nombre para [%s]: ", nombres[i]);
            fgets(nombres[i], sizeof(nombres[i]), stdin);
            nombres[i][strcspn(nombres[i], "\n")] = '\0';

            printf("Nuevo fabricante para [%s]: ", fabricantes[i]);
            fgets(fabricantes[i], sizeof(fabricantes[i]), stdin);
            fabricantes[i][strcspn(fabricantes[i], "\n")] = '\0';

            printf("Nuevo N° unidades para [%d]: ", cantidades[i]);
            scanf("%d", &cantidades[i]);
            getchar();

            printf("Nuevo precio (sin impuestos) para [%.2f]: ", precios[i]);
            scanf("%f", &precios[i]);
            getchar();

            printf("Nuevo Impuesto para [%.2f%%]: ", impuestos[i]);
            scanf("%f", &impuestos[i]);
            getchar();

            printf("\033[1;31m¿Requiere prescripción médica?\033[0m\n");
            printf("\033[1;31mSí [1]\033[0m  \033[1;32mNo [0]\033[0m : ");
            scanf("%d", &requierePrescripcion[i]);
            getchar();

            printf("\033[1;32m-----Producto editado con éxito-----\033[0m\n");
            return;
        }
    }

    printf("\033[1;31mNo se encontró ningún producto con ese código\033[0m\n");
}

#endif // CONSULTARPRODUCTOS_H
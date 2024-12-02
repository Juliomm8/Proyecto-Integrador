#ifndef VALIDACION_H
#define VALIDACION_H

#include <stdio.h>
#include <string.h>

int validarNombreProducto(char *cadena);
int validarCodigoProducto(char *codigo);
int validarCantidadProducto(int cantidad);
int esNombreUnico(char *nombre, char nombres[][50], int numProductos);
int esCodigoUnico(char *codigo, char codigos[][20], int numProductos);
void ingresarCodigoValido(char *codigo, size_t tam);

// Valida que el nombre del producto solo contenga caracteres alfabéticos, numéricos y espacios
int validarNombreProducto(char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        // Verifica si el carácter actual no es válido
        if (!((cadena[i] >= 'A' && cadena[i] <= 'Z') || 
              (cadena[i] >= 'a' && cadena[i] <= 'z') || 
              (cadena[i] >= '0' && cadena[i] <= '9') || 
              cadena[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}

// Valida que el código del producto solo contenga dígitos numéricos
int validarCodigoProducto(char *codigo) {
    for (int i = 0; codigo[i] != '\0'; i++) {
        if (!(codigo[i] >= '0' && codigo[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

// Verifica que la cantidad de producto sea un valor positivo
int validarCantidadProducto(int cantidad) {
    return cantidad > 0;
}

// Comprueba si el nombre del producto es único comparándolo con los nombres existentes
int esNombreUnico(char *nombre, char nombres[][50], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            return 0; // No es único
        }
    }
    return 1; // Es único
}

// Comprueba si el código del producto es único comparándolo con los códigos existentes
int esCodigoUnico(char *codigo, char codigos[][20], int numProductos) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(codigos[i], codigo) == 0) {
            return 0; // No es único
        }
    }
    return 1; // Es único
}

// Solicita al usuario que ingrese un código válido
void ingresarCodigoValido(char *codigo, size_t tam) {
    int valido = 0; // Indicador para determinar si el código es válido
    do {
        printf("Ingresa el código del producto: ");
        fgets(codigo, tam, stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        // Valida si el código está vacío o contiene caracteres no válidos
        if (strlen(codigo) == 0 || !validarCodigoProducto(codigo)) {
            printf("\033[1;31mEl código contiene caracteres no válidos, ingresa de nuevo\033[0m\n");
        } else {
            valido = 1;
        }
    } while (!valido);
}

#endif // VALIDACION_H
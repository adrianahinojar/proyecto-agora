# Proyecto AGORA - Gestión de Accesos al Metro

## Descripción
AGORA es un programa en C diseñado para gestionar los accesos a estaciones de metro a partir de un archivo de datos (`stops.txt`). Permite realizar consultas sobre la ubicación y accesibilidad de los accesos a las estaciones.

## Funcionalidades
El programa ofrece las siguientes funciones principales:

- **Determinar el acceso de metro más cercano** a una ubicación específica, definida por sus coordenadas de latitud y longitud.
- **Mostrar los accesos disponibles** de una estación de metro en particular.
- **Generar un archivo de accesibilidad** con los accesos aptos para personas con movilidad reducida.

## Entrada de Datos
El programa lee la información desde un archivo de texto (`stops.txt`), que contiene los datos de las estaciones y sus accesos. Cada línea del archivo sigue un formato estructurado con información clave, como:

- Nombre de la estación
- Identificador del acceso
- Coordenadas geográficas (latitud y longitud)
- Información sobre accesibilidad

## Implementación
El código está estructurado en módulos que manejan la lectura de archivos, el procesamiento de datos y los cálculos de distancia geográfica. Se utilizan estructuras de datos en C para gestionar eficientemente la información y realizar consultas rápidas.


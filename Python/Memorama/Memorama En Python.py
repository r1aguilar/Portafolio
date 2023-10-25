# Nombre: Rodrigo Aguilar Morales
# Matrícula: A01285921
# Carrera: IDM
# Proyecto: Memorama

import random, os

from colorama import init, Fore, Back, Style

# Variables Globales
colores = [Fore.BLACK, Fore.BLUE , Fore.CYAN , Fore.GREEN, Fore.LIGHTBLACK_EX, Fore.WHITE,
Fore.LIGHTBLACK_EX ,
Fore.LIGHTBLUE_EX,
Fore.LIGHTCYAN_EX,
Fore. LIGHTGREEN_EX,
Fore.LIGHTMAGENTA_EX ,
Fore.LIGHTRED_EX ,
Fore.LIGHTWHITE_EX,
Fore.LIGHTYELLOW_EX ,
Fore.MAGENTA,
Fore.RED,
Fore.RESET,
Fore.WHITE ,
Fore.YELLOW ]
 
fondo = [  Back.BLACK, Back.BLUE, Back.CYAN, Back.GREEN,Back.LIGHTBLACK_EX, Back.LIGHTBLUE_EX, Back.LIGHTCYAN_EX,
 Back.LIGHTGREEN_EX, Back.LIGHTMAGENTA_EX, Back.LIGHTRED_EX, Back.LIGHTWHITE_EX, Back.LIGHTYELLOW_EX,
 Back.MAGENTA, Back.RED, Back.RESET, Back.WHITE , Back.YELLOW ]

# Para restablecer colores después de cada impresión inicializar 
# el módulo con init(autoreset=True) en lugar de init().+Back.RESET
init()

def pares( ):
    pars =    """One
I
Two
II
Three
III
Four
IV
Five
V
Six
VI
Seven
VII
Eight
VIII
Nine
IX
Ten
X
Fifteen
XV
Twenty
XX
Twenty five
XXV
Fifty
L
Seventy Five
LXXV
One hundred
C
One thousand
M
Two thousand and twenty two
MMXXII"""
    
    lista = pars.split("\n")
    # print("Longitud = ", len(lista))
    # for elemento in lista:
    #    print(elemento)
    
    return lista

def limpia():
    '''Función que limpia a pantalla sin importar el sistema operativo
      de la máquina donde esté corriendo'''
    if os.name == 'nt': #Windows
        os.system('cls') 
    else:  #'posix'
        os.system('clear') #Mac/linux


def llena_tablero():
    '''Llena el tablero con las "cartas volteadas"'''
    matriz=[]
    for r in range(6):
        renglon=[]
        for c in range(6):
            # Agrega un emoji de flor en con el código unicode
            renglon.append('\U0001F4AE')
        matriz.append(renglon)
    return matriz


def despliega_matriz(tablero, r1 = None, c1 = None, r2 = None, c2 = None):
    '''Despliega a pantalla la matriz que recibe en forma de tabla
     desplegando una cuadricula'''
    # Agrega los numeros de las columnas
    print("==============="*len(tablero))
    print(f'1'.center(18),f'2'.center(6),f'3'.center(18),f'4'.center(6),f'5'.center(18),f'6'.center(6), end="")
    print('\n'+"==============="*len(tablero))
    
    # Asigna la variable renglones con el número de objetos por fila y columnas con la cantidad de filas
    renglones = len(tablero)
    columnas = len(tablero[0])
    # Imprimir el formato del tablero
    print("==============" * renglones)
    
    # Imprimir los números de filas
    for r in range(renglones):
        print(r + 1,"|", end="")
        for c in range(columnas):
            # Condiciones para desplegar las cartas y resaltarlas
            if r1 != None and r1 == r and c1 == c:
                print(Back.LIGHTMAGENTA_EX + f"{ tablero[r][c] }".center(11) + Back.RESET,end="")
            elif r2 != None and r2 == r and c2 == c:
                print(Back.LIGHTMAGENTA_EX + f"{ tablero[r][c] }".center(11) + Back.RESET,end="")
            else:
                print(fondo[r+1] + f"{ tablero[r][c] }".center(11) + Back.RESET, end="")
                
            print("|" + Back.RESET, end="")
       
        print('\n' + "=============="* renglones)


def llena_escondida(lista):
    '''Llena una matriz de números emojis y palabras, para que el alumno
     aprenda sobre los numeros en romano ...'''
    matriz=[]
    random.shuffle(lista)
    for r in range(6):
        renglon=[]
        for c in range(6):
             # Agrega cada elemento de la lista
            renglon.append(lista.pop(0))
        matriz.append(renglon)
        
    return matriz


def validar_carta(tablero,escondida,r1,c1,r2 = None,c2 = None):    
    """Valida las cartas enviadas por el jugador para saber si las posiciones son validas,
        fueron escogidas en un turno previo o estan siendo repetidas en este turno ..."""
    if r2 is None and c2 is None:
        # Valida la carta 1 del jugador
        while r1 < 1 or r1> 6 or c1 <1 or c1 > 6 or tablero [r1-1][c1-1] != "\U0001F4AE":
            r1 = int(input("Error , Ingresa de nuevo la posición de la carta 1\nRenglon: "))
            c1 = int(input("Columna: "))
        # Retornar el valor para ser leido por la matriz  
        return r1 -1,c1 -1
    else: # Validar la carta 2 del jugador
        while r2 < 1 or r2> 6 or c2 <1 or c2 > 6 or tablero [r2-1][c2-1] != "\U0001F4AE" or escondida [r2-1][c2-1] == escondida[r1][c1]:
            # Si la carta es mayor al rango permitido, fue previamente destapada o fue elegida dos veces, se llama para elegirse una vez más
            r2 = int(input("Error. Ingresa de nuevo la posición de la carta 2\nRenglón: "))
            c2 = int(input("Columna: "))
        # Retornar el valor para ser leido por la matriz  
        return r2 -1, c2 -1
    
    
def validar_carta_computadora(tablero,escondida,r1,c1,r2 = None,c2 = None):    
    # Valida la carta 1 de la computadora
    if r2 is None and c2 is None:
        while tablero [r1 - 1][c1 - 1] != '\U0001F4AE':
            # Si el valor ya fue elegido, genera nuevos valores random
            r1 = random.randint(1,6)
            c1 = random.randint(1,6)
        # Retornar el valor para ser leido por la matriz  
        return r1 - 1, c1 - 1
    else: # Validar la carta 2 de la computadora
        while tablero [r2 - 1][c2 - 1] != '\U0001F4AE' or escondida[r2-1][c2-1] == escondida[r1][c1]:
            # Si la carta es mayor al rango permitido, fue previamente destapada o fue elegida dos veces, se generan nuevos valores random
            r2 = random.randint(1,6)
            c2 = random.randint(1,6)
            # Retornar el valor para ser leido por la matriz  
        return r2 - 1, c2 - 1
       
      
def son_pares(tablero, escondida, lista_pares, lista_impares,r1,c1,r2,c2):     
    
    # Hacer visibles las cartas 1 y 2
    tablero[r1][c1] = escondida[r1][c1]
    tablero[r2][c2] = escondida[r2][c2]
    
    # Desplegar el tablero
    limpia()
    tablero[r1][c1] = escondida[r1][c1]
    tablero[r2][c2] = escondida[r2][c2]
    input("-....OPRIMA UNA TECLA PARA CONTINUAR...-")
    gano = 0
    limpia( )
    despliega_matriz(escondida)
    despliega_matriz(tablero, r1, c1, r2, c2)
    
    # Buscar la carta 1 en la primera lista
    if escondida[r1][c1] in lista_pares:
        # Se encontró en la lista 1, por lo tanto se busca su posición
        posicion = lista_pares.index(escondida[r1][c1])
        # Se compara si la carta 2 elegida coincide con el valor del indice en la lista 2, que es el par de la misma posición en la lista 1
        if escondida[r2][c2] == lista_impares[posicion]:
            # Es par
            print("Felicidades, es par!!")
            # Aumentas el contador
            gano = 1
        else:
            print("No es par!!")
            # Se esconden las cartas una vez mas
            tablero[r1][c1] = '\U0001F4AE'
            tablero[r2][c2] = '\U0001F4AE'
     
     # No se encontró la carta en la lista 1, por tanto se busca en la lista 2
    elif escondida[r1][c1] in lista_impares:
        # Se busca su posición en la lista 2
        posicion = lista_impares.index(escondida[r1][c1])
        # Se compara si la carta 2 elegida coincide con el valor del indice en la lista 1, que es el par de la misma posición en la lista 2
        if escondida[r2][c2] == lista_pares[posicion]:
            # Es par
            print("Felicidades, es par!")
            # Aumenta el contador
            gano = 1  
        else:
            print("No es par")
            # Se esconden las cartas una vez mas
            tablero[r1][c1] = '\U0001F4AE'
            tablero[r2][c2] = '\U0001F4AE'
            
    # Regresa un 1 si fue par, o 0 si no lo fué
    return gano
     
     
def main():
    # Llamar a la funcion pares() - retorna una lista de 36 elementos 
    lista = pares()
    # Separar la lista de elementos en 2
    lista_pares = lista[0::2]
    lista_impares = lista[1::2]
     # Llamamos a las funciones que llenan las matrices
    tablero = llena_tablero()
    escondida = llena_escondida(lista)
    # Inicializar los contadores para cada jugador
    pares1 = 0
    pares2 = 0
    # Mientras existan pares por encontrar en el juego, el ciclo se repite
    while pares1 + pares2 < 18:
        limpia()
        # Despliega los tableros
        despliega_matriz(escondida)
        despliega_matriz(tablero)
        
        # El jugador comienza
        
        print('Escribe la posición del que quieres destapar')

        # Se selecciona la primera carta
        r1=int(input('Ingresa la posicion de la carta 1\nRenglón: '))
        c1=int(input('Columna: '))
        
        # Se valida la primera carta
        r1, c1 = validar_carta(tablero,escondida,r1,c1)
        
        # Se selecciona la segunda carta
        r2 = int(input('Ingresa la posicion de la carta 2\nRenglón: '))
        c2 = int(input('Columna: '))
        
        # Se valida la segunda carta
        r2, c2 = validar_carta(tablero,escondida,r1,c1,r2,c2)
        
        # Actualizar el contador del jugador 
        pares1 += son_pares(tablero, escondida, lista_pares, lista_impares,r1,c1,r2,c2)
        
        # Desplegar la cantidad de pares por jugador
        print("Pares del jugador =", pares1)
        print("Pares de la Computadora = ", pares2)

        # Juega la C O M P U T A D O R A
        
        # Carta 1 de la computadora
        r1 = random.randint(1,6)
        c1 = random.randint(1,6)
        r1,c1 = validar_carta_computadora(tablero,escondida,r1,c1)
        
        # Carta 2 de la computadora
        r2 = random.randint(1,6)
        c2 = random.randint(1,6)
        r2,c2 = validar_carta_computadora(tablero,escondida,r1,c1,r2,c2)
        
        # Mostrar el tiro de la computadora
        print("La computadora eligio la carta 1: [", r1 +1 , "]","[",c1 +1,"]")
        print("La computadora eligio la carta 2: [", r2 +1 , "]","[",c2 +1,"]")
        
        # Pausa
        input('Enter para continuar')
        
        # Actualizar el contador de la computadora
        pares2 += son_pares(tablero, escondida, lista_pares, lista_impares,r1,c1,r2,c2)
        
        # Desplegar la cantidad de pares por jugador
        print("Pares del jugador =", pares1)
        print("Pares de la Computadora = ", pares2)
        # Pausa
        input('Enter para continuar')

    input('Enter para continuar')
    # Se destaparon todas las cartas
    limpia( )
    despliega_matriz(tablero)
    # Despliega los mensajes finales, dependiendo de los contadores
    
    # Si los contadores son iguales
    if pares1 == pares2:
        salida = Back.LIGHTYELLOW_EX + Fore.RED +  "EMPATE!!" + Fore.RESET + Back.RESET
        print(salida.center(80,"*"))
        
    # Si ganó el jugador
    elif pares1>pares2:
        salida = Back.LIGHTMAGENTA_EX + "GANASTE" + " FELICIDADES!!!" + Back.RESET
        print(salida.center(80,"*"))
        
    # Si ganó la computadora
    else:
        salida = Back.LIGHTRED_EX  + "TE GANÉ!!!" + Back.RESET
        print(salida.center(80,"*"))
     
main()

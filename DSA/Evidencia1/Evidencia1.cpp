#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

string keyGenerator(string year, string month, string day, string time)
{
    string key;

    //Eliminar los primeros dos caracteres de year
    year = year.substr(year.length() - 2);

    //Inicializar un array con los meses como vienen en el archivo txt, junto a su conversión en digitos
    string months[24] = {"Jan","01","Feb","02","Mar","03","Apr","04","May","05","Jun","06","Jul","07","Aug","08","Sep","09","Oct","10","Nov","11","Dec","12" };
    //Bandera para poder salir del ciclo
    bool mesEncontrado = false;
    //Iterador para el ciclo while
    int i = 0;

    while (!mesEncontrado)
    {
        //Mientras no se encuentre el mes compara el mes con cada string de mes en el array
        switch (month.compare(months[i]))
        {
        case 0:
            //Si se encuentra la comparación en esta iteración cambia la bandera para salir del ciclo
            mesEncontrado = true;
            //Cambiamos el valor de la variable month al dígito correspondiente del mes, que esta en el índice siguiente
            month = months[i + 1];
            break;

        default:
            //Si no se encuentra el mes en esta iteración aumenta el iterador en 2 para pasar al siguiente mes sin pasar por los digitos
            i = i + 2;
        }
    }

    //Removemos los doble puntos del tiempo
    time.erase(remove(time.begin(), time.end(), ':'), time.end());

    //Concatenamos todos los strings ya cambiados para crear la key del log
    key = year + month + day + time;

    return key;
}

struct Log
{
    //Incializamos las variables de la estructura
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    string key;

    //Constructor 
    Log(string year, string month, string day, string time, string ip, string message);

    //Sobrecarfa del operador <
    bool operator<(Log log);
};

Log::Log(string year, string month, string day, string time, string ip, string message)
{
    //this se usa para referirse a la variable year del struct, y no a la local
    this->year = year;
    this->month = month;
    this->day = day;
    this->time = time;
    this->ip = ip;
    this->message = message;
    //Generamos la llave con una funcion que convierta el mes a número y concatene el año mes día y hora
    key = keyGenerator(year, month, day, time);
    this->key = key;
}

bool Log::operator<(Log log)
{
    return key < log.key;
}

ostream& operator<<(ostream& os, Log log) {
    os << "Log: " << log.month << " " << log.day << " " << log.year << " " << log.time << " " << log.ip << " " << log.message << endl;
    return os;
}

void swap(vector<Log>& lista_a_ordenar, int j, int i)
{
    if (lista_a_ordenar[i].key != lista_a_ordenar[j].key)
    {
        Log aux = lista_a_ordenar[i];
        lista_a_ordenar[i] = lista_a_ordenar[j];
        lista_a_ordenar[j] = aux;
    }

}

int getPivot(vector<Log>& list, int left, int right)
{
    //Definir el índice del pivote
    int pivot = right;
    //Definir el índice auxiliar igual a left-1
    int auxIndex = left - 1;
    //Recorremos la lista desde left hasta right - 1
    for (int index = left; index < right; index++)
    {
        //Comparamos los valores de index contra el pivote
        if (list[index].key < list[pivot].key)
        {
            //Incrementamos auxIndex en 1
            auxIndex++;
            //Intercambiamos index con auxIndex
            swap(list, index, auxIndex);
        }
    }
    //Incrementamos auxIndex en 1
    auxIndex++;
    //Intercambiamos el índice auxiliar con el pivot
    swap(list, auxIndex, pivot);

    return auxIndex;
}

void quickSort(vector<Log>& list, int left, int right)
{
    // Condición de control
    if (left < right)
    {
        //Obtener el índice final del pivote
        int pivot = getPivot(list, left, right);
        //Ordenamos la lista del lado izquierdo
        quickSort(list, left, pivot - 1);
        //Ordenamos la lista del lado derecho
        quickSort(list, pivot + 1, right);
    }
}

void printInFile(vector<Log> lista)
{
    //Inicializamos el archivo de salida para imprimir los registros ordenados
    ofstream outFile("C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence1/output608.txt");

    //Ciclo for para imprimir cada registro en el archivo
    for (auto el : lista)
    {
        outFile << el;
    }
}

void printWithRange(vector<Log> lista, int lowerIndex, int upperIndex)
{
    //Inicializamos el archivo de salida para imprimir los registros del rango de busqueda
    ofstream fileOut("C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence1/range608.txt");

    //Ciclo for para imprimir cada registro del rango
    for (int i = lowerIndex; i <= upperIndex; i++)
    {
        cout << lista[i];
        fileOut << lista[i];
    }
    cout << endl << "Cantidad de registros: " << (upperIndex+1) - lowerIndex;
}

void leerArchivodeLogs(string nombre, vector<Log>& logs)
{
    // Archivo de entrada
    ifstream fileIn(nombre);
    // Archivo de salida
    ofstream fileOut("output608.txt");
    // Variable auxiliar para guardar el contenido del renglón leido
    string line;
    // Variable auxiliar para guardar el contenido de cada palabra del campo message
    string word;
    // Variables auxiliares para guardar el contenido de cada campo del archivo
    string year;
    string month;
    string day;
    string time;
    string ip;
    string message;
    string key;
    // Variable auxiliar para guardar el contador de registros
    int cont = 0;
    // Ciclo para leer todo los renglones del archivo de entrada
    while (getline(fileIn, line)) {
        // Creamos una variable auxiliar ss para recorrer campo por campo
        stringstream ss(line);
        // Guardamos la información de cada campo en la variable auxiliar correspondiente
        ss >> month >> day >> year >> time >> ip >> message;
        // Ciclo para recorrer cada palabra del campo message
        while (ss >> word) {
            message = message + " " + word;
        }

        //Creamos un Log con los datos que acabamos de recibir
        Log log(year, month, day, time, ip, message);

        //Agregamos el nuevo Log al vector donde se guardan
        logs.push_back(log);

        // Incrementamos el contador de registros
        cont++;
    }

    //Mandamos a ordenar los registros
    quickSort(logs, 0, logs.size() - 1);
    //Imprimimos los registros en el archivo de salida
    printInFile(logs);
}

int busquedaBinaria(vector <Log> lista, string valor_a_encontrar, bool esMayor)
{
    //Inicializamos left, mid y right
    int left = 0, right = lista.size() - 1, mid = 0;

    //Mientras left sea menor o igual que right
    while (left <= right)
    {
        //Cálculo para encontrar mid
        mid = left + (right - left) * 0.5;

        //Si el valor a encontrar se encuentra en mid salirse del ciclo
        if (lista[mid].key == valor_a_encontrar)
        {
            break;
        }
        //Si el valor a encontrar es mayor que mid, cambiar left a 1 mas que mid
        else if (lista[mid].key <= valor_a_encontrar)
        {
            left = mid + 1;
        }
        //Si el valor a encontrar es menor que mid, cambiar right a 1 menos que mid
        else if (lista[mid].key >= valor_a_encontrar)
        {
            right = mid - 1;
        }
    }

    //Verificar si esta busqueda es la de la fecha superior 
    if (esMayor)
    {
        //Si es la fecha superior, verifica si mid es mayor al valor a encontrar y lo reduce en 1
        if (lista[mid].key > valor_a_encontrar)
        {
            mid--;
        }
    }
    else
    {
        //Si es la fecha inferior, verifica si mid es menor al valor a encontrar y lo aumenta en 1
        if (lista[mid].key < valor_a_encontrar)
        {
            mid++;
        }
    }

    //Se regresa mid, que es el indice donde empieza o termina el rango, dependiendo de la busqueda
    return mid;
}

int main() 
{
    //Inicializar el vector para guardar los registros
    vector<Log> Logs;
    //Mandar a llamar la función para leer el archivo de registros y guardarlo en Logs
    leerArchivodeLogs("C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence1/log608.txt", Logs);

    if (Logs.empty())
    {
        cout << "Archivo no encontrado ...";
    }
    else 
    {
        //Inicializar la bandera para salir en false y las otras variables string
        bool salir = false;
        string year;
        string mes;
        string dia; 
        string tiempo; 
        string lowerBound;
        string upperBound; 
        string entrada;

        while (!salir)
        {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "                                SISTEMA DE REGISTROS " << endl;
            cout << "------------------------------------------------------------------------------------------------------------------" << endl << endl;
            cout << "                                   Buscar desde:" << endl << endl;
            cout << "                               Año (20XX): ";
            cin >> year;
            //Eliminar los primeros caracteres de year
            year = year.substr(year.length() - 2);
            cout << "                                 Mes (XX): ";
            cin >> mes;
            cout << "                                 Día (XX): ";
            cin >> dia;
            cout << "                          Hora (XX:XX:XX): ";
            cin >> tiempo;
            //Eliminar los : del tiempo
            tiempo.erase(remove(tiempo.begin(), tiempo.end(), ':'), tiempo.end());
            //Crear el limite inferior concatenando las variables de entrada
            lowerBound = year + mes + dia + tiempo;

            cout << endl << endl << "                                     Hasta:" << endl;
            cout << "                               Año (20XX): ";
            cin >> year;
            year = year.substr(year.length() - 2);
            //Eliminar los primeros caracteres de year
            cout << "                                 Mes (XX): ";
            cin >> mes;
            cout << "                                 Día (XX): ";
            cin >> dia;
            cout << "                          Hora (XX:XX:XX): ";
            cin >> tiempo;
            //Eliminar los : del tiempo
            tiempo.erase(remove(tiempo.begin(), tiempo.end(), ':'), tiempo.end()); 
            //Crear el limite superior concatenando las variables de entrada
            upperBound = year + mes + dia + tiempo;

            cout << endl;
            
            //Revisar si los límites son incoherentes
            if (lowerBound > upperBound)
            {
                cout << endl << "------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "                       No se puede tener un rango de búsqueda negativo ... " << endl;
                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            }

            //Si son coherentes
            else
            {
                //LLamar la busqueda binaria con los limites para conocer los indices del rango
                int lowerIndex = busquedaBinaria(Logs, lowerBound, false);
                int upperIndex = busquedaBinaria(Logs, upperBound, true);

                cout << endl <<"------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "                           Registros encontrados ";
                cout << endl << "------------------------------------------------------------------------------------------------------------------" << endl;
                
                //Mandamos a llamar a imprimir los registros desde el indice menor hasta el mayor
                printWithRange(Logs, lowerIndex, upperIndex);
            }

            cout << endl << endl << "------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "                    Presione 0 para salir o 1 para continuar ... " << endl;
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            cin >> entrada;

            if (entrada == "0")
            {
                salir = true;
            }

        }
    }

    return 0;
}
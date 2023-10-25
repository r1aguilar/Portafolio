#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "DoublyLinkedList.h"
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
    int i = 1;

    while (!mesEncontrado)
    {
        //Mientras no se encuentre el mes compara el mes con cada string de mes en el array
        switch (month.compare(months[i-1]))
        {
        case 0:
            //Si se encuentra la comparación en esta iteración cambia la bandera para salir del ciclo
            mesEncontrado = true;
            //Cambiamos el valor de la variable month al dígito correspondiente del mes, que esta en el índice siguiente
            month = months[i];
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

string modificarIp(string ip)
{
    string ip_modificada, val;
    int i = 0;

    stringstream ip_S(ip);

    while(getline(ip_S,val,'.'))
    {
        while(val.length() != 3 && i > 0)
        {
            val.insert(0,"0");        
        }

        ip_modificada = ip_modificada + val;
        i++;
    }

    return ip_modificada;
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
    string ip_modificada;
    string key_ip_modificada;

    Log();

    //Constructor 
    Log(string year, string month, string day, string time, string ip, string message);

    //Sobrecarfa del operador <
    bool operator<(Log log);

    bool compare(Log log);

    bool operator!=(Log log);
};

Log::Log()
{
    ;
}

//Funcion para ordenar por ip, fecha y hora
void sortByIp(DoublyLinkedList<Log>* list)
{
    quickSort(list,0,list->getSize()-1);
}

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
    //Generamos la ip modificada para poder comparar de mejor manera
    this->ip_modificada = modificarIp(ip);
    this->key_ip_modificada = this->ip_modificada + key;
}

bool Log::operator<(Log log)
{
    return key < log.key;
}

bool Log::compare(Log log)
{
    return key_ip_modificada < log.key_ip_modificada;
}

bool Log::operator!=(Log log)
{
    return key_ip_modificada != log.key_ip_modificada;
}

ostream& operator<<(ostream& os, Log log) {
    os << "Log: " << log.month << " " << log.day << " " << log.year << " " << log.time << " " << log.ip << " " << log.message << " " << log.key << " " << log.key_ip_modificada << endl;
    return os;
}

void swap(DoublyLinkedList<Log>& lista_a_ordenar, DNode<Log>* j, DNode<Log>* i)
{
    if (i->data != j->data)
    {
        Log aux = i->data;
        i->data = j->data;
        j->data = aux;
    }

}

DNode<Log>* getNode(DoublyLinkedList<Log>& lista, int index)
{
    DNode<Log>* aux = lista.getHead();
    int auxIndex = 0;

    while(aux->next != nullptr && auxIndex < index)
    {
        aux = aux->next;
        auxIndex++;
    }

    return aux;
}

/* DNode<Log>* getNodeBinarySearch(DoublyLinkedList<Log>& lista, int index, DNode<Log>* prev, string valor)
{
    DNode<Log>* aux;

    if(prev == nullptr)
    {
        aux = lista.getHead();
    }
    else
    {
        aux = prev;
    }

    int auxIndex = 0;

    while(aux->next != nullptr && auxIndex <= index)
    {
        if(aux->data > valor)
        {

        }
        else
        {

        }
        aux = aux->next;
        auxIndex++;
    }

    return aux;
} */

int getPivot(DoublyLinkedList<Log>& list, int left, int right)
{
    //Definir el índice del pivote
    int pivot = right;
    //Definir el índice auxiliar igual a left-1
    int auxIndex = left - 1;

    DNode<Log>* auxNodeIndex;
    DNode<Log>* auxNodePivot = getNode(list, pivot);
    DNode<Log>* auxNodeAuxIndex;

    //Recorremos la lista desde left hasta right - 1
    for (int index = left; index < right; index++)
    {
        auxNodeIndex = getNode(list, index);

        //Comparamos los valores de index contra el pivote
        if (auxNodeIndex->data.compare(auxNodePivot->data))
        {
            //Incrementamos auxIndex en 1
            auxIndex++;

            auxNodeAuxIndex = getNode(list, auxIndex);

            //Intercambiamos index con auxIndex
            swap(list, auxNodeIndex, auxNodeAuxIndex);
        }
    }
    //Incrementamos auxIndex en 1
    auxIndex++;

    auxNodeAuxIndex = getNode(list, auxIndex);

    //Intercambiamos el índice auxiliar con el pivot
    swap(list, auxNodeAuxIndex, auxNodePivot);

    return auxIndex;
}

void quickSort(DoublyLinkedList<Log>& list, int left, int right)
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

void printInFileAsc(DoublyLinkedList<Log>& lista, string nombre, string lower, string upper)
{
    string str = "C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence2/";
    nombre = str + nombre;
    //Inicializamos el archivo de salida para imprimir los registros ordenados
    ofstream outFile(nombre);

    outFile << "Mostrando ip's desde " << lower << " hasta " << upper << endl;
    //Ciclo for para imprimir cada registro en el archivo
    DNode<Log>* aux = lista.getHead();
    while(aux != nullptr)
    {
        outFile << aux->data;
        aux = aux->next;
    }
}

void printInFileDesc(DoublyLinkedList<Log>& lista, string nombre, string lower, string upper)
{
    string str = "C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence2/";
    nombre = str + nombre;
    //Inicializamos el archivo de salida para imprimir los registros ordenados
    ofstream outFile(nombre);
    outFile << "Mostrando ip's desde " << upper << " hasta " << lower << endl;
    //Ciclo for para imprimir cada registro en el archivo
    DNode<Log>* aux = lista.getTail();
    while(aux != nullptr)
    {
        outFile << aux->data;
        aux = aux->prev;
    }
}

void printWithRange(DoublyLinkedList<Log> lista, DNode<Log>* lowerBound, DNode<Log>* upperBound, string lowerOriginal, string upperOriginal)
{
    //Inicializamos el archivo de salida para imprimir los registros del rango de busqueda
    string strAsc = "iprange608-a.out";
    string strDesc = "iprange608-d.out";

    DoublyLinkedList<Log> copia;
    DNode<Log>* aux = lowerBound;
    cout << "Upper: " << upperBound->data << endl;
    cout << "Lower: " << lowerBound->data << endl << endl;

    while(aux != nullptr && aux != upperBound->next)
    {
        cout << aux->data << endl;
        copia.addLast(aux->data);
        aux = aux->next;
    }                                                                                                                   

    printInFileAsc(copia, strAsc, lowerOriginal, upperOriginal);
    printInFileDesc(copia, strDesc, lowerOriginal, upperOriginal);
}

void leerArchivodeLogs(string nombre, DoublyLinkedList<Log>& logs)
{
    // Archivo de entrada
    ifstream fileIn(nombre);
    // Archivo de salida
    // ofstream fileOut("output608.out");
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
        logs.addLast(log);

        // Incrementamos el contador de registros
        cont++;
    }

    //Mandamos a ordenar los registros
    logs.sort();
}

/* DNode<Log>* busquedaBinaria(DoublyLinkedList<Log> lista, string valor_a_encontrar, bool esMayor)
{
    if(esMayor)
    {
        cout << "Encontrando lower ... "<< endl;
    }
    else
    {
        cout << "Encontrando upper ... " << endl;
    }

    valor_a_encontrar = modificarIp(valor_a_encontrar);

    //Inicializamos left, mid y right
    int left = 0, right = lista.getSize() - 1, mid = 0, auxIndex = 0;

    DNode<Log>* auxLeft = lista.getHead();
    DNode<Log>* auxRight = lista.getTail();
    DNode<Log>* auxMid;

    //Mientras left sea menor o igual que right
    while (left <= right)
    {
        //Cálculo para encontrar mid
        mid = left + (right - left) * 0.5;

        if(auxIndex == 0)
        {
            cout << "Buscando ... " << endl;
            auxMid = getNodeBinarySearch(lista, mid, nullptr, valor_a_encontrar);
            cout << auxMid->data << endl;
        }
        else
        {
            cout << "Buscando ... " << endl;
            auxMid = getNodeBinarySearch(lista, mid, auxMid, valor_a_encontrar);
            cout << auxMid->data << endl;
        }

        //Si el valor a encontrar se encuentra en mid salirse del ciclo
        if (auxMid->data.ip_modificada == valor_a_encontrar)
        {
            break;
        }
        //Si el valor a encontrar es mayor que mid, cambiar left a 1 mas que mid
        else if (auxMid->data.ip_modificada <= valor_a_encontrar)
        {
            left = mid + 1;
        }
        //Si el valor a encontrar es menor que mid, cambiar right a 1 menos que mid
        else if (auxMid->data.ip_modificada >= valor_a_encontrar)
        {
            right = mid - 1;
        }

        auxIndex++:
    }

    //Verificar si esta busqueda es la de la fecha superior 
    if (esMayor)
    {
        //Si es la fecha superior, verifica si mid es mayor al valor a encontrar y lo reduce en 1
        if (auxMid->data.ip_modificada > valor_a_encontrar)
        {
            //mid--;
            while(auxMid->prev != nullptr && auxMid->prev->data.ip_modificada == auxMid->data.ip_modificada)
            {
                auxMid = auxMid->prev;
            }

        }
    }
    else
    {
        //Si es la fecha inferior, verifica si mid es menor al valor a encontrar y lo aumenta en 1
        if (auxMid->data.ip_modificada < valor_a_encontrar)
        {
            //mid++;
            while(auxMid->next != nullptr && auxMid->next->data.ip_modificada == auxMid->data.ip_modificada)
            {
                auxMid = auxMid->next;
            }
        }
    }

    //Se regresa auxMid, que es el nodo donde empieza o termina el rango, dependiendo de la busqueda
    cout << "Regresando " << auxMid->data << endl;
    return auxMid;
}
*/

DNode<Log>* busquedaSecuencial(DoublyLinkedList<Log> lista, string valor_a_encontrar, bool esMayor)
{
    DNode<Log>* aux;

    if(esMayor)
    {
        //cout << "Buscando upper ... " << endl;
        aux = lista.getHead();
        while(aux->next != nullptr && aux->data.ip_modificada <= valor_a_encontrar)
        {
           // cout << aux->data.ip_modificada <<" menor que " << valor_a_encontrar << endl;
            aux = aux->next;
        }
        //cout << "Del ciclo en el mayor, se salio con ip " << aux->data.ip << endl;

        //cout << "Checando si aux->data.ip_modificada " << aux->data.ip_modificada << " a valor a encontrar " << valor_a_encontrar << endl;
        if(aux->next != nullptr || aux->data.ip_modificada > valor_a_encontrar)
        {
            aux = aux->prev;
        }
    }
    else
    {
        //cout << "Buscando lower ... " << endl;
        aux = lista.getTail();
        while(aux->prev != nullptr && aux->data.ip_modificada >= valor_a_encontrar)
        {
            //cout << aux->data.ip_modificada <<" mayor que " << valor_a_encontrar << endl;
            aux = aux->prev;
        }
        //cout << "Del ciclo en el menor, se salio con ip " << aux->data.ip << endl;
        //cout << "Checando si aux->data.ip_modificada " << aux->data.ip_modificada << " a valor a encontrar " << valor_a_encontrar << endl;
        if(aux->prev != nullptr || aux->data.ip_modificada < valor_a_encontrar)
        {
            aux = aux->next;
        }
    }
    
    //cout << "Regresando " << aux->data.ip_modificada << endl;
    return aux;
}

int main()
{
    /* DoublyLinkedList<Log> Logs1;

    leerArchivodeLogs("C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence2/log608-2.txt", Logs1);

    Logs1.print("asc"); */

    //cout <<"Primera key "<< log1 < log2 << endl;

    //cout <<"Segunda key "<< log1.compare(log2) ? cout << "Log 1 menor en ip, fecha y hora" << endl : cout << "Log 2 menor en ip, fecha y hora" << endl;
    
    //Inicializar el vector para guardar los registros
    DoublyLinkedList<Log> Logs;
    //Mandar a llamar la función para leer el archivo de registros y guardarlo en Logs
    leerArchivodeLogs("C:/Users/r1agu/Repositorios/C.MTY.TC1031.608.2313.A01285921/Evidences/Evidence2/log608-2.txt", Logs);

    if (Logs.isEmpty())
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
        int entrada;

        while (!salir)
        {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "                                SISTEMA DE REGISTROS " << endl;
            cout << "------------------------------------------------------------------------------------------------------------------" << endl << endl;
            cout << "                       Eliga alguna de las siguientes opciones" << endl << endl;
            cout << "                         1) Ordena los datos por fecha y hora" << endl;
            cout << "                       2) Ordena los datos por ip, fecha y hora." << endl; 
            cout << "                           3) Búsqueda por rango de ip's" << endl;
            cout << "                       4) Mostrar número de ip's por mes y año" << endl;
            cout << "                                     0) Salir" << endl << endl; 
            cout << "                               Ingresa la opción: ";
            cin >> entrada;
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------------" << endl << endl;
            switch(entrada)
            {
                case 1:
                    printInFileAsc(Logs, "output608-1.out", Logs.getHead()->data.ip, Logs.getTail()->data.ip);
                break;
                case 2:
                    quickSort(Logs,0,Logs.getSize()-1);
                    printInFileAsc(Logs, "output608-2.out", Logs.getHead()->data.ip, Logs.getTail()->data.ip);
                break;
                case 3:
                    {
                    /* Pide al usuario un rango de ips
                        Busca todas las ips que se encuentren en el rango solicitado.
                        Guardo los registros dentro de ese rango en una DoublyLinkedList
                        Genera un archivo de salida llamado iprange602-a.out con los datos de la búsqueda en orden ascendente
                        Genera un archivo de salida llamado iprange602-d.out con los datos de la búsqueda en orden descendente */
                    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "                                   Buscar desde:" << endl; 
                    cout << "                             Formato (10.14.XXX.XXX)"<< endl << endl;
                    cout << "                            Ip Inferior: "; 
                    cin >> lowerBound;
                    cout << endl << endl;
                    cout << "                            Ip Superior: "; 
                    cin >> upperBound;
                    cout << endl << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    quickSort(Logs,0,Logs.getSize()-1);
                    string lowerBound_m = modificarIp(lowerBound);
                    string upperBound_m = modificarIp(upperBound);
                    DNode<Log>* auxLowerBound = busquedaSecuencial(Logs, lowerBound_m, false);
                    DNode<Log>* auxUpperBound = busquedaSecuencial(Logs, upperBound_m, true);
                    printWithRange(Logs, auxLowerBound, auxUpperBound, lowerBound, upperBound);
                    }
                break;
                case 4:
                    {
                        //Inicializar un array con los meses como vienen en el archivo txt, junto a su conversión en digitos
                        string months[24] = {"Enero","01","Febrero","02","Marzo","03","Abril","04","Mayo","05","Junio","06","Julio","07","Agosto","08","Septiembre","09","Octube","10","Noviembre","11","Diciembre","12" };
                        vector<tuple<string,int,string>> registroIps;
                        tuple<string,int,string> mes_y_numIps_y_año;
                        string mes;
                        int numMes = 1;
                        int num = 1;

                        Logs.sort();

                        mes = Logs.getHead()->data.key.substr(2,2);
                        DNode<Log>* aux = Logs.getHead();

                        while(aux != nullptr)
                        {
                            if(aux->next == nullptr)
                            {
                                //Bandera para poder salir del ciclo
                                bool mesEncontrado = false;
                                //Iterador para el ciclo while
                                int iter = 1;

                                while (!mesEncontrado)
                                {
                                    //Mientras no se encuentre el mes compara el mes con cada string de mes en el array
                                    switch (aux->data.key.substr(2,2).compare(months[iter]))
                                    {
                                    case 0:
                                        //Si se encuentra la comparación en esta iteración cambia la bandera para salir del ciclo
                                        mesEncontrado = true;
                                        //Cambiamos el valor de la variable month al dígito correspondiente del mes, que esta en el índice siguiente
                                        mes = months[iter-1];
                                        break;

                                    default:
                                        //Si no se encuentra el mes en esta iteración aumenta el iterador en 2 para pasar al siguiente mes sin pasar por los digitos
                                        iter = iter + 2;
                                    }
                                }
                                
                                mes_y_numIps_y_año = make_tuple(mes, num,aux->data.key.substr(0,2));
                                registroIps.push_back(mes_y_numIps_y_año);
                            }
                            else if(aux->next->data.key.substr(2,2) != aux->data.key.substr(2,2))
                            {
                                 //Bandera para poder salir del ciclo
                                bool mesEncontrado = false;
                                //Iterador para el ciclo while
                                int iter = 1;

                                while (!mesEncontrado)
                                {
                                    //Mientras no se encuentre el mes compara el mes con cada string de mes en el array
                                    switch (aux->data.key.substr(2,2).compare(months[iter]))
                                    {
                                    case 0:
                                        //Si se encuentra la comparación en esta iteración cambia la bandera para salir del ciclo
                                        mesEncontrado = true;
                                        //Cambiamos el valor de la variable month al dígito correspondiente del mes, que esta en el índice siguiente
                                        mes = months[iter-1];
                                        break;

                                    default:
                                        //Si no se encuentra el mes en esta iteración aumenta el iterador en 2 para pasar al siguiente mes sin pasar por los digitos
                                        iter = iter + 2;
                                    }
                                }
                                
                                mes_y_numIps_y_año = make_tuple(mes, num,aux->data.key.substr(0,2));
                                registroIps.push_back(mes_y_numIps_y_año);
                                num = 0;
                            }
                            if(aux->next != nullptr && aux->data.ip_modificada != aux->next->data.ip_modificada)
                            {
                                num++;
                            }
                            aux = aux->next;
                        }

                        int acumPorAño;
                        int i = 0;
                        while(i < registroIps.size())
                        {
                            cout << "                       En el mes de " << get<0>(registroIps[i]) << " se registraron " <<  get<1>(registroIps[i]) << " ips." << endl;
                            acumPorAño = acumPorAño + get<1>(registroIps[i]);
                            if(i > 0)
                            {
                                if(get<2>(registroIps[i+1]) != get<2>(registroIps[i]))
                                {
                                    cout << "                       En el año 20" << get<2>(registroIps[i-1]) << " se registraron " << acumPorAño << " ips." << endl;
                                    acumPorAño = 0;
                                    cout << endl;
                                }
                            }
                            i++;
                        }
                        cout << endl;
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    }
                break;
                case 0:
                    salir = true;
                break;
                default:
                    cout << "                                           Opción no válida" << endl;
                    cout << "------------------------------------------------------------------------------------------------------------------" << endl << endl;
                break;
            }
        }
    }
}
#include <iostream>
using namespace std;

class CuentaBancaria {
private:
    double saldo;
    bool activa;
    bool bloqueada;
    int intentosFallidos;

public:
    // Constructor por defecto
    CuentaBancaria() {
        saldo = 1000; // Saldo inicial
        activa = true;
        bloqueada = false;
        intentosFallidos = 0;
    }

 
    void depositar(double monto) {
        if (!activa) {
            cout << "No se puede depositar en una cuenta inactiva." << endl;
            return;
        }
        if (bloqueada) {
            cout << "Cuenta bloqueada. No se pueden realizar operaciones." << endl;
            return;
        }
        saldo += monto;
        cout << "Deposito exitoso. Saldo actual: " << saldo << endl;
    }

    void retirar(double monto) {
        if (bloqueada) {
            cout << "Cuenta bloqueada. No se pueden realizar operaciones." << endl;
            return;
        }
        if (monto > saldo) {
            cout << "Fondos insuficientes." << endl;
            intentosFallidos++;
            if (intentosFallidos >= 3) {
                bloqueada = true;
                cout << "Cuenta bloqueada por intentos fallidos de retiro." << endl;
            }
            return;
        }
        saldo -= monto;
        intentosFallidos = 0;
        cout << "Retiro exitoso. Saldo actual: " << saldo << endl;
        if (saldo < 200) {
            cout << "ADVERTENCIA: Su saldo es bajo." << endl;
        }
    }

    void transferir(CuentaBancaria& destino, double monto) {
        if (bloqueada || destino.bloqueada) {
            cout << "Una de las cuentas esta bloqueada. No se puede realizar la transferencia." << endl;
            return;
        }
        if (monto > saldo) {
            cout << "Fondos insuficientes para la transferencia." << endl;
            return;
        }
        double penalizacion = monto * 0.02; // Penalización del 2%
        saldo -= (monto + penalizacion);
        destino.saldo += monto;
        cout << "Transferencia exitosa. Se aplico una penalizacion de " << penalizacion << ". Saldo actual: " << saldo << endl;
    }

    void mostrarSaldo() {
        cout << "Su saldo es: " << saldo << (bloqueada ? " (Cuenta bloqueada)" : "") << endl;
    }
};


int main() {
    int opcion;
    double monto;
    CuentaBancaria cuentas[30];

    do {
        cout << "\nSeleccione una opcion: " << endl;
        cout << "1. Depositar" << endl;
        cout << "2. Retirar" << endl;
        cout << "3. Consultar saldo" << endl;
        cout << "4. Transferir" << endl;
        cout << "5. Salir" << endl;
        cin >> opcion;

        if (opcion == 5) break;

        int cuentaSeleccionada;
        cout << "Ingrese el numero de cuenta (0-29): ";
        cin >> cuentaSeleccionada;

        if (cuentaSeleccionada < 0 || cuentaSeleccionada >= 30) {
            cout << "Numero de cuenta invalido. Intente de nuevo." << endl;
            continue;
        }

        switch (opcion) {
        case 1: // Depositar
            cout << "Ingrese monto a depositar: ";
            cin >> monto;
            cuentas[cuentaSeleccionada].depositar(monto);
            break;
        case 2: // Retirar
            cout << "Ingrese el monto a retirar: ";
            cin >> monto;
            cuentas[cuentaSeleccionada].retirar(monto);
            break;
        case 3: // Consultar saldo
            cuentas[cuentaSeleccionada].mostrarSaldo();
            break;
        case 4: // Transferir
            int cuentaDestino;
            cout << "Ingrese numero de cuenta destino (0-29): ";
            cin >> cuentaDestino;
            if (cuentaDestino < 0 || cuentaDestino >= 30 || cuentaDestino == cuentaSeleccionada) {
                cout << "Numero de cuenta destino invalido." << endl;
                continue;
            }
            cout << "Ingrese monto a transferir: ";
            cin >> monto;
            cuentas[cuentaSeleccionada].transferir(cuentas[cuentaDestino], monto);
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            break;
        }

    } while (opcion != 5);

    cout << "Gracias por usar el sistema bancario!" << endl;
    return 0;
}

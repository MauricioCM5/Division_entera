//Mauricio Colque Morales - CCOMP3-1
#include<bitset>
#include<iostream>
#include<stdlib.h>
using namespace std;

const int num_bits = 8;

// DETALLES

//Funciones: suma, resta, cambio de signo, shift a la izquierda y división
/*
num_bits : determina el tamaño de bites a ocupar por los bitsets y es modificable.

Se requiere entrada de dividendo y divisor, se obtienen resultados parciales 
y el resultado final. 
*/

//Desplazamiento a la izquierda
void shifter(bitset<num_bits>*temp){
	*temp = ((*temp)<<1);
}

//Suma
bitset<num_bits> suma(bitset<num_bits> &a, bitset<num_bits> &b){
	bitset<num_bits>res;
	bool acarreo = false; 

	for(int i = 0; i < num_bits; i++){
		if((a[i] | b[i]) == 0){
			res[i] = acarreo;
			acarreo = 0; 
		}
		else if((a[i] ^ b[i]) == 1) res[i] = true ^ acarreo; 
		else if((a[i] & b[i]) == 1){
			 res[i] = acarreo;
			 acarreo = true;
		}	
	}
	return res;
}


//Cambio de signo
bitset<num_bits> cambio_de_signo(bitset<num_bits>temp){
	bitset<num_bits>bit_extra("00000001");
	bitset<num_bits>cambiado = suma(temp.flip(), bit_extra);
	return cambiado;
}

//Resta
bitset<num_bits> resta(bitset<num_bits> &a, bitset<num_bits> &b){
	bitset<num_bits> temp = cambio_de_signo(b);
	return suma(a, temp);
}


//División en sí
void division(bitset<num_bits>m, bitset<num_bits>q, int bits){
	bitset<8>A; //Se llena automaticamente de 0
	bitset<8>m_inverso;
	
	cout << "Divisor: \n";
	cout << "en binario: " << q << "\t en entero: " << q.to_ulong() << "\n";;
	
	cout << "Dividendo: \n";
	cout << "en binario: " << m << "\t en entero: " << m.to_ulong() << "\n";

	int contador = bits; 
	
	cout << "\n________________________Resultados parcial por cada iteración: \n" ;
	while(contador != 0){
		
		shifter(&A);
		A[0] = q[num_bits-1];
		shifter(&q);
		
		A = resta(A, m);
		
		if(A[num_bits-1] == 1){
			q[0] = 0;
			A = suma(A, m);
		}
		else{ q[0] = 1; }

		contador--;
		
		
		cout << num_bits - contador << ". ";
		cout << "\n-------\nCociente: \n";
		cout << "en binario: " << q << "\t en entero: " << q.to_ulong() << "\n";;
	
		cout << "Residuo: \n";
		cout << "en binario: " << A << "\t en entero: " << A.to_ulong() << "\n";
		
		
		
	
	}

	cout << "\n_____________RESULTADOS________\nCociente: \n";
	cout << "en binario: " << q << "\t en entero: " << q.to_ulong() << "\n";;
	
	cout << "Residuo: \n";
	cout << "en binario: " << A << "\t en entero: " << A.to_ulong() << "\n";
	
}

int main(){
	bitset<num_bits>num1(186);
	bitset<num_bits>num2(3);
		

	cout << "Prueba de funcionamiento propia: \n";
	division(num2, num1, num_bits);
	
	cout << "\n\nPruebas con entrada: \n";
	
	
	
	
	bitset<num_bits>divisor; //divisor
	bitset<num_bits>dividendo; //dividendo
	

	int temp;
	
	while(true){
		cout << "Introduzca el divisor: " ; cin >> temp;
		bitset<num_bits> x(temp);
		divisor = x;
		cout << "Introduzca el dividendo: "; cin >> temp;
		bitset<num_bits> y(temp);
		dividendo = y;
		
		division(dividendo, divisor, num_bits);
		
		cout << "\n\n";
		
	}
	
	system("pause");
	return 0;
}

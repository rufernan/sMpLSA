#include "plsa.h"
#include "parameters.h"

//////////////////////////////////////////////////////////////////////////////////
// Programa Principal -                                                         //
//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	
	// Uso del programa
	if(argc!=12){
		cout<<endl<<"usage: ./pLSA file_pwd ndocs nwords format ntopics lambda_pzd lambda_pwz fix_iters dir_out init_pzd_hpc init_pwz_hpc"<<endl<<endl;
		exit(0);
	}
	
	// Parametros del programa
	char *file_pwd=argv[1];
	int ndocs=atoi(argv[2]);
	int nwords=atoi(argv[3]);
	int format=atoi(argv[4]);
	int ntopics=atoi(argv[5]);
	double lambda_pzd=atof(argv[6]); // sparse_regularisation over pzd (lambda=0 regular plsa)
	double lambda_pwz=atof(argv[7]); // sparse_regularisation over pwz (lambda=0 regular plsa)
	int fix_iters=atof(argv[8]); // efficiency mode fixing the number of EM iters (fix_iters=0 regular mode)
	char *dir_out=argv[9];
	char *init_pzd_hpc=argv[10]; // initialization for pzd ('random','uniform' of the name og the file to load)
	char *init_pwz_hpc=argv[11]; // initialization for pwz

	cout<<"## PLSA Algorithm ##"<<endl;
	
	// Matriz p(w|d)
	Mat  *pwd; pwd = loadMat(file_pwd, format, ndocs, nwords);
	
	// Ejecutamos pLSA
	plsaEM(pwd, ntopics, lambda_pzd, lambda_pwz, fix_iters, init_pzd_hpc, init_pwz_hpc);
	
	// Guardamos los parametros (pwz, pzd) en formato HPC y HPB en el directorio de salida
	saveParameters(dir_out);
	
	cout<<"## FIN ##"<<endl;
	
}
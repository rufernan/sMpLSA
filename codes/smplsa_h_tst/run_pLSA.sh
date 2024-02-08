#!/bin/bash

# Mostramos uso y definimos parametros por defecto
if [ $# -lt 5 ]; then
	echo "Programa BASH para ejecutar pLSA"
	echo " ./run_pLSA file_pwd format file_voc ntopics dir_out [fix_iters] [lambda_pzd] [lambda_pwd] [init_pzd_hpc] [init_pwz_hpc]"
	exit
elif [ $# -eq 5 ]; then
	FIX_ITERS=0
	LAMBDA_pzd=0
	LAMBDA_pwz=0
	INIT_PZD_HPC="rand"
	INIT_PWZ_HPC="rand"
elif [ $# -eq 6 ]; then
	FIX_ITERS=$6
	LAMBDA_pzd=0
	LAMBDA_pwz=0
	INIT_PZD_HPC="rand"
	INIT_PWZ_HPC="rand"
elif [ $# -eq 7 ]; then
	FIX_ITERS=$6
	LAMBDA_pzd=$7
	LAMBDA_pwz=0
	INIT_PZD_HPC="rand"
	INIT_PWZ_HPC="rand"
elif [ $# -eq 8 ]; then
	FIX_ITERS=$6
	LAMBDA_pzd=$7
	LAMBDA_pwz=$8
	INIT_PZD_HPC="rand"
	INIT_PWZ_HPC="rand"
elif [ $# -eq 8 ]; then
	FIX_ITERS=$6
	LAMBDA_pzd=$7
	LAMBDA_pwz=$8
	INIT_PZD_HPC=$9
	INIT_PWZ_HPC="rand"
else
	FIX_ITERS=$6
	LAMBDA_pzd=$7
	LAMBDA_pwz=$8
	INIT_PZD_HPC=$9
	INIT_PWZ_HPC=${10}
fi


# ///////////////////////
# Programas de ejecucion
PLSA="./pLSA" # 11_plsa_reg_double_cvmat_tbb_FIX_INI
# ./pLSA file_pwd ndocs nwords format ntopics lambda_pzd lambda_pwz fix_iters dir_out init_pwz_hpc
# ///////////////////////

# ///////////////////
# Fichero de entrada con la matrix pwd
PWD=$1
# Numero de documentos
ND=`wc -l $1 | cut -d " " -f 1`
# Formato (0->HPC, 1->HPB)
FORMAT=$2 
# Numero de palabras
NW=`wc -l $3 | cut -d " " -f 1`
# Numero de topicos
NT=$4
# Directorio de salida 
DIROUT=$5
# ///////////////////

# ////////////////
# Ejecutamos pLSA
$PLSA $PWD $ND $NW $FORMAT $NT $LAMBDA_pzd $LAMBDA_pwz $FIX_ITERS $DIROUT $INIT_PZD_HPC $INIT_PWZ_HPC
# ////////////////

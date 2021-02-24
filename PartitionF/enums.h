#ifndef ENUMS
#define ENUMS

//Partition
#define NBNOTESLIGNEMAX 20

//Silence
enum Silences{ZERO, PAUSE, DEMIPAUSE, SOUPIR, DEMISOUPIR, QUARTSOUPIR};

//Nuance
enum Nuances{NON, PPP, PP, P, MP, MF, F, FF, FFF}; //PIAPIAPIANO, PIAPIANO, PIANO, MEZZO PIANO, MEZZO FORTE, FORTE, FOFORTE, FOFOFORTE ;)

#define DBPPP 40
#define DBPP 50
#define DBP 60
#define DBMP 70
#define DBMF 80
#define DBF 90
#define DBFF 100
#define DBFFF 110

//Note
enum Hauteurs{RIEN, DO, RE, MI, FA, SOL, LA, SI};
enum TypeN{NUL, RONDE, BLANCHE, NOIRE, CROCHE, DCROCHE};

#define FDO 65.41
#define FDOD 69.3
#define FRE 73.42
#define FRED 77.78
#define FMI 82.41
#define FFA 87.31
#define FFAD 92.5
#define FSOL 98
#define FSOLD 103.83
#define FLA 110
#define FLAD 116.54
#define FSI 123.47

//Cle
enum Type{AUCUN, SOLC, FA3, FA4, UT1, UT2, UT3, UT4};


#endif // ENUMS

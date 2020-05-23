
/*

       +        M]    M] 
     n U n      MM]  MM]  MMMMM]  M]   M]  MMMMM]  MMMMMM]   MMMMMM] M]    M]
    X*X*X*X     M]M]M]M] M]    M] MM]  M] M]    M] M]    M] M]       M]    M]
   X X* *X*X    M] M] M] M]    M] M]M] M] MMMMMMM] MMMMMM]  M]       MMMMMMM]
    X*X*X*X     M]    M] M]    M] M] M]M] M]    M] M]    M] M]       M]    M]
    0101010     M]    M]  MMMMM]  M]  MM] M]    M] M]     M] MMMMMM] M]    M]
---------------------------------------------- sistema de xadrez versao 1.0 ----

  PROJETO FINAL DO CURSO DE BACHARELADO EM INFORMATICA, UNICENP, CURITIBA
  COPYRIGHT (c) 2000 MARVIN OLIVER SCHNEIDER

--------------------------------------------------------------------------------


*/



///////////////////////////////////////////////////////
// Arquivos incluidos                                //
///////////////////////////////////////////////////////

#include <stdio.h>              // bibliotecas standard
#include <stdlib.h>             // "
#include <ctype.h>              
#include <console.h>    // biblioteca para aplicacao console
						// feita por Prof. Fábio Vinicius Binder
#include <conio.h>

///////////////////////////////////////////////////////
// Constantes globais                                //
///////////////////////////////////////////////////////

const int LIGADO = 1;
const int DESLIGADO = 0;

const int REI = 0;              // codigos das figuras
const int RAINHA = 1;
const int TORRE = 2;
const int CAVALO = 3;
const int BISPO = 4;
const int PEAO = 5;

const int INATIVO = 99; // codigo para uma pecas nao existente -- nao abaixar este valor!!
const int INVALIDO = -99;

const int BRANCO = 0;   // codigos para as cores
const int PRETO  = 1;

const int JOGADOR = 0;  // codigos para destinguir jogador e computador
const int COMPUTADOR = 1;

//const int FALSE = 0;  // utilizado para variaveis booleanas
//const int TRUE = 1;

const int NORMAL               = 0;     // formas de ataque
const int EN_PASSENT           = 1;
const int ROQUE                = 2;
const int PEAO_AVANCADO_RAINHA = 3;
const int PEAO_AVANCADO_TORRE  = 4;
const int PEAO_AVANCADO_CAVALO = 5;
const int PEAO_AVANCADO_BISPO  = 6;

const int ABERTURA            = 0; // fases do jogo para contabilizar pontos
const int BATALHA_CENTRAL     = 1;
const int BATALHA_ESTRATEGICA = 2;
const int FINALIZACAO         = 3;

const int MATE                = 55;  // devolucao do analisador de mate
const int EMPATE              = 8;

const int MATE_OFENSIVO_1		= 0;
const int MATE_OFENSIVO_2		= 1;
const int MATE_OFENSIVO_3		= 2;
const int MATE_DEFENSIVO_1		= 3;
const int MATE_DEFENSIVO_2		= 4;
const int ANTI_EMPATE			= 5;
const int EXECUCAO				= 6;
const int ANTI_ATAQUE_DUPLO		= 7;
const int ANTI_BLOQUEIO			= 8;
const int ANTI_ABRE_PORTAS		= 9;
const int ATAQUE				= 10;
const int ATAQUE_DUPLO			= 11;
const int BLOQUEIO				= 12;
const int DEFESA				= 13;
const int INFLUENCIA_CENTRAL	= 14;
const int CONTROLE_LINHAS		= 15;
const int PROXIMIDADE_REI		= 16;
const int LIBERDADE_MOVIMENTO	= 17;

//const int RECURSIVIDADE		= 18;

const int PORTUGUES = 0;
const int ALEMAO    = 1;
const int INGLES    = 2;

// caracteres para poder fazer um tabuleiro "limpo" (codigo Ascii standard)

const char cds = char(201); //canto direito superior;
const char cei = char(188); //canto direito inferior;
const char ho  = char(205); //horizontal
const char cr  = char(206); //cruz 
const char ve  = char(186); //vertical 
const char vhe = char(185); //vertical com linha horizontal na esquerda
const char vhd = char(204); //vertical com linha horizontal na direita
const char cdi = char(200); //canto direito inferior
const char ces = char(187); //canto esquerdo superior
const char hva = char(203); //horizontal com linha vertical em cima
const char hve = char(202); //horizontal com linha vertical em baixo 

const char cds1 = char(218); //canto direito superior;
const char cei1 = char(217); //canto direito inferior;
const char ho1  = char(196); //horizontal
const char cr1  = char(197); //cruz
const char ve1  = char(179); //vertical
const char vhe1 = char(180); //vertical com linha horizontal na esquerda
const char vhd1 = char(195); //vertical com linha horizontal na direita
const char cdi1 = char(192); //canto direito inferior
const char ces1 = char(191); //canto esquerdo superior
const char hva1 = char(194); //horizontal com linha vertical em cima
const char hve1 = char(193); //horizontal com linha vertical em baixo 


const char h1 = char(196);      // linha para o titulo

const char s1 = char(176); // sombra  1  - a mais fraca
const char s2 = char(177); // sombra  2  - um pouco mais forte
const char s3 = char(178); // sombra  3  - a sombra mais forte
const char s4 = char(219); // "sombra 4" - um campo solido

const char c1 = char(127); // char 1 - para coroa
const char c2 = 'O'; // char(184) - (c) para coroa
const char c3 = 'o'; // char(207) - "explosao" para coroa

typedef int BOOL;       // variaveis booleanas

typedef struct _elemento_ponto {        // array de movimentos possiveis e pontos
   int x_orig[140], y_orig[140], x_dest[140], y_dest[140];
   long int score[140];
   int tipo[140], especiais[140];
   int cor[140];
   int pontos_pos;
   char analisador[17];
}EPONTOS;

typedef struct _figura2 {       // array de figuras atacantes
	int tipo[16], cor[16], x[16], y[16], tipo_rel[16];
}FIGURA2;

typedef struct _tresmelhores {  // array para calcular os tres melhores
	int mov[3];                                     // movimentos de uma jogada
}TRESMELHORES;

typedef struct _imagetabuleiro {
	int l[7][7];
}TABIMG;

typedef struct _menu {
	char *strg[3][150];
}MENU;

typedef struct _coordenadas {
   int x, y;
}COORD1;

typedef struct _movimento {
	int x1, y1, x2, y2;
}MOVIMENTO;

///////////////////////////////////////////////////////
// Variaveis globais                                 //
///////////////////////////////////////////////////////

int resultado; // erros das operações string

char novalinha; // para cin.get(novalinha)

int lingua, player;     // a lingua operacional (para toda a operacao) e o algoritmo

MENU frase;     // as frases operacionais (para toda a operacao)

void mark(int); // marcacao p/ testes

int algo[17];   // definicao do algoritmo

COORD1 mais[8];  // as 8 direcoes
COORD1 cmais[8]; // os oito pontos do cavalo

///////////////////////////////////////////////////////
// TECNICA: PROGRAMACAO ORIENTADA A OBJETOS          //
///////////////////////////////////////////////////////
// A seguir a estutura de classes:                   //
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Classe: PECA - Definicao                          //
///////////////////////////////////////////////////////

class peca {    // caracteristicas gerais de cada peca
	int x, y;
	int cor;
	int tipo;
	char ascii;
	char img;
public:
	void init(int,int,int,int,char);        // inicializacao de uma peca no tabuleiro
	void mpa(int);  // MPA = mostre peca ascii !!
	int coordenadas(int,int);       // checagem de uma pecas nas coordenadas
	void setloc(int,int);   // para definir o lugar de uma peca
	int devolve_tipo(void); // devolver o tipo da peca
	int devolve_cor(void);  // devolver a cor da peca
	int devolve_x(void);    // devolver a coordenada x da peca
	int devolve_y(void);    // devolver a coordenada y da peca
	void informe_valores(void);     // mostrar os valores da peca atual
};

// PECA - Metodos

int peca::coordenadas(int x_in, int y_in)       // eh a mesma peca?
{
	if(x==x_in && y==y_in) return 1;
	return 0;
}

void peca::init(int x_in, int y_in, int tipo_in, int cor_in, char img_in)
// 
// inicializacao da peca
//
{
	x=x_in;
	y=y_in;
	tipo=tipo_in;
	cor=cor_in;
	switch (tipo)
	{
		case REI: ascii=char(127); break;               // inicializacao automatica para o tabuleiro ascii
		case RAINHA: ascii='W'; break;
		case TORRE: ascii='T'; break;
		case CAVALO: ascii=char(20); break;
		case BISPO: ascii=char(186); break;
		case PEAO: ascii='i'; break;
		default: ascii='?';
	}
	img=img_in;     // imagem grafica por enquanto nao utilizada
}

void peca::mpa(int cor_in)      // mostrar o caracter ascii correspondente da peca
{
	
	if(cor==BRANCO && cor_in==TRUE) setcolor( FOREGROUND_YELLOW | BACKGROUND_DARKGRAY ); else
	  if(cor==BRANCO && cor_in==FALSE) setcolor( FOREGROUND_YELLOW | BACKGROUND_BLACK ); else
		  if(cor==PRETO && cor_in==TRUE) setcolor( FOREGROUND_LIGHTPURPLE | BACKGROUND_DARKGRAY ); else
			  setcolor( FOREGROUND_LIGHTPURPLE | BACKGROUND_BLACK );
	
	printf(" %c ",ascii);
	
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
}

void peca::setloc(int set_x, int set_y) // define o lugar da peca
{
	x=set_x;
	y=set_y;
}

int peca::devolve_tipo(void)    // tipo para cima
{
	return tipo;
}

int peca::devolve_cor(void)     // cor para cima
{
	return cor;
}

int peca::devolve_x(void)       // x para cima
{
	return x;
}

int peca::devolve_y(void)       // y para cima
{
	return y;
}

void peca::informe_valores(void) // somente para teste
								// mostrar todos os valores da peca
{
	printf("x:%i y:%i \n",x,y);
	printf("cor:%i\n",cor);
	printf("tipo:%i\n",tipo);
	printf("ascii:%c\n",ascii);
	printf("img:%s\n",img);
}

// a seguir a estrutura para simular o tabuleiro inteiro (array de objetos)

typedef struct _pecas{          // tipo para tratar com todas as pecas de uma tabuleiro
	peca p[32];                             // baseado no objeto "peca"
	BOOL roque_possivel_direito[2]; // guarda se o roque é ainda possivel para o lado direito para uma cor
	BOOL roque_possivel_esquerdo[2]; // guarda se o roque á ainda possivel para o lado esquerdo para uma cor
	int peao_duas_casas_para_a_frente;      // guarda a coluna se um peao foi movido 2 casas para a frente (para en_passent)
	MOVIMENTO ult;
	BOOL ataque;
}PECAS;

///////////////////////////////////////////////////////
// Classe: CONSOLE - Definicao                       //
///////////////////////////////////////////////////////

// ROTINAS RELACIONADAS A CONSOLE (IO)

class console {
public:
	void tut(void);
	void sob(void);
	void aj(void);
	void menu_ajuda(int);
	void linha(int);
	void titulo(void);
	void titulo_completo(void);
	void sobre(void);
	void tutorial(void);
	void ajuda(void);
	void figura(int);
	void init_frases(void);
	int menu_vertical(int,int,int);
	COORD1 menu_tabuleiro(int,PECAS*,int,int);
	void espere_tecla(void);
	PECAS leitura(PECAS);
	void gravacao(PECAS);
	void limpa_direita_tabuleiro(void);
	BOOL tem_certeza(void);
	void caixa_atencao(int,int,char*);
	void caixa_erro(int);
	void acusa_xeque(void);
	void acusa_mate(void);
	void acusa_empate(void);
	void acusa_desistencia(void);
	void escreve_menu_palido(int,int,int);
	void limpa_fundo(void);
	void in_frame(int,int,char*);
	void t(void);
	void flush_ascii(PECAS);
	void show_peca(int,int,int,PECAS);
	int convert(char);
};

void console::linha(int tamanho)
{
	int i;
	for(i=0;i<tamanho;i++)
		printf("%c",h1);
}

void console::titulo(void)
{
	init_frases();
	clrscr(FOREGROUND_WHITE | BACKGROUND_BLUE);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	gotoxy(0,0);
      printf("       %c      ",cr);
	  setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c    %c%c",s4,s3,s4,s3);
	setcolor( FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	gotoxy(0,1);
	printf("     %c %c %c    ",c1,c1,c1);
	setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c%c  %c%c%c  %c%c%c%c%c%c  %c%c   %c%c  %c%c%c%c%c%c  %c%c%c%c%c%c%c   %c%c%c%c%c%c%c %c%c    %c%c ",
		s4,s4,s3,s4,s4,s3,s4,s4,s4,s4,s4,s3,s4,s3,s4,s3,s4,s4,s4,s4,s4,s3,s4,s4,s4,s4,s4,s4,s3,s4,s4,s4,s4,s4,s4,s3,s4,s3,s4,s3);
	gotoxy(0,2);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	printf("    %c%c%c%c%c%c%c   ",c2,c3,c2,c3,c2,c3,c2);
	setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c%c%c%c%c%c%c %c%c    %c%c %c%c%c  %c%c %c%c    %c%c %c%c    %c%c %c%c       %c%c    %c%c ",
		s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3);
	gotoxy(0,3);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	printf("   %c %c%c %c%c%c%c  ",c2,c2,c3,c3,c2,c3,c2);
	setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c %c%c %c%c %c%c    %c%c %c%c%c%c %c%c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c  %c%c       %c%c%c%c%c%c%c%c ",
		s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s4,s4,s4,s4,s4,s4,s3,s4,s4,s4,s4,s4,s4,s3,s4,s3,s4,s4,s4,s4,s4,s4,s4,s3);
	gotoxy(0,4);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	printf("    %c%c%c%c%c%c%c   ",c2,c3,c2,c3,c2,c3,c2);
	setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c    %c%c %c%c    %c%c %c%c %c%c%c%c %c%c    %c%c %c%c    %c%c %c%c       %c%c    %c%c ",
		s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3);
	gotoxy(0,5);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	printf("    %c%c%c%c%c%c%c   ",s4,s4,s4,s4,s4,s4,s4);
	setcolor(FOREGROUND_LIGHTBLUE | BACKGROUND_BLUE);
	printf("  %c%c    %c%c  %c%c%c%c%c%c  %c%c  %c%c%c %c%c    %c%c %c%c     %c%c %c%c%c%c%c%c%c %c%c    %c%c ",
		s4,s3,s4,s3,s4,s4,s4,s4,s4,s3,s4,s3,s4,s4,s3,s4,s3,s4,s3,s4,s3,s4,s3,s4,s4,s4,s4,s4,s4,s3,s4,s3,s4,s3);
	gotoxy(48,6);
	setcolor(FOREGROUND_LIGHTCYAN | BACKGROUND_BLUE);
	printf("%s",frase.strg[lingua][1]);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);       
	gotoxy(0,8);
}

void console::titulo_completo(void)
{
	int i;
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);       
	titulo();
	init_frases();
	gotoxy(0,7);
	setcolor(FOREGROUND_WHITE | BACKGROUND_CYAN);       
	printf("%c",cds1);
	for(i=0;i<78;i++) printf("%c",ho1);
	printf("%c",ces1);

	gotoxy(0,8);
	printf("%c",ve1);
	for(i=0;i<78;i++) printf(" ");
	printf("%c",ve1);

	gotoxy(0,9);
	printf("%c",ve1);
	for(i=0;i<78;i++) printf(" ");
	printf("%c",ve1);

	gotoxy(0,10);
	printf("%c",cdi1);
	for(i=0;i<78;i++) printf("%c",ho1);
	printf("%c",cei1);

	gotoxy(3,8);
	printf("%s",frase.strg[lingua][2]);

	gotoxy(4,9);
	printf("Copyright (c) 2000 Marvin Oliver Schneider");
	
	gotoxy(0,11);
	
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );

	printf("\n");
}

void console::limpa_fundo(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		gotoxy(0,21+i);
		for(j=0;j<79;j++) printf(" ");
	}
}

void console::tut(void)
{
	gotoxy(3,7);
	setcolor( FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE );
	switch(lingua)
	{
	case PORTUGUES : printf("[TUTORIAL]"); break;
	case ALEMAO : printf("[ANLEITUNG]"); break;
	case INGLES : printf("[TUTORIAL]"); break;
	}
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
	gotoxy(0,9);
}

void console::aj(void)
{
	gotoxy(3,7);
	setcolor( FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE );
	switch(lingua)
	{
	case PORTUGUES : printf("[AJUDA]"); break;
	case ALEMAO : printf("[HILFE]"); break;
	case INGLES : printf("[HELP]"); break;
	}
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
	gotoxy(0,9);
}

void console::sob(void)
{
	gotoxy(3,7);
	setcolor( FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE );
	switch(lingua)
	{
	case PORTUGUES : printf("[SOBRE]"); break;
	case ALEMAO : printf("[INFO]"); break;
	case INGLES : printf("[ABOUT]"); break;
	}
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
	gotoxy(0,9);
}


void console::espere_tecla(void)
{
	in_frame(INVALIDO,22,frase.strg[lingua][85]);
	while(kbhit()) getch();
	getch();
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
	gotoxy(3,23);
}

void console::sobre(void)
{
	titulo();
	switch(lingua)
	{
		case PORTUGUES: sob();  
						printf(" Este programa foi criado como um projeto final do curso de Bacharelado em\n");
					printf(" em Informatica no Centro Universitario Positivo (UnicenP) em Curitiba/PR. O\n");
					printf(" foco do projeto e a utilizacao de inteligencia artificial em jogos no exemplo\n");
					printf(" de um jogo de Xadrez.\n");
					printf(" \n");
					printf(" O presente projeto foi orientado pelo Prof.M.Sc. Fabio Vinicius Binder e a \n");
					printf(" equipe de professores orientadores para projetos finais de informatica da \n");
					printf(" Unicenp.\n");
					printf(" \n");
					printf(" Eu dedico este projeto a minha esposa Alessandra sem a qual eu nunca teria\n");
					printf(" tido a coragem de fazer o curso de informatica, um caminho que ninguem da  \n");
					printf(" minha familia ou dos meus parentes tinha ido ainda.\n");
					printf(" \n");
					espere_tecla();
					titulo();
					sob();
					printf(" Gostaria de agradecer ao meu pai Prof.Dr.Dr.h.c. Hans Joachim Schneider e \n");
					printf(" minha mae Hildegard Schneider para uma otima orientacao e uma vontade muito \n");
					printf(" grande de seguir a carreira universitaria.\n");
					printf("\n");
					printf(" Nao deu mais tempo de fazer uma interface melhor, mas mesmo assim espero de \n");
					printf(" ter feito um programa que consiga alcancar o seu objetivo de promover o jogo \n");
					printf(" Xadrez.\n");
					printf(" \n");
					printf(" O presente programa e Freeware, isto e, ele pode ser copiado sem restricoes \n");
					printf(" mas nao pode ser vendido nem alterado. O autor nao aceita nenhuma garantia ou\n");
					printf(" responsabilidade.\n");
					printf(" \n");
					printf(" BOM DIVERTIMENTO!                      Setembro 2000, Marvin Oliver Schneider\n");
					espere_tecla();
					break;
		case ALEMAO:    sob();
						printf(" Das vorliegende Programm wurde im Rahmen eines Diplomprojektes Informatik an\n");
					printf(" der Positivo-Universitaet Curitiba, Parana, Brasilien, erstellt. Der wissen-\n");
					printf(" schaftliche Fokus des Projektes ist die Benutzung kuenstlicher Intelligenz\n");
					printf(" in Computerspielprogrammen am Beispiel eines Schachspieles.\n");
					printf(" \n");
					printf(" Das vorliegende Projekt wurde von Prof.M.Sc. Fabio Vinicius Binder sowie allen\n");
					printf(" anderen Tutoren der Positivo-Universitaet betreut.\n\n");
					printf(" Ich widme dieses Projekt meiner Frau Alessandra ohne die ich nie den Mut ge-\n");
					printf(" habt haette mit dem Informatikstudium einen Weg einzuschlagen, der bisher von\n");
					printf(" noch niemandem in meiner Familie und Verwandtschaft gegangen worden ist.\n");
					printf(" \n");
					espere_tecla();
					titulo();
					sob();
					printf(" Ich moechte mich an dieser Stelle auch bei meinem Vater Prof.Dr.Dr.h.c. Hans \n");
					printf(" Joachim Schneider und meiner Mutter Hildegard Schneider fuer eine ausge-\n");
					printf(" zeichnete Beratung und den Wunsch, auch eine Universitaetslaufbahn einzu-\n");
					printf(" schlagen.\n\n");
					printf(" Aus Zeitgruenden musste auf eine aufwaendigere Benutzeroberflaeche verzichtet\n");
					printf(" werden. Trotzdem hoffen ich, dass das Projekt auch so noch sein Ziel erreicht,\n");
					printf(" zur Verbreitung des Schachs beizutragen.\n");
					printf(" \n");
					printf(" Das vorliegende Programm ist Freeware, d.h. es darf kopiert aber weder ver-\n");
					printf(" aendert noch verkauft werden. Keine Haftung oder Garantie werden uebernommen.\n");
					printf("\n");
					printf(" VIEL FREUDE BEIM SPIELEN!          Im September 2000, Marvin Oliver Schneider\n");
					espere_tecla(); 
					break;
		case INGLES:    sob();  
						printf(" This program was created in the frame of a graduation-project of computer-\n");
					printf(" science at the Positivo-University, Curitiba, Parana, Brazil. Its scientific\n");
					printf(" focus is the usage of artificial inteligence in the development of computer-\n");
					printf(" games taking chess as an example.\n");
					printf(" \n");
					printf(" The present project was developed under supervision of Prof.M.Sc. Fabio \n");
					printf(" Vinicius Binder an all the team of professors that provide orientation for \n");
					printf(" the elaboration of graduation-projects at the Positivo-University.\n\n");
					printf(" I dedicate this project to my wife Alessandra without whom I never would have\n");
					printf(" had the courage to follow a way completely different from that of my family by\n");
					printf(" choosing to study computer-science.\n");
					espere_tecla();
					titulo();
					sob();
					printf(" I would like to also thank my father Prof.Dr.Dr.h.c. Hans Joachim Schneider \n");
					printf(" and my mother Hildegard Schneider for good orientation and the wish to also\n");
					printf(" build up a university-carreer.\n\n");
					
					printf(" Because of the lack of time a better user-interface was not programmed.\n");
					printf(" Though, I hope that this project reaches its aim of promoting Chess.\n");
					printf(" \n");
					printf(" The present program is freeware, that is, it may be copied but neither sold\n");
					printf(" nor modified in any way. No guarantee or liability is accepted.\n");
					printf(" \n");
					printf(" HAVE FUN!                           September 2000, Marvin Oliver Schneider\n");
					espere_tecla();
					break;
	}
}

void console::t(void)
{
	int i;
	for(i=0;i<20;i++) printf(" ");
}

void console::figura(int nro)
{
	titulo();
	tut();
	gotoxy(0,8);
	t(); printf("     A   B   C   D   E   F   G   H  \n");
	printf("\n");
	t(); printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
				cds1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1, ho1, ho1,
				hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, ces1);
	switch(nro)
	{
		case 1: 
			
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 2:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c<T>%c<P>%c<I>%c<W>%c<#>%c<I>%c<P>%c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 3:
			t(); printf(" 8 %c[T]%c[P]%c[I]%c[W]%c[#]%c[I]%c[P]%c[T]%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c[i]%c[i]%c[i]%c[i]%c[i]%c[i]%c[i]%c[i]%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c<i>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c<T>%c<P>%c<I>%c<W>%c<#>%c<I>%c<P>%c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 4:
			t(); printf(" 8 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf("(1)%c<T>%c x %c x %c x %c x %c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 5:
			t(); printf(" 8 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf("(1)%c<T>%c x %c x %c[IX%c   %c   %c   %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 6:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c x %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c x %c   %c x %c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c<I>%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c x %c   %c x %c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 7: 
			t(); printf(" 8 %c   %c///%c   %c x %c   %c///%c   %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c x %c   %c///%c x %c///%c   %c x %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c x %c   %c x %c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c x %c x %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c x %c x %c x %c<W>%c x %c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c x %c x %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c x %c   %c x %c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c x %c   %c///%c x %c///%c   %c x %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 8:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c x %c   %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c x %c   %c///%c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c<P>%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c x %c   %c///%c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c x %c   %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;  
		case 9: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c x %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c[i]%c///%c   %c///%c   %c///%c<i>%c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c<i>%c x %c[IX%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c<i>%c   %c x %c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c x %c///%c<i>%c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c<i>%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 10: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c x %c x %c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c x %c<#>%c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c x %c x %c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 11: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c x %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c x %c<#>%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c x %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c[T]%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 12: 
			t(); printf(" 8 %c   %c///%c   %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c<i>%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 13: 
			t(); printf(" 8 %c   %c///%c   %c<W>%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 14: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c<T>%c   %c///%c   %c<#>%c   %c///%c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 15: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c<#>%c<T>%c///%c   %c///%c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 16: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c<T>%c   %c///%c   %c///%c<T>%c<#>%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 17: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c[i]%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c x %c<i>%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 18: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c<i>%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 19: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c[I]%c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c x %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c<#X%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 20:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c[I]%c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c x %c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c x %c<#>%c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c x %c x %c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 21: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c[T]%c x %c x %c x %c x %c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c[T]%c x %c x %c x %cX#X%c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 22: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c[I]%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c x %c[W]%c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c x %cX#X%c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 23:
			t(); printf(" 8 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c x %c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c x %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c x %c[I]%c///%c   %c///%c[T]%c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c[W]%c x %c x %c x %c x %c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c x %c x %c///%c x %c<#>%c x %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 24:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c[i]%c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c[W]%c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c<W>%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c<T>%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 25: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c[T]%c   %c[T]%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c x %c///%c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c x %c   %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c x %c///%c x %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c<P>%c   %c<P>%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 26: 
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c[P]%c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c<WX%c   %c<#X%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 27:
			t(); printf(" 8 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c///%c[T]%c x %c x %c<IX%c . %c<#>%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c///%c   %c///%c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c   %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 28:
			t(); printf(" 8 %c[T]%c   %c[I]%c[W]%c[#]%c[I]%c   %c[T]%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c[i]%c[i]%c[i]%c[i]%c   %c   %c[i]%c[i]%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c   %c[P]%c...%c...%c[P]%c   %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c   %c   %c...%c...%c[i]%c[i]%c   %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c   %c...%c...%c<i>%c...%c   %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c   %c   %c<P>%c<i>%c...%c...%c   %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c<i>%c<i>%c<i>%c   %c   %c   %c<i>%c<i>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c<T>%c   %c<I>%c<W>%c<#>%c<I>%c   %c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
		case 29:
			t(); printf(" 8 %c x %c x %c x %c[W]%c x %c x %c x %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 7 %c///%c   %c x %c x %c x %c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 6 %c   %c x %c   %c x %c   %c x %c   %c///%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 5 %c x %c   %c///%c x %c///%c   %c x %c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 4 %c   %c///%c   %c x %c   %c///%c   %c x %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 3 %c///%c   %c///%c x %c///%c   %c///%c   %c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 2 %c   %c///%c   %c x %c   %c///%c<i>%c<i>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);
			t(); printf(" 1 %c///%c   %c///%c x %c///%c   %c<P>%c<T>%c\n",ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1,ve1);

			break;
	}
	t(); printf("   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
			cdi1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1, ho1, ho1,
			hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, cei1);
	printf("\n");
	espere_tecla();

	titulo();
	tut();
}

void console::tutorial(void)
{
	// orientacao: possivel escrever de linha 8 a linha 21, entao 14 linha - 80 caracteres cada linha no maximo
	console io;
	io.titulo();    // nao o titulo completo para ter mais espaco;
	switch(lingua)
	{
		case PORTUGUES: tut();   
					gotoxy(0,8);
					printf(" 1.1. C O N S I D E R A C O E S   G E R A I S\n\n");
					printf(" As regras basicas do Xadrez sao bastante simples. A inspiracao do jogo pode \n");
					printf(" ser descrita por uma briga de dois povos da idade media. Dentro de cada povo\n");
					printf(" existe uma hierarquia e a peca mais importante - como poderia ser diferente -\n");
					printf(" e o rei.\n\n");
					printf(" As pecas no total sao para cada povo:\n");
					printf(" Um rei         [#]\n");
					printf(" Uma rainha     [W]\n");
					printf(" Duas torres    [T]\n");
					printf(" Dois bispos    [I]\n");
					printf(" Dois cavalos   [P]\n");
					printf(" Oito peoes     [i]\n\n");
					espere_tecla();
					titulo();
					tut();
					printf(" O campo da batalha e um tabuleiro de 64 posicoes, ele e um quadrado de oito \n");
					printf(" posicoes horizontais e oito posicoes verticais que sao - para melhor \n");
					printf(" distingui-los - pintadas de preto e branco.\n\n");
					printf(" Para facilitar a leitura de partidas dos grandes mestres e escrever partidas \n");
					printf(" no papel existe uma numeracao:\n\n");
					printf(" A, B, C, D, E, F, G, H na horizontal e\n");
					printf(" 8, 7, 6, 5, 4, 3, 2, 1 na vertical\n\n");
					espere_tecla();
					figura(1);
					printf(" Existe uma posicao inicial que deve ser observada rigorosamente. As pecas \n");
					printf(" brancas sao posicionadas nas linhas 7 e 8 da seguinte forma:\n\n");

					printf(" Um linha cheia de peao na linha 7 e na linha 8 observe-se o esquema:\n");

					printf(" Torre - Cavalo - Bispo - Rainha - Rei - Bispo - Cavalo - Torre\n");
					espere_tecla();
					figura(2);
					printf(" La estao as figuras pesadas - como sao chamadas às vezes - atras de uma grade\n");
					printf(" de peoes. As torres parecem ser as torres de um grande castelo . O rei e a \n");
					printf(" rainha no centro merecem todas as atencoes. Pode se observar que a posicao e \n");
					printf(" praticamente simetrica.\n\n");

					printf(" As pecas pretas tem uma posicao inicial de batalha bem parecida. Tambem uma \n");
					printf(" grade de peoes - que ja na roma antiga se mandava como os primeiras para a \n");
					printf(" guerra. Esta grade de peoes se localiza entao na linha 2. Atras desta linha\n");
					printf(" de novo a linha das figuras nobres:\n\n");

					printf(" Torre - Cavalo - Bispo - Rainha - Rei - Bispo - Cavalo - Torre\n\n");

					printf(" Importante: Rei e Rainha dos dois povos estao na mesma coluna.\n");
					espere_tecla();
					figura(3);
					printf(" Despois de colocar esta posicao no tabuleiro pode se finalmente comecar o \n");
					printf(" jogo.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 1.2. M O V I M E N T O S   N O R M A I S\n\n");
					printf(" O objetivo do jogo e colocar o rei do adversario em mate, mas o que significa\n");
					printf(" isso e como chegamos la\?\n");
					printf(" Primeiramente deve-se saber que cada peca pode-se movimentar e cada peca pode\n");
					printf(" atacar ou retirar uma outro peca do adversario. Porem, cada uma se movimenta\n");
					printf(" e luta de uma maneira diferente.\n");
					printf(" A figura talvez mais facil de entender e a torre. A torre pode se mover\n");
					printf(" verticamente e horizontalmente a partir da posicao atual a qualquer lugar que\n");
					printf(" esteja livre nestas linhas, isto e para cima, para baixo, para a direita e\n");
					printf(" para a esquerda. Se esta peca encontrar uma do adversario no caminho ela \n");
					printf(" pode comer esta peca para obter vantagem - mas nao precisa. Tudo isto depende\n");
					printf(" da estrategica do jogador.\n");
					espere_tecla();
					figura(4);
					printf(" Imaginamos entao que num tabuleiro vazio haja uma torre na casa A1. A torre\n");
					printf(" pode se movimentar como alternativas para as casas A2, A3, A4, A5, A6, A7, A8\n");
					printf(" ou na outra direcao B1, C1, D1, E1, F1, G1, H1.\n");
					printf(" Imaginamos entao neste mesmo campo de batalha um bispo perdido do inimigo na\n");
					printf(" casa D1. A torre entao pode se movimentar para as casas A2, A3, A4, A5, A6,\n");
					printf(" A7, A8 ou para as casas B1, C1, D1. Em D1 nao havia um bispo do inimigo\? Pois\n");
					printf(" e, se eu escolher destas possibilidades mover a torre para D1 a torre\n");
					printf(" automaticamente tira a outra peca do tabuleiro.\n");
					espere_tecla();
					figura(5);
					printf(" Desta maneira facil funcionam praticamente todas as pecas. Observe-se porem:\n\n");
					printf(" O bispo se movimenta diagonalmente sem limite de casas. Isto e, um bispo na \n");
					printf(" casa B1 pode ir para todas as casas na diagonal A1 -> H8 e para qualquer casa\n");
					printf(" da pequena diagonal A3-C1. Ele tambem pode tirar as pecas que se encontram\n");
					printf(" nestas diagonais.\n");
					espere_tecla();
					figura(6);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" A dama pode ser considerada uma mistura entre bispo e torre. Na verdade ela\n");
					printf(" combina as habilidades dos dois fazendo dela a figura mais poderosa do \n");
					printf(" tabuleiro. A partir da posicao atual ela pode-se mover nas diagonais e tambem\n");
					printf(" na vertical e horizontal.\n");
					espere_tecla();
					figura(7);
					printf(" A caracteristica principal do cavalo e de pular. Isto ocorre conforme o \n");
					printf(" seguinte diagrama:\n");
					espere_tecla();
					figura(8);
					printf(" Nota-se que nao importa o que ha nos campos nao marcados no meio, pois o \n");
					printf(" cavalo nao passa por eles.\n");
					printf(" O peao pode - na posicao inicial ir duas casas para a frente (em direcao do\n");
					printf(" lado da outra cor) ou uma. Depois que se moveu uma vez somente e possivel se\n");
					printf(" mover uma casa para a frente e somente so se a casa da frente estiver vazia.\n");
					printf(" Mesmo uma peca do adversario nao pode-se retirar da casa. Somente e possivel\n");
					printf(" retirar pecas do adversario nas primeiras casas das diagonais na frente.\n");
					espere_tecla();
					figura(9);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" O rei - a principio - pode se mover para todas as casas proximas a ele como\n");
					printf(" mostra o seguinte diagrama:\n");
					espere_tecla();
					figura(10);
					printf(" Porem, ele nao pode se mover para dentro de linhas de ataque ou seja uma\n");
					printf(" possibilidade do inimigo retirar o rei (o que as regras nao permitem).\n");
					espere_tecla();
					figura(11);
					printf(" Nesta posicao o rei nao pode-se mover para dentro da linha E8-E1 por estar\n");
					printf(" controlada pela torre em E3.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 1.3. M O V I M E N T O S   E S P E C I A I S\n\n");
					printf(" Apos esta explicacao das regras basicas deve-se entao conhecer ainda algumas\n");
					printf(" situacoes especiais que podem ocorrer:\n\n");
					printf(" Na hora que o peao de uma outra cor chega à linha base do adversario e assim\n");
					printf(" nao pode ficar andando mais para a frente ele e trocado - conforme o desejo\n");
					printf(" do jogador - para uma rainha (na maioria dos casos), uma torre, um bispo ou\n");
					printf(" um cavalo. Na seguinte posicao entao:\n");
					espere_tecla();
					figura(12);
					printf(" Apos o movimento pode ter mudado para a seguinte situacao:\n");
					espere_tecla();
					figura(13);
					printf(" Um rei com uma torre pode fazer o chamado \"roque\" se nao houver obstaculo\n");
					printf(" nem ataque no caminho e se ninguem ainda movimentou estas pecas.\n\n");
					printf(" Por exemplo:\n");
					espere_tecla();
					figura(14);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Considerando que nenhuma das pecas se movimentou ate agora. Pode-se obter as \n");
					printf(" seguintes posicoes apos o roque:\n");
					espere_tecla();
					figura(15);
					figura(16);
					printf(" Finalmente existe a figura do \"en passent\". Considerando o seguinte diagrama:\n");
					espere_tecla();
					figura(17);
					printf(" O peao em D7 pode avancar ate D6 e D5. Em ambas as posicoes ele pode ser \n");
					printf(" retirado pelo peao branco em E5. Se ele se mover ate D6 normalmente - se ele\n");
					printf(" se mover ate D5 \"en passent\" ou seja \"ao passar\". A posicao resultante sera a\n");
					printf(" mesma em ambos os casos:\n");
					espere_tecla();
					figura(18);
					printf(" O objetivo final do jogo e colocar o rei do adversario em Xeque-Mate. Para\n");
					printf(" isto, ele primeiro tem que se encontram em Xeque. Xeque e o ataque do rei\n");
					printf(" por qualquer outra peca. Por exemplo:\n");
					espere_tecla();
					figura(19);
					printf(" Aqui o rei esta na linha de ataque do bispo. Sempre que ele estiver em uma\n");
					printf(" linha de ataque ele vai ter que desfazer o ataque ou se movendo para uma casa\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" nao atacada, colocar outra peca na linha de ataque ou retirar a peca atacante.\n");
					printf(" Na presente posicao nao ha peca para colocar no meio nem a possibilidade de \n");
					printf(" retirar o bispo pois o rei nao o alcanca. Entao ele somente podera sair do\n");
					printf(" ataque. Isto da as seguintes possibilidades para ele:\n");
					espere_tecla();
					figura(20);
					printf(" Quando nao ha mais possibilidades de eliminar o ataque fala-se de um \n");
					printf(" Xeque-Mate. A seguir duas posicoes classicas de Xeque-Mate:\n");
					espere_tecla();
					figura(21);
					printf(" O rei esta sendo atacado por uma torre e nao pode sair para a proxima linha,\n");
					printf(" pois esta ja esta no controle da outra torre.\n");
					espere_tecla();
					figura(22);
					printf(" Nesta posicao o rei esta sendo \"pregado na parede\" pela dama em D2. E \n");
					printf(" importante observar que esta dama tem que ser protegida por uma outra peca\n");
					printf(" porque senao o rei simplesmente poderia retirar ela desfazendo assim o ataque.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Existem jogadores com muito azar. E estes nao observem que um rei para ser\n");
					printf(" Xeque-Mate tem que estar em Xeque tambem. Nao observando isto pode ocorrer\n");
					printf(" um empate como na seguinte figura.\n");
					espere_tecla();
					figura(23);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					gotoxy(0,8);
					printf(" 2. E S T R U T U R A S   T A T I C A S / E S T R A T E G I C A S\n\n"); 
					printf(" A abordagem a seguir e curta e bastante objetiva. Nao tentou-se substituir\n");
					printf(" os livros de Xadrez que existem no mercado mas sim dar uma impressao de certas\n");
					printf(" maneiras de jogar que ajudem a ganhar uma partida de Xadrez.\n\n");
					printf(" 2.1. A T A Q U E\n\n");
					printf(" Como ja dito anteriormente uma peca pode atacar uma outra peca, isto e,\n");
					printf(" ameacar a retira-la. E importante saber que geralmente busca-se proteger as \n");
					printf(" proprias pecas ameacando a tirar entao a peca que atacou com outra peca.\n");
					printf(" Se - ou nao - um ataque vale a pena e (nao levando em consideracao vantagens\n");
					printf(" gerais posicionais) pura matematica. Cada peca no tabuleiro tem um determinado\n");
					printf(" valor resultante de seu uso e a probabilidade de finalmente dar Xeque-Mate.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Os valores sao:\n\n");
					printf(" Rainha: 9\n");
					printf(" Torre:  5\n");
					printf(" Bispo:  3\n");
					printf(" Cavalo: 3\n");
					printf(" Peao:   1\n\n");
					printf(" Sendo assim deve-se procurar pelo menos fazer uma troca com valores iguais.\n");
					printf(" Vale a pena lembrar que uma troca tambem e vantageosa por simplificar a\n");
					printf(" posicao no tabuleiro. Este tipo de ataque e contra-ataque pode ocorrer na\n");
					printf(" seguinte posicao:\n");
					espere_tecla();
					figura(24);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Preto ou tambem branco - estando na vez nesta posicao - podem iniciar uma\n");
					printf(" troca de damas. Porem, o jogador preto pode talvez nao gostar muito da ideia,\n");
					printf(" pois ele fica depois com um desvantagem material ainda mais claro.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.2. A T A Q U E   D U P L O\n\n");
					printf(" Um ataque duplo e um ataque de duas pecas do adversario ao mesmo tempo sendo\n");
					printf(" que duas pecas diferentes tambem atacam.\n");
					espere_tecla();
					figura(25);
					printf(" Preto na vez nesta posicao pode escolher tranquilamente entre as duas pecas\n");
					printf(" - qual ele mais goste. Porem, esta posicao somente vira interessante de\n");
					printf(" verdade com o jogador atacado na vez, porque ele tem que decidir - querendo ou\n");
					printf(" nao - qual das duas pecas ele vai abandonar - ja que ele nao pode fazer dois\n");
					printf(" movimentos ao mesmo tempo.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.3. G A R F O\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" O garfo e muito parecido com o ataque duplo. Aqui tambem o outro jogador tem \n");
					printf(" que decidir qual peca ele vai abandonar. Mas agora, somente uma peca ataca\n");
					printf(" duas do outro jogador. Pode-se considerar um caso classico o cavalo atacando\n");
					printf(" ao mesmo tempo uma torre e uma rainha. Tambem classico, mas pior ainda, e um\n");
					printf(" cavalo que ataca a rainha e ao mesmo tempo da Xeque no rei. Desta maneira e\n");
					printf(" imperativo pelas regras desfazer o ataque do rei significando - se o ataque\n");
					printf(" for bem planejado - que o rei tem que sair da linha de ataque e o outro joga-\n");
					printf(" dor praticamente ganhou o jogo retirando com a rainha a mais poderosa peca.\n");
					printf(" Verifica-se um exemplo a seguir:\n");
					espere_tecla();
					figura(26);
					printf(" Neste caso realmente nao ha outra solucao a nao ser colocar o rei em D1 e\n");
					printf(" pelo menos ainda conseguir tirar o cavalo apos e perda da rainha.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.4. B L O Q U E I O\n\n");
					printf(" Uma peca vale como bloqueada se ela se encontra na linha de ataque de uma\n");
					printf(" peca com uma outra de um valor alto assim nao podendo colocar a peca no\n");
					printf(" caminho em outro lugar para nao arriscar a figura atras.\n");
					printf(" O bloqueio e verdadeiro se a peca ameacada a ser atacada e o rei pois as\n");
					printf(" regras nao permitam que um jogador cause um Xeque no proprio rei.\n");	
					printf(" Um exemplo disso:\n");
					espere_tecla();
					figura(27);
					printf(" O bispo em E5 nao pode ser movido para nao causa um Xeque no rei em G5,\n");
					printf(" entao ele se encontra bloqueado.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.5. I N F L U E N C I A   N O   C E N T R O\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" A influencia no centro do tabuleiro e importante no inicio do jogo. Na aber-\n");
					printf(" tura em si e logo apos tenta-se concentrar as forcas no quadrado central do\n");
					printf(" tabuleiro - isto principalmente porque as pecas mais importantes do jogo se\n");
					printf(" encontram na vizinhanca, mas tambem para evitar que as forcas nao sejam nem\n");
					printf(" desenvolvidas direito o que pode ocorrer se um jogador tentar se concentram em\n");
					printf(" um dos lados logo no inicio.\n");
					espere_tecla();
					figura(28);
					printf(" Na posicao acima pode-se verificar que a primeira batalha ira acontecer no\n");
					printf(" quadrado central do tabuleiro. Isto e um caso tipico e deve-se sempre seguir\n");
					printf(" este modelo.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.6. DOMINIO DE LINHAS E LIBERDADE DE MOVIMENTO\n\n");
					printf(" Mais para frente no jogo considera-se importante ter controle de linhas e\n");
					printf(" liberdade de movimento ao mesmo tempo.\n");
					printf(" Controlar uma linha significa ter o poder de ameacar qualquer peca que entre\n");
					printf(" na linha a ser retirada.\n");
					printf(" Ter liberdade de movimento significa poder escolher entre varias possibili-\n");
					printf(" dades de mover uma peca - principalmente quando for de peso - e nao ter que\n");
					printf(" deixar ela inutilmente \"pregada na parede\" onde ela nao servira para nada.\n");
					espere_tecla();
					figura(29);
					printf(" Enquanto a rainha na posicao de cima controla varias linhas e tem liberdade\n");
					printf(" de movimento total, a torre branca nao ha utilidade alguma, pois nao consegue\n");
					printf(" se mover.\n");
					break;


		case ALEMAO:	tut();
						gotoxy(0,8);
						printf(" 1.1. A L L G E M E I N E S\n\n");
					printf(" Die Grundregeln des Schach sind recht einfach zu erlernen. Bei diesem Spiel\n");
					printf(" kaempfen zwei Voelker gegeneinander - weiss und schwarz. Ein jedes Volk ist\n");
					printf(" gemaess einer allgemeinen Hierarchie augebaut. Die wichtigste Figur dabei -\n");
					printf(" wie koennte es anders sein - ist der Koenig.\n\n"); 
					printf(" Jedes Volk hat folgende Figuren in gleicher Anzahl:\n\n");
					printf(" Ein Koenig    [#]\n");
					printf(" Eine Dame     [W]\n");
					printf(" Zwei Tuerme   [T]\n");
					printf(" Zwei Laeufer  [I]\n");
					printf(" Zwei Springer [P]\n");
					printf(" Acht Bauern   [i]\n\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Das Spielfeld hat 64 Felder. Es handelt sich um ein Quadrat mit acht Posi-\n");
					printf(" tionen horizontal und acht Positionen vertikal, die - um sie besser aus-\n");
					printf(" einander halten zu koennen - weiss und schwarz eingefaerbt sind.\n");
					printf(" Um das Nachspielen von Grossmeisterpartien sowie das Aufzeichnen eigener\n");
					printf(" Spiele zu vereinfachen ist das Brett nummeriert.\n\n");
					printf(" A, B, C, D, E, F, G, H horziontal und\n");
					printf(" 8, 7, 6, 5, 4, 3, 2, 1 vertikal\n\n");
					espere_tecla();
					figura(1);
					printf(" Es gibt eine Ausgangsposition, die strikt eingehalten werden muss. Die\n");
					printf(" weissen Figuren werden folgendermasse auf den Linien 7 und 8 aufgestellt:\n\n");

					printf(" Eine lange Reihe nur Bauern auf der 7 und folgende Aufstellung auf der 8:\n");

					printf(" Turm - Springer - Laeufer - Dame - Koenig - Laeufer - Springer - Turm\n");
					espere_tecla();
					figura(2);
					printf(" Da stehen sie nun, die schweren Figuren, wie sie manchmal genannt werden,\n");
					printf(" hinter einer langen Bauernreihe. Die Tuerme scheinen die Eckpfeiler eines\n");
					printf(" grossen Schlosses zu sein und die Herrscher in der Mitte sind das Zentrum\n");
					printf(" der Aufmerksamkeit. Beachtenswert ist, dass die Position fast symmetrisch\n");
					printf(" ist.\n");
					printf(" Die schwarzen Figuren haben eine sehr aehnliche Grundaufstellung. Auch eine\n");
					printf(" lange Reihe Bauern - die man schon im alten Rom als erste in die Schlacht\n");
					printf(" schickte. Diese Reihe befindet sich auf der 2. Dahinter findet man dann\n");
					printf(" die adeligen Steine vor:\n\n");
					printf(" Turm - Springer - Laeufer - Dame - Koenig - Laeufer - Springer - Turm\n");
					printf(" Wichtig: Koenig und Dame der beiden Voelker stehe in denselben Spalten.\n");
					espere_tecla();
					figura(3);
					printf(" Nachdem wir diese Position auf dem Brett aufgebaut haben, kann also das\n");
					printf(" koenigliche Spiel beginnen.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 1.2. A L L T A E G L I C H E   Z U E G E\n\n");
					printf(" Das Ziel des Spieles ist es, den gegnerischen Koenig matt zu setzen, aber\n");
					printf(" was heisst denn das nun eigentlich und wie kommt man da hin\?\n");
					printf(" Als Allererstes muss man wissen, dass jeder Spielstein sich bewegen, angrei-\n");
					printf(" fen und Steine des Gegner schlagen kann. Nun hat aber jede Figur ihre sehr\n");
					printf(" eigene Art, das zu tun.\n");
					printf(" Die Figur, die vielleicht am einfachsten zu verstehen ist, ist der Turm. Der\n");
					printf(" Turm kann sich vertikal und horizontal von seiner Ausgangsposition aus auf\n");
					printf(" jedwedes freie Feld bewegen - d.h. also nach oben, nach unten, nach rechts und\n");
					printf(" nach links. Falls dabei ein gegnerischer Stein in die Quere kommt, kann er\n");
					printf(" entfernt werden, um materiellen Vorteil zu erzielen - aber das ist natuerlich\n");
					printf(" nicht zwingend und haengt von der Strategie jeden Spielers ab.\n");	
					espere_tecla();
					figura(4);
					printf(" Stellen wir uns also vor, dass auf einem leeren Spielfeld auf Feld A1 ein Turm\n");
					printf(" steht. Der Turm kann nach A2, A3, A4, A5, A6, A7, A8 oder in der anderen\n");
					printf(" Richtung nach B1, C1, D1, E1, F1, G1, H1 bewegt werden.\n");
					printf(" Und nun stellen wir uns auf demselben Spielfeld einen verloren gegangenen \n");
					printf(" Laeufer des Gegners auf Feld D1 vor. Der Turm kann sich nunmehr also nach\n");
					printf(" A2, A3, A4, A5, A6, A7 und A8 sowie B1, C1 und D1 bewegen. War da nicht auf D1\n");
					printf(" dieser Laeufer des Gegners\? Ganz recht, und wenn wir den Zug nach D1 aus-\n");
					printf(" waehlen, entfernen wir damit automatisch den Laeufer vom Brett.\n");
					espere_tecla();
					figura(5);
					printf(" Auf diese einfache Art und Weise funktionieren alle Spielfiguren. Man bemerke\n");
					printf(" allerdings: Ein Laeufer bewegt sich z.B. diagonal ohne Begrenzung von Feldern,\n");
					printf(" d.h. ein Laeufer auf B1 kann sich auf alle Felder der Linie A1-> H8 bewegen\n");
					printf(" sowie auf alle der kleinen Diagonale A3-C1. Er kann auch jedweden Spielstein\n");
					printf(" des Gegners auf diesen Linien entfernen.\n");
					espere_tecla();
					figura(6);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Die Dame kann man als Mischung zwischen Turm und Laeufer beschrieben. Genau\n");
					printf(" genommen vereinigt sie die Faehigkeiten beider Figuren und ist damit die\n");
					printf(" maechtigste Figur des Spiels. Von ihrer Ausgangsposition aus kann sie sich\n");
					printf(" nach allen Feldern auf den Diagonalen, der Vertikalen und der Horizontalen\n");
					printf(" bewegen.\n");
					espere_tecla();
					figura(7);
					printf(" Die Hauptcharakteristik des Springers ist der Sprung. Seine Bewegungs- und\n");
					printf(" Schlagmoeglichkeiten im folgenden Diagramm:\n");
					espere_tecla();
					figura(8);
					printf(" Wichtig: Es interessiert im Fall des Springers nicht, was sich auf den un-\n");
					printf(" markierten Feldern auf dem Weg befindet, weil er ueber sie hinwegspringt.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Der Bauer kann in der Anfangsposition zwei Feldern nach vorne (auf den Gegner\n");
					printf(" zu) oder eines gehen. Nach dem ersten Zug ist es dann lediglich moeglich, sich\n");
					printf(" ein einziges Feld jeweils nach vorne zu bewegen und auch nur dann, wenn dieses\n");
					printf(" Feld frei ist. Auch ein gegnerischer Stein kann so nicht genommen werden. Das\n");
					printf(" ist nur moeglich auf den ersten Feldern der vorderen Diagonalen.\n");
					espere_tecla();
					figura(9);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Der Koenig kann sich - im Prinzip - auf alle Felder in seiner Naehe bewegen\n");
					printf(" wie das folgende Diagramm zeigt:\n");
					espere_tecla();
					figura(10);
					printf(" Jedoch, er kann nicht auf angegriffene Felder ziehen und damit die Moeglich-\n");
					printf(" keit erzeugen, dass der Koenig vom Gegner genommen wird (was die Regeln\n");
					printf(" nicht gestatten).\n");
					espere_tecla();
					figura(11);
					printf(" In dieser Position bleiben dem Koenig die Felder der Linie E8-E1 verwaehrt, da\n");
					printf(" sie vom Turm auf E3 kontrolliert werden.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 1.3. E I N I G E   B E S O N D E R H E I T E N\n\n");
					printf(" Nach dieser Erklaerung der Grundregeln, ist es noch wichtig einige besondere\n");
					printf(" Situationen kennenzulernen, die auftreten koennen:\n\n");
					printf(" In dem Moment wenn ein Bauer auf der Grundlinie des Gegners ankommt und somit\n");
					printf(" nicht mehr weiter kann, wird er - nach Belieben des Spielers - gegen eine Dame\n");
					printf(" (in den meisten Faellen), einen Turm, einen Laeufer oder ein Pferd einge-\n");
					printf(" tauscht. Die folgende Position:\n");
					espere_tecla();
					figura(12);
					printf(" Kann sich also sehr rasch nach Zug des Bauern verwandeln:\n");
					espere_tecla();
					figura(13);
					printf(" Ein Koenig und ein Turm koennen zusammen die sogenannte Rochade durchfuehren\n");
					printf(" falls keine anderen Steine im Wege stehen, kein Feld des Weges angegriffen ist\n");
					printf(" und mit keiner der beteiligten Figuren bereits gezogen wurde.\n");
					printf(" Ein Beispiel:\n");
					espere_tecla();
					figura(14);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Wenn wir davon ausgehen, dass keine der Figuren bisher bewegt wurde, kann man\n");
					printf(" folgende Positionen nach der Rochade erhalten:\n");
					espere_tecla();
					figura(15);
					figura(16);
					printf(" Schliesslich gibt es das sogenannte \"en passent\". Sehen wir uns folgendes\n");
					printf(" Diagramm einmal naeher an:\n");
					espere_tecla();
					figura(17);
					printf(" Der Bauer auf D7 kann nach D6 und D5 bewegt werden. In beiden Faellen kann\n");
					printf(" er jedoch vom Bauern auf E5 genommen werden. Wenn er sich auf D6 bewegt, ist\n");
					printf(" das fuer uns nichts Neues, aber auch im Fall von D5 kann er entfernt werden -\n");
					printf(" dann \"en passent\", also im Voruebergehen. Auf dem Brett bleibt nach einem der\n");
					printf(" beiden Zuge folgendes stehen:\n");
					espere_tecla();
					figura(18);
					printf(" Das Ziel des Spieles ist, den Koenig des Gegners schachmatt zu setzen. Dazu\n");
					printf(" muss er sich zunaechst einmal im Schach befinden. Schach ist ein Angriff des\n");
					printf(" Koenigs durch jeweden Stein des Gegners. Z.B.:\n");
					espere_tecla();
					figura(19);
					printf(" Hier befindet sich der Koenig in der Angriffslinie des Laeufers. Immer wenn\n");
					printf(" er angegriffen wird, muss er diesem Angriff entkommen, entweder, indem er\n");
					printf(" sich einfach aus dem Angriff hinausbewegt, eine andere Figur davorgestellt\n");
					printf(" wird oder der Angreifer entfernt wird. In der vorliegenden Stellung kann der\n");
					printf(" Koenig lediglich fluechten. Somit hat er folgenden Zugmoeglichkeiten:\n");
					espere_tecla();
					figura(20);
					printf(" Wenn es keine Moeglichkeit mehr gibt, dem Angriff zu entkommen, spricht man\n");
					printf(" vom Schachmatt. Sehen wir uns einmal zwei typische Mattbilder an:\n");
					espere_tecla();
					figura(21);
					printf(" Hier wird der Koenig von einem Turm angegriffen und kann nicht entweichen,\n");
					printf(" weil die andere Linie auch bereits von einem Turm kontrolliert wird.\n");
					espere_tecla();
					figura(22);
					printf(" In dieser Position wird der Koenig \"festgenagelt\" durch die Dame auf D2. Es\n");
					printf(" ist hierbei wichtig, darauf hinzuweisen, dass die Damen geschuetzt sein muss,\n");
					printf(" weil sie sonst einfach vom Koenig geschlagen werden koennte.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Nun gibt es doch einige Spieler, die vor Pech nur so stinken. Und genau diese\n");
					printf(" sind es, die sich nicht ueberlegen, dass ein Koenig fuer das Matt auch im\n");
					printf(" Schach stehen muss. Wenn der anderen Spieler dann lediglich keine Bewegungs-\n");
					printf(" moeglichkeit mehr hat, ist die Partie zwingend \"Remis\", also unentschieden:\n");
					espere_tecla();
					figura(23);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					gotoxy(0,8);
					printf(" 2. E I N   W E N I G   S T R A T E G I E\n\n");
					printf(" Was jetzt kommt, ist kurz und buendig und soll keineswegs den Anspruch erheben\n");
					printf(" mit der existierenden Schachliteratur mithalten zu koennen. Es sind lediglich\n");
					printf(" einige wichtige Anhaltspunkte fuer den Erfolg in einer Partie:\n\n");
					printf(" 2.1. A N G R I F F\n\n");
					printf(" Wie bereits erwaehnt, kann eine Figur eine andere angreifen, also mit dem\n");
					printf(" Schlagen drohen. Normalerweise versucht man nun die eigenen Steine zu decken\n");
					printf(" also ein eventuelles Schlagen mit einem Gegenschlag ausgleichen zu koennen. Ob\n");
					printf(" dann ein Schlagabtausch von Vorteil oder Nachteil ist, ist (abgesehen von \n");
					printf(" eventuellen Stellungsvorteilen) pure Mathematik. Jede Figur hat einen Wert,\n");
					printf(" der von der allgemeinen Spielstaerke und der Nutzung fuer Mattbilder herruehrt.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Hier die Werte:\n\n");
					printf(" Dame:     9\n");
					printf(" Turm:     5\n");
					printf(" Laeufer:  3\n");
					printf(" Springer: 3\n");
					printf(" Bauer:    1\n\n");
					printf(" Wenn wir also einen Spielstein eintauschen, muessen wir zumindest bei dem\n");
					printf(" Gegner den gleichen Verlust wie bei uns herstellen. Diese Art von Tausch ist\n");
					printf(" auch vorteilhaft, weil sie die Stellung vereinfacht. Sehen wir uns dazu\n");
					printf(" folgende Stellung an:\n");
					espere_tecla();
					figura(24);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Schwarz und auch Weiss koennen hier einen Damentausch ausloesen. Allerdings\n");
					printf(" koennte das Schwarz u.U. nicht sehr gefallen, weil er hinterher einen noch\n");
					printf(" deutlicheren materiellen Nachteil hat.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.2. D O P P E L T   G E M O P P E L T\n\n");
					printf(" Bei einem doppelten Angriff greifen zwei unterschiedliche Figuren einer Farbe\n");
					printf(" zwei einer anderen Farbe an.\n");
					espere_tecla();
					figura(25);
					printf(" Schwarz am Zug kann in dieser Stellung in aller Ruhe entscheiden, welche der\n");
					printf(" beiden Figuren er auf den Weg allen Holzes schicken moechte. Allerdings wird\n");
					printf(" das Ganze erst richtig interessant wenn der angegriffene Spieler am Zug ist\n");
					printf(" weil er die unschoene Aufgabe hat, zu entscheiden, von welcher der beiden\n");
					printf(" Figuren er sich trennt (da er keine zwei Zuege gleichzeitig machen kann).\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.3. G A B E L N\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Eine Gabel ist einem doppelten Angriff sehr aehnlich. Hier muss der ange-\n");
					printf(" griffene Spieler auch entscheiden, von welcher Figur er sich trennt. Aber\n");
					printf(" jetzt greift nur eine Figur zwei des Gegners gleichzeitig an. Als klassischen\n");
					printf(" Fall kann man hierbei den gleichzeitigen Angriff von Dame und Turm durch einen\n");
					printf(" Springer einstufen. Auch klassisch - aber noch gemeiner - ist ein Angriff von\n");
					printf(" Dame und Koenig gleichzeitig. In diesem Fall muss der Koenig dann zwingend dem\n");
					printf(" Schach entgehen und es war einmal eine Dame. Auf diese Art und Weise ist das\n");
					printf(" Spiel dann schon fast entschieden. Ein Beispiel:\n");
					espere_tecla();
					figura(26);
					printf(" In diesem Fall gibt es wirklich keine andere Loesung, als den Koenig auf D1\n");
					printf(" zu stellen und zumindest einen (reichlich unvorteilhaften) Tausch durchzu-\n");
					printf(" fuehren.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.4. F E S S E L U N G E N\n\n");
					printf(" Eine Figur gilt als gefesselt wenn sie in einer Angriffslinie einer \n");
					printf(" gegnerischen Figur zu einer eigenen Figur mit hohem Wert steht, was dann zur\n");
					printf(" Folge hat, dass man die Figur nicht wegziehen kann sofern man die dahinter\n");
					printf(" stehende Figur behalten moechte.\n");
					printf(" Eine Fesselung wird als \"echt\" bezeichnet, wenn die dahinter stehende Figur\n");
					printf(" der eigene Koenig ist. In diesem Fall verbieten die Regeln das Wegziehen des\n");
					printf(" gefesselten Steines. Hier wie immer ein Beispiel:\n");
					espere_tecla();
					figura(27);
					printf(" Der Laeufer kann nicht vom Fleck um kein Schach auf dem Koenig auf G5\n");
					printf(" auszuloesen. Er ist somit \"echt gefesselt\".\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.5. Z E N T R U M S E I N F L U S S\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Zentrumseinfluss ist insbesondere wichtig zu Beginn des Spiels. Bei der \n");
					printf(" Eroeffnung und direkt danach versucht man normalerweise alle Kraefte auf das\n");
					printf(" Quadrat in der Mitte des Brettes zu konzentrieren - das inbesondere, weil die\n");
					printf(" wichtigsten Figuren in der Nahe sind, aber auch, um die Figuren richtig zu\n");
					printf(" entwickeln und zu decken, was bei seitlichen Eroeffnungen nicht geschieht.\n");
					espere_tecla();
					figura(28);
					printf(" In der obigen Position konnten wir sehen, dass die erste Kraftprobe im \n");
					printf(" entschieden werden wird. Dies ist ein klassischer Fall und man sollte immer\n");
					printf(" aehnlich beginnen.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.6. LINIENKONTROLLE UND BEWEGUNGSFREIHEIT\n\n");
					printf(" Etwas weiter vorne im Spielverlauf ist es wichtig, Linien zu kontrollieren und\n");
					printf(" gleichzeitig Bewegungsfreiheit zu haben.\n");
					printf(" Linienkontrolle bedeutet die Macht zu haben, alle Figuren des Gegners, die\n");
					printf(" sich auf eine bestimmte Linie bewegen, anzugreifen.\n");
					printf(" Bewegungsfreiheit bedeutet sich zwischen mehreren Zugmoeglichkeiten fuer eine\n");
					printf(" Figur entscheiden zu koennen und sie nicht einfach nur in einer Ecke stehen-\n");
					printf(" lassen zu muessen.\n");
					espere_tecla();
					figura(29);
					printf(" Waehrend die Dame in der obigen Position mehrere Linie kontrolliert und totale\n");
					printf(" Bewegungsfreiheit hat, ist der weisse Turm von keinerlei Nutzen, weil es sich\n");
					printf(" von der Stelle ruehren kann.\n");
					break;
		case INGLES:	tut();
						gotoxy(0,8);
						printf(" 1. G E N E R A L   C O M M E N T S\n\n");
					printf(" The basic rules of Chess are real simple. The inspiration of the game might\n");
					printf(" have been a battle between two peoples in the middle ages. Each of them has a\n");
					printf(" a specific hierarchy - and the one most-important is - how could it be\n");
					printf(" different the king.\n\n");

					printf(" These are the pieces and the symbols used within the tutorial:\n");
					printf(" One king     [#]\n");
					printf(" One queen    [W]\n");
					printf(" Two rooks    [T]\n");
					printf(" Two bishops  [I]\n");
					printf(" Two knights  [P]\n");
					printf(" Eight pawns  [i]\n\n");
					espere_tecla();
					titulo();
					tut();
					printf(" The battle-field is a board of 64 positions, it is a  square o eight\n");
					printf(" horizontal and eight vertical positions that are - to better distinguish one\n");
					printf(" from the other painted in black and white.\n");
					printf(" To simplify reading games of the Great Masters of Chess and putting down your\n");
					printf(" own games on paper, there is a numeration:\n\n");
					printf(" A, B, C, D, E, F, G, H horizontally e\n");
					printf(" 8, 7, 6, 5, 4, 3, 2, 1 vertically\n\n");
					espere_tecla();
					figura(1);
					printf(" There is an initial position, which must be followed always. The white pieces\n");
					printf(" are set up in lines 7 and 8 in the following way:\n");

					printf(" One full line just pawns in 7 and line 8 like this:\n");
					printf(" Rook - Knight - Bishop - Queen - King - Bishop - Knight - Rook\n");

					espere_tecla();
					figura(2);
					printf(" There they are the heavy pieces - as they are called sometimes - behind a wall\n");
					printf(" of pawns. The rooks look like the turrets of a big castles and kind and queen \n");
					printf(" in the middle draw all of the attention to them. We can observe - by the way -\n");
					printf(" that the position is fairly symetric.\n");
		
					printf(" The black pieces have a initial set-up very alike. There is also a wall of \n");
					printf(" pawns - like Roman soldiers being sent to battle. This wall is positioned in\n");
					printf(" line 2. Behind it, there are the noble pieces:\n\n");
					printf(" Rook - Knight - Bishop - Queen - King - Bishop - Knight - Rook\n\n");
					printf(" Important: King and Queen of the two peoples are in the same column.\n");

					espere_tecla();
					figura(3);
					printf(" After putting these pieces on the board, finally a game can start.\n");

					espere_tecla();
					titulo();
					tut();
					printf(" 1.2. P R E T T Y   C O M M O N   M O V E M E N T S\n\n");
					printf(" The objective of the game is to get the king of the other player checkmate,\n");
					printf(" but what does that mean and how do we get there\?\n");
					printf(" Firstly we have to know that each piece can be moved, can atack another piece\n");
					printf(" or take it off the board. However, each one is different in the way it does\n");
					printf(" that.\n");
					printf(" The piece that is perhaps easiest to understand is the rook. It can move\n");
					printf(" vertically or horizontally to any free position on these lines, that is\n");
					printf(" it can move straight up, down, right and left. If there is a piece of the\n");
					printf(" opponent on the way, it can be removed - but does not have to be. This depends\n");
					printf(" on the strategy of each player.\n");
					espere_tecla();
					figura(4);
					printf(" Let us imagine then that the board is empty and there is just a rook on field\n");
					printf(" A1. This rook can move alternatively to A2, A3, A4, A5, A6, A7, A8 or to B1,\n");
					printf(" C1, D1, E1, F1, G1, H1.\n");

					printf(" Let us figure out now that there is a bishop of the opponent lost in this \n");
					printf(" battle-field on D1. Our rook can move so to the fields A2, A3, A4, A5, A6, A7,\n");
					printf(" A8 or to B1, C1, D1. And what about the bishop on D1\? Well then, if we choose\n");
					printf(" to move our rook to D1, we take the bishop automatically off the board.\n");

					espere_tecla();
					figura(5);
					printf(" Practically all of the pieces function this fairly easy way.\n");
					printf(" The bishop moves diagonally without limits. That is, a bishop on B1 can go to\n");
					printf(" all fields on the diagonal A1 -> H8 and the fields on the small diagonal A3-\n");
					printf(" C3. It can also eliminate the pieces of the opponent on these diagonals.\n");

					espere_tecla();
					figura(6);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" The queen could be considered a mixture between a bishop and a rook. Actually,\n");
					printf(" it combines the abilities of the two making it the most powerful piece on the\n");
					printf(" board. It can move on the diagonals on the horizontal and vertically.\n");
					espere_tecla();
					figura(7);
					printf(" The main characteristic of the knight is to jump. This functions as shown in\n");
					printf(" the following diagram:\n");
					espere_tecla();
					figura(8);
					printf(" We may observe that it does not matter what is on the fields in between that\n");
					printf(" were not marked in the diagram, because the knight simly jumps over them.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" The pawn can - in the initical position - move two fields onwards (in the\n");
					printf(" direction of the opponent) or just one. After the first move it can only\n");
					printf(" walk one field onwards and just so if the field is vacant. Even a piece of\n");
					printf(" the enemy in front of it, it cannot remove. It can take off pieces, though,\n");
					printf(" that are directly asside it on the diagonals in front.\n");
					espere_tecla();
					figura(9);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" The king - in most cases - can move to all fields near to him as show in the\n");
					printf(" following diagram:\n");
					espere_tecla();
					figura(10);
					printf(" However, it may not move into a line of attack, that is, it may not give\n");
					printf(" the opponent the right to take it off the board (which is forebidden by\n");
					printf(" the rules).\n");
					espere_tecla();
					figura(11);
					printf(" In this position the king cannto move into the line E8-E1 as it is \n");
					printf(" controlled by the rook on E3.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 1.3. S O M E T H I N G   S P E C I A L\n\n");
					printf(" After this explanation of the basic rules we need still to get to know some\n");
					printf(" situations that might happen:\n\n");
					printf(" When a pawn arrives at the bottom line of the opponent and in this way \n");
					printf(" cannot keep going, it is changed to whatever piece the player desires - in\n");
					printf(" the mayority of all cases a queen. In the following diagram therefore:\n");

					espere_tecla();
					figura(12);
					printf(" After the movement of the pawn we might find this situation:\n");
					espere_tecla();
					figura(13);
					printf(" A king and a rook can perform a change of places if there is no obstacle\n");
					printf(" in the way, no attack is in the way either and non of the pieces has moved\n");
					printf(" yet. An example:\n");
					espere_tecla();
					figura(14);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" No piece has been moved up to now. After the movement of the king we may find\n");
					printf(" the following positions:\n");
					espere_tecla();
					figura(15);
					figura(16);
					printf(" Finally there is the so-called \"en passent\". Let us have a look at a\n");
					printf(" diagram:\n");
					espere_tecla();
					figura(17);
					printf(" The pawn on D7 may go to D6 or D5. In both cases it can be removed by the\n");
					printf(" white pawn on E5. It it moves to D6, well, that is normal... if it moves\n");
					printf(" to D5 it may be taken \"en passent\", that is, passing by. The final position\n");
					printf(" in both cases is:\n");
					espere_tecla();
					figura(18);
					printf(" The final objective of the games is to give the king of the opponent a \n");
					printf(" check-mate. For that, first of all the king has to be in check. Check is the\n");
					printf(" attack of the king by any other piece. An example:\n");
					espere_tecla();
					figura(19);
					printf(" Here the king is in the line of attack of the bishop. Whenever it is in the\n");
					printf(" line of attack of somebody it has to eliminate the situation of attack, that \n");
					printf(" or move out of it, hide behind another piece or eliminate the piece that is\n");
					printf(" attacking. In the present situation the king can only flee out of the line of\n");
					printf(" attack as there is no other piece around nor is the enemy in reach. That gives\n");
					printf(" us the following possibilities:\n");
					espere_tecla();
					figura(20);
					printf(" When there is no more way of eliminating the attack of the king we speak of\n");
					printf(" Check-Mate. Some classical situations:\n");
					espere_tecla();
					figura(21);
					printf(" The king is being attacked by a rook and cannot move away as the next line\n");
					printf(" is being controlled by the other rook.\n");
					espere_tecla();
					figura(22);
					printf(" In this position the king is being \"nailed to the wall\" by the queen on D2.\n");
					printf(" It is important to observe that the queen has to be protected by another\n");
					printf(" piece as it could be simply removed by the king in any other case.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" There are players that are real damn unlucky. And exactly these do not \n");
					printf(" remember that a king to be Check-Mate has to also be in Check. What can \n");
					printf(" happen then is a stalemate, meaning a tie between the two players - as in\n");
					printf(" the following diagram:\n");
					espere_tecla();
					figura(23);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					gotoxy(0,8);
					printf(" 2. A   L I T T L E   B I T   O F   S T R A T E G Y\n\n");
					printf(" The part that follows is short and objective. It is not meant as an attempt\n");
					printf(" of substituting the excellent literature that is on the market, but mainly\n");
					printf(" as giving a first rough idea of how a game could be won.\n\n"); 
					printf(" 2.1. A T T A C K S\n\n");
					printf(" As already said before, a piece can attack another one, that is, it can \n");
					printf(" threaten to remove it. It is important to know that generally we must protect\n");
					printf(" our pieces threatening ourselves to retake any piece of the opponent that \n");
					printf(" would remove one of ours. If - or not - a battle is worthwhile, is \n");
					printf(" (advantages of position not taken into account) pure mathematics. Each piece\n");
					printf(" has a strategical value:\n");
					espere_tecla();
					titulo();
					tut();
					printf(" Here go the figures:\n\n");
					printf(" Queen:  9\n");
					printf(" Rook:   5\n");
					printf(" Bishop: 3\n");
					printf(" Knight: 3\n");
					printf(" Pawn:   1\n\n");
					printf(" Considering this we must search to at least find exchanges of the same value.\n");
					printf(" It should be reminded that also mere simplifications (loosing the same pieces\n");
					printf(" on both sides) is also of advantage. This kind of attack and counter-attack\n");
					printf(" may happen in the following position:\n");
					espere_tecla();
					figura(24);
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Black or also White in this position may start an exchange of queens. However,\n");
					printf(" Black might not like the idea a lot because his disadvantage of points would\n");
					printf(" be even more obvious then.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.2. D O U B L E   T R O U B L E\n\n");
					printf(" A double attack is an attack of two different pieces that each attack a piece\n");
					printf(" of the opponent.\n");
					espere_tecla();
					figura(25);
					printf(" Black in this position may choose from his sofa which one of the two pieces\n");
					printf(" he likes most. However, this position only gets real nasty when the player\n");
					printf(" in attack has the choice which of his pieces will walk the plank (as he\n");
					printf(" cannot perform two moves at one time).\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.3. F O R K S\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" A fork is highly similar to the double attack. Also the other player will have\n");
					printf(" to decide which piece he will loose. But this time only one piece attacks two.\n");
					printf(" A classical case is a knight threatening a queen and a rook at the same time.\n");
					printf(" Typical as well, but even worse, is a knight attacking a queen and giving\n");
					printf(" Check in one move. As the king has to evade the attack the queen is gone and\n");
					printf(" the game is already half-way finished.\n");
					espere_tecla();
					figura(26);
					printf(" In this case there is really no alternative if not putting the king on\n");
					printf(" D1 and at least executing a (not quite good) exchange.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.4. B L O C K S\n\n");
					printf(" A piece is blocked of it is found inside a line of attack of one piece of\n");
					printf(" the opponent and a piece of your own thus making it impossible to put the\n");
					printf(" piece to another place if you do not want to say goodbye to the one on\n");
					printf(" behind.\n");
					printf(" A piece is truly blocked when the king is hiding behind it. Moving the\n");
					printf(" the piece in the front to another place is prohibited by the rules.\n");
					printf(" Let us have a look at an example:\n");
					espere_tecla();
					figura(27);
					printf(" The bishop on E5 cannot walk to another field because this would cause\n");
					printf(" Check to the king on G5. It is therefore truly blocked.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.5. I N F L U E N C E   O N   T H E   C E N T R E\n\n");
					//      ....x....1....x....2....x....3....x....4....x....5....x....6....x....7....x....8
					printf(" Influence on the centre of the board is especially important in the beginning\n");
					printf(" of the game. In the opening itself and right after it players normally \n");
					printf(" concentrate on the central square - perhaps because the most powerful pieces\n");
					printf(" are nearby but surely to develop the pieces correctly, which is not happening\n");
					printf(" with a beginning on the side.\n");
					espere_tecla();
					figura(28);
					printf(" In the position above it can be verified that the first battle will happen\n");
					printf(" in the central square. This is a typical case and the model should be followed\n");
					printf(" always.\n");
					espere_tecla();
					titulo();
					tut();
					printf(" 2.6. CONTROL OF LINES AND LIBERTY OF MOVEMENT\n\n");
					printf(" During the middle of the game and up to the end control of lines and liberty\n");
					printf(" of movement can be considered important.\n");
					printf(" To control a line means to theaten anybody who enters with elimination.\n");
					printf(" Liberty of movement means to have the possibility to choose between a lot\n");
					printf(" of movements for one piece - especially when the piece is important - and\n");
					printf(" not to leave it stuck in a corner of the board.\n");
					espere_tecla();
					figura(29);
					printf(" Whereas the queen in this position controls various lines and has total\n");
					printf(" liberty of movement, the white rook does not serve for anything as it is stuck.\n");
					break;
	}
	espere_tecla();
}

void console::menu_ajuda(int nro)
{
	espere_tecla();
	titulo();
	aj();
	switch(nro)
	{
		case 0: escreve_menu_palido(20,12,21); break;
		case 1: escreve_menu_palido(20,10,10); break;
		case 2: escreve_menu_palido(20,11,64); break;
		case 3: escreve_menu_palido(20,11,30); break;	
		case 4: escreve_menu_palido(10,9,40); break;
	}
	espere_tecla();
	titulo();
	aj();
}

void console::ajuda(void)
{
	console io;
	io.titulo();    // nao o titulo completo para ter mais espaco;
	aj();
	switch(lingua)
	{
		case PORTUGUES: 	printf("   1.  I N S T A L A C A O   D O   P R O G R A M A\n");
					printf("   \n");
					printf("   O programa de instalacao fornecido no disquete instala Monarch no seu \n");
					printf("   Winchester criando a pasta \"monarch\" no drive c:\\ e copiando o executavel \n");
					printf("   do programa para tal pasta.\n");
					printf("   \n");
					printf("   O programa de instalacao pode ser chamado do Windows Explorer clicando no \n");
					printf("   icone \"install\" ou atraves do prompt do DOS digitando:\n");
					printf("   \n");
					printf("   a: [enter]\n");
					printf("   install [enter]\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
	
					printf("   2.  E X E C U C A O   D O   P R O G R A M A \n");
					printf("   \n");
					printf("   O programa Monarch pode ser chamado atraves do Windows Explorer clicando em \n");
					printf("   cima do icone \"Monarch\" (aplicativo) ou atraves do prompt do DOS com:\n");
					printf("   \n");
					printf("   cd c:\\ [enter]\n");
					printf("   cd monarch [enter]\n");
					printf("   monarch [enter]\n");
					printf("   \n");
					printf("   3.  C O N S I D E R A C O E S   G E R A I S\n");
					printf("   \n");
					printf("   A interface do programa Monarch e uma interface texto. Sendo assim ele roda \n");
					printf("   em todos os computadores pessoais modernos com Windows 95, Windows 98 ou \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   Windows NT. O funcionamente dele em computadores com DOS nao foi testado, \n");
					printf("   porem, provavelmente ele pode ser executado nestes computadores tambem.\n");
					printf("   \n");
					printf("   Para uma execucao mais rapida recomenda-se um Pentium 233 Mhz ou melhor, \n");
					printf("   mas mesmo em Pentiums de 100 Mhz ele ainda apresenta um desenvolvimento \n");
					printf("   razoavel.\n");
					printf("   \n");
					printf("   Monarch e completamente gerenciado por Menus, isto e, listas de opcoes em \n");
					printf("   quais o usuario pode escolher o que deseja.\n");
					printf("   \n");
					printf("   Para escolher basta usar as teclas do cursor colocando a barra azul em cima \n");
					printf("   da opcao desejada e confirmar com [enter] ou [return]. Se por alguma razao \n");
					printf("   as teclas do cursor nao funcionarem em seu computador, pode-se tambem usar \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   os numeros 8, 4, 6, 2 no teclado normal ou no teclado numerico (o que e \n");
					printf("   recomendado neste caso) e 5 para confirmar.\n");
					printf("   \n");
					printf("   4.  E S C O L H A   D A   L I N G U A   D E   O P E R A C A O\n");
					printf("   \n");
					printf("   O programa Monarch pode operar como um todo em tres linguas: Portugues, \n");
					printf("   Alemao e Ingles. Apos a execucao do programa primeiramente o menu de \n");
					printf("   linguas e exibido:\n");

					menu_ajuda(0);

					printf("   Basta ecolher a lingua em que desejar operar o programa. Nota-se que este \n");
					printf("   menu em si e tri-lingue - a partir da definicao da lingua os menus somente \n");
					printf("   serao nesta lingua.\n");
					printf("   \n");
					printf("   Mais para a frente no programa ainda existe a possibilidade de redefinir a \n");
					printf("   lingua de operacao em casos de erro. Porem, recomenda-se nao errar neste \n");
					printf("   primeiro menu, se nao conhecer todas as linguas, para nao se perder depois.\n");
					printf("   \n");
					printf("   5.  O   M E N U   P R I N C I P A L\n");
					printf("   \n");
					printf("   Apos a definicao da lingua e exibido o menu principal do programa:\n");

					menu_ajuda(1);

					printf("   A partir dele entao serao disponiveis as seguintes opcoes:\n");
					printf("   \n");
					printf("   5. 1.  S o b r e   o   S i s t e m a\n");
					printf("   \n");
					printf("   Com esta opcao informacoes gerais sobre o sistema serao apresentadas (2 \n");
					printf("   paginas). Para ler a segunda pagina ou finalizar, basta apertar qualquer \n");
					printf("   tecla.\n");
					printf("   \n");
					printf("   5. 2.  J o g a r :   J o g a d o r   x   J o g a d o r\n");
					printf("   \n");
					printf("   Com esta opcao pode-se jogar Xadrez em dois jogadores humanos. O sistema \n");
					printf("   Monarch neste caso somente funcionara como juiz acusando jogadas invalidas, \n");
					printf("   Xeque, Xeque-Mate etc. (veja tambem item 6 \"COMO JOGADR\").\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 3.  J o g a r :   J o g a d o r   x   M O N A R C H\n");
					printf("   \n");
					printf("   Nesta opcao um jogador humano jogara contra o sistema Monarch. O jogador \n");
					printf("   humano ficara com as pecas brancas enquanto o sistema Monarch jogara com as \n");
					printf("   pretas.\n");
					printf("   \n");
					printf("   5. 4.  J o g a r :   M O N A R C H   x   J o g a d o r\n");
					printf("   \n");
					printf("   Aqui tambem um jogador humano jogara contra o sistema Monarch. Porem, desta \n");
					printf("   vez o sistema Monarch comecara com o jogo (utilizando as pecas brancas).\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 5.  J o g a r :   M O N A R C H   x   M O N A R C H\n");
					printf("   \n");
					printf("   Se quiser pode-se ate assistir uma partir do sistema Monarch contra si \n");
					printf("   mesmo escolhendo esta opcao.\n");
					printf("   \n");
					printf("   5. 6.  C o n f i g u r a c o e s\n");
					printf("   \n");
					printf("   Atraves desta opcao pode-se acessar o menu de configuracoes (veja item 7.).\n");
					printf("   \n");
					printf("   5. 7.  T u t o r i a l\n");
					printf("   \n");
					printf("   Principalmente para quem nao sabe jogar Xadrez ainda, mas tambem para quem \n");
					printf("   precisa de uma referencia a respeito das regras e estrategicas basicas, \n");
					
					espere_tecla();
					titulo();
					aj();
	
					printf("   esta opcao foi criada. O tutorial conta com varios diagramas e quase 70 \n");
					printf("   telas no total. Para acessar a proxima tela basta apertar qualquer tecla. \n");
					printf("   Em caso de erro ou se quiser terminar a leitura outra hora, pode se sair do \n");
					printf("   tuturial mantendo a tecla [espaco] pressionada ate aparecer o menu \n");
					printf("   principal de volta.\n");
					printf("   \n");
					printf("   5. 8.  A j u d a\n");
					printf("   \n");
					printf("   E a presente opcao de ajuda que fornece informacoes para ajudar o iniciante \n");
					printf("   no sistema a conseguir utilizar ele. Para acessar a proxima tela basta \n");
					printf("   apertar qualquer tecla.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5.9.  S A I R   D O   P R O G R A M A\n");
					printf("   \n");
					printf("   Se quiser terminar o programa pode-se escolher esta opcao. Por questoes de \n");
					printf("   seguranca o sistema Monarch pede confirmacao perguntando se tem certeza. \n");
					printf("   Neste caso e so responder com \"s\" de \"sim\" e o programa termina. Caso \n");
					printf("   contrario o programa volta para o menu principal.\n");
					printf("   \n");
					printf("   6.  C O M O   J O G A R\n");
					printf("   \n");
					printf("   Em qualquer das opcoes de jogo, logo o tabuleiro de Xadrez com as figuras \n");
					printf("   sera exibido.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   Escolhendo uma das opcoes para jogar Xadrez com pelo menos um jogador \n");
					printf("   humano no tabuleiro, o jogador podera escolher seu movimento da seguinte \n");
					printf("   maneira:\n");
					printf("   \n");
					printf("   Posicionar o cursor > _ < em cima da peca que quiser mover. Isto e feito \n");
					printf("   atraves das teclas de cursor ou as teclas numericas (como descrito em 3). \n");
					printf("   Para confirmar deve-se apertar [5] ou [return] ou [enter]. \n");
					printf("   \n");
					printf("   Para confirmar que a peca foi escolhida o sistema coloca um \"I\" verde em \n");
					printf("   cima do cursor.\n");
					printf("   \n");
					printf("   Agora e so mover o cursor para o lugar de destino e confirmar novamente.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					gotoxy(0,8);
					printf("   Cuidado: Nao pode-se voltar a jogada, entao a segunda confirmacao nao deve \n");
					printf("   ser feita se nao tiver certeza do movimento.\n");
					printf("   \n");
					printf("   Se quiser largar uma peca escolhida de volta, deve-se fazer a segunda \n");
					printf("   confirmacao no lugar de origem mesmo. Monarch retornara um erro e iniciara \n");
					printf("   o processo de escolha novamente.\n");
					printf("   \n");
					printf("   Se o jogador tiver escolhido uma jogada invalida, um lugar sem peca ou por \n");
					printf("   engano uma peca do inimigo, Monarch acusa tal erro e deixa o jogador fazer \n");
					printf("   uma nova escolha.\n");
					printf("   \n");
					printf("   Apos a jogada feita o sistema Monarch coloca um \"o\" azul no canto esquerdo \n");
					printf("   superior do lugar de destino para marcar o ultimo movimento feito. Isto \n");
					printf("   facilita principalmente a leitura em jogos contra o computador.\n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   \n");
					printf("   No lado direito do tabuleiro pode-se acessar um menu de opcoes movendo o \n");
					printf("   cursor para fora do canto direito do tabuleiro:\n");
		
					menu_ajuda(2);

					printf("   Pode-se entao:\n");
					printf("   \n");
					printf("   6. 1.  L e r   P o s i c a o\n");
					printf("   \n");
					printf("   Escolhendo esta opcao pode-se ler uma posicao pre-gravada do disco \n");
					printf("   fornecendo o nome do arquivo. \n");
					printf("   \n");
					printf("   6. 2.  S a l v a r   P o s i c a o\n");
					printf("   \n");
					printf("   E possivel salvar a posicao atual em disco fornecendo um nome de arquivo.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					gotoxy(0,8);
					printf("   6. 3.  D e s i s t i r   d a   P a r t i d a\n");
					printf("   \n");
					printf("   Pode-se desistir da partida atual escolhendo esta opcao. O sistema Monarch \n");
					printf("   pedira confirmacao e apos ter apertado \"s\" de \"sim\" o sistema informara a \n");
					printf("   desistencia e voltara ao menu principal.\n");
					printf("   \n");
					printf("   6. 4.  V O L T A R   P A R A    O   T A B U L E I R O \n");
					printf("   \n");
					printf("   Se tiver acessado o menu por engano pode-se voltar para o tabuleiro \n");
					printf("   confirmando esta opcao. \n");
					printf("   \n");
					printf("   7.  O   M E N U   D E   C O N F I G U R A C O E S\n");
					printf("   \n");
					printf("   Este e o menu de configuracoes:\n");

					menu_ajuda(3);

					printf("   No menu de configuracoes pode-se modificar a lingua operacional no caso de \n");
					printf("   algum engano no comeco ou por curiosidade para ver como o programa fica em \n");
					printf("   outra lingua. O menu chamado a partir da primeira opcao e o mesmo menu do \n");
					printf("   inicio (veja 4).\n");
					printf("   \n");
					printf("   Pode-se tambem configurar o algoritmo do computador, ou melhor, a maneira \n");
					printf("   como ele joga. Escolhendo esta segunda opcao sera exibido o seguinte menu:\n");

					menu_ajuda(4);

					printf("   Aqui pode-se escolher entre os dois modos padrao, em quais o computador \n");
					printf("   jogara da maneira mais forte que puder utilizando todos os analisadores, ou \n");
					printf("   um jogador simulado que cometara \"erros humanos\".\n");
					printf("   \n");
					printf("   Com a opcao \"SAIR PARA O MENU PRINCIPAL\" pode-se voltar ao menu principal.\n");
					espere_tecla();

					break;

		case ALEMAO:	printf("   1.  I N S T A L L A T I O N   D E S   P R O G R A M M S \n");
					printf("   \n");
					printf("   Das Installationsprogramm, was sich auf der gelieferten Diskette befinden \n");
					printf("   sollte, installiert Monarch auf ihre Festplatte indem es ein Verzeichnis \n");
					printf("   \"monarch\" auf dem Drive c:\\ anlegt und das Programm als solches \n");
					printf("   hineinkopiert.\n");
					printf("   \n");
					printf("   Das Installationsprogramm kann ueber den Windows Explorer per Anklicken des \n");
					printf("   Icons \"install\" (Anwendung) ausgefuehrt werden oder vom DOS-Prompt aus mit:\n");
					printf("   \n");
					printf("   a: [enter]\n");
					printf("   install [enter]\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();

					printf("   2.  S T A R T   D E S   P R O G R A M M S \n");
					printf("   \n");
					printf("   Das Programm kann ueber den Windows Explorer durch Klicken auf das Icon \n");
					printf("   \"Monarch\" (Anwendung) gestartet werden oder ueber das DOS-Prompt:\n");
					printf("   \n");
					printf("   cd c:\\ [enter]\n");
					printf("   cd monarch [enter]\n");
					printf("   monarch [enter]\n");
					printf("   \n");
					printf("   3.  A L L G E M E I N E S\n");
					printf("   \n");
					printf("   Die Benutzeroberflaeche des Programms Monarch benutzt lediglich den \n");
					printf("   Textmodus. Auf diese Art und Weise sollte das Programm auf allen modernen \n");

					espere_tecla();
					titulo();
					aj();
				
					printf("   PCs laufen, die Windows 95, 98 oder NT als Betriebssystem installiert \n");
					printf("   haben. Die Funktionstuechtigkeit wurde auf Rechnern mit MS-DOS nicht \n");
					printf("   getestet, allerdings ist anzunehmen, dass das Programm auch auf diesen \n");
					printf("   Maschinen laeuft.\n");
					printf("   \n");
					printf("   Um eine angenehme Verarbeitsgeschwindigkeit zu garantieren, empfiehlt sich \n");
					printf("   die Benutzung eines Pentium 233 MHz oder besser. Auch auf Pentium 100 MHz \n");
					printf("   ist die Geschwindigkeit aber in aller Regel noch ertraeglich.\n");
					printf("   \n");
					printf("   Monarch ist ein menuegesteuertes Programm, d.h., mit diversen Optionslisten \n");
					printf("   kann der Benutzer die Verarbeitung bestimmen.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   Um in einem Menue eine Option auszuwaehlen, muss man nur den blauen Balken \n");
					printf("   mit den Cursortasten auf die jeweilige Option bewegen und mit [enter] oder \n");
					printf("   [return] bestaetigen. Falls - aus welchem Grund auch immer - auf ihrem \n");
					printf("   Rechner die Steuerung per Cursortasten nicht funktionieren sollte, so \n");
					printf("   laesst sich dasselbe Resultat anhand der Tasten 8, 4, 6, 2, und 5 zum \n");
					printf("   Bestaetigen erreichen. Vorzugsweise benutzen sie in diesem Fall die Tasten \n");
					printf("   des abgesetzten nummerischen Tastenblocks.\n");
					printf("   \n");
					printf("   4.  A U S W A H L   D E R   O P E R A T I O N S S P R A C H E\n");
					printf("   \n");
					printf("   Das Programm Monarch kann komplett in drei Sprachen laufen: Portugiesisch, \n");
					printf("   Deutsch und Englisch. Nach dem Laden des Programms wird das Sprachenmenue \n");
					printf("   als erstes aufgerufen:\n");
					
					menu_ajuda(0);
					
					printf("   Hier muessen sie dann lediglich die geschwuenschte Sprache auswaehlen. Es \n");
					printf("   bleibt zu bemerken, dass nur dieses eine Menue dreisprachig ist, alle \n");
					printf("   weiteren Menues werden sie dann in der gewaehlten Sprache vorfinden.\n");
					printf("   \n");
					printf("   Falls sie sich bei der Auswahl der Sprache geirrt haben sollten, laesst \n");
					printf("   sich dieser Fehler spaeter noch korrigieren. Allerdings empfiehlt es sich, \n");
					printf("   die Auswahl schon sofort richtig zu treffen, falls sie eine der Sprachen \n");
					printf("   nicht beherrschen sollten.\n");
					printf("   \n");
					printf("   5.  D A S   H A U P T M E N U E\n");
					printf("   \n");
					printf("   Nach der Definition der Sprache wird das Hauptmenue aufgerufen:\n");
					
					menu_ajuda(1);

					gotoxy(0,8);
					printf("   Es sind folgende Optionen vorhanden:\n");
					printf("   \n");
					printf("   5. 1.  A l l g e m e i n e   I n f o r m a t i o n e n\n");
					printf("   \n");
					printf("   Nach dem Anwaehlen dieser Option werden allgemeine Informationen zum \n");					
					printf("   Programm (2 Bildschirmseiten) angezeigt. Um zur zweiten Seite bzw. zurueck \n");
					printf("   zum Hauptmenue zu gelangen, muessen sie lediglich eine beliebige Taste \n");
					printf("   druecken.\n");
					printf("   \n");
					printf("   5. 2.  S p i e l e n :   S p i e l e r   x   S p i e l e r\n");
					printf("   \n");
					printf("   Mit dieser Option koennen sie Schach im Zwei-Spieler-Modus spielen. Monarch\n");
					printf("   wird hierbei nur die Rolle des Schiedsrichters uebernehmen, Fehler anmahnen\n");
					printf("   sowie Schach und Schachmatt anzeigen (siehe auch 6 \"SO WIRD GESPIELT\").\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 3.  S p i e l e n :   S p i e l e r   x   M O N A R C H\n");
					printf("   \n");
					printf("   Nach Auswahl dieses Menuepunktes kann ein Spieler gegen das System Monarch \n");
					printf("   spielen. Der Spieler wird hierbei beginnen und mit den weissen Figuren \n");
					printf("   spielen.\n");
					printf("   \n");
					printf("   5. 4.  S p i e l e n :   M O N A R C H   x   S p i e l e r\n");
					printf("   \n");
					printf("   Mit dieser Option spielt Monarch gegen einen Spieler, der in diesem Fall \n");
					printf("   die schwarzen Figuren erhaelt.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
	
					printf("   5. 5.  S p i e l e n :   M O N A R C H   x   M O N A R C H\n");
					printf("   \n");
					printf("   Man kann auch Monarch dabei zusehen, wie er eine Partie gegen sich selbst \n");
					printf("   spielt.\n");
					printf("   \n");
					printf("   5. 6.  E i n s t e l l u n g e n\n");
					printf("   \n");
					printf("   Hiermit gelangen sie zum Einstellungsmenue (siehe 7.).\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();

					printf("   5. 7.  A n l e i t u n g   z u m   S c h a c h s p i e l e n\n");
					printf("   \n");
					printf("   Insbesondere fuer einen Neuling geschrieben, aber auch fuer einen etwas 	\n");
					printf("   fortgeschritteneren Spieler immer noch eine nuetzliche Sache. Es werden\n");
					printf("   alle Regeln erklaert und auch einige Hinweise zu taktischen und \n");
					printf("   strategischen Modellen gegeben. Die Anleitung umfasst fast 70 \n");
					printf("   Bildschirmseiten mit diversen Diagrammen. Falls sie diese Option \n");
					printf("   versehentlich ausgewaehlt haben sollten, oder spaeter weiterlesen moechten, \n");
					printf("   brauchen sie nur die Leertaste gedrueckt zu halten bis das Hauptmenue \n");
					printf("   wieder erscheint. Ansonsten gelangen sie mit jedweder Taste zur naechsten \n");
					printf("   Seite.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 8.  H i l f e\n");
					printf("   \n");
					printf("   Dieser Hilfstext, der dem Einsteiger das Ruestzeug fuer die korrekte \n");
					printf("   Benutzung des Programmes geben soll.\n");
					printf("   \n");
					printf("   5. 9.  P R O G R A M M   V E R L A S S E N\n");
					printf("   \n");
					printf("   Mit dieser Option verlassen sie das Programm. Vor dem Verlassen bittet \n");
					printf("   Monarch um Bestaetigung, indem er sie fragt, ob sie sicher sind. \n");
					printf("   Beantworten sie diese Frage mit \"j\" fuer \"ja\" so wird das Programm beendet. \n");
					printf("   Anderenfalls gelangen sie zurueck zum Hauptmenue.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   6.  S O   W I R D   G E S P I E L T\n");
					printf("   \n");
					printf("   Sobald sie ausgewaehlt haben, Schach zu spielen, wird das Schachbrett auf \n");
					printf("   der linken Seite aufgebaut.\n");
					printf("   \n");
					printf("   Falls an dem Spiel ein menschlicher Spieler teilnimmt, so kann er auf  \n");
					printf("   folgende Art und Weise spielen:\n");
					printf("   \n");
					printf("   Den Cursor > _ < auf die Figur bewegen, die gezogen werden soll. Dies kann \n");
					printf("   mit den Cursortasten oder den nummerischen Tasten (siehe 3.) geschehen. Zum \n");
					printf("   Bestaetigen druecken sie [5] oder [return] oder [enter].\n");
					printf("   \n");
					printf("   Monarch zeigt nun als Quittierung der Auswahl ein gruenes \"I\" ueber dem \n");
					printf("   Cursor an.\n");
					
					espere_tecla();
					titulo();
					aj();

					printf("   Nun muessen sie lediglich den Cursor zum Zielfeld bewegen und erneut \n");
					printf("   bestaetigen.\n");
					printf("   \n");
					printf("   Achtung: Es koennen bei Monarch keine Zuege zurueckgenommen werden, also \n");
					printf("   bestaetigen sie nichts, von dem sie nicht ueberzeugt sind.\n");
					printf("   \n");
					printf("   Falls sie eine bereits zum Zug ausgewaehlte Figur doch nicht ziehen \n");
					printf("   moechten, so stellen sie sie mit einem erneuten [enter] ueber der \n");
					printf("   Ausgangsposition wieder an den alten Ort. Monarch wird eine Fehlermeldung \n");
					printf("   anzeigen und sie koennen eine neue Auswahl treffen.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   Dasselbe gilt uebrigens auch falls sie einen ungueltigen Zug vornehmen \n");
					printf("   wollen, ein leeres Feld zum Zug ausgewaehlt haben oder mit den Figuren des \n");
					printf("   Gegners ziehen moechten. Monarch zeigt jeweils eine Fehlermeldung an, und \n");
					printf("   sie sind aufgeforder, eine neue Auswahl zu treffen.\n");
					printf("   \n");
					printf("   Nachdem die Figur erfolgreich gefuehrt wurde, wird in der linken oberen \n");
					printf("   Ecke des Zielfeldes ein blaues \"o\" als Markierung angezeigt. Es ist \n");
					printf("   insbesondere auch nuetzlich um zu sehen, wohin der Computer gezogen hat.\n");
					printf("   \n");
					printf("   Auf der rechten Seite des Bildschirms koennen sie ein Optionenmenue \n");
					printf("   erreichen, indem sie den Cursor ueber den rechten Rand des Spielfeldes \n");
					printf("   hinausbewegen:\n");

					menu_ajuda(2);

					gotoxy(0,8);
					printf("   6. 1.  P o s i t i o n   l a d e n\n");
					printf("   \n");
					printf("   Nach Wahl dieses Menuepunktes kann eine Position unter Angabe des \n");
					printf("   Dateinamen geladen werden.\n");
					printf("   \n");
					printf("   6. 2.  P o s i t i o n   a b s p e i c h e r n\n");
					printf("   \n");
					printf("   Sie koennen hiermit die aktuelle Position speichern indem sie einen \n");
					printf("   Dateinamen auswaehlen.\n");
					printf("   \n");
					printf("   6. 3.  A u f g e b e n   ( P a r t i e   b e e n d e n )\n");
					printf("   \n");
					printf("   Keine Lust mehr oder ist die Lage aussichtslos\? Dann koennen sie mit diesem \n");
					printf("   Menuepunkt aufgeben und kommen nach Bestaetigung zurueck zum Hauptmenue.\n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   6. 4.  Z U R U E C K   A U F S   S C H A C H B R E T T \n");
					printf("   \n");
					printf("   Wenn sie nur versehentlich ueber den rechten Brettrand hinausgekommen sind, \n");
					printf("   kommen sie mit dieser Option wieder zurueck.\n");
					printf("   \n");
					printf("   7.  D A S   E I N S T E L L U N G S M E N U E\n");
					printf("   \n");
					printf("   Dies ist das Einstellungsmenue:\n");
					
					menu_ajuda(3);
					
					printf("   Sie koennen hier eine andere Operationssprache auswaehlen, falls sie sich \n");
					printf("   bei Programmaufruf vertan haben sollten oder nur sehen moechten, wie das \n");
					printf("   Programm denn in einer anderen Sprache aussieht. Das mit der ersten Option \n");
					printf("   aufgerufene Menu ist dasselbe des Programmstarts (siehe also 4).\n");
					printf("   \n");
					printf("   Sie koennen auch den Computeralgorithmus bestimmen, oder besser gesagt, die \n");
					printf("   Art und Weise, wie der Computer spielen soll. Das geschieht mit dem zweiten \n");
					printf("   Menuepunkt und ruft folgendes Untermenue auf:\n");
		
					menu_ajuda(4);

					printf("   Hier koennen sie dann zwischen zwei Standardmodi und mehreren simulierten\n"); 
					printf("   Spielern auswaehlen. Im Standardmodus spielt der Computer so gut er kann \n");
					printf("   mit allen Analyseroutinen, waehrend simulierte Spieler absichtlich \n");
					printf("   \"menschliche Fehler\" machen.\n");
					printf("   \n");
					printf("   Mit der letzten Option schliesslich gelangt man wieder zurueck zum \n");
					printf("   Hauptmenue.\n");
					
					espere_tecla();
					break;
		case INGLES:	printf("   1.  I N S T A L L A T I O N\n");
					printf("   \n");
					printf("   The installation-program on the program disc installs Monarch on your hard-\n");
					printf("   drive by creating a new directory on drive c:\\ called \"monarch\" and copying \n");
					printf("   the program itself to that directory.\n");
					printf("   \n");
					printf("   The installation-program can be run through Windows Explorer by clicking on \n");
					printf("   the application \"install\" or from DOS-prompt typing:\n");
					printf("   \n");
					printf("   a: [enter]\n");
					printf("   monarch [enter]\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   2.  R U N N I N G   T H E   P R O G R A M\n");
					printf("   \n");
					printf("   The program can be run from Windows Explorer by clicking on the application \n");
					printf("   \"monarch\" or from DOS-prompt like this:\n");
					printf("   \n");
					printf("   cd c:\\ [enter]\n");
					printf("   cd monarch [enter]\n");
					printf("   monarch [enter]\n");
					printf("   \n");
					printf("   3.  G E N E R A L   I N F O R M A T I O N\n");
					printf("   \n");
					printf("   The inferface of the program is text-only. Thus it will run on all modern \n");
					printf("   personal-computers with Windows 95, Windows 98 or Windows NT installed. \n");
					
					espere_tecla();
					titulo();
					aj();	
	
					gotoxy(0,8);
					printf("   Actually it should also run on plain DOS-machines, however, this feature \n");
					printf("   was not tested.\n");
					printf("   \n");
					printf("   For a smoother execution a Pentium 233 MHz or higher is recommended. \n");
					printf("   Though, even on a Pentium 100 MHz the velocity normally is still ok.\n");
					printf("   \n");
					printf("   Monarch makes use of menus, that is, lists of options from which the user \n");
					printf("   may choose what he wants.\n");
					printf("   \n");
					printf("   To choose an option from a menu the user may simply employ the cursor-keys \n");
					printf("   highlighting the option he wants and confirming with [enter] or [return]. \n");
					printf("   If - out of some strange reason - on your PC the cursor-keys will not do \n");
					printf("   the job, you may simply choose by using 8, 4, 6, 2 and 5 to confirm on the \n");
					printf("   numeric key-pad (or on the normal keyboard).\n");
					
					espere_tecla();
					titulo();
					aj();
					
					printf("   4.  C H O I C E   O F   L A N G U A G E\n");
					printf("   \n");
					printf("   The program is able to operate as a whole in three languages: Portuguese, \n");
					printf("   German and English. After loading the program the first menu to be shown is \n");
					printf("   the language-menu:\n");
					
					menu_ajuda(0);
					
					printf("   You may simply choose the operation-language that you like best. Please \n");
					printf("   note that this is the only menu really using the three languages at the \n");
					printf("   same time - after the definition of the language the program will only \n");
					printf("   operate using the chosen tongue.\n");
					printf("   \n");
					printf("   Later on in the program there is still the possibility to redefine this \n");
					printf("   option in case of error. However, beware of choosing a language that you do \n");
					printf("   not know in the first menu, because you might get lost in the program.\n");
					printf("   \n");
					printf("   5.  M A I N   M E N U\n");
					printf("   \n");
					printf("   After the definition of the language the main menu is shown:\n");

					menu_ajuda(1);

					printf("   You may choose from the following options:\n");
					printf("   \n");
					printf("   5. 1.  A b o u t   t h i s   p r o g r a m\n");
					printf("   \n");
					printf("   This will show general information about the program (two pages). To go to \n");
					printf("   the second page or go back to the main menu simply press any key.\n");
					printf("   \n");
					printf("   5. 2.  P l a y :   P l a y e r     x   P l a y e r\n");
					printf("   \n");
					printf("   Choosing this option you may enjoy a two-player-game. Monarch will \n");
					printf("   supervise the game not allowing illegal moves and informing Check, Check-\n");
					printf("   Mate etc. (see also item 6 \"HOW TO PLAY\").\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 3.  P l a y :   P l a y e r     x   M O N A R C H\n");
					printf("   \n");
					printf("   With this option a human player can play against Monarch. In this case the \n");
					printf("   player will play with the white pieces and start the game.\n");
					printf("   \n");
					printf("   5. 4.  P l a y :   M O N A R C H   x   P l a y e r\n");
					printf("   \n");
					printf("   Same as 5.3., however, this time Monarch will start and play with the white \n");
					printf("   pieces.\n");
					printf("   \n");
					printf("   5. 5.  P l a y :   M O N A R C H   x   M O N A R C H \n");
					printf("   \n");
					printf("   You may even watch Monarch play against himself with this option.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
	
					printf("   5. 6.  C o n f i g u r a t i o n\n");
					printf("   \n");
					printf("   Here you can access the configurations-menu (see item 7).\n");
					printf("   \n");
					printf("   5. 7.  T u t o r i a l\n");
					printf("   \n");
					printf("   It is mainly written for absolute green-horns when it comes to Chess, \n");
					printf("   however, even players that are a little bit more advanced may find some \n");
					printf("   useful information in it. The tutorial contains various diagrams and has \n");
					printf("   almost 70 screens of information. To access the following page just press \n");
					printf("   any key. And if you got there by mistake or would like to give it a break, \n");
					printf("   you may simply hold down the [space] key until the main menu appears \n");
					printf("   again.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   5. 8.  H e l p \n");
					printf("   \n");
					printf("   This text which is designed to help beginners to better understand how this \n");
					printf("   program works. To go to the next sreen also simply hit any key.\n");
					printf("   \n");
					printf("   5. 9.  L E A V E   T H E   P R O G R A M\n");
					printf("   \n");
					printf("   If you wish to leave the program then choose this option. The system will \n");
					printf("   ask you to confirm by displaying \"are you sure\?\" and with \"y\" for \"yes\" you \n");
					printf("   will finish the program. Any other key gets you right back to the main \n");
					printf("   menu.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   6.  H O W   T O   P L A Y\n");
					printf("   \n");
					printf("   Choosing any of the options to play chess you will soon find a chess-board \n");
					printf("   on the left side of the screen.\n");
					printf("   \n");
					printf("   If any of the players participating is human, this player may move his \n");
					printf("   pieces in the following way:\n");
					printf("   \n");
					printf("   By placing the cursor > _ < over the piece that he would like to move. This \n");
					printf("   is done using the cursor-keys or the numeric keys (as described in 3). Then \n");
					printf("   confirm with [5] or [return] or [enter].\n");
					printf("   \n");
					printf("   To inform that a piece has been \"picked up\" Monarch shows a green \"I\" above \n");
					printf("   the cursor.\n");
					
					espere_tecla();
					titulo();
					aj();
						
					printf("   Now move the cursor to the field where you would like to put the piece and \n");
					printf("   confirm again.\n");
					printf("   \n");
					printf("   Beware: You may not take back moves, so do not confirm the second time if \n");
					printf("   you are not sure of what you are doing.\n");
					printf("   \n");
					printf("   If you wish to drop a piece again, which you chose by mistake, simply stay \n");
					printf("   on the field of origin and confirm. Monarch will return an error and you \n");
					printf("   may pick up another piece.\n");
					printf("   \n");
					printf("   This is, by the way, also true if you picked up a piece of the opponent, \n");
					printf("   solicitated an illegal move or tried to \"move\" an empty field. Monarch will \n");
					printf("   report these errors and let you choose another.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
				
					printf("   After a successful move Monarch marks the upper left corner of the field \n");
					printf("   with a blue \"o\". This is especially handy when you want to know what the \n");
					printf("   last move of the computer was.\n");
					printf("   \n");
					printf("   On the right side of the board you may find an options-menu which you can \n");
					printf("   access by moving the cursor over the right edge of the board:\n");
					
					menu_ajuda(2);

					printf("   Using this menu you can:\n");
					printf("   \n");
					printf("   6. 1.  L o a d   P o s i t i o n\n");
					printf("   \n");
					printf("   Choosing this option and naming a valid archive you can load a position.\n");
					printf("   \n");
					printf("   6. 2.  S a v e   P o s i t i o n\n");
					printf("   \n");
					printf("   The current position on the board can be saved just giving the archive a \n");
					printf("   name.\n");
					printf("   \n");
					
					espere_tecla();
					titulo();
					aj();
	
					printf("   6. 3.  Q u i t   G a m e \n");
					printf("   \n");
					printf("   Bored or it is just hopeless\? Then use this option to leave the current \n");
					printf("   game. After your confirmation you will come back to the main menu.\n");
					printf("   \n");
					printf("   6. 4.  B A C K   T O   C H E S S - B O A R D\n");
					printf("   \n");
					printf("   If you got to the right side of the board by mistake you may return to it \n");
					printf("   with this option.					\n");
					printf("   \n");
					printf("   7.  C O N F I G U R A T I O N S - M E N U\n");
					printf("   \n");
					printf("   This is the configurations-menu:\n");

					menu_ajuda(3);

					printf("   Here you may choose to modify the language of operation if you got it wrong \n");
					printf("   at the start or if you just want to see how the program looks in another \n");
					printf("   language. The menu that is being accessed by this first option is the same \n");
					printf("   as after loading the program (see 4).\n");
					printf("   \n");
					printf("   You may also choose the algorithm of the program, i.e., the way that it \n");
					printf("   plays. Choosing the second option you will come to:\n");

					menu_ajuda(4);

					printf("   Here you may pick up one of the two standard-modes, in which the computer \n");
					printf("   will do its best to not lose using all of its routines, or one of the \n");
					printf("   simulated players that use to commit \"human errors\"\n");
					printf("   \n");
					printf("   With the last option you can get back to the main menu.\n");
					espere_tecla();
					break;
	}
}

void console::init_frases(void)
{
	// titulo
	frase.strg[PORTUGUES][1]="sistema de xadrez versao 1.0";
	frase.strg[PORTUGUES][2]=" PROJETO FINAL DO CURSO DE BACHARELADO EM INFORMATICA, UNICENP, CURITIBA\n";
	frase.strg[PORTUGUES][3]=" Realmente sair do programa\?\n";
	frase.strg[PORTUGUES][4]=" Tchau! (Programa terminado com sucesso.)\n";
	frase.strg[PORTUGUES][5]=" MENU DESENVOLVIMENTO   ";
	frase.strg[PORTUGUES][6]=" Ambiente de Teste      ";
	frase.strg[PORTUGUES][7]=" Configuracao Algoritmo ";
	frase.strg[PORTUGUES][8]=" ----> MONARCH          ";
	frase.strg[PORTUGUES][9]=NULL;

	// 1o. menu
	frase.strg[PORTUGUES][10]=" MENU PRINCIPAL           ";
	frase.strg[PORTUGUES][11]=" Sobre o Sistema          ";
	frase.strg[PORTUGUES][12]=" Jogar: Jogador x Jogador ";
	frase.strg[PORTUGUES][13]=" Jogar: Jogador x MONARCH ";
	frase.strg[PORTUGUES][14]=" Jogar: MONARCH x Jogador ";
	frase.strg[PORTUGUES][15]=" Jogar: MONARCH x MONARCH ";
	frase.strg[PORTUGUES][16]=" Configuracoes            ";
	frase.strg[PORTUGUES][17]=" Tutorial                 ";
	frase.strg[PORTUGUES][18]=" Ajuda                    ";
	frase.strg[PORTUGUES][19]=" SAIR DO PROGRAMA         ";
	frase.strg[PORTUGUES][20]=NULL;

	// 2nd menu
	frase.strg[PORTUGUES][21]=" LINGUA    / SPRACHE       / LANGUAGE   ";
	frase.strg[PORTUGUES][22]=" Portugues / Portugiesisch / Portuguese ";
	frase.strg[PORTUGUES][23]=" Alemao    / Deutsch       / German     ";
	frase.strg[PORTUGUES][24]=" Ingles    / Englisch      / English    ";
	frase.strg[PORTUGUES][25]=NULL;

	frase.strg[PORTUGUES][26]=" ATENCAO ";
	frase.strg[PORTUGUES][27]="- Desistir com [q]";

	frase.strg[PORTUGUES][28]="> TEM CERTEZA\? (S/N) ";

	frase.strg[PORTUGUES][29]=" [q] para sair ";

	// 3rd menu
	frase.strg[PORTUGUES][30]=" C O N F I G U R A C O E S     ";
	frase.strg[PORTUGUES][31]=" Configurar Lingua de Operacao ";
	frase.strg[PORTUGUES][32]=" Configurar Algoritmo          ";
	frase.strg[PORTUGUES][33]=" SAIR PARA MENU PRINICIPAL     ";
	frase.strg[PORTUGUES][34]=NULL;

	frase.strg[PORTUGUES][35]="Nome do Arquivo:";
	frase.strg[PORTUGUES][36]="Nao e possivel abrir o arquivo.";
	frase.strg[PORTUGUES][37]="Nao e possivel escrever os dados.";
	frase.strg[PORTUGUES][38]="Nao e possivel ler os dados.";

	frase.strg[PORTUGUES][39]=" Peca foi escolhida ";

	// 4th menu
	frase.strg[PORTUGUES][40]=" C O N F I G U R A C A O   A L G O R I T M O                 ";
	frase.strg[PORTUGUES][41]=" Modo padrao: Nivel 1                                        ";
	frase.strg[PORTUGUES][42]=" Modo padrao: Nivel 2                                        ";
	frase.strg[PORTUGUES][43]=" Simulacao:   Jose Maria da Silva,  48, Sao Jose dos Pinhais ";
	frase.strg[PORTUGUES][44]=" Simulacao:   Henrique da Cruz,     30, Rio de Janeiro       ";
	frase.strg[PORTUGUES][45]=" Simulacao:   Clemirson Almeida,    25, Belem                ";
	frase.strg[PORTUGUES][46]=" Simulacao:   Vanio Costa,          59, Curitiba             ";
	frase.strg[PORTUGUES][47]=" Simulacao:   Isabel de Souza,      43, Sao Paulo            ";
	frase.strg[PORTUGUES][48]=" Simulacao:   Adel Hassan,          19, Recife               ";
	frase.strg[PORTUGUES][49]=" Simulacao:   Wilson Ferreira,      32, Florianopolis        ";
	frase.strg[PORTUGUES][50]=" Simulacao:   Alberto Alfredo Neto, 6,  Belo Horizonte       ";
	frase.strg[PORTUGUES][51]=NULL;

	// 5th menu
	frase.strg[PORTUGUES][52]="OPERACOES DISCO    ";
	frase.strg[PORTUGUES][53]="Ler Posicao        ";
	frase.strg[PORTUGUES][54]="Salvar Posicao     ";
	frase.strg[PORTUGUES][55]="VOLTAR PARA O JOGO ";
	frase.strg[PORTUGUES][56]=NULL;

	// tabuleiro
	frase.strg[PORTUGUES][57]="Na Vez: ";
	frase.strg[PORTUGUES][58]="COMPUTADOR";
	frase.strg[PORTUGUES][59]="JOGADOR";
	frase.strg[PORTUGUES][60]="Pensando.....";
	frase.strg[PORTUGUES][61]="Cor: ";
	frase.strg[PORTUGUES][62]="BRANCO";
	frase.strg[PORTUGUES][63]="PRETO";

	frase.strg[PORTUGUES][64]=" O P C O E S             ";
	frase.strg[PORTUGUES][65]=" Ler Posicao             ";
	frase.strg[PORTUGUES][66]=" Salvar Posicao          ";
	frase.strg[PORTUGUES][67]=" Desistir da Partida     ";
	frase.strg[PORTUGUES][68]=" VOLTAR PARA O TABULEIRO ";
	frase.strg[PORTUGUES][69]=NULL;

	frase.strg[PORTUGUES][70]="  ERRO  ";
	
	frase.strg[PORTUGUES][71]=" Peca do adversario! ";
	frase.strg[PORTUGUES][72]=" Sem peca disponivel! ";
	frase.strg[PORTUGUES][73]=" Movimento invalido! ";

	frase.strg[PORTUGUES][75]="TROCAR POR QUAL PECA\? ";
	frase.strg[PORTUGUES][76]="Rainha                ";
	frase.strg[PORTUGUES][77]="Torre                 ";
	frase.strg[PORTUGUES][78]="Cavalo                ";
	frase.strg[PORTUGUES][79]="Bispo                 ";
	frase.strg[PORTUGUES][80]=NULL;

	frase.strg[PORTUGUES][81]="       X E Q U E        ";
	frase.strg[PORTUGUES][82]="  X E Q U E - M A T E   ";
	frase.strg[PORTUGUES][83]="      E M P A T E       ";

	frase.strg[PORTUGUES][84]="   JOGADOR DESISTIU     ";
	
	frase.strg[PORTUGUES][85]="Favor pressionar qualquer tecla para continuar.";

	// AMBIENTE DE TESTE
	frase.strg[PORTUGUES][86]=" AMBIENTE DE TESTE           "; // menu do ambiente de teste
	frase.strg[PORTUGUES][87]=" Posicao inicial             ";
	frase.strg[PORTUGUES][88]=" Tabuleiro zerado            ";
	frase.strg[PORTUGUES][89]=" Colocar Peca                ";
	frase.strg[PORTUGUES][90]=" Deletar Peca                ";
	frase.strg[PORTUGUES][91]=" Finalizar! (Executar Teste) ";
	frase.strg[PORTUGUES][92]=" SAIR /P MENU PRINCIPAL      ";
	frase.strg[PORTUGUES][93]=NULL;

	frase.strg[PORTUGUES][94]=" QUAL O TIPO DA PECA\? "; // menu do ambiente de teste
	frase.strg[PORTUGUES][95]=" Rei                  ";
	frase.strg[PORTUGUES][96]=" Rainha               ";
	frase.strg[PORTUGUES][97]=" Torre                ";
	frase.strg[PORTUGUES][98]=" Cavalo               ";
	frase.strg[PORTUGUES][99]=" Bispo                ";
	frase.strg[PORTUGUES][100]=" Peao                 ";
	frase.strg[PORTUGUES][101]=NULL;

	frase.strg[PORTUGUES][102]="QUAL A COR DA PECA\? ";
	frase.strg[PORTUGUES][103]="Branco              ";
	frase.strg[PORTUGUES][104]="Preto               ";
	frase.strg[PORTUGUES][105]=NULL;

	frase.strg[PORTUGUES][106]=" QUEM ESTA NA VEZ\? ";
	frase.strg[PORTUGUES][107]=" Branco            ";
	frase.strg[PORTUGUES][108]=" Preto             ";
	frase.strg[PORTUGUES][109]=NULL;		

	frase.strg[PORTUGUES][110]="MODIFICACOES      ";
	frase.strg[PORTUGUES][111]="Todos ligados     ";
	frase.strg[PORTUGUES][112]="Todos desligados  ";
	frase.strg[PORTUGUES][113]="Mudar um elemento ";
	frase.strg[PORTUGUES][114]="SAIR              ";
	frase.strg[PORTUGUES][115]=NULL;

	frase.strg[PORTUGUES][116]="?  ";
	frase.strg[PORTUGUES][117]="1. ";
	frase.strg[PORTUGUES][118]="2. ";
	frase.strg[PORTUGUES][119]="3. ";
	frase.strg[PORTUGUES][120]="4. ";
	frase.strg[PORTUGUES][121]="5. ";
	frase.strg[PORTUGUES][122]="6. ";
	frase.strg[PORTUGUES][123]="7. ";
	frase.strg[PORTUGUES][124]="8. ";
	frase.strg[PORTUGUES][125]="9. ";
	frase.strg[PORTUGUES][126]="10.";
	frase.strg[PORTUGUES][127]="11.";
	frase.strg[PORTUGUES][128]="12.";
	frase.strg[PORTUGUES][129]="13.";
	frase.strg[PORTUGUES][130]="14.";
	frase.strg[PORTUGUES][131]="15.";
	frase.strg[PORTUGUES][132]="16.";
	frase.strg[PORTUGUES][133]="17.";
	frase.strg[PORTUGUES][134]="18.";
	frase.strg[PORTUGUES][135]=NULL;

	// Titel
	frase.strg[ALEMAO][1]=   "ein schachsystem version 1.0";
	frase.strg[ALEMAO][2]=   " DIPLOMPROJEKT INFORMATIK, POSITIVO-UNIVERSITAET, CURITIBA, BRASILIEN\n";
	frase.strg[ALEMAO][3]=   " Programm wirklich verlassen\?\n";
	frase.strg[ALEMAO][4]=   " Tschuess! (Programm ohne Fehler beendet.)\n";

	// 1. Menue
	frase.strg[ALEMAO][10]=  " HAUPTMENUE                  ";
	frase.strg[ALEMAO][11]=  " Allgemeine Informationen    ";
	frase.strg[ALEMAO][12]=  " Spielen: Spieler x Spieler  ";
	frase.strg[ALEMAO][13]=  " Spielen: Spieler x MONARCH  ";
	frase.strg[ALEMAO][14]=  " Spielen: MONARCH x Spieler  ";
	frase.strg[ALEMAO][15]=  " Spielen: MONARCH x MONARCH  ";
	frase.strg[ALEMAO][16]=  " Einstellungen               ";
	frase.strg[ALEMAO][17]=  " Anleitung zum Schachspielen ";
	frase.strg[ALEMAO][18]=  " Hilfe                       ";
	frase.strg[ALEMAO][19]=  " PROGRAMM VERLASSEN          ";
	frase.strg[ALEMAO][20]=NULL;
	
	// 2nd menu
	frase.strg[ALEMAO][21]=  " LINGUA    / SPRACHE       / LANGUAGE   ";
	frase.strg[ALEMAO][22]=  " Portugues / Portugiesisch / Portuguese ";
	frase.strg[ALEMAO][23]=  " Alemao    / Deutsch       / German     ";
	frase.strg[ALEMAO][24]=  " Ingles    / Englisch      / English    ";
	frase.strg[ALEMAO][25]=  NULL;

	frase.strg[ALEMAO][26]=" ACHTUNG ";
	frase.strg[ALEMAO][27]="- Aufgeben mit [q]";

	frase.strg[ALEMAO][28]="> SIND SIE SICHER\? (J/N) ";

	frase.strg[ALEMAO][29]=" [q] zum abbrechen ";
	
	// 3rd menu
	frase.strg[ALEMAO][30]=" E I N S T E L L U N G E N    ";
	frase.strg[ALEMAO][31]=" Operationssprache auswaehlen ";
	frase.strg[ALEMAO][32]=" Algorithmus auswaehlen       ";
	frase.strg[ALEMAO][33]=" ZURUECK ZUM HAUPTMENU        ";
	frase.strg[ALEMAO][34]=NULL;

	frase.strg[ALEMAO][35]="Dateiname:";
	frase.strg[ALEMAO][36]="Datei kann nicht geoeffnet werden.";
	frase.strg[ALEMAO][37]="Kann nicht in Datei schreiben.";
	frase.strg[ALEMAO][38]="Kann nicht aus Datei lesen.";

	frase.strg[ALEMAO][39]=" Figur ausgewaehlt ";

	// 4th menu
	frase.strg[ALEMAO][40]=" E I N S T E L L U N G   A L G O R I T H M U S        ";
	frase.strg[ALEMAO][41]=" Standardmodus: Spielstufe 1                          ";
	frase.strg[ALEMAO][42]=" Standardmodus: Spielstufe 2                          ";
	frase.strg[ALEMAO][43]=" Simulation:    Erich Henkel,         48, Bielefeld   ";
	frase.strg[ALEMAO][44]=" Simulation:    Frank Kurzing,        30, Berlin      ";
	frase.strg[ALEMAO][45]=" Simulation:    Lars Dieter Taldorf,  25, Frankfurt   ";
	frase.strg[ALEMAO][46]=" Simulation:    Friedrich Mainfeld,   59, Bonn        ";
	frase.strg[ALEMAO][47]=" Simulation:    Markus Frisch,        43, Iserlohn    ";
	frase.strg[ALEMAO][48]=" Simulation:    Benedikt Lange,       19, Kiel        ";
	frase.strg[ALEMAO][49]=" Simulation:    Miriam Schulte,       32, Aachen      ";
	frase.strg[ALEMAO][50]=" Simulation:    Kai Ipp,              6,  Duesseldorf ";
	frase.strg[ALEMAO][51]=NULL;

	// 5th menu
	frase.strg[ALEMAO][52]="DISKOPERATIONEN      ";
	frase.strg[ALEMAO][53]="Stellung einlesen    ";
	frase.strg[ALEMAO][54]="Stellung abspeichern ";
	frase.strg[ALEMAO][55]="ZURUECK ZUM SPIEL    ";
	frase.strg[ALEMAO][56]=NULL;

	// tabuleiro
	frase.strg[ALEMAO][57]="Am Zug: ";
	frase.strg[ALEMAO][58]="COMPUTER";
	frase.strg[ALEMAO][59]="SPIELER";
	frase.strg[ALEMAO][60]="Ueberlege.....";
	frase.strg[ALEMAO][61]="Farbe: ";
	frase.strg[ALEMAO][62]="WEISS";
	frase.strg[ALEMAO][63]="SCHWARZ";

	frase.strg[ALEMAO][64]=" O P T I O N E N           ";
	frase.strg[ALEMAO][65]=" Position laden            ";
	frase.strg[ALEMAO][66]=" Position abspeichern      ";
	frase.strg[ALEMAO][67]=" Aufgeben (Partie beenden) ";
	frase.strg[ALEMAO][68]=" ZURUECK AUFS SCHACHBRETT  ";
	frase.strg[ALEMAO][69]=NULL;
	
	frase.strg[ALEMAO][70]=" FEHLER ";

	frase.strg[ALEMAO][71]=" Figur des Gegners! ";
	frase.strg[ALEMAO][72]=" Keine Figur vorhanden! ";
	frase.strg[ALEMAO][73]=" Zug ungueltig! ";

	frase.strg[ALEMAO][75]="GEGEN WELCHE FIGUR TAUSCHEN\? ";
	frase.strg[ALEMAO][76]="Dame                         ";
	frase.strg[ALEMAO][77]="Turm                         ";
	frase.strg[ALEMAO][78]="Springer                     ";
	frase.strg[ALEMAO][79]="Laeufer                      ";
	frase.strg[ALEMAO][80]=NULL;


	frase.strg[ALEMAO][81]   ="      S C H A C H       ";
	frase.strg[ALEMAO][82]   ="  S C H A C H M A T T   ";
	frase.strg[ALEMAO][83]   ="       R E M I S        ";

	frase.strg[ALEMAO][84]   ="    SPIELER GAB AUF     ";

	frase.strg[ALEMAO][85]   ="Weiter auf Tastendruck.";

	// title
	frase.strg[INGLES][1]=   " a chess-system version 1.0 ";
	frase.strg[INGLES][2]=   " GRADUATION-PROJECT COMPUTER-SCIENCE, POSITIVO-UNIVERSITY, CURITIBA, BRAZIL\n";
	frase.strg[INGLES][3]=   " Really quit\?\n";
	frase.strg[INGLES][4]=   " See ya! (Program finished without errors.)\n";

	// 1st menu
	frase.strg[INGLES][10]=  " MAIN MENU               ";
	frase.strg[INGLES][11]=  " About this program      ";
	frase.strg[INGLES][12]=  " Play: Player  x Player  ";
	frase.strg[INGLES][13]=  " Play: Player  x MONARCH ";
	frase.strg[INGLES][14]=  " Play: MONARCH x Player  ";
	frase.strg[INGLES][15]=  " Play: MONARCH x MONARCH ";
	frase.strg[INGLES][16]=  " Configuration           ";
	frase.strg[INGLES][17]=  " Tutorial                ";
	frase.strg[INGLES][18]=  " Help                    ";
	frase.strg[INGLES][19]=  " LEAVE THE PROGRAM       ";
	frase.strg[INGLES][20]=NULL;

	// 2nd menu
	frase.strg[INGLES][21]=  " LINGUA    / SPRACHE       / LANGUAGE   ";
	frase.strg[INGLES][22]=  " Portugues / Portugiesisch / Portuguese ";
	frase.strg[INGLES][23]=  " Alemao    / Deutsch       / German     ";
	frase.strg[INGLES][24]=  " Ingles    / Englisch      / English    ";
	frase.strg[INGLES][25]=  NULL;

	frase.strg[INGLES][26]=" ATTENTION ";
	frase.strg[INGLES][27]="- [q] to give up";

	frase.strg[INGLES][28]="> ARE YOU SURE\? (Y/N) ";

	frase.strg[INGLES][29]=" [q] to cancel ";
	
	// 3rd menu
	frase.strg[INGLES][30]=" C O N F I G U R A T I O N S  ";
	frase.strg[INGLES][31]=" Choose Language of Operation ";
	frase.strg[INGLES][32]=" Choose Algorithm             ";
	frase.strg[INGLES][33]=" BACK TO MAIN MENU            ";
	frase.strg[INGLES][34]=NULL;

	frase.strg[INGLES][35]="Filename:";
	frase.strg[INGLES][36]="Cannot open file.";
	frase.strg[INGLES][37]="Cannot write to file.";
	frase.strg[INGLES][38]="Cannot read data.";

	frase.strg[INGLES][39]=" Piece was chosen ";

	// 4th menu
	frase.strg[INGLES][40]=" C O N F I G U R A T I O N   A L G O R I T H M   ";
	frase.strg[INGLES][41]=" Standard mode: Level 1                          ";
	frase.strg[INGLES][42]=" Standard mode: Level 2                          ";
	frase.strg[INGLES][43]=" Simulation:    William Benson, 48, Denver       ";
	frase.strg[INGLES][44]=" Simulation:    Ed Devenport,   30, New York     ";
	frase.strg[INGLES][45]=" Simulation:    Michael Hudson, 25, Seattle      ";
	frase.strg[INGLES][46]=" Simulation:    David Watson,   59, Philadelphia ";
	frase.strg[INGLES][47]=" Simulation:    John Williams,  43, St. Louis    ";
	frase.strg[INGLES][48]=" Simulation:    Andy Ford,      19, Phoenix      ";
	frase.strg[INGLES][49]=" Simulation:    Lucy Street,    32, Los Angeles  ";
	frase.strg[INGLES][50]=" Simulation:    Harry McCord,   6,  San Antonio  ";
	frase.strg[INGLES][51]=NULL;

	// 5th menu
	frase.strg[INGLES][52]="DISC OPERATIONS ";
	frase.strg[INGLES][53]="Load Position   ";
	frase.strg[INGLES][54]="Save Position   ";
	frase.strg[INGLES][55]="BACK TO GAME    ";
	frase.strg[INGLES][56]=NULL;

	// tabuleiro
	frase.strg[INGLES][57]="Turn: ";
	frase.strg[INGLES][58]="COMPUTER";
	frase.strg[INGLES][59]="PLAYER";
	frase.strg[INGLES][60]="Thinking....";
	frase.strg[INGLES][61]="Color: ";
	frase.strg[INGLES][62]="WHITE";
	frase.strg[INGLES][63]="BLACK";
	
	frase.strg[INGLES][64]=" O P T I O N S       ";
	frase.strg[INGLES][65]=" Load Position       ";
	frase.strg[INGLES][66]=" Save Position       ";
	frase.strg[INGLES][67]=" Quit Game           ";
	frase.strg[INGLES][68]=" BACK TO CHESS-BOARD ";
	frase.strg[INGLES][69]=NULL;

	frase.strg[INGLES][70]=" ERROR ";
	
	frase.strg[INGLES][71]=" Piece belongs to other player! ";
	frase.strg[INGLES][72]=" No piece available! ";
	frase.strg[INGLES][73]=" Movement void! ";

	frase.strg[INGLES][75]="CHANGE TO WHICH PIECE\? ";
	frase.strg[INGLES][76]="Queen                  ";
	frase.strg[INGLES][77]="Rook                   ";
	frase.strg[INGLES][78]="Knight                 ";
	frase.strg[INGLES][79]="Bishop                 ";
	frase.strg[INGLES][80]=NULL;

	frase.strg[INGLES][81]   ="       C H E C K        ";
	frase.strg[INGLES][82]   ="   C H E C K M A T E    ";
	frase.strg[INGLES][83]   ="   S T A L E M A T E    ";

	frase.strg[INGLES][84]   ="    PLAYER HAS QUIT     ";

	frase.strg[INGLES][85]   ="Please press any key to continue.";

}

void console::show_peca(int x_in, int y_in, int cor, PECAS p)       // mostra uma peca
{                                                                                                                                       // especifica em ascii
	int j;
	for(j=0;j<32;j++)
	{
		if(p.p[j].coordenadas(x_in,y_in)&&p.p[j].devolve_tipo()!=INATIVO)
		{
			p.p[j].mpa(cor);
			return;
		}
	}
	if (cor) setcolor( FOREGROUND_WHITE | BACKGROUND_DARKGRAY ); else
		setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
	
	printf("   ");

	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
	return;
}

void console::flush_ascii(PECAS p)   // mostra o tabuleiro inteiro em ascii
{
	// ATENCAO - tudo feito com gotoxy para evitar bagunca eventual na tela (por causo do \n)

	int i, j, cor_do_campo;
	//console io;
	// console io;
	gotoxy(0,2);
	printf("       A   B   C   D   E   F   G   H");
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
	gotoxy(5,3);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			cds1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, ces1);
	for (i=7;i>-1;i--)
	{
		if(i<7)
		{
			setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
			gotoxy(5,(7-i)*2+3);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
				vhd1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, vhe1);
		}
		if (i % 2==0)
			cor_do_campo=0; else
			cor_do_campo=1;
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
		gotoxy(3,(7-i)*2+4);
		printf("%i ",i+1);
		for (j=0;j<8;j++)
		{
			setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
			printf("%c",ve1);
			show_peca(j,i,cor_do_campo,p);
			if (cor_do_campo==0) cor_do_campo=1; else
				cor_do_campo=0;
		}
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
		printf("%c",ve1);
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
		printf(" %i",i+1);
	}
	gotoxy(5,19);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			cdi1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, cei1);
	gotoxy(0,20);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
	printf("       A   B   C   D   E   F   G   H");
	setcolor(FOREGROUND_YELLOW | BACKGROUND_BLUE);

	if(p.ult.x1!=INVALIDO)
	{
		//setcolor( FOREGROUND_LIGHTRED | BACKGROUND_BLACK );
		//gotoxy(p.ult.x1*4+5,(7-p.ult.y1)*2+3);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+5,(7-p.ult.y1)*2+5);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+9,(7-p.ult.y1)*2+3);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+9,(7-p.ult.y1)*2+5);
		//printf("%c",cr1);

		setcolor( FOREGROUND_LIGHTBLUE | BACKGROUND_BLACK );
		gotoxy(p.ult.x2*4+5,(7-p.ult.y2)*2+3);
		printf("o");
	//	gotoxy(p.ult.x2*4+5,(7-p.ult.y2)*2+5);
	//	printf("%c",cr1);
	//	gotoxy(p.ult.x2*4+9,(7-p.ult.y2)*2+3);
	//	printf("%c",cr1);
	//	gotoxy(p.ult.x2*4+9,(7-p.ult.y2)*2+5);
	//	printf("%c",cr1);
	}

	setcolor( FOREGROUND_WHITE | BACKGROUND_CYAN );
	gotoxy(49,3);
	printf("%c",cds1);
	for(i=0;i<21;i++) printf("%c",ho1);
	printf("%c",ces1);
	gotoxy(49,4);
	printf("%c M  O  N  A  R  C  H %c",ve1,ve1);
	gotoxy(49,5);
	printf("%c    - Ver. 1.0 -     %c",ve1,ve1);
	gotoxy(49,6);
	printf("%c",cdi1);
	for(i=0;i<21;i++) printf("%c",ho1);
	printf("%c",cei1);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
}


void console::in_frame(int x, int y, char* dialogo)
{
	int length,i;
	
	setcolor( FOREGROUND_WHITE | BACKGROUND_GREEN );

	length=strlen(dialogo);

	if(x==INVALIDO) x=(80-length-2)/2;

	gotoxy(x,y);

	printf("%c",cds1);
	
	for(i=0;i<length;i++) printf("%c",ho1);
	
	printf("%c",ces1);
	
	gotoxy(x,y+1);
	
	printf("%c",ve1);
	setcolor( FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE );
	printf("%s",dialogo);
	setcolor( FOREGROUND_WHITE | BACKGROUND_GREEN );
	printf("%c",ve1);
	
	gotoxy(x,y+2);
	
	printf("%c",cdi1);
	for(i=0;i<length;i++) printf("%c",ho1);
	printf("%c",cei1);
	
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );

	gotoxy(x+1,y+1);

}



BOOL console::tem_certeza(void)
{
	char ch;
	
	in_frame(52,22,frase.strg[lingua][28]);
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
	
	while(kbhit()) getch();
	ch=' ';
	while(ch!='N' && ch!='S' && ch!='J' && ch!='Y')
	{
		ch=getch();
		ch=toupper(ch);
	}

	if(ch=='N') return FALSE;

	return TRUE;
}

void console::escreve_menu_palido(int start_x, int start_y, int nro_menu)
{

	int limite, i, length;

	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );

	gotoxy(start_x-1,start_y-1);

	length=strlen(frase.strg[lingua][nro_menu]);

	printf("%c",cds1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",ces1);

	gotoxy(start_x-1,start_y);

	printf("%c",ve1);

	printf("  %s",frase.strg[lingua][nro_menu]);

	printf("%c",ve1);

	gotoxy(start_x-1,start_y+1);

	printf("%c",vhd1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",vhe1);

	

	limite=nro_menu;
	while(frase.strg[lingua][limite]!=NULL)
		limite++;


	gotoxy(start_x-1,start_y+limite-nro_menu+1);

	printf("%c",cdi1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",cei1);

	for(i=1;i<limite-nro_menu;i++)
	{
		gotoxy(start_x-1,start_y+i+1);
		if(i==1)
			printf("%c>",ve1); else
			printf("%c.",ve1);
		printf(" %s",frase.strg[lingua][nro_menu+i]);
		printf("%c",ve1);
	}

	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
}


int console::menu_vertical(int start_x, int start_y, int nro_menu)
{
	char direcao;
	int opcao, limite, i, length;
	opcao=1;

	setcolor(FOREGROUND_WHITE | BACKGROUND_GREEN);

	gotoxy(start_x-1,start_y-1);

	length=strlen(frase.strg[lingua][nro_menu]);

	printf("%c",cds1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",ces1);

	gotoxy(start_x-1,start_y);

	printf("%c",ve1);

	setcolor(FOREGROUND_YELLOW | BACKGROUND_GREEN);

	printf("  %s",frase.strg[lingua][nro_menu]);

	setcolor(FOREGROUND_WHITE | BACKGROUND_GREEN);

	printf("%c",ve1);

	gotoxy(start_x-1,start_y+1);

	printf("%c",vhd1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",vhe1);

	

	limite=nro_menu;
	while(frase.strg[lingua][limite]!=NULL)
		limite++;


	gotoxy(start_x-1,start_y+limite-nro_menu+1);

	printf("%c",cdi1);

	for(i=0;i<length+2;i++) printf("%c",ho1);

	printf("%c",cei1);


	do{

		for(i=1;i<limite-nro_menu;i++)
		{
			gotoxy(start_x-1,start_y+i+1);
			setcolor(FOREGROUND_WHITE | BACKGROUND_GREEN);
			printf("%c.",ve1);
			printf(" %s",frase.strg[lingua][nro_menu+i]);
			printf("%c",ve1);
		}

		switch(direcao)
		{
			case '8' : if(opcao>1) opcao--; break;
			case '2' : if(opcao<limite-nro_menu-1) opcao++; break;
			case -32 : direcao=getch(); // teclas do cursor!!
					   switch (direcao)
					   {
					   case 72 : if(opcao>1) opcao--; break; // para cima cursor
					   case 80 : if(opcao<limite-nro_menu-1) opcao++; break; // para baixo cursor
					   }
		}

		gotoxy(start_x,start_y+opcao+1);
		setcolor(FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE);
		printf(">");
		printf(" %s",frase.strg[lingua][nro_menu+opcao]);
		setcolor(FOREGROUND_WHITE | BACKGROUND_GREEN);
		gotoxy(start_x,start_y+opcao+1);

		direcao=getch();

	}while(direcao!='5' && direcao!=char(13));

	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);   // default
	return opcao-1;
}

void console::caixa_atencao(int x, int y, char* dialogo)
{
	int length,i;

	setcolor( FOREGROUND_WHITE | BACKGROUND_RED );

	length=strlen(dialogo);
	if(length<15) length=15;
	gotoxy(x,y);
	printf("%c",cds1);
	for(i=0;i<length;i++) printf("%c",ho1);
	printf("%c",ces1);
	gotoxy(x,y+1);
	printf("%c",ve1);
	printf("%s",dialogo);
	printf("%c",ve1);
	gotoxy(x,y+2);
	printf("%c",cdi1);
	for(i=0;i<length;i++) printf("%c",ho1);
	printf("%c",cei1);
	x=x+(length+2-11)/2;
	setcolor( FOREGROUND_YELLOW | BACKGROUND_RED );
	gotoxy(x,y);
	printf(frase.strg[lingua][26]);
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
}

void console::caixa_erro(int nro)
{
	int length,i,x,y;

	setcolor( FOREGROUND_WHITE | BACKGROUND_RED );

	length=strlen(frase.strg[lingua][nro]);
	
	x=(80-length-2)/2;
	y=21;
	gotoxy(x,y);
	printf("%c",cds1);
	for(i=0;i<length;i++) printf("%c",ho1);
	printf("%c",ces1);
	gotoxy(x,y+1);
	printf("%c",ve1);
	printf("%s",frase.strg[lingua][nro]);
	printf("%c",ve1);
	gotoxy(x,y+2);
	printf("%c",cdi1);
	for(i=0;i<length;i++) printf("%c",ho1);
	printf("%c",cei1);
	x=x+(length+2-8)/2;
	setcolor( FOREGROUND_YELLOW | BACKGROUND_RED );
	gotoxy(x,y);
	printf(frase.strg[lingua][70]);
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
}


void console::acusa_xeque()
{
	caixa_atencao(25,21,frase.strg[lingua][81]);
}

void console::acusa_mate()
{
	caixa_atencao(25,12,frase.strg[lingua][82]);
	espere_tecla();
}

void console::acusa_empate()
{
	caixa_atencao(25,12,frase.strg[lingua][83]);
	espere_tecla();
}

void console::acusa_desistencia()
{
	caixa_atencao(25,12,frase.strg[lingua][84]);
	espere_tecla();
}

int console::convert(char in_ch)
{
	switch(in_ch)
	{
		case '0' : return 0;
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
	}
	return INATIVO;
}

PECAS console::leitura(PECAS pc)
{

	char filename[31];

	char filerecord[127];

	int i, x, y, tp, cor;

	FILE *pcf;

	limpa_fundo();

	gotoxy(1,21);

	printf(frase.strg[lingua][35]);

	scanf("%s",&filename);

	limpa_fundo();

	if((pcf=fopen(filename,"r"))==NULL) {
		caixa_erro(36);
		return pc;
	}

	if(fgets(filerecord,129,pcf)!=NULL)
	{

		for(i=0;i<32;i++)
		{
			x=convert(filerecord[i*4]);
			y=convert(filerecord[i*4+1]);
			cor=convert(filerecord[i*4+2]);
			tp=convert(filerecord[i*4+3]);

			pc.p[i].init(x,y,tp,cor,' ');

		}

		pc.roque_possivel_direito[BRANCO]=TRUE;		// inicializar os dados restantes
		pc.roque_possivel_esquerdo[BRANCO]=TRUE;
		pc.roque_possivel_direito[PRETO]=TRUE;
		pc.roque_possivel_esquerdo[BRANCO]=TRUE;
		pc.peao_duas_casas_para_a_frente=INVALIDO;
		pc.ult.x1=INVALIDO;
		pc.ult.x2=INVALIDO;
		pc.ult.y1=INVALIDO;
		pc.ult.y2=INVALIDO;
		pc.ataque=FALSE;

	} else
	{
		caixa_erro(38);
	}

	fclose(pcf);
	return pc;
}

void console::gravacao(PECAS pc)
{
	
	char filename[31];

	char filerecord[127];

	char trans[1];

	int i, x, y, tp, cor;

	FILE *pcf;

	limpa_fundo();

	gotoxy(1,21);

	printf(frase.strg[lingua][35]);	// nome do arquivo

	scanf("%s",&filename);

	limpa_fundo();

	if((pcf=fopen(filename,"w+"))==NULL) {
		caixa_erro(36);
		return;
	}

	for(i=0;i<32;i++)
	{
		x=pc.p[i].devolve_x();
		y=pc.p[i].devolve_y();
		cor=pc.p[i].devolve_cor();
		tp=pc.p[i].devolve_tipo();

		if(x==INATIVO) x=9;
		if(y==INATIVO) y=9;
		if(cor==INATIVO) cor=9;
		if(tp==INATIVO) tp=9;

		_itoa(x,trans,10);
		filerecord[i*4]=trans[0];
		_itoa(y,trans,10);
		filerecord[i*4+1]=trans[0];
		_itoa(cor,trans,10);
		filerecord[i*4+2]=trans[0];
		_itoa(tp,trans,10);
		filerecord[i*4+3]=trans[0];
	}

	if(fprintf(pcf,"%s\n",filerecord)==NULL)
	{
		caixa_erro(37);
	}

	fclose(pcf);

	return;
}

void console::limpa_direita_tabuleiro()
{
	int i;

	for(i=8;i<23;i++)
	{
		gotoxy(45,i);
		printf("                                   ");
	}
}

COORD1 console::menu_tabuleiro(int na_vez, PECAS *pc, int x_in, int y_in)
{
	int escolha;
	char opcao;
	COORD1 flag, board;

	opcao='0';

	if(x_in==INATIVO)
	{
		flag.x=4;
		if(na_vez==BRANCO) flag.y=0; else flag.y=7;
	}else
	{
		flag.x=x_in;
		flag.y=y_in;
	}

	gotoxy(50,8);

	if(na_vez!=INATIVO)
	{
		printf("%s%s    ",frase.strg[lingua][57],frase.strg[lingua][59]);
		gotoxy(50,10);
			printf("%s",frase.strg[lingua][61]);
		if(na_vez==BRANCO)
		{
			setcolor(FOREGROUND_YELLOW | BACKGROUND_BLUE);
			printf(" %s   ",frase.strg[lingua][62]);
		}else
		{
			setcolor(FOREGROUND_LIGHTPURPLE | BACKGROUND_BLUE);
			printf(" %s   ",frase.strg[lingua][63]);
		}
		} else
			printf("AMBIENTE TESTE");

		if(x_in==INATIVO || na_vez==INATIVO)
			escreve_menu_palido(47,14,64); else
		{
			limpa_fundo();
			caixa_atencao(50,14,frase.strg[lingua][39]);
		}

	while(opcao!='5' && opcao!=char(13) && opcao!='Q' && opcao!=' ')
	{
	
		board.x=flag.x;         // no tabuleiro branco joga de baixo!!
		board.y=7-flag.y;
		
		setcolor( FOREGROUND_WHITE | BACKGROUND_LIGHTBLUE );

		gotoxy(board.x*4+5,board.y*2+4);
		printf(">");
		gotoxy(board.x*4+9,board.y*2+4);
		printf("<");

		if(x_in!=INATIVO)
		{
			gotoxy(board.x*4+7,board.y*2+3);
			setcolor( FOREGROUND_LIGHTGREEN | BACKGROUND_BLACK );
			printf("I");
		}

		gotoxy(board.x*4+7,board.y*2+4);
		
		opcao=getch();
		opcao=toupper(opcao);

		gotoxy(board.x*4+7,board.y*2+3);
		setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
		printf("%c",ho1);

		setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );

		gotoxy(board.x*4+5,board.y*2+4);
		printf("%c",ve1);
		gotoxy(board.x*4+9,board.y*2+4);
		printf("%c",ve1);
		gotoxy(board.x*4+7,board.y*2+4);

		setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );

		switch(opcao)
		{
			case 'Q' : opcao='X'; break;
			case '2' : if(flag.y>0) flag.y--;
						break;
			case '4' : if(flag.x>0) flag.x--;
						break;
			case '6' : if(flag.x<7) flag.x++; else 
					   {
						   if(na_vez==INATIVO || x_in==INATIVO)
							{
						   		escolha=menu_vertical(47,14,64);
								switch(escolha)
								{
									case 0: *pc=leitura(*pc); 
											flush_ascii(*pc);
											break;
									case 1: if(na_vez==INATIVO || x_in==INATIVO)
											gravacao(*pc);
											break;
									case 2: if(tem_certeza()) opcao='Q'; 
											break;
								}
								escreve_menu_palido(47,14,64);
						   }

					   }
						break;
			case '8' : if(flag.y<7) flag.y++;
						break;
			case -32 : opcao=getch(); // teclas cursor!!
					   switch(opcao)
					   {
					   case 72 : if(flag.y<7) flag.y++; // para cima
						break;
					   case 80 : if(flag.y>0) flag.y--; // para baixo
						break;
					   case 77 : if(flag.x<7) flag.x++; else
									 {
										if(na_vez==INATIVO || x_in==INATIVO)
										{
									   		escolha=menu_vertical(47,14,64);
										
											switch(escolha)
											{
												case 0: *pc=leitura(*pc);
														flush_ascii(*pc);
														break;
												case 1: if(na_vez==INATIVO || x_in==INATIVO)
														gravacao(*pc);
														break;
												case 2: if(tem_certeza()) opcao='Q';
														break;
											}
											escreve_menu_palido(47,14,64);
										}
								   }
						break;
					   case 75 : if(flag.x>0) flag.x--; 
						break;
					   }
					   
					   break;

		}

		board.x=flag.x;         // no tabuleiro branco joga de baixo!!
		board.y=7-flag.y;

		gotoxy(board.x*4+7,board.y*2+5);

	}

	if(opcao=='Q')    // isto significa cancelar o jogo
	{
		flag.x=-1;
		flag.y=-1;
	}

	limpa_direita_tabuleiro();

	return flag;
}

///////////////////////////////////////////////////////
// Classe: TABULEIRO - Definicao                     //
///////////////////////////////////////////////////////

class tabuleiro {       // classe do tabuleiro virtual
public:
	PECAS init(void);       // inicializa as pecas do tabuleiro
	void mostre_pontos(EPONTOS);    // mostra movimentos e pontos
	void mostre_peca(int,int,int,PECAS);    // mostra uma peca especifica
	void mostre_ascii(PECAS);       // mostra o tabuleiro inteiro em ascii
	int coluna_em_num(char);        // converte o formato normal da coluna para o formato interno
	int qualpeca(int,int,PECAS);    // qualpeca esta no lugar x,y?
	int qual_numero_em_lista(int,int,PECAS);        // qual numero tem a peca x,y na lista de pecas?
	int qual_numero_em_lista_pontos(int,int,int,int,EPONTOS); // qual numero tem a peca na lista de movimentos?
	int qualcor(int,int,PECAS); // qual cor tem a peca x,y ?
	void peca_out(int,PECAS); // mostra os valores da peca x
	char num_to_ascii(int); // converte o formato interno da coluna para o formato normal
	PECAS execute_movimento(int,int,int,int,PECAS,int); // executar um movimento no tabuleiro
	PECAS trata_roque(PECAS);       // anula as possibilidades de roque se for aplicavel
	void init_mais(void);   // inicializa as direcoes
};

// TABULEIRO - Metodos

void tabuleiro::init_mais(void)
{
	mais[0].x=0;    // vertical para cima
	mais[0].y=-1;

	mais[1].x=0;    // vertical para baixo
	mais[1].y=1;

	mais[2].x=1;    // vertical para a direita
	mais[2].y=0;

	mais[3].x=-1;   // vertical para a esquerda
	mais[3].y=0;

	mais[4].x=-1;   // canto esquerdo superior
	mais[4].y=-1;

	mais[5].x=1;    // canto direito superior
	mais[5].y=-1;

	mais[6].x=1;    // canto direito inferior
	mais[6].y=1;

	mais[7].x=-1;   // canto esquerdo inferior
	mais[7].y=1;

	cmais[0].x=-1;
	cmais[0].y=-2;

	cmais[1].x=1;
	cmais[1].y=-2;

	cmais[2].x=2;
	cmais[2].y=-1;

	cmais[3].x=2;
	cmais[3].y=1;

	cmais[4].x=1;
	cmais[4].y=2;

	cmais[5].x=-1;
	cmais[5].y=2;

	cmais[6].x=-2;
	cmais[6].y=1;

	cmais[7].x=-2;
	cmais[7].y=-1;
}

void tabuleiro::peca_out(int nro_peca, PECAS p) // informa os valores da peca
{
	p.p[nro_peca].informe_valores();
}

PECAS tabuleiro::init() // inicializa o tabuleiro da forma padrao
{
	PECAS p;
	int i;

	p.p[0].init(0,0,TORRE,BRANCO,' ');
	p.p[1].init(7,0,TORRE,BRANCO,' ');
	p.p[2].init(1,0,CAVALO,BRANCO,' ');
	p.p[3].init(6,0,CAVALO,BRANCO,' ');
	p.p[4].init(2,0,BISPO,BRANCO,' ');
	p.p[5].init(5,0,BISPO,BRANCO,' ');
	p.p[6].init(3,0,RAINHA,BRANCO,' ');
	p.p[7].init(4,0,REI,BRANCO,' ');
	
	p.p[8].init(0,7,TORRE,PRETO,' ');
	p.p[9].init(7,7,TORRE,PRETO,' ');
	p.p[10].init(1,7,CAVALO,PRETO,' ');
	p.p[11].init(6,7,CAVALO,PRETO,' ');
	p.p[12].init(2,7,BISPO,PRETO,' ');
	p.p[13].init(5,7,BISPO,PRETO,' ');
	p.p[14].init(3,7,RAINHA,PRETO,' ');
	p.p[15].init(4,7,REI,PRETO,' ');

	for (i=0;i<8;i++)       // peoes
	{
		p.p[16+i].init(0+i,1,PEAO,BRANCO,' ');
		p.p[24+i].init(0+i,6,PEAO,PRETO,' ');
	}

	p.peao_duas_casas_para_a_frente=INATIVO;

	p.roque_possivel_direito[BRANCO]=TRUE;
	p.roque_possivel_direito[PRETO]=TRUE;

	p.roque_possivel_esquerdo[BRANCO]=TRUE;
	p.roque_possivel_esquerdo[PRETO]=TRUE;

	p.ult.x1=INVALIDO;
	p.ult.x2=INVALIDO;
	p.ult.y1=INVALIDO;
	p.ult.y2=INVALIDO;

	p.ataque=FALSE;

	return p;
}

char tabuleiro::num_to_ascii(int num_in) // converte um numero para o formato normal
{
	switch (num_in)
	{
	case 0: return 'A';
	case 1: return 'B';
	case 2: return 'C';
	case 3: return 'D';
	case 4: return 'E';
	case 5: return 'F';
	case 6: return 'G';
	case 7: return 'H';
	default: return 'x';    // para detectar erros
	}
}

void tabuleiro::mostre_pontos(EPONTOS loc)      // mostra o array de movimentos e pontos
{                                                       
											// de uma maneira mastigada
	console io;
	clrscr( FOREGROUND_WHITE | BACKGROUND_BLACK );
	printf("\n\n M O V I M E N T O   E   P O N T O S\n");
	int i,j;
	for(i=0;i<loc.pontos_pos;i++)
	{
//              if(loc.x_orig[i]==INATIVO) break;
		switch (loc.tipo[i])
		{
		case REI:    printf("-REI----(#)-"); break;   // tratamento tipo figura
		case RAINHA: printf("-RAINHA-(W)-"); break;
		case TORRE:  printf("-TORRE--(T)-"); break;
		case BISPO:  printf("-BISPO--(I)-"); break;
		case CAVALO: printf("-CAVALO-(P)-"); break;
		case PEAO:   printf("-PEAO---(i)-"); break;
		default: printf("-E R R O-\n");         // acusar erros
		}
		switch (loc.cor[i])
		{
		case BRANCO: printf(" -b- : "); break;     // tratamento da cor
		case PRETO:  printf(" -p- : "); break;
		default:     printf(" -ERRO!!- : "); break;     // dto
		}
		printf(" [%c",num_to_ascii(loc.x_orig[i])); // localizacao da peca
		printf("%i] ",loc.y_orig[i]+1);
		printf("a [%c",num_to_ascii(loc.x_dest[i]));
		printf("%i] ",loc.y_dest[i]+1);
		printf(" AN: ");
		for(j=0;j<18;j++) printf("%c",loc.analisador[j]);
		printf(" ES: %i",loc.especiais[i]);
		printf(" PT: ");
		printf("%i",loc.score[i]);
		printf("\n");
		if((i%18==0) && (i!=0))
		{
			io.espere_tecla();
			clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
		}
	}
	io.espere_tecla();
	clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
}

void tabuleiro::mostre_peca(int x_in, int y_in, int cor, PECAS p)       // mostra uma peca
{                                                                                                                                       // especifica em ascii
	int j;
	for(j=0;j<32;j++)
	{
		if(p.p[j].coordenadas(x_in,y_in)&&p.p[j].devolve_tipo()!=INATIVO)
		{
			p.p[j].mpa(cor);
			return;
		}
	}
	if (cor) setcolor( FOREGROUND_WHITE | BACKGROUND_DARKGRAY ); else
		setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
	
	printf("   ");

	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
	return;
}

void tabuleiro::mostre_ascii(PECAS p)   // mostra o tabuleiro inteiro em ascii
{
	// ATENCAO - tudo feito com gotoxy para evitar bagunca eventual na tela (por causo do \n)

	int i, j, cor_do_campo;
	//console io;
	// console io;
	gotoxy(0,2);
	printf("       A   B   C   D   E   F   G   H");
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
	gotoxy(5,3);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			cds1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, hva1, ho1,ho1,ho1, ces1);
	for (i=7;i>-1;i--)
	{
		if(i<7)
		{
			setcolor( FOREGROUND_WHITE | BACKGROUND_BLACK );
			gotoxy(5,(7-i)*2+3);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
				vhd1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, cr1, ho1,ho1,ho1, vhe1);
		}
		if (i % 2==0)
			cor_do_campo=0; else
			cor_do_campo=1;
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
		gotoxy(3,(7-i)*2+4);
		printf("%i ",i+1);
		for (j=0;j<8;j++)
		{
			setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
			printf("%c",ve1);
			mostre_peca(j,i,cor_do_campo,p);
			if (cor_do_campo==0) cor_do_campo=1; else
				cor_do_campo=0;
		}
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
		printf("%c",ve1);
		setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
		printf(" %i",i+1);
	}
	gotoxy(5,19);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLACK);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
			cdi1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, hve1, ho1,ho1,ho1, cei1);
	gotoxy(0,20);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
	printf("       A   B   C   D   E   F   G   H");
	setcolor(FOREGROUND_YELLOW | BACKGROUND_BLUE);

	if(p.ult.x1!=INVALIDO)
	{
		//setcolor( FOREGROUND_LIGHTRED | BACKGROUND_BLACK );
		//gotoxy(p.ult.x1*4+5,(7-p.ult.y1)*2+3);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+5,(7-p.ult.y1)*2+5);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+9,(7-p.ult.y1)*2+3);
		//printf("%c",cr1);
		//gotoxy(p.ult.x1*4+9,(7-p.ult.y1)*2+5);
		//printf("%c",cr1);

		setcolor( FOREGROUND_LIGHTBLUE | BACKGROUND_BLACK );
		gotoxy(p.ult.x2*4+5,(7-p.ult.y2)*2+3);
		printf("o");
	//	gotoxy(p.ult.x2*4+5,(7-p.ult.y2)*2+5);
	//	printf("%c",cr1);
	//	gotoxy(p.ult.x2*4+9,(7-p.ult.y2)*2+3);
	//	printf("%c",cr1);
	//	gotoxy(p.ult.x2*4+9,(7-p.ult.y2)*2+5);
	//	printf("%c",cr1);
	}

	setcolor( FOREGROUND_WHITE | BACKGROUND_CYAN );
	gotoxy(49,3);
	printf("%c",cds1);
	for(i=0;i<21;i++) printf("%c",ho1);
	printf("%c",ces1);
	gotoxy(49,4);
	printf("%c M  O  N  A  R  C  H %c",ve1,ve1);
	gotoxy(49,5);
	printf("%c    - Ver. 1.0 -     %c",ve1,ve1);
	gotoxy(49,6);
	printf("%c",cdi1);
	for(i=0;i<21;i++) printf("%c",ho1);
	printf("%c",cei1);
	setcolor(FOREGROUND_WHITE | BACKGROUND_BLUE);
}

int tabuleiro::coluna_em_num(char ch)   // converte o formato normal para o formato interno
{
	return toupper(ch)-'A';
}

int tabuleiro::qualpeca(int x_in, int y_in, PECAS p)    // devolve o tipo da peca em x,y
{
	int i;
	for(i=0;i<32;i++)
	{
		if(p.p[i].coordenadas(x_in, y_in))
		{
			return p.p[i].devolve_tipo();
		}
	}
	return INATIVO;
}

int tabuleiro::qualcor(int x_in, int y_in, PECAS p)     // devolve a cor da peca em x,y
{
	int i;
	for(i=0;i<32;i++)
	{
		if(p.p[i].coordenadas(x_in, y_in))
		{
			return p.p[i].devolve_cor();
		}
	}
	return INATIVO;
}

int tabuleiro::qual_numero_em_lista(int x_in, int y_in, PECAS p)        // devolve o numero da peca x,y na
{                                                                                                                                       // lista de movimentos
	int j;
	for(j=0;j<32;j++)
	{
		if(p.p[j].coordenadas(x_in, y_in))
		{
			return j;
		}
	}
	return INATIVO;
}

int tabuleiro::qual_numero_em_lista_pontos(int x_in, int y_in, int x_in2, int y_in2, EPONTOS p)
{
	int i;
	for(i=0;i<p.pontos_pos;i++)
	{
		if(p.x_orig[i]==x_in && p.y_orig[i]==y_in
			&& p.x_dest[i]==x_in2 && p.y_dest[i]==y_in2)
		{
			return i;
		}
	}
	return INATIVO;
}

PECAS tabuleiro::trata_roque(PECAS pc) // utilizada em execute_movimento e roque!
{
	// mexeu a torre em A1, entao perde o direito de fazer roque para este lado
	// (obs.: para determinar se foi mexido utiliza-se a teoria de que uma vez
	//  foi mexido o lugar onde fica a peca fica vazio logo após!)

	if(qualcor(0,0,pc)==INATIVO) pc.roque_possivel_esquerdo[BRANCO]=FALSE;
	// dto. para preto

	if(qualcor(0,7,pc)==INATIVO) pc.roque_possivel_esquerdo[PRETO]=FALSE;
	// dto. para preto

	if(qualcor(7,0,pc)==INATIVO) pc.roque_possivel_direito[BRANCO]=FALSE;
	// dto. para branco e outro lado

	if(qualcor(7,7,pc)==INATIVO) pc.roque_possivel_direito[PRETO]=FALSE;
	// dto. para preto

	if(qualcor(4,0,pc)==INATIVO)
	{
		pc.roque_possivel_esquerdo[BRANCO]=FALSE;
		pc.roque_possivel_direito[BRANCO]=FALSE;
	}

	// mexeu com o rei branco entao branco perdeu os dois direitos de fazer roque

	if(qualcor(4,7,pc)==INATIVO)
	{
		pc.roque_possivel_esquerdo[PRETO]=FALSE;
		pc.roque_possivel_direito[PRETO]=FALSE;
	}

	// dto. para o rei preto

	return pc;
}

PECAS tabuleiro::execute_movimento(int x_o, int y_o, int x_d, int y_d, PECAS pc, int especiais) // excuta um movimento em cima do tabuleiro
{
	int pos, direcao;

	// TRATAMENTO DE MOVIMENTOS NORMAIS A SEGUIR

	pc.ult.x1=x_o;
	pc.ult.y1=y_o;
	pc.ult.x2=x_d;
	pc.ult.y2=y_d;

	pos=qual_numero_em_lista(x_d,y_d,pc);   // deletar se tiver peca no destino
	if(pos!=INATIVO)
	{
		pc.p[pos].init(INATIVO,INATIVO,INATIVO,INATIVO,'X');
		pc.ataque=TRUE;
	} else pc.ataque=FALSE;
	
	pos=qual_numero_em_lista(x_o,y_o,pc);   // mudar coordenadas da peca
	pc.p[pos].init(x_d,y_d,pc.p[pos].devolve_tipo(),pc.p[pos].devolve_cor(),' ');

	// TRATAMENTO DE CONSEQUENCIAS DE MOVIMENTOS NORMAIS A SEGUIR

	// salvamento da coordenada x de um peao que foi duas casas para a frente
	// por causa de "en passent"

	if(qualpeca(x_d,y_d,pc)==PEAO && abs(y_d-y_o)==2)
		pc.peao_duas_casas_para_a_frente=x_d; else
		pc.peao_duas_casas_para_a_frente=INATIVO;

	pc=trata_roque(pc);     

	// TRATAMENTO DE MOVIMENTOS ESPECIAIS A SEGUIR

	switch(especiais)
	{
		case EN_PASSENT           :     if(y_d==2) direcao=1; else direcao=-1; // deletar para cima ou para baixo dependendo da posicao
							pos=qual_numero_em_lista(x_d,y_d+direcao,pc);   // deletar se tiver peca no destino
							pc.p[pos].init(INATIVO,INATIVO,INATIVO,INATIVO,'X');
							break;
		case ROQUE                :   if(y_d==0)
							{
								if(x_d==6)
								{                                               
									pos=qual_numero_em_lista(7,0,pc); // torre da esquina direita branca    
									pc.p[pos].init(5,0,TORRE,BRANCO,' '); // mudar as coordenadas
								} else
								{
									pos=qual_numero_em_lista(0,0,pc); // torre da esquina esquerda branca   
									pc.p[pos].init(3,0,TORRE,BRANCO,' '); // mudar as coordenadas                                                   
								}
							} else
							{
								if(x_d==6)
								{
									pos=qual_numero_em_lista(7,7,pc); // torre da esquina direita preta     
									pc.p[pos].init(5,7,TORRE,PRETO,' '); // mudar as coordenadas    
								}
								else
								{
									pos=qual_numero_em_lista(0,7,pc); // torre da esquina esquerda preta    
									pc.p[pos].init(3,7,TORRE,PRETO,' '); // mudar as coordenadas
								}
							}
							break;
		case PEAO_AVANCADO_RAINHA :     pos=qual_numero_em_lista(x_d,y_d,pc);   // ver a peca que acabou de ser colocada
							pc.p[pos].init(x_d,y_d,RAINHA,pc.p[pos].devolve_cor(),' '); // transformar em rainha
							break;
		case PEAO_AVANCADO_TORRE  :     pos=qual_numero_em_lista(x_d,y_d,pc);   // ver a peca que acabou de ser colocada
							pc.p[pos].init(x_d,y_d,TORRE,pc.p[pos].devolve_cor(),' '); // transformar em torre
							break;
		case PEAO_AVANCADO_CAVALO :     pos=qual_numero_em_lista(x_d,y_d,pc);   // ver a peca que acabou de ser colocada
							pc.p[pos].init(x_d,y_d,CAVALO,pc.p[pos].devolve_cor(),' '); // transformar em cavalo
							break;
		case PEAO_AVANCADO_BISPO  :     pos=qual_numero_em_lista(x_d,y_d,pc);   // ver a peca que acabou de ser colocada
							pc.p[pos].init(x_d,y_d,BISPO,pc.p[pos].devolve_cor(),' '); // transformar em bispo
							break;
	}

	return pc; // rotorno modificado
}

///////////////////////////////////////////////////////
// Classe: ANALISADOR DE MOVIMENTOS - Definicao      //
///////////////////////////////////////////////////////

// OBS.: subclasse de TABULEIRO

class analisador_movimento:public tabuleiro // analisador de movimento - ve as possibilidade de movimentos
{                                                                                       // a partir de certa posicao no tabuleiro
public:
	BOOL borda(int,int);                    // o teste de certa peca esta fora do tabuleiro?
	BOOL amigo(int,int,int,PECAS);  // a peca especificada e da mesma cor?
	BOOL inimigo(int,int,int,PECAS);        // a peca especificada e de cor diferente
	EPONTOS add_mov(int,int,int,EPONTOS,int,PECAS); // adiciona movimento na lista de movimentos
	void mostre_pontos(void);       // mostre os pontos na lista de movimentos
	EPONTOS roque(int,EPONTOS,int,PECAS); // checar se roque e possivel
	EPONTOS en_passent(int,EPONTOS,int,PECAS); // checar se "en passent" é possivel
	EPONTOS peao_avancado(int,EPONTOS,int,PECAS); // se houver um peao avancado
	EPONTOS rei(int,EPONTOS,int,PECAS);     // checagem para a peca rei
	EPONTOS rainha(int,EPONTOS,int,PECAS);  // checagem para a peca rainha
	EPONTOS torre(int,EPONTOS,int,PECAS); // checagem pata a peca torre
	EPONTOS cavalo(int,EPONTOS,int,PECAS);  // checagem para a peca cavalo
	EPONTOS bispo(int,EPONTOS,int,PECAS); // checagem para a peca bispo
	EPONTOS peao(int,EPONTOS,int,PECAS); // checagem para a peca peao
	EPONTOS executa(PECAS,int); // execucao do analisador
	BOOL permitido(int,int,int,int,int,PECAS);      // ve se um movimento e permitido
	BOOL bloqueio_basico(int,int,int,int,PECAS); // ve se ha um bloqueio basico para certo movimento
	BOOL bloqueio_basico_cavalo(int,int,int,int,PECAS); // s/ ultrapassagem de inimigo pois um cavalo pula
	EPONTOS init_pontos(void);      // inicializa o array de pontos e movimentos
	int signum(int); // funcao signum
	BOOL atacado(int,int,int,PECAS); // posicao esta atacada? -- rotina refeita para melhoria de performance
	BOOL vazio(int,int,PECAS); // devolve se certa posicao esta vazia
	BOOL testa_xeque(int, int, PECAS); // testa se houve um xeque
};

// Classe: ANALISADOR DE MOVIMENTOS - Metodos        

BOOL analisador_movimento::atacado(int x_in, int y_in, int na_vez, PECAS pc)

// para melhorar ainda mais o performance pode-se depos fazer uma pesquisa, qual
// peca mais ataca estatisticamente e colocar a checagem por ela na frente

{
	int i,j,peao_mais;

	BOOL acabou[8];
	
	for(i=0;i<8;i++) acabou[i]=FALSE;

	for(i=1;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(acabou[j]==FALSE)
			{
				if(qualcor(x_in+mais[j].x*i,y_in+mais[j].y*i,pc)==na_vez ||
				   borda(x_in+mais[j].x*i,y_in+mais[j].y*i))
					acabou[j]=TRUE;

				if(qualcor(x_in+mais[j].x*i,y_in+mais[j].y*i,pc)==!na_vez && acabou[j]==FALSE)
				      switch(qualpeca(x_in+mais[j].x*i,y_in+mais[j].y*i,pc))
				      {
					   case RAINHA : return TRUE; break;                            
					   case BISPO : if(j>3) return TRUE; else acabou[j]=TRUE; break;
					   case TORRE : if(j<4) return TRUE; else acabou[j]=TRUE; break;
					   case REI : if(i==1) return TRUE; else acabou[j]=TRUE; break;

					   case CAVALO : acabou[j]=TRUE; break;       // tratados separadamente (veja abaixo) aqui somente 
					   case PEAO : acabou[j]=TRUE; break;        // precisa-se evitar que um ataque "passa" sobre uma peca!!
				      }
			}
		}
	}

	if(na_vez==BRANCO) peao_mais=1; else peao_mais=-1;

	if((qualcor(x_in+1,y_in+peao_mais,pc)==!na_vez && qualpeca(x_in+1,y_in+peao_mais,pc)==PEAO) ||
	   (qualcor(x_in-1,y_in+peao_mais,pc)==!na_vez && qualpeca(x_in-1,y_in+peao_mais,pc)==PEAO))
		return TRUE;

	for(i=0;i<8;i++)
		if(qualcor(x_in+cmais[i].x,y_in+cmais[i].y,pc)==!na_vez &&
		   qualpeca(x_in+cmais[i].x,y_in+cmais[i].y,pc)==CAVALO)
			return TRUE;

	return FALSE;
}

int analisador_movimento::signum(int num_in) // funcao signo
{
	if(num_in<0) return -1;
	  else if(num_in==0) return 0; else
		  return 1;
}

BOOL analisador_movimento::borda(int x_in, int y_in) // a peca esta fora da borda?
{
	if(x_in<0 || x_in>7 || y_in<0 || y_in>7)
		return TRUE; else
	return FALSE;
}

BOOL analisador_movimento::amigo(int x_in, int y_in, int na_vez, PECAS p) // peca da mesma cor?
{
	if(qualcor(x_in,y_in,p)==na_vez || qualpeca(x_in,y_in,p)==REI)
		return TRUE; else
	return FALSE;
}

BOOL analisador_movimento::inimigo(int x_in, int y_in, int na_vez, PECAS p) // peca de cor diferente?
{
	if(qualcor(x_in,y_in,p)!=na_vez && qualpeca(x_in,y_in,p)!=REI
		&& qualcor(x_in,y_in,p)!=INATIVO)
		return TRUE; else
		return FALSE;
}

BOOL analisador_movimento::vazio(int x_in, int y_in, PECAS p)
//
// devolve se a posicao esta vazia - somente serve para melhorar a leitura
//
{
	if(qualcor(x_in,y_in,p)==INATIVO) return TRUE; else
		return FALSE;
}

BOOL analisador_movimento::bloqueio_basico(int x_mais,int y_mais, int na_vez, int pos, PECAS p) // existe a figura do bloqueio basico para
{                                                                                                                                                                                               // o movimento
	if(borda(p.p[pos].devolve_x()+x_mais,p.p[pos].devolve_y()+y_mais)
		||amigo(p.p[pos].devolve_x()+x_mais,p.p[pos].devolve_y()+y_mais,na_vez,p)==TRUE
		||(inimigo(p.p[pos].devolve_x()+x_mais+signum(-x_mais),
		p.p[pos].devolve_y()+y_mais+signum(-y_mais),na_vez,p)))
		return TRUE; 
	else return FALSE;
}

BOOL analisador_movimento::bloqueio_basico_cavalo(int x_mais,int y_mais, int na_vez, int pos, PECAS p) // existe a figura do bloqueio basico para
{                                                                                                                                                                                               // o movimento
	if(borda(p.p[pos].devolve_x()+x_mais,p.p[pos].devolve_y()+y_mais)
		||amigo(p.p[pos].devolve_x()+x_mais,p.p[pos].devolve_y()+y_mais,na_vez,p))
		return TRUE; 
	else return FALSE;
}

EPONTOS analisador_movimento::add_mov(int x_mais, int y_mais, int esp, EPONTOS loc, int pos, PECAS pc) // adiciona movimento na lista de movimentos
{
	int i;
	// cout << " ADDMOV EXECUTED \n\n";
	loc.tipo[loc.pontos_pos]=pc.p[pos].devolve_tipo();
	loc.x_orig[loc.pontos_pos]=pc.p[pos].devolve_x();
	loc.y_orig[loc.pontos_pos]=pc.p[pos].devolve_y();
	loc.x_dest[loc.pontos_pos]=pc.p[pos].devolve_x()+x_mais;
	loc.y_dest[loc.pontos_pos]=pc.p[pos].devolve_y()+y_mais;
	loc.cor[loc.pontos_pos]=pc.p[pos].devolve_cor();
	loc.especiais[loc.pontos_pos]=esp;
	for(i=0;i<18;i++) loc.analisador[i]='.';
	loc.pontos_pos++;

	return loc;
}

EPONTOS analisador_movimento::roque(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	int linha_rei;

	pc=trata_roque(pc); // localmente para ter toda certeza que nao de problemas com posicoes lidas de disco!!

	if(na_vez==BRANCO) linha_rei=0; else linha_rei=7; // para facilitar o processamento

	if(pc.roque_possivel_direito[na_vez] && vazio(5,linha_rei,pc) && vazio(6,linha_rei,pc)
	   && atacado(5,linha_rei,na_vez,pc)==FALSE && atacado(6,linha_rei,na_vez,pc)==FALSE
	   && atacado(4,linha_rei,na_vez,pc)==FALSE)	// corrido=o rei tambem nao pode se encontram em ataque!!
		loc1=add_mov(2,0,ROQUE,loc1,pos,pc);

	//loc1=add_mov(2,0,ROQUE,loc1,pos,pc); // somente p teste

	// explicacao: roque para a direita
	//
	// 1. nenhuma das figuras pode ter se mexida, o que é tratado pelo executor e o resultado
	//    e fornecido para a variavel roque_possivel_direito
	// 2. nenhuma das posicoes percorridas pode estar com uma outra figura no meio
	// 3. nenhuma das posicoes percorridas pode estar em ataque
	//
	// obs.: o xeque tem que ser tratado fora desta rotina e o executar recebendo a informacao
	//       adicional que se trata de roque, tem que executar tambem o movimento da torre

	if(pc.roque_possivel_esquerdo[na_vez] && vazio(1,linha_rei,pc) && vazio(2,linha_rei,pc) && vazio(3,linha_rei,pc)
		&& atacado(1,linha_rei,na_vez,pc)==FALSE && atacado(2,linha_rei,na_vez,pc)==FALSE
		&& atacado(3,linha_rei,na_vez,pc)==FALSE
		&& atacado(4,linha_rei,na_vez,pc)==FALSE)	// corrigido=o rei tambem nao pode se encontram em ataque
		loc1=add_mov(-2,0,ROQUE,loc1,pos,pc);

	//loc1=add_mov(-2,0,ROQUE,loc1,pos,pc);  // somente p teste
	

	// mesmo mecanismo de cima com a diferenca que agora tem que checar 3 campos do outro lado do rei

	return loc1;
}

EPONTOS analisador_movimento::en_passent(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	int x_peao, y_peao;

	x_peao=pc.p[pos].devolve_x();   // para facilitar o calculo
	y_peao=pc.p[pos].devolve_y();

//      cout << " en_pass: " << pc.peao_duas_casas_para_a_frente << "\n";
//      cin >> pc.peao_duas_casas_para_a_frente;

	if(pc.peao_duas_casas_para_a_frente!=INATIVO)   // fazer algo somente se houve uma situacao que permite
	{
		if(na_vez==BRANCO &&                                                            // peao branco executando
			abs(pc.peao_duas_casas_para_a_frente-x_peao)==1 &&
				y_peao==4)
			loc1=add_mov((pc.peao_duas_casas_para_a_frente-x_peao),1,EN_PASSENT,loc1,pos,pc); else

		if(na_vez==PRETO &&                                                             // peao preto executando
			abs(pc.peao_duas_casas_para_a_frente-x_peao)==1 &&
				y_peao==3)
			loc1=add_mov((pc.peao_duas_casas_para_a_frente-x_peao),-1,EN_PASSENT,loc1,pos,pc);
	}

	return loc1;
}

EPONTOS analisador_movimento::peao_avancado(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	int x_peao, y_peao;

	x_peao=pc.p[pos].devolve_x();   // para facilitar o calculo
	y_peao=pc.p[pos].devolve_y();

	if(na_vez==BRANCO && y_peao==6 && vazio(x_peao,7,pc))   // peao avancado branco
	{
		loc1=add_mov(0,1,PEAO_AVANCADO_RAINHA,loc1,pos,pc);     // possibilidades de trocas
		loc1=add_mov(0,1,PEAO_AVANCADO_TORRE,loc1,pos,pc);
		loc1=add_mov(0,1,PEAO_AVANCADO_CAVALO,loc1,pos,pc);
		loc1=add_mov(0,1,PEAO_AVANCADO_BISPO,loc1,pos,pc);
	} else
	if(na_vez==PRETO && y_peao==1 && vazio(x_peao,0,pc))    // peao avancado preto
	{
		loc1=add_mov(0,-1,PEAO_AVANCADO_RAINHA,loc1,pos,pc);    // possibilidades de trocas
		loc1=add_mov(0,-1,PEAO_AVANCADO_TORRE,loc1,pos,pc);
		loc1=add_mov(0,-1,PEAO_AVANCADO_CAVALO,loc1,pos,pc);
		loc1=add_mov(0,-1,PEAO_AVANCADO_BISPO,loc1,pos,pc);
	}

	return loc1;
}

EPONTOS analisador_movimento::rei(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	//cout << "am-<#>"; // output de controle

/*      int x_rei, y_rei;

	BOOL possivel[8];

	x_rei=pc.p[pos].devolve_x();
	y_rei=pc.p[pos].devolve_y();

	pc.p[pos].init(x_rei,y_rei,TORRE,na_vez,' ');
	// tirar o rei para nao atrapalhar as possiveis linhas de ataque!!

	// testes comecando de baixo contra o sentido do relogio

	if(atacado(x_rei+1,y_rei+1,na_vez,pos,pc)) possivel[0]=FALSE; else possivel[0]=TRUE;
	if(atacado(x_rei+0,y_rei+1,na_vez,pos,pc)) possivel[1]=FALSE; else possivel[1]=TRUE;
	if(atacado(x_rei-1,y_rei+1,na_vez,pos,pc)) possivel[2]=FALSE; else possivel[2]=TRUE;
	if(atacado(x_rei+1,y_rei+0,na_vez,pos,pc)) possivel[3]=FALSE; else possivel[3]=TRUE;
	if(atacado(x_rei+1,y_rei-1,na_vez,pos,pc)) possivel[4]=FALSE; else possivel[4]=TRUE;
	if(atacado(x_rei+0,y_rei-1,na_vez,pos,pc)) possivel[5]=FALSE; else possivel[5]=TRUE;
	if(atacado(x_rei-1,y_rei-1,na_vez,pos,pc)) possivel[6]=FALSE; else possivel[6]=TRUE;
	if(atacado(x_rei-1,y_rei+0,na_vez,pos,pc)) possivel[7]=FALSE; else possivel[7]=TRUE;

	// os zeros por motivo de leitura

	pc.p[pos].init(x_rei,y_rei,REI,BRANCO,' ');
	// devolver o rei ate a posicao para a analise de bloqeuio basico
*/
	if(bloqueio_basico_cavalo(1,1,na_vez,pos,pc)==FALSE) // && possivel[0]
	loc1=add_mov(1,1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(0,1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(0,1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(-1,1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-1,1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(1,0,na_vez,pos,pc)==FALSE)
	loc1=add_mov(1,0,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(1,-1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(1,-1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(0,-1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(0,-1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(-1,-1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-1,-1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(-1,0,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-1,0,NORMAL,loc1,pos,pc);

	return loc1;    // retorna array de pontos modificado
}

EPONTOS analisador_movimento::rainha(int na_vez, EPONTOS loc1, int pos, PECAS pc) // tratamento da rainha
{
	int j;

	//cout << "am-<W> "; // output de controle
	
	BOOL acabou[8];
	for(j=0;j<8;j++)
		acabou[j]=FALSE;
	for(j=1;j<8;j++)
	{
		if(bloqueio_basico(j,0,na_vez,pos,pc)||acabou[0]) // possiveis movimentos em todas as direcoes
			acabou[0]=TRUE;                                                                 // ate acabar o espaco
		else loc1=add_mov(j,0,NORMAL,loc1,pos,pc);

		if(bloqueio_basico(-j,0,na_vez,pos,pc)||acabou[1])
			acabou[1]=TRUE; 
		else loc1=add_mov(-j,0,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(0,-j,na_vez,pos,pc)||acabou[2])
			acabou[2]=TRUE; 
		else loc1=add_mov(0,-j,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(0,j,na_vez,pos,pc)||acabou[3])
			acabou[3]=TRUE; 
		else loc1=add_mov(0,j,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(j,j,na_vez,pos,pc)||acabou[4])
			acabou[4]=TRUE; 
		else loc1=add_mov(j,j,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(-j,-j,na_vez,pos,pc)||acabou[5])
			acabou[5]=TRUE; 
		else loc1=add_mov(-j,-j,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(j,-j,na_vez,pos,pc)||acabou[6])
			acabou[6]=TRUE; 
		else loc1=add_mov(j,-j,NORMAL,loc1,pos,pc);
		
		if(bloqueio_basico(-j,j,na_vez,pos,pc)||acabou[7])
			acabou[7]=TRUE; 
		else loc1=add_mov(-j,j,NORMAL,loc1,pos,pc);
	}
	return loc1;
}

EPONTOS analisador_movimento::torre(int na_vez, EPONTOS loc1, int pos, PECAS pc) // tratamento torre
{
	int j;
	
	//cout << "am-<T> "; // output de controle
	
	BOOL acabou[4];
	for(j=0;j<4;j++)
		acabou[j]=FALSE;
	for(j=1;j<8;j++)
	{
		if(bloqueio_basico(j,0,na_vez,pos,pc)||acabou[0]) // possiveis movimentos em quatro direcoes 
			acabou[0]=TRUE;                                                                 // de forma vertical e horizontal
		else loc1=add_mov(j,0,NORMAL,loc1,pos,pc);                      // ate acabar o espaco
		if(bloqueio_basico(-j,0,na_vez,pos,pc)||acabou[1])
			acabou[1]=TRUE; 
		else loc1=add_mov(-j,0,NORMAL,loc1,pos,pc);
		if(bloqueio_basico(0,-j,na_vez,pos,pc)||acabou[2])
			acabou[2]=TRUE; 
		else loc1=add_mov(0,-j,NORMAL,loc1,pos,pc);
		if(bloqueio_basico(0,j,na_vez,pos,pc)||acabou[3])
			acabou[3]=TRUE; 
		else loc1=add_mov(0,j,NORMAL,loc1,pos,pc);
	}

	return loc1;
}

EPONTOS analisador_movimento::cavalo(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	
	//cout << "am-<P> "; // output de controle
	
	if(bloqueio_basico_cavalo(2,1,na_vez,pos,pc)==FALSE) // checagem dos 8 pontos especificos que o cavalo pode ir
	loc1=add_mov(2,1,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(-2,1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-2,1,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(2,-1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(2,-1,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(-2,-1,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-2,-1,NORMAL,loc1,pos,pc);

	if(bloqueio_basico_cavalo(1,2,na_vez,pos,pc)==FALSE)
	loc1=add_mov(1,2,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(-1,2,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-1,2,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(1,-2,na_vez,pos,pc)==FALSE)
	loc1=add_mov(1,-2,NORMAL,loc1,pos,pc);
	if(bloqueio_basico_cavalo(-1,-2,na_vez,pos,pc)==FALSE)
	loc1=add_mov(-1,-2,NORMAL,loc1,pos,pc);

	return loc1;
}


EPONTOS analisador_movimento::bispo(int na_vez, EPONTOS loc1, int pos, PECAS pc)
{
	int j;
	
	//cout << "am-<L> "; // output de controle
	
	BOOL acabou[4];
	for(j=0;j<4;j++)
		acabou[j]=FALSE;
	for(j=1;j<8;j++)
	{
		if(bloqueio_basico(j,j,na_vez,pos,pc)||acabou[0]) // veja torre - somente diagonal!
			acabou[0]=TRUE; 
		else loc1=add_mov(j,j,NORMAL,loc1,pos,pc);
		if(bloqueio_basico(-j,-j,na_vez,pos,pc)||acabou[1])
			acabou[1]=TRUE; 
		else loc1=add_mov(-j,-j,NORMAL,loc1,pos,pc);
		if(bloqueio_basico(j,-j,na_vez,pos,pc)||acabou[2])
			acabou[2]=TRUE; 
		else loc1=add_mov(j,-j,NORMAL,loc1,pos,pc);
		if(bloqueio_basico(-j,j,na_vez,pos,pc)||acabou[3])
			acabou[3]=TRUE; 
		else loc1=add_mov(-j,j,NORMAL,loc1,pos,pc);
	}

	return loc1;
}

EPONTOS analisador_movimento::peao(int na_vez, EPONTOS loc1, int pos, PECAS pc)
// 
// trata somente os casos normais do peao - en passent e peao avancado sao tratados aparte
//
{
	
	//cout << "am-<i> "; // output de controle
	
	int peao_x, peao_y;

	peao_x=pc.p[pos].devolve_x();
	peao_y=pc.p[pos].devolve_y();

	if(na_vez==BRANCO && peao_y!=6) // branco para cima - preto para baixo
	{
		if(vazio(peao_x,peao_y+1,pc))
		{
			loc1=add_mov(0,1,NORMAL,loc1,pos,pc);           // movimentos normais
			if(vazio(peao_x,peao_y+2,pc) && peao_y==1)
				loc1=add_mov(0,2,NORMAL,loc1,pos,pc);

		}

		if(bloqueio_basico_cavalo(1,1,na_vez,pos,pc)==FALSE && 
			vazio(peao_x+1,peao_y+1,pc)==FALSE)             // movimentos para tirar outra peca
			loc1=add_mov(1,1,NORMAL,loc1,pos,pc);

		if(bloqueio_basico_cavalo(-1,1,na_vez,pos,pc)==FALSE &&
			vazio(peao_x-1,peao_y+1,pc)==FALSE)
			loc1=add_mov(-1,1,NORMAL,loc1,pos,pc);

	}
	else
		if(na_vez==PRETO && peao_y!=1)
		{
			if(vazio(peao_x,peao_y-1,pc))           
			{
				loc1=add_mov(0,-1,NORMAL,loc1,pos,pc);  // movimentos normais
				if(vazio(peao_x,peao_y-2,pc) && peao_y==6)
					loc1=add_mov(0,-2,NORMAL,loc1,pos,pc);
			}

			if(bloqueio_basico_cavalo(1,-1,na_vez,pos,pc)==FALSE &&        // movimentos para tirar outra peca
				vazio(peao_x+1,peao_y-1,pc)==FALSE)
				loc1=add_mov(1,-1,NORMAL,loc1,pos,pc);
	
			if(bloqueio_basico_cavalo(-1,-1,na_vez,pos,pc)==FALSE &&
				vazio(peao_x-1,peao_y-1,pc)==FALSE)
				loc1=add_mov(-1,-1,NORMAL,loc1,pos,pc);

		}

	return loc1;
}

BOOL analisador_movimento::testa_xeque(int na_vez, int pos, PECAS pc)
// 
// analisa se o rei se encontra em xeque
//
{
//      cout << "Testa-Xeque online.\n";

//      cin.get(novalinha);

//      tabuleiro tb;

	BOOL xeque_achado;

	int x_rei, y_rei;

	x_rei=pc.p[pos].devolve_x();
	y_rei=pc.p[pos].devolve_y();

//      cout << "X-rei:" << x_rei << " Y-Rei:" << y_rei << " Pos:" << pos << "\n";

//      cin.get(novalinha);

	pc.p[pos].init(x_rei,y_rei,TORRE,na_vez,' ');  // retirar o rei para nao atrapalhar no teste
										// (rei nao pode-se retirar entao ele tambem nao iria acusar
										// que esta atacado)

//      cout << "analisador ataque online\n";

//      cin.get(novalinha);
//      cin.get(novalinha);

//      tb.mostre_ascii(pc);

	if(atacado(x_rei,y_rei,na_vez,pc))
		xeque_achado=pos; else
		xeque_achado=INVALIDO;          // ver se o campo encontra-se atacado

//      cout << "xeque achado:" << xeque_achado << "\n";

//      cin.get(novalinha);

	//cout << " x_rei: " << x_rei << " y_rei: " << y_rei << " xeque: " << xeque_achado << "\n";
	//cin >> xeque_achado;

	pc.p[pos].init(x_rei,y_rei,REI,na_vez,' '); // colocar o rei de volta no lugar antes de retornar

	return xeque_achado;
}

EPONTOS analisador_movimento::init_pontos()     // inicializa a lista de pontos
{                                                                                       // e movimentos
	int i;
	EPONTOS loc;
	for(i=0;i<140;i++)
	{
		loc.x_orig[i]=INATIVO;
		loc.y_orig[i]=INATIVO;
		loc.x_dest[i]=INATIVO;
		loc.y_dest[i]=INATIVO;
		loc.score[i]=0;
		loc.especiais[i]=0;
	}
	loc.pontos_pos=0;

	return loc;
}

EPONTOS analisador_movimento::executa(PECAS pc, int na_vez_atualmente)
{
	EPONTOS loc2;
	PECAS pecas_analise_xeque;
	BOOL xeque, xeque2;
//      tabuleiro tb;
	int i, j;

	xeque=INVALIDO;         // se nao passar pelo analisador!!

	loc2=init_pontos();
	// cout << "--->ANALISADOR DE MOVIMENTOS  O N L I N E !\n";

	for(i=0;i<32;i++)
	{
		// cout << algo[1] << algo[2] << algo[3] << algo[4] << algo[5] << algo[6];
		if(pc.p[i].devolve_cor()==na_vez_atualmente) //somente os movimentos da cor atual, os outros NAO INTERESSAM porque nao serao executados
		{
			switch(pc.p[i].devolve_tipo())
			{
				case RAINHA :  loc2=rainha(na_vez_atualmente,loc2,i,pc); break; // primeiro analisador todas as relacoes
				case TORRE  :  loc2=torre(na_vez_atualmente,loc2,i,pc); break;
				case CAVALO :  loc2=cavalo(na_vez_atualmente,loc2,i,pc); break;
				case BISPO  :  loc2=bispo(na_vez_atualmente,loc2,i,pc); break;
				case PEAO   :  loc2=peao(na_vez_atualmente,loc2,i,pc); 
								//cout << " en pass: " << pc.peao_duas_casas_para_a_frente;
								//cout << " x: " << pc.p[i].devolve_x() << "\n"; 
								loc2=en_passent(na_vez_atualmente,loc2,i,pc);
								loc2=peao_avancado(na_vez_atualmente,loc2,i,pc); break;
				case REI    :  loc2=rei(na_vez_atualmente,loc2,i,pc);
									loc2=roque(na_vez_atualmente,loc2,i,pc);
								xeque=i;
								//xeque=testa_xeque(na_vez_atualmente,i,pc); break;
								break;
			}
		}
	}

//      cout << " xeque: " << xeque << "\n";

//      cin.get(novalinha);
//      cin.get(novalinha);

	//cin >> xeque;

	// TESTAR AQUI !!!!

//      cout << "posicao 0\n";

    //tb.mostre_pontos(loc2);

	//if(xeque!=INVALIDO)   // reducao dos movimentos disponiveis em caso de xeque
	//{

		for(i=0;i<loc2.pontos_pos;i++)
		{
			pecas_analise_xeque=execute_movimento(loc2.x_orig[i],loc2.y_orig[i],loc2.x_dest[i],loc2.y_dest[i],pc,loc2.especiais[i]);

//                      tb.mostre_ascii(pecas_analise_xeque);

//                      cin.get(novalinha);
//                      cin.get(novalinha);

			xeque2=testa_xeque(na_vez_atualmente,xeque,pecas_analise_xeque);
			
			if(xeque2!=INVALIDO)
			{
//                              printf("entrei!! \n");
				j=loc2.pontos_pos-1;
//                              cout << "antes:\n";
//                              tb.mostre_pontos(loc2);
				if(j>0)
				{
					loc2.x_orig[i]=loc2.x_orig[j];  // o movimento atual provoca um xeque a segundo nivel, o que significa que ele
					loc2.y_orig[i]=loc2.y_orig[j];  // NAO ESTA PERMITIDO - por isso grava-se o ultimo movimento em cima dele
					loc2.x_dest[i]=loc2.x_dest[j];  // e deleta-se o ultimo movimento
					loc2.y_dest[i]=loc2.y_dest[j];  // obs.: isto funciona somente com mais do que 1 movimento, por isso o "if" -
					loc2.tipo[i]=loc2.tipo[j];              //       se houver somente um movimento ele e deletado direto
					loc2.cor[i]=loc2.cor[j];
					loc2.especiais[i]=loc2.especiais[j];

				}

				loc2.x_orig[j]=INATIVO;         // deletar movimento que nao se aplica
				loc2.y_orig[j]=INATIVO;
				loc2.x_dest[j]=INATIVO;
				loc2.y_dest[j]=INATIVO;
				loc2.score[j]=0;
				loc2.especiais[j]=0;

				loc2.pontos_pos--;              // posicao dos pontos - 1
//                              cout << "apos:";
//                              tb.mostre_pontos(loc2);

				i--;    // senao pula uma posicao !!

				}
		}       
	//}

	return loc2;
}

int analisador_movimento::permitido(int x_o, int y_o, int x_d, int y_d, int na_vez, PECAS pc) // ver se um movimento e permitid o cfe. analisador movimentos
//
// comparar o movimento atual com a lista de movimentos -> se o movimento escolhido estiver dentro entao esta permitido, senao 
//
{
	int i;

	EPONTOS pontos_loc;

	pontos_loc=executa(pc,na_vez); // rodar o analisador de movimentos em cima da posicao atual

	if(pontos_loc.pontos_pos==0)
	{
		for(i=0;i<32;i++)
		{
			if(pc.p[i].devolve_tipo()==REI && pc.p[i].devolve_cor()==na_vez)
				if(atacado(pc.p[i].devolve_x(),pc.p[i].devolve_y(),na_vez,pc))
					return MATE; else return EMPATE;
		}
	}

	for(i=0;i<pontos_loc.pontos_pos;i++)
	{
		if(x_o==pontos_loc.x_orig[i] &&
			y_o==pontos_loc.y_orig[i] &&
			x_d==pontos_loc.x_dest[i] &&
			y_d==pontos_loc.y_dest[i])
				return TRUE;            // achou um movimento igual na lista, entao e permitido
	
	}

	return FALSE; // nao caiu fora ainda, isto e, nao achou nada, entao nao e permitido
}

///////////////////////////////////////////////////////
// Classe: BIBLIOTECA - Definicao                    //
///////////////////////////////////////////////////////
/*
class biblioteca {      // aplicacao da biblioteca de aberturas
public: 
	void executa(void);
};

// BIBLIOTECA - Metodos

void biblioteca::executa(void)
{
	printf("--->BIBLIOTECA DE ABERTURA  O N L I N E\n");
}
*/
///////////////////////////////////////////////////////
// Classe: ANALISADOR MATE DIRETO - Definicao        //
///////////////////////////////////////////////////////

// OBS.: subclasse de tabuleiro

// esta classe somente existe para melhoria de leitura - o mecanismo e o seguinte:
// o analisador de movimentos e chamado com um movimento com certeza ilegal (dummy-movement)
// e se e devolvido uma lista vazia (o que ja e processado no analisador de movimentos corretamente
// como mate) entao achou-se um mate e estes dados serao devolvidos

class analisador_mate:public tabuleiro // analisador de mate direto a partir de uma posicao
{
	analisador_movimento amove;
public:
	int mate(int, PECAS);
};

// ANALISADOR MATE DIRETO - Metodos

int analisador_mate::mate(int na_vez, PECAS pc)
{
	int flag;
	flag=amove.permitido(0,0,0,0,na_vez,pc);

	return flag;
	
}

///////////////////////////////////////////////////////
// Classe: ANALISADOR CENTRAL - Definicao            //
///////////////////////////////////////////////////////

// OBS.: subclasse de tabuleiro

class analisador_central:public tabuleiro
{
	analisador_movimento amove;
	BOOL debug;
	int rei_x[2], rei_y[2];
public:
	int mate_ofensivo_em_1(EPONTOS,PECAS,int);
	EPONTOS mate_ofensivo_em_2(EPONTOS,PECAS,int);
	EPONTOS mate_ofensivo_em_3(EPONTOS,PECAS,int);

	EPONTOS mate_defensivo_em_1(EPONTOS,PECAS,int);
	EPONTOS mate_defensivo_em_2(EPONTOS,PECAS,int);

	EPONTOS anti_empate(EPONTOS,PECAS,int);
	EPONTOS anti_ataque(EPONTOS,PECAS,int);

	EPONTOS anti_ataque_duplo(EPONTOS,PECAS,int);
	EPONTOS anti_ataque_duplo_completo(EPONTOS,PECAS,int);
	EPONTOS anti_xeque(EPONTOS,PECAS,int);

	EPONTOS anti_abre_portas(EPONTOS,PECAS,int);
	
	EPONTOS ataque(EPONTOS,PECAS,int);
	
	EPONTOS ataque_duplo(EPONTOS,PECAS,int);

	EPONTOS busca_xeque(EPONTOS,PECAS,int);
	
	EPONTOS defesa(EPONTOS,PECAS,int);

	EPONTOS desenvolvimento(EPONTOS,PECAS,int,int);

	EPONTOS decisao(EPONTOS,int);

	BOOL controle_linhas(int,int,int,PECAS);
	BOOL proximidade_rei(int,int,PECAS,int);

	int define_fase(PECAS); // define a fase do jogo

	int calcule_melhor_movimento(int,PECAS,EPONTOS*);        // versao III gerenciador do analisador central

	EPONTOS deleta_movimento(EPONTOS,int);  // para deletar um movimento da lista

	void debug_output(int);

	int retorna_valor_peca(int);

	long int retorna_ataque_multiplo(EPONTOS,PECAS,int);

	void pega_posicoes_reis(PECAS);

	int risco(int,int,int,PECAS);

	int vantagem(int,EPONTOS,PECAS);

	int conta_ataques(PECAS,int);

	int maior_movimento(EPONTOS);
};

void analisador_central::pega_posicoes_reis(PECAS pc)
{
	int i, cor;
	
	rei_x[BRANCO]=INVALIDO;
	rei_y[BRANCO]=INVALIDO;
	rei_x[PRETO]=INVALIDO;
	rei_y[PRETO]=INVALIDO;

	for(i=0;i<32;i++)
	{
		if(pc.p[i].devolve_tipo()==REI)
		{
			cor=pc.p[i].devolve_cor();
			rei_x[cor]=pc.p[i].devolve_x();
			rei_y[cor]=pc.p[i].devolve_y();
		}
	}
}

long int analisador_central::retorna_ataque_multiplo(EPONTOS pt, PECAS pc, int na_vez)
//
//	RETORNA SE NO TABULEIRO ATUAL HA UM ATAQUE MULTIPLO (+ QUE 2)
//
//	OTIMIZACAO DO PROCEDIMENTO UTILIZADO ANTERIORMENTE
//
{
	//console io;

	int i, atacados, j, xeque_no_tabuleiro;

	long int risc, maior, segundo_maior;

	maior=INVALIDO;

	segundo_maior=INVALIDO;

	xeque_no_tabuleiro=FALSE;

	atacados=0;

	for(i=0;i<32;i++)
	{
		if(pc.p[i].devolve_cor()!=na_vez && pc.p[i].devolve_tipo()!=INVALIDO)
		{
			if(amove.atacado(pc.p[i].devolve_x(),pc.p[i].devolve_y(),!na_vez,pc))
			{
				atacados++;
				for(j=0;j<pt.pontos_pos;j++)
				{
					if(pc.p[i].devolve_x()==pt.x_dest[j] && 
						pc.p[i].devolve_y()==pt.y_dest[j])
					{
						risc=vantagem(j,pt,pc);	// vantagem pela execucao deste movimento??
						if(risc>0)
						{
							if(risc>maior)
							{
								segundo_maior=maior;		// caso afirmativo:
								maior=risc;
							} else
								if(risc>segundo_maior)
									segundo_maior=risc;
						}
					}
					if(pc.p[i].devolve_tipo()==REI) xeque_no_tabuleiro=TRUE;
				}
			}
		}
	}

	
//	mostre_ascii(pc);
//	gotoxy(0,0);
//	printf("devol: sm:%i ma:%i at:%i",segundo_maior,maior,atacados);
//	io.espere_tecla();
//	gotoxy(0,0);
//	printf("                                                         ");

	if(atacados>1) 
		if(xeque_no_tabuleiro) return maior; else
			return segundo_maior;	// pelo menos 2 ataques!!

	return INVALIDO;
}

int analisador_central::retorna_valor_peca(int peca)
{
	switch(peca)	// valores multiplicados por 10 para poder aplicar ainda pequenos descontos ou aumentos
	{
		case REI :    return 10000;	// nao tomar pecas com o rei se houver perigo algum!!
		case RAINHA : return 9000;
		case TORRE :  return 5000;
		case BISPO :  return 3000;
		case CAVALO : return 3000;
		case PEAO :   return 1000;
	}
	return 0;	
}

int analisador_central::risco(int loc_x, int loc_y, int na_vez, PECAS pc)
//
//	calculo de risco que uma peca tem se ficar em certa posicao
//	rotina essencial para o conhecimento de boas jogadas e para evitar
//	uma recursividade muito alta
//
//	a presente rotina calcula os movimentos possiveis ATE O FINAL da cadeia,
//	isto e, ate acabar a batalha definitivamente!!
//
//	SAIDA: pontuacao negativa = desvantagem
//		 pontuacao positiva = vantagem
{
	const long int DUMMY = 200000;	// valores de inicializacao

//	console io;	// somente para os testes

	int pontos, peca, posicao, i;	

	int pontos_totais, menor_pos, menor_valor, na_vez_inicial;

	EPONTOS mov_loc;	// array de movimentos obtidos a partir das posicoes

	BOOL stop;	// indicador que para a analise de maneira extraordinaria

	pontos=0;	// os pontos a serem devolvidos sao = 0

	posicao=0;	// comeca a avaliar a posicao 0

	pontos_totais=0;	// total de pontos ate o final da batalha

	na_vez_inicial=na_vez;	// memorizar quem esta jogando

	mov_loc.pontos_pos=DUMMY;

	stop=FALSE;	// inicializacao do indicador "stop"

	while(amove.atacado(loc_x,loc_y,na_vez,pc) && stop==FALSE)	// importante: o atacado nao funciona em situacoes de xeque 
											// para estes casos utiliza-se o indicador "stop"
	{
		posicao++;	// proxima posicao

		peca=qualpeca(loc_x,loc_y,pc);	// para poupar tempo de processamento, 
								// aramazena valor em variavel

		if(na_vez==na_vez_inicial)
			pontos_totais=pontos_totais-retorna_valor_peca(peca); else	// se uma peca propria estiver atacada, entao desconta o valor dela
			pontos_totais=pontos_totais+retorna_valor_peca(peca);		// se uma peca do inimigo estiver atacada, entao adiciona o valor dela

		if(posicao==1 || posicao==2) pontos=pontos_totais;	// os pontos a serem devolvidos acompanham os pontos totais somente nas primeiras
											// duas jogadas - isto ocorre, porque pode-se interromper a sequencia de batalha a qualquer
											// momento - porem isto traz uma pequena desvantagem o que e tratado abaixo
		na_vez=!na_vez;	// o outro jogador sera na vez

		mov_loc=amove.executa(pc,na_vez);	// ver os movimentos de resposta

		menor_pos=DUMMY;	// valores a nunca serem alcancados para pegar o menor valor sempre
		menor_valor=DUMMY;

		// o seguinte laco procura uma resposta com a peca do menor valor possivel tendo como base que um jogador vai sempre
		// tentar tomar com a peca menos valorosa para nao colocar pecas de alto valor em risco

		for(i=0;i<mov_loc.pontos_pos;i++)
		{
			if(mov_loc.x_dest[i] == loc_x && mov_loc.y_dest[i] == loc_y)	// o destino bateu?
			{
				peca=mov_loc.tipo[i];
				if(retorna_valor_peca(peca)<menor_valor)	// ver se o valor e o menor
				{
					menor_valor=retorna_valor_peca(peca);
					menor_pos=i;
				}
			}
		}

		// se nao achou-se nenhum movimento o que e possivel neste ponto por nao tratamento do ataque quando ha um xeque ou mate
		// entao nao sera feito nada de execucao neste ponto para nao travar (executar um movimento em posicao que nao existe!!)

		if(menor_pos!=DUMMY)	
			pc=execute_movimento(mov_loc.x_orig[menor_pos],mov_loc.y_orig[menor_pos],mov_loc.x_dest[menor_pos],mov_loc.y_dest[menor_pos],
				pc,mov_loc.especiais[menor_pos]); 
			else stop=TRUE;		// nao achou nenhum movimento entao?? PARE POR AQUI MESMO!

//		mostre_ascii(pc);

//		gotoxy(1,1);
//		printf("pontos: %i pontos totais: %i",pontos,pontos_totais);

//		io.espere_tecla();

	}

	if(pontos_totais>0) pontos=pontos+5;	// se ainda forcar o outra a interromper a cadeia
											// minuscula pontuacao somente para distinguir entre dois movimentos

	return pontos;
}

int analisador_central::vantagem(int pos, EPONTOS pt, PECAS pc)
//
//	calculo da vantagem ou desvantagem que um movimento traz:
//	VANTAGEM = pontuacao POSITIVA
//	DESVANTAGEM = pontuacao NEGATIVA
//	NEUTRAL = valor ZERO
//
//	pode ser calculado para QUALQUER movimento - porem movimentos para casas vazias nunca terao
//	vantagem aplicada por ai
//
//	o procedimento e principalmente importante pela questao se deve-se ou nao pegar uma peca do inimigo!!
//
//	trocas terao vantagem (pequena) aplicada artificialmente (para sair da neutralidade do 0 (zero) calculado nesta situacao)
//
{
	int pv, na_vez, peca_inicial;

	long int risc;

	BOOL vantagem_inicial;

//	console io;	// somente para teste
	
	na_vez=pt.cor[pos];	// pegar automaticamente quem esta na vez no inicio

	pv=0;		// pv=pontos vantagem - abreviacao para melhor leitura (menos extensa)

	peca_inicial=qualpeca(pt.x_dest[pos],pt.y_dest[pos],pc);	// retornar eventual peca do inimigo no local

	if(peca_inicial!=INATIVO)		// tinha uma peca la??
		pv=retorna_valor_peca(peca_inicial);	// afirmativo? entao eu vou contabilizar os pontos para mim!

	if(pv!=0) vantagem_inicial=TRUE; else vantagem_inicial=FALSE;	// ver se houve vanatgem inicialmente (para tratamento de trocas)

	//	gotoxy(0,0);

//	printf("xo:%i yo:%i xd:%i yd:%i pi:%i vi:%i pv0:%i",pt.x_orig[pos]+1,pt.y_orig[pos]+1,pt.x_dest[pos]+1,pt.y_dest[pos]+1,peca_inicial,vantagem_inicial,pv);

	pc=execute_movimento(pt.x_orig[pos],pt.y_orig[pos],pt.x_dest[pos],pt.y_dest[pos],pc,pt.especiais[pos]);	// ....executar o movimento teoricamente

//	mostre_ascii(pc);

//	gotoxy(1,1);

//	printf("NIVEL MACRO");

//	io.espere_tecla();

//	gotoxy(1,1);

//	printf("VANTAGEM perguntando risco de: %i/%i",pt.x_dest[pos],pt.y_dest[pos]);

//	io.espere_tecla();

	risc=risco(pt.x_dest[pos],pt.y_dest[pos],na_vez,pc);	// ...e entrar no merito de riscos resultantes do movimento!

	if(risc<0)
		pv=pv+risc;

//	printf(" risco cru:%i ",pv);

//	gotoxy(1,1);

//	printf("CALCULADO:%i peca inicial:%i             ",pv,peca_inicial);

//	io.espere_tecla();

	if(vantagem_inicial==FALSE && pv>0) pv=0;	// nao tinha peca no local inicialmente? entao pontos positivos do risco nao
												// interessam, pois ocupando uma posicao vazia, NAO ganha-se pontos (a nao ser
												// que o inimigo e um completo imbecil)

//	printf(" r2:%i ",pv);

//	gotoxy(1,1);

//	printf("DEVOLVIDO:%i                   ",pv);

//	io.espere_tecla();

	if((pv==0 || pv==-90) && vantagem_inicial) pv=900;		// se houve uma vantagem inicialmente, mas chegou-se ao 0 (zero) mesmo assim,
								// entao houve uma TROCA
								// conforme isto, pontuacao artificial - um pouco menos do que um peao ganho

//	printf(" final:%i                ",pv);

//	io.espere_tecla();

	return pv;		// retornar os pontos de vantagem calculados
}

EPONTOS analisador_central::ataque(EPONTOS pt, PECAS pc, int na_vez)
//
// Rotina para aumentar a agressividade de computador em caso de indecisao
//
// 
{
	int i, peca;

	for(i=0;i<pt.pontos_pos;i++)
	{
		if(pt.score[i]>=-900)	// sem patricionio de perda de figuras!
		{
			peca=qualpeca(pt.x_dest[i],pt.y_dest[i],pc);

			pt.score[i]=pt.score[i]+retorna_valor_peca(peca)/1000;
		}
	}

	return pt;
}

/*BOOL analisador_central::em_linha(int x1, int y1, int x2, int y2, int x3, int y3)
{

	int x_diff, y_diff, i;

	x_diff=x1-x2;
	y_diff=y1-y2;

	if(abs(x_diff)!=abs(y_diff))
		if(x_diff!=0 && y_diff!=0) return FALSE;

	if(x_diff>0) x_diff=1; else if(x_diff<0) x_diff=-1; else x_diff=0;
	if(y_diff>0) y_diff=1; else if(y_diff<0) y_diff=-1; else y_diff=0;

	for(i=0;i<8;i++)
	{
		if((x1+x_diff*i==x3 && y1+y_diff*i==y3) || 
			(x1-x_diff*i==x3 && y1+y_diff*i==y3))
			return TRUE;

	}	

	return FALSE;
}*/

EPONTOS analisador_central::anti_xeque(EPONTOS pt, PECAS pc, int na_vez)
//
//  rotina que coloca demerito nos movimentos que tem um possivel xeque como
//	consequencia - principalmente importante na finalizacao, mas tambem geralmente durante 
//	o jogo para evitar bloqueios reais!
//
//
{
	int i, j, rei_xx, rei_yy;

	rei_xx=INVALIDO;
	rei_yy=INVALIDO;

//	console io;

	EPONTOS movimentos2;

	PECAS pecas_teste, pecas_teste2;

	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente

		movimentos2=amove.executa(pecas_teste,!na_vez);

		for(j=0;j<32;j++)
		{
			if(pc.p[j].devolve_cor()==na_vez && pc.p[j].devolve_tipo()==REI)
			{
				rei_xx=pc.p[j].devolve_x();
				rei_yy=pc.p[j].devolve_y();
			}
		}

		for(j=0;j<movimentos2.pontos_pos;j++)
		{
			pecas_teste2=execute_movimento(movimentos2.x_orig[j],movimentos2.y_orig[j],movimentos2.x_dest[j],movimentos2.y_dest[j],pecas_teste,movimentos2.especiais[j]); // executar todos os movimentos possiveis teoricamente

			if(amove.atacado(rei_xx,rei_yy,na_vez,pecas_teste2))
			{
				//mostre_ascii(pecas_teste2);
				//gotoxy(0,0);
				//printf("xeque");
				//io.espere_tecla();
				//gotoxy(0,0);
				//printf("       ");
				pt.score[i]=pt.score[i]-20;
				j=movimentos2.pontos_pos;
			}
		}
	}

	return pt;
}

EPONTOS analisador_central::busca_xeque(EPONTOS pt, PECAS pc, int na_vez)
//
//  Da Xeque no Rei do inimigo - principalmente na finalizacao importante para ganhar tempo
//
{
	int i;

	PECAS pecas_teste;

	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente
		if(amove.atacado(rei_x[!na_vez],rei_y[!na_vez],!na_vez,pecas_teste))
			pt.score[i]=pt.score[i]+50;
	}
	return pt;
}

EPONTOS analisador_central::anti_abre_portas(EPONTOS pt, PECAS pc, int na_vez)
//
// Rotina para evitar que Monarch indiretamente abre possibilidades a execucao vantageosa
//
{
	if(debug) debug_output(ANTI_ABRE_PORTAS);
	int i, k;
//	console io;
	PECAS pecas_teste;
	EPONTOS movimentos2;
	int long vant, vant_max, ataques;
	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente
//			mostre_ascii(pecas_teste);

		vant_max=0;

		ataques=-1;

		movimentos2=amove.executa(pecas_teste,!na_vez);                  // a partir da nova posicao pegar os movimentos no nivel 2

		for(k=0;k<movimentos2.pontos_pos;k++)
		{
			if(qualpeca(movimentos2.x_dest[k],movimentos2.y_dest[k],pecas_teste)!=INATIVO)
			{
				if(pt.score[i]>0 && movimentos2.x_dest[k]==pt.x_dest[i] 
					&& movimentos2.y_dest[k]==pt.y_dest[i])
				{
					//gotoxy(0,0);
					//printf("local: %i-%i pt: %i",movimentos2.x_dest[k],movimentos2.y_dest[k],pt.score[i]);
					//io.espere_tecla();
				} else
				{
					vant=vantagem(k,movimentos2,pecas_teste);
					if(vant>=1000) ataques++;
					if(vant>vant_max) vant_max=vant;
				//mostre_ascii(pecas_teste);
				//gotoxy(0,0);
				//printf("at: %i %i -> %i %i",movimentos2.x_orig[k]+1,movimentos2.y_orig[k]+1,movimentos2.x_dest[k]+1,movimentos2.y_dest[k]+1);
				//io.espere_tecla();
				}
			}
		}
		if(vant_max<1000) vant_max=0;
		pt.score[i]=pt.score[i]-vant_max-ataques*5;	// se houver mais ataques, entao o caso fica um pouco mais grava (5 para diferenciar entre dois movimentos)
	}

	return pt;
}

EPONTOS analisador_central::defesa(EPONTOS pt, PECAS pc, int na_vez)
//
// Rotina do Analisador Central Versao III
//
{
	PECAS pecas_teste;

	//console io;

	long int k, j, exam_x, exam_y, bonus_inicial, peca;

	long int risco_x[33], risco_y[33], risco_valor[33], risco_pos, risc;

	for(j=0;j<33;j++)	// inicializacao do array de pontos
	{
		risco_x[j]=INVALIDO;
		risco_y[j]=INVALIDO;
		risco_valor[j]=INVALIDO;
	}

	risco_pos=0;	// posicao para escrita para a posicao 0

	for(k=0;k<32;k++)	// empilhar todos os riscos de deixar as pecas paradas
	{
		if(amove.atacado(pc.p[k].devolve_x(),pc.p[k].devolve_y(),na_vez,pc) &&
			pc.p[k].devolve_cor()==na_vez)
		{
			risco_x[risco_pos]=pc.p[k].devolve_x();
			risco_y[risco_pos]=pc.p[k].devolve_y();
			risco_valor[risco_pos]=risco(risco_x[risco_pos],risco_y[risco_pos],na_vez,pc);

//			gotoxy(1,1);

//			mostre_ascii(pc);

//			printf(" DEFESA perguntando risco de: %i/%i = %i      ",risco_x[risco_pos],risco_y[risco_pos],risco_valor[risco_pos]);

//			io.espere_tecla();

			risco_pos++;
		}
	}

	if(risco_pos>0)	// se houver algum risco (isto e, a lista nao estiver vazia)
	{

		for(k=0;k<pt.pontos_pos;k++)
		{
			bonus_inicial=0;
			peca=qualpeca(pt.x_dest[k],pt.y_dest[k],pc);
			if(peca!=INATIVO) bonus_inicial=retorna_valor_peca(peca);
				pecas_teste=execute_movimento(pt.x_orig[k],pt.y_orig[k],pt.x_dest[k],pt.y_dest[k],pc,pt.especiais[k]); // executar todos os movimentos possiveis teoricamente
//				mostre_ascii(pecas_teste);
				for(j=0;j<risco_pos;j++)
				{
					if(risco_valor[j]<0)
					{
						if(risco_x[j]==pt.x_orig[k] && risco_y[j]==pt.y_orig[k])
						{
							exam_x=pt.x_dest[k];
							exam_y=pt.y_dest[k];
						} else
						{
							exam_x=risco_x[j];
							exam_y=risco_y[j];
						}
						risc=risco(exam_x,exam_y,na_vez,pecas_teste);
						//gotoxy(0,0);
						//printf("xo:%i yo:%i xd:%i yd:%i rx:%i ry:%i ri:%i rf:%i",pt.x_orig[k]+1,pt.y_orig[k]+1,pt.x_dest[k]+1,pt.y_dest[k]+1,risco_x[j],risco_y[j],risco_valor[j],risc);						
						//pt.score[k]=pt.score[k]-risco_valor[j]+risc;	// metodo velho
						pt.score[k]=pt.score[k]+(bonus_inicial+risc)/10;		// para reforcar um pouco e distinguir os casos de somente "dar xeque" e evadir assim					// metodo novo
						//printf(" pont:%i              ",pt.score[k]);
						//io.espere_tecla();
					}
				}
				
		}
	}

	return pt;
}

EPONTOS analisador_central::desenvolvimento(EPONTOS pt, PECAS pc, int na_vez, int fase)
{
//	console io;

	int i, linha_peao, linha_cavalo;

	if(na_vez==BRANCO)
	{
		linha_peao=1;
		linha_cavalo=0;
	} else
	{
		linha_peao=6;
		linha_cavalo=7;
	}

	for(i=0;i<pt.pontos_pos;i++)	
	{
		
		if(pt.score[i]>=0)	// problemas? entao resolver primeiro!
		{
			if(pt.tipo[i]==CAVALO && (fase==ABERTURA || fase==BATALHA_CENTRAL))
			{
				if((pt.x_orig[i]==1 || pt.x_orig[i]==6) &&
					pt.y_orig[i]==linha_cavalo)
					pt.score[i]=pt.score[i]+15;
			} else
				if(pt.tipo[i]==PEAO && (fase==ABERTURA || fase==BATALHA_CENTRAL))
				{
					if(pt.x_orig[i]>1 && pt.x_orig[i]<6 &&
						pt.y_orig[i]==linha_peao)
						pt.score[i]=pt.score[i]+10;
					if(pt.x_orig[i]>2 && pt.x_orig[i]<5 &&
						pt.y_orig[i]==linha_peao)
						pt.score[i]=pt.score[i]+10;
				}
				else
					if(pt.tipo[i]==BISPO && (fase==ABERTURA || fase==BATALHA_CENTRAL))
					{
						if((pt.x_orig[i]==2 || pt.x_orig[i]==5) &&
							pt.y_orig[i]==linha_cavalo)
							pt.score[i]=pt.score[i]+5;
					}	


		}
		if(pt.tipo[i]!=RAINHA && pt.tipo[i]!=REI && fase!=FINALIZACAO)	// no final nao ha centro nem lado!
		{
			if(pt.x_dest[i]>1 && pt.x_dest[i]<6 &&
			pt.y_dest[i]>1 && pt.y_dest[i]<6)
				pt.score[i]=pt.score[i]+2;

			if(pt.cor[i]==BRANCO)
			{
				if(pt.y_dest[i]>2) pt.score[i]=pt.score[i]+1;
			}else
			{
				if(pt.y_dest[i]<5) pt.score[i]=pt.score[i]+1;	
			}
		}
		if(pt.tipo[i]==REI && abs(pt.x_orig[i]-pt.x_dest[i])==2)	// pequeno patrocionio para o roque
			pt.score[i]=pt.score[i]+1;
		
		if((fase==FINALIZACAO || fase==BATALHA_ESTRATEGICA)			// pequeno patrocionio para tirar as torres no final dos cantos
			&& pt.tipo[i]==TORRE && pt.y_orig[i]==linha_cavalo &&
			(pt.x_orig[i]==0 || pt.x_orig[i]==7))
			pt.score[i]=pt.score[i]+1;

	}

	return pt;
}

EPONTOS analisador_central::decisao(EPONTOS pt, int fase_local)
//
// Rotina do Analisador Central Versao III
//
{

	int i, max_score;

//	console io;

	max_score=pt.score[0];

	if(pt.pontos_pos==1) return pt;	// somente uma possibilidade??? Entao e essa!

	for(i=1;i<pt.pontos_pos;i++)
	{
		if(pt.score[i]>max_score)
			max_score=pt.score[i];
	}

//	gotoxy(0,0);
//	printf("%i",max_score);
//	io.espere_tecla();

	for(i=0;i<pt.pontos_pos;i++)
	{
//		gotoxy(0,0);
//		printf("%i ",i);
//		printf("%i %i %i %i %i",pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pt.score[i]);
//		io.espere_tecla();
		if(pt.score[i]<max_score)
		{
			pt=deleta_movimento(pt,i);
			i--;
		}
	}

//	gotoxy(1,1);
//	printf("TV:%i",teste_validade);
//	io.espere_tecla();

	return pt;
}

BOOL analisador_central::controle_linhas(int peca, int x, int y, PECAS pc)
//
// Rotina do Analisador Central Versao III
//
{
	int vertical, horizontal, diagonal1, diagonal2, i;
//	console io;

	vertical=0;
	horizontal=0;
	diagonal1=0;
	diagonal2=0;
	
	if(peca==PEAO || peca==CAVALO || peca==REI) return FALSE;

	for(i=1;i<8;i++)
	{
		if(qualpeca(x+i,y,pc)==INATIVO && amove.borda(x+i,y)==FALSE) horizontal++;
		if(qualpeca(x-i,y,pc)==INATIVO && amove.borda(x-i,y)==FALSE) horizontal++;
		if(qualpeca(x,y+i,pc)==INATIVO && amove.borda(x,y+i)==FALSE) vertical++;
		if(qualpeca(x,y-i,pc)==INATIVO && amove.borda(x,y-i)==FALSE) vertical++;

		if(qualpeca(x+i,y-i,pc)==INATIVO && amove.borda(x+i,y-i)==FALSE) diagonal1++;
		if(qualpeca(x-i,y+i,pc)==INATIVO && amove.borda(x-i,y+i)==FALSE) diagonal1++;
		if(qualpeca(x+i,y+i,pc)==INATIVO && amove.borda(x+i,y+i)==FALSE) diagonal2++;
		if(qualpeca(x-i,y-i,pc)==INATIVO && amove.borda(x-i,y-i)==FALSE) diagonal2++;
	}
	
//	gotoxy(20,50);
//	printf(" p:%i %i/%i h:%i v:%i d1:%i d2:%i",peca,x,y,horizontal,vertical,diagonal1,diagonal2);
//	io.espere_tecla();

//	gotoxy(0,0);
	if((peca==RAINHA || peca==TORRE) && (vertical>6 || horizontal>6)) return TRUE;

	if((peca==RAINHA || peca==BISPO) && (diagonal1>6 || diagonal2>6)) return TRUE;

//	io.espere_tecla();
	return FALSE;
}

BOOL analisador_central::proximidade_rei(int x, int y, PECAS pc, int na_vez)
//
// Rotina do Analisador Central Versao III
//
{
	int i, rei_x, rei_y;

	rei_x=INVALIDO;
	rei_y=INVALIDO;

	for(i=0;i<32;i++)
		if(pc.p[i].devolve_tipo()==REI && pc.p[i].devolve_cor()!=na_vez)
		{
			rei_x=pc.p[i].devolve_x();
			rei_y=pc.p[i].devolve_y();
		}

	if(rei_x!=INVALIDO)
		if(abs(x-rei_x)<2 && abs(y-rei_y)<2) return TRUE;

	return FALSE;
	
}

int analisador_central::define_fase(PECAS pc) // define a fase do jogo
//
// Descricao: Define a fase do jogo cfe. as figuras no tabuleiro
//                              (A definicao e feita de uma maneira rapida para nao
//                              atrapalhar o processamento em geral)
//
// (rotina testada 10.08.00)
//
{
	int pesadas, totais, i, fase;

	pesadas=0;      // figuras pesadas, isto e, que não sao peoes
	totais=0;       // figuras totais no tabuleiro

	for(i=0;i<32;i++)       // contagem
	{
		if(pc.p[i].devolve_tipo()!=INATIVO)
		{
			totais++;
			if(pc.p[i].devolve_tipo()!=PEAO)
				pesadas++;
		}
	}
	
	// definicao fase:
	//
	// 31 ou 32 figuras no tabuleiro    = abertura
	// 8-6 figuras pesadas no tabuleiro = batalha central
	// 4/5 figuras pesadas no tabuleiro = batalha estrategica

	// 3-0 figuras pesadas no tabuleiro = finalizacao

	if(totais>28) fase=ABERTURA; else
		if(pesadas>5) fase=BATALHA_CENTRAL; else
			if(pesadas>3) fase=BATALHA_ESTRATEGICA; else
				fase=FINALIZACAO;

	//
	//OUTPUT DEBUG
	//
	//cout << " DEFINICAO DE FASE\n\n";
	//cout << " PECAS TOTAIS: " << totais << "\n";
	//cout << " PECAS PESADAS: " << pesadas << "\n\n";
	//cout << " FASE: " << fase << "\n\n";
	//

	return fase;
}

EPONTOS analisador_central::deleta_movimento(EPONTOS m_in, int i)
{
	int j;
	j=m_in.pontos_pos-1;    // j no ultimo movimento

	if(j>0) // copiar o ultimo movimento da lista para a posicao a ser deletada
			// (somente se houver mais do que 1 movimento - senao deleta direto)
	{
		m_in.x_orig[i]=m_in.x_orig[j];          
		m_in.y_orig[i]=m_in.y_orig[j];  
		m_in.x_dest[i]=m_in.x_dest[j];  
		m_in.y_dest[i]=m_in.y_dest[j];          
		m_in.tipo[i]=m_in.tipo[j];      
		m_in.cor[i]=m_in.cor[j];
		m_in.especiais[i]=m_in.especiais[j];
		m_in.score[i]=m_in.score[j];
	}

	// deletar o ultimo movimento da lista a nivel de dados
	m_in.x_orig[j]=INATIVO;         
	m_in.y_orig[j]=INATIVO;
	m_in.x_dest[j]=INATIVO;
	m_in.y_dest[j]=INATIVO;
	m_in.score[j]=0;
	m_in.especiais[j]=0;

	// ponteiro do final da lista para tras
	m_in.pontos_pos--;

	// devolver lista pronta
	return m_in;      
}

void analisador_central::debug_output(int posicao)
{
	console io;
	gotoxy(50,14);
	printf("                    "); // deletar 20 (!!) posicoes
	gotoxy(50,14);
	switch(posicao)
	{
		case MATE_OFENSIVO_1:		printf("MATE OF. I");	return;
		case MATE_OFENSIVO_2:		printf("MATE OF. II");	return;
		case MATE_OFENSIVO_3:		printf("MATE OF. III");	return;
		case MATE_DEFENSIVO_1:		printf("MATE DEF. I");	return;
		case MATE_DEFENSIVO_2:		printf("MATE DEF. II");	return;
		case ANTI_EMPATE:			printf("ANTI EMPATE");	return;
		case EXECUCAO:				printf("EXECUCAO");		return;
		case ANTI_ATAQUE_DUPLO:		printf("ANTI ATQ. 2x"); return;
		case ANTI_BLOQUEIO:			printf("ANTI BLOQ.");	return;
		case ANTI_ABRE_PORTAS:		printf("ANTI ABR.PO."); return;
		case ATAQUE:				printf("ATAQUE");		return;
		case ATAQUE_DUPLO:			printf("ATAQUE_DUPLO");	return;
		case BLOQUEIO:				printf("BLOQUEIO");		return;
		case DEFESA:				printf("DEFESA");		return;
		case INFLUENCIA_CENTRAL:	printf("INF. CENTRAL"); return;
		case CONTROLE_LINHAS:		printf("CONTRL. LIN.");	return;
		case PROXIMIDADE_REI:		printf("PROX. REI");	return;
		case LIBERDADE_MOVIMENTO:	printf("LIB. MOV."); return;
	}
	io.espere_tecla();
}

int analisador_central::mate_ofensivo_em_1(EPONTOS pt, PECAS pc, int na_vez)
{
	// Descricao: Se houver um mate em 1, entao execute e termine a jogada
	// Algoritmo: Execute todos os movimentos possiveis teoricamente obtendo cada vez a posicao resultante e teste
	//                se a partir desta posicao o adversario nao pode fazer nenhum movimento (chamando "permitido" com um
	//                movimento dummy).
	// Implementacao basica: 30/09/00
	// Funcionamento:        02/10/00 
	// Teste:                02/10/00 - 15 posicoes s/ erro
	// Otimizacao: nao necessaria.
	// Colocada em Funcao:   15/10/00
	// Reteste (pre):		 15/10/00 - 1 posicao em ambiente de teste s/ erro

	// COMPORTAMENTE = devolucao do primeiro movimento achado para direta execucao

	PECAS pecas_teste;

	int i;

	if(debug) debug_output(MATE_OFENSIVO_1);

	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente
		if(amove.permitido(0,0,0,0,!na_vez,pecas_teste)==MATE)                                                                                         // e testar se existe uma posicao em qual o adversario nao
			return i;                                                                                                                              // pode reagir (MATE) - esta sera JA executada!!
	}

	return INVALIDO;
}

EPONTOS analisador_central::mate_ofensivo_em_2(EPONTOS pt, PECAS pc, int na_vez)
{
	// Descricao: Se houver um mate em 2, entao da uma pontuacao alta a este movimento a nivel 1
	// Algoritmo: Execute todos os movimentos possiveis a partir da posicao atual teoricamente e 
	//				a partir da nova posicao execute mais uma vez todos os movimentos PROPRIO possiveis,
	//				isto eu jogo teoricamente duas vezes e vejo se consigo dar mate assim
	// Implementacao basica: 15/10/00
	// Funcionamento:        15/10/10 
	// Teste:				 15/10/00 - duas posicoes em AT ok                
	// Otimizacao: ok. (testar antes do mate se o rei esta em Xeque)
	// Colocada em Funcao:   15/10/00

	// COMPORTAMENTE = devolucao do array de pontos modificado (com pontuacao gravada)

	int i,k;
	PECAS pecas_teste, pecas_teste2;
	EPONTOS movimentos2;

	if(debug) debug_output(MATE_OFENSIVO_2);
		
	for(i=0;i<pt.pontos_pos;i++)
	{
		if(pt.score[i]>-900)	// sem armadilhas!!
		{
			pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente
//			mostre_ascii(pecas_teste);

			movimentos2=amove.executa(pecas_teste,na_vez);                  // a partir da nova posicao pegar os movimentos no nivel 2
			for(k=0;k<movimentos2.pontos_pos;k++)
			{
				pecas_teste2=execute_movimento(movimentos2.x_orig[k],movimentos2.y_orig[k],movimentos2.x_dest[k],movimentos2.y_dest[k],pecas_teste,movimentos2.especiais[k]); // executar todos os movimentos possiveis teoricamente

//				mostre_ascii(pecas_teste2);

				if(amove.atacado(rei_x[!na_vez],rei_y[!na_vez],!na_vez,pecas_teste2))
				if(amove.permitido(0,0,0,0,!na_vez,pecas_teste2)==MATE)
				{
//					mostre_ascii(pecas_teste2);
					pt.score[i]=pt.score[i]+10000;
				}
			}
		}
	}

	return pt;
}

EPONTOS analisador_central::mate_ofensivo_em_3(EPONTOS pt, PECAS pc, int na_vez)
{
	// supostamente ok - achou pastor durante o jogo

	int i,k,l;

	//console io;

	PECAS pecas_teste, pecas_teste2, pecas_teste3;
	EPONTOS movimentos2, movimentos3;

	if(debug) debug_output(MATE_OFENSIVO_3);
		
	for(i=0;i<pt.pontos_pos;i++)
	{
		if(pt.score>=0) 
		{
			pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente
//			mostre_ascii(pecas_teste);

			movimentos2=amove.executa(pecas_teste,na_vez);                  // a partir da nova posicao pegar os movimentos no nivel 2
			for(k=0;k<movimentos2.pontos_pos;k++)
			{
				pecas_teste2=execute_movimento(movimentos2.x_orig[k],movimentos2.y_orig[k],movimentos2.x_dest[k],movimentos2.y_dest[k],pecas_teste,movimentos2.especiais[k]); // executar todos os movimentos possiveis teoricamente

//				mostre_ascii(pecas_teste2);

				movimentos3=amove.executa(pecas_teste2,na_vez);
				for(l=0;l<movimentos3.pontos_pos;l++)
				{
					pecas_teste3=execute_movimento(movimentos2.x_orig[l],movimentos3.y_orig[l],movimentos3.x_dest[l],movimentos3.y_dest[l],pecas_teste2,movimentos3.especiais[l]); // executar todos os movimentos possiveis teoricamente

//				mostre_ascii(pecas_teste2);

					if(amove.atacado(rei_x[!na_vez],rei_y[!na_vez],!na_vez,pecas_teste2))
					if(amove.permitido(0,0,0,0,!na_vez,pecas_teste3)==MATE)
					{
						//mostre_ascii(pecas_teste3);
						//io.espere_tecla();
						pt.score[i]=pt.score[i]+800;	// pontuacao cuidadosa pois muito pode acontecer no caminho!
					}
				}
			}
		}
	}
	return pt;
}

EPONTOS analisador_central::mate_defensivo_em_1(EPONTOS pt, PECAS pc, int na_vez)
{
	// Descricao: Se houver a possibilidade do adversario fazer um mate em 1, entao
	//            tire os movimentos que dao margem a isto da lista. Se todos os movimentos
	//              possibilitam o mate, entao nao faca nada (anti-trava).
	// Implementacao basica:        30/09/00, 02/10/00
	// Funcionamento: 
	// Teste:                       duas posicoes faceis funcionaram, mas pastor nao (02/10/00)
	// Otimizacao: teste do xeque "no braco", isto e fornecendo coordenadas obtidas somente 1 vez por movimento amigo
	//                 teste do xeque antes de deixar entrar no "permitido" para evitar a repetida execucao do analisador de movimentos!!
	//         otimizacao OK (02/10/00)

	EPONTOS movimentos_inimigo, copia_pontos;

	int rei_xx, rei_yy, i, k, j;

	PECAS pecas_teste, pecas_teste2;

	if(debug) debug_output(MATE_DEFENSIVO_1);
	
	//      mostre_pontos(*movimentos);

	copia_pontos=pt;
		
	for(i=0;i<copia_pontos.pontos_pos;i++)
	{
	//              gotoxy(50,12);
	//              printf(" i: %i ",i);
	//              io.espere_tecla();
		pecas_teste=execute_movimento(copia_pontos.x_orig[i],copia_pontos.y_orig[i],copia_pontos.x_dest[i],copia_pontos.y_dest[i],pc,copia_pontos.especiais[i]);                // executar todos os movimentos teoricamente
		movimentos_inimigo=amove.executa(pecas_teste,!na_vez);                  // a partir da nova posicao pegar os movimentos possiveis do adversario
		
		for(k=0;k<32;k++)       // pegar as coordenadas do rei amigo, pois na execucao dos movimentos do adversario na irao mudar (e "testa_xeque" pega a posicao CADA VEZ que for executada)
		{
			if(pecas_teste.p[k].devolve_tipo()==REI && pecas_teste.p[k].devolve_cor()==na_vez)
			{
				rei_xx=pecas_teste.p[k].devolve_x();
				rei_yy=pecas_teste.p[k].devolve_y();
				k=32;           // achou o rei - entao nao teste mais
			}
		}

	//              gotoxy(50,10);
	//              printf(" rei: %i %i",rei_x,rei_y);
	//          io.espere_tecla();
		
		for(j=0;j<movimentos_inimigo.pontos_pos;j++)    // executar todos os movimentos do inimigo teoricamente
		{
			pecas_teste2=execute_movimento(movimentos_inimigo.x_orig[j],movimentos_inimigo.y_orig[j],movimentos_inimigo.x_dest[j],
			movimentos_inimigo.y_dest[j],pecas_teste,movimentos_inimigo.especiais[j]);               
				if(amove.atacado(rei_xx,rei_yy,na_vez,pecas_teste2))      // se o rei amigo estiver atacado
			if(amove.permitido(0,0,0,0,na_vez,pecas_teste2)==MATE)  // entao se nao ha mais movimentos desta posicao
			{
//                                      gotoxy(50,10);
//                                      printf("entrei!!");
//                                      io.espere_tecla();
//                                      mostre_pontos(copia_pontos);
				copia_pontos=deleta_movimento(copia_pontos,i);  // deleta o movimento de origem
				j=movimentos_inimigo.pontos_pos;        // nao testa mais movimentos do inimigo, pois ja achou
				i--;                                            // e trata da delecao do movimento (troca da ultima posicao)
//                                      mostre_pontos(copia_pontos);
			}
		}
	}

	if(copia_pontos.pontos_pos>0) pt=copia_pontos;	// anti-trava
//              mostre_pontos(*movimentos);

	return pt;
}

EPONTOS analisador_central::mate_defensivo_em_2(EPONTOS pt, PECAS pc, int na_vez)
{
	
	// Descricao: Se houver a possibilidade do adversario fazer um mate em 1, entao
	//            tire os movimentos que dao margem a isto da lista. Se todos os movimentos
	//              possibilitam o mate, entao nao faca nada (anti-trava).
	// Implementacao basica:        30/09/00, 02/10/00
	// Funcionamento: 
	// Teste:                       duas posicoes faceis funcionaram, mas pastor nao (02/10/00)
	// Otimizacao: teste do xeque "no braco", isto e fornecendo coordenadas obtidas somente 1 vez por movimento amigo
	//                 teste do xeque antes de deixar entrar no "permitido" para evitar a repetida execucao do analisador de movimentos!!
	//         otimizacao OK (02/10/00)
	//			erro corrigido - achou 3 posicoes e se defendeu

	EPONTOS movimentos_inimigo, movimentos_inimigo2, copia_pontos;

	int rei_xx, rei_yy, i, k, j, l;

//	console io;

	PECAS pecas_teste, pecas_teste2, pecas_teste3;

	if(debug) debug_output(MATE_DEFENSIVO_2);
	
	//      mostre_pontos(*movimentos);

	copia_pontos=pt;
		
	for(i=0;i<copia_pontos.pontos_pos;i++)
	{
	//              gotoxy(50,12);
	//              printf(" i: %i ",i);
	//              io.espere_tecla();
		pecas_teste=execute_movimento(copia_pontos.x_orig[i],copia_pontos.y_orig[i],copia_pontos.x_dest[i],copia_pontos.y_dest[i],pc,copia_pontos.especiais[i]);                // executar todos os movimentos teoricamente
		movimentos_inimigo=amove.executa(pecas_teste,!na_vez);                  // a partir da nova posicao pegar os movimentos possiveis do adversario
		
		for(k=0;k<32;k++)       // pegar as coordenadas do rei amigo, pois na execucao dos movimentos do adversario na irao mudar (e "testa_xeque" pega a posicao CADA VEZ que for executada)
		{
			if(pecas_teste.p[k].devolve_tipo()==REI && pecas_teste.p[k].devolve_cor()==na_vez)
			{
				rei_xx=pecas_teste.p[k].devolve_x();
				rei_yy=pecas_teste.p[k].devolve_y();
				k=32;           // achou o rei - entao nao teste mais
			}
		}

	//              gotoxy(50,10);
	//              printf(" rei: %i %i",rei_x,rei_y);
	//          io.espere_tecla();
		
		for(j=0;j<movimentos_inimigo.pontos_pos;j++)    // executar todos os movimentos do inimigo teoricamente
		{
			pecas_teste2=execute_movimento(movimentos_inimigo.x_orig[j],movimentos_inimigo.y_orig[j],movimentos_inimigo.x_dest[j],
			movimentos_inimigo.y_dest[j],pecas_teste,movimentos_inimigo.especiais[j]);               

			movimentos_inimigo2=amove.executa(pecas_teste2,!na_vez);

			for(l=0;l<movimentos_inimigo2.pontos_pos;l++)
			{
				pecas_teste3=execute_movimento(movimentos_inimigo2.x_orig[l],movimentos_inimigo2.y_orig[l],movimentos_inimigo2.x_dest[l],
				movimentos_inimigo2.y_dest[l],pecas_teste2,movimentos_inimigo2.especiais[l]);               
	
				
				if(amove.atacado(rei_xx,rei_yy,na_vez,pecas_teste3))      // se o rei amigo estiver atacado
				if(amove.permitido(0,0,0,0,na_vez,pecas_teste3)==MATE)  // entao se nao ha mais movimentos desta posicao
				{
	//					mostre_ascii(pecas_teste3);
	//					io.espere_tecla();
//
  //                                    gotoxy(50,10);
    //                                  printf("entrei!!");
      //                                io.espere_tecla();
        //                              mostre_pontos(copia_pontos);
					copia_pontos=deleta_movimento(copia_pontos,i);  // deleta o movimento de origem
					j=movimentos_inimigo.pontos_pos;        // nao testa mais movimentos do inimigo, pois ja achou
					l=movimentos_inimigo2.pontos_pos;
					i--;                                            // e trata da delecao do movimento (troca da ultima posicao)
  //                                    mostre_pontos(copia_pontos);
				}
			}
		}
	}

	if(copia_pontos.pontos_pos>0) pt=copia_pontos;	// anti-trava
//              mostre_pontos(*movimentos);
	return pt;
}

EPONTOS analisador_central::anti_empate(EPONTOS pt,PECAS pc,int na_vez)
{
	
	// Descricao: Se houver movimentos na lista produzindo um empate em 1, entao tira estes
	//            movimentos da lista. Se somente tiver movimentos produzindo empate, entao
	//            nao faca nada (anti-trava).
	// Implementacao basica:        30/09/00
	// Funcionamento: 
	// Teste:

	EPONTOS copia_pontos;

	PECAS pecas_teste;

	int i;

	if(debug) debug_output(ANTI_EMPATE);

	copia_pontos=pt;

	for(i=0;i<copia_pontos.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(copia_pontos.x_orig[i],copia_pontos.y_orig[i],copia_pontos.x_dest[i],copia_pontos.y_dest[i],pc,copia_pontos.especiais[i]);                
		if(amove.permitido(0,0,0,0,!na_vez,pecas_teste)==EMPATE)
		{
			copia_pontos=deleta_movimento(copia_pontos,i);
			i--;
		}
	}

	if(copia_pontos.pontos_pos>0) pt=copia_pontos;	// anti-trava

	return pt;
}

EPONTOS analisador_central::anti_ataque(EPONTOS pt, PECAS pc, int na_vez)
{
	int vt, i;

	EPONTOS copia_pontos;

	if(debug) debug_output(EXECUCAO);

	copia_pontos=pt;

	for(i=0;i<copia_pontos.pontos_pos;i++)
	{
		vt=vantagem(i,copia_pontos,pc);

		if(vt<0)
		{
			copia_pontos=deleta_movimento(copia_pontos,i);
			i--;
		} else 
				copia_pontos.score[i]=copia_pontos.score[i]+vt;
	}

	if(copia_pontos.pontos_pos>0) pt=copia_pontos;   // anti-trava

	return pt;
}

EPONTOS analisador_central::ataque_duplo(EPONTOS pt, PECAS pc, int na_vez)
//
//  testa, se existe a possibilidade de criar um ataque duplo, seja garfo ou outra construcao
//
//	dois erros corrigidos em caixa branca (16/10/00)
//
{
	int i;

//	console io;

	long int buffer_ataque, nivel_atual;

	PECAS pecas_teste;

	EPONTOS movimentos2;

	nivel_atual=retorna_ataque_multiplo(pt,pc,na_vez);

	for(i=0;i<pt.pontos_pos;i++)
	{
		if(pt.score[i]>-500)	// movimentos com real perda de peca constatada ou troca NAO
		{
			pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente

			movimentos2=amove.executa(pecas_teste,na_vez);

			buffer_ataque=retorna_ataque_multiplo(movimentos2,pecas_teste,na_vez);

//		mostre_ascii(pecas_teste);
//		gotoxy(0,0);
//		printf("xo:%i yo:%i xd:%i yd:%i sc:%i bu:%i",pt.x_orig[i]+1,pt.y_orig[i]+1,pt.x_dest[i]+1,pt.y_dest[i]+1,pt.score[i],buffer_ataque);
//		io.espere_tecla();
//		gotoxy(0,0);
//		printf("                                                                            ");

			if(buffer_ataque!=INVALIDO && buffer_ataque>nivel_atual)
			{
				pt.score[i]=pt.score[i]+buffer_ataque-700-nivel_atual;
//			mostre_ascii(pecas_teste);
//			gotoxy(0,0);
//			printf("xo:%i yo:%i xd:%i yd:%i sc:%i bu:%i",pt.x_orig[i]+1,pt.y_orig[i]+1,pt.x_dest[i]+1,pt.y_dest[i]+1,pt.score[i],buffer_ataque);
//			io.espere_tecla();
//			gotoxy(0,0);
//			printf("                                                                            ");
			}
		}

	}
	return pt;
}

int analisador_central::conta_ataques(PECAS pc, int na_vez)
{
	int i, atacados;

	atacados=0;

	for(i=0;i<32;i++)
		if(amove.atacado(pc.p[i].devolve_x(),pc.p[i].devolve_y(),na_vez,pc))
			atacados++;

	return atacados;
}

EPONTOS analisador_central::anti_ataque_duplo_completo(EPONTOS pt, PECAS pc, int na_vez)
{
	//
	//	funcao completa para evitar ataques duplos - para analisador mais forte
	//
	int i, j;

	//console io;

	long int buffer_ataque, nivel_atual;

	PECAS pecas_teste, pecas_teste2;

	EPONTOS movimentos2, movimentos3;

	nivel_atual=retorna_ataque_multiplo(pt,pc,na_vez);

	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente

		movimentos2=amove.executa(pecas_teste,!na_vez);

		for(j=0;j<movimentos2.pontos_pos;j++)
		{
			if(amove.atacado(movimentos2.x_dest[j],movimentos2.y_dest[j],!na_vez,pecas_teste)==FALSE)
			{
				pecas_teste2=execute_movimento(movimentos2.x_orig[j],movimentos2.y_orig[j],movimentos2.x_dest[j],movimentos2.y_dest[j],pecas_teste,movimentos2.especiais[j]); // executar todos os movimentos possiveis teoricamente

				movimentos3=amove.executa(pecas_teste2,!na_vez);

	//		mostre_ascii(pecas_teste2);

				buffer_ataque=retorna_ataque_multiplo(movimentos3,pecas_teste2,!na_vez);

			
				if(buffer_ataque!=INVALIDO && buffer_ataque>nivel_atual)
				{
					pt.score[i]=pt.score[i]-buffer_ataque+701+nivel_atual;
			
	//		mostre_ascii(pecas_teste2);
	//		gotoxy(0,0);
	//		printf("xo:%i yo:%i xd:%i yd:%i sc:%i bu:%i",pt.x_orig[i]+1,pt.y_orig[i]+1,pt.x_dest[i]+1,pt.y_dest[i]+1,pt.score[i],buffer_ataque);
	//		io.espere_tecla();
	//		gotoxy(0,0);
	//		printf("                                                                            ");
			
				}
			}

		}	

	}
	return pt;
}

EPONTOS analisador_central::anti_ataque_duplo(EPONTOS pt, PECAS pc, int na_vez)
{
	//
	//	funcao normal otimizado somente analisando os casos comuns (peao e cavalo)
	//
	int i, j;

	//console io;

	long int buffer_ataque, nivel_atual;

	PECAS pecas_teste, pecas_teste2;

	EPONTOS movimentos2, movimentos3;

	nivel_atual=retorna_ataque_multiplo(pt,pc,na_vez);

	for(i=0;i<pt.pontos_pos;i++)
	{
		pecas_teste=execute_movimento(pt.x_orig[i],pt.y_orig[i],pt.x_dest[i],pt.y_dest[i],pc,pt.especiais[i]); // executar todos os movimentos possiveis teoricamente

		movimentos2=amove.executa(pecas_teste,!na_vez);

		for(j=0;j<movimentos2.pontos_pos;j++)
		{
			if(amove.atacado(movimentos2.x_dest[j],movimentos2.y_dest[j],!na_vez,pecas_teste)==FALSE)
			{

				pecas_teste2=execute_movimento(movimentos2.x_orig[j],movimentos2.y_orig[j],movimentos2.x_dest[j],movimentos2.y_dest[j],pecas_teste,movimentos2.especiais[j]); // executar todos os movimentos possiveis teoricamente

				if(movimentos2.tipo[j]==CAVALO || movimentos2.tipo[j]==PEAO)	// os mais comuns - pena que mais o tempo de processamento nao permite!!
				{
					movimentos3=amove.executa(pecas_teste2,!na_vez);

//				mostre_ascii(pecas_teste2);

					buffer_ataque=retorna_ataque_multiplo(movimentos3,pecas_teste2,!na_vez);

				
					if(buffer_ataque!=INVALIDO && buffer_ataque>nivel_atual)
					{
						pt.score[i]=pt.score[i]-buffer_ataque+701+nivel_atual;
//			mostre_ascii(pecas_teste2);
//			gotoxy(0,0);
//			printf("xo:%i yo:%i xd:%i yd:%i sc:%i bu:%i",pt.x_orig[i]+1,pt.y_orig[i]+1,pt.x_dest[i]+1,pt.y_dest[i]+1,pt.score[i],buffer_ataque);
//			io.espere_tecla();
//			gotoxy(0,0);
//			printf("                                                                            ");
					}
				}
			}

		}	

	}
	return pt;
}

int analisador_central::maior_movimento(EPONTOS pt)
{
	int i;
	long int max;
	max=-999999;

	for(i=0;i<pt.pontos_pos;i++)
		if(pt.score[i]>max) max=pt.score[i];

	return max;
}

////////////////////////////////////////////////////////////
// MONARCH - gerenciador do analisador central verão 3.0  //
//           rotina o mais iterativo possivel para evitar //
//           problemas na performance                     //
//                                                        //
// Rotina: calcule melhor movimento                       //
////////////////////////////////////////////////////////////

int analisador_central::calcule_melhor_movimento(int na_vez, PECAS pc, EPONTOS *movimentos)
{

	PECAS pecas_teste;

	EPONTOS copia_pontos, movimentos2;
	char ch;

	console io;

	int i, fase, liberdade_atual, resultado;

//	gotoxy(0,0);
//	printf("pc1:%i",pc.ataque);
//	io.espere_tecla();

	liberdade_atual=movimentos->pontos_pos;

	debug=FALSE;

	fase=define_fase(pc);	// definir a fase do jogo

	pega_posicoes_reis(pc);	// pegar as posicoes atuais dos reis para otimizar analise

	for(i=0;i<movimentos->pontos_pos;i++) movimentos->score[i]=0;	// inicializar array de pontos por seguranca


	// ANALISADORES PRIMEIRA LINHA - SET BASICO:
	//
	// este set sera chamado sempre


	// MATE OFENSIVO EM 1 - utltrapassa TODOS e nao importa qual movimento e, pois e VITORIA

	if(algo[MATE_OFENSIVO_1]==LIGADO)
	{
		if(debug) debug_output(MATE_OFENSIVO_1);

		resultado=mate_ofensivo_em_1(*movimentos,pc,na_vez);
			if(resultado!=INVALIDO) return resultado;
	}

	//mostre_pontos(*movimentos);

	
	
	
	// MATE DEFENSIVO EM 1 - deletar os respetivos movimentos da lista de pontos

	if(algo[MATE_DEFENSIVO_1]==LIGADO)
	{
		if(debug) debug_output(MATE_DEFENSIVO_1);

		*movimentos=mate_defensivo_em_1(*movimentos,pc,na_vez);	
	}

	
	
	
	// ANTI EMPATE - deleta os movimentos que causam empate em 1 da lista

	if(algo[ANTI_EMPATE]==LIGADO)
	{
		if(debug) debug_output(ANTI_EMPATE);

		*movimentos=anti_empate(*movimentos,pc,na_vez);
	}

	

	// EXECUCAO - ve se um movimento e vantageoso ou e por dentro de um ataque 
	//            no primeiro caso o movimento recebera ponutacao no segundo caso
	//            ele sera deletado
	
	if(algo[EXECUCAO]==LIGADO)
	{
		if(debug) debug_output(EXECUCAO);

		*movimentos=anti_ataque(*movimentos,pc,na_vez);
	}

	
	
	// ANTI ABRE PORTAS - procedimento defensivo 1 - ver se existe uma resposta maligna a um movimento
	
	if(algo[ANTI_ABRE_PORTAS]==LIGADO)
	{
		if(debug) debug_output(ANTI_ABRE_PORTAS);

		*movimentos=anti_abre_portas(*movimentos,pc,na_vez);
	}



	// DEFESA - procedimento defensivo 2 vendo todos os ataques e vendo se ha como escapar
	//          complementa o anterior com uma pequeno pontuacao para ele nao dar Xeque sempre...

	if(algo[DEFESA]==LIGADO)
	{
		if(debug) debug_output(DEFESA);

		*movimentos=defesa(*movimentos,pc,na_vez);
	}	

	// DESENVOLVIMENTO - analisador para garantir uma abertura a posicao boa no comeco

	if(algo[INFLUENCIA_CENTRAL]==LIGADO)
	{
		if(debug) debug_output(INFLUENCIA_CENTRAL);

		*movimentos=desenvolvimento(*movimentos,pc,na_vez,fase);
	}

	// ANALISADORES PRIMEIRA LINHA - set opcional
	//
	// para evitar desinteresse em trocas a um certo ponto os analisadores a seguir somente
	// serao chamados se o movimento anterior nao foi que o adversario retirou uma peca

	if(pc.ataque==FALSE)	
	{

		// MATE DEFENSIVO EM 2 - deletar os respetivos movimentos da lista de pontos
		// se defende contra mate em 2 lances

		
		// ANTI ATAQUE DUPLO - ve os ataques duplos de peao e cavalo (garfos), e pontua um pouco mais baixo que a execucao

		if(algo[ANTI_ATAQUE_DUPLO]==LIGADO)
		{
			if(debug) debug_output(ANTI_ATAQUE_DUPLO);

			if(player==1) *movimentos=anti_ataque_duplo_completo(*movimentos,pc,na_vez); else	// somente no modo standard 2 faz-se analise completa
			*movimentos=anti_ataque_duplo(*movimentos,pc,na_vez);
		}

		if(algo[MATE_DEFENSIVO_2]==LIGADO)
		{

			if(debug) debug_output(MATE_DEFENSIVO_2);

			*movimentos=mate_defensivo_em_2(*movimentos,pc,na_vez);	
		}



		// as seguintes rotinas buscam o mate, mas NAO na abertura que e ma estilo

		if(fase!=ABERTURA)	// para nao dar margem a aberturas "lixo" (veja "pastor")
		{


			// MATE OFENSIVO 2 - busca o mate ofensivo em 2 e pontua altamente

			if(algo[MATE_OFENSIVO_2]==LIGADO)
			{
				if(debug) debug_output(MATE_OFENSIVO_2);

				*movimentos=mate_ofensivo_em_2(*movimentos,pc,na_vez);
			}


			// MATE OFENSIVO 3 - busca o mate ofensivo em 3 e atribui uma pontuacao

			if(algo[MATE_OFENSIVO_3]==LIGADO)
			{
				if(debug) debug_output(MATE_OFENSIVO_3);

				*movimentos=mate_ofensivo_em_3(*movimentos,pc,na_vez);
			}
		}



		// os seguintes analisadores serao utilizados mais pelo fim do jogo para
		// ganhar efetivamente

		if(fase==FINALIZACAO || fase==BATALHA_ESTRATEGICA)
		{



			// ANTI XEQUE - evitar na medida do possivel movimentos que o adversario
			// pode dar Xeque na proxima

			if(algo[ANTI_BLOQUEIO]==LIGADO)
			{

				if(debug) debug_output(ANTI_BLOQUEIO);

				*movimentos=anti_xeque(*movimentos,pc,na_vez);
			}



			// XEQUE - busca "apertar" o adversario dando Xeque de vez em quando

			if(algo[BLOQUEIO]==LIGADO)
			{
				if(debug) debug_output(BLOQUEIO);

				*movimentos=busca_xeque(*movimentos,pc,na_vez);
			}


		}




		// achou um movimento bom ate agora?? 

		if(maior_movimento(*movimentos)<1000 &&
			maior_movimento(*movimentos)>0)	// somente fazer mais analises se nao se achou nada realmente bom ate agora e nao
												// tiver no prego total
		{


			// ATAQUE DUPLO - busca atacar duas pecas ao mesmo tempo

			if(algo[ATAQUE_DUPLO]==LIGADO)
			{
				if(debug) debug_output(ATAQUE_DUPLO);

				*movimentos=ataque_duplo(*movimentos,pc,na_vez);
			}
		}

		if(maior_movimento(*movimentos)<1000)	// em caso de problemas na analise ou total desespero ajudar a decidir
		{

			// ATAQUE - somente da uma apertada no inimigo atacando a peca de maior valor (mesmo
			// estando protegida)

			if(algo[ATAQUE]==LIGADO)
			{
				if(debug) debug_output(ATAQUE);

				*movimentos=ataque(*movimentos,pc,na_vez);
			}

		}
	}

	ch='X';

	//gotoxy(50,14);
	//printf("Debug? (d)      ");
	//ch=getch();

	if(ch=='d') mostre_pontos(*movimentos);


	// FIM ANALISADORES PRIMEIRA LINHA - PRIMEIRO CUT OFF

	*movimentos=decisao(*movimentos,fase);	// reduzir ao numero de melhores_movimentos

	if(ch=='d') 
	{
		mostre_pontos(*movimentos);
		for(i=0;i<movimentos->pontos_pos;i++)
		{
			copia_pontos=*movimentos;
			pecas_teste=execute_movimento(copia_pontos.x_orig[i],copia_pontos.y_orig[i],copia_pontos.x_dest[i],copia_pontos.y_dest[i],pc,copia_pontos.especiais[i]);                
			mostre_ascii(pecas_teste);
			io.espere_tecla();
		}
	}

	io.limpa_fundo();

	// SE A PONTUACAO JA E SUFICIENTE PARA TER ACHADO UM MELHOR MOVIMENTO, ENTAO TERMINA AQUI,
	// SENAO ENTRE EM

	// ANALISADORES SEGUNDA LINHA - para decidir entre varios movimentos com a mesmo pontuacao

	if(movimentos->pontos_pos>1)	// ja achou o melhor? nao, entao aplica analisadores
									// de segunda ordem
	{


		// LIBERDADE MOVIMENTO - achar o movimento dando mais liberdade posterior

		if(algo[LIBERDADE_MOVIMENTO]==LIGADO)
		{

			if(debug) debug_output(LIBERDADE_MOVIMENTO);

			for(i=0;i<movimentos->pontos_pos;i++)
			{

				pecas_teste=execute_movimento(movimentos->x_orig[i],movimentos->y_orig[i],movimentos->x_dest[i],movimentos->y_dest[i],pc,movimentos->especiais[i]);                
				movimentos2=amove.executa(pecas_teste,na_vez);
				if(movimentos2.pontos_pos>liberdade_atual) 
					movimentos->score[i]=movimentos->score[i]+(movimentos2.pontos_pos-liberdade_atual)*2;
			}
		}

		if(fase!=ABERTURA && fase!=BATALHA_CENTRAL)	// rotinas mais para a finalizacao
		{


			// CONTROLE LINHAS - buscar controlar linhas no final do jogo

			if(algo[CONTROLE_LINHAS]==LIGADO)
			{

				if(debug) debug_output(CONTROLE_LINHAS);

				for(i=0;i<movimentos->pontos_pos;i++)
				{
					if(controle_linhas(movimentos->tipo[i],movimentos->x_orig[i],movimentos->y_orig[i],pc)==FALSE &&
						controle_linhas(movimentos->tipo[i],movimentos->x_dest[i],movimentos->y_dest[i],pc)==TRUE)
						movimentos->score[i]=movimentos->score[i]+300;
				}
			}



			// PROXIMIDADE REI - se aproximar do rei do inimigo na fase final

			if(algo[PROXIMIDADE_REI]==LIGADO)
			{

				if(debug) debug_output(PROXIMIDADE_REI);
			
				for(i=0;i<movimentos->pontos_pos;i++)
				{
					if(proximidade_rei(movimentos->x_orig[i],movimentos->y_orig[i],pc,na_vez)==FALSE &&
						proximidade_rei(movimentos->x_dest[i],movimentos->y_dest[i],pc,na_vez)==TRUE)
						movimentos->score[i]=movimentos->score[i]+200;
				}
			}

		}

		// FIM ANALISADORES SEGUNDA LINHA - SEGUNDO CUT OFF

		*movimentos=decisao(*movimentos,fase);	// reduzir ao numero de melhores_movimentos novamente

		if(ch=='d') mostre_pontos(*movimentos);
	}

	

	// RANDOMIZADOR - randomizar os movimentos restantes

	i=(movimentos->pontos_pos*rand())/RAND_MAX; // randomizador integer

	//      mostre_pontos(*movimentos);

	//      printf(" mp: %i ",melhor.pos);
	//      io.espere_tecla();
	//      io.espere_tecla();


	return i;
}

///////////////////////////////////////////////////////
// Classe: COMPUTADOR - Definicao                    //
///////////////////////////////////////////////////////

// OBS.: subclasse de tabuleiro

class computador:public tabuleiro // rotinas ligadas ao computador jogando
{
	analisador_movimento amove;
	analisador_mate amate;
	analisador_central actrl;
public:
	PECAS jogada(int,PECAS);
};

// Classe: COMPUTADOR - Metodos                

PECAS computador::jogada(int na_vez, PECAS pc)  // rotina de jogado do computador - inclusive jogadores simulados!
{
	int i, exec;
	console io;
	EPONTOS possibilidades;

	io.init_frases();

	possibilidades=amove.executa(pc,na_vez);

	io.limpa_direita_tabuleiro();

	for(i=0;i<18;i++) // ligar todos os analisadores por default
		algo[i]=LIGADO;

	algo[MATE_DEFENSIVO_2]=DESLIGADO;	// procedimentos reservados a nivel 2
	algo[MATE_OFENSIVO_3]=DESLIGADO;

	gotoxy(50,8);

	printf("%s%s",frase.strg[lingua][57],frase.strg[lingua][58]);   // na vez computador
	gotoxy(50,10);

	printf("%s",frase.strg[lingua][61]);

	if(na_vez==BRANCO) 
	{
		setcolor( FOREGROUND_YELLOW | BACKGROUND_BLUE );
		printf("%s",frase.strg[lingua][62]); 
	}else   // coloca cor
	{
		setcolor( FOREGROUND_LIGHTPURPLE | BACKGROUND_BLUE );
		printf("%s",frase.strg[lingua][63]);
	}

	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );

	io.limpa_fundo();

	gotoxy(10,23);
	printf(frase.strg[lingua][41+player]);  // nome do jogador simulado

	gotoxy(50,14);
	printf(frase.strg[lingua][60]);	// pensando ...

	switch(player)
	{
				// modo normal, tudo que seja standard ligado:

		case 0: exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades); break;        // modo normal

				// modo mais forte, tudo ligado:

		case 1: algo[MATE_DEFENSIVO_2]=LIGADO;
				algo[MATE_OFENSIVO_3]=LIGADO;
				exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades); break;        // modo forte
		
		// pessoa de 48 anos (mais ou menos experiente) - jogador simulado 1
		
		case 2: algo[ANTI_ATAQUE_DUPLO]=DESLIGADO;
				algo[BLOQUEIO]=DESLIGADO;
				algo[ANTI_BLOQUEIO]=DESLIGADO;
				algo[LIBERDADE_MOVIMENTO]=DESLIGADO;
				algo[CONTROLE_LINHAS]=DESLIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);     // pensamento nao muito profundo 
			  break;

		// pessoa de 30 anos (conhecendo bastante) - jogador simulado 2

		case 3: algo[ANTI_ATAQUE_DUPLO]=DESLIGADO; 
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);
			  break;

		// pessoa de 25 anos (iniciante) - jogador simulado 3

		case 4: algo[ANTI_ATAQUE_DUPLO]=DESLIGADO;
				algo[ATAQUE_DUPLO]=DESLIGADO;
			    algo[MATE_DEFENSIVO_1]=DESLIGADO;
				algo[MATE_OFENSIVO_2]=DESLIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);
			  break;

		// pessoa de 59 anos (louca) - jogador simulado 4

		case 5: algo[INFLUENCIA_CENTRAL]=DESLIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);
			  break;

		// pessoa de 43 anos (nervosa) - jogador simulado 5

				
		case 6: algo[MATE_DEFENSIVO_2]=DESLIGADO;
				algo[ANTI_ATAQUE_DUPLO]=DESLIGADO;
				algo[ANTI_EMPATE]=DESLIGADO;
				exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);       // conhece tudo, mas nao tem profundidade de pens.
		    		break;

		// pessoa de 19 anos (conhecendo bastante) - jogador simulado 6;

		case 7: algo[MATE_DEFENSIVO_2]=LIGADO;
				algo[ANTI_EMPATE]=DESLIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);
			  break;

		// pessoa de 32 anos (conhece pouco, mas pensa muito) - jogador simulado 7

		case 8: algo[EXECUCAO]=DESLIGADO;
				algo[MATE_DEFENSIVO_2]=LIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades);
			  break;

		// pessoa de 6 anos (mal conhece as regras) - jogador simulado 8

		case 9: algo[MATE_DEFENSIVO_1]=DESLIGADO;
				algo[MATE_OFENSIVO_2]=DESLIGADO;
				algo[ANTI_ABRE_PORTAS]=DESLIGADO;
				algo[INFLUENCIA_CENTRAL]=DESLIGADO;
				algo[ANTI_ATAQUE_DUPLO]=DESLIGADO;
			  exec=actrl.calcule_melhor_movimento(na_vez,pc,&possibilidades); // ... a muito curto prazo
			  break;
			  
	}

	pc=execute_movimento(possibilidades.x_orig[exec],possibilidades.y_orig[exec],possibilidades.x_dest[exec],
		possibilidades.y_dest[exec],pc,possibilidades.especiais[exec]);
	
	//PECAS tabuleiro::execute_movimento(int x_o, int y_o, int x_d, int y_d, PECAS pc, int especiais) // excuta um movimento em cima do tabuleiro

	gotoxy(10,23);
	printf("                                                               ");

//      io.espere_tecla();

	return pc;
}


///////////////////////////////////////////////////////
// Classe: JOGADOR - Definicao                       //
///////////////////////////////////////////////////////

// OBS.: subclasse de tabuleiro

class jogador:public tabuleiro
{
	analisador_movimento amove;
public:
	PECAS jogada(int,PECAS);
};

PECAS jogador::jogada(int na_vez, PECAS pc) // jogada conduzida por jogador humano
{
	COORD1 orig, dest;
	EPONTOS lista_pontos;
	tabuleiro tb;
	analisador_movimento amove;
	console io;
	int rodada, grande_rodada, pos, special;
//	char dump;

	grande_rodada=0;        // se ja foi executada a rotina de movimentacao uma vez
	do{
		tb.mostre_ascii(pc);
	//      gotoxy(40,23);
	//printf("%i%i%i%i",pc.roque_possivel_direito[BRANCO],pc.roque_possivel_esquerdo[BRANCO],
	//      pc.roque_possivel_direito[PRETO],pc.roque_possivel_esquerdo[PRETO]);
		rodada=0;
		if(grande_rodada>0)     // ja passou por aqui? entao nao deu certo na primeira vez
		{
			io.limpa_fundo();
			if(tb.qualcor(orig.x,orig.y,pc)!=na_vez)
				io.caixa_erro(71); else
			io.caixa_erro(73);    // "destino invalido"
			//dump=getch();
			//if(dump=='d') // DUMPING da lista de movimentos p/ teste!!!
			//{
			//	lista_pontos=amove.executa(pc,na_vez);
			//	tb.mostre_pontos(lista_pontos);
			//	tb.mostre_ascii(pc);
			//}
		}
		do{
			if(rodada>0)    // ja passou por aqui? entao a selecao nao deu certo na primeira vez
			{
				io.limpa_fundo();
				io.caixa_erro(72);    // "sem peca disponivel"
			}
			orig=io.menu_tabuleiro(na_vez,&pc,INATIVO,INATIVO);
			rodada++;
		}while(tb.qualpeca(orig.x,orig.y,pc)==INATIVO && tb.qualcor(orig.x,orig.y,pc)!=na_vez && orig.x!=-1); // teste somente para o origem

		if(orig.x!=-1)
		{
			dest=io.menu_tabuleiro(na_vez,&pc,orig.x,orig.y);        // destino sem validacao na entrada
			grande_rodada++;
		}
	} while(amove.permitido(orig.x,orig.y,dest.x,dest.y,na_vez,pc)==FALSE && orig.x!=-1);   // movimento nao existe? entao destino invalido e volte o processo

	//gotoxy(40,23);
	//printf("%i%i%i%i",pc.roque_possivel_direito[BRANCO],pc.roque_possivel_esquerdo[BRANCO],
	//      pc.roque_possivel_direito[PRETO],pc.roque_possivel_esquerdo[PRETO]);

	if(orig.x!=-1)
	{
		lista_pontos=amove.executa(pc,na_vez);  // executar analisador de movimentos em cima da posicao atual (para movimentos especiais)

		pos=qual_numero_em_lista_pontos(orig.x,orig.y,dest.x,dest.y,lista_pontos);      // qual numero tem o movimento escolhido na lista?

		special=lista_pontos.especiais[pos];    // pegar os especiais desta lista (a partir daqui roque e en passent ja estao tratados)

		if(lista_pontos.especiais[pos]>2 && lista_pontos.especiais[pos]<7)      // peao avancado? entao selecionar a alternativa desejada
		{
			io.limpa_direita_tabuleiro();
			special=io.menu_vertical(47,12,75)+3;
		}

		pc=tb.execute_movimento(orig.x,orig.y,dest.x,dest.y,pc,special);        // EXECUTAR o movimento escolhido

	}else
	{
		pc.p[0].init(-1,-1,-1,-1,' ');  // marca para saida
	}

	io.limpa_fundo();

	return pc;      // .... e retornar o tabuleiro modificado
}

///////////////////////////////////////////////////////
// Classe: JOGO - Definicao                          //
///////////////////////////////////////////////////////

// OBS.: classe "principal"

class jogo
{
	tabuleiro tab;
	computador comp;
	jogador jog;
	analisador_mate amate;
	analisador_movimento amove;
	analisador_central actrl;
	int resultado;
public:
	console io;
	void menu(void);
	void partida(int, int);
	void define_algoritmo(void);
	void ambiente_teste(void);
	void init_algoritmo(void);
	void mostre_ligado(int);
	void xeque(int,PECAS);
};

void jogo::mostre_ligado(int elemento)
{
	if(elemento)
	{
		setcolor( FOREGROUND_LIGHTGREEN | BACKGROUND_BLUE );
		printf("OK");
	} else
	{
		setcolor( FOREGROUND_LIGHTRED | BACKGROUND_BLUE );
		printf("desligado");
	}
	setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
}

void jogo::define_algoritmo(void)
// 
// rotina para poder isolar processamentos e assim isolar os problemas
// (sera desligada na versao final)
//
{
	int i, j, l;
	j=0;
	while(j!=3)
	{
		clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
		setcolor( FOREGROUND_YELLOW | BACKGROUND_BLUE );
		gotoxy(20,1);
		printf("CARACTERISICAS DO ALGORITMO PARA TESTE");
		
		setcolor( FOREGROUND_WHITE | BACKGROUND_BLUE );
		//...............................x
		gotoxy(3,3);
		printf(" 1.  Mate Ofensivo 1.....: ");
		mostre_ligado(algo[MATE_OFENSIVO_1]);
		//...............................x
		gotoxy(3,4);
		printf(" 2.  Mate Ofensivo 2.....: ");
		mostre_ligado(algo[MATE_OFENSIVO_2]);
		//...............................x
		gotoxy(3,5);
		printf(" 3.  Mate Ofensivo 3.....: ");
		mostre_ligado(algo[MATE_OFENSIVO_3]);
		//...............................x
		gotoxy(3,6);
		printf(" 4.  Mate Defensivo 1....: ");
		mostre_ligado(algo[MATE_DEFENSIVO_1]);
		//...............................x
		gotoxy(3,7);
		printf(" 5.  Mate Defensivo 2....: ");
		mostre_ligado(algo[MATE_DEFENSIVO_2]);
		//...............................x
		gotoxy(3,8);
		printf(" 6.  Anti Empate.........: ");
		mostre_ligado(algo[ANTI_EMPATE]);
		//...............................x
		gotoxy(3,9);
		printf(" 7.  Execucao............: ");
		mostre_ligado(algo[EXECUCAO]);
		//...............................x
		gotoxy(3,10);
		printf(" 8.  Anti Ataque Duplo...: ");
		mostre_ligado(algo[ANTI_ATAQUE_DUPLO]);
		//...............................x
		gotoxy(3,11);
		printf(" 9.  Anti Xeque..........: ");
		mostre_ligado(algo[ANTI_BLOQUEIO]);
		//...............................x
		gotoxy(3,12);
		printf(" 10. Anti Abre Portas....: ");
		mostre_ligado(algo[ANTI_ABRE_PORTAS]);
		//...............................x
		gotoxy(3,13);
		printf(" 11. Ataque..............: ");
		mostre_ligado(algo[ATAQUE]);
		//...............................x
		gotoxy(3,14);
		printf(" 12. Ataque Duplo........: ");
		mostre_ligado(algo[ATAQUE_DUPLO]);
		//...............................x
		gotoxy(3,15);
		printf(" 13. Xeque...............: ");
		mostre_ligado(algo[BLOQUEIO]);
		//...............................x
		gotoxy(3,16);
		printf(" 14. Defesa..............: ");
		mostre_ligado(algo[DEFESA]);
		//...............................x
		gotoxy(3,17);
		printf(" 15. Influencia Central..: ");
		mostre_ligado(algo[INFLUENCIA_CENTRAL]);
		//...............................x
		gotoxy(3,18);
		printf(" 16. Controle Linhas.....: ");
		mostre_ligado(algo[CONTROLE_LINHAS]);
		//...............................x
		gotoxy(3,19);
		printf(" 17. Proximidade Rei.....: ");
		mostre_ligado(algo[PROXIMIDADE_REI]);
		//...............................x
		gotoxy(3,20);
		printf(" 18. Liberdade Movimento.: ");
		mostre_ligado(algo[LIBERDADE_MOVIMENTO]);
		

		j=io.menu_vertical(50,10,110);
		io.limpa_direita_tabuleiro();
		switch (j)
		{
		case 0:{
					for(i=0;i<18;i++)
						algo[i]=LIGADO;
					break;
			   }
		case 1:{
					for(i=0;i<18;i++)
						algo[i]=DESLIGADO;
					break;
			   }
		case 2:{
					gotoxy(50,10);
					printf("Favor escolher elemento.");
					l=io.menu_vertical(2,1,116);
					algo[l]=!algo[l];
					break;
			   }
		}
	}
	clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
}

void jogo::ambiente_teste(void)
//
// esta rotina somente existe para teste e sera desligada na versao final!!
//
{
	int i, na_vez;
	COORD1 lugar;
	int tipo, cor, contador, codigo_mate, exec;
	EPONTOS local;
	PECAS p_local, pecas_para_teste;
	for(i=0;i<32;i++)
	{
		p_local.p[i].init(INATIVO,INATIVO,INATIVO,INATIVO,' ');
		p_local.ult.x1=INVALIDO;
//              tab.peca_out(i);
	}
	contador=0;
	i=0;
	while(i!=4 && i!=5)
	{
		tab.mostre_ascii(p_local);
		i=io.menu_vertical(48,10,86);
		io.limpa_direita_tabuleiro();
		switch (i)
		{
		case 0 : {
			p_local=tab.init();
			tab.mostre_ascii(p_local);
			break;
				 }
		case 1 : {
				for(i=0;i<32;i++) 
				p_local.p[i].init(INATIVO,INATIVO,INATIVO,BRANCO,' ');
				tab.mostre_ascii(p_local);
				break;
			}
		case 2 :        tab.mostre_ascii(p_local);
					gotoxy(1,1);
					printf("COLOCAR PECA AONDE?");
					lugar=io.menu_tabuleiro(INATIVO,&p_local,0,0);
					io.limpa_direita_tabuleiro();
					tipo=io.menu_vertical(50,12,94);
					io.limpa_direita_tabuleiro();
					cor=io.menu_vertical(50,12,102);
					contador=0;
					gotoxy(45,20);
					if(tab.qualpeca(lugar.x,lugar.y,p_local)==INATIVO)
					{
						while(contador<32 && p_local.p[contador].devolve_tipo()!=INATIVO)
							contador++;
						if(contador<32)
						{
							p_local.p[contador].init(lugar.x,lugar.y,tipo,cor,' ');
						} else
						{
							printf("ERRO: MAIS DO QUE MAXIMO!!");
							io.espere_tecla();
						}
					} else
					{
						printf("ERRO: LUGAR JA OCUPADO!");
						io.espere_tecla();
					}
					tab.mostre_ascii(p_local);
				break;
		case 3 : {
			tab.mostre_ascii(p_local);
			gotoxy(1,1);
			printf("DELETAR QUAL PECA?");
			lugar=io.menu_tabuleiro(INATIVO,&p_local,0,0);
			i=tab.qual_numero_em_lista(lugar.x,lugar.y,p_local);
			if(i!=INATIVO)
				p_local.p[i].init(0,0,INATIVO,BRANCO,' ');
			tab.mostre_ascii(p_local);
			i=0;
			break;
		}
	}
	}
	if(i==4)
	{
		io.limpa_direita_tabuleiro();
		na_vez=io.menu_vertical(50,10,106);
		io.limpa_direita_tabuleiro();
		
		p_local.roque_possivel_direito[BRANCO]=TRUE;
		p_local.roque_possivel_direito[PRETO]=TRUE;
		p_local.roque_possivel_esquerdo[BRANCO]=TRUE;
		p_local.roque_possivel_esquerdo[PRETO]=TRUE;
		// todos os roque a principio ainda possivel - o contrario sera setado no analisador

		p_local.peao_duas_casas_para_a_frente=INVALIDO; // s/ teste de en passent       
		
		local=amove.executa(p_local,na_vez);
		
		clrscr( FOREGROUND_WHITE | BACKGROUND_BLACK );

		tab.mostre_pontos(local);
		
		codigo_mate=amate.mate(na_vez,p_local);

		p_local.ataque=FALSE;

		tab.mostre_ascii(p_local);

		if(codigo_mate==FALSE)
		{
			exec=actrl.calcule_melhor_movimento(na_vez,p_local,&local);

			pecas_para_teste=tab.execute_movimento(local.x_orig[exec],local.y_orig[exec],local.x_dest[exec],local.y_dest[exec],p_local,local.especiais[exec]);
			tab.mostre_pontos(local);
			tab.mostre_ascii(pecas_para_teste);

		} else if(codigo_mate==EMPATE)
		{ 
			printf("ATENCAO: E M P A T E....");
		} else
			printf("ATENCAO: M A T E!!!");
	}
	gotoxy(50,12);
	printf("(TESTE EXECUTADO)");
	io.espere_tecla();
}

void jogo::xeque(int cor, PECAS pc)
{
	int i;
	for(i=0;i<32;i++)
	{
		if(pc.p[i].devolve_cor()==cor && pc.p[i].devolve_tipo()==REI)
		{
			if(amove.atacado(pc.p[i].devolve_x(),pc.p[i].devolve_y(),cor,pc))
				io.acusa_xeque();
		}
	}
}

void jogo::partida(int adversario1, int adversario2)  // gerenciamento de todas as formas de partida.
{
	PECAS p_local;
	analisador_movimento amove_loc;
	EPONTOS pt;
	int resultado, buffer;
	char ch;

	if(adversario1==COMPUTADOR && adversario2==COMPUTADOR)
	{
		io.caixa_atencao(40,15,frase.strg[lingua][29]);
		io.espere_tecla();
	}

	clrscr(FOREGROUND_WHITE | BACKGROUND_BLUE);

	p_local=tab.init();
	resultado=FALSE;
	tab.mostre_ascii(p_local);
	pt=amove_loc.executa(p_local,BRANCO);

	//ATENCAO p_local.p[0].devolve_x()=-1 e a marca que um jogador desistiu

	ch='X';

	while (amate.mate(BRANCO,p_local)==FALSE && p_local.p[0].devolve_x()!=-1)
	{
		if(adversario1==COMPUTADOR && adversario2==COMPUTADOR)
			while(kbhit()) ch=getch();

		if(ch=='q' || ch=='Q') return;

		xeque(BRANCO,p_local);

		if(adversario1==JOGADOR)
			p_local=jog.jogada(BRANCO,p_local); else
			p_local=comp.jogada(BRANCO,p_local);

		if(p_local.p[0].devolve_x()!=-1) 
		{
			tab.mostre_ascii(p_local);

			buffer=amate.mate(PRETO,p_local); // para nao perder tempo com processamento repetido!!!
		}

		if(buffer==MATE || buffer==EMPATE || p_local.p[0].devolve_x()==-1)
		{
			
			if(buffer==MATE)
				io.acusa_mate();    // branco venceu
				else
					if(p_local.p[0].devolve_x()==-1)
						io.acusa_desistencia(); // preto venceu (brance desistiu)
					else
						io.acusa_empate();    // empate!!
			
			return; // CAIR FORA
		} 

		xeque(PRETO,p_local);

		if(adversario1==COMPUTADOR && adversario2==COMPUTADOR)
			while(kbhit()) ch=getch();

		if(ch=='q' || ch=='Q') return;

		if(adversario2==JOGADOR)
			p_local=jog.jogada(PRETO,p_local); else
			p_local=comp.jogada(PRETO,p_local);

		tab.mostre_ascii(p_local);
	}

	buffer=amate.mate(BRANCO,p_local); // para nao perder tempo com processamento repetido!!!

	if(buffer==MATE)
		io.acusa_mate();    // preto venceu
		else
			if(p_local.p[0].devolve_x()==-1)
						io.acusa_desistencia(); // branco venceu (brance desistiu)
				else
					io.acusa_empate();    // empate!!

}

void jogo::init_algoritmo(void) // inicializa os parametros de teste do algoritmo
{
	int i;
	for(i=0;i<18;i++)
		algo[i]=LIGADO;
}

void jogo::menu(void)
{
	int modo, config;
	char gc;
	srand(1);
	tab.init_mais();
//   for(modo=0;modo<256;modo++) printf(" %i:%c ",modo,char(modo));
//      io.espere_tecla();
	gc=' ';
//      while(gc!='q')
//      {
//              gc=getch();
//              printf("%i\n",gc);
//      }
	init_algoritmo();
	io.init_frases();
	lingua=PORTUGUES;
	//do{				// ligar menu ambiente de teste aqui (comeco)
	//	clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
	//	modo=io.menu_vertical(25,12,5);
	//	clrscr( FOREGROUND_WHITE | BACKGROUND_BLUE );
	//	switch (modo)
	//	{
	//	case 0: ambiente_teste(); break;
	//	case 1: define_algoritmo(); break;
	//	}
	//}while(modo!=2);		// menu ambiente de teste (fim)
	io.titulo_completo();
	modo=1;
//      ambiente_teste();
	lingua=io.menu_vertical(20,14,21);
	io.init_frases();
	while (modo != 8)
	{
		io.titulo_completo();
		modo=io.menu_vertical(20,13,10);
		switch (modo)
		{
			//MENU PRINCIPAL
			case 0: io.sobre(); break;//Sobre o Sistema
			case 1: partida(JOGADOR,JOGADOR); break; //Jogar: Jogador x Jogador
			case 2: partida(JOGADOR,COMPUTADOR); break; //Jogar: Jogador x MONARCH
			case 3: partida(COMPUTADOR,JOGADOR); break; //Jogar: MONARCH x Jogador
			case 4: partida(COMPUTADOR,COMPUTADOR); break; //Jogar: MONARCH x MONARCH
			case 5: config=0;
					while(config!=2)
					{
						io.titulo_completo();
						config=io.menu_vertical(20,13,30);
						switch (config)
						{
							case 0: io.titulo_completo();
									lingua=io.menu_vertical(20,13,21);
									break;
							case 1: io.titulo();
									player=io.menu_vertical(10,9,40);
									break;
						}
					}
					break; //Configuracoes
			case 6: io.tutorial(); break; //Tutorial
			case 7: io.ajuda(); break; //Ajuda
			case 8: if(io.tem_certeza()==FALSE) modo=INVALIDO;
	
			//atencao ambiente de teste pode-se acessar com:
				// ambiente_teste();
		}
	} // SAIR DO PROGRAMA
	clrscr(FOREGROUND_LIGHTGRAY | BACKGROUND_BLACK);
}

///////////////////////////////////////////////////////
// PROGRAMA PRINCIPAL                                //
///////////////////////////////////////////////////////

void main(void)
{
	jogo ambiente;  // cria o ambiente
	ambiente.menu(); // executa o menu Ascii
}

void mark(int nro_marca) // somente para desenvolvimento
{
	printf("\n\n **** MARCA NRO. %i  EXECUTADA ****\n\n",nro_marca);
	while(kbhit()) getch();
	getch();
}

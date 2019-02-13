/*------------------------------------------------------*/
/* Prog    : Tp1_IFT3205-1-1.c                          */
/* Auteur  : Dennis Orozco Martinez & Kevin Laurent     */
/* Date    : 18/05/2010                                 */
/* version :                                            */
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo1.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/
/*------------------------------------------------*/
#define NAME_VISUALISER "display "
#define NAME_IMG_IN  "photograph"
#define NAME_IMG_OUT "image-Tp1_IFT3205-2-1d"

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/
/*------------------------------------------------*/
void CenterImg(float** , int, int);
int  power(int, int);
void PasseBasV(float** Img, int length, int width);

/*------------------------------------------------*/
/* IMPLEMENTATION DE FONCTIONS DEMANDEE ----------*/
/*------------------------------------------------*/
void CenterImg(float** Img, int length, int width)
  {
    int i=0;
    int j=0;

    for(i=0;i<length;i++)
      for(j=0;j<width;j++)
        {
  	  Img[i][j]=Img[i][j] * power((-1), (i+j));
        }
  }

void LogAffiche(float** Img, int k, int length, int width)
  {
    int i=0;
    int j=0;

    for(i=0;i<length;i++)
      for(j=0;j<width;j++)
        {
          Img[i][j]= k * log(1 + abs(Img[i][j]));
        }
  }

void PasseBasV(float** Img, int length, int width)
  {
    int i=0;
    int j=0;
    int x=length/2;
    int y=width/2;
    float dist=0;

    for(i=0;i<length;i++)
      for(j=0;j<width;j++)
        {
          dist=sqrt(power(i-x,2));
          if (dist >= 10)
            Img[i][j]=0;
        }
  }

int power(int x, int y){
    if(y == 0)
      return 1;
   return (x * power(x,y-1) );
  }

/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/
/*------------------------------------------------*/
int main(int argc,char **argv)
 {
  int i,j,k;
  int length,width;
  char BufSystVisuImg[100];
  float** MatriceImgR;
  float** MatriceImgI;
  float** MatriceImgM;

  /*Allocation memoire pour la matrice image*/
  MatriceImgR=LoadImagePgm(NAME_IMG_IN,&length,&width);
  MatriceImgI=fmatrix_allocate_2d(length,width);
  MatriceImgM=fmatrix_allocate_2d(length,width);

  /*Initialisation a zero de toutes les matrices */
  for(i=0;i<length;i++)
    for(j=0;j<width;j++)
      {
	MatriceImgI[i][j]=0.0;
	MatriceImgM[i][j]=0.0;
      }

  /*CENTRER*/
  CenterImg(MatriceImgR, length, width);

  /*FFT*/
  FFTDD(MatriceImgR,MatriceImgI,length,width);

  /*Supprimer par distance par rapport a l'axe V*/
  PasseBasV(MatriceImgR,length,width);
  PasseBasV(MatriceImgI,length,width);

  /*IFFT*/
  IFFTDD(MatriceImgR,MatriceImgI,length,width);
  CenterImg(MatriceImgR, length, width);

  /*Pour visu*/
  Recal(MatriceImgR,length,width);

  /*Sauvegarde de MatriceImgM sous forme d'image pgm*/
  SaveImagePgm(NAME_IMG_OUT,MatriceImgR,length,width);

  /*Liberation memoire pour les matrices*/
  free_fmatrix_2d(MatriceImgR);
  free_fmatrix_2d(MatriceImgI);
  free_fmatrix_2d(MatriceImgM);

  /*Commande systeme: visualisation de Ingout.pgm*/
  strcpy(BufSystVisuImg,NAME_VISUALISER);
  strcat(BufSystVisuImg,NAME_IMG_OUT);
  strcat(BufSystVisuImg,".pgm&");
  printf(" %s",BufSystVisuImg);
  system(BufSystVisuImg);

  /*retour sans probleme*/
  printf("\n C'est fini ... \n\n");
  return 0;
}
